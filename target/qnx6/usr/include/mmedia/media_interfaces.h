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



#ifndef __MEDIA_INTERFACES_H__
#define __MEDIA_INTERFACES_H__

#include <inttypes.h>

#include <aoi/aoi_interfaces.h>
#include <mmedia/mediafilter_defs.h>

#define MM_MEDIAFILTER_VERSION 110
/* The MediaFilter interface is used to create and destroy filters
 */
typedef struct
{
  MmFilter_t *(*Create)(void);
  int32_t (*Destroy)(MmFilter_t *filter);
} MediaFilter;


#define MM_MEMORYALLOCATOR_VERSION 122
/* The MediaMemoryAllocator interface is used to allocate acquire, share, release
 * and destroy media buffers
 */
typedef struct MediaMemoryAllocator
{
  /* mmedia framework library access functions */
  int32_t (*AllocateMemoryPool)(MmMemoryPool_t **mem_handle, MmChannel_t *channel,const MmMemoryFormat_t *mef, MmMemoryPool_t *old_handle, const MmFormat_t *fmt);
  int32_t (*FreeMemoryPool)(MmMemoryPool_t *mem_handle);
  /* filters access function */
  int32_t (*GetBufferInfo)(MmMemoryPool_t *mpool, int32_t *count, int32_t *size, MmBuffer_t **bufferList);
  int32_t (*AcquireBuffer)(MmMemoryPool_t *mem_handle, MmBuffer_t **buffer,int32_t noblock);
  int32_t (*IncrementRefCount)(MmBuffer_t *buffer);
  int32_t (*DecrementRefCount)(MmBuffer_t *buffer);
  int32_t (*ReleaseBuffer)(MmBuffer_t *buffer);
  const MmMemoryFormat_t *(*GetMemoryFormat)(MmMemoryPool_t *mpool);
  int32_t (*AdjustNumBuffers)(MmMemoryPool_t *mpool, int32_t delta);
} MediaMemoryAllocator;


typedef enum
{
  MM_TIME_USEC,
  MM_TIME_PAL,
  MM_TIME_NTSC,
  MM_TIME_32000HZ,
  MM_TIME_44100HZ,
  MM_TIME_48000HZ,
  MM_TIME_88200HZ,
  MM_TIME_96000HZ,
  MM_TIME_176400HZ,
  MM_TIME_192000HZ,
} MmTimeFormat_t;

#define MM_CLOCK_VERSION 130

struct MediaClockAlarm;

typedef struct MediaClockAlarm MediaClockAlarm_t;

typedef enum
{
   MEDIA_CLOCK_FORWARD,
   MEDIA_CLOCK_BACKWARD
} MediaClockDirection_t;

typedef struct
{
   /* return tick frequency ex: MM_TIME_PAL */
   MmTimeFormat_t (*QueryTick)( MmFilter_t *clock);
   /* init the interface */
   int32_t (*Initialize)(MmFilter_t *clock);
   /* uninitialize the interface */
   int32_t (*Uninitialize)(MmFilter_t *clock);
   /* set the clock value to the value specified according to format */
   int32_t (*SetValue)( MmFilter_t *clock, MmTimeFormat_t format, MmTime_t value, int64_t domain); /* Can return an error if the domain doesn't match the current one. */
   /* get the clock value in the specified format */
   MmTime_t (*GetValue)(MmFilter_t *clock, MmTimeFormat_t format, MmTime_t resolution, MmTimeFormat_t resolution_format, int64_t *domain);
   /* convert the invalue specified in the informat to a value expressed in the outformat */
   MmTime_t (*Convert)(MmFilter_t *clock, MmTimeFormat_t informat, MmTime_t invalue, MmTimeFormat_t outformat);
   int32_t (*Resume)(MmFilter_t *clock);
   int32_t (*SetSpeed)( MmFilter_t *clock, uint32_t speed, MediaClockDirection_t direction);
   int32_t (*Stop)(MmFilter_t *clock);
   /* create a new alarm based on the MediaClock.  flags MUST be 0. */
   int32_t (*CreateAlarm)( MmFilter_t *clock, MediaClockAlarm_t **alarm_obj, uint32_t flags);
   int32_t (*DestroyAlarm)( MmFilter_t *clock, MediaClockAlarm_t *alarm_obj);
   /* Blocks (sleeps) until the alarm expires, or error.  */
   int32_t (*SetAlarm)( MmFilter_t *clock, MediaClockAlarm_t *alarm_obj, MmTime_t wakeup, MmTimeFormat_t
                        wakeup_format, int64_t *actual_wakeup, int64_t domain);
   /* Blocks (sleeps) until all alarm holders make this call, or error or stop is called.
    * When it returns, if *send_event is set, the caller is responsible for posting a MM_EV_TRACK_CHANGE event. */
   int32_t (*WaitForEndOfTrack)(MmFilter_t *clock, MediaClockAlarm_t *alarm_obj, uint8_t *send_event);
   /* All alarm holders must call this function when they are ready to start.  This includes once they
    * are ready to commit their first payload, or if they recieve EOF, ERROR
    */
   void (*SignalPreroll)(MmFilter_t *clock, MediaClockAlarm_t *alarm_obj);
} MediaClock;

