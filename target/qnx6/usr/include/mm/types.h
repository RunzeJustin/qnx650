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



#if !defined(_MULTIMEDIA_TYPES_H_INCLUDED)
#define _MULTIMEDIA_TYPES_H_INCLUDED

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif 


typedef enum mm_button {
	MM_BUTTON_NEXT,
	MM_BUTTON_PREV,
	MM_BUTTON_TOP,

	MM_BUTTON_CURSOR_LEFT,
	MM_BUTTON_CURSOR_RIGHT,
	MM_BUTTON_CURSOR_UP,
	MM_BUTTON_CURSOR_DOWN,

	MM_BUTTON_ENTER,
	MM_BUTTON_RETURN,
	MM_BUTTON_GOUP,

	MM_BUTTON_MENU_TITLE,
	MM_BUTTON_MENU_ROOT,
	MM_BUTTON_MENU_AUDIO,
	MM_BUTTON_MENU_ANGLE,
	MM_BUTTON_MENU_SUBTITLE,
	MM_BUTTON_MENU_PTT,

	MM_BUTTON_REPEAT_AB_OFF,
	MM_BUTTON_REPEAT_AB_POINT_A,
	MM_BUTTON_REPEAT_AB_POINT_B,

	MM_BUTTON_REPEAT_OFF,
	MM_BUTTON_REPEAT_CHAPTER,
	MM_BUTTON_REPEAT_TITLE,
	MM_BUTTON_REPEAT_DISC,

	MM_BUTTON_RESUME,
	MM_BUTTON_FRAME_ADVANCE,
	MM_BUTTON_FRAME_REVERSE,
	MM_BUTTON_PAUSE,
	
	MM_BUTTON_PLAY,
	MM_BUTTON_STOP,

	MM_BUTTON_0, MM_BUTTON_1, MM_BUTTON_2, MM_BUTTON_3, MM_BUTTON_4,
	MM_BUTTON_5, MM_BUTTON_6, MM_BUTTON_7, MM_BUTTON_8, MM_BUTTON_9,
	MM_BUTTON_99 = MM_BUTTON_0 + 99,
	/* More TBD */
} mm_button_t;
  

#define MM_CODEC_NAME_MAX_LEN  (32) 

#define MM_MAX_VIDEO_SUBTITLES			32
#define MM_MAX_VIDEO_AUDIO_STREAMS		8

typedef struct mm_video_angle_info {
	uint32_t     title; /* title angle info provided for */
	uint8_t      total;  /* number of video angles available */
	int8_t       current;  
	int8_t	     angles_available; /* bool, clear if changing angles will have no effect on the current chapter */
	int8_t	     align; /* align struct to 32bits */
} mm_video_angle_info_t;

typedef enum mm_subpict_lang_ext {
	MM_CAPTION_NOT_SPECIFIED = 0,
	MM_CAPTION_NORMAL,
	MM_CAPTION_LARGE,
	MM_CAPTION_CHILDRENS,
	MM_CLOSED_CAPTION_NORMAL = 5,
	MM_CLOSED_CAPTION_LARGE,
	MM_CLOSED_CAPTION_CHILDRENS,
	MM_CAPTION_FORCED = 9,
	MM_DIRECTORS_COMMENT_NORMAL = 13,
	MM_DIRECTORS_COMMENT_LARGE,
	MM_DIRECTORS_COMMENT_CHILDREN,
} mm_subpict_lang_ext_t;
	
#define	NOT_SPECIFIED               MM_CAPTION_NOT_SPECIFIED     /* Deprecated, use MM_CAPTION_NOT_SPECIFIED */
#define	CAPTION_NORMAL              MM_CAPTION_NORMAL            /* Deprecated, use MM_CAPTION_NORMAL */
#define	CAPTION_LARGE               MM_CAPTION_LARGE             /* Deprecated, use MM_CAPTION_LARGE */
#define	CAPTION_CHILDRENS           MM_CAPTION_CHILDRENS         /* Deprecated, use MM_CAPTION_CHILDRENS */
#define	CLOSED_CAPTION_NORMAL       MM_CLOSED_CAPTION_NORMAL     /* Deprecated, use MM_CLOSED_CAPTION_NORMAL */
#define	CLOSED_CAPTION_LARGE        MM_CLOSED_CAPTION_LARGE      /* Deprecated, use MM_CLOSED_CAPTION_LARGE */
#define	CLOSED_CAPTION_CHILDRENS    MM_CLOSED_CAPTION_CHILDRENS  /* Deprecated, use MM_CLOSED_CAPTION_CHILDRENS */
#define	CAPTION_FORCED              MM_CAPTION_FORCED            /* Deprecated, use MM_CAPTION_FORCED */
#define	DIRETORS_COMMENT_NORMAL     MM_DIRECTORS_COMMENT_NORMAL  /* Deprecated, use MM_DIRECTORS_COMMENT_NORMAL */
#define	DIRECTORS_COMMENT_LARGE     MM_DIRECTORS_COMMENT_LARGE   /* Deprecated, use MM_DIRECTORS_COMMENT_LARGE */
#define	DIRECTORS_COMMENT_CHILDREN  MM_DIRECTORS_COMMENT_CHILDREN/* Deprecated, use MM_DIRECTORS_COMMENT_CHILDREN */

