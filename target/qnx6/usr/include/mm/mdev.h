/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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
#ifndef MEDIA_DEVICE_DATATYPE_H_
#define MEDIA_DEVICE_DATATYPE_H_

#include <stdint.h>
#include <unistd.h>
#include <devctl.h>

/*
 * same as defines in aoi_dataformat.h
 * */
enum {
    MDEV_MEDIA_IMAGE = 0x00000001,
    MDEV_MEDIA_VIDEO = 0x00000002,
    MDEV_MEDIA_AUDIO = 0x00000004,
};

typedef struct {
    uint32_t width;
    uint32_t height;
    uint16_t depth;
} mdev_image_format_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t depth;

    int32_t frame_rate;
    int32_t scale;
    int32_t duration;
} mdev_video_format_t;

typedef struct {
    uint32_t channels;
    uint32_t depth;

    int32_t frame_rate;
    int32_t scale;
    int32_t duration;
} mdev_audio_format_t;

/*
 * wrapper for all formats
 * */
typedef struct {
    uint32_t mtype;
    uint32_t fourcc;
    union {
        mdev_image_format_t image;
        mdev_audio_format_t audio;
        mdev_video_format_t video;
    };
} mdev_format_t;

typedef struct {
    uint32_t nstreams;   //number of sub-streams in the stream
    uint16_t pids[0];    //pids of the sub-streams
}mdev_stream_info_t;

#define MDEV_OPTIONFLAGS_ABSPTS 0x00000001   // The PTS values are absolute from CLOCK_MONOTONIC

enum {
    MDEV_PACKET_TYPE_STREAMINFO = 0,  //The packet contains mdev_stream_info_t
    MDEV_PACKET_TYPE_DATA    = 1,
    MDEV_PACKET_TYPE_FORMAT,
    MDEV_PACKET_TYPE_PTSDATA,         //The packet contains PTS and data, first 8 bytes is PTS
    MDEV_PACKET_TYPE_DECCFG,
    MDEV_PACKET_TYPE_OPTIONFLAGS,
};

/*
 * header of every read
 * */
typedef struct {
    uint32_t type;
    uint32_t len;
} mdev_pktheader_t;

#define mdev_pkt_mktype(type, pid)  ((((uint32_t)(pid)&0xFFFF)<<16)|((uint32_t)(type)&0xFFFF))
#define mdev_pkt_type(hdr)          ((hdr)->type&0xFFFF)
#define mdev_pkt_pid(hdr)           (((hdr)->type>>16)&0xFFFF)

#define MDEV_FOURCC(a,b,c,d) ((((uint32_t)a)<<24)|(((uint32_t)b)<<16)|(((uint32_t)c)<<8)|d)

#endif /* MEDIA_DEVICE_H_ */


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/streamers/mdev_streamer/public/mm/mdev.h $ $Rev: 736007 $")
#endif
