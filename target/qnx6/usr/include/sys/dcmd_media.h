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



#ifndef __DCMD_MEDIA_H_INCLUDED
#define __DCMD_MEDIA_H_INCLUDED

#include <devctl.h>
#include <inttypes.h>
#include <sys/types.h>

struct _media_date {
	uint16_t			year;
	uint8_t				seconds;	/*  (0-59) */
	uint8_t				minutes;	/*  (0-59) */
	uint8_t				hours;		/*  (0-23) */
	uint8_t				day;		/*  (1-31) */
	uint8_t				month;		/*  (1-12) */
	uint8_t				weekday;	/*  (0-6, where 0=Sunday and 6=Saturday) */
	char                text[40];   /*  ASCII date as formatted by device */
};

#define DCMD_MEDIA_PLAY				__DION(_DCMD_MEDIA, 10)
#define DCMD_MEDIA_PLAY_AT			__DIOT(_DCMD_MEDIA, 11, struct _media_play)
#define DCMD_MEDIA_PAUSE			__DION(_DCMD_MEDIA, 12)
#define DCMD_MEDIA_RESUME			__DION(_DCMD_MEDIA, 13)
#define DCMD_MEDIA_NEXT_TRACK		__DION(_DCMD_MEDIA, 14)
#define DCMD_MEDIA_PREV_TRACK		__DION(_DCMD_MEDIA, 15)
#define DCMD_MEDIA_FASTFWD			__DIOT(_DCMD_MEDIA, 16, struct _media_speed)
#define DCMD_MEDIA_FASTRWD			__DIOT(_DCMD_MEDIA, 17, struct _media_speed)
#define DCMD_MEDIA_PLAYBACK_INFO	__DIOF(_DCMD_MEDIA, 18, struct _media_playback)
#define DCMD_MEDIA_GET_SHUFFLE		__DIOF(_DCMD_MEDIA, 19, struct _media_settings)
#define DCMD_MEDIA_SET_SHUFFLE		__DIOT(_DCMD_MEDIA, 20, struct _media_settings)
#define DCMD_MEDIA_GET_REPEAT		__DIOF(_DCMD_MEDIA, 21, struct _media_settings)
#define DCMD_MEDIA_SET_REPEAT		__DIOT(_DCMD_MEDIA, 22, struct _media_settings)
#define DCMD_MEDIA_GET_STATE		__DIOF(_DCMD_MEDIA, 23, uint8_t[1])
#define DCMD_MEDIA_SET_STATE		__DIOT(_DCMD_MEDIA, 24, uint8_t[1])
#define DCMD_MEDIA_PLAYBACK_STATUS	__DIOF(_DCMD_MEDIA, 25, struct _media_playback_status)
#define DCMD_MEDIA_SEEK_CHAP		__DIOT(_DCMD_MEDIA, 26, uint32_t)
#define DCMD_MEDIA_NEXT_CHAP		__DION(_DCMD_MEDIA, 27)
#define DCMD_MEDIA_PREV_CHAP		__DION(_DCMD_MEDIA, 28)

#define DCMD_MEDIA_ALBART_INFO		__DIOF(_DCMD_MEDIA, 52, struct _media_albart_entry)		/*  retval is # of ents in array */
#define DCMD_MEDIA_ALBART_LOAD		__DIOT(_DCMD_MEDIA, 53, struct _media_albart_entry)		/*  retval is index returned */

/**
 * The READ call can be used to read the image in chunks. Once part of the
 * image is read (startting with the struct _media_albart), that data will no
 * longer be returned from a subsequent DCMD_MEDIA_ALBART_READ call. Instead
 * the next block of data will be returned. The retval is the # of bytes
 * returned (total size is in the header structure). Once the whole image is
 * done being read, ENODATA is returned. If this call is made while the image
 * is still being received, EAGAIN will be returned.
 */
#define DCMD_MEDIA_ALBART_READ		__DIOF(_DCMD_MEDIA, 54, struct _media_albart)			/*  retval is # bytes */

struct _media_img_desc {
	uint32_t					width;		/*  width in pixels */
	uint32_t					height;		/*  height in pixels */
	uint32_t					size;		/*  size in bytes */
	uint32_t					reserved;
	char						mimetype[64];
};

#define ALBART_FLAG_POS_NONE		0x00000000	/*  No position information */
#define ALBART_FLAG_POS_TRKPOS		0x00000001	/*  Position is ms from start of track */
#define ALBART_FLAG_POS_CHPIDX		0x00000002	/*  Position is chapter number */
#define ALBART_FLAG_POS_MASK		0x0000000f

