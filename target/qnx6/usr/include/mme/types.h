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


#ifndef _MME_TYPES_H_INCLUDED
#define _MME_TYPES_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

__BEGIN_DECLS

struct _mme_hdl;
typedef struct _mme_hdl mme_hdl_t;

typedef struct {
   uint64_t          dstmsid;
   const char        *dstfolder;
   const char        *dstfilename;
   uint64_t          encodeformatid;
} mme_mediacopier_info_t;

typedef enum mme_outputtype {
	MME_OUTPUTTYPE_UNKNOWN = 0,
	MME_OUTPUTTYPE_AUDIO = 1,
	MME_OUTPUTTYPE_VIDEO = 2,
	MME_OUTPUTTYPE_ENCODED = 3
} mme_outputtype_t;

/**
 * Output Attributes
 *
 * This structure is used for getting and setting different attributes
 * on output devices.  It is a union of audio, video, and encoded therefore
 * it can only control one class of output device at a time.
 */
typedef struct mme_output_attr {
	union {
		struct {
			int         	volume;     /* 0 - 100 (percent based) */
			int            	balance;    /* -100(left) 0(center) +100(right) */
			int            	fade;       /* -100(back) 0(center) +100(forward) */
			int            	mute;       /* 0 = not muted, 1 = muted */
			uint64_t       	delay;      /* number of milliseconds to delay output */
			int	         	change_duration;   /* number of milliseconds to ramp volume */
		} audio;

		struct {
            int             layer;      /* GF/Video layer */
		} video;

		struct {
            /* not yet implemented */
		} encoded;
	};
} mme_output_attr_t;

/**
 * This structure is used to define the sync status
 * for a single media store.
 *
 * See MME_SYNC_OPTION_* values in interface.h.
 */
typedef struct s_mme_sync_status {
	uint64_t	msid;			/**< ID of the media store */
	uint16_t	passes_done;	/**< From database. */
	uint16_t	current_pass;	/**< The current pass flag. */
	uint16_t	passes_to_do;	/**< The passes yet to do */
	uint16_t	reserved[1];	/**< Packing element */
    uint32_t    operation_id;   /**< 0 for non-directed sync */
} mme_sync_status_t;

typedef enum mme_playstate {
    MME_PLAYSTATE_UNKNOWN   = 0,
    MME_PLAYSTATE_ERROR     = 1,
    MME_PLAYSTATE_PLAYING   = 2,
    MME_PLAYSTATE_PAUSED    = 3,
    MME_PLAYSTATE_FASTFWD   = 4,
    MME_PLAYSTATE_FASTREV   = 5,
    MME_PLAYSTATE_STOPPED   = 7,
	MME_PLAYSTATE_SLOWFWD   = 8,
	MME_PLAYSTATE_SLOWREV   = 9
} mme_playstate_t;

typedef struct mme_playstate_speed {
    uint32_t		playstate;
    int32_t			speed;
} mme_playstate_speed_t;

/* Random mode settings */
typedef enum mme_mode_random {
   MME_RANDOM_OFF           = 0,
   MME_RANDOM_ALL           = 1,
   MME_RANDOM_ALBUMS        = 2,
   MME_RANDOM_FOLDER        = 3,
   MME_RANDOM_SUBFOLDER     = 4
} mme_mode_random_t;

/* Repeat mode settings */
typedef enum mme_mode_repeat {
   MME_REPEAT_OFF           = 0,
   MME_REPEAT_SINGLE        = 1,
   MME_REPEAT_ALL           = 2,
   MME_REPEAT_FOLDER        = 3,
   MME_REPEAT_SUBFOLDER     = 4
} mme_mode_repeat_t;

typedef struct _mme_time_info {
   uint64_t          time;             /* Current time position (ms) */
   uint64_t          duration;         /* Track time duration (ms) */
} mme_time_t;

typedef struct _mme_byte_status {
   uint64_t          bytepos;          /* Bytes already copied */
   uint64_t          nbytes;           /* Total number of bytes to copy */
} mme_byte_status_t;

typedef enum mme_buffer_state {
    MME_BUFFER_STATE_NORMAL=0,
    MME_BUFFER_STATE_PREFETCHING=1,
    MME_BUFFER_STATE_BUFFERING=2
} mme_buffer_state_t;
typedef struct mme_buffer_status {
	uint32_t			state;            /* Buffer state, see #define MME_BUFFER_STATE */
	uint32_t			read_ms;          /* Number of milliseconds buffered */
	uint32_t			max_ms;           /* Max buffer size in milliseconds */
	uint32_t			reserved;
} mme_buffer_status_t;

typedef struct _mme_play_status {
   mme_time_t          time_info;      /* Time info */
   uint32_t            playstate;      /* Current MME playstate */
   mme_buffer_status_t buffer;         /* Current playback buffer status */
} mme_play_status_t;

