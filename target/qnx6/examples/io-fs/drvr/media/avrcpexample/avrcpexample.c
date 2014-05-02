/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. All Rights Reserved.
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

#include "avrcpexample.h"
#define avrcpexample_node_get avrcpexample_fs_node_get
#include "media_funcs.ci"
#include <sys/netmgr.h>

#define USERFUNC_WAITFOR_CHANGE(arg) 1
#define USERFUNC_GETTRACK(arg)        2
#define USERFUNC_GETMETASEQ(arg)     3

#define USERVALUE_TRACK_CHANGE        1
#define USERVALUE_METADATA_SEQ_CHANGE 2

static int pulseCode = 0;

/**
 * Function handles asyncronous pulses from the monitor thread
 *
 * @param   ctp
 * @param   code   The pulse code
 * @param   code   The pulse code
 * @param   handle The pulse code
 * @return  EOK on success
 * @return  -1 on failure
*/
static int
avrcpexample_pulse_handler( message_context_t *ctp, int code, unsigned flags, void *handle )
{
	struct avrcp_device *dep;
	int do_notify;
	int change;
	int track_index;
	int meta_sequence;


	dep = (struct avrcp_device *) handle;
	change = ctp->msg->pulse.value.sival_int;

	do_notify = 0;

	switch(change) {
	case USERVALUE_TRACK_CHANGE:
		// Check to see if the track has chagned
		track_index = USERFUNC_GETTRACK(void);
		if (track_index != dep->track_index ) {
			dep->track_index = track_index; // Update the stored track index.
			do_notify = 1;
		}
		break;
	case USERVALUE_METADATA_SEQ_CHANGE:
		// Check to see if the metadata has chagned
		meta_sequence = USERFUNC_GETMETASEQ(void);
		if (meta_sequence != dep->meta_sequence ) {
			dep->meta_sequence = meta_sequence; // Update the stored meta sequnce.
			do_notify = 1;
		}
		break;
	}

	// If there were any changes on the device, we need to notify on the
	// control point, to signal the upperlayers to request the playback structure
	// via the DMC_MEDIA_PLAYBACK_INFO device control message.
	if (do_notify && dep->mediafs.notify_fmp) {
		avrcpexample_control_notify(dep->mediafs.notify_fmp);
	}
	return 0;
}

/**
 * Function fills in the information in the .FS_info./info.xml file.
 *
 * @param   dev    Pointer to an io-fs MediaFS device structure.
 * @param   xp     Pointer to an xml buffer.
 * @return  EOK on success
 * @return  -1 on failure
*/
static int avrcp_getinfo(struct avrcp_device *dep, struct xmlbuf *xp) {

	// This will create a xml file that appears as follows:
	//
	//<?xml version="1.0" standalone="yes"?>
	//<media>
	//        <device>AVRCP</device>
	//        <type>A2DP</type>
	//</media>
	//<fsys>
	//        <type>avrcpexample</type>
	//        <mountpoint>/fs/avrcp0</mountpoint>
	//        <mountdevice>file-0-avrcpexample-4294967295-media</mountdevice>
	//</fsys>
	//<device>
	//        <driver>avrcpexample</driver>
	//        <catagory>media</catagory>
	//</device>


	// Delete previous "<media>" section
	xmlbuf_del(xp, "media");
	
	// Create a new "<media>" section
	xmlbuf_add(xp, "media", 0);
	xmlbuf_add(xp, "device", "AVRCP");
	xmlbuf_add(xp, "type", IOFS_MEDIA_TYPE_A2DP);

	// Add the device serial number	
	if (dep->dserial[0]=='\0') {
		xmlbuf_addf(xp, "serial", "f:%s-d:%d", dep->devpath, dep->fd );
	} else {
		xmlbuf_addf(xp, "serial", dep->dserial);
	}

	// Add the user friendly device name
	if (dep->dname[0]=='\0') {
		xmlbuf_addf(xp, "name", "bluetooth");
	} else {
		xmlbuf_addf(xp, "name", dep->dname);
	}
	xmlbuf_add(xp, 0, 0);
	
	// Finished adding to "<media>" section
	xmlbuf_add(xp, 0, 0);
	
	return(EOK);
}


