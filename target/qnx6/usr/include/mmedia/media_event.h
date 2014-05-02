/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems (QSS) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by QSS by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

#ifndef __MEDIAEVENT_DEFS_H__
#define __MEDIAEVENT_DEFS_H__

#include <inttypes.h>

typedef enum MmEventType
{
  MM_EV_ERR = 1,
  MM_EV_STATE_TRANSITION_COMPLETE, /* Stopping -> Stopped, Pausing -> Paused */
  MM_EV_GAPLESS_PLAYBACK_BARRIER,  /* point in time where control of what is pushed to an audio card has to change
                                      to ensure gapless playback of two different streams  */
  MM_EV_METADATA_UPDATE,
  MM_EV_PREFETCH,
  MM_EV_WARNING,
  MM_EV_READ_SUCCESS,             /* first successful read  after read error, read timeout or graph started. extra info in MmReadEventInfo_t */
  MM_EV_READ_NEWPOS,              /* move to a new position after read error, read timeout. extra info in MmReadEventInfo_t */
  MM_EV_OUTPUT_ACTIVATED,         /* an inactive output channel has just been activated */
  MM_EV_USER,
  MM_EV_RESERVED1,
  MM_EV_AUDIO_METER,
  MM_EV_RESOURCE_CHANGE,          /* This event is used to signal resource-limited filters that resources have been revoked or returned.  (i.e. video decoders and allocators) */
  MM_EV_MEDIACLOCK_STARTED,       /* This event is emitted by the MediaClock when it has started after start
                                     is called.  This allows apps to know when the first frame of video is
                                     visible after MmStart is called. */
  MM_EV_OUTPUT_PROTECTION_LEVEL,  /* event is emitted by writer filter in their start() MediaControl interface  function
                                     when dealing with a DRM stream (drm flag set in the MmFormat_t).
                                     See the MmOutputInfo_t structure to see the data associated with the event.        */
  MM_EV_TRACK_CHANGE,             /* An event emitted by the writer filter when a new track has started playback in a gapless playback situation. */
  MM_EV_NEW_INPUT_STREAM,         /* the graph is fetching data from a new input stream   */
  MM_EV_AUDIO_DEVICE_CHANGE,      /* event emitted by an audio reader or writer when an audio device change has been detected */
  MM_EV_EOF,                      /* Sent when EOF is output to the next filter */
  MM_EV_NET_RECONNECTION,         /* Reconnection request is sent when the preferable network adapter changes and the reader "wants" to reconnect to use the preferable adapter */
  MM_EV_LIVE_WINDOW,              /* For detailed description read MmLiveWindowEventInfo_t */
} MmEventType_t;

typedef enum MmErrorInfo
{
  MM_ERR_READ = 1,
  MM_ERR_WRITE,
  MM_ERR_WRITE_UNDERRUN,
  MM_ERR_DROPPED_FRAME,
  MM_ERR_CORRUPTED_STREAM,
  MM_ERR_READ_OVERRUN,
  MM_ERR_DRM_OPL,
  MM_ERR_UNSUPPORTED_FORMAT,
} MmErrorInfo_t;

typedef enum MmErrorValueType
{
  MM_ERRVAL_NONE,
  MM_ERRVAL_ERRNO,
  MM_ERRVAL_STREAM_POS, /* the stream byte position where the read error occur */
  MM_ERRVAL_CUSTOM,
} MmErrorValueType_t;

typedef struct MmErrorEventInfo
{
  MmErrorInfo_t       info;          /* info about the error event */
  int32_t             flags;         /* see  below  MM_EVF...      */
  MmErrorValueType_t  value_type;
  uint64_t            value;
} MmErrorEventInfo_t;


#define MM_EVF_ERR_STATUS  0x01  /* the filter will assume the MM_STATUS_ERROR state in its Status() interface function */
#define MM_EVF_ERR_FATAL   0x02  /* fatal error, don't try to recover */

typedef enum MmWarningInfo
{
  MM_WARN_READ_TIMEOUT = 1,
  MM_WARN_WRITE,
  MM_WARN_WAIT_RESOURCES
} MmWarningInfo_t;