typedef enum mme_copy_units {
    MME_COPY_UNITS_NONE     = 0,       /* No units defined */
    MME_COPY_UNITS_TIME_MS  = 1,       /* Time in ms */
    MME_COPY_UNITS_BYTES    = 2        /* Bytes */
} mme_copy_units_t;

typedef struct _mme_copy_status {
   uint64_t				cqid;             /* Copy Queue ID entry being processed */
   uint64_t				srcfid;           /* File ID of source file being copied */
   uint64_t				dstfid;           /* File ID of destination file */
   uint32_t				units;            /* Defines the progress units of measure */
   uint32_t				reserved;
   union {
      mme_time_t        time_info;        /* Time info */
      mme_byte_status_t byte_info;        /* Byte info */
   };
} mme_copy_status_t;

typedef struct _mme_copy_info {
   /* Note: put srcfid first so that it is compatible with previous mme_event_t data */
   uint64_t             srcfid;           /* File ID of source file being copied */
   uint64_t             dstfid;           /* File ID of destination file */
   uint64_t             cqid;             /* Copy Queue ID entry being processed */
} mme_copy_info_t;

/**
 * The current track is navigable.  Use of the mme_button( )
 * interface is recommended.
 */
#define MME_PLAYSUPPORT_NAVIGATION               0x0001

/**
 * The device supports it own track session management.
 * One example is iPod running in serial mode.
 * Rather than issue mme_next( ), issue mme_button( NEXT )
 * to get to the next track.
 */
#define MME_PLAYSUPPORT_DEVICE_TRACKSESSION      0x0002

/**
 * The current track has video
 */
#define MME_PLAYSUPPORT_VIDEO                    0x0004

/**
 * The current track has audio
 */
#define MME_PLAYSUPPORT_AUDIO                    0x0008

/**
 * The device track session supports repeat and random.
 * One example is iPod running in serial mode.
 */
#define MME_PLAYSUPPORT_DEVICE_REPEATRANDOM      0x0010


/**
 * information about the current playing track.
 */
typedef struct mme_play_info {
	uint64_t        fid;
	uint64_t        msid;
	uint32_t        storage_type;
	uint32_t        ftype;
	uint32_t        playmode;
	uint32_t        slottype;
	uint32_t        tracknum;
	uint32_t        titlenum;
    uint32_t        audio_index;
	uint32_t        support;
	uint32_t		reserved;
    uint64_t        mscap;

    /*
     * The support flag indicates what the current playing
     * track supports.  The following defines are bitmasks
     * to indicate that it is supported.
     *
     * See the MME_PLAYSUPPORT_* masks
     */
	uint64_t		offset;
} mme_play_info_t;


/* Define valid string substitutions for mme_mediacopier_set_name_template() */
#define MME_MEDIACOPIER_TEMPLATE_TITLE     "$TITLE"     /* song title */
#define MME_MEDIACOPIER_TEMPLATE_ARTIST    "$ARTIST"    /* artist name */
#define MME_MEDIACOPIER_TEMPLATE_ALBUM     "$ALBUM"     /* album name */
#define MME_MEDIACOPIER_TEMPLATE_GENRE     "$GENRE"     /* song genre */
#define MME_MEDIACOPIER_TEMPLATE_TRACK     "$TRACK"     /* track number */
#define MME_MEDIACOPIER_TEMPLATE_0TRACK    "$0TRACK"    /* track number with leading 0's (i.e. 01, 02, etc) */
#define MME_MEDIACOPIER_TEMPLATE_DISC      "$DISC"      /* disc number */
#define MME_MEDIACOPIER_TEMPLATE_0DISC     "$0DISC"     /* disc number with leading 0's (i.e. 01, 02, etc) */
#define MME_MEDIACOPIER_TEMPLATE_YEAR      "$YEAR"      /* release year */
#define MME_MEDIACOPIER_TEMPLATE_SRCFID    "$SRCFID"    /* The source file ID */
#define MME_MEDIACOPIER_TEMPLATE_SRCMSID   "$SRCMSID"   /* The source mediastore ID */
#define MME_MEDIACOPIER_TEMPLATE_TIMESTAMP "$TIMESTAMP" /* Time when the file is copied */
#define MME_MEDIACOPIER_TEMPLATE_DATESTAMP "$DATESTAMP" /* Date when the file is copied */
#define MME_MEDIACOPIER_TEMPLATE_MSIDENTIFIER "$MSIDENTIFIER" /* src mediastores.identifier value */

/* mme_mediacopier_add() flags */
#define MME_MEDIACOPIER_COPYADD_NONE                              0x0000  /*  obsolete */
#define MME_MEDIACOPIER_COPYADD_PRESERVE_PATH                     0x0001  /*  obsolete */
#define MME_MEDIACOPIER_USE_DEFAULT_FILENAME                      0x0002  /* use default file name */
#define MME_MEDIACOPIER_USE_METADATA                              0x0004  /* force use of given metadata */
#define MME_MEDIACOPIER_USE_DEFAULT_FOLDERNAME                    0x0008  /* use default folder name */

