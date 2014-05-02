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


#ifndef _MME_MME_H_INCLUDED
#define _MME_MME_H_INCLUDED

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef __SIGINFO_H_INCLUDED
#include <sys/siginfo.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _MME_TYPES_H_INCLUDED
#include <mme/types.h>
#endif

#ifndef _MME_METADATA_H_INCLUDED
#include <mme/metadata.h>
#endif

#ifndef _MME_EVENT_H_INCLUDED
#include <mme/event.h>
#endif

#ifndef _MME_INTERFACE_H_INCLUDED
#include <mme/interface.h>
#endif

__BEGIN_DECLS

/**
 * Connects to the multi-media engine on a particular zone.
 *
 * To communicate to multiple zones connect once for each zone.  This function
 * initializes the mme_hdl_t object which is used for the rest of the mme interface
 * functions.
 *
 * Flags that can be used to change the behaviour of the MME connection:
 *  * O_SYNC        The MME will completely execute requests before returning to the client
 *
 *  *        		  (default) The MME will return to the client as soon as
 *                  possible and complete the majority of the work after unblocking the client.
 *                  As much of the request as possible will be verified to be valid before
 *                  unblocking with a success code.
 *
 *  *               (default) The MME will block clients in a queue until it can service their requests.
 *
 *  * O_NONBLOCK    The MME will return an error with errno set to EAGAIN if a client request would result
 *                  in it being blocked.
 *
 * @param filename is the full pathname to the mme device name (eg. /dev/mme/zone1)
 * @param flags Flags to use for the connection to the MME
 * @return NULL on error.
 */
mme_hdl_t *mme_connect(const char *filename, uint32_t flags);

/**
 * Changes MME connection flags
 *
 * @param hdl The MME connection handle
 * @param flags New flags to use. See mme_connect() flags parameter
 *
 * @return -1 on error
 */
int mme_set_connect_flags(mme_hdl_t *hdl, uint32_t flags);


/**
 * Disconnect from an MME zone.  This should only be called when the client is completely
 * finished with the zone.
 *
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_disconnect(mme_hdl_t *hdl);


/**
 * Set the API timeout for future calls
 * 
 * Clients can choose per connection what timeout they'd like for all future calls.  This can be changed
 * at any time, but will only affect future calls made with the same handle.  If the MME were to keep a
 * client blocked for longer than the timeout value then the client will be unblocked and receive
 * an error return and an EINTR errno value.  It is not possible to tell if the client received EINTR
 * because of this timeout, or because the MME received EINTR from one of its own requests.
 * 
 * If this is not called, the default is to have no timeout.
 * 
 * @param hdl The MME connection handle
 * @param milliseconds The maximum number of milliseconds to block for.  Set to 0 to block forever.
 * @return -1 on error with errno set.
 */
int mme_set_api_timeout(mme_hdl_t *hdl, uint32_t milliseconds);

/**
 * Get the amount of time left on the API timer
 * 
 * If a client connection has timeouts set for the API using mme_set_api_timeout( ), calls can be
 * returned early with an error unblocking the client with an errno EINTR.  Because errno's propagate up
 * it is possible that EINTR would be returned for other reasons.  To distinguish between an API timeout
 * and other reasons for receiving EINTR clients can use this function.
 * 
 * This function returns the number of milliseconds left on the timer.  If the timer did expire it will
 * return a value of 0.  If the timer did not expire, it will return a value greater than 0.
 * 
 * @param hdl The MME connection handle
 * @param milliseconds The number of milliseconds remaining on the timer
 * 
 * @return -1 on error with errno set.  EINVAL indicates that the timeout is set to 0 so the request
 *         for time remaining is invalid.
 */
int mme_get_api_timeout_remaining(mme_hdl_t *hdl, uint32_t *milliseconds);

/**
 * Register and unregister for events from the MME.
 *
 * By default the MME delivers no events, clients must register for events that they are interested in.
 * Each event class can deliver a different sigevent.
 *
 * @param event_class The event class to register for
 * @param event The event to have delivered when the event is received.  To unregister for the specified class
 *              set event to NULL.
 *
 * @return -1 on error with errno set
 */
int mme_register_for_events(mme_hdl_t *hdl, mme_event_class_t event_class, struct sigevent *event);

/**
 * Shutdown the MME
 *
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_shutdown(mme_hdl_t *hdl);

/**
 * Set the time update interval for the control context
 *
 * The interval is the period between updates of playback time.  The MME scales
 * the value depending on the speed to provide regular intervals.  
 *
 * Examples:
 *   period = 100, speed = 1000:  updates will be delivered every 100ms of playback time
 *   period = 100, speed = 0 (paused):   no updates will be delivered
 *   period = 100, speed = 2000:  updates will be delivered every 200ms of playback time
 *   period = 100, speed = 500 (slow play):  updates will be delivered every 50ms of playback time
 *
 * @param hdl The MME event handle
 * @param period The time interval between MME_EVENT_TIME updates in milliseconds
 *
 * @return -1 on error with errno set
 */
int mme_set_notification_interval(mme_hdl_t *hdl, uint32_t time);

/**
 * Set the preferred language.
 * 
 * This call does not affect the preferred language that is used on media
 * that has multiple language support. Use mme_media_set_lang() for that.
 *
 * The current implementation uses only the first two characters
 * to extract the language. The requested language must exist in
 * the database, even though it doesn't (yet) select that language.
 *  
 * In the future, it may:
 * -set the language used in strings where language sets
 * are available. This may cause a re-ordering of database tables
 * that are lexicographically collated.
 * -other to be determined
 * 
 * @param	hdl		The MME connection handle
 * @param	locale	String containing 5-character language and region code
 * 					This consists of a 2-character ISO639-1 language code,
 * 					followed by a '_' character,
 * 					followed by a 2-character ISO3166-1 alpha-2 region code.
 * @see		<http://www.loc.gov/standards/iso639-2/php/code_list.php>
 * @return	-1	on failure; errno is set.
 */
int mme_setlocale ( mme_hdl_t *hdl, const char *locale );

/**
 * Get the current locale setting.
 * 
 * @param	hdl		The MME connection handle
 * @param	locale	Pointer to place to put locale string.
 * 					Must be at least 6 characters long.
 * @return	-1	on failure; errno is set.
 */
int mme_getlocale ( mme_hdl_t *hdl, char *locale );

/**
 * Set the preferred media playback language. If this is not called
 * after MME startup, no preference is placed on the media.
 *
 * @see		<http://www.loc.gov/standards/iso639-2/php/code_list.php>
 * 
 * @param	hdl		The MME connection handle.
 * @param	lang	String containing 2-character ISO639-1 language code.
 * @return	-1	on failure; errno is set.
 */
int mme_media_set_def_lang ( mme_hdl_t *hdl, const char *lang );

/**
 * Get the preferred media playback language. If this is not called
 * after MME startup, the returned string is 0-length..
 *
 * @see		<http://www.loc.gov/standards/iso639-2/php/code_list.php>
 * 
 * @param	hdl		The MME connection handle.
 * @param	lang	String to place 2-character ISO639-1 language code (0 terminated).
 * @return	-1	on failure; errno is set.
 */
int mme_media_get_def_lang ( mme_hdl_t *hdl, char *lang );

/**
 * Indicate the default character encoding
 *
 * @param hdl The MME connection handle
 * @param default_encoding A string that is passed to the charconvert DLL loaded 
 *        into the MME.  Currently the contents of this string are not defined.
 *        The contents should be understood by the configured charconvert DLL.
 * @param allow_detection To allow the MME and charconvert DLL to perform encoding
 *        detection set this to 1.  To disable detection set to 0.
 *
 * @return -1 on error
 */
int mme_charconvert_setup(mme_hdl_t *hdl, const char *default_encoding, uint32_t allow_detection);

/**
 * Request that a mediastore be resynced.
 *
 * @param hdl The MME connection handle
 * @param msid The mediastore ID to resync
 * @param folderid	The folderid to resync; 0 means do all.
 * @param options A mask to indicate which synchronization options are to be used.
 *              See MME_SYNC_OPTION_* values in interface.h.
 * These include MME_SYNC_OPTION_BLOCKING; if used then block till complete.
 *              If not used, the function will return immediately and the sync
 *              will happen in the background.
 */
int mme_resync_mediastore(mme_hdl_t *hdl, uint64_t msid, uint64_t folderid, uint32_t options);

/**
 * Request that unavailable media stores be deleted from the database. 
 *  
 * @param hdl The MME connection handle 
 * @param flags	Flags; see MME_DB_DELETION_* in interace.h
 * @return 0 on success. 
 * @return -1 on error; errno is set. 
 */
int mme_delete_mediastores(mme_hdl_t *hdl, uint32_t flags);

/** 
 * Request that a media store be restarted. 
 *  
 * This causes the specified media store to go through an active->nonexistent 
 * transition, followed by an insertion to the active state. On success, the 
 * media store ID is changed. 
 *  
 * Not supported for media stores that are not active or for media stores that 
 * use an mmdev handler plug-in (errno ENOTSUP). 
 *  
 * After validating the request, this operation runs asynchronously, so it may 
 * still may fail after returning success. The caller must examine the media 
 * store state change events to determine if the entire operation finished 
 * successfully. The user may use the identifier of the newly active media store 
 * to match it to the restarted media store. 
 * 
 * @param hdl The MME connection handle 
 * @param msid		ID of media store to be restarted.
 * @return 0 on success 
 * @return -1 on failure 
 *  errno ENOTSUP	media store uses an mmdev handler
 *  errno EINVAL    media store does not exist or is not active
 */
