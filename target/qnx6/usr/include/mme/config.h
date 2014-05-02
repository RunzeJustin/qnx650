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


#ifndef _MME_CONFIG_H_INCLUDED
#define _MME_CONFIG_H_INCLUDED

/**
 * The default mountpath to the MME's resource manager API. 
 * All control contexts are created under this path. 
 */
#define CONFIG_DEFAULT_DEVICE_PATH      "/dev/mme"

/** Verbosity level of configuration initialization */
#define	CONFIG_DEF_CONFIG_VERBOSITY_LEVEL	2


#define CONFIG_DEFAULT_SYNC_BUFFER  (250)
#define CONFIG_DEFAULT_SYNC_MAX_RECURSE (8)
#define	CONFIG_DEFAULT_SYNC_THREADS_MAX (8)

#define CONFIG_DEF_CONSECUTIVE_PLAY_ERRORS_BEFORE_STOP   (5)

#define CONFIG_NTFY_QUEUE_MAX (80)
#define CONFIG_DEFAULT_NOTIFY_INTERVAL_MS  (100)

#define CONFIG_MAX_PATH      4000
#define CONFIG_MAX_SQL       8000
#define CONFIG_MAX_EXTENSION_LENGTH (30)
#define CONFIG_MAX_EXTENSIONS 200

#define CONFIG_MAX_MS_NAME_LEN   (128)

/*  Metadata maximums are in multibyte characters */
#define CONFIG_UTF8_CHAR_SIZE        (4)
#define CONFIG_MAX_TITLE_CHARS       (256)
#define CONFIG_MAX_ARTIST_CHARS      (256)
#define CONFIG_MAX_ALBUM_CHARS       (256)
#define CONFIG_MAX_GENRE_CHARS       (256)
#define CONFIG_MAX_COMPOSER_CHARS    (256)
#define CONFIG_MAX_LANGUAGE_CHARS    (256)
#define CONFIG_MAX_DESCRIPTION_CHARS (256)
#define CONFIG_MAX_CATEGORY_CHARS    (256)
#define CONFIG_MAX_CONDUCTOR_CHARS   (256)
#define CONFIG_MAX_SOLOIST_CHARS     (256)
#define CONFIG_MAX_ENSEMBLE_CHARS    (256)
#define CONFIG_MAX_OPUS_CHARS        (256)
#define CONFIG_MAX_IMAGE_DESC_CHARS  (32)
#define CONFIG_MAX_IMAGE_URL_CHARS   (256)
#define CONFIG_MAX_EXTENDED_CHARS    (256)

#define CONFIG_MAX_TITLE       (CONFIG_MAX_TITLE_CHARS * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_ARTIST      (CONFIG_MAX_ARTIST_CHARS * CONFIG_UTF8_CHAR_SIZE) 
#define CONFIG_MAX_ALBUM       (CONFIG_MAX_ALBUM_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_GENRE       (CONFIG_MAX_GENRE_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_COMPOSER    (CONFIG_MAX_COMPOSER_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_LANGUAGE    (CONFIG_MAX_LANGUAGE_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_DESCRIPTION (CONFIG_MAX_DESCRIPTION_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_CATEGORY    (CONFIG_MAX_CATEGORY_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_CONDUCTOR   (CONFIG_MAX_CONDUCTOR_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_SOLOIST     (CONFIG_MAX_SOLOIST_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_ENSEMBLE    (CONFIG_MAX_ENSEMBLE_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_OPUS        (CONFIG_MAX_OPUS_CHARS  * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_EXTENDED    (CONFIG_MAX_EXTENDED_CHARS  * CONFIG_UTF8_CHAR_SIZE)

#define CONFIG_MAX_UID           (100)
#define CONFIG_MAX_BOOKMARK_NAME_LENGTH (200)
#define CONFIG_MAX_ZONE_NAME_LENGTH (100)

#define CONFIG_MAX_IMAGE_DESC    (CONFIG_MAX_IMAGE_DESC_CHARS * CONFIG_UTF8_CHAR_SIZE)
#define CONFIG_MAX_IMAGE_URL     (CONFIG_MAX_IMAGE_URL_CHARS * CONFIG_UTF8_CHAR_SIZE)

#define CONFIG_MAX_PLAYLIST_BYTES     (500000)    /* half a million bytes */
#define CONFIG_MAX_PLAYLIST_LINES       (5000)
#define CONFIG_MAX_PLAYLIST_LINE_LENGTH (1024)

#define CONFIG_MAX_STORAGETYPE			(10000)
#define CONFIG_MAX_MSSNAME_LENGTH       (20)

#define CONFIG_MAX_ARTWORK_FILE_SPECIFIERS       (32)
#define CONFIG_MAX_ARTWORK_FILE_SPECIFIER_LENGTH (64)
#define CONFIG_MAX_ARTWORK_FILE_EXTENSION_LENGTH (8)

/**
 * The high water mark of the database size.  If the
 * database exceeds this size then the prune managers
 * will attempt to prune the database.
 * If this is set to 0 then this type of prune management
 * is disabled.  Value is in kB.
 */