typedef enum mme_mediacopier_mode {
    MME_MEDIACOPIER_MODE_BKG = 0,
    MME_MEDIACOPIER_MODE_PRIORITY_BKG,
    MME_MEDIACOPIER_MODE_FOREGROUND
} mme_mediacopier_mode_t;


typedef struct {
	uint64_t		trksessionid;    /* Currently set trksessionid */
	uint64_t		flags;           /* None defined */
	uint32_t		track;           /* Current track number */
	uint32_t		totaltracks;     /* Total number of tracks */
	uint32_t		title;           /* Current title number */
	uint32_t		ntitles;         /* Total number of titles */
	uint32_t		chapter;         /* Currently unused */
	uint32_t		nchapters;       /* Currently unused */
	char			reserved[16];    /* Currently unused */
} mme_trksessionview_info_t;


#define TRKVIEW_READ_FID		0x00000001
#define TRKVIEW_READ_FILE		0x00000002
#define TRKVIEW_READ_FID_EXTENDED	0x00000003

typedef struct {
	uint64_t fid;
} trksessionview_entry_t; 

typedef struct {
	uint64_t	msid;
	uint32_t	reserved;
	char		*filename;
} trksessionview_entry_file_t;

typedef struct {
	uint64_t fid;
	union {
		uint64_t sequentialid;
		uint64_t randomid;
	};
} trksessionview_entry_fid_extended_t; 

typedef struct s_mme_metadata_session {
	uint64_t session_id; /* Session identifier */
} mme_metadata_session_t;

typedef struct s_mme_metadata_info {
	int32_t		len;       /* Length of xmlbuf string including NULL terminator */
	char		xmlbuf[1]; /* NULL terminated, XML formated string containing metadata. */
} mme_metadata_info_t;

typedef struct s_mme_metadata_image_url {
	int32_t		len;     /* Length of the URL string including the NULL termintor */
	char		url[1]; /* NULL terminated, URL formated string location of an image. */
} mme_metadata_image_url_t;


typedef enum {
	MME_PLAY_EXTENDED_TYPE_UNKNOWN = 0,
	MME_PLAY_EXTENDED_TYPE_FID,    /* mme_play_extended_fid_t */
	MME_PLAY_EXTENDED_TYPE_OFFSET, /* mme_play_extended_offset_t */
} mme_play_extended_type_t;

typedef struct {
	uint64_t        fid;          /* fid to play; 0 plays from beginning of tracksession */
	uint64_t        time_ms;      /* Start time offset in milliseconds. */
	uint8_t         reserved[8];  /* For future use. Must be 0. */
} mme_play_extended_fid_t;

typedef struct {
	uint64_t        offset;       /* The 0-based offset into tracksession to play. */
	uint64_t        time_ms;      /* Start time offset in milliseconds. */
	uint32_t        flags;        /* None, or MME_PLAY_OFFSET_MMETRACKSESSION to use the MME's
	                               * tracksession for devices that are tracksession capable (iPod). */
	uint8_t         reserved[8];  /* For future use. Must be 0. */
} mme_play_extended_offset_t;

typedef struct s_mme_play_extended {
	uint32_t	type;         /* The play type, defined in mme_play_extended_type_t. */
	uint32_t        reserved;     /* For future use. Must be 0. */
	union {
		mme_play_extended_fid_t fid;
		mme_play_extended_offset_t offset;
	};
} mme_play_extended_t;

typedef enum {
	MME_BOOKMARK_TYPE_UNKNOWN  = 0,
	MME_BOOKMARK_TYPE_USER     = 1,   /* default 'user requested' bookmark */
	MME_BOOKMARK_TYPE_RESUME   = 2,   /* resumable bookmark */
	MME_BOOKMARK_TYPE_MINAVAIL = 128, /* application-available bookmark types */
	MME_BOOKMARK_TYPE_MAXAVAIL = 255,
} mme_bookmark_type_t;

typedef enum {
	MME_PLAYAUTOPAUSED_REASON_UNKNOWN = 0,
	MME_PLAYAUTOPAUSED_REASON_USER,     /* autopause is on and (gapless failed, is disabled, or first play) */
	MME_PLAYAUTOPAUSED_REASON_BOOKMARK, /* bookmark resume is on and a resume bookmark exists */
} mme_playautopaused_reason_t;

typedef struct s_mme_playautopaused {
	uint8_t  reason;
} mme_playautopaused_t;


__END_DECLS

#endif /* _MME_TYPES_H_INCLUDED */

/* __SRCVERSION("types.h $Rev: 398360 $"); */