int mme_ms_restart(mme_hdl_t *hdl, uint64_t msid);

/*
 * Starts a directed synchronization operation. Honours all MME_SYNC_OPTION_*
 * flags except BLOCKING.
 * 
 * This function returns a positive integer that is the operation ID. This
 * value is sent with a MME_EVENT_SYNCABORTED when the operation completes
 * unsuccessfully, or with a MME_EVENT_MS_SYNCCOMPLETE if it completes
 * successfully as this function returns synchronously.
 *
 * @param  hdl MME connection handle.
 * @param  msid    Media store identifier on which sync is to take place.
 * @param  path    The path on the media store to be synchronized.
 * @param  options The synchronization options.
 *
 * @return -1  on failure; errno is set
 * @return 0   (to be determined)
 * @return >0  on success; value is synchronization operation ID.
 */
int mme_sync_directed( mme_hdl_t *hdl, uint64_t msid, const char *path, uint32_t options );

/*
 * Starts a directed synchronization operation using a specific MDP and 
 * specific MDP match. Honours all MME_SYNC_OPTION_* flags except BLOCKING.
 * 
 * This function returns a positive integer that is the operation ID. This
 * value is sent with a MME_EVENT_SYNCABORTED when the operation completes
 * unsuccessfully, or with a MME_EVENT_MS_SYNCCOMPLETE if it completes
 * successfully as this function returns synchronously.
 *
 * @param  hdl MME connection handle.
 * @param  msid        Media store identifier on which sync is to take place.
 * @param  path        The path on the media store to be synchronized.
 * @param  mdp_name    The name of the mdp to use.
 * @param  mdp_matchid The matchid returned in the XML structure to use.
 * @param  options The synchronization options.
 *
 * @return -1  on failure; errno is set
 * @return 0   (to be determined)
 * @return >0  on success; value is synchronization operation ID.
 */
int mme_sync_metadata_directed( mme_hdl_t *hdl, uint64_t msid, const char *path, const char *mdp_name, const char *mdp_matchid, uint32_t options );

/**
 * Starts a synchronization operation directed at a file.
 *
 * This function may be used to cause the database to be updated when the
 * application knows there is a specific file change that has taken place,
 * such as a file deletion, file addition, and file move (or renaming).
 *
 * Note that file move or rename is supported only when the file remains
 * on the same media store it started on. In this case, all metadata about
 * the file is preserved. Otherwise, two separate calls are required and
 * metadata is not preserved and the file ID of the renamed file may change.
 * 
 * Use of this function is limited to certain media store types; for example
 * it is not supported on iPods. Other limitations are to be determined.
 *
 * No sync options are associated with this operation; it attempts to do
 * the equivalent of both file and metadata passes.
 *
 * This function returns a positive integer that is the operation ID. This
 * value is sent with a MME_EVENT_SYNCABORTED when the operation completes
 * unsuccessfully, or with a MME_EVENT_MS_SYNCCOMPLETE if it completes
 * successfully as this function returns synchronously.
 * (It is to be determined if there are cases it may also complete the
 * operation synchronously.)
 *
 * For file additions, old_fid should be 0, and new_filename should be the
 * path and name of the new file.
 * For file removals, old_fid should be the fid of the deleted file.
 * For file changes, both old_fid and new_filename should be specified as
 * described above.
 * In no case should neither of them be specified.
 *
 * Initially, there is no support for changes across media stores. For
 * example, the msid of the old_fid (when specified) must match the old_msid
 * (when specified).
 *
 * @param  hdl     MME connection handle.
 * @param  old_fid The file ID of the file in the library before the change.
 *                 May be 0 to indicate that there is no existing file
 *                 associated with the operation.
 * @param  new_msid The media store ID that the new_filename path is used
 *                 on for the new file. May be 0 if new_filename is NULL.
 * @param  new_filename The path and name of the new file, relative to the
 *                 mountpath of media store identified by new_msid.
 *                 May be a NULL pointer to indicate there is no new file
 *                 associated with the operation.
 * @return -1  on failure; errno is set
 * @return 0   on success; operation completed synchronously (TBD).
 * @return >0  on success; value is synchronization operation ID.
 */
int mme_sync_file(
        mme_hdl_t *hdl,
        uint64_t old_fid,
        uint64_t new_msid,
        const char *new_filename
        );

/**
 * This function is used to synchronize a specific playlist.
 *
 * This is implemented as a specific subset of a playlists pass
 * synchronization operation, and as such has the normal set of synchronization
 * events and logs associated with.
 *
 * It returns a positive integer that is the operation ID. This value is
 * sent with a MME_EVENT_SYNCABORTED when the operation completes
 * unsuccessfully, or with a MME_EVENT_MS_SYNCCOMPLETE if it completes
 * successfully as this function returns before performing the synchronization 
 * (only performed some validation of the request). (It is to be determined if 
 * there are cases it may also complete the operation synchronously.) 
 *
 * @param  hdl     MME connection handle.
 * @param  plid    ID of the playlist to be synchronized. 
 * @param  flags   Flags (to be determined). 
 * @return -1  on failure; errno is set
 * @return 0   on success; operation completed synchronously (TBD).
 * @return >0  on success; value is synchronization operation ID.
 */
int mme_playlist_sync(mme_hdl_t *hdl, uint64_t plid, uint32_t flags);

/**
 * Cancels a specific directed synchronization operation, whether current
 * or pending.
 *
 * @param hdl MME connection handle.
 * @param operation_id    Operation ID that was returned from mme_sync_directed().
 * @return    -1 on failure
 */
int mme_directed_sync_cancel( mme_hdl_t *hdl, int operation_id );

/**
 * Cancels synchronization of a media store, whether current or pending.
 *
 * @param	hdl	MME connection handle.
 * @param	msid	Media store ID on which synchronization is to be stopped
 *      	   		or cancelled.
 * @return	-1 on failure
 */
int mme_sync_cancel ( mme_hdl_t *hdl, uint64_t msid );

/**
 * Get the number of clients that are connected to this zone
 * 
 * @param hdl The MME connection handle
 * @return -1 on error or the number of clients connected to the zone
 */
int mme_getclientcount(mme_hdl_t *hdl);

/**
 * Get the control context ID for the current connected controlcontext
 *
 * @param hdl The MME connection handle
 * @param ccid The Control Context ID (output)
 * @return -1 on error
 */
int mme_getccid(mme_hdl_t *hdl, uint64_t *ccid);

/**
 * New Track Session
 * Create a new track session for the connected zone.  Track sessions are used
 * by the MME's playback engine to play a sequence of files.  When playing from 
 * the library mode the MME will select fids.
 *
 * @param hdl The MME connection handle
 * @param statement The SQL statement to create the trksession with.  This could 
 *   select from the library table or from the playlist table as examples.
 * @param mode The mode to use for playback.  Valid options are:
 *   - MME_PLAYMODE_LIBRARY
 *   - MME_PLAYMODE_FILE
 * @param trksessionid The track session id created by this command.  Use settrksession
 *                     to make it active.
 * @return -1 on error with errno set
 */
int mme_newtrksession(mme_hdl_t *hdl, const char *statement, short int mode, uint64_t *trksessionid);

/**
 * Set the current tracksession for the connected zone.
 *
 * @param hdl The MME connection handle
 * @param trksession The tracksession id for the zone
 *
 * @return -1 on error with errno set
 */
int mme_settrksession(mme_hdl_t *hdl, uint64_t trksessionid);

/**
 * Delete the track session from the database
 *
 * @param hdl The MME connection handle
 * @param trksession The tracksession id for the zone
 *
 * @return -1 on error with errno set
 */
int mme_rmtrksession(mme_hdl_t *hdl, uint64_t trksessionid);

/**
 * Reshuffle the random tracksession playback order
 *
 *
 * This will cause the tracksession to re-shuffle the random playorder.  If the 
 * MME_TRK_SHUFFLE_PLAYINGFID_FIRST flag is set, the currently playing track will 
 * be set to be first in playback during random order.  
 * 
 * @param hdl The MME connection handle
 * @param trksessionid The tracksession id for the zone
 * @param flags:
 *    MME_TRK_SHUFFLE_PLAYINGFID_FIRST
 * @return -1 on error
 */
int mme_trksession_reshuffle(mme_hdl_t *hdl, uint32_t flags);

/**
 * Update the track session view table
 *
 * This will cause the tracksessionview table to be updated for the track session that the
 * control context has currently set.  Clients connected to the control context can expect to see 
 * the following sequence of events:
 *   1.  MME_EVENT_TRKSESSIONVIEW_INVALID
 *   2.  MME_EVENT_TRKSESSIONVIEW_UPDATE   (several times possibly)
 *   3.  MME_EVENT_TRKSESSIONVIEW_COMPLETE
 * 
 * Because the trksessionview table is a static snapshot expansion of the tracksession, it will not
 * reflect changes in the database in realtime that are caused by syncing.  Use this API to cause it
 * to be updated to reflect the latest database content.
 * 
 * @return -1 on error
 */
