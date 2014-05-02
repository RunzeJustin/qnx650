/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef _IAP2_TYPES_H_INCLUDED
#define _IAP2_TYPES_H_INCLUDED

__BEGIN_DECLS

struct iap2_hdl_s;

/**
 * @brief The iAP2 connection handle type.
 */
typedef struct iap2_hdl_s iap2_hdl_t;

/**
 * @brief The iAP2 EAP connection handle type.
 */
typedef struct iap2ea_hdl_s iap2ea_hdl_t;

// Flags for Track Sync
#define IAP2_MEDIALIB_ITEM_UID                  0x000000001
#define IAP2_MEDIALIB_ITEM_TITLE                0x000000002
#define IAP2_MEDIALIB_ITEM_TYPE                 0x000000004
#define IAP2_MEDIALIB_ITEM_RATING               0x000000008
#define IAP2_MEDIALIB_ITEM_DURATION             0x000000010
#define IAP2_MEDIALIB_ITEM_ALBUM_UID            0x000000020
#define IAP2_MEDIALIB_ITEM_ALBUM                0x000000040
#define IAP2_MEDIALIB_ITEM_ALBUM_TRKNUM         0x000000080
#define IAP2_MEDIALIB_ITEM_ALBUM_DISCNUM        0x000000100
#define IAP2_MEDIALIB_ITEM_ALBUM_DISCCNT        0x000000200
#define IAP2_MEDIALIB_ITEM_ARTIST_UID           0x000000400
#define IAP2_MEDIALIB_ITEM_ARTIST               0x000000800
#define IAP2_MEDIALIB_ITEM_ALBUMARTIST_UID      0x000001000
#define IAP2_MEDIALIB_ITEM_ALBUMARTIST          0x000002000
#define IAP2_MEDIALIB_ITEM_GENRE_UID            0x000004000
#define IAP2_MEDIALIB_ITEM_GENRE                0x000008000
#define IAP2_MEDIALIB_ITEM_COMPOSER_UID         0x000010000
#define IAP2_MEDIALIB_ITEM_COMPOSER             0x000020000
#define IAP2_MEDIALIB_ITEM_COMPILATION          0x000040000

// Flags for Playlist Sync
#define IAP2_MEDIALIB_PLIST_UID                 0x000000001
#define IAP2_MEDIALIB_PLIST_NAME                0x000000002
#define IAP2_MEDIALIB_PLIST_PARENT_UID          0x000000004
#define IAP2_MEDIALIB_PLIST_GENIUS              0x000000008
#define IAP2_MEDIALIB_PLIST_FOLDER              0x000000010
#define IAP2_MEDIALIB_PLIST_CONTENTS            0x000000020

/* Header type for Media Library Downloading */
typedef enum {
	/* No data */
	IAP2_MEDIALIB_NODATA = 0,                   // No data

	/* Simulate a Sync Complete */
	IAP2_MEDIALIB_COMPLETE,                     // No data

	/* Reset the Media Library contents */
	IAP2_MEDIALIB_RESET,                        // No data

	/* Revision Data */
	IAP2_MEDIALIB_REVISION,                     // IAP2_MEDIALIB_REVISION_ID

	/* New MediaItem to add */
	IAP2_MEDIALIB_ITEM_ADD,                     // IAP2_MEDIALIB_ITEM_ADD_*

	/* MediaItem to delete */
	IAP2_MEDIALIB_ITEM_DEL,                     // IAP2_MEDIALIB_ITEM_DEL_*

	/* New MediaPlaylist to add */
	IAP2_MEDIALIB_PLIST_ADD,                    // IAP2_MEDIALIB_PLIST_ADD_*

	/* MediaPlaylist to delete */
	IAP2_MEDIALIB_PLIST_DEL,                    // IAP2_MEDIALIB_PLIST_DEL_*

	/* MediaPlaylist content */
	IAP2_MEDIALIB_PLIST_CONTENT,                // IAP2_MEDIALIB_PLIST_CONTENT_*

	/* MediaPlaylist content end */	
	IAP2_MEDIALIB_PLIST_CONTENTEND              // IAP2_MEDIALIB_PLIST_CONTENTEND_*
} iap2_medialib_sync_info_e;

/* Data for IAP2_MEDIALIB_REVISION type */
enum {
	/* Returns the Revision ID */
	IAP2_MEDIALIB_REVISION_ID = 0
};