#define MM_TRICKPLAY_VERSION 100
typedef enum
{
  MM_TRICKMODE_NONE       = 0x01, /* the input stream cannot be trickplayed                        */
  MM_TRICKMODE_INFORM     = 0x02, /* call my scan interface function to inform me of trickplay mode */
  MM_TRICKMODE_FRAME_RATE = 0x04, /* the filter is able to change the frame rate                   */
  MM_TRICKMODE_DROP_FRAME = 0x08, /* the filter is able to drop frames                             */
  MM_TRICKMODE_EXTERNAL   = 0x10  /* the stream is externally trickplay mode controlled (no seeking required) */
}MmTrickMode_t;


typedef struct
{
  MmTrickMode_t (*Query)(MmFilter_t *filter);
  int32_t (*ScanForward)(MmFilter_t *filter, uint32_t speed, int32_t mute);
  int32_t (*ScanBackward)(MmFilter_t *filter, uint32_t speed, int32_t mute);
  int32_t (*ScanEnd)(MmFilter_t *filter);
} MediaTrickPlay;

#define MM_LISTREADER_VERSION 100
/*
 * The MediaListReader interface is implemented and used by a stream reader filter
 * to read data from a stream according to a list a read request
 */
typedef enum
{
  MM_DEFAULT_READ,
  MM_LIST_READ
} MmStreamMode_t;

typedef struct
{
  int32_t (*SetStreamMode)( MmFilter_t *filter, MmStreamMode_t mode );
  int32_t (*SetStreamList)( MmFilter_t *filter, const MmReadList_t *rlist);
} MediaListReader;


#define MM_LISTMAKER_VERSION 100
/*
 * The MediaListMaker interface is used to setup the stream reader filter
 * with a list of read request
 */
typedef struct
{
  int32_t (*GetNextReadList)(MmChannel_t *channel, MmReadList_t **new_list, const MmReadList_t *old_list);

} MediaListMaker;



#define MM_CONTROL_VERSION 101
/*
 * The MediaControl interface is used to start, stop pause, and resume media
 * filters.
 */
typedef struct
{
	int32_t (*Start)(MmFilter_t *filter,MmTime_t start_time);
	int32_t (*Stop)(MmFilter_t *filter);
	int32_t (*Pause)(MmFilter_t *filter);
	int32_t (*Resume)(MmFilter_t *filter,MmTime_t media_time,MmTime_t real_time);
	int32_t (*Status)(MmFilter_t *filter);
} MediaControl;


#define MM_FLUSH_VERSION 100
/*
 * The MediaFlush interface is used to flush filters that buffer mra
 *
 */
typedef struct
{
  int32_t (*Flush)(MmFilter_t *filter);
} MediaFlush;



#define MM_TIME_CONVERTER_VERSION 100
typedef struct
{
  int32_t (*ToPosition)(const MmFilter_t *filter, MmTime_t time, int64_t *position);
  int32_t (*ToTime)(const MmFilter_t *filter, int64_t position, MmTime_t *time);
} MediaTimeConverter;

#define MM_SEEK_NO       0x01    /* the input stream cannot be seeked                             */
#define MM_SEEK_INFORM   0x02    /* call my seek interface fuction to inform me of a seek         */
#define MM_SEEK_TIME     0x04    /* the input stream can be seeked by time                        */
#define MM_SEEK_BYTE     0x08    /* the input stream can be seeked by byte                        */
#define MM_SEEK_OPTIONAL 0x10  /* I can handle a restart after a flush, without a seek          */

#define MM_SEEKER_VERSION 102
/*
 * The MediaSeeker interfaces is used (and defined) if you need to be informed
 * when the graph is seeking to a new location.
 */
typedef struct
{
  int32_t (*Query)(MmFilter_t *filter);
  int32_t (*Seek)(MmFilter_t *filter,MmTime_t media_time, int64_t position);
} MediaSeeker;


#define MM_OUTPUT_VERSION 101
/*
 * The MediaOutput interface is defined for any filter that sends its output
 * to another filter, either streaming or buffered.  It contains all the
 * functionality you need to connect to another filter.
 */
