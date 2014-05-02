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


#ifndef _MMSYNC_EVENT_H_INCLUDED
#define _MMSYNC_EVENT_H_INCLUDED

#ifndef _MMSYNC_TYPES_H_INCLUDED
#include <mmsync/types.h>
#endif

#ifndef _IOMEDIA_TYPES_H_INCLUDED
#include <mm/types.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

__BEGIN_DECLS

/**************************************************************************************
 *
 *                                   MMSYNC Events
 *
 * This file describes the events that can be delivered by the MMSYNC to clients who are
 * connected to it.
 *
 **************************************************************************************/

 /** 
  * mm-sync event types, which can be general or synchronization events 
  */
typedef enum mmsync_event_type {
	/**
	 * Name:  
	 *     	MMSYNC_EVENT_NONE
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
	 *		None (event is not related to database updates)
	 *
	 * Class:
	 *      Not defined
	 */
	MMSYNC_EVENT_NONE 				= 0,

	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_1PASSCOMPLETE
	 *
	 * Description:
	 * 		The files pass of synchronization is complete.
	 *
	 *      The files pass updates the files, folders, and playlists tables
	 *      with all files/tracks and playlists found on the device. Items that
	 *      used to exist but are no longer on the device are removed.
	 *
	 *		The mediastore_metadata table is also updated with
	 *      the synchronizer used, the mediastore mountpoint, and 
	 *      the completion time of the files pass (in the last_sync and syncflags fields).
	 *
	 * 		No metadata has been gathered at this point.
	 *
	 * Delivered When:
	 * 		The files pass completes.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		files
	 * 		folders
	 * 		playlists
	 * 		mediastore_metadata
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_1PASSCOMPLETE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNCCOMPLETE
	 *
	 * Description:
	 * 		Synchronization of the mediastore is complete.
	 * 		All tables are as accurate as possible.
	 *
	 * Delivered When:
	 * 		All synchronization passes are complete for the mediastore that was requested.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		files
	 * 		folders
	 * 		playlists
	 * 		playlist_entries
	 *		audio_metadata (if necessary)
	 *		video_metadata (if necessary)
	 *		photo_metadata (if necessary)
	 *      genres (if necessary)
	 *      artists (if necessary)
	 *      albums (if necessary)
	 * 		mediastores
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNCCOMPLETE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_UPDATE
	 *
	 * Description:
	 * 		Database content related to a mediastore has been updated.
	 *
	 * Delivered When:
	 * 		The MMSYNC has written new data to the database. This event informs
	 * 		The user about which mediastore the changes are associated with and
	 * 		information related to the source of the changes.
	 * 
	 *   NOTE: An event will be delivered during sync operations per mediastore
	 *      per operation ID per flags value.
	 *
	 * Event Data:
	 * 		Type: mmsync_ms_update_data_t
	 *
	 * 		The number of added files and folders
	 * 		The synchronization pass under which the changes were made (if any)
	 * 		The operation ID of the synchronization process
	 * 		The timestamp field is the value of the MMSYNC's internal timestamp
	 * 		that is assigned to the 'last_sync' field of all files entries adjusted
	 *		during this update.
	 *
	 * DB Tables Updated:
	 * 		Depends on which sync pass (if any) made the database change.
	 *
	 * 		Not in a sync operation: (mmsync_ms_update_event_t.flags == 0)
	 * 			files
	 * 
	 * 		Files pass: (mmsync_ms_update_event_t.flags == MMSYNC_SYNC_OPTION_PASS_FILES)
	 * 			files
	 * 			folders
	 * 			playlists
	 * 			mediastore_metadata
	 * 			
	 * 		Metadata pass: (mmsync_ms_update_event_t.flags == MMSYNC_SYNC_OPTION_PASS_METADATA)
	 * 			files
	 * 			folders
	 *          audio_metadata, video_metadata, photo_metadata, genres, artists, albums 
	 *				(some or all of these tables depending on the categories of the media files)
	 * 			mediastore_metadata
	 *
	 * 		Playlist pass: (mmsync_ms_update_event_t.flags == MMSYNC_SYNC_OPTION_PASS_PLAYLISTS)
	 * 			files
	 * 			folders
	 * 			playlists
	 * 			playlist_entries
	 * 			mediastore_metadata
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_UPDATE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_SHUTDOWN
	 *
	 * Description:
	 * 		mm-sync can be requested to shutdown by any client.  This event allows
	 * 		other clients to know that the MMSYNC was requested to shutdown.
	 *
	 * Delivered When:
	 * 		Before the shutdown process begins, immediately after receiving the request to
	 * 		shutdown.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 *		None (event is not related to database updates)
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_GENERAL
	 */
	MMSYNC_EVENT_SHUTDOWN,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_SHUTDOWN_COMPLETED
	 *
	 * Description:
	 *      The MMSYNC was requested to shutdown.  Once this event is delivered it indicates
	 *      that the MMSYNC has finished its shutdown process and is no longer active.
	 *      The MMSYNC must be terminated and restarted to perform actions again.
	 *
	 * Delivered When:
	 *      The shutdown process is complete.  Playback and sync have stopped.
	 *
	 * Event Data:
	 * 		0 (no data)
	 *
	 * DB Tables Updated:
	 *		None (event is not related to database updates)
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_GENERAL
	 */
	MMSYNC_EVENT_SHUTDOWN_COMPLETED,

	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNCFIRSTFID
	 *
	 * Description:
	 * 		During a files pass sync, the first new file that is playable by the
	 * 		MMSYNC was found. This is delivered so clients can start playback as
	 * 		soon as possible if desired. However, if there are files to be
	 * 		removed from the database, this event is not emitted until after all
	 * 		those files are removed. This means that once this event is emitted,
	 * 		the receiver can be sure that all database items are valid.
	 *
	 * Delivered When:
	 * 		The first new playable file is found and placed in the library once
	 * 		deletion from the database of removed mediastore items is complete.
	 *
	 * Event Data:
	 * 		The fid of the first file. (mmsync_first_fid_data_t.fid)
	 *		operation_id: The sync operation's operation ID.
	 * 		The timestamp field is the value of the MMSYNC's internal timestamp
	 * 		that the 'last_sync' field of the files entry associated with this
	 * 		update is set to.
	 *
	 * DB Tables Updated:
	 * 		files
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNCFIRSTFID,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_SYNC_ERROR
	 *
	 * Description:
	 * 		An error occurred during sync'ing.
	 *
	 * Delivered When:
	 * 	    Various sync errors will cause this event to be generated, 
	 *      the event data will determine the cause.
	 *
	 * Event Data:
	 *		The error data, including the error type, sync operation ID,
	 *      and other information (mmsync_sync_error_t)
	 *
	 * DB Tables Updated:
	 *		Error dependent.
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_SYNC_ERROR,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_SYNCABORTED
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
	 *      The sync data, providing the mediastore that is being synced,
	 *      the operation ID (0 for non-directed) for the sync operation and
	 *      the sync error type. (mmsync_sync_data_t)
         *
	 * DB Tables Updated:
	 *		None (event is not related to database updates)
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_SYNCABORTED,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_SYNC_SKIPPED
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
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_SYNC_SKIPPED,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_STARTED
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
	 *      (mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_STARTED,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_2PASSCOMPLETE
	 *
	 * Description:
	 * 		The metadata pass of synchronization is complete.  
	 *
	 * 		The metadata pass updates the audio_metadata, video_metadata, 
	 *      and photo_metadata tables, based on the type of media files 
	 *      being synced. The supporting tables of genres, artists, and albums 
	 *      are also updated as needed.
	 *
	 *		The files table is updated to show that 
	 *		all metadata describing the media content is now accurate.
	 *
	 *		The mediastore_metadata table is updated to reflect
	 *      the completion time of the metadata pass (in the last_sync and syncflags fields).
	 *
	 * Delivered When:
	 * 		The metadata pass completes.
	 *
	 * Event Data:
	 * 		The sync data, providing the mediastore that is being synced
	 * 		and the operation ID (0 for non-directed) for the sync operation.
	 * 		(mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 *      audio_metadata
	 *      video_metadata
	 *      photo_metadata
	 *      genres
	 *      artists
	 *      albums
	 * 		mediastore_metadata
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_2PASSCOMPLETE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_3PASSCOMPLETE
	 *
	 * Description:
	 *      The playlist pass of synchronization is complete. 
	 *
	 * 		The playlist pass updates the playlists and playlist_entries tables.
	 *		Information on device playlists is now accurate in the database.
	 *
	 *		The mediastore_metadata table is updated to reflect
	 *      the completion time of the playlist pass (in the last_sync and syncflags fields).
	 *
	 * Delivered When:
	 *      The playlist pass completes.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		files
	 * 		folders
	 * 		playlists
	 * 		playlist_entries
	 * 		mediastore_metadata
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_3PASSCOMPLETE,
	
	/**
	 * Name:  
	 *
	 * Description:
	 * 		Sent when a mediastore is to be synchronized, but is put on the
	 * 		pending list instead due to a lack of availability of sync threads.
	 *
	 * Delivered When:
	 * 		After the mediastores table is updated and there are no sync threads
	 * 		to sync it further.
	 *
	 * Event Data:
	 *      The sync data, providing the mediastore that is being synced
	 *      and the operation ID (0 for non-directed) for the sync operation.
	 *      (mmsync_sync_data_t)
	 *
	 * DB Tables Updated:
	 * 		mediastores
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_PENDING,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FOLDER_STARTED
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
	 *      mmsync_folder_sync_data_t, the number of files, folders and playlists
	 *      is 0. The timestamp field is set to 0 and not used for this event.
	 *
	 * DB Tables Updated:
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_FOLDER_STARTED,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FOLDER_COMPLETE
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
	 * 		mmsync_folder_sync_data_t;
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
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_FOLDER_COMPLETE,

	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_PRIORITY_FOLDER_STARTED
	 *
	 * Description:
	 * 		Describes a priority folder that has started synchronization.
	 *
	 * Delivered When:
	 * 		Synchronization of a priority folder has started.
	 *
	 * Event Data:
	 *      	mmsync_folder_sync_data_t;
	 *	specifically the operation id, pass number
	 *	and the folder id of the folder being synced.
	 *
	 * DB Tables Updated:
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_PRIORITY_FOLDER_STARTED,
 	
 	/**
 	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FOLDER_COMPLETE
	 *
	 * Description:
	 * 		Describes a priority folder that has completed synchronization.
	 *
	 * Delivered When:
	 * 		Non-recursive synchronization of a priority folder has completed.
	 *
	 * Event Data:
	 *      	mmsync_folder_sync_data_t;
	 *	specifically operation id, pass number,
	 *	the folder id of the folder being synced,
	 *	and number of new files, folders, and playlists.
	 *
	 * DB Tables Updated:
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_PRIORITY_FOLDER_COMPLETE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE
	 *
	 * Description:
	 * 		Event emitted when synchronization of all folders in a folder.
	 *
	 * Delivered When:
	 * 		Recursive synchronization of a folder has completed. It is not
	 * 		emitted on a non-recursive synchronization of a folder.
	 *
	 * Event Data:
	 * 		mmsync_folder_sync_data_t;
	 * 		The number of files and playlists is always 0 (not used).
	 * 		The number of folders is number of folders in this folder that were
	 * 		synchronized (as part of recursive sync of this folder).
	 * 		The timestamp field is set to 0 and not used for this event.
	 *
	 * DB Tables Updated:
	 * 		folders
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FIRST_EXISTING_FID
	 *
	 * Description:
	 *      During a files pass sync, the first existing file that is playable
	 *      by the MMSYNC was found.  This is delivered so clients can start
	 *      playback as soon as possible if desired.
	 *  
	 *      This is different from the MMSYNC_EVENT_MS_SYNCFIRSTFID event as that
	 *      event is emitted only by added files after all deleted are removed
	 *      from the database that need to be.
	 *
	 * Delivered When:
	 *      The first existing playable file is found that is already in the
	 *      library.
	 *
	 * Event Data:
	 *      The fid of the first file. (mmsync_first_fid_data_t.fid)
	 *      operation_id: The sync operation's operation ID.
	 *      The timestamp field is the value of the time of the start of the
	 *      files pass.
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_FIRST_EXISTING_FID,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_BUFFER_TOO_SMALL
	 *
	 * Description:
	 *      Delivered to a client when the event buffer on the client side is
	 *      too small to fetch any events from the MMSYNC. The payload indicates
	 *      the next message size as well as the full queue size to fetch.
	 * 		
	 * Delivered When: 
	 * 		A client requests an event but does not have enough room to hold it.
	 *
	 * Event Data:
	 * 		mmsync_event_queue_size_t
	 *
	 * DB Tables Updated:
	 * 		None
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_GENERAL
	 */
	MMSYNC_EVENT_BUFFER_TOO_SMALL,
	
	/**
	 * Name:  
	 * 		MMSYNC_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE
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
	 *      mmsync_folder_sync_data_t;
	 *      ID of mediastore folder is on.
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
	 * 		files
	 *      folders
	 *      playlists
	 *      playlist_entries
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE,

	/**
	 * Name:
	 *		MMSYNC_EVENT_DB_RESET
	 *
	 * Description:
	 *		Metadata, file and playlist database content has been completely
	 *		cleared.
	 *
	 * Delivered When:
	 *		During an IAP2 iPod sync when the iPod instructs us to delete
	 *		all database contents.
	 *
	 * Event Data:
	 *		Type: mmsync_reset_sync_data_t
	 *
	 *		The operation ID of the synchronization process
	 *		The timestamp field is the value of the MMSYNC's internal timestamp
	 *		that the 'last_sync' field of the files entry associated with this
	 *		update is set to.
	 *
	 * DB Tables Updated:
	 *		files
	 *		playlists
	 *		playlist_data
	 *		mediastore_metadata
	 *		all metadata tables including:
	 *		   -- audio_metadata
	 *		   -- video_metadata
	 *		   -- ipod_metadata
	 *		   -- artists
	 *		   -- albums
	 *		   -- genres
	 *
	 * Class:
	 *      MMSYNC_EVENT_CLASS_SYNC
	 */
	MMSYNC_EVENT_DB_RESET,
} mmsync_event_type_t;


 /** 
  * mm-sync error types
  */
typedef enum mmsync_sync_error_type {
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_NONE
	 *
	 * Description:
	 * 		No sync error
	 *
	 * Delivered When:
	 * 		Never (placeholder)
	 *
	 * Event Data:
	 *      None
	 *
	 * DB Tables Updated:
	 *	    None	
	 */
	MMSYNC_SYNC_ERROR_NONE              = 0,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_MEDIABUSY
	 *
	 * Description:
	 * 		The media was busy and sync was not allowed to start on it
	 * 		because of concurrency rules.
	 *
	 * Delivered When:
	 * 		Sync should have started on a device
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MMSYNC_SYNC_ERROR_MEDIABUSY,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_READ
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
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MMSYNC_SYNC_ERROR_READ,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_NETWORK
	 *
	 * Description:
	 * 		There was a network error while syncing.  This can be caused when a
	 * 		metadata lookup required network access but failed.
	 *
	 * Delivered When:
	 * 		Sync has a network error.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MMSYNC_SYNC_ERROR_NETWORK,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_UNSUPPORTED
	 *
	 * Description:
	 * 		The mediastore to sync is not a supported mediastore by the
	 * 		MMSYNC.
	 *
	 * Delivered When:
	 * 		Sync starts and determines the device to be unsupported.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MMSYNC_SYNC_ERROR_UNSUPPORTED,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_USERCANCEL
	 *
	 * Description:
	 * 		Sync was stopped by a client request.
	 *
	 * Delivered When:
	 * 		A client requests that sync be stopped.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    mediastores
	 */
	MMSYNC_SYNC_ERROR_USERCANCEL,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_NOTSPECIFIED
	 *
	 * Description:
	 * 		A non specified error occured that is not classified by other error types.
	 *
	 * Delivered When:
	 * 		At any time during sync
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_NOTSPECIFIED,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_LIB_LIMIT
	 *
	 * Description:
	 * 	    First pass synchronization for the mediastore reached a
	 *      configuration limit, and no further entries may be added to the
	 *      files table.
	 *
	 * Delivered When:
	 * 		When the maximum number of database entries has been reached
	 *      during files pass sync.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *      param: The limit that the mediastore reached.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_LIB_LIMIT,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_FOLDER_LIMIT
	 *
	 * Description:
	 * 	    First pass synchronization for the mediastore reached a
	 *      configuration limit, and no further entries may be added to the
	 *      files table.
	 *
	 * Delivered When:
	 *      When the maximum number of folder items presented to the MMSYNC has
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_FOLDER_LIMIT,
	
	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_DATABASE
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
	MMSYNC_SYNC_ERROR_DATABASE,

	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_FOLDER_DEPTH_LIMIT
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
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_FOLDER_DEPTH_LIMIT,

	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_DB_LIMIT
	 *
	 * Description:
	 * 	    The maximum database size has been reached, no further data may be
	 * 	    added to the files and playlist tables.
	 *
	 * Delivered When:
	 * 		When the MMSYNC notices that the max DB size has been reached and no
	 * 		further pruning can be done on the DB to reduce its size.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_DB_LIMIT,

	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_FOLDER_NONMEDIA_LIMIT
	 *
	 * Description:
	 *      First pass synchronization for the mediastore reached the
	 *      non-media file limit, and no entries for this folder will be
	 *      added to the files table.
	 *
	 * Delivered When:
	 *      When the maximum number of non-media items in a folder has hit
	 *      the configured limit.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_FOLDER_NONMEDIA_LIMIT,

	/**
	 * Name:  
	 * 		MMSYNC_SYNC_ERROR_FOLDER_MEDIA_LIMIT
	 *
	 * Description:
	 *      First pass synchronization for the media store reached the
	 *      media file limit, and no further entries for this folder will be
	 *      added to the files table.
	 *
	 * Delivered When:
	 *      When the maximum number of media items in a folder has hit
	 *      the configured limit.
	 *
	 * Event Data:
	 *      operation_id: The sync operation's operation ID.
	 *      param: The folder ID that the limit was reached in.
	 *
	 * DB Tables Updated:
	 *	    None
	 */
	MMSYNC_SYNC_ERROR_FOLDER_MEDIA_LIMIT,

	/**
	 * Name:
	 * 		MMSYNC_SYNC_ERROR_MEMORY_ALLOCATION
	 *
	 * Description:
	 *		Synchronization encountered a memory allocation problem.
	 *
	 * Delivered When:
	 * 		Cannot allocate memory during synchronization.
	 *
	 * Event Data:
	 * 		operation_id: The sync operation's operation ID.
	 *
	 * DB Tables Updated:
	 * 		None
	 */
	MMSYNC_SYNC_ERROR_MEMORY_ALLOCATION,
} mmsync_sync_error_type_t;

/**
 * Data for MMSYNC_SYNC_ERROR_* errors. 
 */
typedef struct mmsync_sync_error {
   uint32_t				 type;		   ///< The error type (one of MMSYNC_SYNC_ERROR_* codes).
   uint32_t              operation_id; ///< The synchronization operation ID.
   uint32_t              param;		   ///< Additional information; often, the ID of the folder in which the error occurred. 
   uint32_t              reserved;		///< Reserved for future use.
} mmsync_sync_error_t;

/**
 * Data for many MMSYNC_EVENT_MS_* events.
 */
typedef struct mmsync_sync_data {
    uint32_t    operation_id;   ///< The synchronization operation ID.
    uint32_t    error;			///< One of MMSYNC_SYNC_ERROR_* on a SYNCABORTED event.
} mmsync_sync_data_t;

/**
 * Data for MMSYNC_EVENT_MS_SYNCFIRSTFID and MMSYNC_EVENT_MS_SYNC_FIRST_EXISTING_FID 
 * events. 
 */
typedef struct s_mmsync_first_fid_data {
    uint64_t    fid;			///< The file ID of the first media file synchronized.
    uint64_t	timestamp;		///< The time the first media file was synchronized.
    uint32_t	operation_id;	///< The synchronization operation ID.
	uint32_t    count;			///< The number of time the event was sent.
} mmsync_first_fid_data_t;

/**
 * Data for MMSYNC_EVENT_MS_UPDATE event.
 */
typedef struct s_mmsync_ms_update_data {
	uint64_t	added_filecount;	///< The number of files that had information added to the database.
	uint64_t	added_foldercount;	///< The number of folders that had information added to the database.
	uint32_t	operation_id;		///< The synchronization operation ID.
	uint32_t	flags;				///< The synchronization pass (one of the MMSYNC_SYNC_OPTION_PASS_* flags).
	uint64_t	timestamp;			///< The timestamp value assigned to the 'last_sync' fields of all updated database entries. 
	uint64_t	playlist_count;		///< The number of playlists added/updated in this pass (applicable for the files and playlists pass, otherwise 0).
	uint64_t	pass_added_filecount; ///< The total number of files added/updated in this pass (accumulative).
	uint64_t	pass_added_foldercount; ///< The total number of folders added/updated in this pass (accumulative).
	uint64_t	pass_playlist_count; ///< The total number of playlists added/updated in this pass (accumulative).
	uint64_t    playlist_item_count; ///< The number of playlist items added/updated in this pass (applicable for the playlists pass, otherwise 0).
} mmsync_ms_update_data_t;

/**
 * Data for MMSYNC_EVENT_MS_SYNC_FOLDER_* events.
 */
typedef struct s_mmsync_folder_sync_data {
	uint64_t	folderid;		///< ID of the folder whose synchronization progress is described by this event.
	uint32_t	pass;			///< The synchronization pass (one of the MMSYNC_SYNC_OPTION_PASS_* flags).
	uint32_t	num_files;		///< See documentation for specific events.
	uint32_t	num_folders; 	///< See documentation for specific events.
	uint32_t	num_playlists; 	///< See documentation for specific events.
	uint64_t	timestamp;		///< The timestamp value assigned to the 'last_sync' fields of all updated database entries.
	uint32_t	operation_id;	///< The synchronization operation ID.
	uint32_t    reserved;		///< Reserved for future use.
} mmsync_folder_sync_data_t;

/**
 * Data for MMSYNC_EVENT_BUFFER_TOO_SMALL.
 */
typedef struct s_mmsync_event_queue_size {
	size_t					first_event;	///< The size (in bytes) of the first queued event.
	size_t					all_events;		///< The size (in bytes) of all queued events. 
} mmsync_event_queue_size_t;

/**
 * Data for MMSYNC_EVENT_MS_SYNC_DB_RESET.
 */
typedef struct s_mmsync_reset_sync_data {
	uint64_t	timestamp;	///< The timestamp value assigned to the 'last_sync' fields of all updated database entries.
	uint32_t	operation_id;	///< The synchronization operation ID.
	uint32_t	reserved;	///< Reserved for future use.
} mmsync_reset_sync_data_t;

/** 
 * General information provided for all events
 */
typedef struct _mmsync_event {
	mmsync_event_type_t   type;      ///< The event type.
	size_t                size;      ///< The event data size.
	char                  data[0];   ///< The event data.
} mmsync_event_t;

__END_DECLS

#endif /* #ifndef _MMSYNC_EVENT_H_INCLUDED */

/* __SRCVERSION("event.h $Rev: 713235 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/lib/public/mmsync/event.h $ $Rev: 713235 $")
#endif
