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



#if !defined(IOMEDIA_EVENTS_H_INCLUDED)
#define IOMEDIA_EVENTS_H_INCLUDED

#if !defined(_IOMEDIA_TYPES_H_INCLUDED)
#include <iomedia/types.h>
#endif

__BEGIN_DECLS

/** @file iomedia/events.h
 * io-media event type definitions.
 * Used both by the external API and the internal interfaces.
 * @ingroup commonTypes Common Types
 */

/** @addtogroup commonTypes Common Types
 */
/*@{*/

/**
 *  End of input.
 *  This event is sent when the graph has finished reading the current
 *  input track into its buffers.  It can still take some time before
 *  the end of the track reaches the speaker; but since reading the track
 *  is no longer necessary, it can be detached.
 *  The event data is the current track ID (an uint64_t).
 */
#define IOM_EV_INPUT_EOF        1

/**
 *  Time notification.
 *  This event is sent whenever the playback reaches a position that
 *  differs from the position of the previous event by at least the
 *  amount specified by the most recent call to
 *  iom_set_time_notification().
 *  The event data is a iom_graph_time_t structure.
 */
#define IOM_EV_TIME             2

/**
 *  Track transition.
 *  This event is sent whenever the previous track ends and the current
 *  input track starts playing.  Currently it is not sent when the graph
 *  is stopped while playing the previous track (and the current input
 *  becomes the current track), or on a seek request from the previous
 *  track to the current input track.
 *  The event data is a track ID (an uint64_t).
 */
#define IOM_EV_TRACK            3

/**
 *  State change.
 *  This event is sent whenever the play state changes (see
 *  iom_play_state_t) or the speed changes while the graph is playing
 *  (i.e. not when the speed is set while the graph is stopped),
 *  regardless of whether the change was caused by an API call
 *  or some other reason (such as end of file or an error).
 *  The event data is a iom_graph_status_t structure.
 */
#define IOM_EV_STATUS           4

/**
 *  Playback finished.
 *  This event is sent when the graph finishes playing a track and there
 *  is no next track attached to play.  An IOM_EV_STATUS event follows
 *  that indicates that the graph has stopped.
 *  The event data is a track ID (an uint64_t).
 */
#define IOM_EV_FINISHED         5

/**
 *  Volume change.
 *  This event is unused.
 */
#define IOM_EV_VOLUME           6


/**
 *  Scan mode change.
 *  This event is unused.
 */
#define IOM_EV_SCANMODE         7


/**
 *  Graph error.
 *  This event is sent whenever an error causes the graph to stop. An
 *  IOM_EV_STATUS event follows that indicates that the graph has
 *  stopped.  Currently, the event and the state change must be atomic,
 *  because the MME relies on the state being STOPPED immediately after
 *  the event is received.  This requirement will be removed in the
 *  future.
 *  The event data is an iom_error_info_t structure.
 */
#define IOM_EV_ERROR            8

/**
 *  EQ settings changed.
 *  This event is unused.
 */
#define IOM_EV_EQ               9

/**
 *  Oputput device change.
 *  This event is unused.
 */
#define IOM_EV_OUTPUTDEVICE    10

/**
 * A DVD or other media status change has occurred
 */
#define IOM_EV_DVD_STATUS      11

/**
 * A video change has occurred (source w, h, aspect ration, etc)
 */
#define IOM_EV_VIDEO_STATUS    12

/**
 *  Warning event.
 *  This event is sent to report a problem that does not cause the graph
 *  to stop.  The graph will try to continue playback; if that turns
 *  impossible, an IOM_EV_ERROR event will be sent before the graph
 *  stops.
 *  The event data is an iom_warning_info_t structure.
 */
#define IOM_EV_WARNING         13

/**
 *  Metadata change.
 *  New metadata is available for the currently playing track,
 *  or for the current input track.  Call iom_get_track_info()
 *  to get the new information.
 */
#define IOM_EV_METADATA        14

/**
 *  New input has been attached.
 *  This event is sent prior to a IOM_EV_TRACK to indicate the track id and
 *  URL of the track that was attached.
 *  The event data is an iom_new_input_t structure.
 */
#define IOM_EV_NEW_INPUT       15

/**
 *  Image event.
 *  A request to load or save an image has completed.
 *  The event data is an iom_image_event_t structure.
 */
#define IOM_EV_IMAGE           16

/**
 *  Media status event.
 *  The event data is an mm_media_status_event_t structure.
 */
#define IOM_EV_MEDIA_STATUS    17

/**
 *  User event.
 *  The format and meaning of the event data
 *  is up to the graphs that send the event and clients that receive it.
 */
#define IOM_EV_USER            18

/**
 *  Resource change.
 *  Sent when certain resources change their value.
 *  The event data is the null-terminated name of the resource,
 *  possibly followed by some resource-specific content.
 */
#define IOM_EV_RESOURCE        19

/*  Event structures */

/**
 *  Structure of an IOM_EV_IMAGE event
 */
typedef struct iom_image_event {
	_Uint32t result;        /**< See iom_result_type_t                      */
	_Uint32t load_id;       /**< The load ID from the load or save request  */
	_Uint32t image_id;      /**< The image ID from the track info           */
	_Uint32t reserved;
	iom_error_info_t error; /**< Error info, only valid if result is IOM_RESULT_FAILURE */
} iom_image_event_t;

/*@}*/

__END_DECLS

#endif

/* __SRCVERSION("events.h $Rev: 263760 $"); */