struct _media_albart_entry {
	uint16_t					index;		/*  index to match this entry */
#define ALBART_INDEX_NONE			0xffff	/*  No specific index (used for DCMD_MEDIA_ALBART_LOAD to best-match) */
	uint16_t					reserved[3];
	uint32_t					flags;		/*  ALBART_FLAG_* */
	uint32_t					pos;		/*  track position in ms for this entry */
	struct _media_img_desc		desc;
};

struct _media_albart {
	uint32_t					flags;		/*  ALBART_FLAG_* */
	uint32_t					pos;		/*  position to display albumart (TRKPOS or CHPIDX if set) */
	uint32_t					reserved[6];
	struct _media_img_desc		desc;
	uint8_t						data[1];
};


/**
 * If returning EOK returns the number of bytes of events as the extra data, doesn't read partial events.
 * If the number of bytes of events exceeds the client reply buffer, no data will be copied to client, EOK will
 * still be returned.  Up to client to check that reply buffer is larger than the number of bytes returned to
 * indicate valid data in the reply buffer.
 */
#define DCMD_MEDIA_READ_EVENTS		__DIOF(_DCMD_MEDIA, 55, char[1])

#define MEDIA_EVENT_ERROR    0
#define MEDIA_EVENT_WARNING  1
#define MEDIA_EVENT_TRACK    2
#define MEDIA_EVENT_TIME     3
#define MEDIA_EVENT_METADATA 4
#define MEDIA_EVENT_USER     5

struct _media_event {
	uint32_t			type;	/* Type of event */
	uint32_t			len;	/* Length of event (includes padding to 8 byte alignment) */
};

#define MEDIA_EVENT_ERROR_UNKNOWN 0
#define MEDIA_EVENT_ERROR_DRM     1
#define MEDIA_EVENT_ERROR_CORRUPT 2
struct _media_event_error {
	struct _media_event	event;
	uint32_t			index;		  /* Track index event relates to. */
	uint32_t            type;         /* Error type; */
};

#define MEDIA_EVENT_WARNING_UNKNOWN 0
struct _media_event_warning {
	struct _media_event	event;
	uint32_t			index;		  /*  Track index event relates to. */
	uint32_t            type;         /*  Warning type; */
};

#define MEDIA_EVENT_INFO_UNKNOWN 0
struct _media_event_info {
	struct _media_event	event;
	uint32_t			index;		  /*  Track index event relates to. */
	uint32_t            type;         /*  info type; */
	char                value[1];
};

struct _media_event_time {
	struct _media_event	event;
	uint32_t			index;		/*  Track index event relates to. */
	uint32_t			elapsed;	/*  Elapsed time for the current track. */
	uint32_t			duration;	/*  Duration of the current track. */
};

struct _media_event_track {
	struct _media_event	event;
	uint32_t			index;		  /*  Track index event relates to. */
	uint32_t			duration;	  /*  Duration of the current track. */
	char                trackpath[1]; /*  Track file name relative to mountpoint. */
};

#define MEDIA_EVENT_METADATA_UNKNOWN      0
#define MEDIA_EVENT_METADATA_SONG         1
#define MEDIA_EVENT_METADATA_ALBUM        2
#define MEDIA_EVENT_METADATA_ARTIST       3
#define MEDIA_EVENT_METADATA_GENRE        4
#define MEDIA_EVENT_METADATA_COMPOSER     5
#define MEDIA_EVENT_METADATA_RELEASE_DATE 6
#define MEDIA_EVENT_METADATA_TRACK_NUM    7
#define MEDIA_EVENT_METADATA_PUBLISHER    8
#define MEDIA_EVENT_METADATA_DURATION     9
#define MEDIA_EVENT_METADATA_NAME         10
#define MEDIA_EVENT_METADATA_COMMENT      11

struct _media_event_metadata {
	struct _media_event	event;
	uint32_t            type;         /*  Type of Metadata event. */
	uint32_t			index;		  /*  Track index event relates to. */
	uint32_t            duration;     /*  Length of the track in milliseconds. */
	struct _media_date  date;         /*  Date of the track. */
	char                value[1];     /*  String UTF8 encoded, for character based types. */
};

struct _media_event_user {
	struct _media_event	event;
	char                data[1];         // User event data.
};

/**
 * This command can be sent to any node within the filesystem to indicate
 * if the filesystem is active or not, this is used in the case where
 * a fs is being used to cache data, but the underlying device is
 * not in a state where media actions cannot be performed.
 */
