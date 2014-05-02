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



#ifndef __MMEDIA_H__
#define __MMEDIA_H__

#include <inttypes.h>

#include <aoi/aoi.h>
#include <aoi/aoi_mime.h>
#include <mmedia/medialib_defs.h>
#include <mmedia/media_interfaces.h>

#ifdef __cplusplus
extern "C" {
#endif
//deprecated
int32_t MmInitialize(const char *addon_path);
//
//MmInit is the replacement of MmInitialize 
int32_t MmInit(const char *config_file);

MmGraph_t *MmCreateGraph(const char *name);
int32_t MmDestroyGraph(MmGraph_t *graph);
int32_t MmFinalizeGraph(MmGraph_t *graph);
MmFilter_t *MmIterateFilters(MmGraph_t *graph, int32_t *cookie);

MmFilter_t *MmCreateFilter(MmGraph_t *g,const AOICtrl_t *a);
int32_t MmDestroyFilter(MmFilter_t *filter);

MmChannel_t *MmIterateChannels(const MmFilter_t *f,int32_t d,int32_t * const cookie);
int32_t MmAcquireChannel(MmChannel_t *c);
int32_t MmReleaseChannel(MmChannel_t *c);
int32_t MmAttachChannels(MmChannel_t *ic,MmChannel_t *oc);
int32_t MmDetachChannel(MmChannel_t *c);

int32_t MmStart(void *e,MmTime_t mt);
int32_t MmStop(void *e);
int32_t MmPause(MmGraph_t *g);
int32_t MmResume(MmGraph_t *g);
int32_t MmSeek(MmGraph_t *g,MmTime_t mt);
int32_t MmStatus(const void *e);
int32_t MmSetInputPosition(MmGraph_t *graph, int64_t position, uint32_t flags);
int32_t MmIsSeekable(MmGraph_t *graph);

int32_t MmScanForward( MmGraph_t *graph, uint32_t speed, int32_t mute );
int32_t MmScanBackward( MmGraph_t *graph, uint32_t speed, int32_t mute );

const AOResource_t *MmGetResources(const void *element);
const AOResource_t *MmGetResource(const void *element,const char *resource);
const void *MmGetResourceValue(const void *element,const char *resource);
#define MmGetResourceINT32(E,R,I) \
do { \
	int32_t const *__t=MmGetResourceValue(E,R); \
	(I) = __t ? *__t : 0; \
} while(0)
#define MmGetResourceINT64(E,R,I) \
do { \
	int64_t const *__t=MmGetResourceValue(E,R); \
	(I) = __t ? *__t : 0; \
} while(0)
#define MmGetResourceSTRING(E,R,I) \
do { \
	char *const *__t=MmGetResourceValue(E,R); \
	(I) = __t ? *__t : 0; \
} while (0)
int32_t MmSetResourceValue(const void *element,const char *resource,const void *data);

const AOICtrl_t *MmIterateMimeReaders(int32_t * const cookie);
const AOMimeInfo_t *MmMimeInfo(const AOICtrl_t *a);

/* Fails if highest rated filter can't be used. */
MmFilter_t *MmFindChannelsFilter(MmGraph_t *g,MmChannel_t *c);
/* Accepts highest rated filter that is usable and available. */
MmFilter_t *MmFindChannelsFilterAny(MmGraph_t *graph, MmChannel_t *oc);
MmFilter_t *MmTryChannelsFilter(MmGraph_t *g, MmChannel_t *oc, const char *name, int32_t minrating);
MmFilter_t *MmFindStreamsFilter(MmGraph_t *g,AOIStream_t *sobj);
MmFilter_t *MmFindMimetypesFilter(MmGraph_t *g,const char *mimetype);
MmFilter_t *MmFindExtEncoder(MmGraph_t *graph,const char *ext);
MmFilter_t *MmFindFilter(MmGraph_t *g,const char *name);
int32_t MmSetOutputStream(MmFilter_t *f,AOIStream_t *sobj);

void MmPrintGraph(const MmFilter_t *f,int32_t level);
int32_t MmSetDefaultClock(MmGraph_t *g);
MmFilter_t *MmFindBufferedMediaReader(MmGraph_t *graph,AOIStream_t *sobj);
MmFilter_t *MmFindMediaReader(MmGraph_t *graph,AOIStream_t *sobj);
int32_t  MmFindMetadataReader( void  *obj, MmFilter_t  **mreader,  MediaMetadataReader **interface);
int32_t  MmFindMetadataParser( void  *obj, MmFilter_t  **mreader,  const MediaMetadataParser **interface);
int32_t  MmFindMetadata( void *obj, MmFilter_t **mreader, const MediaMetadataParser **interface, MmMetadata_t **md);
int32_t MmFindMetadataParserInterface( const AOIStream_t *sobj, const AOICtrl_t** ctrl, const MediaMetadataParser **interface );

MmChannel_t *MmAcquireOutputChannel(MmFilter_t *f,int32_t mtype);
MmChannel_t *MmAcquireNextOutputChannel(MmFilter_t *f,int32_t mtype, int32_t *cookie);
MmChannel_t *MmAcquireInputChannel(MmFilter_t *f,int32_t mtype);
MmTime_t MmGetDuration(MmGraph_t *graph);
MmTime_t MmGetClockPosition(MmGraph_t *graph, MmTime_t resolution);
int32_t  MmFindMetadataWriter( void  *element, MmFilter_t  **mwriter,  MediaMetadataWriter **interface);
int32_t MmSetGraphParams(MmGraph_t *graph, uint32_t params);
int32_t MmSetGraphString(MmGraph_t *graph, const char *name, const char *value);
uint32_t MmSetGraphMemoryLimit(MmGraph_t *graph, uint32_t limit);
int32_t MmGetGraphError(MmGraph_t *graph);
int32_t MmSetMediaReaderStream(void  *obj, AOIStream_t *sobj);

typedef enum
{
  MM_STATUS_ERROR       = 0x0001,
  MM_STATUS_TIMEOUT     = 0x0002,
  MM_STATUS_EOF         = 0x0004,
  MM_STATUS_STOPPING    = 0x0008,
  MM_STATUS_STOPPED     = 0x0010,
  MM_STATUS_PAUSING     = 0x0020,
  MM_STATUS_PAUSED      = 0x0040,
  MM_STATUS_PREFETCHING = 0x0080, 
  MM_STATUS_PLAYING     = 0x0100,
  MM_STATUS_SCANFWD     = 0x0200,
  MM_STATUS_SCANBWD     = 0x0400,
  MM_STATUS_INACTIVE    = 0x0800,
} MmStatus_t;


#define MM_STATUS_RUNMASK (MM_STATUS_PREFETCHING|MM_STATUS_PLAYING|MM_STATUS_PAUSING|MM_STATUS_PAUSED|MM_STATUS_SCANFWD|MM_STATUS_SCANBWD|MM_STATUS_EOF|MM_STATUS_ERROR)

#define MM_PRIORITY_SIZE 1
#define MM_PRIORITY_CPU 2
#define MM_PRIORITY_QUALITY 3

#define MM_NOADDONPATH "NOADDONPATH"

typedef void (MmEventPostF)(MmFilter_t*,MmEventType_t, const void*,size_t);

typedef void (MmEventNotifyF)(MmElement_t *producer,
	MmEventType_t type,
	const void *info,
	size_t ilen,
	void *cbdata);

typedef union {
	MmFilter_t		*filter;
	MmEventNotifyF	*callback;
} MmEventListener_t;

int MmEventList(MmElement_t *element, MmEventType_t *type, MmCookie_t *cookie);
int MmEventSubscribe(MmElement_t *element,
	MmEventType_t type,
	MmEventNotifyF *notify_f,
	void *cbdata);
int MmEventSubscriptionSetPriority(MmElement_t *producer,
	MmEventListener_t *listener,
	MmEventType_t type,
	MmEventPriority_t prio);

#ifdef __cplusplus
};
#endif

#endif

/* __SRCVERSION("mmedia.h $Rev: 718428 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/corelib/public/mmedia/mmedia.h $ $Rev: 718428 $")
#endif
