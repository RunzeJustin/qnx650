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



#if !defined(IOMEDIA_DEVCTL_H_INCLUDED)
#define IOMEDIA_DEVCTL_H_INCLUDED

#if !defined(IOMEDIA_TYPES_H_INCLUDED)
#include <iomedia/types.h>
#endif

#include <mm/types.h>
#include <devctl.h>

/* This will be defined in <devctl.h> as well */
#define _DCMD_IOMEDIA 0x0F

#define _DCMD_IOMEDIA_C(  maj, min )        ( (maj) << 5 | (min) )
#define _DCMD_IOMEDIA_N(  maj, min )        __DION(  _DCMD_IOMEDIA, _DCMD_IOMEDIA_C( maj, min ) )
#define _DCMD_IOMEDIA_T(  maj, min, type )  __DIOT(  _DCMD_IOMEDIA, _DCMD_IOMEDIA_C( maj, min ), type )
#define _DCMD_IOMEDIA_F(  maj, min, type )  __DIOF(  _DCMD_IOMEDIA, _DCMD_IOMEDIA_C( maj, min ), type )
#define _DCMD_IOMEDIA_TF( maj, min, type )  __DIOTF( _DCMD_IOMEDIA, _DCMD_IOMEDIA_C( maj, min ), type )

#define _DCMD_IOMEDIA_MAJ( dcmd ) ( ( get_device_command(dcmd) ^ __DION( _DCMD_IOMEDIA, 0 ) ) >> 5 )
#define _DCMD_IOMEDIA_MIN( dcmd ) ( get_device_command(dcmd) & ~( ~0U << 5 ) )

enum _dcmd_iomedia_major {
	_DCMD_IOMEDIA_GENERAL,
	_DCMD_IOMEDIA_AUDIO,
	_DCMD_IOMEDIA_FILE,
	_DCMD_IOMEDIA_NAVIGATOR,
	_DCMD_IOMEDIA_DVD,
	_DCMD_IOMEDIA_VIDEO,
	_DCMD_IOMEDIA_AUDIO_INPUT,
	_DCMD_IOMEDIA_MAJOR_MAX
};

/*
 * General graph interface 
 */
#define DCMD_IOMEDIA_GRAPHOPTIONS      _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_GENERAL,  0, _Uint32t )
#define DCMD_IOMEDIA_ATTACHINPUT       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL,  1, char * )
#define DCMD_IOMEDIA_DETACHINPUT       _DCMD_IOMEDIA_N(  _DCMD_IOMEDIA_GENERAL,  2 )
#define DCMD_IOMEDIA_SETRESOURCE       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL,  3, struct iom_resource_hdr )
#define DCMD_IOMEDIA_GETRESOURCE       _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_GENERAL,  4, struct iom_resource_hdr )
struct iom_resource_hdr {
	_Uint32t name_len;
	_Uint32t data_len;
};
#define DCMD_IOMEDIA_CTRLMSG           _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_GENERAL,  5, struct iom_ctrl_msg_dcmd )
struct iom_ctrl_msg_dcmd {
	_Uint32t msg_len;
	_Uint32t reply_len;
};
#define DCMD_IOMEDIA_PLAY              _DCMD_IOMEDIA_N(  _DCMD_IOMEDIA_GENERAL,  6 )
#define DCMD_IOMEDIA_STOP              _DCMD_IOMEDIA_N(  _DCMD_IOMEDIA_GENERAL,  7 )
#define DCMD_IOMEDIA_GETTIME           _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL,  8, iom_graph_time_t )
#define DCMD_IOMEDIA_GETSTATUS         _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL,  9, iom_graph_status_t )
#define DCMD_IOMEDIA_SENDCOMMAND       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 10, _Int32t )
#define DCMD_IOMEDIA_SETSPEED          _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 11, _Int32t )
#define DCMD_IOMEDIA_SETNOTIFICATION   _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 12, _Uint32t )
#define DCMD_IOMEDIA_GETNOTIFICATION   _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL, 13, _Uint32t )
#define DCMD_IOMEDIA_SEEKTIME          _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 14, struct iom_seek_time_dcmd )
struct iom_seek_time_dcmd {
	_Uint64t        milliseconds;
	_Uint64t        track_id;
};
#define DCMD_IOMEDIA_SETTRANSITION     _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 15, iom_track_transition_t )
#define DCMD_IOMEDIA_GETTRANSITION     _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL, 16, iom_track_transition_t )
#define DCMD_IOMEDIA_GETERROR          _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL, 17, iom_error_info_t )
#define DCMD_IOMEDIA_GETTRKINFO        _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_GENERAL, 18, struct iom_track_info_dcmd )
enum iom_track_info_part_index {
	IOM_TRKINFO_INDEX_METADATA =  0,
	IOM_TRKINFO_INDEX_AUDIO    =  1,
	IOM_TRKINFO_INDEX_VIDEO    =  2,
	IOM_TRKINFO_INDEX_IMAGES   =  3,
	IOM_TRKINFO_MAX_PARTS      = 16,
};
struct iom_track_info_dcmd {
	_Uint64t        track_id;
	_Uint32t        datasize;
	_Uint32t        totalsize;
	_Uint32t        string_bitmask;
	_Uint16t        sizetab[ IOM_TRKINFO_MAX_PARTS ];
	_Uint16t        cnttab[ IOM_TRKINFO_MAX_PARTS ];
};