#define MEDIA_FS_STATE_INACTIVE 0
#define MEDIA_FS_STATE_ACTIVE   1
#define DCMD_MEDIA_GET_FS_STATE		__DIOF(_DCMD_MEDIA, 56, unsigned int)

/* Start after 100 for the Meta Data. */
#define DCMD_MEDIA_SONG				__DIOF(_DCMD_MEDIA,  100, char[1])
#define DCMD_MEDIA_ALBUM			__DIOF(_DCMD_MEDIA,  101, char[1])
#define DCMD_MEDIA_ARTIST			__DIOF(_DCMD_MEDIA,  102, char[1])
#define DCMD_MEDIA_GENRE			__DIOF(_DCMD_MEDIA,  103, char[1])
#define DCMD_MEDIA_COMPOSER			__DIOF(_DCMD_MEDIA,  104, char[1])
#define DCMD_MEDIA_RELEASE_DATE		__DIOF(_DCMD_MEDIA,  105, struct _media_date)
#define DCMD_MEDIA_TRACK_NUM	    __DIOF(_DCMD_MEDIA,  106, char[1])
#define DCMD_MEDIA_PUBLISHER		__DIOF(_DCMD_MEDIA,  107, char[1])
#define DCMD_MEDIA_DURATION 		__DION(_DCMD_MEDIA,  107)
#define DCMD_MEDIA_NAME				__DIOF(_DCMD_MEDIA,  108, char[1])
#define DCMD_MEDIA_COMMENT			__DIOF(_DCMD_MEDIA,  109, char[1])
#define DCMD_MEDIA_URL      		__DIOF(_DCMD_MEDIA,  110, char[1])

#define DCMD_MEDIA_ACCESS_TYPE 		__DION(_DCMD_MEDIA,   114)  /*  return integer value  */
#define ACCESS_TYPE_DRM_PROTECTED       1   /*  file is known to be DRM protected */
#define ACCESS_TYPE_DRM_UNPROTECTED     2   /*  file is known to not be DRM protected */
#define ACCESS_TYPE_READ_SUPPORTED  	4   /*  file can be read using POSIX read function (is not Zune) */
#define ACCESS_TYPE_STREAM_SUPPORTED  	8   /*  file can be read using DCMD_MEDIA_STREAM devctls */

#define DCMD_MEDIA_INFO_STREAM      __DIOF(_DCMD_MEDIA,   114, struct _media_stream_info)
#define DCMD_MEDIA_OPEN_STREAM      __DION(_DCMD_MEDIA,   115)
#define DCMD_MEDIA_CLOSE_STREAM     __DION(_DCMD_MEDIA,   116)
#define DCMD_MEDIA_SET_STREAM       __DIOT(_DCMD_MEDIA,   117, unsigned int)
#define DCMD_MEDIA_READ_STREAM      __DIOF(_DCMD_MEDIA,   118, char[16*1024-1])

#define DCMD_MEDIA_GET_DEVINFO		__DIOF(_DCMD_MEDIA,   119, char[8*1024])

#define DCMD_MEDIA_UPNP_CDS_BROWSE	__DIOT(_DCMD_MEDIA,   120, char[8])

#define DCMD_MEDIA_DRM_IS_AUTH      __DIOTF(_DCMD_MEDIA,  121, char[8*1024])
#define DCMD_MEDIA_DRM_REGISTER     __DIOTF(_DCMD_MEDIA,  122, char[8*1024])
#define DCMD_MEDIA_DRM_PROXIMTY     __DIOTF(_DCMD_MEDIA,  123, char[8*1024])
#define DCMD_MEDIA_DRM_LICENSE      __DIOTF(_DCMD_MEDIA,  124, char[8*1024])
#define DCMD_MEDIA_DRM_CHALLENGE    __DIOTF(_DCMD_MEDIA,  125, char[8*1024])

#define DCMD_MEDIA_IPOD_DAUDIO		__DIOF(_DCMD_MEDIA,   130, struct _media_ipod_daudio)
struct _media_ipod_daudio {
	unsigned			rate;	/*  Sample rate (in Hertz. 32000, 44100, 48000 or optional 8000, 11025, 12000, 16000, 22050 or 24000) */
	int					sndchk;	/*  Sound check (gain in db + or -, always zero if sound check is disabled) */
	int					voladj;	/*  Volume adjustment (gain in db + or -) */
	unsigned			reserved;
};
#define DCMD_MEDIA_IPOD_CAP			__DIOF(_DCMD_MEDIA,  131, char[1])
#define DCMD_MEDIA_IPOD_TAG			__DIOT(_DCMD_MEDIA,  132, uint8_t[1])		/*  Write iTunes Tag */

