/*
 * $QNXLicenseC:
 * Copyright 2011, QNX Software Systems. All Rights Reserved.
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


#ifndef _MMSYNCCLIENT_H_INCLUDED
#define _MMSYNCCLIENT_H_INCLUDED

#include <stddef.h>
#include <mmsync/event.h>
#include <mmsync/types.h>
#include <sys/siginfo.h>
#include <sys/strm.h>

#define MM_SYNC_SUSPEND_FLAGS_WAIT	0x00000001

__BEGIN_DECLS

/**
 * @brief Connect to mm-sync and obtain a handle.
 *
 * @param filename	The path to the mm-sync device name
 * @param flags		Must be set to 0; reserved for future use
 * @return An mmsync connection handle on success, NULL on failure
 */
mmsync_hdl_t *mm_sync_connect(const char *filename, uint32_t flags);

/**
 * @brief Disconnect from mm-sync.
 *
 * @details Disconnect from mm-sync.
 * After calling disconnect the mmsync connection handle should not be used.
 *
 * @param hdl	The mmsync connection handle
 * @return 0 on success
 *         -1 if any resources could not be fully released
 */
int mm_sync_disconnect(mmsync_hdl_t *hdl);

/**
 * @brief Start a synchronization.
 *
 * @details Start a synchronization of the media content in the specified synchronization 
 * path. This path is relative within the filesystem of the mediastore located at the given 
 * mount path. The media content is synchronized to the database identified by the device path. 
 * mm-sync performs the synchronization in a dedicated thread, so this call returns before the 
 * synchronization begins.
 *
 * @param hdl		The mmsync connection handle
 * @param db		The device path of the database where the content is to be synchronized
 * @param mountpoint	The path to the mountpoint of the mediastore to synchronize
 * @param syncpath	The relative path of the file or folder to synchronize
 * @param options	The synchronization options (MMSYNC_OPTION_*)
 * @param extended_options	A set of key/value pairs with extended synchronization options,
 *               	formatted as a comma-separated list of pairs, as follows:
 *               	key1=value1,key2=value2,key3=value3,...
 *                  This parameter may be NULL.
 *
 * extended_options:	Key			Value		Description
 *			use_synchronizer	mss name	Try to use only the requested synchronizer.
 *											The mm_sync_start() call will fail if the
 *											synchronizer does not support the media.
 *			force_synchronizer  mss name    Force the use of the requested synchronizer.
 *
 * @return > 0 the synchronization operation ID
 *         -1 on failure
 */
int mm_sync_start(mmsync_hdl_t *hdl, const char *db, const char *mountpoint,
                  const char *syncpath, uint32_t options, const strm_dict_t *extended_options);

/**
 * @brief Get the status of all current synchronizations.
 *
 * @details Get the status of all current synchronizations.
 * The application provides a buffer of sizeof(mmsync_status_t) * status_size as
 * the status argument.  status_size is a count of the maximum number of status
 * structures that can be returned, not the size of the status buffer.
 *
 * This function will always return the total number of synchronizations in progress
 * or pending, even if this number is greater than max_num_status.  To get the count of
 * synchronizations provide a max_num_status of 0; the status pointer may be NULL
 * in this case.
 *
 * @param hdl		The mmsync connection handle
 * @param status	A pointer to an array of elements to place statuses; may be NULL
 * @param max_num_status	The maximum number of status elements to retrieve; may be 0
 * @param flags		Must be set to 0; reserved for future use
 * @return >= 0 The number of active synchronizations in progress or pending.
 *              The number may be greater than status_size, but only the minimum
 *              of this return value or status_size elements have status available.
 *         -1 on failure
 */
int mm_sync_status_get(mmsync_hdl_t *hdl, mmsync_status_t *status, size_t max_num_status, uint32_t flags);

/**
 * @brief Get the status of a synchronization, based on the operation ID.
 *
 * @param hdl		The mmsync connection handle
 * @param status	A status element to store the result in
 * @param id		The operation ID of the synchronization whose status is to be retrieved
 * @param flags		Must be set to 0; reserved for future use
 * @return 		>= 0 number of results on success
 *       	       	-1 on failure.
 */
int mm_sync_status_get_byid(mmsync_hdl_t *hdl, mmsync_status_t *status, uint32_t id, uint32_t flags);

/**
 * @brief Get the status of a synchronization, based on the database name.
 *
 * @param hdl		The mmsync connection handle
 * @param status	A status element to store the results in
 * @param dbname	The name of the database whose current synchronization status is to be retrieved
 * @param flags		Must be set to 0; reserved for future use
 * @return 		>= 0 number of results on success
 *       	       	-1 on failure.
 */
int mm_sync_status_get_bydbname(mmsync_hdl_t *hdl, mmsync_status_t *status, const char *dbname, uint32_t flags);

