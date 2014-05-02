/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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


#ifndef _MME_EVENT_H_INCLUDED
#define _MME_EVENT_H_INCLUDED

#ifndef _MME_TYPES_H_INCLUDED
#include <mme/types.h>
#endif

#ifndef _IOMEDIA_TYPES_H_INCLUDED
#include <mm/types.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

__BEGIN_DECLS

/**
 * This defines the different classes of events.
 * It is a bit mask and they can be OR'd together.
 */
typedef int mme_event_class_t;
#define MME_EVENT_CLASS_PLAY     (0x0001)
#define MME_EVENT_CLASS_SYNC     (0x0002)
#define MME_EVENT_CLASS_COPY     (0x0004)
#define MME_EVENT_CLASS_GENERAL  (0x0008)
#define MME_EVENT_CLASS_METADATA (0x0010)
#define MME_EVENT_CLASS_ALL      (0xFFFF) /* ALL Classes OR'd together. */

/*
 * Defines types of MME commands that can return play errors
 */
typedef enum mme_command_type {
    MME_COMMAND_TYPE_PLAY			= 1,
    MME_COMMAND_TYPE_BUTTON			= 2
} mme_command_type_t;

/**************************************************************************************
 *
 *                                   MME Events
 *
 * This file describes the events that can be delivered by the MME to clients who are
 * connected to it.
 *
 **************************************************************************************/