int mme_trksessionview_update(mme_hdl_t *hdl);

/**
 * Play the selected fid/bid.  
 *
 * This requires that the HMI first create a track session using
 * the QDB interface.  Calling mme_play while another title is playing will cause the
 * first one to be stopped and the new on to be started.
 *
 * The decision to play a fid or bid comes from the mode of the tracksession when it was
 * created using mme_newtrksession API.
 *
 * @see mme_newtrksession
 *
 * @param hdl The MME connection handle
 * @param fid The FID or BID found in the tracksession to play.
 * @return -1 on error with errno set if an error occured.
 */
int mme_play(mme_hdl_t *hdl, uint64_t fid);

/**
 * Play a bookmark.
 *
 * This functions very similar to mme_play( ) except that it plays a fid at its
 * bookmark location rather than the beginning.  This requires just like mme_play( ) that the
 * fid be in the track session that is active.
 *
 * @param hdl The MME connection handle
 * @param bookmarkid The bookmark ID to play
 * @return -1 on error with errno set if an error occured.
 */
int mme_play_bookmark(mme_hdl_t *hdl, uint64_t bookmarkid);

/**
 * Play a file based on the filename
 * NOTE: This call is deprecated. Use MME_PLAYMODE_FILE track session instead.
 * 
 * This function is similar to mme_play( ).  It will play a file on a mediastore
 * that may or may not have been synchronized.
 * 
 * Note that the filename must begin with a '/' character.
 *
 * @param hdl The MME connection handle
 * @param msid The mediastore ID that the file is on
 * @param filename The path and filename (minus the mountpath) of the file to play
 * 
 * @return -1 on error.  errno is set.
 */
int mme_play_file(mme_hdl_t *hdl, uint64_t msid, const char *filename);

/**
 * Stop playing a playing song.  It is ok to call stop even if nothing is playing.
 *
 * @param hdl The MME connection handle
 */
int mme_stop(mme_hdl_t *hdl);

/**
 * Skip to the next title in the track session.
 *
 * @param hdl The MME connection handle
 * @return -1 on error with errno set.
 *         errno ENODATA indicates that there were no more tracks to play
 */
int mme_next(mme_hdl_t *hdl);

/**
 * Skip backwards to the previous title.  Works for random or sequential playback.
 *
 * @param hdl The MME connection handle
 * @return -1 on error with errno set.
 *         errno ENODATA indicates that there were no more tracks to play
 */
int mme_prev(mme_hdl_t *hdl);

/**
 * Set Play Speed
 *
 * Set the playback speed for all tracks on the control context.  The requested
 * speed is not guaranteed for all devices and clients should get the status
 * of playback afterwards to learn the real playback speed that is being used.
 *
 * The speed is expressed in units of 1/1000 of normal speed: 1000 means normal
 * speed, 2000 double speed etc.  The graph will select the closest supported
 * speed.  Negative values mean reverse and zero means pause.  Values between
 * 0 and abs(1000) are slow speed playback.
 *
 * @param hdl The MME connection handle
 * @param speed The speed to use for playback.
 *
 * @return -1 on error with errno set.
 */
int mme_play_set_speed(mme_hdl_t *hdl, int speed);

/**
 * Get the play speed
 *
 * @param hdl The MME connection handle
 * @param speed The speed on the control context.  returned.
 *
 * @return -1 on error with errno set
 */
int mme_play_get_speed(mme_hdl_t *hdl, int *speed);

/**
 * Seek to a specific time in the title.
 *
 * @param time The time to seek to in milliseconds.  This requires that the media is already
 *             playing.
 * @param hdl The MME connection handle
 * @return -1 on error with errno set.
 */
int mme_seektotime(mme_hdl_t *hdl, uint64_t time);

/**
 * Set the output attributes for the specified output device(s).
 *
 * @param hdl The MME connection handle
 * @param outputid The output device id.  Set to 0 to apply to all output devices that are in use
 *                 by the control context.
 * @param attr The output attributes to set.
 *
 * @return -1 on error with errno set
 */
int mme_play_set_output_attr(mme_hdl_t *hdl, uint64_t outputdeviceid, mme_output_attr_t *attr);

/**
 * Get the output attributes for the specified output device
 *
 * @param hdl The MME connection handle
 * @param outputid The output device id.  Set to 0 to get the attributes from the first output
 *                 device that is connected to the control context.
 * @param attr The attr structure that the MME will write the output device attributes to.
 *
 * @return -1 on error with errno set
 */
int mme_play_get_output_attr(mme_hdl_t *hdl, uint64_t outputdeviceid, mme_output_attr_t *attr);

/**
 * Attach an output to a zone.  If the zone is in use then this will attempt to have it used
 * synchronously with other outputs on that zone.
 *
 * This setting will be saved for the zone for the next time it is used.
 *
 * @param hdl The MME Connection handle
 * @param zoneid The zone to attach the output to.  If 0 then use the current CC zone.
 * @param outputid The outputdeviceid to attach
 *
 * @return -1 on error with errno set
 */
int mme_play_attach_output(mme_hdl_t *hdl, uint64_t zoneid, uint64_t outputid);

/**
 * Detach an output from a zone.  If there are no more outputs on that zone active, then playback will stop.
 *
 * @param hdl The MME Connection handle
 * @param zoneid The zone to detach the output from.  If 0 then use the current CC zone.
 * @param outputid The outputid to detach
 *
 * @return -1 on error with errno set
 */
int mme_play_detach_output(mme_hdl_t *hdl, uint64_t zoneid, uint64_t outputid);

/**
 * Sets the zone to use for playback on the control context.
 *
 * @param hdl The MME Connection handle
 * @param zoneid The zone to use on the control context
 *
 * @return -1 on error with errno set
 */
int mme_play_set_zone(mme_hdl_t *hdl, uint64_t zoneid);

/**
 * Get the zoneid that is used by the control context.
 *
 * @param hdl The MME Connection handle
 * @param zoneid The zoneid used by the control context
 *
 * @return -1 on error.
 */
int mme_play_get_zone(mme_hdl_t *hdl, uint64_t *zoneid);

/**
 * Create a zone.
 *
 * @param hdl The MME connection handle
 * @param name The name of the zone
 * @param zoneid The created zoneid. Returned.
 *
 * @return -1 on error
 */
int mme_zone_create(mme_hdl_t *hdl, const char *name, uint64_t *zoneid);

/**
 * Delete a zone
 *
 * @param hdl The MME connection handle
 * @param zoneid The zoneid to delete.  Cannot be the currently set zone
 *
 * @return -1 on error.  EBUSY is returned as errno if the zoneid is currently being used
 */
int mme_zone_delete(mme_hdl_t *hdl, uint64_t zoneid);

/**
 * Set an output device's permanent field.
 *
 * @param hld the MME connection handle
 * @param outputid The output device ID to make permanent.
 * @param permanent 1=permanent, 0=not permanent
 *
 * @return -1 on error
 */
int mme_output_set_permanent(mme_hdl_t *hdl, uint64_t outputid, int permanent);

/**
 * Get the next queued MME event 
 * 
 * The event that is returned is stored in the mme_hdl_t and is not to be free'd by the
 * client.  When mme_get_event( ) is called on a mme_hdl_t object, it invalidates the
 * previous mme_event_t returned.  Clients who want to keep the old event should copy
 * it out before calling mme_get_event( ) a second time.
 *
 * @param hdl The MME connection handle
 * @param mme_event A pointer to the event
 * @return -1 on error with errno set.
 */
int mme_get_event(mme_hdl_t *hdl, mme_event_t **mme_event);

/**
 * Get the playback status 
 *
 * @param hdl The MME connection handle
 * @param play_status Snapshot of the current playback status 
 * @return -1 on error with errno set.
 */
int mme_play_get_status(mme_hdl_t *hdl, mme_play_status_t *play_status);

/**
 * Get information about the current playing track.
 *
 * @param hdl The MME connection
 * @param info The information structure that will be filled out with details about the current playing file
 * @return -1 on error
 */
int mme_play_get_info(mme_hdl_t *hdl, mme_play_info_t *info);

/**
 * Gets info about the track session.
 *
 * Make sure to use this API rather than checking the trksession table for this
 * information.  This is because the MME may route the call to external devices
 * such as iPod's.
 *
 * @param hdl The MME connection handle
 * @param trksessionid The track session ID.  Not set if NULL. (out)
 * @param current_trk The current track in the playlist that is being played.  Not set if NULL (out)
 * @param total_trk The total number of tracks in the tracksession. Not set if NULL (out)
 * @return -1 on error with errno set.
 */
int mme_trksession_get_info(mme_hdl_t *hdl, uint64_t *trksessionid, uint64_t *current_trk, uint64_t *total_trk);

/**
 * Deprecated, use mme_random_set() instead.
 */
int mme_setrandom(mme_hdl_t *hdl, mme_mode_random_t random);

