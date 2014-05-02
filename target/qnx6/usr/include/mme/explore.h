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


#ifndef _MME_EXPLORE_H_INCLUDED
#define _MME_EXPLORE_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _MME_TYPES_H_INCLUDED
#include <mme/types.h>
#endif

#ifndef	_MME_METADATA_H_INCLUDED
#include <mme/metadata.h>
#endif

/*
 * This file contains explorer extensions to the MME. 
 *  
 * This is version 2 of the explorer API; all names have been changed... 
 *  
 * Items that may be explored include: 
 *  -regular folders
 *  -playlist folders (normally transparently)
 *  -playlist files (if parsers exist)
 *  
 * The items that are explorable must be on a media store that has plug-ins 
 * provided to allow exploration of the media store's contents. 
 */

__BEGIN_DECLS


/**
 * Definitions of flags defining information about the entity.
 * 
 * Others are to be determined.
 */

/** Indicate item is a folder, as opposed to a file */
#define	MME_EXPLORE_FLAGS_IS_FOLDER				0x00000001

/** Indicate item is a playlist of some sort (folder or file) */
#define	MME_EXPLORE_FLAGS_IS_PLAYLIST			0x00000002

/** Indicate item is a name from a playlist file */
#define	MME_EXPLORE_FLAGS_IS_PLAYLIST_ITEM		0x00000004

/** Indicate item is a resolved filename from a playlist file. This value is
   returned only for items retrieved from playlists when the
   MME_EXPLORE_RESOLVE_PLAYLIST_ITEM is used that were successfully converted
   to a file on the media store. Otherwise, the
   MME_EXPLORE_FLAGS_IS_PLAYLIST_ITEM flag is returned with the item. */
#define	MME_EXPLORE_FLAGS_IS_PLAYLIST_FILENAME	0x00000008

/** Indicate item's filename has been UTF-8 converted */
#define MME_EXPLORE_FLAGS_IS_PLAYLIST_CONV_ENTRY	0x00000010

/** Indicate there is metadata present with the response */
#define	MME_EXPLORE_FLAGS_HAS_METADATA			0x00000100

/** Inbound flag: Tell MME to resolve playlist file entries immediately.
   NOTE: The use of the flag results in much faster resolution of playlist
   contents to playable files. However, the actual playlist entry value is then
   not seen at the API if this approach is taken.
   NOTE: This feature over-rides the MME_EXPLORE_UNCONVERTED_CHAR_ENCODING
   flag. */
#define	MME_EXPLORE_RESOLVE_PLAYLIST_ITEM		0x00010000

/** Inbound flag: Tell MME to treat the filter specification as an include-only
   specifier. This is the default if no flag is specified. */
#define	MME_EXPLORE_FILTER_INCLUDE				0x00000000

/** Inbound flag: Tell MME to treat the filter specification as an exclude
   specifier.*/
#define	MME_EXPLORE_FILTER_EXCLUDE				0x00020000

/** Inbound flag: Tell MME not to perform any character conversion on entries
   before returning them. Normally, the MME attempts to convert the playlist
   file entries to UTF-8. This is useful for seeing what comes out of playlists
   if they don't appear to convert to real files. */
#define MME_EXPLORE_UNCONVERTED_CHAR_ENCODING	0x00040000

/** Inbound flag: Tell MME to return the UTF-8 converted filename even if
   the filename couldn't be resolved.  This does not guarantee that the 
   filename will be UTF-8.  This is used in combination 
   with MME_EXPLORE_RESOLVE_PLAYLIST_ITEM. */
#define MME_EXPLORE_CONVERT_UNRESOLVED_ENTRIES	0x00080000

/**
 * This structure is used to contain information about items found at
 * paths.
 */
typedef struct s_mme_explore_info {
	uint32_t			flags;		/**< MME_EXPLORE_FLAGS_* */
	uint32_t			index;		/**< Index of this entry in parent item. */
	char				*path;		/**< full path to element on media store */
	mme_metadata_hdl_t	*metadata;	/**< pointer to metadata if requested */
} mme_explore_info_t;


/**
 * Explorer session control; used per explored item.
 */
struct s_mme_explore_hdl;
typedef struct s_mme_explore_hdl mme_explore_hdl_t;


