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



#if !defined(_IOMEDIA_TYPES_H_INCLUDED)
#define _IOMEDIA_TYPES_H_INCLUDED

#include <sys/platform.h>
#include <_pack64.h>
#include <mm/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file iomedia/types.h
 * Common io-media types.
 * Used both by the extarnal API and the internal interfaces.
 * @ingroup commonTypes Common Types
 */

/** @addtogroup commonTypes Common Types
 */
/*@{*/

/**
 * Flags that can be passed to iom_create_graph()
 */
enum iom_graph_flags {
	IOM_GF_ATTACH   =  1,  /**< Attach to an already existing graph                */
	IOM_GF_KEEP     =  2,  /**< Don't unlink the graph when this fd is closed      */
	IOM_GF_NOEVENTS =  4,  /**< This fd will not be used to read events            */
};

/**
 * The playstate defining the different states of the graph
 * Note that fast forward and rewind are not here because
 * they can be found by checking play_speed in graph_status
 */
typedef enum iom_play_state {
	IOM_PS_IDLE,      /**< The graph has no media to play              */
	IOM_PS_STOPPED,   /**< The graph has some media but is not playing */
	IOM_PS_PAUSED,    /**< The graph is paused ("playing at speed 0")  */
	IOM_PS_PREFETCH,  /**< The graph is preparing to play              */
	IOM_PS_PLAY       /**< The graph is playing                        */
} iom_play_state_t;

enum iom_state_flags {
	IOM_SF_INEXACT_SPEED   =  1,  /**< Used for graphs where exact play speed is unknown */
};

typedef enum iom_graph_capability {
	IOM_GC_PLAYBACK        = 1, /**< The graph can play things */
	IOM_GC_METADATA        = 2, /**< The graph can extract metadata */
	IOM_GC_TRACKSESSION    = 4, /**< The graph can handle device tracksessions */
	IOM_GC_TRACK_ID        = 8, /**< The graph generates its own track id */
} iom_graph_capability_t;

/**
 *  Flags passed to iom_attach_output().
 */
enum iom_output_flags {
	IOM_OF_AUDIO  = 1,                           /**< The output is an audio device */
	IOM_OF_VIDEO  = 2,                           /**< The output is an video device */
	IOM_OF_AV     = IOM_OF_AUDIO | IOM_OF_VIDEO, /**< A combined audio+video device */
};

/**
 *  Buffering state returned by iom_get_buffering_status().
 */
typedef enum iom_buffering_state {
    IOM_BS_PREFETCHING,        /**< Paused and fetching data to prepare to play.  Need to read. */
    IOM_BS_BUFFERING,          /**< Buffer level is low.  Need to read. */
    IOM_BS_DRAINING,           /**< Draining without reading.  Playing buffered data */
    IOM_BS_NORMAL,             /**< Normal operation.  May or may not attempt to read. */
} iom_buffering_state_t;

/**
 * Possible results of an asynchronous request.
 */
typedef enum iom_result_type {
	IOM_RESULT_SUCCESS,  /**< The operation was successful              */
	IOM_RESULT_FAILURE,  /**< The operation failed                      */
	IOM_RESULT_CANCELED, /**< The operation was canceled by an API call */
} iom_result_type_t;

/**
 * Defines the time information for a graph
 */
typedef struct iom_graph_time {
	_Uint64t        current_track_id;  /**< Currently playing track ID
	                                        (or current input if graph stopped)         */
	_Int64t         current_time;      /**< Current position in milliseconds            */
	_Uint64t        total_time;        /**< Duration of the track in milliseconds       */
	_Uint32t        current_prefetch;  /**< Current amount prefetched in milliseconds.
	                                        This can be greater than total_prefetch
	                                        due to payload-size rounding.               */
	_Uint32t        total_prefetch;    /**< Size of the prefetch buffer in milliseconds */
} iom_graph_time_t;

/**
 * Defines the volume information for an audio output
 */