/**
 * Set the zone's track session to playback in random order. If the MME is
 * playing a device that its own internal playback engine (like an iPod), the
 * random mode will by default be set at the device level and not at the MME
 * track session level.
 *
 * @param hdl The MME connection handle
 * @param random The random mode can be one of the following
 *          MME_RANDOM_OFF - Random playback is off.
 *          MME_RANDOM_ALL - Random playback for the track session.
 *          MME_RANDOM_ALBUMS - The MME does not support this type of random and will fallback 
 *                  to MME_RANDOM_ALL, but if playback is done externally (i.e.
 *                  iPod) then the random command is handle by the device.
 * @param flags None, or MME_RANDOMFLAG_MMETRACKSESSION to force the random mode
 *          to be set at the MME track session level for devices that are track
 *          session capable (iPod).
 * @return -1 on error with errno set, otherwise success.
 */
int mme_random_set(mme_hdl_t *hdl, mme_mode_random_t random, uint32_t flags);

/**
 * Determine if the zone is playing randomly.
 *
 * @param hdl The MME connection handle
 * @return MME_RANDOM_OFF, MME_RANDOM_ALL, MME_RANDOM_ALBUMS, or -1 on error with errno set.
 */
int mme_getrandom(mme_hdl_t *hdl);

/**
 * Deprecated, use mme_repeat_set() instead.
 */
int mme_setrepeat(mme_hdl_t *hdl, mme_mode_repeat_t repeat);

/**
 * Set the zone's track session to playback in repeat mode. If the MME is
 * playing a device that its own internal playback engine (like an iPod), the
 * repeat mode will by default be set at the device level and not at the MME
 * track session level.
 *
 * @param hdl The MME connection handle
 * @param repeat The repeat mode can be one of the following
 *          MME_REPEAT_OFF - Repeat is off.
 *          MME_REPEAT_SINGLE - Repeat only the current playing track.
 *          MME_REPEAT_ALL - Repeat all tracks in the track session.
 * @param flags None, or MME_REPEATFLAG_MMETRACKSESSION to force the repeat mode
 *          to be set at the MME track session level for devices that are track
 *          session capable (iPod).
 * @return -1 on error with errno set, otherwise success.
 */
int mme_repeat_set(mme_hdl_t *hdl, mme_mode_repeat_t repeat, uint32_t flags);

/**
 * Gets the zone's repeat state.
 *
 * @param hdl The MME connection handle
 * @return MME_REPEAT_OFF, MME_REPEAT_SINGLE, MME_REPEAT_ALL, or -1 on error with errno set.
 */
int mme_getrepeat(mme_hdl_t *hdl);

/**
 * Save the current playing position for the active tracksession.
 *
 * This allows it to be resumed later on using mme_trksession_resume_state( ) or
 * mme_play_resume_msid( )
 *
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_trksession_save_state(mme_hdl_t *hdl);

/**
 * Resumes playback of a tracksession from where it was last saved.
 *
 * @param hdl The MME connection handle
 * @return -1 on error with errno set.
 * 
 * Additionally on an error, where the FID does not exist, 
 * errno will be set to a value of ENOENT.
 */
int mme_trksession_resume_state(mme_hdl_t *hdl);

/**
 * Set the track session ID that is used to resume the mediastore with.
 *
 * More than one msid can have the same trksessionid
 *
 * @param hdl The MME connection handle
 * @param msid The msid to set the trksessionid to
 * @return -1 on error with errno set.
 */
int mme_set_msid_resume_trksession(mme_hdl_t *hdl, uint64_t msid);

/**
 * Resume playback for the mediastore.
 *
 * For mediastores that a track session was saved and playback uses MME track sessions then
 * it will resume that track session state.
 *
 * For devices like iPods where they device itself maintains state knowledge this command will
 * create a new track session and resume playback with the devices memory.
 *
 * @hdl The MME connection handle
 * @msid The mediastore to resume playback of
 * 
 * @return -1 on error.  errno is set.
 */
int mme_play_resume_msid(mme_hdl_t *hdl, uint64_t msid);

/**
 * Buttons can be passed into the MME for the browsing of devices that support
 * navigation.  See mm/types.h for the list of buttons.
 *
 * @see mm/types.h
 *
 * @param hdl The MME connection handle
 * @param button The button press to send to the device.
 * @return -1 on error with errno set
 */
int mme_button(mme_hdl_t *hdl, mm_button_t button);

/**
 * Set the scan mode state.
 *
 * The scanmode setting is the maximum number of seconds from the beginning of
 * the track to play before going to the next track.
 *
 * If the scanmode setting is changed while a track is playing it will take effect
 * immediately and will behave as if it were set before the track started
 * playing.
 *
 * @param hdl The MME connection handle
 * @param time The maximum number of milliseconds to play a track before ending
 *                it.  0 disables scan mode.
 * @return -1 on error.
 */
int mme_setscanmode(mme_hdl_t *hdl, uint64_t time);

/**
 * Get the scan mode setting.
 *
 * This retrieves the scan mode setting from the control context.  This value is set
 * in the first place by mme_setscanmode( ).
 *
 * @param hdl The MME connection handle.
 * @param time The maximum number of milliseconds to play a track before ending it.  0
 *             indicates that scan mode is disabled.  Returned.
 *
 * @return -1 on error.
 */
int mme_getscanmode(mme_hdl_t *hdl, uint64_t *time);

/**
 * Set Mediastore Synchronizer to prioritize a folder.
 *
 * Choose a folderid from the folders table that the requires immediate synchronization.  
 * The Current MSS when pause its current operation to handle the request, and then
 * return to continue on with preivous work.
 *
 * @param hdl The MME connection handle
 * @param folderif The folderid of the folder to be synced
 * @return -1 on error.
 */
int mme_setpriorityfolder(mme_hdl_t *hdl, uint64_t folderid);

/**
 * Set the auto pause setting
 *
 * @param hdl The MME connection handle
 * @param enable false if files should be played automatically.  
 *               true if they are started paused
 * @return -1 on error
 */
int mme_setautopause(mme_hdl_t *hdl, bool enable);

/**
 * Get the auto pause setting
 *
 * @param hdl The MME connection handle
 * @return -1 on error.  1 if enabled, 0 otherwise
 */
int mme_getautopause(mme_hdl_t *hdl);

/**
 * Add files to be copied/ripped 
 * 
 * @param hdl The MME connection handle
 * @param copyinfo Info describing the copy operation. 
 * @param statement SQL statement of fids that you want to encode.
 * @param flags Option flags.
 * @return -1 on error
 */
int mme_mediacopier_add(mme_hdl_t *hdl, mme_mediacopier_info_t *copyinfo, const char *statement, uint32_t flags);

/**
 * Add files to be copied/ripped specifying metadata
 * 
 * @param hdl The MME connection handle
 * @param copyinfo Info describing the copy operation. 
 * @param statement SQL statement of fids that you want to encode.
 * @param flags Option flags.
 * @param unknown_album to use if album is unknown
 * @param unknown_artist to use if artist is unknown
 * @return -1 on error
 */
int mme_mediacopier_add_with_metadata(mme_hdl_t *hdl, mme_mediacopier_info_t *copyinfo, const char *statement, 
	uint32_t flags, const char *unknown_album, const char *unknown_artist);

/**
 * Remove files from the copy queue 
 * 
 * @param hdl The MME connection handle
 * @param statement SQL statement of cqid's that you want to remove from the copy queue
 * @param flags Option flags.
 * @return -1 on error
 */
int mme_mediacopier_remove(mme_hdl_t *hdl, const char *statement, uint32_t flags);

/**
 * Clear all files from the copy queue 
 * 
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_mediacopier_clear(mme_hdl_t *hdl);

/**
 * Enable the mediacopier 
 * 
 * @param hdl The MME connection handle
 * @param flags Option flags.
 * @return -1 on error
 */
int mme_mediacopier_enable(mme_hdl_t *hdl, uint32_t flags);

/**
 * Disable the mediacopier 
 * 
 * @param hdl The MME connection handle
 * @param flags Option flags.
 * @return -1 on error
 */
int mme_mediacopier_disable(mme_hdl_t *hdl, uint32_t flags);

/**
 * Get the copy status 
 *
 * @param hdl The MME connection handle
 * @param copy_status Snapshot of the current copy status 
 * @return -1 on error with errno set.
 */
int mme_mediacopier_get_status(mme_hdl_t *hdl, mme_copy_status_t *copy_status);

/**
 * Cleanup incomplete files that were synced.  This can only be called while
 * the mediacopier is not enabled.
 * 
 * @param hdl The MME connection handle
 * @return -1 on error with errno set.  EBUSY indicates that mediacopier is enabled.
 */
int mme_mediacopier_cleanup(mme_hdl_t *hdl);


/**
 * Start device detection; this has meaning only if device
 * detection wasn't already started.
 * 
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_start_device_detection( mme_hdl_t *hdl );

/**
 *  Get the video information.
 * 
 * @param hdl 		The MME connection handle
 * @param info	Pointer to video information structure to fill in.
 * @return -1 on error
 */
int	mme_video_get_info( mme_hdl_t *hdl, mm_video_info_t *info );

/**
 *  Set the video properties.
 * 
 * @param hdl 		The MME connection handle
 * @param props	Pointer to video properties structure.
 * @return -1 on error
 */
int	mme_video_set_properties( mme_hdl_t *hdl, mm_video_properties_t *props );