/**
 * Function to create a directory/file structure outside the .FS_info. directory.
 * 
 * @param   dep      Pointer to an io-fs MediaFS device structure.
 * @param   handpath Array of inodes to track backwards up tree.
 * @params  rdirs    Array of readdir structures.
 * @params  nrdir    Number of readdir structures returned.
 * @params  flags    Readdir flags from io-fs level.
 * @return  0        If no more entries from reader
 * @return  1        If there are more entires.
*/
static int avrcp_readdir(struct avrcp_device *dep, unsigned handpath[], struct media_readdir *rdirs, unsigned nrdir, unsigned flags) {
	// No files live outside the .FS_info. directroy, so this function can simply
	// return 0, to indicate there are no entries.
	return 0;
}

/**
 * Function to get file node attributes
 * 
 * @param   dep      Pointer to an io-fs MediaFS device structure.
 * @param   handpath Array of inodes to track backwards up tree.
 * @param   fip      Pointer to a mediafs inode structure.
 * @params  flags    Readdir flags from io-fs level.
 * @return  EOK on success
 * @return  -1 on failure
*/
static int avrcp_getattr(struct avrcp_device *dep, unsigned handpath[], struct mediafsinode *fip, unsigned flags) {
	// No files live outside the .FS_info. directroy, so this function only has
	// to handle the root directory.
	if(handpath[0] == 0) {
		fip->fsinode.mode = S_IFDIR | 0555;
	}
	return EOK;
}