typedef struct mm_video_subtitle_info {
	uint32_t        title; /* title subtitle info provided for */
 	uint8_t          total; /* number of available subtittles */
	int8_t          current;	/* 0...total-1, or -1 for "none" */
	struct mm_video_subtitle_attr {
		char            lang[2];  /* language codes per ISO 639-1 */
		uint8_t         ext;        /* language extension codes from subpict_lang_ext enum */
	} attr[MM_MAX_VIDEO_SUBTITLES];
} mm_video_subtitle_info_t;

typedef enum mm_audio_lang_ext {
	MM_LANG_EXT_CAPTIONS_NORMAL = 1,
	MM_LANG_EXT_VISUAL_IMPARED_AUDIO,
	MM_LANG_EXT_DIRECTORS_COMMENTS1,
	MM_LANG_EXT_DIRECTORS_COMMENTS2,
} mm_audio_lang_ext_t;

#define	CAPTIONS_NORMAL      MM_LANG_EXT_CAPTIONS_NORMAL         /* Deprecated, use MM_LANG_EXT_CAPTIONS_NORMAL */
#define	VISUAL_IMPARED_AUDIO MM_LANG_EXT_VISUAL_IMPARED_AUDIO/* Deprecated, use MM_LANG_EXT_VISUAL_IMPARED_AUDIO */
#define	DIRECTORS_COMMENTS1  MM_LANG_EXT_DIRECTORS_COMMENTS1  /* Deprecated, use MM_LANG_EXT_DIRECTORS_COMMENTS1 */
#define	DIRECTORS_COMMENTS2  MM_LANG_EXT_DIRECTORS_COMMENTS2  /* Deprecated, use MM_LANG_EXT_DIRECTORS_COMMENTS2 */

typedef struct mm_language_defaults {
	char menu_language[2];      /* language codes per ISO 639-1 */
	char subtitle_language[2];  /* language codes per ISO 639-1 */
	char audio_language[2];     /* language codes per ISO 639-1 */
	uint8_t subtitle_extensions;/* from mm_subpict_lang_ext     */
	uint8_t audio_extensions;   /* from mm_audio_lang_ext       */
} mm_language_defaults_t;

enum mm_audio_type { /* Deprecated */
	DOLBY_AC3 = 0,
	MPEG_1_2 = 2,
	MPEG_2_EXT = 3,
	LINEAR_PCM = 4,
	DTS = 6,
	SDDS = 7,
	STEREO,
	MONO,
	JOINT_STEREO,
	DUAL_CHANNEL,
	OTHER = 255
};

typedef struct mm_video_audio_info {
  uint32_t        title; /* title audio stream info provided for */
  int8_t          total; /* number of available audio streams    */
  int8_t          current; /* audio stream currently selected */
  struct mm_audio_attr {
    char          lang[2]; /* language codes per ISO 639-1 */
    uint8_t       ext;  /* language extension from audio_lang_ext enum */
    uint8_t       type; /* value as per mm_audio_types enum */
    uint8_t       channels; /* number of channels (8 = 7.1, 6 = 5.1, 3 = 2.1, 4 = 4, 2 = 2, 1 = 1, 255 = unknown) */
    uint8_t       spare;
    uint32_t      channel_configuration;  /* channel connection bitmask, use macro near mm_audio_info_t */
    uint32_t      reserve[4];             /* spare for future                      */
  } attr[MM_MAX_VIDEO_AUDIO_STREAMS];
} mm_video_audio_info_t;



typedef enum display_mode {
	MM_DISPLAY_MODE_NORMAL, 
 	MM_DISPLAY_MODE_LETTERBOX, 
	MM_DISPLAY_MODE_PANSCAN,	
	MM_DISPLAY_MODE_OPEN_MATTE,
} mm_display_mode_t;

