/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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


#ifndef _MME_PLAYLIST_H_INCLUDED
#define _MME_PLAYLIST_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _MME_TYPES_H_INCLUDED
#include <mme/types.h>
#endif

__BEGIN_DECLS

/**
 * Generates a new playlist similar to an existing fid
 *
 * @param hdl    The MME connection handle
 * @param name   Any textual name to display
 * @param fid    The fid to use as a seed for the new playlist
 * @param msid   The msid also specifies from which mediastore the tracks will
 *               be chosen from, 0 means all active mediastores. If that the
 *               msid is pruned, this playlist is deleted.  Set to 0 to have no
 *               pruning on this playlist.
 * @param max_entries The maximum number of entries in the playlist (there may be less)
 * @param flags  Flags that modify the behaviour. None defined.
 * @param plid   The new playlist ID.
 *
 * @return -1 on error
 */
int mme_playlist_generate_similar(mme_hdl_t *hdl, const char *name, uint64_t fid,
								  uint64_t msid, unsigned max_entries,
								  uint32_t flags, uint64_t *plid);


/**
 * The playlist handle for playlist operations.
 */
struct mme_playlist_hdl;
typedef struct mme_playlist_hdl mme_playlist_hdl_t;


/**
 * Definitions of flags for playlist viewing.
 * 
 * Others are to be determined.
 */

/** Convert entry to a real file before returing it. */
#define	MME_PLAYLIST_RESOLVE_PLAYLIST_ENTRY		0x00000001

/** Item is an unconverted entry from a playlist. */
#define	MME_PLAYLIST_FLAGS_PLAYLIST_ENTRY		0x00000001

/** Item is a playlist entry that's been converted to a real file. */
#define	MME_PLAYLIST_FLAGS_PLAYLIST_FILE		0x00000002

/**
 * This function is used to open a playlist for extracting entries from it.
 * For file-based playlists, this is identical to using the explorer-based
 * API on the file itself.
 *
 * It returns a playlist session handle.
 *
 * Note that an open call will fail for playlists that have no PLSSs able
 * to deal with it. This is likely to include playlists created at the API.
 *
 * @param  mme     MME connection handle.
 * @param  plid    The ID of the playlist to open.
 * @param  flags   Flags controlling operation (tbd).
 * @return NULL on failure
 * @return non-NULL on success
 */
mme_playlist_hdl_t *mme_playlist_open(mme_hdl_t *mme, uint64_t plid,
									  uint32_t flags);

/**
 * This function is used to close an opened playlist.
 *
 * @param  mme     MME connection handle.
 * @param  hdl     The playlist session handle returned by mme_playlist_open().
 * @return 0 on success
 * @return -1 on failure
 */
int mme_playlist_close(mme_playlist_hdl_t *hdl);

/** 
 * This function is used to get the number of items in the playlist.
 * 
 * @param  hdl     The playlist session handle returned by mme_playlist_open(). 
 * @param  items   Place to return the number of items. If this value is -1, it 
 *                 means the playlist is variable or changing in length (has no
 *                 fixed length).
 * @return 0 on success 
 * @return -1 on failure 
 */
int mme_playlist_items_count_get(mme_playlist_hdl_t *hdl, int *items);

/** 
 * This function is used to set the current position in the playlist. 
 *  
 * If the requested position exceeds the length of a fixed-length playlist, then 
 * the position is set to the end of the playlist and sn error is returned. 
 * The errno in this case is ENOSPC 
 *  
 * @param  hdl     The playlist session handle returned by mme_playlist_open(). 
 * @param  position   Position to put in the playlist.
 * @return 0 on success 
 * @return -1 on failure; errno is set.
 */
int mme_playlist_position_set(mme_playlist_hdl_t *hdl, unsigned position);

/**
 * This function returns the playlist entry at the specified position
 * and places it in the buffer. Flags (tbd) are used to indicate if
 * the raw playlist entry is used or if is should be converted to 
 * real file name (mountpath of media store is included???).
 *
 * If position is greater than or equal to the number of items in
 * the playlist, then 0 is returned.
 *
 * @param  hdl     The playlist session handle returned by mme_playlist_open().
 * @param  flags   On input, flags controlling operation (none or 
 *                 MME_PLAYLIST_RESOLVE_PLAYLIST_ENTRY).
 *                 On output, flags indicating status of returned entry
 *                 (MME_PLAYLIST_FLAGS_*).
 * @param  buffer  Place to put result; may be NULL
 * @param  length  Length of buffer (may be 0)
 * @param  >0 length of result (even if buffer too short)
 * @return 0 on success but end of playlist reached
 * @return -1 on failure
 */
int mme_playlist_item_get(mme_playlist_hdl_t *hdl, uint32_t *flags,
						  char *buffer, size_t length);


__END_DECLS

#endif /* _MME_PLAYLIST_H_INCLUDED */

/* __SRCVERSION("playlist.h $Rev:$"); */

