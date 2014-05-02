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


#ifndef _MMSYNC_INTERFACE_H_INCLUDED
#define _MMSYNC_INTERFACE_H_INCLUDED


/**
 * Media file categories supported by mm-sync. 
 */
typedef enum mm_ftypes_e {
	FTYPE_UNKNOWN = 0,		///< Unknown media file category
	FTYPE_AUDIO = 1,		///< Audio file
	FTYPE_VIDEO = 2,		///< Video file
	FTYPE_RESERVED1 = 3,    ///< Reserved for future usage
	FTYPE_PHOTO = 4,        ///< Photo file
	FTYPE_DEVICE = 5,       ///< POSIX filesystem device
	FTYPE_MAX               ///< End-of-list identifier 
} mm_ftypes_t;
	
#define MMSYNC_FORMAT_UNKNOWN          (0ULL)  ///< Unknown file format
#define MMSYNC_FORMAT_MLP              (1ULL)  ///< Meridian Lossless Packing (Packed PCM)
#define MMSYNC_FORMAT_PCM              (2ULL)  ///< LPCM and PCM
#define MMSYNC_FORMAT_AC3              (3ULL)  ///< Audio Codec 3 (Dolby Digital)
#define MMSYNC_FORMAT_MP2              (4ULL)  ///< MPEG1 Layer II 
#define MMSYNC_FORMAT_MPEG1_L2         (4ULL)  ///< MPEG1 Layer II 
#define MMSYNC_FORMAT_DTS              (5ULL)  ///< DTS encoded audio file
#define MMSYNC_FORMAT_SDDS             (6ULL)  ///< Sony Dynamic Digital Sound
#define MMSYNC_FORMAT_MPEG1_L1         (7ULL)  ///< MPEG1 Layer I 
#define MMSYNC_FORMAT_MPEG1_L3         (8ULL)  ///< MPEG1 Layer III 
#define MMSYNC_FORMAT_MPEG2_L1         (9ULL)  ///< MPEG2 Layer I
#define MMSYNC_FORMAT_MPEG2_L2         (10ULL)  ///< MPEG2 Layer II
#define MMSYNC_FORMAT_MPEG2_L3         (11ULL)  ///< MPEG3 Layer III
#define MMSYNC_FORMAT_MPEG2_PRO        (12ULL)  ///< ???
#define MMSYNC_FORMAT_OGG              (13ULL)  ///< Ogg container format
#define MMSYNC_FORMAT_AAC              (14ULL)  ///< Advanced Audio Coding
#define MMSYNC_FORMAT_AMR              (15ULL)  ///< Adaptive Multi-Rate
#define MMSYNC_FORMAT_PCM_PREEMPH      (16ULL)  ///< Raw preemphasised PCM audio
#define MMSYNC_FORMAT_WMA              (17ULL)  ///< Windows Media Audio

/* Synchronization Option Definitions */
#define	MMSYNC_OPTION_PASS_FILES		(0x00000001)	///< Flag for performing files pass of synchronization.
#define	MMSYNC_OPTION_PASS_METADATA	(0x00000002)		///< Flag for performing metadata pass of synchronization.
#define	MMSYNC_OPTION_PASS_PLAYLISTS	(0x00000004)	///< Flag for performing playlist pass of synchronization.
#define	MMSYNC_OPTION_PASS_ALL		(MMSYNC_OPTION_PASS_FILES + \
										 MMSYNC_OPTION_PASS_METADATA + \
										 MMSYNC_OPTION_PASS_PLAYLISTS) ///< Flag for performing all three passes of synchronization.
#define	MMSYNC_OPTION_REPAIR			(0x00000400)	///< Flag for repairing database inconsistencies in folder information (for debugging only).
#define	MMSYNC_OPTION_VERIFY			(0x00000800)	///< Flag for verifying data consistency in folder information in database (for debugging only).
#define	MMSYNC_OPTION_CANCEL_CURRENT	(0x00002000)	///< Flag for cancelling any ongoing synchronization when a new one is started.
#define	MMSYNC_OPTION_RECURSIVE		(0x00004000)		///< Flag for synchronizing contents of sub-folders within folder named in path.
#define	MMSYNC_OPTION_SKIPNONMEDIACHECK	(0x00010000)	///< Flag for skipping check for non-media files; implicitly set by iPod synchronizers.

#define MMSYNC_PLAYLIST_OWNER_MMSYNC          0		///< Indicates mm-sync is playlist owner; this setting enables assignment of ratings to playlist session synchronizers (PLSS)
#define MMSYNC_PLAYLIST_OWNER_DEVICE       1		///< Indicates media device is playlist owner; PLSS ratings can't be assigned in this case
#define MMSYNC_PLAYLIST_OWNER_USER         2		///< Indicates user is playlist owner; PLSS ratings can't be assigned in this case

#define MMSYNC_PLAYLIST_MODE_LIBRARY       0		///< Indicates playlist was defined on device
#define MMSYNC_PLAYLIST_MODE_GENERATED     1		///< Indicates playlist was created by client application

#define MMSYNC_DEBUG_LOG_EMIT_TO_STDERR    (0x01)   ///< Indicates that logs should also be send to stderr output (on top of slog).

#endif /*#ifndef _MMSYNC_INTERFACE_H_INCLUDED */

/* __SRCVERSION("interface.h $Rev: 722124 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/lib/public/mmsync/interface.h $ $Rev: 722124 $")
#endif