#define	DISPLAY_MODE_NORMAL      MM_DISPLAY_MODE_NORMAL      /* Deprecated, use MM_DISPLAY_MODE_NORMAL */
#define	DISPLAY_MODE_LETTERBOX   MM_DISPLAY_MODE_LETTERBOX   /* Deprecated, use MM_DISPLAY_MODE_LETTERBOX */
#define	DISPLAY_MODE_PANSCAN     MM_DISPLAY_MODE_PANSCAN     /* Deprecated, use MM_DISPLAY_MODE_PANSCAN */	
#define	DISPLAY_MODE_OPEN_MATTE  MM_DISPLAY_MODE_OPEN_MATTE  /* Deprecated, use MM_DISPLAY_MODE_OPEN_MATTE */
typedef enum capture_format_enum {
	MM_CAPTURE_NTSC,
	MM_CAPTURE_PAL,
	MM_CAPTURE_OTHER,
} capture_format_t;

#define	CAPTURE_NTSC  MM_CAPTURE_NTSC  /*Deprecated, use MM_CAPTURE_NTSC */
#define	CAPTURE_PAL   MM_CAPTURE_PAL   /*Deprecated, use MM_CAPTURE_PAL */
#define	CAPTURE_OTHER MM_CAPTURE_OTHER /*Deprecated, use MM_CAPTURE_OTHER */

/* mm_video_info flags */
#define MM_VIDEO_SOURCE_CROP    0x00000001    /* source rect in video_properties does not need to equal the video w/h from video info */
#define MM_VIDEO_SCALEABLE      0x00000002 /* video player supports scaling */
                          /* if not set, the video_width and video_height members describe the active video size */
#define MM_VIDEO_FRAME_SETABLE  0x00000004  /* implementation allows the frame size to be specified */
#define MM_VIDEO_SOURCE_LETTERBOXED	0x00000008 /* content indicates source 4:3 picture is actually 16:9 with black bars  */
#define MM_VIDEO_AUTO_SCALED    0x00000010 /* video is being scaled to best fit the frame described in mm_video_info */

typedef struct mm_video_info {
	struct {
		uint16_t w;
		uint16_t h;
	} aspect_ratio;
	uint32_t	width; /*  width of the video source */
	uint32_t	height;/*  height of the video source */
	uint32_t	capture_format;
        uint32_t	frame_rate;//in Hz
	uint32_t	frame_width; /*  size of frame delivered to graphics port (may be different from video w/h) */
	uint32_t	frame_height;/*  differening values does not imply scaling -- see video flags. */
	uint32_t	max_bufferable_frames; 
	uint32_t    display_mode;
	uint32_t	flags;
	char		codec[32];
	/* more tbd.., */
} mm_video_info_t;

/*  we are considering making video_status just be a mm_video_info_t. */
typedef struct mm_video_status {
	uint32_t	width;
	uint32_t	height;
	struct {
		uint16_t w;
		uint16_t h;
	} aspect_ratio;
} mm_video_status_t;

typedef struct mm_video_format {
	uint32_t      width;
	uint32_t      height;
	struct {
		uint16_t w;
		uint16_t h;
	} aspect_ratio;
	char          codec[MM_CODEC_NAME_MAX_LEN];
	uint32_t      framerate;   /* in Hz */
} mm_video_format_t;

/*
 * mm_video_properties flags
 */
#define MM_AUTO_SCALE         0x00000001 /*  if supported, scaling is automatic otherwise source and dest are used to perform crop/scale... */
#define MM_SET_VID_FRAME_SIZE 0x00000002 /*  frame width and height used to set frame size, otherwise width and height are ignored */
#define MM_SET_FRAME_BUFFERS  0x00000004 /*  frame_buffers used to set number of video frames to buffer, otherwise frame_buffers is ignored */
#define MM_SET_DISPLAY_MODE   0x00000008 /*  This should only be used in conjunction with MM_AUTO_SCALE */
#define MM_SOURCE_IS_RELATIVE 0x00000010 /*  The source rectangle is in units of 1/1000 of the frame rather than pixels */

typedef struct mm_video_properties {
	uint32_t           flags;
	struct {
		uint32_t  left,top,right,bottom; /*  top, left, bottom, and right boundries of source viewport */
	} source; /*  muse be a subset of the rectangle described by the source width and height given by mm_video_info */
	struct {
		uint32_t  left,top,right,bottom; /*  top, left, bottom, and right boundries of dest viewport */
	} dest; /*  must be within the rectangle described by 0,0,frame_width-1,frame_height-1 (frame w/h given by mm_video_info)  */
	uint32_t   frame_width;	
	uint32_t   frame_height;
	uint32_t   frame_buffers;
	uint32_t   display_mode;
		
	/* more tbd.., */
} mm_video_properties_t;





