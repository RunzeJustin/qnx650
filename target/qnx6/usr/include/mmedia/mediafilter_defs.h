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



#ifndef __MEDIAFILTER_DEFS_H__
#define __MEDIAFILTER_DEFS_H__

#include <mmedia/medialib_defs.h>
#include <aoi/aoi.h>
#include <sys/types.h>

typedef enum
{
  MM_ELEMENT_GRAPH   = 0x01,
  MM_ELEMENT_FILTER  = 0x02, 
  MM_ELEMENT_CHANNEL = 0x04
} MmElementType_t;

typedef	int32_t	MmCookie_t;

typedef struct
{
	MmElementType_t type;
	char            *ID;
} MmElement_t;

typedef struct media_memory_pool {
	const struct MediaMemoryAllocator *mmai;
} hMB_t, MmMemoryPool_t;

typedef struct media_channel_user         MmChannelUser_t;
typedef struct media_filter_user          MmFilterUser_t;
typedef struct media_filter_private       MmFilterPrivate_t;
typedef struct media_private              MmPrivate_t; 
typedef struct media_reference_array_pool hMRA_t;
typedef struct media_readlist_pool        hMRL_t;
typedef struct MediaRefArray              MediaRefArray_t;
typedef struct MediaReadList              MmReadList_t;
typedef struct media_format_change        MmFormatChange_t;
typedef struct media_renegotiation        MmReNegotiation_t;
typedef struct media_renegotiatior_data   MmReNegotiatorData_t;

/*
 * The MmFilter_t structure.
 */
struct media_filter
{
  MmElement_t     element;
  /* filled out by filter implementation */
  MmChannel_t     *ichannels;		/* input channels for this filter */
  MmChannel_t     *ochannels;		/* output channels for this filter */
  MmFilterUser_t  *user;			/* filter defined variables */
  /* filled out by media library */
  const AOICtrl_t	*interfaces;	/* interfaces for this filter */
  MmGraph_t       *graph;			/* graph this filter is in */
  MmFilterPrivate_t *fprv;
};


typedef enum
{
  MM_CHANNEL_INPUT  = 0x01,
  MM_CHANNEL_OUTPUT = 0x02
} MmChannelType_t;

/*
 * The MmChannel_t structure
 */
struct media_channel
{
	MmElement_t      element;
	MmChannelType_t  direction;	/* MM_CHANNEL_INPUT or MM_CHANNEL_OUTPUT */
	int32_t          flags;
	MmFormat_t       format;
	MmFilter_t       *filter;
	MmFormatChange_t *fc;
	MmPrivate_t      *mp;
	MmChannel_t      *lchannel;	/* channel this channel is attached to */
	MmChannel_t      *schannel;	/* input (in the same filter) that this output takes its buffers from */ 
	MmChannelUser_t	 *user;
};

/* various flags we can set in the channel->flags */
#define MM_CHANNEL_ACQUIRED  0x0000001
#define MM_CHANNEL_INPUTSET  0x0000002
#define MM_CHANNEL_STREAM    0x0000004  /* do we use a Streamer instead? */
#define MM_CHANNEL_OUTPUTSET 0x0000008
#define MM_CHANNEL_SNIFFER	 0x0000010	/* do we use the sniff interface to rate the input format ? */
#define MM_CHANNEL_PASSIVE   0x0000020  /* do not negotiate format. the channel accept whatever is available (queue) */ 

/*
 * Set your exclflags to MM_ALLOCATE_FILTER and one of MM_ALLOCATE_INPUT/OUTPUT
 * if that format needs to be allocated by your input or output filter. (The
 * MM_ALLOCATE_FILTER portion gives it its exclusivity, and the INPUT/OUTPUT
 * tells us who's to allocate.)
 */
#define MM_ALLOCATE_FILTER  0x00000001L
#define MM_ALLOCATE_INPUT   0x00000002L
#define MM_ALLOCATE_OUTPUT  0x00000004L

/* matchflags flags */
#define MM_ALLOCATE_VIDEO  0x00000008L
#define MM_ALLOCATE_SHARED 0x00000010L
#define MM_ALLOCATE_RAM    0x00000020L

/* buffer flags */
#define MM_BUFFER_SHARED	0x00000001L
#define MM_BUFFER_VIDEO		0x00000002L
#define MM_BUFFER_USER1		0x00000004L
#define MM_BUFFER_USER2		0x00000008L
#define MM_BUFFER_USER3		0x00000010L
#define MM_BUFFER_USER4		0x00000020L
#define MM_BUFFER_LE			0x00000040L
#define MM_BUFFER_KEYFRAME	0x00010000L

/* convenient endian dependent fourcc macro   */
/* #define MmFOURCC(a,b,c,d) ((a << 24) | (b << 16) | (c << 8) | d) */


/* for use in the "Version" interface */
#define MM_VERSION 100

#endif

/* __SRCVERSION("mediafilter_defs.h $Rev: 680336 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/corelib/public/mmedia/mediafilter_defs.h $ $Rev: 680336 $")
#endif