/**
 *  Get the video status
 * 
 * @param hdl The MME connection handle
 * @param status	Pointer to video status structure to fill in.
 * @return -1 on error
 */
int	mme_video_get_status( mme_hdl_t *hdl, mm_video_status_t *status );

/**
 * Get Audio status
 *
 * @param hdl The MME connection handle
 * @param status Pointer to the audio status structure to fill in.
 * @return -1 on error
 */
int mme_audio_get_status(mme_hdl_t *hdl, mm_audio_format_t *status);

/**
 *  Get the angle information for the current position
 * 
 * @param hdl The MME connection handle
 * @param title	The title for which the information is wanted.
 * @param info	Pointer to video angle info structure to fill in.
 * @return -1 on error
 */
int	mme_video_get_angle_info( mme_hdl_t *hdl, uint64_t title, mm_video_angle_info_t *info );

/**
 * Set the video angle for the current file.
 * 
 * Fails if the serial number is stale, or the command is not appropriate
 * for the current file being played.
 * 
 * @param hdl The MME connection handle
 * @param title	The the angle is to be set on.
 * @param index	Index to desired angle from array in previous call to
 * 			mme_get_video_angle_info().
 * @return -1 on error
 */
int	mme_video_set_angle( mme_hdl_t *hdl, uint64_t title, int index );

/**
 * Get the audio channel information for the given title
 * 
 * @param hdl The MME connection handle
 * @param title	The title for which the information is wanted.
 * @param info	Pointer to audio info structure to fill in.
 * @return -1 on error
 */
int mme_video_get_audio_info( mme_hdl_t *hdl, uint64_t title, mm_video_audio_info_t *info );

/**
 * Sets the audio for the specified title to the one in the index of the array
 * of a previous call to mme_get_audio_info().
 * 
 * Fails if specified title isn't playing.
 * 
 * @param hdl The MME connection handle
 * @param title Title number used in previous call to
 * 			mme_get_video_audio_info().
 * @param index	Index to desired angle from array in previous call to
 * 			mme_get_video_audio_info().  -1 turns audio off.
 * @return -1 on error
 */
int	mme_video_set_audio ( mme_hdl_t *hdl, uint64_t title, int index );

/**
 * Get the subtitle information for the given title.
 * 
 * @param hdl The MME connection handle
 * @param title	The title for which the information is wanted.
 * @param info	Pointer to subtitle info structure to fill in.
 * @return -1 on error
 */
int	mme_video_get_subtitle_info ( mme_hdl_t *hdl, uint64_t title, mm_video_subtitle_info_t *info );

/**
 * Sets the audio for the specified title to the one in the index of the array
 * of a previous call to mme_get_subtitle_info().
 * 
 * Fails if specified title isn't playing.
 * 
 * @param hdl The MME connection handle
 * @param title Title number used in previous call to
 * 			mme_get_video_subtitle_info().
 * @param index	Index to desired subtitle from array in previous call to
 * 			mme_get_video_subtitle_info().  -1 turns subtitles off.
 * @return -1 on error
 */
int	mme_video_set_subtitle ( mme_hdl_t *hdl, uint64_t title, int index );

/**
 *  Get the DVD status
 * 
 * @param hdl The MME connection handle
 * 
 * @param status	Pointer to DVD status structure to fill in.
 * @return -1 on error
 */
int	mme_dvd_get_status ( mme_hdl_t *hdl, mm_dvd_status_t *status );

/**
 * Gets information about the status of system synchronization.
 *
 * @param	hdl	MME connection handle.
 * @param	status	A pointer to an array of elements to place status. May be
 * 					NULL to get number of media stores actively involved in 
 * 					synchronization.
 * @param	status_size	The number of elements in the status array. May be 0.
 * @return	-1 on failure
 * @return  >= 0 the number of media stores that have synchronization passes
 *          in progress or pending.
 *          If the return value is greater than or equal to status_size,
 *       	elements in status contain valid data. Otherwise, only the
 *       	first elements do.
 * 
 * When the values are read from the various locations, it should be
 * remembered that it provides a snapshot.
 * 
 * Additionally, there is one circumstance under which the function will
 * return fewer status elements that the caller provides data for. This is
 * if the number of media stores being sychronized or pending synchronization
 * is greater than about 500; in this case, even if the caller provides a
 * buffer large enough for more than that many devices, the MME does not
 * extract enough of that buffer to fill it beyond the initial part handed to it.
 */
int mme_sync_get_status (
	mme_hdl_t *hdl,
	mme_sync_status_t *status,
	size_t status_size
);

/**
 * Gets information about the status of synchronization about a specific
 * media store.
 *
 * On success, the status structure will be filled in.
 *
 * @param	hdl	MME connection handle.
 * @param	msid	The ID of the mediastore that sync status is wanted on.
 * @param	status	A pointer to an array of elements to place status.
 * @return	-1 on failure
 */
int mme_sync_get_msid_status (
	mme_hdl_t *hdl,
	uint64_t  msid,
	mme_sync_status_t *status
);

/**
 * Checks and optionally repairs a database folder's consistency. This applies 
 * only to database folders for media stores that have consistency checking 
 * information associated with them. 
 *  
 * @param hdl		MME connection handle.
 * @param folderid	ID of folder to check.
 * @param flags		Flags controlling operation. Only MME_SYNC_OPTION_REPAIR and
 *                  MME_SYNC_OPTION_RECURSIVE are supported
 *                  (but MME_SYNC_OPTION_VERIFY is implied).
 * @return -1 on failure 
 * @return 0 check or repair request started.
 */
int mme_sync_db_check(mme_hdl_t *hdl, uint64_t folderid, uint32_t flags);

/**
 * Create a new playlist
 *
 * @param hdl  The MME connection handle
 * @param msid Set to a mediastore.  If that the msid is pruned, this playlist is deleted.  Set to 0
 *             to have no pruning on this mediastore.
 * @param name Any textual name to display
 * @param plid The new playlist ID.
 *
 * @return -1 on error
 */
int mme_playlist_create(mme_hdl_t *hdl, uint64_t msid, const char *name, uint64_t *plid);

/**
 * Sets the playlist statement to generate the list of fids.
 *
 * @param hdl  The MME connection handle
 * @param sql  The sql statement to get the fids, like a track session.
 *
 * @return -1 on error
 */
int mme_playlist_set_statement(mme_hdl_t *hdl, uint64_t plid, const char *sql);

/**
 * Delete a playlist
 *
 * This deletes a playlist from the system.  If the playlist is a custom playlist and was added to the
 * playlistdata_custom then that table must be deleted from manually.  This function only causes
 * the playlists and playlistdata tables to be deleted from.
 *
 * @param hdl The MME connection handle
 * @param plid The playlist ID to delete
 *
 * @return -1 on error
 */
int mme_playlist_delete(mme_hdl_t *hdl, uint64_t plid);

/**
 * Create a new bookmark for the playing track
 *
 * @param hdl The mme connection handle
 * @param name The name of the bookmark.  Pass NULL if not important.
 * @param bookmarkid The created bookmark ID.  Returned
 *
 * @return -1 on error (errno is set).
 */
int mme_bookmark_create(mme_hdl_t *hdl, const char *name, uint64_t *bookmarkid);

/**
 * Update or create a new bookmark for the playing track.
 *
 * @param hdl The mme connection handle
 * @param name The name of the bookmark.  Pass NULL if not important.
 * @param bookmarkid  IN: pointer to value 0 for create, >0 for update.
 *                   OUT: bookmarkid of created or updated bookmark.
 * @param btype The bookmark type for the created or updated bookmark.
 * @param flags 0 for default behaviour.
 *              MME_BOOKMARKUPDATE_FINDFIRSTOFTYPE - look for an existing bookmark for the
 *                                                   playing fid of a given type--update
 *                                                   the existing bookmark if found, create
 *                                                   a new bookmark if no existing bookmark.
 *
 * @return -1 on error (errno is set).
 */
int mme_bookmark_update(mme_hdl_t *hdl, const char *name, uint64_t *bookmarkid, mme_bookmark_type_t btype, uint32_t flags);

/**
 * Delete bookmarks
 *
 * This API allows deleting of a bookmark based on its bookmarkid, or all
 * bookmarks for the fid can be deleted at once.
 *
 * @param hdl The mme connection handle
 * @param bookmarkid The bookmarkid to delete.  Set to 0 if deleting based on fid
 * @param fid The fid to delete bookmarks from.  This will delete all bookmarks for that fid.  
 *            Set to 0 if deleting only one specific bookmark.
 *
 * @return -1 on error (errno is set)
 */
int mme_bookmark_delete(mme_hdl_t *hdl, uint64_t bookmarkid, uint64_t fid);

/**
 * Delete bookmarks
 *
 * This API allows deleting of a bookmark based on its bookmarkid, fid,
 * or bookmark type.  Can delete all bookmarks for a given fid or type.
 *
 * @param hdl The mme connection handle
 * @param bookmarkid The bookmarkid to delete.  Set to 0 if deleting based on fid
 * @param fid The fid to delete bookmarks from.  This will delete all bookmarks for that fid.  
 *            Set to 0 if deleting only one specific bookmarkid.
 * @param btype The type of bookmark to delete.  Set to MME_BOOKMARK_TYPE_UNKNOWN
 *              to delete all types for a given bookmarkid or fid.
 *              If bookmarkid and fid are both 0, all bookmarks of this type
 *              will be deleted.  If btype is also 0, bookmarks are cleared.
 * @param flags Set to 0.  Available for future use.
 *
 * @return number of deleted bookmarks
 * @return -1 on error (errno is set)
 */