typedef struct
{
	MmChannel_t *(*IterateChannels)(const MmFilter_t *f,int32_t * const cookie);
	int32_t (*AcquireChannel)(MmChannel_t *c);
	int32_t (*ReleaseChannel)(MmChannel_t *channel);
  /* format negotiationi functions */
	int32_t (*IterateFormats)(MmChannel_t *channel,MmFormat_t *mf,int32_t * const cookie);
	int32_t (*VerifyFormat)(MmChannel_t *channel,const MmFormat_t *new_fmt, const MmFormat_t *ofmt);
	int32_t (*SetFormat)(MmChannel_t *channel,const MmFormat_t *fmt);
  /* memory buffers allocation and access functions */
	int32_t (*NextBuffer)(MmChannel_t *channel, MediaRefArray_t **mra);
	int32_t (*SetMemoryPool)(MmChannel_t *channel,const MediaMemoryAllocator *mmai, hMB_t *mpool);
} MediaOutput;


#define MM_INPUT_VERSION 101
/*
 * The MediaInput interface is defined for any filter that gets its input from
 * another filter, either streaming or buffered.  It contains all the
 * functionality you need to connect to another filter.
 */
typedef struct
{
	MmChannel_t *(*IterateChannels)(const MmFilter_t *f,int32_t * const cookie);
	int32_t (*AcquireChannel)(MmChannel_t *c);
	int32_t (*ReleaseChannel)(MmChannel_t *channel);
	int32_t (*RateFormat)(MmChannel_t *channel, MmFormat_t *fmt, int32_t negotiable, int32_t * const cookie);
	int32_t (*SetFormat)(MmChannel_t *channel,const MmFormat_t *fmt);
	int32_t (*SetMediaOutput)(MmChannel_t *c,const MediaOutput *mo);
	int32_t (*SetMemoryPool)(MmChannel_t *channel,const MediaMemoryAllocator *mmai, hMB_t *mpool);
} MediaInput;

#define MM_INPUT_RENEGOTIATOR_VERSION 101
/*
 * The MediaInputReNegotiator interface is defined for any filter capable of
 * changing its input format on the fly.
 */
typedef struct
{
	int32_t (*ReRateFormat)(MmChannel_t *channel, MmFormat_t *fmt, int32_t negotiable, int32_t *cookie, MmReNegotiatorData_t *rdata);
	int32_t (*ApproveFormatChange)(MmChannel_t *channel, const MmFormat_t *fmt, MmReNegotiation_t *handle, MmReNegotiatorData_t *rdata);
	int32_t (*UpdateInputFormat)(MmChannel_t *channel, const MmFormat_t *fmt, MmMemoryPool_t *newwmpool, MmReNegotiatorData_t *rdata);
	void    (*Cleanup)(MmChannel_t *channel, const MmFormat_t *fmt, MmReNegotiatorData_t *rdata);
} MediaInputReNegotiator;

#define MM_OUTPUT_RENEGOTIATOR_VERSION 101
/*
 * The MediaOutputReNegotiator interface is defined for any filter capable of
 * changing its output format on the fly.
 */
typedef struct
{
	int32_t (*ReIterateFormats)(MmChannel_t *channel, MmFormat_t *mf, int32_t *cookie, void *odata);
	int32_t (*ReVerifyFormat)(MmChannel_t *channel, const MmFormat_t *newfmt, const MmFormat_t *ofmt, void *odata);
	int32_t (*AcceptFormatChange)(MmChannel_t *channel, MmFormatChange_t *fc, const MmFormat_t *fmt, void *odata);
	int32_t (*UpdateOutputFormat)(MmChannel_t *channel, const MmFormat_t *fmt, MmMemoryPool_t *mpool);
	int32_t (*FlushFormatChanges)(MmFilter_t *filter);
	int32_t (*ReNegotiate)(MmChannel_t *channel, MmReNegotiation_t *rhandle);
} MediaOutputReNegotiator;


#define MM_READER_VERSION 101
/*
 * The MediaReader interface is defined for any filter that is (and can only
 * be) a graph input endpoint.  This should be only defined for your filter
 * if it can never have another filter's output as an input.
 */
typedef struct
{
	int32_t (*SetInputStream)(MmFilter_t *f,AOIStream_t *sobj);
  AOIStream_t * (*GetInputStream)(MmFilter_t *f);
} MediaReader;


#define MM_WRITER_VERSION 100
/*
 * The MediaWriter interface is defined for any filter that is (and can only
 * be) a graph output endpoint.  This should be only defined for your filter
 * if it can never output to another filter's input.
 */
