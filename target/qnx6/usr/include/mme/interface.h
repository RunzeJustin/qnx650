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


#ifndef _MME_INTERFACE_H_INCLUDED
#define _MME_INTERFACE_H_INCLUDED

/* Define storage types */
#define MME_STORAGETYPE_UNKNOWN    (0)
#define MME_STORAGETYPE_AUDIOCD    (1)
#define MME_STORAGETYPE_FS         (2)
#define MME_STORAGETYPE_DEVB       MME_STORAGETYPE_FS
#define MME_STORAGETYPE_DVDAUDIO   (3)
#define MME_STORAGETYPE_VCD        (4)
#define MME_STORAGETYPE_SVCD       (5)
#define MME_STORAGETYPE_DVDVIDEO   (6)
#define MME_STORAGETYPE_IPOD       (8)
#define MME_STORAGETYPE_KODAKCD    (9)
#define MME_STORAGETYPE_PICTURECD  (10)
#define MME_STORAGETYPE_A2DP       (12)
#define MME_STORAGETYPE_RESERVED0  (13)	/* UPNP placeholder, moved to mediafs */
#define MME_STORAGETYPE_SMB        MME_STORAGETYPE_FS
#define MME_STORAGETYPE_FTP        (15)
#define MME_STORAGETYPE_HTTP       (16)
#define MME_STORAGETYPE_NAVIGATION (17)
#define MME_STORAGETYPE_UPGRADE    (18)
#define MME_STORAGETYPE_PLAYSFORSURE   (20)
#define MME_STORAGETYPE_UPNP           (21)
#define MME_STORAGETYPE_INTERNETSTREAM (22)
#define MME_STORAGETYPE_SND_INPUT      (23)
#define MME_STORAGETYPE_DMB        (24)
#define MME_STORAGETYPE_MIRRORLINK (26)

/* User defined storage types */
#define MME_STORAGETYPE_CUSTOM_FIRST (100)
#define MME_STORAGETYPE_CUSTOM1    (100) 
#define MME_STORAGETYPE_CUSTOM2    (101)
#define MME_STORAGETYPE_CUSTOM3    (102)
#define MME_STORAGETYPE_CUSTOM4    (103)
#define MME_STORAGETYPE_CUSTOM5    (104)
#define MME_STORAGETYPE_CUSTOM6    (105)
#define MME_STORAGETYPE_CUSTOM7    (106)
#define MME_STORAGETYPE_CUSTOM8    (107)
#define MME_STORAGETYPE_CUSTOM9    (108)
#define MME_STORAGETYPE_CUSTOM10   (110)
#define MME_STORAGETYPE_CUSTOM_LAST (199)


/* Define slot types */
#define MME_SLOTTYPE_UNKNOWN       (0)
#define MME_SLOTTYPE_USB           (1)
#define MME_SLOTTYPE_CD            (2)  /* Internal CD/DVD drive */
#define MME_SLOTTYPE_DRIVE         (3)
#define MME_SLOTTYPE_MEDIAFS       (4)
#define MME_SLOTTYPE_CD_EXT        (5)  /* External CD/DVD drive */
#define MME_SLOTTYPE_CD_CHGR_INT   (6)  /* Internal CD/DVD changer */
#define MME_SLOTTYPE_CD_CHGR_EXT   (7)  /* External CD/DVD changer */
#define MME_SLOTTYPE_FILESYSTEM    (8)  /* Generic POSIX filesystem type */
#define MME_SLOTTYPE_BLUETOOTH     (9)  /* Bluetooth stack */
#define MME_SLOTTYPE_INTERNET      (10) /* Internet */
#define MME_SLOTTYPE_SND_INPUT     (11) /* Audio input from snd sources */
#define MME_SLOTTYPE_DMB           (12) /* DMB Digital Multimedia Broadcasting */


#define MME_SLOTTYPE_CUSTOM_FIRST  (100)
#define MME_SLOTTYPE_CUSTOM_LAST   (199)

/* Macro to determine of the slottype is any of the different CD types */
#define check_slottype_cd(slottype) \
  ((slottype == MME_SLOTTYPE_CD || slottype == MME_SLOTTYPE_CD_EXT || \
	slottype == MME_SLOTTYPE_CD_CHGR_INT || slottype == MME_SLOTTYPE_CD_CHGR_EXT))
/* Macro to determine of the slottype an internal CD */
#define check_slottype_cd_int(slottype) \
  ((slottype == MME_SLOTTYPE_CD || slottype == MME_SLOTTYPE_CD_CHGR_INT))