int64_t mme_bookmark_delete_type(mme_hdl_t *hdl, uint64_t bookmarkid, uint64_t fid, mme_bookmark_type_t btype, uint32_t flags);


/**
 * Gets the region code for the DVD media (i.e. the disc)
 *
 * Fails if there is no region information on the disc, if the disc isn't DVD
 * or if the mediastores isn't currently active.
 *
 * @param	hdl	MME connection handle.
 * @param	msid	The ID of the mediastore that region info is wanted from.
 * @param	region	Region as reported by media
 * @return	-1 on failure
 */
int mme_dvd_get_disc_region(mme_hdl_t *hdl, uint64_t msid, uint32_t *region);

/**
 * Set metadata for a file
 *
 * @param hdl The MME connection handle
 * @param fid The file ID of the file you want to modify the metadata
 * @param metadata The data to update in the database and the file's metadata tags
 * @param flags Flags that affect the behaviour of the call. None are currently defined.
 * @return -1 on error
 *
 *
 * @todo un-void the param
 */
int mme_metadata_set(mme_hdl_t *hdl, uint64_t fid, mm_metadata_t *metadata, uint64_t flags);


/**
 * Create a new metatdata session.
 *
 * @param hdl The MME connection handle
 * @param session Continer for session information.
 * @return -1 on error, with errno set.
 */
int mme_metadata_create_session(mme_hdl_t *hdl, mme_metadata_session_t **session);

/**
 * Free a metatdata session.  Frees all memory and images used during a session.
 *
 * @param session Container for session information.
 * @return -1 on error, with errno set.
 */
int mme_metadata_free_session(mme_metadata_session_t *session);

/**
 * Get metadata for a given track based on FID.
 *
 * @param session Container for session information.
 * @param fid FID from library upon which to obtain metadata information.
 * @param metadata_groups A string that represents the metadata information groups of interest.
 * @param mdinfo_rid A generated metadata information request ID.
 * @param metadata The returned metadata information about the requested fid, if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_getinfo_library(mme_metadata_session_t *session, uint64_t fid, const char *metadata_groups, uint64_t *mdinfo_rid, mme_metadata_info_t **metadata);

/**
 * Get metadata for a given track based on a file path.
 *
 * @param session Container for session information.
 * @param msid The msid that the relative path exists on.
 * @param file File path to the track, relative to the msid mountpath.
 * @param metadata_groups A string that represents the metadata information groups of interest.
 * @param mdinfo_rid A generated metadata information request ID.
 * @param metadata The returned metadata information about the requested fid, if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_getinfo_file(mme_metadata_session_t *session, uint64_t msid, const char *file, const char *metadata_groups, uint64_t *mdinfo_rid, mme_metadata_info_t **metadata);

/**
 * Get metadata for the currently playing track.
 *
 * @param session Container for session information.
 * @param metadata_groups A string that represents the metadata information groups of interest.
 * @param mdinfo_rid A generated metadata information request ID.
 * @param metadata The returned metadata information about the requested fid, if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_getinfo_current(mme_metadata_session_t *session, const char *metadata_groups, uint64_t *mdinfo_rid, mme_metadata_info_t **metadata);

/**
 * Get metadata for a mediastore.  Multiple MDPS may return data.
 *
 * @param hdl A valid connection handle to the MME.
 * @param msid The mediastore to get metadata for.
 * @param max_mdps The maximum number of MDPs to search (0 for unlimited)
 * @param max_results The maximum number of MDP results to return (0 for unlimited).
 * @param flags Reserved for future use.
 * @param mdinfo_rid A spot to hold a returned request ID.
 * @param metadata The returned metadata information about the requested mediastore, if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_getinfo_mediastore(mme_hdl_t *hdl, uint64_t msid, uint32_t max_mdps, uint32_t max_results, uint32_t flags, uint64_t *mdinfo_rid, mme_metadata_info_t **metadata); 
/**
 * Load an image from a track.
 *
 * @param session Container for session information.
 * @param mdinfo_rid The metadata infromation request ID, obtained from calls to the mme_medatata_get_info_XXX API calls.
 * @param image_id  The image ID of an image, obtained from the track metadata.
 * @param image_format_profile Predefined profile format index. Set to -1 for no conversion.
 * @param mdimage_rid A generated metadata image request ID.
 * @param image_url The returned image URL if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_image_load(mme_metadata_session_t *session, uint64_t mdinfo_rid, unsigned image_id, int image_format_profile, uint64_t *mdimage_rid, mme_metadata_image_url_t **image_url);

/**
 * Unload or cancel a loaded image.
 *
 * @param session Container for session information.
 * @param mdimage_rid The metadata image request ID, obtained from a call to the
 *                    mme_medatata_image_load API function.
 * @return -1 on error, with errno set.
 */
int mme_metadata_image_unload(mme_metadata_session_t *session, uint64_t mdimage_rid);

/**
 * Clear the image cache.
 *
 * @param hdl The MME connection handle
 * @param msid The mediastore ID for which cached images should be purged.
 * @return -1 on error, with errno set.
 */
int mme_metadata_image_cache_clear(mme_hdl_t *hdl, uint64_t msid);

/* Link an external image to a fid in the metadata cache.
 *
 * @param session Container for session information.
 * @param fid  The fid that the image should be associated with.
 * @param image_format_profile The profile to use.
 * @param file A full path to the image to be linked to a fid.
 * @param mdinfo_rid A generated metadata information request ID.
 * @param image_url The returned image URL if used synchronously.
 * @return -1 on error, with errno set.
 */
int mme_metadata_link_image(mme_metadata_session_t *session, uint64_t fid, int image_format_profile, const char *file, uint64_t *mdinfo_rid, mme_metadata_image_url_t **image_url);

/* Unlink an external image from a fid in the metadata cache.
 *
 * @param hdl The MME connection handle
 * @param fid  The fid that the image should be unassociated with.
 * @param image_index The index of the image.
 * @param image_format_profile The profile to use.
 * @return -1 on error, with errno set.
 */
int mme_metadata_unlink_image(mme_hdl_t *hdl, uint64_t fid, int image_index, int image_format_profile);

/**
 * Set mediacopier mode
 *
 * @param hdl The MME connection handle
 * @param copymode The selected ripping mode
 * @return -1 on error
 */
int mme_mediacopier_set_mode(mme_hdl_t *hdl, mme_mediacopier_mode_t copymode);
 
/**
 * Get mediacopier mode
 *
 * @param hdl The MME connection handle
 * @param copymode The selected ripping mode.  Returned.
 * @return -1 on error
 */
int mme_mediacopier_get_mode(mme_hdl_t *hdl, mme_mediacopier_mode_t *copymode);

/**
 * Set debug settings
 *
 * @param hdl The MME connection handle
 * @param verbose The new verbose setting to use
 * @param debug The new debug setting to use
 * @return -1 on error
 */
#define MME_MAX_VERBOSE 10
#define MME_MAX_DEBUG   10
int mme_set_debug(mme_hdl_t *hdl, uint8_t verbose, uint8_t debug);

/**
 * Set logging settings for logging modules.
 *  
 * @param hdl     The MME connection handle
 * @param name    The name of the mme logging module, NULL sets all modules.
 * @param verbose The new verbose setting to use
 * @param debug   The new debug setting to use
 * @return 0 on success
 * @return -1 on error
 */
int mme_set_logging(mme_hdl_t *hdl, const char* name, uint8_t verbose, uint8_t debug);

/**
 * Get the logging settings for logging modules.
 *  
 * @param hdl      The MME connection handle
 * @param name     The name of the mme logging module, NULL indicates all.
 * @param settings A comma seperated list of logging modules and thier log levels 
 *                 in the format of <module>=<verbose>:<debug>
 * @param size     The size of the setting buffer to put the result into.
 * @return 0 on success
 * @return -1 on error
 */
int mme_get_logging(mme_hdl_t *hdl, const char* name, char* settings, size_t size);

/**
 * Set files as permanent so that they won't be pruned
 *
 * @param hdl The MME connection handle
 * @param permanent Permanent: true, Prunable: false
 * @param fidselect The fid select statement
 * @return -1 on error
 */
int mme_set_files_permanent(mme_hdl_t *hdl, bool permanent, const char * fidselect);

/**
 * Query the number of titles within the currently playing track/device. Use 
 * this only if the MME_PLAYSUPPORT_NAVIGATION bit is set in the 
 * mme_play_info_t structure returned from mme_play_get_info()
 *
 * @param hdl The MME connection handle
 * @param title The current title number
 * @param ntitles The number of titles in the currently playing track.
 * @param chapter The current chapter number
 * @param ntitles The number of chapters in the current title.
 * @return -1 on error
 * @return 0 on success.
 */
int mme_get_title_chapter(mme_hdl_t *hdl, uint64_t *title, uint64_t *ntitles, uint64_t *chapter, uint64_t *nchapters);