/**
 * This function handles all devctl() calls to any file under the mountpoint.
 * 
 * @param   dep      Pointer to an io-fs MediaFS device structure.
 * @param   handpath Array of inodes to track backwards up tree.
 * @param   ioflag   IO flags for the node.
 * @param   dcm      Devctl command number.
 * @param   nbytes   Number of bytes on client side.
 * @param   retval   Pointer to integer on client side for return data.
 * @return  EOK on success
 * @return  -1 on failure
*/
static int avrcp_devctl(struct avrcp_device *dep, unsigned handpath[], unsigned ioflag, int dcmd, void *data, int nbytes, int *retval) {
	union {
	     struct _media_play          play;
	     struct _media_playback      playback;
	     struct _media_settings      settings;
	     char                        string[1];  // song,album,artist,genre
	} *dcp = data;
	
	int      status         = EOK;
	int      repeat_mode    = -1;
	int      shuffle_mode   = -1;
	int      playback_state = -1;
	unsigned duration       = 0;
	size_t   size           = nbytes;
	char     tmpBuf[AVCP_METADATA_MAX+1];
	
	tmpBuf[AVCP_METADATA_MAX] = '\0';

	switch(dcmd) {
	case DCMD_MEDIA_PLAY:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_PLAY");
		// -- START DEVICECODE
		// -- TASK: Issue command to start playback on the remote device.
		//          Device control must be supported. Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_PLAY();
		// -- END DEVICECODE --
		break;

	case DCMD_MEDIA_PAUSE:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_PAUSE");
		// -- START DEVICECODE
		// -- TASK: Issue command to pause playback on the remote device.
		//          Device control must be supported. Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_PAUSE();
		// -- END DEVICECODE 
		break;

	case DCMD_MEDIA_RESUME:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_RESUME");
		// -- START DEVICECODE
		// -- TASK: Issue command to resume playback on the remote device.
		//          Device control must be supported. Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_RESUME();
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_NEXT_TRACK:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_NEXT_TRACK");
		// -- START DEVICECODE
		// -- TASK: Issue command to skip to the next track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_NEXT_TRACK();
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_PREV_TRACK:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_PREV_TRACK");
		// -- START DEVICECODE
		// -- TASK: Issue command to skip to the previous track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_PREV_TRACK();
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_FASTFWD:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_FASTFWD");
		// -- START DEVICECODE
		// -- TASK: Issue command to change to fast forward the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_FASTFWD();
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_FASTRWD:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_FASTRWD");
		// -- START DEVICECODE
		// -- TASK: Issue command to change to fast rewind the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_FASTRWD();
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_SONG:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_SONG");
		// -- START DEVICECODE
		// -- TASK: Issue command to retrieve the "title" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_GET_SONG(tmpBuf);
		// -- END DEVICECODE 
		if (status == EOK) {
			strncpy(dcp->string, tmpBuf, size);
			*retval = strlen(tmpBuf);
		}
		break;

	case DCMD_MEDIA_ALBUM:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_ALBUM");
		// -- START DEVICECODE --
		// -- TASK: Issue command to retrieve the "album" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_GET_TITLE(tmpBuf);
		// -- END DEVICECODE 
		if (status == EOK) {
			strncpy(dcp->string, tmpBuf, size);
			*retval = strlen(tmpBuf);
		}
		break;

	case DCMD_MEDIA_ARTIST:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_ARTIST");
		// -- START DEVICECODE --
		// -- TASK: Issue command to retrieve the "artist" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = USER_GET_ARTIST(tmpBuf);
		// -- END DEVICECODE --
		if (status == EOK) {
			strncpy(dcp->string, tmpBuf, size);
			*retval = strlen(tmpBuf);
		}
		break;

	case DCMD_MEDIA_GENRE:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_GENRE");
		// -- START DEVICECODE
		// -- TASK: Issue command to retrieve the "genre" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_GET_GENRE(tmpBuf);
		// -- END DEVICECODE 
		if (status == EOK) {
			strncpy(dcp->string, tmpBuf, size);
			*retval = strlen(tmpBuf);
		}
	break;

	case DCMD_MEDIA_DURATION:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_DURATION");
		// -- START DEVICECODE
		// -- TASK: Issue command to retrieve the "duration" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    duration = DEVICEFUNC_GET_DURATION();
		// -- END  DEVICECODE
		*retval = duration;
		break;

	case DCMD_MEDIA_TRACK_NUM:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_TRACK_NUM");
		// -- START DEVICECODE --
		// -- TASK: Issue command to retrieve the "track number" of the current track on the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_GET_TRACKNUM(tmpBuf);
		// -- END DEVICECODE
		if (status == EOK) {
			strncpy(dcp->string, tmpBuf, size);
			*retval = strlen(tmpBuf);
		}
		break;

	case DCMD_MEDIA_GET_SHUFFLE:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_GET_SHUFFLE");
		// -- START DEVICECODE
		// -- TASK: Issue command to retrieve the current shuffle mode from the remote device.
		//          Device control may be supported. If not supported status=ENOSUP. 
		//          Device control can fail.
		// -- PSEUDOCODE:
		//    shuffle_mode = DEVICEFUNC_GET_SHUFFLE();

		// -- TASK: Translate the user shuffle modes to MediaFS shuffle modes.
		switch(shuffle_mode) {
		case 0:
			dcp->settings.value = SHUFFLE_OFF;
			break;
		case 1:
			dcp->settings.value = SHUFFLE_TRACKS;
			break;
		case 2:
			dcp->settings.value = SHUFFLE_ALBUMS;
			break;
		default:
			dcp->settings.value = SHUFFLE_OFF;
		}
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_SET_SHUFFLE:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_SET_SHUFFLE");
		// -- START DEVICECODE
		// -- TASK: Translate the MediaFS shuffle mode to the remote device mode.
		// -- EXAMPLECODE 
		switch (dcp->settings.value) {
		case SHUFFLE_OFF:
			shuffle_mode = 0;
			break;
		case SHUFFLE_TRACKS:
			shuffle_mode = 1;
			break;
		case SHUFFLE_ALBUMS:
			shuffle_mode = 2;
			break;
		default:
			shuffle_mode = 0;
		}

		// -- TASK: Issue command to set the current shuffle mode on the remote device.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_SET_SHUFFLE(shuffle_mode);
		// -- END DEVICECODE
		break;


	case DCMD_MEDIA_GET_REPEAT:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_GET_REPEAT");
		// -- START DEVICECODE
		// -- TASK: Issue command to retrieve the current repeat mode from the remote device.
		// -- PSEUDOCODE:
		// repeat_mode = DEVICEFUNC_GET_SHUFFLE();

		// -- TASK: Translate the user shuffle mode to MediaFS shuffle mode.
		switch( repeat_mode ){
			case 0:
				dcp->settings.value = REPEAT_OFF;
				break;
			case 1:
				dcp->settings.value = REPEAT_ONE_TRACK;
				break;
			case 2:
				dcp->settings.value = REPEAT_ALL_TRACKS;
				break;
			default:
				dcp->settings.value = 0;
		}
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_SET_REPEAT:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_SET_REPEAT");
		// -- START DEVICECODE
		// -- TASK: Translate the MediaFS repeat mode to the remote device mode.
		// -- EXAMPLECODE 
		switch(dcp->settings.value){
		case REPEAT_OFF:
			repeat_mode = 0;
			break;
		case REPEAT_ONE_TRACK:
			repeat_mode = 1;
			break;
		case REPEAT_ALL_TRACKS:
			repeat_mode = 2;
			break;
		default:
			repeat_mode = 0;
		}
		// TASK: Issue command to set the current repeat mode on the remote device.
		// -- PSEUDOCODE:
		//    status = DEVICEFUNC_SET_REPEAT(shuffle_mode);
		// -- END DEVICECODE
		break;

	case DCMD_MEDIA_PLAYBACK_INFO:
		if(dep->verbose) 
			fs_log(AVRCP_NAME, _SLOG_INFO, "GOT DCMD_MEDIA_PLAYBACK_INFO");

		memset(&dcp->playback, 0, nbytes); // Clear the playback structure;

		dcp->playback.index    = dep->track_index;   // Fill in the current playing index.
		dcp->playback.metaseq  = dep->meta_sequence; // Fill in the current metaseq.

		// -- START DEVICECODE 
		// -- TASK: Issue command to get thre remote device play status
		// -- PSEUDOCODE:
		//    playback_state = DEVICEFUNC_GET_PLAYBACK_STATE();

		// -- TASK: Translate from the remote device playback state to MeidaFS state.
		// -- EXAMPLECODE 
		switch ( playback_state ) {
			case 0:
				dcp->playback.state = PLAYBACK_STATE_STOP;
				break;
			case 1:
				dcp->playback.state = PLAYBACK_STATE_PLAY;
				break;
			case 2:
				dcp->playback.state = PLAYBACK_STATE_PAUSE;
				break;
			default:
				dcp->playback.state = PLAYBACK_STATE_STOP;
				break;
		}
		// -- END DEVICECODE --
		break;

	default:
		return _RESMGR_DEFAULT;
	}

	return(status);
}