typedef enum mm_blocked_uops{
  UOP_BLOCK_NONE = 0, UOP_BLOCK_TIME_PLAY_SEARCH = (1 << 0), UOP_BLOCK_PTT_PLAY_SEARCH = (1 << 1), UOP_BLOCK_TITLE_PLAY = (1 << 2),
  UOP_BLOCK_STOP = (1 << 3), UOP_BLOCK_GO_UP = (1 << 4), UOP_BLOCK_TIME_PTT_SEARCH = (1 << 5), UOP_BLOCK_PREV_TOP_PG_SEARCH = (1 << 6),
  UOP_BLOCK_NEXT_PG_SEARCH = (1 << 7), UOP_BLOCK_FORWARD_SCAN = (1 << 8), UOP_BLOCK_BACKWARD_SCAN = (1 << 9), UOP_BLOCK_MENU_CALL_TITLE = (1 << 10),
  UOP_BLOCK_MENU_CALL_ROOT = (1 << 11), UOP_BLOCK_MENU_CALL_SUB_PICTURE = (1 << 12), UOP_BLOCK_MENU_CALL_AUDIO = (1 << 13), UOP_BLOCK_MENU_CALL_ANGLE = (1 << 14),
  UOP_BLOCK_MENU_CALL_PTT = (1 << 15), UOP_BLOCK_RESUME = (1 << 16), UOP_BLOCK_BUTTON = (1 << 17), UOP_BLOCK_STILL_OFF = (1 << 18),
  UOP_BLOCK_PAUSE_ON = (1 << 19), UOP_BLOCK_AUDIO_CHANGE = (1 << 20), UOP_BLOCK_SUB_PICTURE_CHANGE = (1 << 21), UOP_BLOCK_ANGLE_CHANGE = (1 << 22),
  UOP_BLOCK_KARAOKE_CHANGE = (1 << 23), UOP_BLOCK_VIDEO_CHANGE = (1 << 24)
} mm_blocked_uops_t;

typedef enum mm_dvd_domain {
	MM_DVD_DOMAIN_STOP = 1,  /* DVD is not playing */
	MM_DVD_DOMAIN_FP,        /* FIRST PLAY -- optional initialization domain */
	MM_DVD_DOMAIN_VMGM,      /* Video Manage Menu Domain, optional, The Title menu operate in this domain, as well as legal notices/warnings and occasionally previews */
	MM_DVD_DOMAIN_VTSM,      /* Video Title Set Menu Domain, optional, 
								most menus operate in this domain {ROOT menu, PTT (chapter selection) menu, Audio Menu, Sub-Picture (subtitles) Menu, and Angle Menu} */
	MM_DVD_DOMAIN_TT         /* Title Domain, manditory, previews, main feature, etc. usually in standard (playback) mode */
} mm_dvd_domain_t;

#define	DOMAIN_STOP  MM_DVD_DOMAIN_STOP /* DVD is not playing */
#define	DOMAIN_FP    MM_DVD_DOMAIN_FP   /* FIRST PLAY -- optional initialization domain */
#define	DOMAIN_VMGM  MM_DVD_DOMAIN_VMGM /* Video Manage Menu Domain, optional, The Title menu operate in this domain, as well as legal notices/warnings and occasionally previews */
#define	DOMAIN_VTSM  MM_DVD_DOMAIN_VTSM /* Video Title Set Menu Domain, optional, 
									     Most menus operate in this domain {ROOT menu, PTT (chapter selection) menu, Audio Menu, Sub-Picture (subtitles) Menu, and Angle Menu} */
#define	DOMAIN_TT    MM_DVD_DOMAIN_TT   /* Title Domain, manditory, previews, main feature, etc. usually in standard (playback) mode */
	