/* Macro to determine of the slottype an external CD */
#define check_slottype_cd_ext(slottype) \
  ((slottype == MME_SLOTTYPE_CD_EXT || slottype == MME_SLOTTYPE_CD_CHGR_EXT))

/* Media Types */
#define FTYPE_UNKNOWN               (0)
#define FTYPE_AUDIO                 (1)
#define FTYPE_VIDEO                 (2)
#define FTYPE_AUDIOVIDEO            (3)
#define FTYPE_PHOTO                 (4)
#define	FTYPE_DEVICE                (5)

/* Mediastore Capabilities */
#define _MME_MSCAP_MSS_MASK               (0xFFFFFFFF)
#define MME_MSCAP_SET                     (0x80000000) /*  capabilities have been set (make non-zero) */
#define MME_MSCAP_SYNC                    (0x00000001) /*  Mediastore sync possible */
#define MME_MSCAP_PRUNABLE                (0x00000002) /*  Indicates that sync should do pruning */
#define MME_MSCAP_SYNC_DIRECTED           (0x00000004) /*  Indicates that directed sync is supported */
#define MME_MSCAP_NO_AUTO_SYNC            (0x00000008) /*  Indicates never automatically synced */
#define MME_MSCAP_PRIO_FOLDER             (0x00000010) /*  Indicates can prioritize folders in sync */
#define MME_MSCAP_MEDIAFS_1WIRE           (0x00000020) /*  supports mediafs 1wire protocol */
#define MME_MSCAP_MEDIAFS_2WIRE           (0x00000040) /*  supports mediafs 2wire protocol */
#define MME_MSCAP_DEVICE_TRACKSESSIONS    (0x00000080) /*  device will manage it's own track sessions */
#define MME_MSCAP_NOWPLAYING_METADATA     (0x00000100) /*  metadata for the nowplaying track can be retrieved from the device */
#define MME_MSCAP_NOWPLAYING_FILENAME     (0x00000200) /*  the current playing file can be retrieved from the device */
#define MME_MSCAP_DEVICE_SAVES_STATE      (0x00000400) /*  device can save its own state, used for resuming msid */
#define MME_MSCAP_DEVICE_REPEATRANDOM     (0x00000800) /*  device supports repeat and random modes */
#define MME_MSCAP_DELETE_ON_EJECT         (0x00001000) /* Indicates that the system should delete it
														  from the database when it's ejected. */
#define MME_MSCAP_PLAY_FILE               (0x00002000) /*  The device supports the mme_play_file API */
#define	MME_MSCAP_EXPLORABLE              (0x00004000) /*  The device supports the explore API. */
#define	MME_MSCAP_TRKSESSIONVIEW_METADATA (0x00008000) /*  Supports the trksessionview metadata API. */
#define	MME_MSCAP_TRACK_POSITION_COOKIE_BASED (0x00010000) /*  Supports the trksession save state. */
#define MME_MSCAP_SUPPORTS_VIDEO          (0x00020000) /*  Supports video playback */
#define MME_MSCAP_CONNECTION_NONOPTIMAL   (0x00040000) /*  Non optimal link to device (ex: iPod using serial, but supports USB) */
#define MME_MSCAP_AUDIO_NONOPTIMAL        (0x00080000) /*  Non optimal audio link (ex: iPod using ditial, but using analog) */
#define MME_MSCAP_MEDIAFS_ALBART          (0x00100000) /*  is a mediafs device supporting DCMD_MEDIA_ALBART devctls for any file (Zune, not iPod) */
#define MME_MSCAP_FORCE_TRKSESSION        (0x00200000) /*  Device normally manages it's own track sessions, but MME can override */

/* Definitions for track session creation */
#define MME_PLAYMODE_LIBRARY        (0x0)
#define MME_PLAYMODE_FILE           (0x2)

#define MME_FORMAT_UNKNOWN          (0ULL)
#define MME_FORMAT_MLP              (1ULL)
#define MME_FORMAT_PCM              (2ULL)  /* LPCM and PCM */
#define MME_FORMAT_AC3              (3ULL)
#define MME_FORMAT_MP2              (4ULL)  /* MPEG1 Layer II */
#define MME_FORMAT_MPEG1_L2         (4ULL)  /* MPEG1 Layer II */
#define MME_FORMAT_DTS              (5ULL)
#define MME_FORMAT_SDDS             (6ULL)
#define MME_FORMAT_MPEG1_L1         (7ULL)  /* MPEG1 Layer I */
#define MME_FORMAT_MPEG1_L3         (8ULL)  /* MPEG1 Layer III */
#define MME_FORMAT_MPEG2_L1         (9ULL)
#define MME_FORMAT_MPEG2_L2         (10ULL)
#define MME_FORMAT_MPEG2_L3         (11ULL)
#define MME_FORMAT_MPEG2_PRO        (12ULL)
#define MME_FORMAT_OGG              (13ULL)
#define MME_FORMAT_AAC              (14ULL)
#define MME_FORMAT_AMR              (15ULL)
#define MME_FORMAT_PCM_PREEMPH      (16ULL)  /* raw preemphasised pcm audio */
#define MME_FORMAT_WMA              (17ULL)