/**
 * @brief Get the name of the database being used in a specific synchronization.
 *
 * @param hdl		The mmsync connection handle
 * @param id		The operation ID of the synchronization whose database's name is to be retrieved
 * @param dbname	A buffer to store the database name
 * @param dbname_sz	The size of the dbname buffer
 * @param flags		Must be set to 0; reserved for future use
 * @return 		>= 0 number of results on success
 *       	       	-1 on failure.
 */
int mm_sync_status_get_dbname(mmsync_hdl_t *hdl, uint32_t id, char *dbname, size_t dbname_sz, uint32_t flags);

/**
 * @brief Suspend a synchronization.
 *
 * @details Suspend a synchronization.
 * A synchronization may be suspended to relieve contention on a device for a
 * temporary purpose, such as accessing a file or starting playback quickly.
 * This differs from cancelling a synchronization, which may be done if that synchronization 
 * is no longer needed or begins to negatively impact performance.  
 *
 * @param hdl	The mmsync connection handle
 * @param op_id	The operation ID of synchronization to suspend
 * @param flags	Use MM_SYNC_SUSPEND_FLAGS_WAIT to block until the synchronization thread 
 *              has been suspended
 * @return 	buffer size required to store full name on success
 *		-1 on failure or not found.
 */
int mm_sync_suspend(mmsync_hdl_t *hdl, unsigned op_id, uint32_t flags);

/**
 * @brief Resume a suspended synchronization.
 *
 * @param hdl	The mmsync connection handle
 * @param op_id	The operation ID of the suspended synchronization to resume
 * @param flags	Must be set to 0; reserved future use
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_resume(mmsync_hdl_t *hdl, unsigned op_id, uint32_t flags);

/**
 * @brief Cancel a synchronization.
 * @details Cancel a synchronization. 
 * A synchronization may be cancelled if a device is no longer of interest, or if playback 
 * is requested from a device that is being synchronized and would experience problems with 
 * simultaneous playback and synchronization activities. 
 *
 * @param hdl	The mmsync connection handle
 * @param op_id	The operation ID of the synchronization to cancel
 * @param flags	Must be set to 0; reserved for future use
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_cancel(mmsync_hdl_t *hdl, unsigned op_id, uint32_t flags);

/**
 * @brief Register and unregister for mmsync event notifications.
 *
 * @param hdl	The mmsync connection handle
 * @param event	The event to deliver when an mmsync event is received;
 *				set to NULL to unregister
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_events_register(mmsync_hdl_t *hdl, struct sigevent *event);

/**
 * @brief Get the next queued mmsync event.
 *
 * @details Get the next queued mmsync event.
 * The event returned is stored in the mmsync_hdl_t and is not to be free()'d by the
 * client.  When mm_sync_events_get() is called on an mmsync_hdl_t object, it invalidates the
 * previous mmsync_event_t returned.  Clients that wish to keep the old event should copy it
 * before calling mm_sync_events_get() a second time.
 *
 * @param hdl		The mmsync connection handle
 * @param mmsync_event	A pointer to the event
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_events_get(mmsync_hdl_t *hdl, mmsync_event_t **mmsync_event);

#define MMSYNC_MAX_VERBOSE  10
#define MMSYNC_MAX_DEBUG    0xff
/**
 * @brief Set the logging verbosity and debugging levels.
 *
 * @param hdl		The mmsync connection handle
 * @param verbose	The new verbosity setting to use
 * @param debug		The set debug flags (MMSYNC_DEBUG_*). This will overwrite
 *                  the previous debug flags setting.
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_debug_set(mmsync_hdl_t *hdl, uint8_t verbose, uint8_t debug);

/**
 * @brief Get the logging verbosity level and debugging flags.
 *
 * @param hdl		The mmsync connection handle
 * @param verbose	The verbosity level
 * @param debug		The debugging flags
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_debug_get(mmsync_hdl_t *hdl, uint8_t *verbose, uint8_t *debug);

/**
 * @brief Send commands to a synchronization in progress.
 *
 * @param hdl		The mmsync connection handle
 * @param op_id		The operation ID of the synchronization being controlled
 * @param extended_options	A set of key/value pairs with synchronization control commands, 
 *               	formatted as a comma-separated list of pairs, as follows:
 *               	key1=value1,key2=value2,key3=value3,...
 *
 * Formatting for pairs:	Key			Description
 * 				action			Used to select the action to perform on the synchronization
 *				folderID		Used for actions requiring a folderID, such as priority_folder_set
 *
 * Accepted actions:		Action			Description
 *				priority_folder_set	Initiates a priority folder synchronization. Requires the 'folderID' key/value pair.
 *
 * @param flags		Must be set to 0; reserved for future use
 * @return 0 on success
 *         -1 on failure
 */
int mm_sync_control(mmsync_hdl_t *hdl, uint32_t op_id, strm_dict_t *extended_options,
                    uint32_t flags);

__END_DECLS

#endif /* _MMSYNCCLIENT_H_INCLUDED */

/* __SRCVERSION("mmsyncclient.h $Rev: 722124 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/mmsyncclient/public/mmsync/mmsyncclient.h $ $Rev: 722124 $")
#endif