typedef enum mm_uop {
	MM_UOP_CLOSE,
	MM_UOP_GET_BOOKMARK,
	MM_UOP_SET_BOOKMARK,
	MM_UOP_GET_SPRMS,
	MM_UOP_GET_GPRMS,
	MM_UOP_SET_GPRM,

	MM_UOP_STOP,
	MM_UOP_GO_UP,
	MM_UOP_PREV_PG_SEARCH,
	MM_UOP_TOP_PG_SEARCH,
	MM_UOP_NEXT_PG_SEARCH,
	MM_UOP_SET_SPEED,
	MM_UOP_FRAME_ADVANCE,
	MM_UOP_FRAME_REVERSE,
	MM_UOP_RESUME,
	MM_UOP_UPPER_BUTTON_SELECT,
	MM_UOP_LOWER_BUTTON_SELECT,
	MM_UOP_LEFT_BUTTON_SELECT,
	MM_UOP_RIGHT_BUTTON_SELECT,
	MM_UOP_BUTTON_ACTIVATE,
	MM_UOP_BUTTON_SELECT_AND_ACTIVATE,
	MM_UOP_STILL_OFF,
	MM_UOP_PAUSE_ON,
	MM_UOP_PAUSE_OFF,
	MM_UOP_MENU_LANGUAGE_SELECT,
	MM_UOP_AUDIO_STREAM_CHANGE,
	MM_UOP_SUB_PICTURE_STREAM_CHANGE,
	MM_UOP_ANGLE_CHANGE,
	MM_UOP_VIDEO_MODE_CHANGE,

	MM_UOP_BUTTON_SELECT,
	MM_UOP_BUTTON_SELECT_POINT,
	MM_UOP_BUTTON_ACTIVATE_POINT,
	MM_UOP_SUB_PICTURE_STREAM_CHANGE_STREAM,
	MM_UOP_SUB_PICTURE_STREAM_CHANGE_DISPLAY,
	MM_UOP_AUDIO_LANGUAGE_SELECT,
	MM_UOP_SUB_PICTURE_LANGUAGE_SELECT,
	MM_UOP_REPEAT_MODE_CHANGE,
	MM_UOP_TITLE_PLAY,
	MM_UOP_PTT_PLAY,
	MM_UOP_TITLE_TIME_PLAY,
	MM_UOP_TITLE_TIME_SEARCH,
	MM_UOP_PTT_SEARCH,
	MM_UOP_MENU_CALL_VIDEO,
	MM_UOP_PARENTAL_LEVEL_SELECT,
	MM_UOP_PARENTAL_COUNTRY_SELECT,
	MM_UOP_KARAOKE_MODE_CHANGE,
	MM_UOP_PTT_PLAY_RANGE,
	MM_UOP_TITLE_TIME_PLAY_RANGE,
	MM_UOP_FIRST_PLAY,
	MM_UOP_TITLE_GROUP_PLAY,
	MM_UOP_TRACK_PLAY,
	MM_UOP_GROUP_TIME_PLAY,
	MM_UOP_GROUP_TIME_SEARCH,
	MM_UOP_TRACK_SEARCH,
	MM_UOP_PREV_TK_SEARCH,
	MM_UOP_TOP_TK_SEARCH,
	MM_UOP_NEXT_TK_SEARCH,
	MM_UOP_PREV_DLIST_SEARCH,
	MM_UOP_NEXT_DLIST_SEARCH,
	MM_UOP_HOME_DLIST_SEARCH,
	MM_UOP_MENU_CALL_AUDIO,
	MM_UOP_TEXT_LANGUAGE_SELECT,
	MM_UOP_HIDDEN_GROUP_PLAY,
	MM_UOP_HIDDEN_TRACK_PLAY,
	MM_UOP_HIDDEN_TIME_PLAY,
} mm_uop_t;