typedef enum mme_event_type {
	/**
	 * Name:  
	 *     	MME_EVENT_NONE
	 *
	 * Description:  
	 *    	Indicates that no 'single' type events are in the clients queue.  The
	 *    	global and transient data are both valid and can be checked.
	 *
	 * Delivered When:  
	 *    	Never delivered
	 *
	 * Event Data:  
	 * 		0  (no data)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      Not defined
	 */
	MME_EVENT_NONE 				= 0,
	
	/**
	 * Name:  
	 * 		MME_EVENT_TIME
	 *
	 * Description:
	 * 		A specified amount of time has passed in the playback of a track.
	 *
	 * Delivered When:
	 * 		Not currently delivered.
	 *
	 * Event Data:
	 * 	    Snapshot of current Time information (mme_time_t)
	 *
	 * DB Tables Updated:
	 * 		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TIME,
	
	/**
	 * Name:  
	 * 		MME_EVENT_FILECHANGE   (deleted old name)
	 * 		MME_EVENT_TRACKCHANGE  (new name)
	 *
	 * Description:
	 * 		A track change occured while playing.
	 *
	 * Delivered When:
	 * 		When the file being rendered at the output device switches from one
	 * 		track to another.
	 *
	 * Event Data:
	 * 		The new fid/bid as well as offset of the track that is now playing (mme_trackchange_t)
	 *
	 * DB Tables Updated:
	 * 		nowplaying
	 * 		tracksessions
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TRACKCHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_PLAYLIST
	 *
	 * Description:
	 * 		A playlist changed.
	 *
	 * Delivered When:
	 * 		Not delivered.  Not implemented
	 *
	 * Event Data:
	 *
	 * DB Tables Updated:
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_PLAYLIST,
	
	/**
	 * Name:  
	 * 		MME_EVENT_PLAYSTATE
	 *
	 * Description:
	 * 		The playstate on the controlcontext has changed.
	 *
	 * Delivered When:
	 * 		The playback state has changed
	 *
	 * Event Data:
	 * 		playstatespeed (mme_playstate_speed_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_PLAYSTATE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_FINISHED
	 *
	 * Description:
	 * 		Finished playing a track session.  No other playback will occur automatically.
	 *
	 * Delivered When:
	 * 		A track sessions's last track finishes playing, and repeat it turned off.
	 *
	 * Event Data:
	 * 		trksessionid that is effected (mme_event_data_t.trksessionid)
	 *
	 * DB Tables Updated:
	 *		tracksessions
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_FINISHED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MEDIACOPIER_COPYFID
	 *
	 * Description:
	 * 		Finished copying a file
	 *
	 * Delivered When:
	 * 		A file is completely copied
	 *
	 * Event Data:
	 * 		The copy information (mme_copy_info_t)
	 *
	 * DB Tables Updated:
	 * 		library
	 * 		library_*
	 * 		copyqueue
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_MEDIACOPIER_COPYFID,
	
	/**
	 * Name:
	 * 		MME_EVENT_USERMSG
	 *
	 * Description:
	 * 		An MME user event.
	 *
	 * Delivered When:
	 * 		Can be delivered whenever any custom module in the MME or in a
	 * 		renderer needs to deliver a user message.
	 *
	 * Event Data:
	 * 		Starts with a unique null terminated string to identify the source
	 * 		of the message. The format is of the message varies by source.
	 *
	 * DB Tables Updated:
	 *
	 * Class:
	 *		No specific class. Can be any class depending on source:
	 *		MME_EVENT_CLASS_GENERAL
	 *		MME_EVENT_CLASS_PLAY
	 *		MME_EVENT_CLASS_SYNC
	 *		MME_EVENT_CLASS_COPY
	 *		MME_EVENT_CLASS_METADATA
	 *
	 */
	MME_EVENT_USERMSG,
	
	/**
	 * Name:  
	 * 		MME_EVENT_OUTPUTATTRCHANGE
	 *
	 * Description:
	 * 		One of the output's attributes have changed.
	 *
	 * Delivered When:
	 * 		When any output attribute changes on an output.
	 *
	 * Event Data:
	 * 	    The output ID of the output (uint64_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_OUTPUTATTRCHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_REPEATCHANGE
	 *
	 * Description:
	 * 		The repeat setting was changed on the control context.
	 *
	 * Delivered When:
	 * 		After the repeat setting was chagned on the control context
	 * 		This can occur because a client calls mme_setrepeat( ), or because
	 * 		a new tracksession is set for the control context.
	 *
	 * Event Data:
	 * 		The new repeat setting (mme_mode_repeat_t)
	 *
	 * DB Tables Updated:
	 * 		tracksessions
	 * 		controlcontexts
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_REPEATCHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_RANDOMCHANGE
	 *
	 * Description:
	 * 		The random setting was changed for the control context.
	 *
	 * Delivered When:
	 * 		After the random setting was changed for the control context.
	 * 		This can occur because a client calls mme_setrandom( ), or because
	 * 		a new tracksession is set for the control context.
	 *
	 * Event Data:
	 * 		The new random setting for the control context (mme_mode_random_t)
	 *
	 * DB Tables Updated:
	 * 		tracksessions
	 * 		controlcontexts
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_RANDOMCHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SCANMODECHANGE
	 *
	 * Description:
	 * 		The scan mode setting was changed to a different value for
	 * 		the control context.
	 *
	 * Delivered When:
	 * 		The scan mode setting was changed to a different value for
	 * 		the control context.
	 *
	 * Event Data:
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_SCANMODECHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_1PASSCOMPLETE
	 *
	 * Description:
	 * 		The files pass of synchronization was completed.
	 *
	 *      The files pass updates the library, folders, and playlists table
	 *      with all files/tracks and playlists found on the device.  Ones that
	 *      use to exist but are no longer on the device are removed.
	 *
	 * 		No metadata has been gathered at this point.
	 *
	 * Delivered When:
	 * 		The files pass is complete.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 * 		library
	 * 		folders
	 * 		playlists
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_1PASSCOMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNCCOMPLETE
	 *
	 * Description:
	 * 		Synchronization of the mediastore is complete.
	 *
	 * Delivered When:
	 * 		All synchronization steps are complete for the mediastore that were requested.
	 * 		All tables are as accurate as possible.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		library
	 * 		library_*
	 * 		folders
	 * 		playlists
	 * 		playlistdata
	 * 		mediastores
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNCCOMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_UPDATE
	 *
	 * Description:
	 * 		Database content related to a media store has been updated.
	 *
	 * Delivered When:
	 * 		The MME has written new data to the database. This event informs
	 * 		The user about which media store the changes are associated with and
	 * 		information related to the source of the changes.
	 * 
	 *   NOTE: An event will be delivered during sync operations per media store
	 *      per operation ID per flags value.
	 *
	 * Event Data:
	 * 		Type: mme_ms_update_data_t
	 *
	 * 		The msid that is being synchronized, and the number of added files
	 * 		and folders, the synchronization pass under which the changes were
	 * 		made (if any) and the operation ID of the synchronization process
	 * 		(if directed sync was used).
	 * 		The timestamp field is the value of the MME's internal timestamp
	 * 		that the 'last_sync' field of all library entries adjust during this
	 * 		update is set to.
	 *
	 * DB Tables Updated:
	 * 		Depends on which sync pass (if any) made the database change.
	 *
	 * 		Not in a sync operation: (mme_ms_update_event_t.flags == 0)
	 * 			library
	 * 			library_*
	 * 
	 * 		Files pass: (mme_ms_update_event_t.flags == MME_SYNC_OPTION_PASS_FILES)
	 * 			library
	 * 			folders
	 * 			playlists
	 * 			mediastores
	 * 			
	 * 		Metadata pass: (mme_ms_update_event_t.flags == MME_SYNC_OPTION_PASS_METADATA)
	 * 			library
	 * 			library_*
	 * 			folders
	 * 			mediastores
	 *
	 * 		Playlist pass: (mme_ms_update_event_t.flags == MME_SYNC_OPTION_PASS_PLAYLISTS)
	 * 			playlists
	 * 			playlistsdata
	 * 			folders
	 * 			mediastores
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_UPDATE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SHUTDOWN
	 *
	 * Description:
	 * 		The mme can be requested to shutdown by any client.  This event allows
	 * 		other clients to know that the MME was requested to shutdown.
	 *
	 * Delivered When:
	 * 		Before the shutdown process begins, immediately after receiving the request to
	 * 		shutdown.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_GENERAL
	 */
	MME_EVENT_SHUTDOWN,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SHUTDOWN_COMPLETED
	 *
	 * Description:
	 *      The MME was requested to shutdown.  Once this event is delivered it indicates
	 *      that the MME has finished its shutdown process and is no longer active.
	 *      The MME must be terminated and restarted to perform actions again.
	 *
	 * Delivered When:
	 *      The shutdown process is complete.  Playback and sync have stopped.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_GENERAL
	 */
	MME_EVENT_SHUTDOWN_COMPLETED,

	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNCFIRSTFID
	 *
	 * Description:
	 * 		During a files pass sync, the first new file that is playable by the
	 * 		MME was found. This is delivered so clients can start playback as
	 * 		soon as possible if desired. However, if there are files to be
	 * 		removed from the database, this event is not emitted until after all
	 * 		those files are removed. This means that once this event is emitted,
	 * 		the receiver can be sure that all database items are valid.
	 *
	 * Delivered When:
	 * 		The first new playable file is found and placed in the library once
	 * 		deletion from the database of removed media store items is complete.
	 *
	 * Event Data:
	 * 		The fid of the first file. (mme_first_fid_data_t.fid)
	 * 		The media store ID the first file is on. (mme_first_fid_data_t.msid)
	 * 		he timestamp field is the value of the MME's internal timestamp
	 * 		that the 'last_sync' field of the library entry associated with this
	 * 		update is set to.
	 *
	 * DB Tables Updated:
	 * 		library
	 * 		folders
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNCFIRSTFID,
	
	/**
	 * Name:  
	 * 		MME_EVENT_AUTOPAUSECHANGED
	 *
	 * Description:
	 * 		The setting for autopause was changed for the control context.
	 *
	 * Delivered When:
	 * 		Any client changes the autopause setting for the control context
	 *
	 * Event Data:
	 * 		The new autopause setting.  1 for enabled, 0 for disabled. (uint64_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_AUTOPAUSECHANGED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_PLAYAUTOPAUSED
	 *
	 * Description:
	 * 		A track is being played, but is starting in the pause state waiting 
	 * 		for client interaction to begin playback using mme_resume( ).
	 *
	 * Delivered When:
	 * 		A file is started in pause state because autopause is enabled.
	 *
	 * Event Data:
	 * 		Reason for auto-pausing (mme_playautopaused_t).
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_PLAYAUTOPAUSED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_PLAY_ERROR
	 *
	 * Description:
	 * 		A playback error has occurred.
	 *
	 * Delivered When:
	 * 	    Various playback errors will cause this event to be generated, 
	 *      the event data will determine the cause.
	 *
	 * Event Data:
	 * 		mme_play_error_t error code
	 *
	 * DB Tables Updated:
	 *		Error dependent.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_PLAY_ERROR,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SYNC_ERROR
	 *
	 * Description:
	 * 		An error occurred during sync'ing.
	 *
	 * Delivered When:
	 * 	    Various sync errors will cause this event to be generated, 
	 *      the event data will determine the cause.
	 *
	 * Event Data:
	 * 		mme_sync_error_t error code
	 *
	 * DB Tables Updated:
	 *		Error dependent.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_SYNC_ERROR,
	
	/**
	 * Name:  
	 * 		MME_EVENT_COPY_ERROR
	 *
	 * Description:
	 * 		An error occurred during copying.
	 *
	 * Delivered When:
	 * 	    Various copy errors will cause this event to be generated, 
	 *      the event data will determine the cause.
	 *
	 * Event Data:
	 * 		mme_copy_error_t error code
	 *
	 * DB Tables Updated:
	 *		Error dependent.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_COPY_ERROR,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MEDIACOPIER_STARTFID
	 *
	 * Description:
	 * 		A file copy has started.
	 *
	 * Delivered When:
	 * 		The file copy process begins.
	 *
	 * Event Data:
	 * 		The copy information (mme_copy_info_t)
	 *
	 * DB Tables Updated:
	 * 		copyqueue
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_MEDIACOPIER_STARTFID,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MEDIACOPIER_SKIPFID
	 *
	 * Description:
	 * 		Copying of the specified fid was skipped
	 *
	 * Delivered When:
	 * 		Mediacopier is disabled or playback given priority of media source
	 *
	 * Event Data:
	 * 		The copy information (mme_copy_info_t)
	 *
	 * DB Tables Updated:
	 * 		copyqueue
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_MEDIACOPIER_SKIPFID,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MEDIACOPIER_COMPLETE
	 *
	 * Description:
	 * 		There are no more files to copy.  Media copying is not running anymore.
	 *
	 * Delivered When:
	 * 		The last file in the copyqueue is copied.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 * 		copyqueue
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_MEDIACOPIER_COMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MEDIACOPIER_DISABLED
	 *
	 * Description:
	 * 		The mediacopier operation was disabled. Normally emitted in response
	 *      to a user request to stop copying before the operation is complete.
	 *
	 * Delivered When:
	 * 		Copying is stopped before it would normally complete.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 * 		copyqueue
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_MEDIACOPIER_DISABLED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SYNCABORTED
	 *
	 * Description:
	 * 		Synchronization on the mediastore was aborted before finishing
	 * 		completely. This can happen for many reasons, such as the device
	 * 		was removed, the sync was cancelled by the user, or some other
	 * 		serious failure.
	 *
	 * Delivered When:
	 * 		Sync is stopped on the mediastore before it completes successfully.
	 *
	 * Event Data:
	 * 		The sync data, providing the mediastore that is being synced,
	 * 		the operation ID (0 for non-directed) for the sync operation and
	 * 		the sync error type. (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_SYNCABORTED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_SYNC_SKIPPED
	 *
	 * Description:
	 * 		If synchronization was not started automatically on a mediastore
	 * 		this event is delivered. The user can request a manual sync at this
	 * 		point.
	 *
	 * Delivered When:
	 * 		A mediastore is inserted, and a manual sync can be requested.
	 *
	 * Event Data:
	 * 		msid of the mediastore that was not auto synced. (uint64_t)
	 *
	 * DB Tables Updated:
	 * 		slots
	 * 		mediastores
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_SYNC_SKIPPED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_STARTED
	 *
	 * Description:
	 * 		Synchronization has begun on a mediastore
	 *
	 * Delivered When:
	 * 		Sync starts on a mediastore.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		slots
	 * 		mediastores
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_STARTED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_2PASSCOMPLETE
	 *
	 * Description:
	 * 		The metadata pass of synchronization is complete.  Metadata in the
	 * 		library tables should be accurate now for the mediastore being
	 * 		synced.
	 *
	 * Delivered When:
	 * 		The metadata pass completes, and data has been written to the
	 * 		database.
	 *
	 * Event Data:
	 * 		The sync data, providing the mediastore that is being synced
	 * 		and the operation ID (0 for non-directed) for the sync operation.
	 * 		(mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		library
	 * 		library_*
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_2PASSCOMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_3PASSCOMPLETE
	 *
	 * Description:
	 *      The playlist pass of synchronization is complete. The playlist pass
	 *      synchronizes device playlists with the database.
	 *
	 * Delivered When:
	 *      The playlist pass sync completes, and its results are available in
	 *      the database.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		playlists
	 * 		playlistdata
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_3PASSCOMPLETE,
	
	/**
	 * Name:  
	 *
	 * Description:
	 * 		Sent when a media store is to be synchronized, but is put on the
	 * 		pending list instead due to a lack of availability of sync threads.
	 *
	 * Delivered When:
	 * 		After the mediastores table is updated and there are no sync threads
	 * 		to sync it further.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_PENDING,
	
	
	/**
	 * Name:  
	 * 		MME_EVENT_DVD_STATUS
	 *
	 * Description:
	 * 		Event sent to indicate a change in the status of DVD playback.
	 *
	 * Delivered When:
	 * 		On changes to:
	 * 			- title
	 * 			- chapter
	 * 			- domain
	 * 			- forbidden uop
	 *
	 * Event Data:
	 * 		mm_dvd_status_event_t data
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_DVD_STATUS,
	
	/**
	 * Name:  
	 * 		MME_EVENT_VIDEO_STATUS
	 *
	 * Description:
	 * 		Event sent to indicate a video status change in the media being
	 * 		played.
	 *
	 * Delivered When:
	 * 		Whenever the video resolution changes (initial resolution set, and
	 * 		then whenever the source resolution or aspect ratio changes). 
	 *
	 * Event Data:
	 * 		mm_video_status_t data
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_VIDEO_STATUS,
	
	/**
	 * Name:  
	 * 		MME_EVENT_TRKSESSION
	 *
	 * Description:
	 * 		The tracksession that the control context is using has changed.  Can
	 * 		occur because of resuming mediastores, mme_settrksession( ).
	 *
	 * Delivered When:
	 * 		A new trksessionid is set for the control context. 
	 *
	 * Event Data:
	 * 		trksessionid for the new tracksession (uint64_t)
	 *
	 * DB Tables Updated:
	 * 		controlcontexts
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TRKSESSION,
	
	/**
	 * Name:  
	 * 		MME_EVENT_NEWOUTPUT
	 *
	 * Description:
	 * 		A new output device was detected in the system.  It can be attached
	 * 		to zones.If it is already part of a zone that is being used
	 * 		currently for playback, it will be auto-attached.
	 *
	 * Delivered When:
	 * 		A new output device is detected by the MME.
	 *
	 * Event Data:
	 * 		The output ID of the device (uint64_t);
	 *
	 * DB Tables Updated:
	 * 		outputdevices
	 */
	MME_EVENT_NEWOUTPUT,
	
	/**
	 * Name:  
	 * 		MME_EVENT_OUTPUTREMOVED
	 *
	 * Description:
	 * 		An output was removed from the system.  If a zone contained only one
	 * 		active output device and it is the one that is removed, playback
	 * 		will stop.
	 *
	 * Delivered When:
	 * 		The MME detects that an output device was removed.
	 *
	 * Event Data:
	 * 		The output ID of the device (uint64_t);
	 *
	 * DB Tables Updated:
	 * 		outputdevices
	 */
	MME_EVENT_OUTPUTREMOVED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_STATECHANGE
	 *
	 * Description:
	 * 		A mediastore state change notification. This event replaces
	 * 		MME_EVENT_MS_INSERTED and MME_EVENT_MS_REMOVED.
	 *
	 * Delivered When:
	 * 		A media store is inserted (and changes state from non-existent or
	 * 		unavailable to active or available).
	 * 		A media store is removed (and changes state from active or available
	 * 		to unavailable).
	 * 		A media store is pruned (and changes state to non-existent).
	 * 		A media store changes state from active to available or vice versa.
	 *
	 * Event Data:
	 * 		The msid of the new mediastore  (mme_ms_statechange_t.msid)
	 * 		The old state of the mediastore (mme_ms_statechange_t.old_state)
	 * 		The new state of the mediastore (mme_ms_statechange_t.new_state)
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 * 		slots (on some state changes)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_STATECHANGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_NOWPLAYING_METADATA
	 *
	 * Description:
	 * 		The metadata for the nowplaying file has been updated.
	 *
	 * Delivered When:
	 * 		While playing a track, it's metadata is updated after the MME_EVENT_TRACKCHANGE
	 * 		is delivered.
	 *
	 * Event Data:
	 * 		none
	 *
	 * DB Tables Updated:
	 * 		nowplaying
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_NOWPLAYING_METADATA,
	
	/**
	 * Name:  
	 * 		MME_EVENT_TRKSESSIONVIEW_UPDATE
	 *
	 * Description:
	 * 		The tracksession view has had an update (more data written).
	 *
	 * Delivered When:
	 * 		A new chunk of data is written to the trksessionview table.
	 *
	 * Event Data:
	 * 		trksessionid which is effected (uint64_t)
	 *
	 * DB Tables Updated:
	 * 		trksessionview
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TRKSESSIONVIEW_UPDATE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_TRKSESSIONVIEW_COMPLETE
	 *
	 * Description:
	 * 		The tracksession view is done being updated.
	 *
	 * Delivered When:
	 * 		The final chunk of data is written to the trksessionview.
	 *
	 * Event Data:
	 * 		trksessionid which is effected (uint64_t)
	 *
	 * DB Tables Updated:
	 * 		trksessionview
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TRKSESSIONVIEW_COMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_TRKSESSIONVIEW_INVALID
	 *
	 * Description:
	 * 		The tracksession view is no longer valid. It will be deleted.
	 *
	 * Delivered When:
	 * 		The tracksession is changed, before the delete of an unused tracksessionview is deleted.
	 *
	 * Event Data:
	 * 		trksessionid which is effected (uint64_t)
	 *
	 * DB Tables Updated:
	 * 		trksessionview
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_TRKSESSIONVIEW_INVALID,
	
	/**
	 * Name:  
	 * 		MME_EVENT_FINISHED_WITH_ERROR
	 *
	 * Description:
	 * 		Stopped playing a track session prematurely because of errors.  The HMI
	 *      can call mme_next( ) to try to go to the next track continuing playback
	 *      within the track session.
	 *
	 * Delivered When:
	 * 		A track sessions's had errors playing and was stopped.  Equivalent to
	 *      MME_EVENT_FINISHED
	 *
	 * Event Data:
	 * 		trksessionid that is effected (mme_event_data_t.trksessionid)
	 *
	 * DB Tables Updated:
	 *		tracksessions
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_FINISHED_WITH_ERROR,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_FOLDER_STARTED
	 *
	 * Description:
	 * 		Describes a folder that has started synchronization.
	 *
	 * Delivered When:
	 * 		Synchronization of a folder has started.
	 *      On the files pass, this is emitted after the folder has been
	 *      inserted into the database.
	 *      On the metadata pass, this is emitted before the contents of the
	 *      folder go through metadata pass synchronization.
	 *
	 * Event Data:
	 *      mme_folder_sync_data_t, the number of files, folders and playlists
	 *      is 0. The timestamp field is set to 0 and not used for this event.
	 *
	 * DB Tables Updated:
	 * 		Folders table.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_FOLDER_STARTED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_FOLDER_COMPLETE
	 *
	 * Description:
	 * 		Event emitted when synchronization of all files in a folder
	 * 		has been completed, and when the folders in the folder have been
	 * 		enumerated.
	 *
	 * Delivered When:
	 * 		Non-recursive synchronization of a folder has completed.
	 *
	 * Event Data:
	 * 		mme_folder_sync_data_t;
	 * 		Files pass:
	 *          The number of files, folders and playlists is the number that
	 *          were added during the pass.
	 *  
	 *      Metadata pass:
	 *          The number of files is the number of files for which
	 *          the metadata was changed. The number of folders and playlists is
	 *          always 0. The timestamp field is set to the value of the
	 *          'last_sync' column in the folders table.
	 *  
	 *      Playlist pass:
	 *          The number of playlists that were synchronized during the pass.
	 *
	 * DB Tables Updated:
	 * 		Folders table (syncflags and last_sync changed).
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_FOLDER_COMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE
	 *
	 * Description:
	 * 		Event emitted when synchronization of all folders in a folder.
	 *
	 * Delivered When:
	 * 		Recursive synchronization of a folder has completed. It is not
	 * 		emitted on a non-recursive synchronization of a folder.
	 *
	 * Event Data:
	 * 		mme_folder_sync_data_t;
	 * 		The number of files and playlists is always 0 (not used).
	 * 		The number of folders is number of folders in this folder that were
	 * 		synchronized (as part of recursive sync of this folder).
	 * 		The timestamp field is set to 0 and not used for this event.
	 *
	 * DB Tables Updated:
	 * 		Folders table (syncflags changed).
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_METADATA_LICENSING
	 *
	 * Description:
	 * 		When using a metadata service that requires special licensing
	 * 		requirements such as displaying a logo, this event is delivered
	 *
	 * Delivered When:
	 * 		At the start of usage of metadata service
	 *
	 * Event Data:
	 * 		mme_event_metadata_licensing_t;
	 * 		If the sync is occuring on a mediastore entirely then the msid will
	 * 		be set, and fid will be 0. If the sync is per file then fid will be
	 * 		set and msid will be 0.
	 * 		The license field will contain the licensing requirement.
	 *
	 * DB Tables Updated:
	 * 		None.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_METADATA_LICENSING,
	
	/**
	 * Name:  
	 * 		MME_EVENT_PLAY_WARNING
	 *
	 * Description:
	 * 		When playing, and there are conditions occuring that may
	 *      affect the quality of playback, this event is emitted.
	 *
	 * Delivered When:
	 * 		Potential playback problems are detected by io-media.
	 *
	 * Event Data:
	 * 		mm_warning_info_t data
	 *
	 * DB Tables Updated:
	 *		None.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_PLAY_WARNING,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_DETECTION_ENABLED
	 *
	 * Description:
	 * 		Event emitted when mediastore detection is enabled.
	 *
	 * Delivered When:
	 * 		The MME has successfully read path monitoring configuration
	 *      and connected to it.
	 *      For example, MCD configuration has been parsed and the MME
	 *      has successfully opened all required MCD rule logical files.
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 *      All mediastores tables entry in the database that may have been
	 *      set as active or available are now marked as unavailable.
	 *      (Media store state change events were emitted for these.)
	 * 		Additionally, media store state changes may be processed from this
	 *      point on.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_DETECTION_ENABLED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_DETECTION_DISABLED
	 *
	 * Description:
	 * 		Event emitted when mediastore detection is disabled.
	 *
	 * Delivered When:
	 * 		Device detection has been disabled (by a shutdown() command).
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 * 		none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_DETECTION_DISABLED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_FIRST_EXISTING_FID
	 *
	 * Description:
	 *      During a files pass sync, the first existing file that is playable
	 *      by the MME was found.  This is delivered so clients can start
	 *      playback as soon as possible if desired.
	 *  
	 *      This is different from the MME_EVENT_MS_SYNCFIRSTFID event as that
	 *      event is emitted only by added files after all deleted are removed
	 *      from the database that need to be.
	 *
	 * Delivered When:
	 *      The first existing playable file is found that is already in the
	 *      library.
	 *
	 * Event Data:
	 * 		The fid of the first file. (mme_first_fid_data_t.fid)
	 *      The media store ID the first file is on.
	 *      (mme_first_fid_data_t.msid)
	 *      The timestamp field is the value of the time of the start of the
	 *      files pass.
	 *
	 * DB Tables Updated:
	 * 		none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_FIRST_EXISTING_FID,
	
	/**
	 * Name:  
	 * 		MME_EVENT_COPY_FATAL_ERROR
	 *
	 * Description:
	 * 		A non-recoverable error occurred during copying and the copyqueue
	 * 		entry has been deleted because it is expected the same error would
	 * 		continue to occur.  The DeleteOnNonRecoverableError configuration
	 * 		variable must be set to "true" to enable this event and the 
	 * 		associated deletion.
	 *
	 * Delivered When:
	 * 	    A corrupted file is detected or there is an authorization failure
	 * 	    and the copyqueue entry has been deleted.
	 *
	 * Event Data:
	 * 		mme_copy_error_t error code (mme_event_data_t.copy_error)
	 *
	 * DB Tables Updated:
	 *		Error dependent.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_EVENT_COPY_FATAL_ERROR,
	
	/**
	 * Name:  
	 * 		MME_EVENT_METADATA_INFO
	 *
	 * Description:
	 *		When a request to retrieve metadata about a entry is issued
	 *		via the mme_metadata_get_info_XXX() API function calls
	 *		a metadata request id is returned to the client.  If the request
	 *      was issued in an asynchronous manner an event will be generated
	 *		as an indication of completion.
	 * 		
	 * Delivered When: 
	 *		Either on completion of the loading of the requested metadata or
	 * 		upon failure of the request.
	 * 
	 * Event Data:
	 *		A mme_event_metadata_info_t structure is returned, with the
	 *		corresponding metadata request id. Only if the error element
	 *		is set to EOK is the data valid.
	 *
	 * DB Tables Updated:
	 * 		none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_METADATA
	 */
	MME_EVENT_METADATA_INFO,
	
	/**
	 * Name:  
	 * 		MME_EVENT_METADATA_IMAGE
	 *
	 * Description:
	 *      When a request to load an image from metadata is issued via the
	 *      mme_metadata_image_load() API function call a metadata image request
	 *      id is returned to the client. If the request was issued in an
	 *      asynchronous manner an event will be generated as an indication of
	 *      completion.
	 * 		
	 * Delivered When: 
	 *		Either on completion of the loading of the requested image or
	 * 		upon failure of the request.
	 *
	 * Event Data:
	 *		A mme_event_metatadata_image_t structure is returned, with the
	 *		corresponding metadata request id. Only if the error element
	 *		is set to EOK is the data valid.
	 *
	 * DB Tables Updated:
	 * 		none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_METADATA
	 */
	MME_EVENT_METADATA_IMAGE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_BUFFER_TOO_SMALL
	 *
	 * Description:
	 *      Delivered to a client when the event buffer on the client side is
	 *      too small to fetch any events from the MME. The payload indicates
	 *      the next message size as well as the full queue size to fetch.
	 * 		
	 * Delivered When: 
	 * 		A client requests an event but does not have enough room to hold it.
	 *
	 * Event Data:
	 * 		mme_event_queue_size_t
	 *
	 * DB Tables Updated:
	 * 		none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_GENERAL
	 */
	MME_EVENT_BUFFER_TOO_SMALL,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE
	 *
	 * Description:
	 *      All database entries that are no longer in a folder have been
	 *      deleted from the database.
	 *
	 * Delivered When:
	 *      During files pass synchronization, if a folder was previously
	 *      synchronized, this event is emitted once all items are deleted from
	 *      the database that have been determined as having been removed from
	 *      the folder.
	 *  
	 *      After this event, users can be sure that any items in the database
	 *      that are shown as being in the folder will be valid items.
	 *
	 * Event Data:
	 *      mme_folder_sync_data_t;
	 *      ID of media store folder is on.
	 *      ID of folder for which trim is complete.
	 *      Pass is always 1 (files pass flag value).
	 *      num_files is number of files deleted from database in this folder.
	 *      num_folders is number of child folders deleted from database in this
	 *      folder.
	 *      num_playlists is number of playlists deleted from database in this
	 *      folder.
	 *      Operation ID of sync operation.
	 *      Timestamp is start time of sync for which trim is complete.
	 *
	 * DB Tables Updated:
	 * 		Folders table.
	 *      Library table.
	 *      Playlist and playlist data tables.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE,
	
	/**
	 * Name:  
	 * 		MME_EVENT_MS_DB_SYNC_COMPLETE
	 *
	 * Description:
	 *      The database synchronization pass of synchronization is complete.
	 *      This pass tells database synchronization plug-ins what has changed
	 *      in the MME's library table.
	 *
	 * Delivered When:
	 *      The pass completes, and it's told all plug-ins about the changes.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mme_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		db_sync
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_MS_DB_SYNC_COMPLETE,

	/**
	 * Name:  
	 * 		MME_EVENT_MEDIA_STATUS
	 *
	 * Description:
	 * 		Event sent to indicate a change in the status of media playback.
	 *
	 * Delivered When:
	 * 		On changes to:
	 * 			- title
	 * 			- chapter
	 * 			- angle
	 * 			- subtitle
	 * 			- audio
	 *
	 * Event Data:
	 * 		mm_media_status_event_t
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_MEDIA_STATUS,

	/**
	 * Name:  
	 * 		MME_EVENT_DEFAULT_LANGUAGE
	 *
	 * Description:
	 *      This event indicates when the default language has been set or was attempted
	 *      to be set but has failed.
	 *
	 * Delivered When:
	 *      After a request to set the default language has been made.
	 *
	 * Event Data:
	 *       An error code if there was an error setting the default language. EOK on success.
	 *       The new default language, on error the previous set language.
	 *
	 * DB Tables Updated:
	 *       Not related to database updates.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_GENERAL
	 */
	MME_EVENT_DEFAULT_LANGUAGE,

	/**
	 * Name:  
	 * 		MME_EVENT_ZONEOUTPUT_CHANGE
	 *
	 * Description:
	 * 		An output has been attached or detached.
	 *
	 * Delivered When:
	 * 		When any output is attached or detached from a zone.
	 *
	 * Event Data:
	 * 		The zoneid, outputid, operation and status of the change. (mme_zoneoutput_change_t)
	 *
	 * DB Tables Updated:
	 *		zoneoutputs table is updated.
	 *
     * Class:
     *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_ZONEOUTPUT_CHANGE,

	/**
	 * Name:
	 *		MME_EVENT_MEDIACOPIER_COPYSTATUS
	 * 
	 * Description:
	 *		A status update from the mediacopier.
	 * 
	 * Delivered When:
	 *		At a configurable interval as requested by an MME client.
	 * 
	 * Event Data:
	 *		cqid, srcfid, dstfid, and time or byte copied information. (mme_copy_status_t)
	 * 
	 * DB Tables Updated:
	 *		None.
	 * 
	 * Class:
	 *		MME_EVENT_CLASS_COPY
	 * 
	 */
	MME_EVENT_MEDIACOPIER_COPYSTATUS,

	/**
	 * Name:  
	 * 		MME_EVENT_PREQUEUEING_CHANGED
	 *
	 * Description:
	 * 		The setting for prequeueing was changed for the control context.
	 *
	 * Delivered When:
	 * 		Any client changes the prequeueing setting for the control context
	 *
	 * Event Data:
	 * 		The new prequeueing setting.  1 for enabled, 0 for disabled. (uint64_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_PREQUEUEING_CHANGED,
	
	/**
	 * Name:  
	 * 		MME_EVENT_BOOKMARKRESUME_CHANGED
	 *
	 * Description:
	 * 		The setting for resume bookmarks was changed for the control context.
	 *
	 * Delivered When:
	 * 		Any client changes the resume bookmarks setting for the control context
	 *
	 * Event Data:
	 * 		The new resume bookmarks setting.  1 for enabled, 0 for disabled. (uint64_t)
	 *
	 * DB Tables Updated:
	 *		Not related to database updates
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_EVENT_BOOKMARKRESUME_CHANGED,

	/**
	 * Name:  
	 * 		MME_EVENT_PRUNE
	 *
	 * Description:
	 * 		Sent when database pruning is active as a status or progress update.
	 *
	 * Delivered When:
	 * 		Prune status changes.
	 *
	 * Event Data:
	 * 		mme_event_prune_t
	 *
	 * DB Tables Updated:
	 *		Library, folders, exif, playlistdata, playlists, mediastores.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_SYNC
	 */
	MME_EVENT_PRUNE,
} mme_event_type_t;