/* Data for IAP2_MEDIALIB_ITEM_ADD type */
enum {
	/* Returns the MediaItem UID */
	IAP2_MEDIALIB_ITEM_ADD_UID = 0,
	/* Returns the MediaItem Title */
	IAP2_MEDIALIB_ITEM_ADD_TITLE,
	/* Returns the MediaItem Type Music*/
	IAP2_MEDIALIB_ITEM_ADD_TYPE,
	/* Returns the MediaItem Rating */
	IAP2_MEDIALIB_ITEM_ADD_RATING,
	/* Returns the MediaItem Duration (ms) */
	IAP2_MEDIALIB_ITEM_ADD_DURATION,
	/* Returns the MediaItem Album UID */
	IAP2_MEDIALIB_ITEM_ADD_ALBUM_UID,
	/* Returns the MediaItem Album */
	IAP2_MEDIALIB_ITEM_ADD_ALBUM,
	/* Returns the MediaItem Album Track number */
	IAP2_MEDIALIB_ITEM_ADD_ALBUM_TRKNUM,
	/* Returns the MediaItem Album Disc number */
	IAP2_MEDIALIB_ITEM_ADD_ALBUM_DISCNUM,
	/* Returns the MediaItem Album Total Disc count */
	IAP2_MEDIALIB_ITEM_ADD_ALBUM_DISCCNT,
	/* Returns the MediaItem Artist UID */
	IAP2_MEDIALIB_ITEM_ADD_ARTIST_UID,
	/* Returns the MediaItem Artist */
	IAP2_MEDIALIB_ITEM_ADD_ARTIST,
	/* Returns the MediaItem AlbumArtist UID */
	IAP2_MEDIALIB_ITEM_ADD_ALBUMARTIST_UID,
	/* Returns the MediaItem AlbumArtist */
	IAP2_MEDIALIB_ITEM_ADD_ALBUMARTIST,
	/* Returns the MediaItem Genre UID */
	IAP2_MEDIALIB_ITEM_ADD_GENRE_UID,
	/* Returns the MediaItem Genre */
	IAP2_MEDIALIB_ITEM_ADD_GENRE,
	/* Returns the MediaItem Composer UID */
	IAP2_MEDIALIB_ITEM_ADD_COMPOSER_UID,
	/* Returns the MediaItem Composer */
	IAP2_MEDIALIB_ITEM_ADD_COMPOSER,
	/* Returns the MediaItem if part of a compilation (true, false) */
	IAP2_MEDIALIB_ITEM_ADD_COMPILATION
};

/* Data for IAP2_MEDIALIB_PLIST_ADD type */
enum {
	/* Returns the Playlist UID */
	IAP2_MEDIALIB_PLIST_ADD_UID = 0,
	/* Returns the Playlist name */
	IAP2_MEDIALIB_PLIST_ADD_NAME,
	/* Returns the Parent UID of this playlist */
	IAP2_MEDIALIB_PLIST_ADD_PARENT_UID,
	/* Returns if this is a Genius playlist */
	IAP2_MEDIALIB_PLIST_ADD_GENIUS,
	/* Returns if this is a folder */
	IAP2_MEDIALIB_PLIST_ADD_FOLDER
};

/* Data for IAP2_MEDIALIB_ITEM_DEL_UID type */
enum {
	/* Returns the Item UID to be deleted */
	IAP2_MEDIALIB_ITEM_DEL_UID = 0
};

/* Data for IAP2_MEDIALIB_PLIST_DEL_UID type */
enum {
	/* Returns the Playlist UID deleted */
	IAP2_MEDIALIB_PLIST_DEL_UID = 0
};

/* Data for IAP2_MEDIALIB_PLIST_CONTENT type */
enum {
	/* Returns the Playlist UID */
	IAP2_MEDIALIB_PLIST_CONTENT_PLISTUID = 0,
	/* Returns a Item UID as part of this playlist */
	IAP2_MEDIALIB_PLIST_CONTENT_ITEMUID
};

/* Data for IAP2_MEDIALIB_PLIST_CONTENTEND type */
enum {
	/* Returns the Playlist UID */
	IAP2_MEDIALIB_PLIST_CONTENTEND_PLISTUID = 0
};

typedef enum {
	IAP2_MEDIALIB_INFO_TYPE_LOCAL = 0,
} iap2_medialib_type_e;

typedef struct iap2_medialib_info_s {
	const char              *name;              // Name of Media Library
	const char              *uid;               // UID of Media Library
	iap2_medialib_type_e    type;               // Type of Media Library
} iap2_medialib_info_t;

#define IAP2_VEHICLE_KEY_NIGHT			"night"
#define IAP2_VEHICLE_KEY_RANGE			"range"
#define IAP2_VEHICLE_KEY_OUTSIDETEMP	"outsidetemp"
#define IAP2_VEHICLE_KEY_INSIDETEMP		"insidetemp"
#define IAP2_VEHICLE_KEY_RANGEWARN		"rangewarn"

__END_DECLS

#endif /* _IAP2_TYPES_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product_with_ipod/mainline/services/mm-ipod/ipod-drvr/iap2/clientlib/public/iap2/iap2_types.h $ $Rev: 299766 $")
#endif