typedef struct iom_audio_volume {
	_Uint8t         volume;     /**< The volume in percent (0 - 100)         */
	_Uint8t         balance;    /**< The balance in percent (50 = balanced,
	                                 0 = fully left, 100=fully right)        */
	_Uint8t         fade;       /**< The fade in percent (50 = balanced,
	                                 0= fully back, 100=fully front)         */
	_Uint8t         mute;       /**< Nonzero = muted                         */
	_Uint16t        change_duration; /**< The time in milliseconds over which
	                                      to apply the settings above.       */
	_Uint16t        reserved;
} iom_audio_volume_t;

/**
 *  Defines transitions between tracks
 */
typedef struct iom_track_transition {
	_Uint32t        fade_time;  /**< The amount of time in milliseconds that
	                                 one track should be faded for           */
	_Int32t         gap_time;   /**< The time between tracks in silence.
	                                 If negative then there is a cross
	                                 fade if it is 0 then there is no
	                                 gap between tracks, and if it is
	                                 positive then there is silence
	                                 between tracks.                         */

	_Uint64t        scan_time;  /**< The max number of milliseconds of songs
	                                 to play before going to the next one    */
} iom_track_transition_t;

/**
 * Status information for a graph
 */
typedef struct iom_graph_status {
	_Uint64t        current_track_id; /**< Currently playing track ID
	                                       (or current input if graph stopped) */
	_Uint32t        play_state;       /**< One of iom_play_state_t's           */
	_Int32t         play_speed;       /**< 1000 = normal speed, 0=pause,
	                                       negative means reverse              */
	_Uint32t        flags;            /**< Flags from enum iom_state_flags     */
	_Int32t         reserved;
} iom_graph_status_t;

typedef struct iom_key_val {
	const char *key;
	const char *val;
} iom_key_val_t;

/**
 * Information about an image associated with a track
 */
typedef struct iom_image_info {
	_Uint32t             width;        /**< Width of the image in pixels, or zero if unknown    */
	_Uint32t             height;       /**< Height of the image in pixels, or zero if unknown   */
	_Uint64t             size;         /**< Size of the image data in bytes, or zero if unknown */
	_Uint32t             image_id;     /**< Image ID for use with the API                       */
	_Uint32t             flags;        /**< See enum iom_image_flags                            */
	_Uint64t             start_pos;    /**< Starting position of where the image applies, in ms */
	_Uint64t             end_pos;      /**< End of where the image applies, ~0=EOF, 0=unknown   */
	const iom_key_val_t *properties;   /**< Misc properties, encoded as strings                 */
	_Uint32t             num_props;    /**< The length of the properties array                  */
	_Uint64t             reserved2;
} iom_image_info_t;

/**
 * Misc bits of information about an image associated with a track
 */
enum iom_image_flags {
	IOM_IMAGE_EXTERNAL_URL = 1, /**< the media contains the URL rather than the image itself. The URL for this image can be obtained and used without calling iom_load_image() first, but may be invalid or point to the wrong or non-existent image. */
	IOM_IMAGE_INTERNAL_URL = 2, /**< the URL for this image can be obtained and used without calling iom_load_image() first, and is known to be valid (for instance, because it points to a file that the graph just saved). */
	IOM_IMAGE_ONDEMAND     = 4, /**< before the URL for this image can be accessed, it must be loaded using the iom_load_image() function. */
	IOM_IMAGE_SAVEABLE     = 8, /**< this image can be saved to a file using the iom_save_image() function. */
};

/**
 * Info about a track, also relevant to other media types
 */
typedef struct iom_track_info {
	_Uint64t                 track_id;
	const mm_metadata_t     *metadata;
	const mm_audio_format_t *audio;
	const mm_video_format_t *video;
	_Uint32t                 num_images;
	const iom_image_info_t  *images;
} iom_track_info_t;

/**
 * Info about devices with navigation, such as DVD, VCD, iPod, etc.
 */
typedef struct iom_device_info {
	_Uint32t        title_count;    /**< Number of titles or tracks */
	_Uint32t        device_type;
	_Uint64t        disc_id;        /**< For discs: unique ID */
} iom_disc_info_t, iom_device_info_t;

/**
 *  Information about a title
 */