typedef enum mme_play_error_type {
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_NONE
	 *
	 * Description:
	 * 		No play error
	 *
	 * Delivered When:
	 * 		Never (placeholder)
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 *	    None	
	 */
	MME_PLAY_ERROR_NONE              = 0, 
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_NOTSPECIFIED
	 *
	 * Description:
	 *      Playback failed, and no other error codes applied, or the error reason
	 *      is not specified.
	 *
	 * Delivered When:
	 *      playback on a track fails.
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 *	    None	
	 */
	MME_PLAY_ERROR_NOTSPECIFIED,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_CORRUPT
	 *
	 * Description:
	 *      The file to play was corrupt.  The MME believes it had the correct
	 *      codec to play the file.
	 *
	 * Delivered When:
	 * 		Playback begins on a file, and is found to be corrupt.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *	    library  (playable is set to 0)	
	 */
	MME_PLAY_ERROR_CORRUPT,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_TRACKSESSIONEMPTY
	 *
	 * Description:
	 * 		The tracksession being played is empty, therefore there is nothing to
	 * 		play.
	 *
	 * Delivered When:
	 * 		Selecting the next track to play, the MME will send this if it finds the
	 * 		tracksession to be empty.
	 *
	 * Event Data:
	 *      trksessionid:  the trksession ID that is empty (mme_play_error_t.trksessionid)
	 *
	 * DB Tables Updated:
	 *	    None	
	 */
	MME_PLAY_ERROR_TRACKSESSIONEMPTY,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_DEVICEREMOVED
	 *
	 * Description:
	 *      The device being played from has been removed from the system.  The active
	 *      tracksession has had its state saved.  Playback will stop automatically, an
	 *      event for the stopped state will also be delivered afterwards.
	 *
	 * Delivered When:
	 *      The device being played from is removed.
	 *
	 * Event Data:
	 *      msid:  the mediastore ID that was removed. (mme_play_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    trksessions
	 */
	MME_PLAY_ERROR_DEVICEREMOVED,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_NOOUTPUTDEVICES
	 *
	 * Description:
	 *      Failed playback because there were no output devices attached.
	 *
	 * Delivered When:
	 *      Playback starts on a file and no output devices were attached.
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_NOOUTPUTDEVICES,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_OUTPUTFAILEDATTACH
	 *
	 * Description:
	 *      Failed to attach an output for playback that is part of the current
	 *      zone.  This is a warning that it was not attached.
	 *
	 * Delivered When:
	 *
	 * Event Data:
	 *      outputid:  The outputid that failed to attach (mme_play_error_t.outputid)
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_OUTPUTFAILEDATTACH,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_MEDIABUSY
	 *
	 * Description:
	 *      Playback attempted to start on a file, but the mediastore it is
	 *      on is currently locked for use.
	 *
	 * Delivered When:
	 *      Playback starts, but fails because the device is in use.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_MEDIABUSY,
	
	/**
	 * Name:
	 *      MME_PLAY_ERROR_NOEXIST
	 *
	 * Description:
	 *      The file that was to be played does not exist. This can occur
	 *      because the file was attempted to play before the files pass sync
	 *      could determine that it was removed from the media.
	 *
	 * Delivered When:
	 *      Playback starts on a file, and is found to not exist.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none.
	 */
	MME_PLAY_ERROR_NOEXIST,
	
	/**
	 * Name:
	 *      MME_PLAY_ERROR_NETWORK
	 *
	 * Description:
	 *      A network error occured and playback failed because of this.
	 *
	 * Delivered When:
	 *      During playback at any time and a network error occured.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_NETWORK,
	
	/**
	 * Name:
	 *      MME_PLAY_ERROR_UNSUPPORTEDCODEC
	 *
	 * Description:
	 *      Playback started and it was determined that the file's encoding is
	 *      done with a codec that the renderer did not have a codec for.
	 *
	 * Delivered When:
	 *      Playback starts and no codec was found to decode the stream.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      library.playable is set to 0.
	 */
	MME_PLAY_ERROR_UNSUPPORTEDCODEC,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_READ
	 *
	 * Description:
	 *      A read error occured while trying to read the media
	 *
	 * Delivered When:
	 *      While playing at any time and a read error occurs.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_READ,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_REGION
	 *
	 * Description:
	 *      The media has a different region setting then the hardware
	 *      and therefore playback is not allowed.
	 *
	 * Delivered When:
	 *      Playback starts and the fid to play has a different region than
	 *      the hardware.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_REGION,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_PARENTALCONTROL
	 *
	 * Description:
	 *      Playback failed because parental controls prevented playback.
	 *
	 * Delivered When:
	 *      Playback starts, but parental controls prevent it.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_PARENTALCONTROL,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_NORIGHTS
	 *
	 * Description:
	 *      There is DRM protecting the file, and the system is not
	 *      licensed to decrypt it.
	 *
	 * Delivered When:
	 *      Playback starts and fails because of DRM.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_NORIGHTS,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_INPUTUNDERRUN
	 *
	 * Description:
	 *      Playback had an issue filling it's buffers from the input media.
	 *      This is only a warning but should result in an audio gap.  This
	 *      is usually caused by slow input media
	 *
	 * Delivered When:
	 *      There is a buffer under run
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_INPUTUNDERRUN,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_OUTPUTUNDERRUN
	 *
	 * Description:
	 *      There was an output underrun.  This results in an audio gap
	 *      and is usually cause by the system decode process being too slow
	 *      to keep up with audio output at a 1x rate.  This is only a warning.
	 *
	 * Delivered When:
	 *      The output buffer drains during playback.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_OUTPUTUNDERRUN,
	
	/**
	 * Name:  
	 *      MME_PLAY_ERROR_INVALIDFID
	 *
	 * Description:
	 *      The fid requested to play was invalid.  This can be because
	 *      there is no fid by that number in the library table, or
	 *      that fid does not exist in the current active track session.
	 *
	 * Delivered When:
	 *      Playback starts on a fid and it is found to be invalid.
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * DB Tables Updated:
	 *      none
	 */
	MME_PLAY_ERROR_INVALIDFID,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_BLOCKEDUOP
	 *
	 * Description:
	 * 		The user operation was blocked by the navigator.
	 *
	 * Delivered When:
	 * 		A play or button command is attempted when it isn't allowed.
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 * 		The type of user operation that was attempted. (mme_play_error_t.command_error.command)
	 * 		If it's a MME_COMMAND_TYPE_PLAY, data is fid (mme_play_error_t.command_error.fid).
	 * 		If it's a MME_COMMAND_TYPE_BUTTON, data is button (mme_play_error_t.command_error.button)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_PLAY_ERROR_BLOCKEDUOP,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_BLOCKEDDOMAIN
	 *
	 * Description:
	 * 		The user operation was blocked by the navigator.
	 *
	 * Delivered When:
	 * 		A play or button command is attempted when it isn't allowed.
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 * 		The type of user operation that was attempted. (mme_play_error_t.command_error.command)
	 * 		If it's a MME_COMMAND_TYPE_PLAY, data is fid (mme_play_error_t.command_error.fid).
	 * 		If it's a MME_COMMAND_TYPE_BUTTON, data is button (mme_play_error_t.command_error.button)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_PLAY_ERROR_BLOCKEDDOMAIN,
	
	/**
	 * Name:  
	 * 		MME_PLAY_ERROR_INVALIDSAVEDSTATE
	 *
	 * Description:
	 * 		The MME tried to resume a previous state but something is wrong
	 * 		with the saved state data.
	 *
	 * Delivered When:
	 * 		When a trksession or bookmark is resumed and something (corruption,
	 * 		data doesn't match disk, etc.) is wrong with the previously saved data.
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 *      track.fid    : The file ID that was corrupt (may be a device FID).
	 *      track.offset : The offset of the track that caused the error.
	 *
	 * Class:
	 *      MME_EVENT_CLASS_PLAY
	 */
	MME_PLAY_ERROR_INVALIDSAVEDSTATE,

 	/**
 	 * Name:  
 	 * 		MME_PLAY_ERROR_RENDERER_RESOURCE_UNAVAILABLE
 	 *
 	 * Description:
	 * 		The renderer could not aquire some resource needed for playback.
 	 *
 	 * Delivered When:
	 * 		The underlying renderer (typically io-media) could not acquire a
	 * 		neccessary resource. For example, in a hardware optimized system
	 * 		this error might be delivered if the DSP is locked or already in
	 * 		use.
 	 *
 	 * DB Tables Updated:
 	 *	    None	
 	 *
 	 * Event Data:
	 *      track.fid    : The file ID that failed to play.
	 *      track.offset : The offset of the track that caused the error.
 	 *
 	 * Class:
 	 *      MME_EVENT_CLASS_PLAY
 	 */
 	MME_PLAY_ERROR_RENDERER_RESOURCE_UNAVAILABLE
 

} mme_play_error_type_t;

typedef enum mme_sync_error_type {
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_NONE
	 *
	 * Description:
	 * 		No sync error
	 *
	 * Delivered When:
	 * 		Never (placeholder)
	 *
	 * Event Data:
	 *      none
	 *
	 * DB Tables Updated:
	 *	    None	
	 */
	MME_SYNC_ERROR_NONE              = 0,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_MEDIABUSY
	 *
	 * Description:
	 * 		The media was busy and sync was not allowed to start on it
	 * 		because of concurrency rules.
	 *
	 * Delivered When:
	 * 		Sync should have started on a device
	 *
	 * Event Data:
	 *      msid:  The mediastore that sync skipped. (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MME_SYNC_ERROR_MEDIABUSY,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_READ
	 *
	 * Description:
	 * 		While syncing, there was a read error that prevented
	 * 		the device from being synced.  This can be caused by a scratched
	 * 		disc for example.
	 *
	 * Delivered When:
	 * 		Sync fails because of a read error.
	 *
	 * Event Data:
	 *      msid:  The mediastore that had a read error. (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MME_SYNC_ERROR_READ,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_NETWORK
	 *
	 * Description:
	 * 		There was a network error while syncing.  This can be caused when a
	 * 		metadata lookup required network access but failed.
	 *
	 * Delivered When:
	 * 		Sync has a network error.
	 *
	 * Event Data:
	 *      msid: The mediastore that failed sync because of a network error. (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MME_SYNC_ERROR_NETWORK,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_UNSUPPORTED
	 *
	 * Description:
	 * 		The mediastore to sync is not a supported mediastore by the
	 * 		MME.
	 *
	 * Delivered When:
	 * 		Sync starts and determines the device to be unsupported.
	 *
	 * Event Data:
	 *      msid:  The mediastore that is not supported. (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MME_SYNC_ERROR_UNSUPPORTED,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_USERCANCEL
	 *
	 * Description:
	 * 		Sync was stopped by a client request.
	 *
	 * Delivered When:
	 * 		A client requests that sync be stopped.
	 *
	 * Event Data:
	 *      msid:  The mediastore that sync was stopped on. (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MME_SYNC_ERROR_USERCANCEL,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_NOTSPECIFIED
	 *
	 * Description:
	 * 		A non specified error occured that is not classified by other error types.
	 *
	 * Delivered When:
	 * 		At any time during sync
	 *
	 * Event Data:
	 *      msid:  The mediastore that had an non specified sync error (mme_sync_error_t.msid)
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_NOTSPECIFIED,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_LIB_LIMIT
	 *
	 * Description:
	 * 	    First pass synchronization for the media store reached a
	 *      configuration limit, and no further entries may be added to the
	 *      library table.
	 *
	 * Delivered When:
	 * 		When the maximum number of database entries has been reached
	 *      during files pass sync.
	 *
	 * Event Data:
	 *      msid:  The mediastore that the limit was reached on.
	 *      operation_id: The sync operation's operation ID.
	 *      param: The limit that the media store reached.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_LIB_LIMIT,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_FOLDER_LIMIT
	 *
	 * Description:
	 * 	    First pass synchronization for the media store reached a
	 *      configuration limit, and no further entries may be added to the
	 *      library table.
	 *
	 * Delivered When:
	 *      When the maximum number of folder items presented to the MME has
	 *
	 * Event Data:
	 *      msid:  The mediastore that the limit was reached on.
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_FOLDER_LIMIT,
	
	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_DATABASE
	 *
	 * Description:
	 * 	    Synchronization encountered a database problem.
	 *
	 * Delivered When:
	 *      A database operation fails during synchronization.
	 *
	 * Event Data:
	 *      TBD.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_DATABASE,

	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_FOLDER_DEPTH_LIMIT
	 *
	 * Description:
	 * 	    Skipped synchronizing a folder to avoid syncronizing beyond the
	 * 	    configured max folder depth.
	 *
	 * Delivered When:
	 *      The first time we skip over a folder because of max folder depth
	 *      configuration limit is reached.
	 *
	 * Event Data:
	 *      msid:  The mediastore that the limit was reached on.
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_FOLDER_DEPTH_LIMIT,

	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_DB_LIMIT
	 *
	 * Description:
	 * 	    The maximum database size has been reached, no further data may be
	 * 	    added to the library and playlist tables.
	 *
	 * Delivered When:
	 * 		When the MME notices that the max DB size has been reached and no
	 * 		further pruning can be done on the DB to reduce its size.
	 *
	 * Event Data:
	 *      msid:  The mediastore that the limit was reached on.
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_DB_LIMIT,

	/**
	 * Name:  
	 * 		MME_SYNC_ERROR_FOLDER_NONMEDIA_LIMIT
	 *
	 * Description:
	 *      First pass synchronization for the media store reached the
	 *      non-media file limit, and no entries for this folder will be
	 *      added to the library table.
	 *
	 * Delivered When:
	 *      When the maximum number of non-media items in a folder has hit
	 *      the configured limit.
	 *
	 * Event Data:
	 *      msid:  The mediastore that the limit was reached on.
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MME_SYNC_ERROR_FOLDER_NONMEDIA_LIMIT,
} mme_sync_error_type_t;

typedef enum mme_copy_error_type {
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_NONE
	 *
	 * Description:
	 * 		No sync error
	 *
	 * Delivered When:
	 * 		Never (placeholder)
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 *      none
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_NONE              = 0,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_MEDIABUSY
	 *
	 * Description:
	 * 		Media copying attempted to run on a mediastore that was already in use.
	 * 		It will skip that fid and go the next in the copy queue.
	 *
	 * Delivered When:
	 * 		When attempting to sync a fid, and the mediastore is busy.
	 *
	 * DB Tables Updated:
	 *	    None
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_MEDIABUSY,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_MEDIAFULL
	 *
	 * Description:
	 * 		Could not copy to the destination mediastore because it has no space
	 * 		left.
	 *
	 * Delivered When:
	 * 		Copying and the destination mediastore does not have enough space left.
	 *      Can be delivered before copying starts, or in the middle of a copy.
	 *      May also be delivered if the destination mediastore has library
	 *      table limits configured and copying the file would cause it to
	 *      exceed that limit.
	 *
	 * DB Tables Updated:
	 *	    None
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_MEDIAFULL,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_DEVICEREMOVED
	 *
	 * Description:
	 * 		While copying the source or destination mediastore were removed from the system.
	 *
	 * Delivered When:
	 * 		Never (placeholder)
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *      msid: The msid that was removed. (mme_copy_error_t.msid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_DEVICEREMOVED,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_WRITE
	 *
	 * Description:
	 * 		There was a write error while copying.
	 *
	 * Delivered When:
	 * 		A write error occurs.
	 *
	 * DB Tables Updated:
	 *	    None
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_WRITE,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_READ
	 *
	 * Description:
	 * 		There was a read error while copying.
	 *
	 * Delivered When:
	 * 		A read error occurs.
	 *
	 * DB Tables Updated:
	 *	    None
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_READ,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_FILEEXISTS
	 *
	 * Description:
	 *      The destination file already exists.  Copy failed.
	 *
	 * Delivered When:
	 * 		Copy is going to begin, but the destination file exists.
	 *
	 * DB Tables Updated:
	 *	    None	
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_FILEEXISTS,
	
	/**
	 * Name:  
	 * 		MME_COPY_ERROR_NOTSPECIFIED
	 *
	 * Description:
	 * 		A non specified error occured while copying.
	 *
	 * Delivered When:
	 * 		An error occurs, and is not classified by other error types.
	 *
	 * DB Tables Updated:
	 *	    None
	 *
	 * Event Data:
	 *      cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 *      MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_NOTSPECIFIED,
	
	/**
	 * Name:
	 *		MME_COPY_ERROR_NORIGHTS
	 *
	 * Description:
	 * 		The source file is a DRM protected file, and the system is not
	 * 		licensed to copy it.  If the DeleteOnNonRecoverableError MME configuration
	 * 		 option is enabled then this error should be delivered with a 
	 * 		 MME_EVENT_COPY_FATAL_ERROR event and corresponding copyqueue entry 
	 * 		 will be deleted.
	 *
	 * Delivered When:
	 * 		Copy is going to begin, but the source file is DRM protected.
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Event Data:
	 * 		cqid: The copy queue ID that failed. (mme_copy_error_t.cqid)
	 *
	 * Class:
	 * 		MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_NORIGHTS,

	/**
	 * Name:
	 *		MME_COPY_ERROR_CORRUPTION,
	 *
	 * Description:
	 * 		The file cannot be ripped or copied because it is corrupted.  If the
	 * 		DeleteOnNonRecoverableError MME configuration option is enabled then
	 * 		this error should be delivered with a MME_EVENT_COPY_ERROR event and
	 * 		the corresponding copyqueue entry will be deleted.
	 *
	 * Delivered When:
	 * 		Corruption detected.
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Event Data:
	 * 		cqid: The copy queue ID that failed. (mme_event_data_t.copy_error.cqid)
	 *
	 * Class:
	 * 		MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_CORRUPTION,
	
	/**
	 * Name:
	 *		MME_COPY_ERROR_DEST_FOLDER,
	 *
	 * Description:
	 * 		The file cannot be ripped because there is a problem with the destination
	 * 		folder (possibly the name does not start and end with '/' characters).
	 * 		If the DeleteOnNonRecoverableError MME configuration option is enabled then
	 * 		this error should be delivered with a MME_EVENT_COPY_ERROR event and
	 * 		the corresponding copyqueue entry will be deleted.
	 *
	 * Delivered When:
	 * 		Corruption detected.
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Event Data:
	 * 		cqid: The copy queue ID that failed. (mme_event_data_t.copy_error.cqid)
	 *
	 * Class:
	 * 		MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_DEST_FOLDER,
	
	/**
	 * Name:
	 *		MME_COPY_ERROR_UNSUPPORTED_MEDIA_TYPE,
	 *
	 * Description:
	 *		The format for the output encoding is unsupported.  Check your platform its supported
	 * 		encoders and make sure you're choosing one that is supported.
	 *
	 * Delivered When:
	 * 		Ripping starts and is failed because the output media type is unsupported.
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Event Data:
	 * 		cqid: The copy queue ID that failed. (mme_event_data_t.copy_error.cqid)
	 *
	 * Class:
	 * 		MME_EVENT_CLASS_COPY
	 */
	MME_COPY_ERROR_UNSUPPORTED_MEDIA_TYPE
} mme_copy_error_type_t;

typedef struct mme_play_command_error {
    uint32_t				command;
    uint32_t				button;
    uint64_t                fid;
} mme_play_command_error_t;

typedef struct mme_play_error_track {
    uint64_t                fid;
    uint64_t                offset;
} mme_play_error_track_t;

typedef struct mme_play_error {
   uint32_t						type;
   uint32_t						reserved;
   union {
      uint64_t                  value;
      uint64_t                  fid;
      uint64_t                  trksessionid;
      uint64_t                  msid;
      uint64_t                  outputid;
      mme_play_command_error_t  command_error;
	  mme_play_error_track_t	track;
  };
} mme_play_error_t;

typedef struct mme_sync_error {
   uint32_t				 type;
   uint32_t              operation_id;
   uint32_t              param;
   uint32_t              reserved;
   uint64_t              msid;
} mme_sync_error_t;

typedef struct mme_copy_error {
   uint32_t              type;
   uint32_t              reserved;
   uint64_t              cqid;
   union {
       uint64_t          value;
       uint64_t          msid;
   };
} mme_copy_error_t;

/**
 * Data for many MME_EVENT_MS_SYNC_* events.
 */
typedef struct mme_sync_data {
    uint64_t    msid;
    uint32_t    operation_id;
	uint32_t    error;		/* one of MME_SYNC_ERROR_* on a SYNCABORTED event */
} mme_sync_data_t;

/**
 * The possible mediastore states.
 */
typedef enum {
	e_mme_ms_nonexistent = 0,
	e_mme_ms_unavailable,
	e_mme_ms_available,
	e_mme_ms_active
} mme_ms_state_t;

/**
 * Data for media store state change event.
 */
typedef struct s_mme_ms_statechange {
	uint64_t		msid;
	uint32_t		old_state;
	uint32_t		new_state;
	uint16_t		device_type;	/* user defined value */
	uint16_t		storage_type;	/* one of MME_STORAGETYPE_* values */
	uint32_t		reserved;
} mme_ms_statechange_t;

/**
 * Data for MME_EVENT_MS_SYNCFIRSTFID and MME_EVENT_MS_SYNC_FIRST_EXISTING_FID 
 * event. 
 */
typedef struct s_mme_first_fid_data {
    uint64_t    fid;
    uint64_t    msid;
    uint64_t	timestamp;
    uint32_t	operation_id;
	uint32_t	reserved;
} mme_first_fid_data_t;

/**
 * Data for the MME_EVENT_METADATA_LICENSING event
 */
typedef struct mme_event_metadata_licensing {
	uint64_t    msid;
	uint64_t    fid;
	char        license[32];
} mme_event_metadata_licensing_t;

/**
 * Data for MME_EVENT_MS_UPDATE event.
 */
typedef struct s_mme_ms_update_data {
	uint64_t	msid;
	uint64_t	added_filecount;
	uint64_t	added_foldercount;
	uint32_t	operation_id;
	uint32_t	flags;
	uint64_t	timestamp;	/**< 'last_sync' value for items associated with this event */
	uint64_t	playlist_count;
	uint64_t	pass_added_filecount; /**< Total number of files added/updated in this pass (inclusive) */
	uint64_t	pass_added_foldercount; /**< Total number of folders added/updated in this pass (inclusive) */
	uint64_t	pass_playlist_count; /**< Total number of playlists added/updated in this pass (inclusive) */
} mme_ms_update_data_t;

/**
 * Data for MME_EVENT_TRACKCHANGE event.
 */
typedef struct mme_trackchange {
	uint64_t 	fid; 			/* The actual fid the mme is playing */
	uint64_t 	fid_requested; 	/* The requested fid - may be different from fid during ripping */
	uint64_t	offset;			/* The current offset into the tracksession */
} mme_trackchange_t;

/**
 * Data for
 * MME_EVENT_MS_SYNC_FOLDER_STARTED,
 * MME_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE, 
 * MME_EVENT_MS_SYNC_FOLDER_COMPLETE and
 * MME_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE
 * events.
 */
typedef struct s_mme_folder_sync_data {
	uint64_t	msid;		/**< ID of the media store the folder is on. */
	uint64_t	folderid;	/**< ID of the folder the sync process is on. */
	uint32_t	pass;		/**< The synchronization pass that this event is for.
								 Uses MME_SYNC_OPTION_PASS_* flags. */
	uint32_t	num_files;	/**< See documentation for specific events. */
	uint32_t	num_folders; /**< See documentation for specific events. */
	uint32_t	num_playlists; /**< See documentation for specific events. */
	uint64_t	timestamp;	/**< 'last_sync' value for items associated with this event */
	uint32_t	operation_id;
	uint32_t	reserved;
} mme_folder_sync_data_t;

/**
 * Data for MME_EVENT_METADATA_INFO event.
 */
typedef struct s_mme_metadata_info_event {
	uint64_t            mdinfo_rid;  /* Metadata information request identifier. */
	int32_t             error;       /* Errno of request. EOK on success. */
	uint32_t            reserved;
	mme_metadata_info_t metadata;
} mme_event_metadata_info_t;

/**
 * Data for MME_EVENT_METADATA_IMAGE event.
 */
typedef struct s_mme_metadata_image_event {
	uint64_t                 mdinfo_irid;   /* Metadata image request identifier. */
	int32_t                  error;         /* Errno of request. EOK on success.*/
	uint32_t                 reserved;
	mme_metadata_image_url_t url;
} mme_event_metadata_image_t;

/**
 * Data for MME_EVENT_DEFAULT_LANGUAGE event.
 */
typedef struct s_mme_default_language_event {
	int        error;       /* Result for last request, 0 on success. */
	const char language[1]; /* NULL terminated string representing the current 
	                           default language. */
} mme_event_default_language_t;

/**
 * Data for MME_EVENT_BUFFER_TOO_SMALL
 */
typedef struct s_mme_event_queue_size {
	size_t					first_event;
	size_t					all_events;
} mme_event_queue_size_t;

/**
 * Data for MME_EVENT_ZONEOUTPUT_CHANGE event.
 */
typedef struct mme_zoneoutput_change_event {
	uint64_t 	zoneid; 		/* The zoneid on which the change occured */
	uint64_t 	outputid; 		/* The outputid that was attached/detached */
#define MME_ZONEOUTPUT_ATTACH	0x00
#define MME_ZONEOUTPUT_DETACH	0x01
	uint32_t	operation;		/* The operation (detach or attach) */
	uint32_t	error;			/* EOK on success, errno if an error occured issuing request */
} mme_zoneoutput_change_t;

typedef enum {
	MME_PRUNE_TYPE_UNKNOWN,		/* Unknown pruning event */
	MME_PRUNE_TYPE_STARTED,		/* Pruning started */
	MME_PRUNE_TYPE_COMPLETED,	/* Pruning completed */
} mme_event_prune_type_t;

typedef struct s_mme_event_prune {
	uint32_t        type;		/* Pruning event type, mme_event_prune_type_t */
	uint64_t        msid;		/* MSID pertaining to event */
	uint32_t        reserved;	/* Reserved for future use */
} mme_event_prune_t;

typedef struct _mme_event {
	mme_event_type_t      type;      /* Event Type */
	size_t                size;      /* Event data size */
	char                  data[0];   /* Event data */
} mme_event_t;

__END_DECLS

#endif /* #ifndef _MME_EVENT_H_INCLUDED */

/* __SRCVERSION("event.h $Rev: 637877 $"); */