/* Synchronization Option Definitions */
#define	MME_SYNC_OPTION_PASS_FILES		(0x00000001)
#define	MME_SYNC_OPTION_PASS_METADATA	(0x00000002)
#define	MME_SYNC_OPTION_PASS_PLAYLISTS	(0x00000004)
#define	MME_SYNC_OPTION_PASS_EXT_DB_SYNC (0x00000008)
#define	MME_SYNC_OPTION_PASS_ALL		(MME_SYNC_OPTION_PASS_FILES + \
										 MME_SYNC_OPTION_PASS_METADATA + \
										 MME_SYNC_OPTION_PASS_PLAYLISTS + \
										 MME_SYNC_OPTION_PASS_EXT_DB_SYNC)
#define	MME_SYNC_OPTION_REPAIR			(0x00000400)
#define	MME_SYNC_OPTION_VERIFY			(0x00000800)
#define	MME_SYNC_OPTION_CLR_INV_COPIED	(0x00001000)
#define	MME_SYNC_OPTION_CANCEL_CURRENT	(0x00002000)
#define	MME_SYNC_OPTION_RECURSIVE		(0x00004000)
#define	MME_SYNC_OPTION_BLOCKING		(0x00008000)	/* not used */
#define	MME_SYNC_OPTION_SKIPNONMEDIACHECK	(0x00010000)
#define MME_SYNC_OPTION_DB_RESYNC	(0x00020000)

#define MME_PLAYLIST_OWNER_MME          0
#define MME_PLAYLIST_OWNER_DEVICE       1
#define MME_PLAYLIST_OWNER_USER         2

#define MME_PLAYLIST_MODE_LIBRARY       0
#define MME_PLAYLIST_MODE_GENERATED     1

/* Database Deletion Flag Definitions */
#define	MME_DB_DELETION_IGNORE_PERMANENT	(0x0001)

/* mme_trksessionview_metadata_get() flags */
#define	MME_TRKSESSIONVIEW_METADATA_NOWPLAYING	(0x00000001)	/* get metadata from playing graph */

/* mme_play_offset() flags */
#define MME_PLAY_OFFSET_MMETRACKSESSION		(0x00000001)	/* use the MME's tracksession over a device's */

/* mme_repeat_set() flags */
#define MME_REPEATFLAG_MMETRACKSESSION		(0x00000001)	/* set the MME tracksession repeat mode over a device's */

/* mme_random_set() flags */
#define MME_RANDOMFLAG_MMETRACKSESSION		(0x00000001)	/* set the MME tracksession random mode over a device's */

/* mme_bookmark_update() flags */
#define MME_BOOKMARKUPDATE_FINDFIRSTOFTYPE	(0x00000001)	/* search for an existing bookmark for given type and update rather than create */

/* folders table folderflags flags */
#define MME_FOLDERFLAGS_NONMEDIALIMIT		(0x00010000)	/* This folder hit the non-media limit. */
#define MME_FOLDERFLAGS_SKIPNONMEDIACHECK	(0x00000001)	/* This folder was synced with MME_SYNC_OPTION_SKIPNONMEDIACHECK . */

/* mme_prune_inactive() flags */
#define MME_PRUNE_FLAG_BACKGROUND		(0x00000000)	/* prune at background priority */
#define MME_PRUNE_FLAG_FOREGROUND		(0x00000001)	/* prune at calling thread's priority */
#define MME_PRUNE_FLAG_BLOCKING			(0x00000002)	/* do not return until prune is complete; must be combined with MME_PRUNE_FLAG_FOREGROUND */
#define MME_PRUNE_FLAG_ALLMEDIASTORES		(0x00000004)	/* prune all inactive mediastores */
#define MME_PRUNE_FLAG_PRUNEPERMANENT		(0x00000008)	/* force the prune of mediastores containing library entries marked as permanent */

#endif /*#ifndef _MME_INTERFACE_H_INCLUDED */

/* __SRCVERSION("interface.h $Rev: 702196 $"); */