typedef struct
{
	int32_t (*SetOutputStream)(MmFilter_t *filter,AOIStream_t *sobj);
} MediaWriter;

#define MM_DEBUG_VERSION 100
/*
 * The MediaDebug interface is currently only intended for the DebugFilter.
 */
typedef struct
{
  int32_t ( *SetInputIDs )( MmFilter_t* pFilter, const char* pstrFilterID, const char* pstrChannelID );
  int32_t ( *SetOutputIDs )( MmFilter_t* pFilter, const char* pstrFilterID, const char* pstrChannelID );
  int32_t ( *SetLogFilename )( MmFilter_t* pFilter, const char* pstrFilename );
} MediaDebug;

#define MM_EVENTPRODUCER_VERSION 100

/* the event producer interface; any element that wishes to post events must implement this interface */

typedef struct {
	/* List the event types this element is capable of posting.

	   filter  - handle of the filter being queried
	   type    - address of a MmEventType_t which the function should fill with a distinct event type
	   cookie  - an iteration counter used internally by the function. Apart from initializing the cookie to
	             zero prior to the first call, the caller will not manipulate the cookie in any other way; the
	             function may manipulate the cookie in any way it sees fit to preserve state across successive
	             calls to the function

	   Return 0 to indicate a valid event type has been returned, otherwise return nonzero to indicate that no event
	   type has been reported and there are no more event types to report. */

	int (*List)(MmFilter_t *filter, MmEventType_t *type, MmCookie_t *cookie);

	/* Called to advise element of the function to call when posting all events.

	   filter  - handle of the filter
	   post_f  - pointer to a function which must be called to post an event */

	void (*SetPostFunction)(MmFilter_t *filter, void (*post_f)(MmFilter_t*,MmEventType_t,const void*,size_t));

	/* Called to register interest in an event. This will only be called once per element per type to indicate
	   that someone has registered an interest in the specified type of event.

	   filter  - handle of the filter
	   type    - event of interest

	   Returns 0 to indicate that everything is OK, or nonzero to indicate some kind of error. */

	int (*Register)(MmFilter_t *filter, MmEventType_t type);

} MediaEventProducer;

#define MM_EVENTLISTENER_VERSION 100

/* the event listener interface; any filter that wishes to listen to events must implement this interface */

typedef struct {
	/* List the event types this element is interested in.

	   filter  - the filter whose events are being iterated
	   type    - address of a MmEventType_t which the function should fill with a distinct event type
	   cookie  - an iteration counter used internally by the function. Apart from initializing the cookie to
	             zero prior to the first call, the caller will not manipulate the cookie in any other way; the
	             function may manipulate the cookie in any way it sees fit to preserve state across successive
	             calls to the function
	   Return 0 to indicate a valid event type has been returned, otherwise return nonzero to indicate that no event
	   type has been reported and there are no more event types to report. */

	int (*List)(MmFilter_t *filter,
		MmEventType_t *type,
		MmCookie_t *cookie);

	/* Called to notify the element of the possibility that an event of interest may be posted. This will only be
	   called once per element per type to indicate that someone has registered the capability to post that type of
	   event, before any invocations of 'Handle'.
	   filter     - the filter who is listening for events
	   type       - type of event
	   producers  - points to an array of filters who will post the events
	   nproducers - the number of elements in the 'producers' array */

	void (*Register)(MmFilter_t *filter,
		MmEventType_t type,
		MmFilter_t **producers,
		unsigned nproducers);

	/* Called to notify the element that an event of interest has occurred.
	   producer - the element who has posted the event
	   filter   - the filter who is listening for the event
	   type     - the type of the event
	   info     - pointer to a buffer containing additional information regarding the event
	   ilen     - size (in bytes) of the buffer pointed to by 'info', or 0 if 'info' is not a valid pointer */

	void (*Handle)(MmFilter_t *producer, MmFilter_t *filter, MmEventType_t type, const void *info, size_t ilen);

} MediaEventListener;

#define MM_STREAMER_VERSION 100
/*
 * The MediaStreamer interface is used to query a streamer
 * for any known information about a stream's data format
 */
typedef struct {
	/* return the stream format parameter is known, Otherwise -1  */
	int32_t (*GetFormat)(void *ctx, struct MmFormat_t *fmt);
} MediaStreamer;


#define MM_STREAMER_SEEK_TIME_VERSION 100
/*
 * The MediaStreamerSeekTime interfaces is used request playback of media content
 * that is some amount of time from the the start the content
 */
typedef struct
{
	int (*SeekTime)(const AOIStream_t *stream, MmTime_t seek_time);
} MediaStreamerSeekTime;