/**
 * Jump to a specific title/chapter. Use this only if the 
 * MME_PLAYSUPPORT_NAVIGATION bit is set in the mme_play_info_t structure 
 * returned from mme_play_get_info()
 *
 * @param hdl The MME connection handle
 * @param title The title you want to play
 * @param chapter The chapter to play.
 * @return -1 on error
 * @return 0 on success.
 */
int mme_seek_title_chapter(mme_hdl_t *hdl, uint64_t title, uint64_t chapter);

/** Get info about the MME trksessionview.
 *
 * @param hdl The MME connection handle
 * @param track The track (0 based) into the mme trksessionview you want details for.
 * @param title The title or device level track of the track you want details for.
 * @param info The requested information is stored here.
 *
 * @return -1 on error
 * @return 0 on success.
 */
int mme_trksessionview_get_info(mme_hdl_t *hdl, unsigned track, unsigned title, mme_trksessionview_info_t *info);

/** Get info about the current track in the MME trksessionview.
 *
 * @param hdl The MME connection handle
 * @param info The requested information is stored here.
 *
 * @return -1 on error
 * @return 0 on success.
 */
int mme_trksessionview_get_current(mme_hdl_t *hdl, mme_trksessionview_info_t *info);

/*
 * Get metadata about something in the MME trksessionview
 *
 * @param hdl The MME connection handle
 * @param track The track (0 based) into the mme trksessionview you want details for.
 * @param title The title or device level track of the track you want details for.
 * @param chapter The chapter of the specified track you want details for (currently unsupported).
 * @param types	The metadata requested.
 * @param flags Flags, none or MME_TRKSESSIONVIEW_METADATA_NOWPLAYING for currently playing track.
 *
 * @return -1 on error
 * @return metadata structure on success.
 */
mme_metadata_hdl_t *mme_trksessionview_metadata_get(mme_hdl_t *hdl, unsigned track, unsigned title, unsigned chapter, const char *types, uint32_t flags);



/*
 * Write out the trksessionview to the DB. This call returns before the data is
 * actually written out. MME_EVENT_TRKSESSIONVIEW_COMPLETE will be emitted once
 * the data is fully written out. If the data is already written out when the
 * function is called, an MME_EVENT_TRKSESSIONVIEW_COMPLETE will still be
 * emitted (but no writes to the DB will occur).
 *
 * @param hdl The MME connection handle
 * @return -1 on error
 */
int mme_trksessionview_writedb(mme_hdl_t *hdl);


/*
 * Read data from the MME trksessionview.
 * NOTE: Deprecated, use mme_trksessionview_readx() instead.
 *
 * @param hdl The MME connection handle
 * @param array The array in which to save trksessionview entries
 * @param entrysize The size of a single array entry in bytes (only 8 supported).
 * @param offset The 0 based offset to start reading from.
 * @param ntracks The number of tracks requested
 * @param reserved Currently unused. Leave as NULL.
 *
 * @return -1 on error
 * @return number of entries read.
 *
 */
int mme_trksessionview_read(mme_hdl_t *hdl, trksessionview_entry_t *array, size_t entrysize, int offset, int ntracks, void *reserved);


/*
 * Read data from the MME trksessionview
 *
 * @param hdl The MME connection handle
 * @param type The type of information requested.
 * @param offset The 0 based offset to start reading from.
 * @param ntracks The number of tracks requested
 * @param buf The buffer to store the data in.
 * @param buflen [IN]Pointer to the size of the buffer [OUT] size needed for request.
 *
 * @return -1 on error
 * @return number of entries read.
 *
 */
int mme_trksessionview_readx(mme_hdl_t *hdl, unsigned type, int offset, unsigned ntracks, void *buf, unsigned *buflen);

/**
 * This function is used to set the value of the specified columns in
 * the library (or adjunct) table to the specified value on the
 * specified media store (or all media stores).
 * 
 * @param hdl    The MME connection handle
 * @param msid   If 0, all media stores; otherwise the media store to change.
 * @param column The name of the column whose values should change.
 * @param value  The value to set the column to.
 * @return >=0 on success; the number of rows changed in the database table
 * @return -1 on failure
 */
int mme_lib_column_set(mme_hdl_t *hdl, uint64_t msid, const char *column, int value);

/*
 * Mark a whole mediastore as inaccurate.
 * 
 * NOTE: This function may also be implemented by using
 * mme_lib_column_set(0, "accurate", 0);
 *
 * @param hdl The MME connection handle
 * @param msid The msid to mark as inaccurate, 0 means all msids.
 *
 * @return -1 on error
 * @return 0 on success
 */
int mme_ms_clear_accurate(mme_hdl_t *hdl, uint64_t msid);


/**
 * This function is used to append files to the files already in a track
 * session that is used for file playback.
 *
 * It can be used under the following conditions:
 * 1/ The track session was created using the device FID that the file is on.
 * 2/ The track session is not in repeat or random mode.
 *
 * A MME_EVENT_TRKSESSIONVIEW_UPDATE event is emitted if the file is
 * successfully added to the track session to indicate that it has
 * changed. 
 *  
 * Note that the filenames must begin with a '/' character.
 *
 * @param hdl      Handle to the MME.
 * @param nfiles   Number of files to append.
 * @param msid     Array of msids matching the filename array. The msid must
 *                 match the media store FTYPE_DEVICE fid that was used to when
 *                 the trksession what created.
 * @param filename Array of file names to be played including their
 *                 path on the media store, but not including the media
 *                 store's mount path.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_append_files(mme_hdl_t *hdl, uint64_t trksessionid, int nfiles, uint64_t *msid, const char **filename);


/**
 * This function is used to set a new list of files in a track session. The old
 * list (if any) is replaced with the new list. If this call is successful, a
 * MME_EVENT_TRKSESSIONVIEW_UPDATE event is emitted. The offset, if non zero,
 * will be considered the offset/position in the new list/tracksession that the 
 * MME should center on. This offset in the new tracksession must match the
 * currently playing track.
 *
 * Note that the filenames must begin with a '/' character.
 *
 * @param hdl      Handle to the MME.
 * @param nfiles   Number of files to set.
 * @param msid     Array of msids matching the filename array. The msid must
 *                 match the media store FTYPE_DEVICE fid that was used to when
 *                 the trksession what created.
 * @param filename Array of file names to be played including their
 *                 path on the media store, but not including the media
 *                 store's mount path.
 * @param offset   The offset into the new list that should be jumped to. If
 *                 the MME is playing, the current file must match with the
 *                 file at "offset" in the new list.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_set_files(mme_hdl_t *hdl, uint64_t trksessionid, int nfiles, uint64_t *msid, const char **filename, unsigned offset);


/**
 * This function is used to clear the list of files in a track session.
 * Playback must be stopped.
 *
 * @param hdl            Handle to the MME.
 * @param trksessionid   The current tracksession to clear the file for.
 *
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_clear_files(mme_hdl_t *hdl, uint64_t trksessionid);


/**
 * Play at the specified offset in the tracksession.
 *
 * This requires that the HMI first create and set a tracksession. Calling 
 * mme_play_at while another title is playing will cause the first one to be 
 * stopped and the new on to be started. If the track currently playing
 * is part of a device tracksession (i.e. mme_play_get_info() reports
 * MME_PLAYSUPPORT_DEVICE_TRACKSESSION) then the offset will be applied
 * to the device tracksession unless the MME_PLAY_OFFSET_MMETRACKSESSION 
 * flag is used. Otherwise it will apply to the MME level tracksession.
 *
 * NOTE: You need to be playing the iPod before you can jump to an
 * index into it's tracksession (if you aren't playing the iPod 
 * mme_play_get_info() won't have MME_PLAYSUPPORT_DEVICE_TRACKSESSION 
 * set).
 *
 * @see mme_newtrksession
 *
 * @param hdl The MME connection handle
 * @param offset The 0 based offset into the tracksession to play.
 * @param flags None, or MME_PLAY_OFFSET_MMETRACKSESSION to use the MME's 
 *              tracksession for devices that are tracksession capable (iPod).
 * @return -1 on error with errno set if an error occured.
 */
int mme_play_offset(mme_hdl_t *hdl, int offset, uint32_t flags);


/**
* Get device option information for supported devices. Currently only mediafs.
*
* @param hdl       The MME connection handle
* @param msid      The mediastore ID.
* @param xpath     The xpath to fetch (must be the string "/")
* @param flags     Flags which affect the behavior of the operation. None defined.
* @param buflen    The length of the value buffer.
* @param buffer    The buffer to store the value in.
*
* @return -1 on error with errno set.
* @return the buffer size that the full result would occupy up on success
*         (could be larger than buflen).
*/
int mme_device_get_config(mme_hdl_t *hdl, uint64_t msid, const char *xpath, unsigned flags, unsigned buflen, char *buffer);


/**
 * Sets a device options for supported devices. Currently only mediafs.
 *
 * @param hdl       The MME connection handle
 * @param msid      The mediastore ID.
 * @param xpath     The xpath to set (must refer to an attribute, i.e. "/path/to/node@value")
 * @param newvalue  The new value to set set on the result of the xpath.
 * @param flags     Flags which affect the operation. None defined.
 *
 * @return -1 on error with errno set.
 * @return 0 on success.
 */ 