typedef struct iom_title_info {
	_Uint32t        chapter_count; /**< Number of chapters in this title */
	_Uint32t        reserved;
	_Uint64t        title_length;  /**< Title duration */
} iom_title_info_t;

/**
 *  Information about a chapter within a title
 */
typedef struct iom_chapter_pos {
	_Uint32t        title;          /**< Title number */
	_Uint32t        chapter;        /**< Chapter number */
	_Uint64t        chapter_start;  /**< Offset of the chapter from the beginning of the title */
	_Uint64t        chapter_length; /**< Duration of the chapter */
} iom_chapter_time_t, iom_chapter_info_t;

#define IOM_MAX_DVD_SUBTITLES 32
#define IOM_MAX_DVD_AUDIO      8

/**
 *  The header that every event starts with.
 */
typedef struct iom_event_header {
	_Uint32t        length;       /**< Length in bytes, including the header */
	_Uint32t        type;         /**< The event type                        */
} iom_event_header_t;

/**
 * Round the event length to find the next event in the buffer.
 * @param length The lengh taken from the event header
 * @return The rounded length, in bytes
 */
#define iom_event_rounded_size( length )  ( ( (length) + 7 ) & ~(_Uint32t) 7 )

#if __STDC_VERSION__ >= 199901 || __GNUC__ >= 3
	#define _FLEXIBLE
#elif __GNUC__ >= 2
	#define _FLEXIBLE 0
#else
	#define _FLEXIBLE 1
#endif

/**
 *  This structure can be used to create a buffer aligned at an 8-byte boundary.
 *
 *  For instance,
 *  \code
 *        struct {
 *            iom_event_buffer_t hdr;
 *            char moredata[ DATALEN ];
 *        } buf;
 *  \endcode
 *  Instead, you can simply use a union that includes a \p uint64_t:
 *  \code
 *        union {
 *            iom_event_header_t hdr;
 *            uint64_t align;
 *            char thedata[ DATALEN + sizeof(iom_event_header_t) ];
 *        } buf;
 *  \endcode
 */
typedef struct iom_event_buffer {
	union {
		iom_event_header_t h;
		_Uint64t        ui;     /* Enforces alignment */
	} u;
	char            data[_FLEXIBLE];
} iom_event_buffer_t;

struct sigevent;  /* Include <sys/siginfo.h> to get the contents */

/**
 * Structure describing the details of an error.
 */
typedef struct iom_error_info {
	_Uint32t iom_errno;  /**< One of iom_errno_t */
	_Uint32t value_type; /**< One of iom_errval_t */
	_Uint64t value;      /**< Zero or some value, depending on value_type */
} iom_error_info_t;

/**
 * Error info from graphs
 */
typedef enum iom_error_class {
	IOM_ERRORCLASS_UNSUPPORTED = 1,
	IOM_ERRORCLASS_INVALID,
	IOM_ERRORCLASS_PERMISSION,
	IOM_ERRORCLASS_MEDIA,
	IOM_ERRORCLASS_IO,
	IOM_ERRORCLASS_UNDERRUN,
	IOM_ERRORCLASS_AUTHENTICATION,
	IOM_ERRORCLASS_RESOURCE,
	IOM_NUM_ERRORCLASSES
} iom_error_class_t;

typedef enum iom_errval {
	IOM_ERRVAL_NONE,
	IOM_ERRVAL_ERRNO,
	IOM_ERRVAL_MMF,
	IOM_ERRVAL_USER1 = 1000,
	IOM_ERRVAL_USER2,
	IOM_ERRVAL_USER3,
} iom_errval_t;