/*
 * This function is the function that runs in a thread to monitor
 * for device state changes.
 *
 * @param   Pointer to the MediaFS device structure.
 */
static void* avrcpexample_monitor_thread ( void *pArg )
{
	struct avrcp_device *dep;
	int change;

	dep = (struct avrcp_device *) pArg ;

	if(dep->verbose) 
		fs_log(AVRCP_NAME, _SLOG_INFO, "Started Monitor Thread");

	// -- START DEVICECODE 
	// -- TASK: Monitor the device for changes in track, playbackstate
	//          or metadata. If there are any changes update the values
	//          that will be returned in the playback structure 
	//          and do a notification on the control point.
	// -- EXAMPLECODE 
	while(1) {
		// Wait for a device state change
		change = USERFUNC_WAITFOR_CHANGE(void);
	
		MsgSendPulse(dep->mediafs.device.driver->iface.gop->coid,
		             12,
		             pulseCode,
		             change);
		delay(500); 
	}
	// -- END DEVICECODE --
}

/*
 * This function is called to initalize the device, before mounting
 * the filesystem.
 *
 * @param   Pointer to the MediaFS device structure.
 * @return	EOK on success.
 * @return	-1 on error.
 */
static int avrcp_init_dev(struct avrcp_device *dep) {

	int            status = EOK;
	char           tmpBuf[AVCP_METADATA_MAX+1];
	pthread_attr_t attr;
	
	tmpBuf[AVCP_METADATA_MAX] = '\0';
	
	dep->dserial[0] = '\0';
	dep->dname[0] = '\0';
	
	// -- START DEVICECODE 
	// -- TASK: Get the remote device address 
	// -- PSEUDOCODE:
	//    status = DEVICEFUNC_GET_SERIAL(tmpBuf);
	// -- END DEVICECODE
	if (status == EOK)  {
		strncpy( dep->dserial, tmpBuf, AVCP_METADATA_MAX );
	}
	
	// -- START DEVICECODE
	// -- TASK: Get the remote device name
	// -- PSEUDOCODE:
	//    status = DEVICEFUNC_GET_NAME(tmpBuf);
	// -- END DEVICECODE
	if (status == EOK)  {
		strncpy( dep->dname, tmpBuf, AVCP_METADATA_MAX );
	}
	
	// Set device parameters
	dep->mediafs.device.bus = "file";
	dep->mediafs.device.busdevno = minor(dep->mediafs.device.driver->iface.gop->blkfs->mount.dev);
	dep->mediafs.device.unit = dep->fd;

	//Register the pulse handler
	pulseCode = pulse_attach(dep->mediafs.device.driver->iface.gop->dispatch,
	                         MSG_FLAG_ALLOC_PULSE,
	                         0,
	                         avrcpexample_pulse_handler,
	                         dep);
	
	/* If the pulse attach fails destroy everything and die */
	if( pulseCode  == -1) {
		return -1;
	}

	// Start a thread to handle asyncronous device changes.
    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
    pthread_create( NULL, &attr, &avrcpexample_monitor_thread, dep);
	
	IFDBG print_mounted("media-avrcp", dep);
	
	return(status);
}