#define DCMD_IOMEDIA_GETEXTENTS        _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL, 19, struct iom_get_extents_dcmd ) 
struct iom_get_extents_dcmd {
    _Uint64t earliest;
    _Uint64t latest;
};
#define DCMD_IOMEDIA_GETBUFFERINGSTATUS _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_GENERAL, 20, _Uint32t ) 
#define DCMD_IOMEDIA_CAPABILITIES       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 21, struct iom_graph_capabilities_dcmd )
struct iom_graph_capabilities_dcmd {
	_Uint32t enable;
	_Uint32t disable;
};

#define DCMD_IOMEDIA_GETIMAGEURL       _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_GENERAL, 22, struct iom_get_image_url_dcmd )
struct iom_get_image_url_dcmd {
	_Uint32t image_id;
	_Uint32t buf_len;
};
#define DCMD_IOMEDIA_LOADIMAGE         _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 23, struct iom_load_image_dcmd )
struct iom_load_image_dcmd {
	_Uint32t image_id;
	_Uint32t load_id;
};
#define DCMD_IOMEDIA_UNLOADIMAGE       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 24, struct iom_load_image_dcmd )
#define DCMD_IOMEDIA_SAVEIMAGE         _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_GENERAL, 25, struct iom_load_image_dcmd )


/*
 * Audio interface 
 */
#define DCMD_IOMEDIA_ATTACHOUTPUT      _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_AUDIO, 0, struct iom_attach_output_dcmd )
struct iom_attach_output_dcmd {
	uint32_t flags;
	char device[ 4 ]; /* Really longer */
};
#define DCMD_IOMEDIA_DETACHOUTPUT      _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_AUDIO, 1, _Int32t )
#define DCMD_IOMEDIA_SETVOLUME         _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_AUDIO, 2, struct iom_audio_volume_dcmd )
struct iom_audio_volume_dcmd {
	_Int32t         output_id;
	iom_audio_volume_t vol;
};
#define DCMD_IOMEDIA_GETVOLUME         _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_AUDIO, 3, struct iom_audio_volume_dcmd )

/*
 * File writer interface 
 */
#define DCMD_IOMEDIA_SETOUTPUTFILE     _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_FILE, 0, char *[2] )
#define DCMD_IOMEDIA_SETMETADATA       _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_FILE, 1, struct iom_set_metadata_dcmd )
struct iom_set_metadata_dcmd {
	_Uint16t   release_year;
	_Uint8t    release_month;
	_Uint8t    release_mday;
	_Uint16t   track_num;
	_Uint16t   disc_num;
	char       strings[ 1 ];
};

/*
 * Video interface 
 */