/*  for iomsg of mgrid type _IOMSGR_MEDIA: define subtype ranges */
#define IOMSG_MEDIA_PFS_START        1000     /*  start of PFS subtype messages */
#define IOMSG_MEDIA_PFS_END          1099     /*  end of PFS subtype messages */

/*  Set a configuration option */
#define DCMD_MEDIA_CONFIG      		__DIOT(_DCMD_MEDIA,  133, char[1])

#define DCMD_MEDIA_SET_SUBTITLE		__DIOT(_DCMD_MEDIA, 134, int32_t)                   /*  array index or -1 for off */
#define DCMD_MEDIA_GET_SUBTITLE		__DIOF(_DCMD_MEDIA, 135, struct _media_subtitle)	/*  retval is #entries */
struct _media_subtitle {
	char            lang[2];  /* language codes per ISO 639-1 */
	unsigned char	reserved[30];
};

#define DCMD_MEDIA_SET_AUDIO		__DIOT(_DCMD_MEDIA, 136, int32_t)               /*  array index or -1 for off */
#define DCMD_MEDIA_GET_AUDIO		__DIOF(_DCMD_MEDIA, 137, struct _media_audio)	/*  retval is #entries */
struct _media_audio {
	char            lang[2];  /* language codes per ISO 639-1 */
	unsigned char	reserved[30];
};

#define DCMD_MEDIA_SET_XML			__DIOT(_DCMD_MEDIA, 138, char[1])
#define DCMD_MEDIA_GET_XML			__DIOF(_DCMD_MEDIA, 139, char[1])

#define DCMD_MEDIA_TRKSESSION_MODE		__DION(_DCMD_MEDIA,   140)  /*  return integer value  */
#define MEDIA_TRKSESSION_ENABLED			0   /* Tracksessions are enabled */
#define MEDIA_TRKSESSION_DISABLED			1   /* Tracksessions are disabled */

#define DCMD_MEDIA_SET_TRACK_TIME	__DIOT(_DCMD_MEDIA, 141, uint64_t)

__BEGIN_DECLS

struct _media_play {
	unsigned			pos;
};

struct _media_stream_info {
    unsigned char       is_DRM;
    unsigned char       seek_supported;
    unsigned char       unused[2];
    uint32_t            reserved;           /*  pad to 64 bit alignment */
    uint64_t            stream_length;
#define MEDIA_STREAM_LENGTH_UNKNOWN ((uint64_t) -1LL)   /*  if stream length unkown */
};

#define DCMD_MEDIA_ANALOG_DIGITAL_SWITCH	__DIOT(_DCMD_MEDIA, 140, uint32_t)
#define MEDIA_IPOD_ANALOG	0
#define MEDIA_IPOD_DIGITAL	1

/**
 * This struture is used to send to the speed to the device.
 * Rates will be: 1, 2, 4, 8, 16, 32
 * Normal playback is 1x.
 */
struct _media_speed {
	unsigned			rate;
};


struct _media_playback {
	uint32_t			count;		/*  Total # tracks in playback list. */
	uint32_t			index;		/*  Track index currently in playback. */
#define PLAYBACK_STATE_STOP		0
#define PLAYBACK_STATE_PLAY		1
#define PLAYBACK_STATE_PAUSE	2
	uint8_t				state;		/*  State of the track: Play/Paused/Stopped. */
#define PLAYBACK_FLAG_FASTFWD		0x01	/*  DCMD_MEDIA_FASTFWD is in effect (i.e. not 1) */
#define PLAYBACK_FLAG_FASTRWD		0x02	/*  DCMD_MEDIA_FASTRWD is in effect (i.e. not 1) */
#define PLAYBACK_FLAG_SPEED_EXACT	0x04	/*  actual device speed, otherwise passed in DCMD_MEDIA_FAST?WD value */
#define PLAYBACK_FLAG_EVENTS		0x08	/*  There are events waiting in the queue. */
	uint8_t				flags;
	uint16_t			metaseq;	/*  Sequence number changes if metadata values have changed during the current track */
	uint32_t			length;		/*  Length of the track. */
	uint32_t			elapsed;	/*  Elapsed time for the current track. */
	uint32_t			speed;		/*  Only valid if PLAYBACK_FLAG_FAST?WD bit set */
};