/* deprecated versions of mm_uop_t values */
#define UOP_CLOSE                    MM_UOP_CLOSE
#define UOP_GET_BOOKMARK             MM_UOP_GET_BOOKMARK
#define UOP_SET_BOOKMARK             MM_UOP_SET_BOOKMARK
#define UOP_GET_SPRMS                MM_UOP_GET_SPRMS
#define UOP_GET_GPRMS                MM_UOP_GET_GPRMS
#define UOP_SET_GPRM                 MM_UOP_SET_GPRM
#define UOP_STOP                     MM_UOP_STOP
#define UOP_GO_UP                    MM_UOP_GO_UP
#define UOP_PREV_PG_SEARCH           MM_UOP_PREV_PG_SEARCH
#define UOP_TOP_PG_SEARCH            MM_UOP_TOP_PG_SEARCH
#define UOP_NEXT_PG_SEARCH           MM_UOP_NEXT_PG_SEARCH
#define UOP_SET_SPEED                MM_UOP_SET_SPEED
#define UOP_FRAME_ADVANCE            MM_UOP_FRAME_ADVANCE
#define UOP_FRAME_REVERSE            MM_UOP_FRAME_REVERSE
#define UOP_RESUME                   MM_UOP_RESUME
#define UOP_UPPER_BUTTON_SELECT      MM_UOP_UPPER_BUTTON_SELECT
#define UOP_LOWER_BUTTON_SELECT      MM_UOP_LOWER_BUTTON_SELECT
#define UOP_LEFT_BUTTON_SELECT       MM_UOP_LEFT_BUTTON_SELECT
#define UOP_RIGHT_BUTTON_SELECT      MM_UOP_RIGHT_BUTTON_SELECT
#define UOP_BUTTON_ACTIVATE          MM_UOP_BUTTON_ACTIVATE
#define UOP_BUTTON_SELECT_AND_ACTIVATE MM_UOP_BUTTON_SELECT_AND_ACTIVATE
#define UOP_STILL_OFF                MM_UOP_STILL_OFF
#define UOP_PAUSE_ON                 MM_UOP_PAUSE_ON
#define UOP_PAUSE_OFF                MM_UOP_PAUSE_OFF
#define UOP_MENU_LANGUAGE_SELECT     MM_UOP_MENU_LANGUAGE_SELECT
#define UOP_AUDIO_STREAM_CHANGE      MM_UOP_AUDIO_STREAM_CHANGE
#define UOP_SUB_PICTURE_STREAM_CHANGE MM_UOP_SUB_PICTURE_STREAM_CHANGE
#define UOP_ANGLE_CHANGE             MM_UOP_ANGLE_CHANGE
#define UOP_VIDEO_MODE_CHANGE        MM_UOP_VIDEO_MODE_CHANGE
#define UOP_BUTTON_SELECT            MM_UOP_BUTTON_SELECT
#define UOP_BUTTON_SELECT_POINT      MM_UOP_BUTTON_SELECT_POINT
#define UOP_BUTTON_ACTIVATE_POINT MM_UOP_BUTTON_ACTIVATE_POINT
#define UOP_SUB_PICTURE_STREAM_CHANGE_STREAM MM_UOP_SUB_PICTURE_STREAM_CHANGE_STREAM
#define UOP_SUB_PICTURE_STREAM_CHANGE_DISPLAY MM_UOP_SUB_PICTURE_STREAM_CHANGE_DISPLAY
#define UOP_AUDIO_LANGUAGE_SELECT    MM_UOP_AUDIO_LANGUAGE_SELECT
#define UOP_SUB_PICTURE_LANGUAGE_SELECT MM_UOP_SUB_PICTURE_LANGUAGE_SELECT
#define UOP_REPEAT_MODE_CHANGE       MM_UOP_REPEAT_MODE_CHANGE
#define UOP_TITLE_PLAY               MM_UOP_TITLE_PLAY
#define UOP_PTT_PLAY                 MM_UOP_PTT_PLAY
#define UOP_TITLE_TIME_PLAY          MM_UOP_TITLE_TIME_PLAY
#define UOP_TITLE_TIME_SEARCH        MM_UOP_TITLE_TIME_SEARCH
#define UOP_PTT_SEARCH               MM_UOP_PTT_SEARCH
#define UOP_MENU_CALL_VIDEO          MM_UOP_MENU_CALL_VIDEO
#define UOP_PARENTAL_LEVEL_SELECT    MM_UOP_PARENTAL_LEVEL_SELECT
#define UOP_PARENTAL_COUNTRY_SELECT  MM_UOP_PARENTAL_COUNTRY_SELECT
#define UOP_KARAOKE_MODE_CHANGE      MM_UOP_KARAOKE_MODE_CHANGE
#define UOP_PTT_PLAY_RANGE           MM_UOP_PTT_PLAY_RANGE
#define UOP_TITLE_TIME_PLAY_RANGE    MM_UOP_TITLE_TIME_PLAY_RANGE
#define UOP_FIRST_PLAY               MM_UOP_FIRST_PLAY
#define UOP_TITLE_GROUP_PLAY         MM_UOP_TITLE_GROUP_PLAY
#define UOP_TRACK_PLAY               MM_UOP_TRACK_PLAY
#define UOP_GROUP_TIME_PLAY          MM_UOP_GROUP_TIME_PLAY
#define UOP_GROUP_TIME_SEARCH        MM_UOP_GROUP_TIME_SEARCH
#define UOP_TRACK_SEARCH             MM_UOP_TRACK_SEARCH
#define UOP_PREV_TK_SEARCH           MM_UOP_PREV_TK_SEARCH
#define UOP_TOP_TK_SEARCH            MM_UOP_TOP_TK_SEARCH
#define UOP_NEXT_TK_SEARCH           MM_UOP_NEXT_TK_SEARCH
#define UOP_PREV_DLIST_SEARCH        MM_UOP_PREV_DLIST_SEARCH
#define UOP_NEXT_DLIST_SEARCH        MM_UOP_NEXT_DLIST_SEARCH
#define UOP_HOME_DLIST_SEARCH        MM_UOP_HOME_DLIST_SEARCH
#define UOP_MENU_CALL_AUDIO          MM_UOP_MENU_CALL_AUDIO
#define UOP_TEXT_LANGUAGE_SELECT     MM_UOP_TEXT_LANGUAGE_SELECT
#define UOP_HIDDEN_GROUP_PLAY        MM_UOP_HIDDEN_GROUP_PLAY
#define UOP_HIDDEN_TRACK_PLAY        MM_UOP_HIDDEN_TRACK_PLAY
#define UOP_HIDDEN_TIME_PLAY         MM_UOP_HIDDEN_TIME_PLAY