typedef enum MmWarningValueType
{
  MM_WARNVAL_NONE,
  MM_WARNVAL_ERRNO,
  MM_WARNVAL_CUSTOM,
} MmWarningValueType_t;

typedef struct MmWarningEventInfo
{
  MmWarningInfo_t       info;          /* info about the warning event */
  MmWarningValueType_t  value_type;
  uint64_t              value;
} MmWarningEventInfo_t;


typedef struct MmReadEventInfo
{
  uint64_t  bytepos;                   /* the position in the stream  associated with the read event */
} MmReadEventInfo_t;

typedef struct MmAudioMeterEventInfo
{
  uint16_t         nchan;    /* Number of channels  */
  uint16_t         depth;    /* Number of bits per sample (including sign bit)  */
  uint32_t         ceiling;  /* The maximum possible value for the format (1 << depth-1)  */
  uint32_t         maxval;   /* The max sample value for this chunk of stream  */
  const uint32_t   *chanmax; /* The max sample value separately for each channel  */
} MmAudioMeterEventInfo_t;

#define MM_RESOURCES_REVOKED  0x01
#define MM_RESOURCES_RETURNED 0x02
typedef struct MmResourceChangeEventInfo
{
  uint32_t change_type;  /* Type of resource change.  See flags.  They are flags for the possible case that both happened.  */
  void     *id;          /* ID associated with the change. This is used to distinguish between resources if there are multiple managed resources in a graph. */
} MmResourceChangeEventInfo_t;


typedef struct MmAudioDeviceChangeEventInfo
{
  uint64_t bcount;       /* Number of bytes transmitted since last Resume cmd */
  uint8_t  old_device;
  uint8_t  new_device;
  uint16_t padding;
  uint32_t status_next; // An MmStatus_t that tells the filter what to do next (auto-pause, error, EOF, keep playing)
  uint32_t status_mask; // A mask of MmStatus_t bits that the filter supports in status_next
} MmAudioDeviceChangeEventInfo_t;

struct media_channel; // MmChannel_t

typedef struct MmEofEventInfo {
  struct media_channel *channel;
} MmEofEventInfo;
typedef enum MmNetReconnectInfo
{
  MM_NETRECONN_QUERY,     // "Please set the permission flags"
  MM_NETRECONN_CANCELLED,     // "Someone said no to the query, we'll try to keep using the old connection"
  MM_NETRECONN_SUCCESS,       // "We have successfully reconnected"
  MM_NETRECONN_FAILURE,       // "We have tried and it didn't work, we'll try to keep using the old connection"
} MmNetReconnectInfo_t;

typedef struct MmNetReconnectEventInfo
{
  MmNetReconnectInfo_t       info;         /* info about the reconnect event */
  char const * current_adapter_name;       /* Name of the network adapater in use by the connection */
  char const * preferable_adapter_name;    /* Name of the suggested network adapater for reconnection */
  int32_t      permission_from_app;        /* Application authorizes the reconnection by setting this variable  */
  int32_t      permission_from_parser;     /* Parser authorizes the reconnection by setting this variable  */
  int64_t      byte_position;              /* Byte position where the reconnection will happen */
} MmNetReconnectEventInfo_t;

/*
 "MmLiveWindowEventInfo_t: This event provides rough information for live streaming (ex: mp3 radio) about how much payload is available "behind" the live presentation point.
presentation_time is the actual played time; for example: lets say that the user plays the stream for 2 seconds, pauses for 3 seconds and resumes; after 10 seconds of the very beginning of the play the filter that originates this event has collected the information and post the event to the application. in this example the presentation_time will be 7 seconds; all the accumulated pause time is subtracted from the collecting information time.
The num_bytes_read, as its name suggests, brings the number of bytes read (downloaded). "
 */
typedef struct MmLiveWindowEventInfo
{
  uint32_t    presentation_time;      /* presentation time in milliseconds (pause time is taken out) */
  uint32_t    num_bytes_read;
} MmLiveWindowEventInfo_t;

#endif

/* __SRCVERSION("media_event.h $Rev: 715124 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/corelib/public/mmedia/media_event.h $ $Rev: 715124 $")
#endif