#define DCMD_IOMEDIA_JUMPFRAMES         _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_VIDEO, 0, _Int32t )
#define DCMD_IOMEDIA_GETVIDEOSTATUS     _DCMD_IOMEDIA_F( _DCMD_IOMEDIA_VIDEO, 1, mm_video_status_t )
#define DCMD_IOMEDIA_SETVIDEOPROPERTIES _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_VIDEO, 2, mm_video_properties_t )
#define DCMD_IOMEDIA_GETVIDEOINFO       _DCMD_IOMEDIA_F( _DCMD_IOMEDIA_VIDEO, 3, mm_video_info_t )

/*
 * Navigator interface 
 */
#define DCMD_IOMEDIA_SETDEVICE         _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_NAVIGATOR, 0, char* )
#define DCMD_IOMEDIA_GETDEVICEINFO     _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_NAVIGATOR, 1, iom_device_info_t )
#define DCMD_IOMEDIA_GETTITLEINFO      _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_NAVIGATOR, 2, struct iom_title_info_dcmd )
struct iom_title_info_dcmd {
	_Uint16t title;
	_Uint16t padding1;
	_Uint32t padding2;
	iom_title_info_t info;
};
#define DCMD_IOMEDIA_GETCHAPTERINFO    _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_NAVIGATOR, 3, struct iom_chapter_info_dcmd )
struct iom_chapter_info_dcmd {
	_Uint16t title;
	_Uint16t chapter;
	_Uint32t padding;
	iom_chapter_info_t info;
};
#define DCMD_IOMEDIA_SEEKTITLE         _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_NAVIGATOR, 4, struct iom_seek_chapter_dcmd )

#define DCMD_IOMEDIA_SEEKCHAPTER       _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_NAVIGATOR, 5, struct iom_seek_chapter_dcmd )
struct iom_seek_chapter_dcmd {
	_Uint64t        milliseconds;
	_Uint16t        title;
	_Uint16t        chapter;
};
#define DCMD_IOMEDIA_GETCHAPTERTIME    _DCMD_IOMEDIA_F( _DCMD_IOMEDIA_NAVIGATOR, 6, struct iom_chapter_time_dcmd )
struct iom_chapter_time_dcmd {
	iom_graph_time_t  time;
	iom_chapter_time_t chapter;
};
#define DCMD_IOMEDIA_SAVESTATE  	   _DCMD_IOMEDIA_F( _DCMD_IOMEDIA_NAVIGATOR, 7, void* )
#define DCMD_IOMEDIA_RESTORESTATE      _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_NAVIGATOR, 8, void* )

/*
 * DVD interface 
 */
#define DCMD_IOMEDIA_GETANGLEINFO      _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_DVD, 0, mm_video_angle_info_t )
#define DCMD_IOMEDIA_GETAUDIOINFO      _DCMD_IOMEDIA_TF( _DCMD_IOMEDIA_DVD, 1, mm_video_audio_info_t )
#define DCMD_IOMEDIA_GETSUBTITLEINFO   _DCMD_IOMEDIA_F( _DCMD_IOMEDIA_DVD, 2, mm_video_subtitle_info_t )
#define DCMD_IOMEDIA_SETANGLE          _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_DVD, 3, struct iom_set_angle_dcmd )
struct iom_set_angle_dcmd {
	uint32_t title;  /* title or fid */
	int32_t index;
};
#define DCMD_IOMEDIA_SETAUDIO          _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_DVD, 4, struct iom_set_title_index_dcmd )
struct iom_set_title_index_dcmd {
	int32_t title;
	int32_t index;
};
#define DCMD_IOMEDIA_SETSUBTITLE       _DCMD_IOMEDIA_T(  _DCMD_IOMEDIA_DVD, 5, struct iom_set_title_index_dcmd )
#define DCMD_IOMEDIA_GETDVDSTATUS      _DCMD_IOMEDIA_F(  _DCMD_IOMEDIA_DVD, 6, mm_dvd_status_t )


/*
 * Audio input interface 
 */
#define DCMD_IOMEDIA_SETINPUTDEVICE    _DCMD_IOMEDIA_T( _DCMD_IOMEDIA_AUDIO_INPUT, 0, char* )

#endif


/* __SRCVERSION("dcmd_io-media.h $Rev: 216387 $"); */

