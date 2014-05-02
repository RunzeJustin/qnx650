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


#if !defined(MM_RENDERER_PLAYLIST_H_INCLUDED)
#define MM_RENDERER_PLAYLIST_H_INCLUDED

/** @file playlist.h
 *  Engine plugin API -- playlist engines
 *  @ingroup engineAPI Engine plugin API
 */

#if !defined(MM_RENDERER_ENGINE_H_INCLUDED)
#include <mm/renderer/engine.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup engineAPI Engine plugin API
 */
/*@{*/

/**
 *  @brief Extra calls for playlist engines.
 */
typedef struct mmr_engine_playlist_calls {
	/**
	 *  Change playlist
	 *  Before returning success,
	 *  this call must use mmr_playlist_queue_move()
	 *  to trim any entries that become invalid and renumber the rest.
	 *  @param handle The engine instance handle
	 *  @param url The URL of a new playlist
	 *  @param delta The difference between the position of the current track on the two lists
	 */
	void (*newlist)( mmr_engine_handle_t *handle, const char *url, int delta );
	/**
	 *  Set track parameters.
	 *  @param handle The engine instance handle
	 *  @param index Zero to set the default track parameters, otherwise an index within the playlist window
	 *  @param parms A handle for the new parameters (call must consume, even on error)
	 */
	void (*trkparams)( mmr_engine_handle_t *handle, unsigned index, strm_dict_t *parm );
} mmr_engine_playlist_calls_t;

/**
 *  @brief Enter playlist mode.
 *  @details Enter playlist mode.
 *  This function must be called by an engine's create() or newlist() function.
 *  @param ctxt The context handle
 *  @param vtab 
 *  @param len
 *  @param ei The error information
 *  @return NULL on success, ei on error
 */
mmr_error_info_t *mmr_playlist_set( mmr_ctxt_t *ctxt, const mmr_engine_playlist_calls_t *vtab, unsigned len, mmr_error_info_t *ei );

/**
 *  @brief Update the playlist position.
 *  @details Update the playlist position.
 *  A playlist engine must use this function instead of mmr_engine_update_status().
 *  Setting index to zero or morestatus to NULL means "don't change".
 *  @param ctxt The context handle
 *  @param index
 *  @param mspos
 *  @param morestatus
 *  @param len
 */
void mmr_playlist_update_status( mmr_ctxt_t *ctxt,
	unsigned index, uint64_t mspos, strm_dict_t *morestatus, unsigned len );

/**
 *  @brief Add an item to the playlist window.
 *  @details Add an item to the playlist window.
 *  The metadata and trkparam handles are consumed on success.
 *  @param ctxt The context handle
 *  @param index The index of the new item 
 *  @param url The URL of the track
 *  @param metadata Metadata, or NULL if no metadata available
 *  @param trkparam Track parameters, or NULL for empty parameters
 *  @param ei A pointer to a buffer for error information
 *  @return NULL on success, ei on error
 */
mmr_error_info_t *mmr_playlist_queue_add( mmr_ctxt_t *ctxt, unsigned index,
	const char *url, strm_dict_t *metadata, strm_dict_t *trkparm, mmr_error_info_t *ei );

/**
 *  @brief Update track metadata.
 *  @details Update the metadata of an item in the playlist window.
 *  The metadata handle is consumed on success.
 *  @param ctxt The context handle
 *  @param index The index of the item to update
 *  @param metadata The new metadata
 *  @param ei A pointer to a buffer for error information
 *  @return NULL on success, ei on error
 */
mmr_error_info_t *mmr_playlist_queue_update( mmr_ctxt_t *ctxt, unsigned index, strm_dict_t *metadata, mmr_error_info_t *ei );

/**
 *  @brief Update track parameters.
 *  @details Update the track parameters for an item in the playlist window.
 *  The handle is consumed on success or error
 *  @param ctxt The context handle
 *  @param index The index of the item to update
 *  @param metadata The new track parameters
 *  @param ei A pointer to a buffer for error information
 *  @return NULL on success, ei on error
 */
mmr_error_info_t *mmr_playlist_track_param( mmr_ctxt_t *ctxt, unsigned index, strm_dict_t *parm, mmr_error_info_t *ei );

/**
 *  @brief Trim and move the playlist window.
 *  @details Trim and move the playlist window.
 *  @param ctxt The context handle
 *  @param bot The number of items to remove from the bottom end of the window
 *  @param top The number of items to remove from the top end of the window
 *  @param delta The value to be added to the indexes of any remaining items 
 */
void mmr_playlist_queue_move( mmr_ctxt_t *ctxt, unsigned bot, unsigned top, int delta );

/**
 *  @brief Remove items from the playlist window.
 *  @details Remove items from the playlist window.
 *  Equivalent to mmr_playlist_queue_move() with a delta of zero.
 *  @param ctxt The context handle
 *  @param bot The number of items to remove from the bottom end of the window
 *  @param top The number of items to remove from the top end of the window
 */
void mmr_playlist_queue_delete( mmr_ctxt_t *ctxt, unsigned bot, unsigned top );


/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/playlist.h $ $Rev: 680336 $")
#endif