typedef struct mm_dvd_status {
	struct mm_dvd_blocked { /* 1 bits in these masks represent blocked functionality */
		uint32_t	uop_mask; /* see mm_blocked_uops enum */
		uint32_t	audio_mask;
		uint32_t	subpicture_mask;
	} blocked;
	uint32_t    domain;
	uint32_t    title; /* current title */
	uint32_t    chapter; /* current chapter */
	uint64_t    chapter_start_time; /* changing to chapter_start_time: time at beginning of current chapter */
	uint32_t    num_audio_streams;
	uint32_t    audio_stream;
	uint32_t    num_subtitle_streams;
	uint32_t    subtitle_stream;
	uint32_t    num_angles;
	uint32_t    angle;
	uint32_t    playback_pml; /*  the new parental management level needed for playback, 0 if no change required. */
	uint32_t    spare[4];
} mm_dvd_status_t;

typedef enum mm_dvd_status_reason {
	MM_DVD_DOMAIN_UPDATE       = 0x01,
	MM_DVD_TITLE_UPDATE        = 0x02,
	MM_DVD_CHAPTER_UPDATE      = 0x04,
	MM_DVD_ANGLE_UPDATE        = 0x08,
	MM_DVD_AUDIO_UPDATE        = 0x10,
	MM_DVD_SUBTITLE_UPDATE     = 0x20,
	MM_DVD_BLOCKED_UPDATE      = 0x40,
	MM_DVD_MENU_ACTIVE_UPDATE  = 0x80,
	MM_DVD_PML_UPDATE          = 0x0100, /*  parental management level insufficient for playback, see playback_pml for needed level */
} mm_dvd_status_reason_t;


#define	DVD_DOMAIN_UPDATE           MM_DVD_DOMAIN_UPDATE /* Deprecated, use MM_DVD_DOMAIN_UPDATE */
#define	DVD_TITLE_UPDATE            MM_DVD_TITLE_UPDATE /* Deprecated, use MM_DVD_TITLE_UPDATE */
#define	DVD_CHAPTER_UPDATE          MM_DVD_CHAPTER_UPDATE /* Deprecated, use MM_DVD_CHAPTER_UPDATE */
#define	DVD_ANGLE_UPDATE            MM_DVD_ANGLE_UPDATE /* Deprecated, use MM_DVD_ANGLE_UPDATE */
#define	DVD_AUDIO_UPDATE            MM_DVD_AUDIO_UPDATE /* Deprecated, use MM_DVD_AUDIO_UPDATE */
#define	DVD_SUBTITLE_UPDATE         MM_DVD_SUBTITLE_UPDATE /* Deprecated, use MM_DVD_SUBTITLE_UPDATE */
#define	DVD_BLOCKED_UPDATE          MM_DVD_BLOCKED_UPDATE /* Deprecated, use MM_DVD_BLOCKED_UPDATE */
#define	DVD_MENU_ACTIVE_UPDATE      MM_DVD_MENU_ACTIVE_UPDATE /* Deprecated, use MM_DVD_MENU_ACTIVE_UPDATE */
#define	DVD_PML_UPDATE              MM_DVD_PML_UPDATE /*  parental management level insufficient for playback, see playback_pml for needed level */

typedef struct mm_dvd_status_event {
	mm_dvd_status_t         status;
	mm_dvd_status_reason_t  reason;
} mm_dvd_status_event_t;

typedef struct mm_parental_control {
	uint16_t country_code; /* based on ISO3166 */
	uint8_t	level; /* (1-8 1 being most restrictive (general audience)) */
	uint8_t	spare; /* align */
} mm_parental_control_t;

typedef struct mm_media_status {
	uint32_t    title; /* current title */
	uint32_t    title_count;
	uint32_t    chapter; /* current chapter */
	uint32_t    chapter_count;
	uint32_t    num_audio_streams;
	uint32_t    audio_stream;
	uint32_t    num_subtitle_streams;
	uint32_t    subtitle_stream;
	uint32_t    num_angles;
	uint32_t    angle;
} mm_media_status_t;

typedef enum mm_media_status_reason {
	MM_MEDIA_TITLE_UPDATE        = 0x01,
	MM_MEDIA_CHAPTER_UPDATE      = 0x02,
	MM_MEDIA_ANGLE_UPDATE        = 0x04,
	MM_MEDIA_AUDIO_UPDATE        = 0x08,
	MM_MEDIA_SUBTITLE_UPDATE     = 0x10,
} mm_media_status_reason_t;

typedef struct mm_media_status_event {
	mm_media_status_t       status;
	mm_media_status_reason_t  reason;
} mm_media_status_event_t;

typedef enum
{
  MM_BITRATE_TYPE_UNKNOWN,
  MM_BITRATE_TYPE_CONSTANT,
  MM_BITRATE_TYPE_VARIABLE,
  CBR = MM_BITRATE_TYPE_CONSTANT, /* Deprecated, use MM_BITRATE_TYPE_CONSTANT */
  VBR = MM_BITRATE_TYPE_VARIABLE, /* Deprecated, use MM_BITRATE_TYPE_VARIABLE */ 
  /* more tbd.., */
}mm_bitrate_t;

