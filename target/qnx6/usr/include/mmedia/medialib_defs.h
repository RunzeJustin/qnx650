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



#ifndef __MEDIALIB_DEFS_H__
#define __MEDIALIB_DEFS_H__

#include <inttypes.h>
#include <sys/types.h>
#include <mmedia/media_error.h>
#include <mmedia/media_event.h>
#include <aoi/aoi_dataformat.h>

typedef int64_t MmTime_t;

struct media_memory_pool;

struct media_buffer
{
  struct media_memory_pool *mpool; /* the pool this buffer belongs to */
  iov_t          load;   /* buffer payload */
  off64_t        offset; /* offset or physical address of the buffer payload. */
};


/* MmMemoryFormat_t bsizeflag possible value */
typedef enum
{
  MM_BUFFER_SIZE_NEGOTIABLE = 0x01,
  MM_BUFFER_SIZE_FIXED      = 0x02,
  MM_MEMORY_FORMAT_FIXED    = 0x04,
} MmBufferSizeFlag_t;


typedef struct
{
	int32_t            bsize;        /* buffer size                        */
	int32_t            nbuffers;     /* number of buffers to use           */
	MmBufferSizeFlag_t bsizeflag;    /* buffer size flag                   */

  int32_t            aflags;       /* memory access flags (mmap flags)   */
  int32_t            cflags;       /* memory control flag (mmap flags)   */
  int32_t            fildes;       /* The file descriptor for a shared memory object, or NOFD if mapping physical memory */
  uint64_t           offset;       /* The offset for a shared memory object */
  uint32_t           step;         /* The step to increment offset by between buffers */
  int32_t            reserve;
} MmMemoryFormat_t;

/* the structure we use when we're setting up/negotiating formats */
typedef enum
{
  MM_STREAM_NATIVE_ENDIAN = 0,
  MM_STREAM_LITTLE_ENDIAN,
  MM_STREAM_BIG_ENDIAN
}MmEndian_t;

typedef struct MmFormat_t
{
  AODataFormat_t   mf;        /* media stream format description             */
  MmMemoryFormat_t mef;       /* memory type description (mmap flags,paddr ) */
  /* a couple of buffer constraints */
  int32_t          icmflags;  /* connecting input channel memory usage flags */
  int32_t          ocmflags;  /* source output channel memory usage flags    */
  uint64_t         duration;  /* duration in microseconds                    */
  uint32_t         bitrate;   /* input bitrate                               */
  MmEndian_t       etype;     /* the endianess of the stream                 */

  int32_t          seekable;  /* flags ex: MM_SEEK_TIME|MM_SEEK_BYTE         */
  int32_t          drm;       /* digital right management flags              */
  int32_t          sbrpresentflag;
  uint32_t         seek_latency; /* latency of a seek in microseconds.       */
                                 /* Used to indicate the relative expense of a seek. */
  uint32_t         extra_size;   /* size of extra data.  Usually decoder config */
  void *           extra_ptr;    /* pointer to the extra data.               */
}MmFormat_t;

typedef struct media_filter  MmFilter_t;
typedef struct media_clock   MmClock_t;
typedef struct media_channel MmChannel_t;
typedef struct media_graph   MmGraph_t;
typedef struct media_buffer  MmBuffer_t;

/* MmFormat_t icmflags or ocmflags possible values */
enum
{
  MM_MEMORY_SOURCE         = 0x01,  /* the filter  write data to the memory area */
  MM_MEMORY_SHARE          = 0x02,  /* the filter  parse the data in the  memory area ( reuse it ) */
  MM_MEMORY_SINK           = 0x04,  /* the filter consume the data in the memory area (end of a sub-graph) */
  MM_MEMORY_ALLOC_OVERRIDE = 0x08,  /* the filter want to take over the MediaMemoryAllocator interface */
};

typedef enum
{
	MM_AAC_MAIN_AUDIO_TYPE 		= 1,
	MM_AAC_LC_AUDIO_TYPE 		= 2,
	MM_AAC_SSR_AUDIO_TYPE		= 3,
	MM_AAC_LTP_AUDIO_TYPE 	 	= 4,
	MM_AAC_HE_AUDIO_TYPE  	 	= 5,
	MM_AAC_SCALABLE_AUDIO_TYPE 	= 6,
}MmAacProfile_t;

/* a enum describing possible graph level settable parameters (bitmask) */
typedef enum MmGraphParams
{
  MM_GRAPH_PARA_EXTRACT_METADATA = 0x01, /* The filter with the MediaMetadataReader interface should parse
                                            and hold on to the stream metadata */
} MmGraphParams_t;

typedef	int8_t		MmEventPriority_t;

typedef struct MmMetadata MmMetadata_t;
/* data structure used with the "Load On Demand"  Fourcc value: "RDOD"  */
typedef struct MmReadHandle MmReadHandle_t;
typedef struct MmMetaLoadInfo
{
  int32_t        fourcc;  /* a sequence of 4 bytes describing the type of the data to be read */
  uint64_t       minsize; /* the minimum size of the data, 0 if unknown  */
  uint64_t       maxsize; /* the maximum size of the data, UINT64_MAX if unknown */
  MmReadHandle_t *hdl;
  /* the ReadMetadata function:
   hdl   :  Context handle to the data to be read
   offset:  Zero or the number of bytes read so far. Other values may be unsupported
   buffer:  A pointer to a buffer where the function can store the data that it reads.
   buf_size:The size if the provided buffer
   min_read:Block until at least that many bytes are available.
            Typically will be 0, 1, or same as buf_size.
            Zero means don't block, return EAGAIN if no data is available
   nread:   Store the actual number of bytes read. There could be fewer than min_read on an error or EOF
   return MM_EOK on success or an error code */
  int32_t (*ReadMetadata)( MmReadHandle_t *hdl, uint64_t offset, void *buffer, size_t buf_size, size_t min_read, size_t *nread);
} MmMetaLoadInfo_t;

typedef struct MmMetadataInfo
{
  uint32_t     fourcc;
  uint64_t     size;
  const void   *data;
  MmMetadata_t *md;
} MmMetadataInfo_t;

#endif

/* __SRCVERSION("medialib_defs.h $Rev: 680336 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/corelib/public/mmedia/medialib_defs.h $ $Rev: 680336 $")
#endif