#define	CONFIG_DEF_MAX_DATABASE_SIZE	0

/**
 * After this many synced files the MME will check to
 * see how big the database is.  The bigger the number
 * the faster the sync, with a low number it is 
 * possible to go over the highsize by a larger amount.
 * If set to 0 then it will not check in the middle of a sync.
 */
#define	CONFIG_DEF_SYNC_INTERVAL		0

/**
 * Default pruning behaviour when media stores are ejected; if enabled, they 
 * still have to be in the "permit" list of pruning based on storage type. 
 */
#define	CONFIG_DEF_PRUNE_ON_EJECTION	false

/**
 * Default synchronization mode is automatic.
 */
#define	CONFIG_DEF_SYNC_AUTOMATIC		true

/**
 * Default synchronization passes (since default is automatic).
 */
#define	CONFIG_DEF_SYNC_OPTIONS			"all,recursive"

/**
 * Default sync threads' priority.
 */
#define	CONFIG_DEF_SYNC_THREAD_PRIORITY			0

/**
 * Default sync merge thread priority adjustement
 */
#define	CONFIG_DEF_MERGE_THREAD_PRIORITY_ADJ		1

/**
 * Default emission control of folder sync events.
 */
#define	CONFIG_DEF_SYNC_FOLDER_EVENTS			false

/**
 * Default unknown titles handling
 */
#define	CONFIG_DEFAULT_UNKNOWN_TITLES_NULL		true

/**
 * Default control for DVD-A device file ID creation.
 */
#define	CONFIG_DEV_DVDA_DEV_FID_CREATION		true

/**
 * Default control for DVD-A IFO parsing.
 */
#define	CONFIG_DEV_DVDA_IFO_PARSING				true

/**
 * Default control for DVD-V device file ID creation.
 */
#define	CONFIG_DEV_DVDV_DEV_FID_CREATION		true

/**
 * Default control for DVD-V IFO parsing.
 */
#define	CONFIG_DEV_DVDV_IFO_PARSING				true

/**
 * Default control for insertion of zero duration entries.
 */
#define	CONFIG_DEF_DVD_SKIP_DURATION_ZERO		true

/**
 * Flag to enable internal CD changer support.
 * Set to 0 to disable, set to 1 to enable.
 */
#define	CONFIG_DEF_DEVS_INT_CHANGER_ENABLED		false

/**
 * Flag to enable external CD changer support.
 * Set to 0 to disable, set to 1 to enable.
 */
#define	CONFIG_DEF_DEVS_EXT_CHANGER_ENABLED		false

/**
 * Set the ripping mode:
 * 0 = Background Ripping (playback has priority)
 * 1 = Priority Background Ripping (ripping has priority)
 */
#define	CONFIG_DEF_COPYING_MODE					0 /* MME_MEDIACOPIER_MODE_BKG */

/**
 * Default destination mediastore for ripping.
 */
#define	CONFIG_DEF_COPYING_DEST_MEDIA_STORE		"/media/drive"

/**
 * Default Encoding Format ID
 */
#define	CONFIG_DEF_COPYING_ENCODEFORMATID		2 /* Default to wav ripping */

/**
 * Default destination folder for ripping
 */
#define	CONFIG_DEF_COPYING_DEST_FOLDER			"/ripped/$ARTIST/$ALBUM/"

/**
 * Default destination file template for ripping (make sure name is unique)
 */
#define	CONFIG_DEF_COPYING_DEST_FILENAME	 	"$0TRACK-$TITLE(date=$DATESTAMP,time=$TIMESTAMP,srcfid=$SRCFID)"	


/**
 * Flag to enable creation of folder paths to the copied file
 * Set to 0 to disable, set to 1 to enable.
 */
#define CONFIG_DEF_COPYING_PRESERVEPATH_ENABLED    false

/**
 * Flag to enable file overwrite if the dest file exist
 * Set to 0 to disable, set to 1 to enable.
 */
#define CONFIG_DEF_COPYING_FILEOVERWRITE_ENABLED    false

/**
 * Values to control when copyqueue table entries are to be automatically deleted
 */
#define CONFIG_DELETE_ON_TYPE_NONE    0 /*  "none" - do not automatically delete copyqueue entries */
#define CONFIG_DELETE_ON_TYPE_ANY     1 /*  "any" - delete copyqueue entry on any error */
#define CONFIG_DELETE_ON_TYPE_NR      2 /*  "nonrecoverable" - delete copyqueue entry on nonrecoverable error */
#define CONFIG_DEF_COPYING_DELETE_ON_TYPE  "none"

/**
 * Flag to enable deleting copyqueue entries on non-recoverable errors
 * Set to 0 to disable, set to 1 to enable.
 */
#define CONFIG_DEF_COPYING_DELETE_ON_NR_ERROR          false
   
/**
 * Flag to enable using the default copying filename template instead of the
 * specifed filename template if the metadata is not accurate.
 * Set to 0 to disable, set to 1 to enable.
 */
#define CONFIG_DEF_COPYING_IGNORE_NONACCURATE_ENABLED     false