/*channel configuration bitmask(0x00FF0000 - front, 0x0000FF00 - back, 0x000000FF LFE*/
#define MM_AUDIO_CHANNEL_CONFIG( front, back, LFE ) ( (front)<< 12 | (back) << 4 | (LFE) )
#define MM_AUDIO_CHANNEL_FRONT( channels ) ( (channels) >> 12 & 0x00FF )
#define MM_AUDIO_CHANNEL_BACK( channels )  ( (channels) >> 4  & 0x00FF )
#define MM_AUDIO_CHANNEL_LFE( channels )   ( (channels) & 1 )

typedef struct mm_audio_format 
{
  char                    codec[MM_CODEC_NAME_MAX_LEN];
  uint32_t                bitrate;      /* bits per second  */
  uint32_t                samplerate;   /* in Hz */
  int64_t                 duration;     /* in msec */
  uint8_t                 channels;     /* 1 = mono, 2 =  stereo, etc. */
  uint8_t                 bitrate_type; /* CBR,VBR .. see enum mm_bitrate_t     */
  uint8_t                 channel_type; /* Deprecated */
  uint8_t                 protected_track;    /* 1 if DRM protected file, 0 otherwise */
  uint32_t                channel_configuration;  /* channel connection bitmask            */
  int32_t                 reserve3;
} mm_audio_format_t;

/**
 *  Enum used to index the strings inside mm_metadata_t
 */
typedef enum mm_metadata_string_index {
    MM_METADATA_TITLE,
    MM_METADATA_ARTIST,
    MM_METADATA_COMPOSER,
    MM_METADATA_ALBUM,
    MM_METADATA_GENRE,
    MM_METADATA_COMMENT,
    MM_METADATA_EXTRA,
    MM_METADATA_NUM_STRINGS,
    MM_METADATA_TOTAL_STRINGS = 16
} mm_metadata_string_index_t;

#define MM_METADATA_EXTRA_KVPAIR_DELIM	'='
#define MM_METADATA_EXTRA_RECORD_DELIM	'\x1e'

/**
 * Metadata structure
 */
typedef struct mm_metadata {
    const char *strings[ MM_METADATA_NUM_STRINGS ];
    const char *reserved1[ MM_METADATA_TOTAL_STRINGS - MM_METADATA_NUM_STRINGS ];
    uint16_t   release_year;
    uint8_t    release_month;
    uint8_t    release_mday;
    uint16_t   track_num;
    uint16_t   disc_num;
	uint8_t    rating;
    char       reserved2[ 15 ];
} mm_metadata_t;

typedef enum {
    LWM_RISING  = 0x01, /*  low watermark rising traversal  */
    LWM_FALLING = 0x02, /*  low watermark falling traversal  */
    HWM_RISING  = 0x04, /*  high watermark rising traversal */
    HWM_FALLING = 0x08, /*  high watermark falling traversal */
    MM_DRAINING = 0x10, /*  draining without reading */
    MM_FETCHING = 0x20, /*  reading */
} mm_wm_trig_t;


/**
 * Flags associated with warnings
 */
typedef enum e_mm_warning_flags {
	MM_WARNING_FLAG_NONE    = 0x0,
	MM_WARNING_FLAG_AUDIBLE = 0x1,	/* A warning with this flag set indicates that it */
									/* was audible to the listener. */
	MM_WARNING_FLAG_VISIBLE = 0x2,	/* A warning with this flag set indicates that it */
									/* was visible to the viewer. */
} mm_warning_flags_t;

/**
 * The multimedia warnings.
 */
typedef enum e_mm_warnings {
	MM_WARNING_READ_TIMEOUT = 0x1,	/* The source was slow and a read timed out. */
									/* It is being retried.*/
	MM_WARNING_READ_ERROR   = 0x2, /* There was a read error.  We're trying to recover. */
	MM_WARNING_AUDIO_UNDERRUN = 0x3, /* There was an underrun on the audio output. */
	MM_WARNING_VIDEO_UNDERRUN = 0x4, /* There was an underrun on the audio output. */
	MM_WARNING_RESOURCE_UNAVAILABLE = 0x5, /* One or more resources are unavailable which may reduce playback quality*/
} mm_warnings_t;

/**
 * Payload structure for the MM_EV_WARNING event.
 */
typedef struct s_mm_warning_info {
	_Uint32t mm_warning;	/* mm_warnings_t */
	_Uint32t flags;			/* mm_warning_flags_t */
} mm_warning_info_t;

#ifdef __cplusplus
}
#endif

#endif

/* __SRCVERSION("types.h $Rev: 680336 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/support/public/mm/types.h $ $Rev: 680336 $")
#endif
