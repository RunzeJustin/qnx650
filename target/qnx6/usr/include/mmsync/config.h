/*
 * $QNXLicenseC:
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


#ifndef _MMSYNC_CONFIG_H_INCLUDED
#define _MMSYNC_CONFIG_H_INCLUDED

/**
 * The default mountpoint to mmsync's resource manager API.
 * All control contexts are created under this path.
 */
#define CONFIG_DEFAULT_DEVICE_PATH      "/dev/mmsync"

/**
 * Verbosity level of configuration initialization log messages.
 */
#define	CONFIG_DEF_CONFIG_VERBOSITY_LEVEL	2

/**
 * The default maximum number of synchronization records in the buffers between
 * the foreground and background synchronization threads.
 */
#define CONFIG_DEFAULT_SYNC_BUFFER  (250)

/**
 * The maximum directory structure depth to recursively visit when synchronizing
 * a mediastore. This setting also applies to priority folders.
 */
#define CONFIG_DEFAULT_SYNC_MAX_RECURSE (8)

/**
 * The default value for the maximum number of MS_SYNC_FIRST_EXISTING_FID events
 * sent during file synchronization.
 */
#define CONFIG_DEFAULT_SYNC_MAX_FIRST_FID (1)

/**
 * The maximum number of foreground synchronization threads permitted to run at
 * a time.
 */
#define	CONFIG_DEFAULT_SYNC_THREADS_MAX (8)

/**
 * The maximum number of event notifications that can be queued at a time.
 */
#define CONFIG_NTFY_QUEUE_MAX (80)

/**
 * The maximum allowable length of any filename (including the path) given to
 * mm-sync as a synchronization parameter.
 */
#define CONFIG_MAX_PATH      4000

/**
 * The maximum size of the message that can be sent to mm-sync. */
#define CONFIG_MAX_SQL       8000

/**
 * The maximum length of a file extension that can be specified in any filename
 * given to mm-sync.
 */
#define CONFIG_MAX_EXTENSION_LENGTH (30)

/**
 * The maximum number of distinct file extensions that can be synchronized.
 * This setting is applied separately for the extensions of media files and
 * for the extensions of playlists.
 */
#define CONFIG_MAX_EXTENSIONS 200


#define CONFIG_MAX_MS_NAME_LEN   (128)

/**
 * Metadata maximum string lengths are specified in 4-byte characters.
 * This constant is used internally by mm-sync for data copying.
 */
#define CONFIG_UTF8_CHAR_SIZE        (4)

/**
 * The mm-sync limit on the maximum size of the metadata that gets written to
 * the database. This maximum size is the number of characters in the metadata 
 * strings copied from the metadata provider into database fields.
 */
#define CONFIG_MAX_METADATA_CHARS    (256)

/**
 * The maximum number of lines that can be read from a playlist file. Each line
 * names one playlist entry, so this setting limits the allowable playlist
 * length. Used by some playlist session synchronizers (PLSSes).
 */
#define CONFIG_MAX_PLAYLIST_LINES       (5000)


/**
 * The maximum length of a mediastore synchronizer (mss) name that can be
 * given to mm-sync in the extended options for mm_sync_start().
 */
#define CONFIG_MAX_MSSNAME_LENGTH       (20)

/**
 * The maximum length of a file extension that can be specified as an image file
 * for retrieving external artwork from.
 * Used by the external art (extart) metadata plugin (MDP) for retrieving
 * cover art from Gracenote.
 */
#define CONFIG_MAX_ARTWORK_FILE_EXTENSION_LENGTH (8)


/**
 * The maximum number of MaxMediaStoreItems elements allowed in the
 * MaxMediaStoreItemsConfiguration configuration.
 */
#define CONFIG_MAX_MAXMEDIASTOREITEMS         (100)

/**
 * The default maximum size for the database, in kilobytes (kB).
 * If the database exceeds this size sync will abort.
 * If 0 there is no maximum database size.
 */
#define	CONFIG_DEF_MAX_DATABASE_SIZE	0

/**
 * After synchronizing this many files, mm-sync will check the database size.
 * Larger values mean faster synchronizations but also that the maximum
 * database size can be exceeded by a greater margin before sync aborts.
 * If 0, mm-sync will not check the database size during a synchronization.
 */
#define	CONFIG_DEF_SYNC_INTERVAL		0

/**
 * Default priority of sync thread (0 means inherit).
 */
#define	CONFIG_DEF_SYNC_THREAD_PRIORITY			0

/**
 * Default sync merge thread priority adjustement. This value is added to the
 * original synchronization thread priority, and so it is a relative value.
 */
#define	CONFIG_DEF_MERGE_THREAD_PRIORITY_ADJ		1

/**
 * Default emission control of folder sync events, which is "trimonly"
 */
#define	CONFIG_DEF_SYNC_FOLDER_EVENTS			2

/**
 * The default timeout value for database accesses, in milliseconds.
 */
#define CONFIG_DEF_DATABASE_TIMEOUT_MS   (0)

/**
 * Default number of non-media items allowed in a folder before the folder
 * is determined to not contain media items.  0 is unlimited.
 */
#define CONFIG_DEF_NONMEDIAITEMS_MAXITEMS (0)

/**
 * Default number of media items allowed in a folder before the folder
 * is determined to not contain media items.  0 is unlimited.
 */
#define CONFIG_DEF_MEDIAITEMS_MAXITEMS (0)

/**
 * Minimum size of a discovered file to be treated as a new file during
 * synchronization pass.  0 is any size.
 */
#define CONFIG_DEF_MEDIAITEMS_SIZEMIN (0)

/**
 * Default number of items to pre-scan for non-media items when a maximum
 * number of acceptable items is set.  0 is no limit.
 */
#define CONFIG_DEF_NONMEDIAITEMS_PRESCANLIMIT (0)

/**
 * The default maximum type to use for truncating the metadata.  It can be
 * either characters (default) or bytes
 */
#define CONFIG_DEF_TYPE_CHARS (1)

#endif /* #ifndef _MMSYNC_CONFIG_H_INCLUDED */

/* __SRCVERSION("config.h $Rev: 710621 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/lib/public/mmsync/config.h $ $Rev: 710621 $")
#endif