/**
 * Flag to enable the second pass syncing of the source fid before
 * copying it
 */
#define CONFIG_DEF_COPYING_UPDATE_METADATA_ENABLED     true

/**
 * The default mediacopier notification interval in milliseconds.
 * This can be changed by calling mme_mediacopier_set_notification_interval().
 */
#define CONFIG_DEF_COPYING_NOTIFICATION_INTERVAL_MS    1000

/**
 * Default behaviour at end of seek;
 * non-zero means to play forward,
 * zero means keep seeking (same direction)
 */
#define	CONFIG_DEF_PLAY_AT_END_OF_SEEK			0

/**
 * Default behaviour for incrementing the played count 
 * value for a track. Acceptable values are "off", "start" and "end". 
 */
#define CONFIG_DEF_PLAYED_COUNT_INC				"end"

/**
 * Default locale string.
 */
#define	CONFIG_DEF_LOCALE						"en"

/**
 * Maximum length of path to the MME's database.
 */
#define	CONFIG_MAX_DATABASE_MOUNTPATH_LEN		256

/**
 * Default path to the MME's database.
 */
#define	CONFIG_DEF_DATABASE_MOUNTPATH			"/dev/qdb/mme"

/**
 * Maximum length of name of MME Database Backup Set.
 */
#define	CONFIG_MAX_DATABASE_SETNAME_LENGTH		32

/**
 * Default database backup set name.
 */
#define	CONFIG_DEF_DATABASE_SETNAME				"mme"

/**
 * Default is to monitor device paths at start.
 */
#define	CONFIG_DEF_DEVICE_DETECTION				true

/**
 * Default path monitor thread's priority.
 */
#define	CONFIG_DEF_DEVICE_MONITOR_PRIORITY		0

/**
 * Default number of maximum control contexts.
 */
#define	CONFIG_DEF_MAX_CONTROLCONTEXTS			10

/**
 * The maximum length of an output device's name
 */
#define CONFIG_MAX_OUTPUTNAME_LENGTH       (1024)

/**
 * The default timeout value for database accesses in milliseconds.
 */
#define CONFIG_DEF_DATABASE_TIMEOUT_MS   (0)

/**
 * The default playview window size.
 */
#define CONFIG_DEF_PLAYVIEW_SIZE         (0)

/**
 * The number of rows to write/delete at once in the trksessionview
 */
#define CONFIG_DEFAULT_TRKSESSIONVIEW_WRITE_SIZE         (1000)

/**
 * On MME_PLAY_ERROR_DEVICEREMOVED events the MME saves the trksession state.
 */
#define	CONFIG_DEF_DEVICE_REMOVAL_SAVES_STATE				true

/**
 *  Default maxium number of threads for the metadata interface server.
 */
#define CONFIG_DEF_JOBENGINE_MAX_THREADS (10)
/**
 *  Default number of threads to allocate when needed.
 */
#define CONFIG_DEF_JOBENGINE_THREAD_INC (2)
/**
 *  Default minimum number of threads to keep blocked waiting for jobs
 */
#define CONFIG_DEF_JOBENGINE_THREAD_LOW_WM (2)
/**
 *  Default maximum number of threads to keep blocked waiting for jobs
 */
#define CONFIG_DEF_JOBENGINE_THREAD_HIGH_WM (5)

/**
 *  Default image cache setting, disabled.
 */
#define CONFIG_DEF_MDI_IMAGE_CACHE_ENABLED (0)

/**
 *  Default number of active caches.
 */
#define CONFIG_DEF_MDI_NUM_CACHES (1)

/**
 *  Default original image cache setting, enabled.
 */
#define CONFIG_DEF_MDI_IMAGE_CACHE_ORIGINAL (1)

/**
 *  Default persistent storage path
 */
#define CONFIG_DEF_MDI_PERSISTENT_STORAGE "/tmp"

/**
 *  Default persistent storage maximum size in bytes
 */
#define CONFIG_DEF_MDI_PERSISTENT_SIZE 0

/**
 *  Default persistent storage path
 */
#define CONFIG_DEF_MDI_TEMP_STORAGE "/tmp"

/**
 *  Default search limit,in files, to look for external artwork in a folder.
 */
#define CONFIG_DEF_MDI_EXT_ARTWORK_SEARCH_LIMIT (100)

/**
 * Default number of non-media items allowed in a folder before the folder
 * is determined to not contain media items.  0 is unlimited.
 */
#define CONFIG_DEF_NONMEDIAITEMS_MAXITEMS (0)

/**
 * Default number of items to pre-scan for non-media items when a maximum
 * number of acceptable items is set.  0 is no limit.
 */
#define CONFIG_DEF_NONMEDIAITEMS_PRESCANLIMIT (0)

/**
 * Default value indicating whether the list of FIDs from the database should
 * be ordered by album_id and artist_id.
 */
#define CONFIG_DEF_ORDER_BY_METADATA_ENABLED true


#endif /* #ifndef _MME_CONFIG_H_INCLUDED */

/* __SRCVERSION("config.h $Rev: 700144 $"); */