/**
 * This function is used to start exploring a folder or playlist file to extract 
 * the contents of that item. 
 *  
 * @param	hdl		handle
 * @param	msid	The ID of the media store to explore.
 * @param	path	The path to the item to explore. Use an empty string to 
 *                  start at the root of the media store.
 * @param	flags	Flags (to be determined)
 * @return	NULL on failure
 * @return	non-NULL on success; a exploration session reference
 */
mme_explore_hdl_t *mme_explore_start(mme_hdl_t *hdl, uint64_t msid,
									 const char *path, uint32_t flags);

/**
 * This function is used to end the exploration of an item on a media store.
 * 
 * @param	x_hdl	Value returned by mme_ms_explore_start()
 * @return	0 on success
 * @return	-1 on failure
 */
int mme_explore_end(mme_explore_hdl_t *x_hdl);

/**
 * This function gets the number of entries in the item being explored. 
 * 
 * @param	x_hdl	Value returned by mme_explore_start()
 * @param	flags	Flags (to be determined)
 * @return	>=0 on success
 * @return	-1 on failure
 */
ssize_t mme_explore_size_get(mme_explore_hdl_t *x_hdl, uint32_t flags);

/**
 * The function is used to position the information extraction location to a 
 * specific place in the current folder. 
 * 
 * It also provides a hint to the MME about how many consecutive items
 * information might be wanted for.
 *  
 * If the item being explored is a playlist file, no metadata will be returned. 
 *  
 * @param	x_hdl	Value returned by mme_explore_start()
 * @param	offset	Offset into folder to get information for.
 * @param	items	Number of items starting at offset information will be wanted for.
 * @param	metadata_types	Optional pointer to string containing a 
 *                          comma-separated list of metadata types to retrieve.
 *                          May be NULL.
 * @param	filter  Regular expression for filtering; may be NULL. 
 * @param	flags	See inbound flags above.
 * @return	0 on success
 * @return	-1 on failure
 */
int	mme_explore_position_set(mme_explore_hdl_t *x_hdl, unsigned offset,
							 unsigned items, const char *metadata_types,
							 const char *filter, uint32_t flags);

/**
 * This function is used to get information about an element in an item being 
 * explored. 
 * 
 * The element the information is for depends on the current position in the 
 * item and the number of times this function has already been called. 
 * 
 * The default initial position in the item is at the first element, but this
 * may be changed by mme_explore_position_set().
 * 
 * The returned structure is valid until the next call to this function or
 * mme_explore_end(), whichever is done first.
 * 
 * @param	x_hdl	Value returned by mme_explore_start()
 * @param	flags	Flags (to be determined)
 * @return	NULL on failure
 * @return	non-NULL on success
 */
const mme_explore_info_t *mme_explore_info_get(mme_explore_hdl_t *x_hdl,
											   uint32_t flags);

/**
 * This function is used to convert playlist file entries (as retrieved when
 * a playlist file is explored) to a filename on the system. 
 *  
 * Note that since this function has no idea of the origin of the entry to be 
 * converted, it always returns a value of 0 for the index member of the 
 * returned structure. 
 *
 * @param hdl   Handle to the MME.
 * @param msid  The msid the file is on.
 * @param entry The playlist file entry retrieved from the explorer. 
 * @param path	The playlist file's path on the media store. 
 * @param metadata_types If desired, the list of metadata types wanted with
 *              the file. NULL, otherwise.
 * @param flags To be determined.
 * @return NULL on failure. The errno values may be used to determine
 *         why the entry could not be resolved. Exact values are to be
 *         determined.
 * @return non-NULL on success; result must be released by
 *         mme_explore_info_free().
 */
const mme_explore_info_t *mme_explore_playlist_find_file(mme_hdl_t *hdl,
														 uint64_t msid,
														 const char *entry,
														 const char *path,
														 const char *metadata_types,
														 uint32_t flags);

/**
 * This function is used to release a mme_explore_info_t structure that was
 * returned by any function not in the context of an explorer session, such as
 * mme_explore_playlist_find_file().
 *
 * @param hdl   Handle to the MME.
 * @param info  Pointer to mme_explore_info_t structure to free.
 * @return 0 on success.
 * @return -1 on error.
 */
int mme_explore_info_free(mme_hdl_t *hdl, const mme_explore_info_t *info);

__END_DECLS

#endif /* _MME_EXPLORE_H_INCLUDED */

/* __SRCVERSION("mme_explore.h $Rev:$"); */