struct _media_playback_status {
	uint32_t			flags;			/*  Flags: PLAYBACK_FLAG_* */
#define PLAYBACK_FLAG_FASTFWD		0x01	/*  DCMD_MEDIA_FASTFWD is in effect (i.e. not 1) */
#define PLAYBACK_FLAG_FASTRWD		0x02	/*  DCMD_MEDIA_FASTRWD is in effect (i.e. not 1) */
#define PLAYBACK_FLAG_SPEED_EXACT	0x04	/*  actual device speed, otherwise passed in DCMD_MEDIA_FAST?WD value */
#define PLAYBACK_FLAG_EVENTS		0x08	/*  There are events waiting in the queue. */
#define PLAYBACK_FLAG_ALBART		0x10	/*  Albumart is available to be read (DCMD_MEDIA_ALBART_READ) */
#define PLAYBACK_FLAG_IS_VIDEO		0x20	/*  Video is currently playing */
#define PLAYBACK_FLAG_REPEAT_SHUFFLE	0x00000100 /*  The shuffle and repeat states in this structure are valid */
	uint32_t			state;			/*  State of playback: PLAYBACK_STATE_* */
#define PLAYBACK_STATE_STOP			0
#define PLAYBACK_STATE_PLAY			1
#define PLAYBACK_STATE_PAUSE		2
	uint32_t			speed;			/*  Speed only valid if PLAYBACK_FLAG_FAST?WD is set */
	uint32_t			trkidx_total;	/*  Total number of tracks in playback list */
	uint32_t			trkidx_current;	/*  Currently playing track */
	uint32_t			trkpos_total;	/*  Length of currently playing track (in ms) */
	uint32_t			trkpos_current;	/*  Position in currently playing track (in ms) */
	uint32_t			chpidx_total;	/*  Total number of chapters (0=no chapters) */
	uint32_t			chpidx_current;	/*  Currently playing chapter */
	uint32_t			chppos_total;	/*  Length of currently playing chapter (in ms, -1 if unknown) */
	uint32_t			chppos_start;	/*  Position from start of track to start of chapter (in ms, -1 if unknown) */
	uint32_t			metaseq;		/*  Sequence number changes if metadata values changed during current track playback */
	uint8_t				repeat;		/* If PLAYBACK_FLAG_SHUFFLE_REPEAT set, current repeat state */
	uint8_t				shuffle;	/* If PLAYBACK_FLAG_SHUFFLE_REPEAT set, current shuffle state */
	uint8_t				reserved[14];
};


#define REPEAT_OFF			0
#define REPEAT_ONE_TRACK	1
#define REPEAT_ALL_TRACKS	2
#define REPEAT_FOLDER		3
#define REPEAT_SUBFOLDER	4

#define SHUFFLE_OFF			0
#define SHUFFLE_TRACKS		1
#define SHUFFLE_ALBUMS		2
#define SHUFFLE_FOLDER		3
#define SHUFFLE_SUBFOLDER	4
struct _media_settings {
	uint8_t				value;
};

/* Common media type strings used in the info.xml file 
   in the "media/type" tag to describe the medium. Currently
   consistent with the defined storage types used by the QNX
   media software, to provide a mapping of type to string.
*/
#define IOFS_MEDIA_TYPE_UNKNOWN      "UNKNOWN"
#define IOFS_MEDIA_TYPE_AUDIOCD      "AUDIOCD"
#define IOFS_MEDIA_TYPE_VCD          "VCD"
#define IOFS_MEDIA_TYPE_SVCD         "SVCD"
#define IOFS_MEDIA_TYPE_FS           "FS"
#define IOFS_MEDIA_TYPE_DVDAUDIO     "DVDAUDIO"
#define IOFS_MEDIA_TYPE_DVDVIDEO     "DVDVIDEO"
#define IOFS_MEDIA_TYPE_IPOD         "IPOD"
#define IOFS_MEDIA_TYPE_KODAKCD      "KODAKCD"
#define IOFS_MEDIA_TYPE_PICTURECD    "PICTURECD"
#define IOFS_MEDIA_TYPE_A2DP         "A2DP" 
#define IOFS_MEDIA_TYPE_SMB          "SMB"
#define IOFS_MEDIA_TYPE_FTP          "FTP"
#define IOFS_MEDIA_TYPE_HTTP         "HTTP"
#define IOFS_MEDIA_TYPE_NAVIGATION   "NAVIGATION"
#define IOFS_MEDIA_TYPE_PLAYSFORSURE "PFS"
#define IOFS_MEDIA_TYPE_UPNP         "UPNP"


__END_DECLS

#endif

/* __SRCVERSION("dcmd_media.h $Rev: 720372 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/lib/public/sys/dcmd_media.h $ $Rev: 720372 $")
#endif