int mme_device_set_config(mme_hdl_t *hdl, uint64_t msid, const char *xpath, const char *newvalue, unsigned flags);

/**
 * Update the hit_count and hit_sequence fields of in the mdi_image_cache table.
 * User may decide to look for the cache directly from the DB and this function
 * allows them to safely update the fields.
 *
 * @param hdl The MME connection handle.
 * @param fid to search for in the  database.
 * @param image_index to search for in the database.
 * @param profile_index to serach for in the database.
 *
 * @return -1 on error.
 * @return the number of updated fields on success.
 */
int mme_metadata_update_hitcount(mme_hdl_t *hdl, uint64_t fid, unsigned image_index, int profile_index);

/** 
 * For systems that don't have a real-time clock implemented, this function must 
 * be called to make sure the database's time values are always monotonically 
 * increasing. 
 * 
 * @param hdl       The MME connection handle 
 *  
 * @return -1 on error with errno set.
 * @return 0 on success.
 */
int mme_timebase_set(mme_hdl_t *hdl);


/**
 * Returns a static snapshot of the state of the currently playing object (not
 * the state or content of the tracksession, just the state of the playing
 * object). This call may not succeed on all types of playback (iPods, HTTP
 * streams, etc.). The object returned is an allocated buffer which (once
 * stored by the client) must be freed by a call to mme_play_state_free().
 *
 * The size of the state will vary based on the type of object playing (i.e.
 * DVD state will be a different size than the state of a MP3 file).
 *
 * @param hdl       The MME connection handle
 * @param state     Pointer to a location in which the MME can store the state buffer pointer.
 * @param len       Pointer to a location in which the MME can store the size of the state buffer.
 *
 * @return -1 on error with errno set.
 * @return 0 on success.
 */ 
int mme_play_state_get(mme_hdl_t *hdl, void **state, int *len);


/**
 * Frees a play state previously allocated by mme_play_state_get().
 *
 * @param state		Pointer to the state object return by mme_play_state_get().
 *
 * @return -1 on error with errno set.
 * @return 0 on success.
 */
int mme_play_state_free(void *state);


/**
 * Resumes playback of a previously saved state within a tracksession.
 *
 * This functions is similar to other play type functions (like
 * mme_play_offset()) in that it requires that a tracksession already be
 * active. The tracksession must contain the fid that was previously playing
 * (for library based tracksessions) or the file that was previously playing
 * (for filemode based tracksessions). The offset parameter must match to the
 * object that was playing when mme_play_state_get() was previously called.
 *
 * @param hdl		The MME connection handle
 * @param state		State returned from a previous call to mme_play_state_get()
 * @param len		Size of the state buffer.
 *
 * @return -1 on error with errno set if an error occured.
 * @return 0 on success
 */
int mme_play_state(mme_hdl_t *hdl, int offset, void *state, int len);

/**
 * Used to set resources in a specific MDP.
 *
 * A resource is an arbitrary entity in a MDP.  Currently, only the MDP
 * rating can be changed via this API, but it is left open for chaging
 * other settings in the future.  The resource is set as paired strings with
 * the following format: "resource1:value1,resource2:value2".
 *
 * @param hdl		The MME connection handle.
 * @param name		The name of the MDP to target.
 * @param flags		Reserved for future flags.
 * 
 *
 * @return -1 on error with errno set if an error occured.
 * @return >=0 representing num resources set.
 */
int mme_mdp_resource_set(mme_hdl_t *hdl, char *name, char *resource, uint32_t flags);

/**
 * Used to get resources from a specific MDP.
 *
 * A resource is an arbitrary entity in a MDP.  Currently, only the MDP
 * rating can be read back from this API, but it is left open for reading
 * other settings in the future.  The request string take a comma seperated 
 * list of resources to read and the result string returns values in a a colon
 * delimited string.  Empty values will have no data associated with them.
 * for example:  search_string = "base_rating,doesnt_exist,base_rating"
 *               return_string = "80::80"
 *
 * @param hdl		The MME connection handle.
 * @param name		The name of the MDP to target.
 * @param buf		A buffer to return the data in.
 * @param size		The size of the buffer.
 * @param flags		Reserved for future flags.
 * 
 *
 * @return -1 on error with errno set if an error occured.
 * @return >=0 representing the number of bytes which would get written
               if the buffer was big enough.
 */
int mme_mdp_resource_get(mme_hdl_t *hdl, char *name, char *resource, char *buf, size_t size, uint32_t flags);

/**
 * Get MME version as a string.
 *
 * @param hdl           The MME connection handle.
 * @param buffer        A buffer to return the version in.
 * @param buflen        The size of the buffer.  A 32-byte buffer is recommended.
 *
 * @return -1 on error with errno set.
 * @return >=0 size of buffer required for full version number.
 */
int mme_version_get(mme_hdl_t *hdl, char *buffer, size_t buflen);

/**
 * Extended play function.
 *
 * @param hdl           The MME connection handle.
 * @param ext           The play command structure.  All unused and reserved
 *                      fields should be zeroed.
 * @param ext_size      The size of the play command structure.
 * 
 * @return -1 on error with errno set.
 * @return 0 on success.
 */
int mme_play_extended(mme_hdl_t *hdl, mme_play_extended_t *ext, size_t ext_size);

/**
 * Set the time update interval for the mediacopier.
 * 
 * NOTE: This setting applies to future copy operations (file/track),
 *       not copy operations currently in progress.
 * 
 * The interval is the period (in milliesconds) between copy status events.
 *
 * @param hdl The MME event handle
 * @param time_ms The time interval between MME_EVENT_MEDIACOPIER_COPYSTATUS 
 *                updates in milliseconds
 *
 * @return -1 on error with errno set
 */
int mme_mediacopier_set_notification_interval(mme_hdl_t *hdl, uint32_t time_ms);

/**
 * This function is used to set a new list of fids in a track session. The old
 * list (if any) is replaced with the new list. If this call is successful, a
 * MME_EVENT_TRKSESSIONVIEW_UPDATE event is emitted. The offset, if non zero,
 * will be considered the offset/position in the new list/tracksession that the 
 * MME should center on. This offset in the new tracksession must match the
 * currently playing track.
 *
 * @param hdl      Handle to the MME.
 * @param nfiles   Number of files to set.
 * @param fids     Array of file IDs to be played.
 * @param offset   The offset into the new list that should be jumped to. If
 *                 the MME is playing, the current fid must match with the
 *                 fid at "offset" in the new list.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_set_fids(mme_hdl_t *hdl, uint64_t trksessionid, int nfids, uint64_t *fids, unsigned offset);

/**
 * This function is used to clear the list of fids in a track session.
 * Playback must be stopped.
 *
 * @param hdl            Handle to the MME.
 * @param trksessionid   The current tracksession to clear the fids for.
 *
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_clear_fids(mme_hdl_t *hdl, uint64_t trksessionid);

/**
 * This function is used to append fids to the fids already in a track
 * session that is used for fidlist playback.
 *
 * It can be used under the following conditions:
 * 1/ The track session has had its fidlist set or cleared with
 * mme_trksession_set_fids() or mme_trksession_clear_fids().
 * 2/ The track session is not in repeat or random mode.
 *
 * A MME_EVENT_TRKSESSIONVIEW_UPDATE event is emitted if the fids are
 * successfully added to the track session to indicate that it has
 * changed. 
 *  
 * @param hdl      Handle to the MME.
 * @param nfids    Number of fids to append.
 * @param fids     Array of fids to be played.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_trksession_append_fids(mme_hdl_t *hdl, uint64_t trksessionid, int nfids, uint64_t *fids);

/**
 * Enable or disable prequeueing for connected controlcontext.
 * 
 * @param hdl      Handle to the MME.
 * @param enabled  true to enable; false to disable.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_prequeueing_set(mme_hdl_t *hdl, bool enabled);

/**
 * Get current prequeueing setting from connected controlcontext.
 * 
 * @param hdl      Handle to the MME.
 * @return 1 if enabled.
 * @return 0 if disabled.
 * @return -1 on failure (errno is set).
 */
int mme_prequeueing_get(mme_hdl_t *hdl);

/**
 * Enable or disable resumable bookmarks for connected controlcontext.
 * 
 * @param hdl        Handle to the MME.
 * @param resumable  true to enable; false to disable.
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int mme_bookmark_resume_set(mme_hdl_t *hdl, bool resumable);

/**
 * Get current setting for resumable bookmarks from connected controlcontext.
 * 
 * @param hdl      Handle to the MME.
 * @return 1 if enabled.
 * @return 0 if disabled.
 * @return -1 on failure (errno is set).
 */
int mme_bookmark_resume_get(mme_hdl_t *hdl);

/**
 * Prune an inactive mediastore from MME's database.
 *
 * @param hdl      Handle to the MME.
 * @param msid     Mediastore to prune.
 * @param flags    MME_PRUNE_FLAG_* flags, defined in <mme/interface.h>.
 * @return 0 if request is successful.
 * @return -1 on failure (errno is set).
 */
int mme_prune_inactive(mme_hdl_t *hdl, uint64_t msid, uint32_t flags);

__END_DECLS

#endif /* _MME_MME_H_INCLUDED */

/* __SRCVERSION("mme.h $Rev: 637877 $"); */
