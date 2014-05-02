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


#ifndef _TRKS_H_INCLUDED
#define _TRKS_H_INCLUDED

#ifndef __SIGINFO_H_INCLUDED
#include <sys/siginfo.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

__BEGIN_DECLS

/**
 * Connects to the tracksession manager.
 *
 * @param filename    The full pathname to the tracksession manager device name (eg. "/dev/trkmgr")
 * @param flags       Flags to use (None defined)
 *
 * @return handle on success
 * @return NULL on failure
 */
trks_hdl_t *trks_connect(const char *path, uint32_t flags);


/**
 * Disconnect from the tracksession manager.
 *
 * @param hdl The trkmngr connection handle
 *
 * @return 0 on success
 */
int trks_disconnect(trks_hdl_t *hdl);


/**
 * Create a new track session.
 *
 * @param hdl           The trkmgr connection handle.
 * @param trksessionid  Pointer to store the new trksessionid.
 * @param udata_size    Size of user data 
 *
 * @return 0 on success
 * @return -1 on failure
 */
int trks_session_new(trks_hdl_t *hdl, uint64_t *trksessionid, size_t udata_size);


/*
 * Import tracks from an external source.
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 * @param url           A string that is used to import tracks from
 * @param flags         Flags to use (None defined)
 *
 * url requirements:
 * 1) A prefix 'qdb:/'
 * 2) The path to the database
 * 3) A query that returns at least a column name named "url"
 * 4) A result with column name "userdata" is optional
 * 
 * Example url: "qdb://db/mydbase.db?query=SELECT filename AS url, fid AS userdata FROM files"
 */
int trks_session_import(trks_hdl_t *hdl, uint64_t trksessionid, const char *url, uint32_t flags);


/**
 * Export track session to an external source specified by an url.
 *
 * @param hdl           The track session manager connection handle
 * @param trksessionid  The track session identifier
 * @param url           A string that is used to exort track to
 * @param flags         Flags to use (None defined)
 *
 * url requirement:
 * 1) A prefix 'trkmgr_file:/'
 * 2) The path to a file. For the first iteration of this implementation,
 *    the track manager session will be stored in the binary format.
 *
 * @return 0 on success;
 * @return -1 on error
 */
int trks_session_export(trks_hdl_t *hdl, uint64_t trksessionid,
		const char *url, uint32_t flags);


/**
 * Delete a track session
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 *
 * @return -1 on error with errno set
 */
int trks_session_delete(trks_hdl_t *hdl, uint64_t trksessionid);


/**
 * Shuffle the random tracksession playback order
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 * @param offset        The offset to start the randomizing
 * @param nentries      The number of entries to randomize from offset
 * @param trk           The track to set to the top (only used with TRKS_SHUFFLE_FIRST_TRK_* flags)
 * @param flags         Type of track to move to index 0 of random list
 *
 * @return 0 on success
 * @return -1 on error
 */
int trks_trksession_shuffle(trks_hdl_t *hdl, uint64_t trksessionid, unsigned offset, unsigned nentries, unsigned trk, uint32_t flags);


/**
 * Gets info about the track session - number of tracks in the tracksession
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 * @param total_trk     The total number of tracks in the tracksession
 *
 * @return 0 on success
 * @return -1 on error with errno set
 */
int trks_trksession_get_info(trks_hdl_t *hdl, uint64_t trksessionid, uint32_t *total_trk);


/**
 * Set debug settings
 *
 * @param hdl           The trksession manager connection handle
 * @param verbose       The new verbose setting to use
 * @param debug         The new debug setting to use
 *
 * @return 0 on success
 */
int trks_set_debug(trks_hdl_t *hdl, uint8_t verbose, uint8_t debug);


/*
 * Read data from the tracksession.
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 * @param type          The type of information requested
 *   TRKS_READ_ENTRY_SEQ - Request full url entries & user data from the sequential list
 *   TRKS_READ_ENTRY_RAND - Request full url entries & user data from a randomized list
 *   TRKS_READ_INDEX_SEQ - Request the indexes from the sequential list that correlate to the specfied
 *                         index of the randimized list
 *   TRKS_READ_INDEX_RAND - Request the indexes from the random list that correlate to the specfied
 *                          index of the sequential list
 * @param offset        The 0 based offset to start reading from
 * @param ntracks       The number of tracks to read
 * @param buf           The buffer to store the data in 
 *                      (trksession_entry_t structs will be written here for TRKS_READ_ENTRY_*,
 *                      trksession_index_t structs will be written here for TRKS_READ_INDEX_*)
 * @param buflen        [IN]Pointer to the size of the buffer [OUT] size needed for the amount of entries requestes
 *
 * Note: If shuffle is not called, the sequential order and random order will be equivalent.
 *
 * @return -1 on error
 * @return number of entries read (number of trksession_entry_t copied to buf)
 */
int trks_read(trks_hdl_t *hdl, uint64_t trksessionid, unsigned type, unsigned offset, unsigned ntracks, void *buf, unsigned *buflen);


/**
 * This function is used to add entries to the tracksession.
 *
 * @param hdl           The trksession manager connection handle
 * @param trksessionid  The tracksession id
 * @param offset        Offset into tracksession list to add entries to
 * @param nentries      Number of entries to add
 * @param filename      Array of entry names to be stored
 * @param userdata      Array of userdata associated with the entries
 * @param flags         Type of operation to perform
 *   TRKS_WRITE_ENTRY_DELETE - Delete n tracks from tracki session
 *   TRKS_WRITE_ENTRY_REPLACE - Replace n tracks to track session with new tracks
 *   TRKS_WRITE_ENTRY_INSERT - Insert n tracks to track session
 *   TRKS_WRITE_ENTRY_APPEND - Append n tracks to track session
 *
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int trks_write(trks_hdl_t *hdl, uint64_t trksessionid, unsigned offset, unsigned nentries, const char **filename, uint64_t *userdata, uint32_t flags);


/**
 * This function writes userdata to the entries in the trksession.
 *
 * @param hdl           The trksession manager connection handle.
 * @param trksessionid  The tracksession id.
 * @param offset        Offset into tracksession list
 * @param nentries      Number of entries to add.
 * @param userdata      Array of userdata associated with the entries.
 * @param flags         Flags (for future use)
 *
 * @return 0 on success.
 * @return -1 on failure (errno is set).
 */
int trks_set_userdata(trks_hdl_t *hdl, uint64_t trksessionid, unsigned offset, unsigned nentries, uint64_t *userdata, uint32_t flags);

__END_DECLS

#endif /* _TRKS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-trkmgr/clientlib/public/trkmgr/trks.h $ $Rev: 680334 $")
#endif