#define iom_errclass(errclass) (errclass<<16)
typedef enum iom_errno {
	IOM_ERROR_NONE = 0,
	IOM_ERROR_UNKNOWN,
	IOM_ERROR_INVALID = iom_errclass(IOM_ERRORCLASS_INVALID),
	    IOM_ERROR_INVALID_PARAMETER,
	    IOM_ERROR_INVALID_STATE,
	IOM_ERROR_UNSUPPORTED = iom_errclass(IOM_ERRORCLASS_UNSUPPORTED),
	    IOM_ERROR_UNSUPPORTED_RESOURCE,
	    IOM_ERROR_UNSUPPORTED_RESOURCE_OPERATION,
	    IOM_ERROR_UNSUPPORTED_OPERATION,  /* function invalid for this graph or the currently attached input */
	    IOM_ERROR_UNSUPPORTED_MEDIA_TYPE,
	    IOM_ERROR_UNSUPPORTED_VALUE, /* value is correct but unsupported by graph */
	IOM_ERROR_PERMISSION = iom_errclass(IOM_ERRORCLASS_PERMISSION),
	    IOM_ERROR_REGION_CODE,
	    IOM_ERROR_PARENTAL_CONTROL,
	    IOM_ERROR_BLOCKED_UOP,
	    IOM_ERROR_DOMAIN,
	    IOM_ERROR_ID_MISMATCH,
	IOM_ERROR_MEDIA = iom_errclass(IOM_ERRORCLASS_MEDIA),
	    IOM_ERROR_MEDIA_UNAVAILABLE,
	    IOM_ERROR_MEDIA_CORRUPTED,
	    IOM_ERROR_MEDIA_PROTECTED,
	IOM_ERROR_IO = iom_errclass(IOM_ERRORCLASS_IO),
	    IOM_ERROR_READ,
	    IOM_ERROR_WRITE,
	    IOM_ERROR_DESTINATION_FULL,
	    IOM_ERROR_DESTINATION_READONLY,
	IOM_ERROR_UNDERRUN = iom_errclass(IOM_ERRORCLASS_UNDERRUN),
	IOM_ERROR_AUTHENTICATION = iom_errclass(IOM_ERRORCLASS_AUTHENTICATION),
	    IOM_ERROR_INVALID_KEY,
	IOM_ERROR_RESOURCE = iom_errclass(IOM_ERRORCLASS_RESOURCE),
	    IOM_ERROR_NO_MEMORY,
	    IOM_ERROR_RESOURCE_UNAVAILABLE,
} iom_errno_t;
#undef iom_errclass

#define IOM_ERROR_CLASS_MASK 0xffff0000u
#define IOM_ERRNO_MASK     0x0000ffffu

#define iom_error_class(_err_)  (((_err_) & IOM_ERROR_CLASS_MASK)>>16)

/**
 * Flags in a warning event
 */
typedef enum iom_warning_flags {
	IOM_WARNING_FLAG_NONE    = 0x0,
	IOM_WARNING_FLAG_AUDIBLE = 0x1, /**< A warning with this flag set indicates
	                                     that it was audible to the listener.   */
	IOM_WARNING_FLAG_VISIBLE = 0x2, /**< A warning with this flag set indicates
	                                     that it was visible to the viewer. */

} iom_warning_flags_t;

/**
 * Types of warning events
 */
typedef enum iom_warnings {
	IOM_WARNING_READ_TIMEOUT   = 0x1, /**< The source was slow and a read timed out.
	                                       It is being retried.                              */
	IOM_WARNING_READ_ERROR     = 0x2, /**< There was a read error.  We're trying to recover. */
	IOM_WARNING_AUDIO_UNDERRUN = 0x3, /**< There was an underrun on the audio output.        */
	IOM_WARNING_VIDEO_UNDERRUN = 0x4, /**< There was an underrun on the video output.
	                                       This results in dropped frames. */
} iom_warnings_t;

/**
 * Payload structure for the IOM_EV_WARNING event.
 */
typedef struct iom_warning_info {
	_Uint32t iom_warning;   /**< One of iom_warnings_t */
	_Uint32t flags;         /**< Zero or some flags from iom_warning_flags_t */
} iom_warning_info_t;

/**
 * Payload structure for the IOM_EV_NEW_INPUT event.
 */
typedef struct iom_new_input {
	_Uint64t  track_id;  /**< Track id of the track that has been attached.
	                          It matches the track_id field of the iom_track_info_t struct. */
	char      track_url[_FLEXIBLE]; /**< A string containing the URL of the new track. */
} iom_new_input_t;

#include <_packpop.h>

/*@}*/

#ifdef __cplusplus
}
#endif

#endif

/* __SRCVERSION("types.h $Rev: 276615 $"); */
