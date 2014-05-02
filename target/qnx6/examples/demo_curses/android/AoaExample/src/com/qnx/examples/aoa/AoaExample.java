/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


package com.qnx.examples.aoa;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.ParcelFileDescriptor;
import android.text.InputType;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.util.Log;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.SeekBar;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.SeekBar.OnSeekBarChangeListener;

import android.graphics.Color;
import android.hardware.usb.UsbManager;
import android.hardware.usb.UsbAccessory;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class AoaExample extends Activity implements Runnable, TextView.OnEditorActionListener, 
														OnSeekBarChangeListener, OnCheckedChangeListener {

	private static final String TAG = "QNX_AOA";
	private static final String ACTION_USB_PERMISSION = "com.qnx.examples.aoa.action.USB_PERMISSION";
	private static final byte CTRL_TEXT = 't';
	private static final byte CTRL_SLIDER = 's';
	private static final byte CTRL_COLOR = 'c';
	private static final int numButtons = 5;
	private EditText inTxt;
    private EditText outTxt;
    private TextView tvColor;
    private SeekBar slider;
    private RadioGroup rGroup;
    private RadioButton[] rButtons = new RadioButton[numButtons];
    private ParcelFileDescriptor mFileDescriptor;
    private FileInputStream mInputStream;
    private FileOutputStream mOutputStream;
    private UsbManager mUsbManager;
    private UsbAccessory mAccessory;
    private PendingIntent mPermissionIntent;
    private boolean mPermissionRequestPending;
    private boolean shutdown = false;

    /*
     * This method is used to enable/disable the physical controls on the UI
     * when the device isn't plugged in or the USB stack not accessible.
     */
    public void setupView(boolean enabled) {
    	int	i;

    	inTxt.setFocusable(false);
    	inTxt.setEnabled(enabled);
    	outTxt.setEnabled(enabled);
    	tvColor.setEnabled(enabled);
    	rGroup.setEnabled(enabled);
    	slider.setEnabled(enabled);

    	for ( i=0; i<numButtons; i++ ) {
    		rButtons[i].setEnabled(enabled);
    	}
    }

    /*
     * This method is called when the device is first started.  We use it to setup
     * the USB manager and all UI controls.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	Log.d(TAG, "onCreate() called");
    	
    	super.onCreate(savedInstanceState);

        mUsbManager = (UsbManager) getSystemService(Context.USB_SERVICE);
        mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
        IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
        filter.addAction(UsbManager.ACTION_USB_ACCESSORY_DETACHED);
        filter.addAction(UsbManager.ACTION_USB_ACCESSORY_ATTACHED);
        registerReceiver(mUsbReceiver, filter);

        setContentView(R.layout.aoa_example);
        inTxt = (EditText)findViewById(R.id.msgIn);
        inTxt.setInputType(InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS);
        outTxt = (EditText)findViewById(R.id.msgOut);
        outTxt.setImeOptions(EditorInfo.IME_ACTION_DONE);
        outTxt.setInputType(InputType.TYPE_TEXT_FLAG_NO_SUGGESTIONS);
        outTxt.setOnEditorActionListener(this);
        tvColor = (TextView)findViewById(R.id.tvColor);
        rButtons[0] = (RadioButton)findViewById(R.id.rbNone);
        rButtons[1] = (RadioButton)findViewById(R.id.rbRed);
        rButtons[2] = (RadioButton)findViewById(R.id.rbGreen);
        rButtons[3] = (RadioButton)findViewById(R.id.rbBlue);
        rButtons[4] = (RadioButton)findViewById(R.id.rbYellow);
        rGroup = (RadioGroup)findViewById(R.id.radio_group);
        rGroup.check(((RadioButton)findViewById(R.id.rbNone)).getId());
        rGroup.setOnCheckedChangeListener(this);
      
        slider = (SeekBar)findViewById(R.id.slider);
        slider.setOnSeekBarChangeListener(this);
        
        setupView(false);
    }
    
    BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {
    	/*
         * This method is run when the Android device is plugged into a USB host.  We need to
         * check our permissions to ensure we have permissions.
         */
    	@Override
    	public void onReceive(Context context, Intent intent) {
    		Log.d(TAG, "mUsbReceiver: onReceive()");
    		if (ACTION_USB_PERMISSION.equals(intent.getAction())) {
    			Log.d(TAG, "Accessory attached");
                synchronized (this) {
                    UsbAccessory accessory = (UsbAccessory) intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);
                    if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
                        if (accessory != null) {
                        	Log.d(TAG, "Permissions accepted (accessory != null) for accessory = " +accessory);
                        	openAccessory(accessory);
                        }
                        else {
                        	Log.d(TAG, "Permissions accepted (accessory == null)");
                        }
                    }
                    else {
                        Log.d(TAG, "Permission denied for accessory = " +accessory);
                    }
                    mPermissionRequestPending = false;
                }
            }
        	else if (UsbManager.ACTION_USB_ACCESSORY_DETACHED.equals(intent.getAction())) {
        		Log.d(TAG, "Accesory detached");
        		UsbAccessory accessory = (UsbAccessory) intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);
        		if (accessory != null && accessory.equals(mAccessory)) {
        			Log.d(TAG, "It's our accessory detached");	
        			closeAccessory();
        			finish();
        		}
        	}
        }
    };

    /*
     * This method is called when a key is pressed on our textView.  We want to send
     * to the QNX application when the 'Done' button is pressed.
     */
    @Override
    public boolean onEditorAction(final TextView v, int actionId, KeyEvent event) {
        if (actionId == EditorInfo.IME_ACTION_DONE && mOutputStream != null) {
        	Message m;

        	/* Skip the control byte */
        	m = Message.obtain(oHandler, (int)CTRL_TEXT);
        	m.obj = (byte[])v.getText().toString().getBytes();
        	oHandler.sendMessage(m);

        	/* Clear the text field */
        	v.post(new Runnable() {
				public void run() {
					v.setText("");	
				}
			});

        	return true;
        }
        return false;
    }

    /*
     * This method is called when a radio button selection is made.  This can either be
     * called because of a user action or because the QNX application requested a change.
     * It is interesting to note that because this API doesn't notify us if it was a user
     * action or not, we send the results back to the QNX application even if the QNX
     * application made a change.  There are workarounds for this but we'll leave it like
     * this for simplicity. 
     */
    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
    	Message			m;
    	byte[]			val = new byte[1];
    	final int		index = group.indexOfChild(findViewById(checkedId));
    	final int[]	colors = { Color.TRANSPARENT, Color.RED, Color.GREEN, Color.BLUE, Color.YELLOW };

    	/* Set the background color */
    	tvColor.post(new Runnable() {
    		public void run() {
    			tvColor.setBackgroundColor(colors[index]);
    		}
    	});

    	/* Send a message with the color index to the QNX application */
	   	m = Message.obtain(oHandler, (int)CTRL_COLOR);
	   	val[0] = (byte)index;
	   	m.obj = (byte[])val;
	   	oHandler.sendMessage(m);
    }

    /*
     * This method is called when the slider button is changed.  Unlike the onCheckedChanged()
     * method, this method has a fromUser argument so we only send updates back to the QNX
     * application when the change is generated from the user.  This method can generated
     * a lot of small USB transfers as the progress is updated live.
     */
    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {    	
    	if ( fromUser ) {
    		Message m;
        	byte[] val = new byte[1];

        	/* Send a message with the slider position to the QNX application */
        	m = Message.obtain(oHandler, (int)CTRL_SLIDER);
	    	val[0] = (byte)progress;
	    	m.obj = (byte[])val;
	    	oHandler.sendMessage(m);
    	}
    }

    /*
     * This method is called when the slider button is initially touched.  We ignore this.
     */
    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
    	return;
    }
    
    /*
     * This method is called when the slider button is released.  We ignore this.
     */
    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
    	return;
    }
    
    /*
     * This method is run as a thread in the background and continuously monitors for
     * incoming USB information.  When data is received, it is passed as a message to a
     * handler where it is interpreted.  This thread will die when an exception occurs
     * which includes when we force the USB fd's to close.
     */
    public void run() {
        Message m;
    	int sz = 0;
        byte[] buffer = new byte[16384];
        
        Log.d(TAG, "Listener thread starting...");

        /* Loop while not an error */
        while (sz >= 0) {
            try {
            	/* Blocking read from our input stream */
                sz = mInputStream.read(buffer);
            } 
            catch (IOException e) {
            	Log.e(TAG, "Read failed", e);
            	break;
            }

            if (sz > 1) {
            	/* We have actual data, send it as a message for analysis */
            	m = Message.obtain(iHandler, (int)buffer[0]);
            	m.obj = (byte[])Arrays.copyOfRange(buffer, 1, sz);
            	iHandler.sendMessage(m);
            }
        }
        Log.d(TAG, "Listener thread exiting...");

        if ( sz == -1 && !shutdown ) {
        	/* Our listener thread is dead, we should exit */
        	closeAccessory();
        }
    }

    /*
     * This method is run when Android re-establishes focus of our application.  We need
     * to re-check our USB accessory permissions and re-open it if we received permission.
     */
    @Override
    public void onResume() {
    	Log.d(TAG, "onResume() called");
    	
    	super.onResume();

    	/* Figure out the USB intent */
        Intent intent = getIntent();
        Log.d(TAG, "Intent: " + intent);
        UsbAccessory[] accessories = mUsbManager.getAccessoryList();
        UsbAccessory accessory = (accessories == null ? null : accessories[0]);
        if (accessory != null) {
        	/* Do we have permission for the device? */
            if (mUsbManager.hasPermission(accessory)) {
            	Log.d(TAG, "USB permissions granted");
                openAccessory(accessory);
            }
            else {
                synchronized (mUsbReceiver) {
                    if (!mPermissionRequestPending) {
                    	Log.d(TAG, "Requesting USB permissions");
                        mUsbManager.requestPermission(accessory, mPermissionIntent);
                        mPermissionRequestPending = true;
                    }
                }
            }
         }
        else {
            Log.d(TAG, "mAccessory is null");
        }
    }
   
    /*
     * This method is run when Android loses focus of our application.  We close our
     * file descriptor thus stopping or reader thread as well when this takes place.
     */
    @Override
    public void onPause() {
    	Log.d(TAG, "onPause() called");

        super.onPause();
    }

    /*
     * This method is run when Android closes our app.  Do some final cleanup.
     */
    @Override
    public void onDestroy() {
    	Log.d(TAG, "onDestroy() called");
 
    	unregisterReceiver(mUsbReceiver);
    	super.onDestroy();
    }

    /*
     * This method is called when our accessory is opened.  We need to get the
     * file descriptor for our input/output streams, start our listener thread
     * and enable our UI.
     */
    private void openAccessory(UsbAccessory accessory) {
    	Log.d(TAG, "openAccessory(): " +accessory);
    	mAccessory = accessory;
        mFileDescriptor = mUsbManager.openAccessory(accessory);
        if (mFileDescriptor != null) {
            FileDescriptor fd = mFileDescriptor.getFileDescriptor();
            mOutputStream = new FileOutputStream(fd);
            mInputStream = new FileInputStream(fd);
            Thread thread = new Thread(null, this, "AoaExample");
            thread.start();
            setupView(true);
            Log.d(TAG, "Accesory open succeeded");
        }
        else {
            Log.d(TAG, "Accessory open failed");
        }
    }

    /*
     * This method is called when our accessory is close.  We should do some
     * cleanup such as closing our file descriptors and setting our accessory
     * handle to NULL.
     */
    private void closeAccessory() {
    	Log.d(TAG, "closeAccessory(): " +mAccessory);

    	shutdown = true;
    	if (mFileDescriptor != null) {
			try {
				mFileDescriptor.close();
			}
			catch (IOException e) {
			}
			finally {
				mFileDescriptor = null;
				mAccessory = null;
				finish();
			}	
		}
    }

    /*
     * This method is used to send a message to our QNX application.  The message
     * has two parts, the control byte (byte #1) and the message (byte #2...#n).
     * 
     * Note: Need to setup a WeakReference to get rid of the compiler warning.
     */
    Handler oHandler = new Handler() {
		@Override
        public void handleMessage(final Message msg) {
        	final byte[] in = (byte[])msg.obj;
        	final byte[] out = new byte[in.length + 1];

        	/* Build our message from the control byte and the rest of the data */
        	out[0] = (byte)msg.what;
        	System.arraycopy(in, 0, out, 1, in.length);

        	/* Send data to the application */
            new Thread(new Runnable() {
            @Override
            	public void run() {
            		try {
            			if ( mOutputStream != null ) {
            				mOutputStream.write(out);
            			}
            		}
            		catch (IOException e) {
            			Log.e(TAG, "Write failed", e);
            		}		
            	}
            }).start();
        }
    };
    
    /*
     * This method is used to receive data from our QNX application.  The first
     * byte of the message is our control byte which tells us what's being
     * requested and the rest of the data is the payload.
     * 
     * Note: Need to setup a WeakReference to get rid of the compiler warning.
     */
    Handler iHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
        	Message		m;
        	final int	id;
        	byte[]		msg_bytes = (byte[])msg.obj;
        	byte[]		val = new byte[1];
        	int			msg_int;
		
        	switch ((byte)msg.what) {
	        case CTRL_TEXT:		/* Message is text, write it */
	        	String text = new String(msg_bytes, 0, msg_bytes.length -1);
	
		    	Log.d(TAG, "Received text: " + text);
		    	inTxt.setText(text);
		    	break;
	        case CTRL_SLIDER:	/* Message is slider position, set it */
	        	msg_int = (int)msg_bytes[0];
	
		    	Log.d(TAG, "Received slider: " +msg_int);
		    	if ( msg_int == -1 ) {
		    		/* Payload is -1, it's a request for slider info */
	            	m = Message.obtain(oHandler, (int)CTRL_SLIDER);
	    	    	val[0] = (byte)slider.getProgress();
	    	    	m.obj = (byte[])val;
	    	    	oHandler.sendMessage(m);
	    		}
	    		else {
	    			slider.setProgress(msg_int);
	    		}
	    		break;
	
        	case CTRL_COLOR:	/* Message is color, set it */
        		msg_int = (int)msg_bytes[0];

        		Log.d(TAG, "Received color: " +msg_int);
        		if ( msg_int == -1 ) {
        			/* Payload is -1, it's a request for slider info */
	    			msg_int = rGroup.indexOfChild(findViewById(rGroup.getCheckedRadioButtonId()));
	            	m = Message.obtain(oHandler, (int)CTRL_COLOR);
	    	    	val[0] = (byte)msg_int;
	    	    	m.obj = (byte[])val;
	    	    	oHandler.sendMessage(m);
        		}

        		if ( msg_int < 0 || msg_int >= numButtons ) {
        			break;
       			}
        		id = msg_int;

	        	rGroup.post(new Runnable() {
	        		public void run() {
	        			rGroup.check(rButtons[id].getId());
	        		}
	        	});
	        }
        }
    };
}