#define MM_SETINPUT_POSITION_VERSION 100
/*
 * The MediaSetInputPosition interface is used to move to a specific byte location in a stream without
 * flushing or affecting the current graph state.
 */
typedef struct
{
  int32_t (*SetInputPosition)(MmFilter_t *filter, int64_t position, uint32_t flags);
} MediaSetInputPosition;


#define MM_METADATA_WRITER_VERSION   100
/*
 The MediaMetadataWriter interface is defined for any filter that can associate Metadata to a particular stream.
*/

typedef  struct
{
  /* An interface function that let you write a metadata field. Return MM_EOK on success
     This interface function can only be call after a graph has been fully constructed
     (MmFinalizedGraph() has been called) and before the first MmStart() has been issued. */
  int32_t (*WriteMetadata)( MmFilter_t *filter, const char* key, int32_t instance, const void *data, uint32_t fourcc, uint32_t dsize);
  /* An interface function that let you  query expected fourcc and max size  for a metadata field.
     Return MM_EOK on success or an error code */
  int32_t (*Query)( MmFilter_t *filter, const char* key,int32_t instance, uint32_t *fourcc, uint32_t *dsize, int32_t * cookie);

  /* An interface function that let you verify that a previously written key is what you expected */
  int32_t (*Verify)(MmFilter_t *filter,const char* key,int32_t instance, uint32_t *fourcc, uint32_t *dsize, void const **data);

  /* An interface function that let you clear a previously written key */
  int32_t (*Clear)(MmFilter_t *filter,const char* key,int32_t instance);

  /* An interface function that let you commit all the successful metadata writing. Return MM_EOK on success or an error code
     This  interface function can only be call  after a graph has been fully constructed (MmFinalizedGraph() has been called)
     and before the first MmStart() has been issued. */
  int32_t (*Commit)(MmFilter_t *filter);
} MediaMetadataWriter;


#define MM_METADATA_READER_VERSION   100
/*
 The MediaMetadataReader interface is defined for any filter that can extract metadata from a stream.
 This interface is used on filters that are part of a fully constructed graph and can extract metatada
 on the currently playing stream. The extracted metadata can be static or changing as the playback of the stream progress.

 Note: The FreeMetadata,QueryMetadata,IterateMetadata interface function have been kept identical as those defined
       in the AOMetadataParser interface. Filters implementing both interfaces can just reference one set of functions
*/

typedef  struct
{
  /*
     An interface function that let you extract metadata.
     This interface function can only be call after a graph has been fully constructed (MmFinalizedGraph() has been called)
  */
  int32_t (*GetMetadata)(MmFilter_t *filter, AOMetadata_t **metadata);

  /*
   An interface function that let you free the metadata referenced by the AOMetadata_t handle.
  */
  void    (*FreeMetadata)(AOMetadata_t *metadata);

  /*
    An interface function that let you query if a specific metadata key is available.
  */
  int32_t (*QueryMetadata)(AOMetadata_t *metadata, char* key, int32_t instance,void **data,int32_t *fourcc,int32_t *dsize);

  /*
   An interface function that let you iterate through all available metadata .
  */
  int32_t (*IterateMetadata)(AOMetadata_t *metadata,int32_t *cookie,char** key,void **data,int32_t *fourcc,int32_t *dsize);
} MediaMetadataReader;




#define MM_METADATA_PARSER_VERSION   100    
typedef  struct
{

  /*
     An interface function that let you extract metadata from an arbitrary stream.
  */
  int32_t (*ParseMetadata)( const AOIStream_t *sobj, char *const *strings, MmMetadata_t **md);

  /*
     An interface function that let you extract metadata.
     This interface function can only be call after a graph has been fully constructed (MmFinalizedGraph() has been called)
  */
  int32_t (*GetMetadata)(MmFilter_t *filter, MmMetadata_t **metadata);

  /*
   An interface function that let you free the metadata referenced by the MmMetadata_t handle.
  */
  void (*FreeMetadata)(MmMetadata_t *metadata);

  /*
    An interface function that let you query if a specific metadata key is available.
  */
  int32_t (*QueryMetadata)(const MmMetadata_t *md, const char* key, int32_t instance, MmMetadataInfo_t *info);

  /*
   An interface function that let you iterate through all available metadata .
  */
  int32_t (*IterateMetadata)(const MmMetadata_t *metadata,int32_t *cookie, const char **key, MmMetadataInfo_t *info);
} MediaMetadataParser;

#endif
/* __SRCVERSION("media_interfaces.h $Rev: 715124 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/corelib/public/mmedia/media_interfaces.h $ $Rev: 715124 $")
#endif
