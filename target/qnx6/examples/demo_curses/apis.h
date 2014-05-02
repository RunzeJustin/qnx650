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


#ifndef __API_H__
#define __API_H__

#include <aoa/aoa.h>

__BEGIN_DECLS

/*
 * This is our accessory structure to keep track of any conencted devices. We
 * often interchange the words "device" and "accessory" hence why the variables
 * referencing this struct are sometimes are called 'dev'.
 */
typedef struct acc_s {
	struct acc_s		*next;
	struct acc_s		*prev;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	aoa_hdl_t		*hdl;
	char			name[64];
	int			shutdown;
	int			idx;
} acc_t;

/*
 * This function is used to cleanup the device once it is no longer required.
 * It should be called when an application thread is no longer required.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int destroy_devices( void );

/*
 * This function handles input from the user (keystrokes).  It will continue
 * looking for characters until SIGERM is caught or SIGWINCH as we don't
 * currently handle terminal resizing.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int read_loop( void );

/*
 * This function is used to set a color in the color window.  It can be
 * called internally with a pos of -1 to reset it or externally when data
 * containing the control byte 'c' is returned from the the Android
 * application.
 *
 * @param hdl	A valid AOA handle.
 * @param pos	The position of the color to set (-1 for reset).
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int write_color( aoa_hdl_t *hdl, int pos );

/*
 * This function is used to set the slider position in the slider window. It
 * can be called internally with a pos of -1 to reset it or externally when data
 * containing the control byte 's' is returned from the the Android application.
 * application.
 *
 * @param hdl	A valid AOA handle.
 * @param pos	The position of the slider to set (-1 for reset).
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int write_slider( aoa_hdl_t *hdl, int pos );

/*
 * This function is used to setup the main curses windows.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int setup_windows( void );

/*
 * This function is used to destroy the main curses windows and return the
 * terminal to it's previous state.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int destroy_windows( void );

/*
 * This function is used to notify the curses module that a resize signal was
 * caught (SIGWINCH).  We currently don't handle a resize so this translates
 * to the equivalent of a shutdown.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int set_resize( void );

/*
 * This function is used to notify the curses module that a shutdown signal was
 * caught (SIGTERM).  This will breark our read loop allowing us to properly
 * shutdown.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int set_shutdown( void );

/*
 * This function is used to write to the console curses window.
 *
 * @return	void
 */
void write_console( const char *fmt, ... );

/*
 * This function is used to remove a device from the device list.  The device
 * is still valid until the time destory_device() is called allowing for our
 * client threads to handle the cleanup when they're completely finished. This
 * function sends a signal to our worker thread to unblock it if it is
 * currently blocked allowing it to cleanup.
 *
 * @param hdl		A valid AOA handle.
 * @param mutex		A boolean signifying if we should lock or not.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int remove_device( aoa_hdl_t *hdl, bool mutex );

/*
 * This function is used to cleanup a device and destroy the memory associated
 * with it once it is no longer required.
 *
 * @param dev	A valid device handle.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int destroy_device( acc_t *dev );

/*
 * This function is used to unblock worker threads which are currently
 * waiting at our barrier.  This will allow the thread to complete allowing
 * our application to fully shutdown.
 *
 * @return	-1 on error.
 * @return	 0 on success.
 */
int unblock_worker_threads( void );

/*
 * This function is used to get a device name from our list of devices based
 * on the aoa handle.  We append index values to our devices in order to
 * differentiate devices with the same name.
 *
 *   ex.) NEXUS (1), NEXUS (2), etc.
 *
 * @param hdl	A valid AOA handle.
 *
 * @returns	device name on success.
 * @returns	"UNKNOWN" on error.
 */
const char *get_device_name( aoa_hdl_t *hdl );

/*
 * This function is used to add a new device to our device list after it has
 * been inserted and our worker thread spawned.
 *
 * @param hdl	A valid AOA handle.
 * @param name	The name of the device to save.
 *
 * @returns	device handle on success.
 * @returns	NULL on error.
 */
acc_t *add_device( aoa_hdl_t *hdl, const char *name );

/*
 * This function is used to send data to the Android application.  It handles
 * sending a control byte and value or a buffer.
 *
 * @param dev	A valid device handle.
 * @param buf	A buffer with data to send (can be NULL).
 * @param ctrl	The ctrl byte to send.
 * @param val	The value to send with the ctrl byte.
 * @param sz	The size of the buffer.
 *
 * @returns	 0 on success.
 * @returns	-1 on error.
 */
int send_data( acc_t *dev, uint8_t *buf, uint8_t ctrl, uint8_t val, uint32_t sz );

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/aoa/examples/demo_curses/apis.h $ $Rev: 734140 $")
#endif