/*
 * This function is used to detect the presence of a remote device to mount.  The process of mounting is a
 * two stage process.  The first stage involves establishing a valid connection to the resource manager or
 * avrcp controller and the second stage ensures that the remote device actually is connected.
 *
 * If the avrcp controller or resource manager is not available, then we use this to "poll" 
 * until we detect that the resource is available for mounting.  
 * The poll rate is set by the user in the configuration options or the default value.
 *
 * @param   Pointer to the MediaFS device structure.
 * @return	Pollrate in milliseconds.
 */
static unsigned avrcp_timer(struct avrcp_device *dep) {

	int ismounted = 1;
	int canplay   = 1;

	// -- START DEVICECODE 
	// -- TASK: Try to Open/Connect to the avrcp resource. If fails return
	//          the pollrate. 
	// -- EXAMPLECODE 
    //
	//    if(dep->fd == -1 && dep->devpath != NULL) {
	//        dep->fd = open(dep->devpath, O_RDONLY);
	//    }
	//    if(dep->fd == -1) {  //No device to attach to, don't probe
	//        return 1000;
	//    }
	//
	// -- END DEVICECODE
	
	ismounted = (dep->mediafs.device.flags & DEVICE_ISMOUNTED);
	
	// -- START DEVICECODE 
    // -- TASK: Check if remote device can play or not set canplay flag 
	// -- PSEUDOCODE:
	//    canplay = USER_CANPLAY(tmpBuf);
	// -- END DEVICECODE 

	if((ismounted && canplay) || (!ismounted && !canplay)) {
		//Do nothing already mounted or unmounted;
	} else if(!ismounted && canplay) {
		// Mount the filesystem      
		if(avrcp_init_dev(dep) == EOK) {
			media_devio_mount(&dep->mediafs);
			if(dep->verbose) {
				fs_log(AVRCP_NAME, _SLOG_INFO, "*** MOUNT ***");
			}
		}
	} else if(ismounted && !canplay) { 
		// Unmount the filesystem      
		if(dep->verbose) {
			fs_log(AVRCP_NAME, _SLOG_INFO, "*** UMOUNT ***");
		}
		media_devio_umount(&dep->mediafs);
	}
	
	return 1000;
}

/**
 * Function to allow options to be passed into module level
 *
 * @param   dev      Pointer to a io-fs MediaFS device structure.
 * @param   optargs  Pointer to arguments passed in on the commandline.
 * @param   cond     Pointer to conditions string.
 * @return  EOK on success
 * @return  -1 on failure
*/
static int avrcp_options(struct avrcp_device *dep, char *optargs, const char *cond) {
	char *value;
	int   err;

	struct subopt        subopt = {
		.name = dep->mediafs.device.driver->iface.module->name,
		.conditions = cond,
	};
	enum {
		OPT_USE,
		OPT_DEVICE,
		OPT_VERBOSE,
		OPT_MOUNT,
		LAST_OPT
	};
	static const char * const opts[] ={
		[OPT_USE]       = "use",
		[OPT_DEVICE]    = "device"         "\0?={devpath}",
		[OPT_VERBOSE]   = "verbose"        "\0?={number}",
		[OPT_MOUNT]     = "mount"          "\0?={path}",
		[LAST_OPT]      = 0
	};
	static const char    * const examples[] ={
		"device",
		   "\tThe device to be used to communicate with the remote media source.",
		"verbose",
		   "\tIncrease verbosity.",
		"mount",
		   "\tMount filesystem here.",
		NULL
	};
	
	// -- START DEVICECODE
	// -- TASK: Fill in the default device for connection if FD based.
	// -- EXAMPLECODE
		dep->devpath = strdup("/dev/avrcp_manager");
	// -- END DEVICECODE
	
	while (optargs && *optargs) {
		if (subopt.skip) {
			if ((err = suboptif(&subopt, &optargs)) != EOK) {
				return err;
			}
			continue;
		}
	
		value = NULL;
		switch (getsubopt(&optargs, (char * const *)opts, &value)) {
			case OPT_USE:
				subopthelp(&subopt, opts, examples, 0);
				return EL2HLT;
			
			case OPT_DEVICE:     //Always require a device
				if(value == NULL) {
					fs_log(AVRCP_NAME, _SLOG_ERROR, "Invalid device");
					return EINVAL;
				}
				snprintf(dep->devpath, sizeof(dep->devpath), value);
				break;

			case OPT_VERBOSE:    //Assume verbose = 1 if they don't specify it
				dep->verbose = strtosize((value == NULL) ? "1" : value, NULL, 0, GIGA(1));
				break;
			
			case OPT_MOUNT:
				if(value) {
					dep->mediafs.device.forcemnt = strdup(value);
				}
			    break;
			
			default:
				if ((err = suboptif(&subopt, &value)) != EOK) {
				return err;
				}
				break;
		}
	}

	// Default mount point for the mediaFS file system.  
	// %# will generate a new number of each instance of the
	// driver run.  i.e. avrcp0, avrcp1, avrcp2
	if(dep->mediafs.device.forcemnt == NULL) {
		dep->mediafs.device.forcemnt = "/fs/avrcp%#";
	}
	
	return(EOK);
}

/**
 * Function entry point for module. Allocates memory for the internal
 * device structure, registers function callbacks, and start the monitor
 * timer.
 *
 * @param   dirv     Pointer to an io-fs driver structure.
 * @param   flags    io-fs flags.
 * @param   options  String options passed from command line.
 * @return  EOK on success
 * @return  -1 on failure
*/
static int avrcp_mount(struct driver *drp, int flags, const char *options) {
	struct avrcp_device      *dep;
	int                     err;
	char                    *s;
           	
	s = strdupa(options);
	if (!(dep = (struct avrcp_device *)media_devio_alloc(drp, s))) {
		return EAGAIN;
	}
	
	// Calls from media.c to here
	dep->mediafs.funcs.readdir = avrcp_readdir;
	dep->mediafs.funcs.getattr = avrcp_getattr;
	dep->mediafs.funcs.devctl  = avrcp_devctl;
	dep->mediafs.funcs.getinfo = avrcp_getinfo;
	
	dep->devpath    = NULL;
	dep->fd         = -1;
	dep->dname[0]   = '\0';
	dep->dserial[0] = '\0';
	
	if ((err = avrcp_options(dep, s, 0)) != EOK) {
		return err;
	}
	
	dep->mediafs.funcs.timer = avrcp_timer;
	timer_setdev(&dep->mediafs.device, 1);
	
	return EOK;
}

#ifdef CHECK_MODULE_VALID   // We don't need to check if static linking
static const struct check check[] = {
	CHECK_COMMON_STRUCTS,
	{ 0 }
};
#endif

// io-fs/media initialization code
static struct driver avrcp_drvr = {
	.iface = {.type = IFACE_DRVR, },
	.device_size = sizeof(struct avrcp_device),
	.funcs = {
		.mount = avrcp_mount,
	}
};

const struct fsmodule   IOFS_MODULE(MODULE_NAME) = {
	.name = IOFS_STR(MODULE_NAME),
	.version = IOFS_VER_CURRENT,
#ifdef CHECK_MODULE_VALID   // We don't need to check if static linking
	.check = check,
#endif
	.ifaces = {
		&avrcp_drvr.iface,
		&mediafs_fsys.iface,
		0
	},
};


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/avrcpexample.c $ $Rev: 680892 $")
#endif
