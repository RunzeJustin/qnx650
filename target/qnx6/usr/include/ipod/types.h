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

#ifndef _IPOD_TYPES_H_INCLUDED
#define _IPOD_TYPES_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _TIME_H_INCLUDED
#include <time.h>
#endif

__BEGIN_DECLS

/**
 * @file types.h
 *
 * @brief Defines constants and data structures used by the iPod interface. 
 */

#define IPOD_LOG_LEVEL	0

/** Some logging macros */
#define IPODLIB_LOG( verbose_level, format, args... )													\
	do {																								\
		if ( verbose >= verbose_level ) {																\
			ipod_log( _SLOG_INFO, __PRETTY_FUNCTION__, __LINE__, verbose_level, format, ##args );		\
        }																								\
     } while(0)

typedef struct {
	uint32_t		eventtype;
	
/** iPod requested session; eventinfo is protocol ID. */
#define IPOD_EAF_EVENT_SESSION_REQ		0x00000001

/**  iPod closed a session; eventinfo is session ID. */
#define IPOD_EAF_EVENT_SESSION_CLOSE	0x00000002

/** iPod sent data; eventinfo is session ID. */
#define IPOD_EAF_EVENT_SESSION_DATA		0x00000003

/** iPod session available; eventinfo is protocol ID. */
#define IPOD_EAF_EVENT_SESSION_OPEN		0x00000004
	uint32_t		eventinfo;
	uint32_t		reserved[2];
} ipod_eaf_event_t;

typedef enum {
	IPOD_EVENT_STATUS,
	IPOD_EVENT_GPS,
} ipod_event_type_t;

typedef enum {
	IPOD_EVENT_GPS_CTRLRECV,            // Received SetAccessoryControl, eventinfo is loctype
	IPOD_EVENT_GPS_DATARECV,            // Received SetAccessoryData, eventinfo is loctype, eventinfo2 is datatype
	IPOD_EVENT_GPS_DATASEND,            // Received GetAccessoryData, cached data sent
} ipod_gps_type_t;

typedef struct {
	ipod_event_type_t		type;
	uint32_t				subtype;
	uint32_t				count;
	uint32_t				eventinfo;
	uint32_t				eventinfo2;
	uint32_t				reserved[4];
} ipod_event_t;

// GPS Location Types
enum {
	IPOD_GPS_LOC_TYPE_SYSTEM	= 0x00,
	IPOD_GPS_LOC_TYPE_NMEA		= 0x01,
	IPOD_GPS_LOC_TYPE_ASSIST 	= 0x02
};

// GPS Data Types for Location Assist
enum {
	IPOD_GPS_ASSIST_DATA_POINT		= 0x00,
	IPOD_GPS_ASSIST_DATA_SATEMP		= 0x01,
	IPOD_GPS_ASSIST_DATA_ACCSATEMP	= 0x02,
	IPOD_GPS_ASSIST_DATA_MAXREF		= 0x03,
	IPOD_GPS_ASSIST_DATA_SETREF		= 0x04,
	IPOD_GPS_ASSIST_DATA_TIME		= 0x05
};

// GPS Data Types for NMEA
enum {
	IPOD_GPS_NMEA_DATA			= 0x00,
	IPOD_GPS_NMEA_ACCDATA		= 0x80
};

// Data structure for IPOD_GPS_LOC_TYPE_ASSIST/IPOD_GPS_ASSIST_DATA_POINT
typedef struct {
	uint16_t	week;
	uint32_t	time;
	int32_t		deglat;
	int32_t		deglong;
	uint16_t	radius;
} ipod_gps_points_t;

// Data structure for IPOD_GPS_LOC_TYPE_ASSIST/IPOD_GPS_ASSIST_DATA_TIME
typedef struct {
	uint16_t	week;
	uint32_t	time;
} ipod_gps_time_t;

/** Different iPod modes of operation */
#define IPOD_MODE_STANDARD			0x00
#define IPOD_MODE_EXT_INTERFACE		0x01
#define IPOD_MODE_IPODOUT			0x02

/** iPod capabilities */
#define IPOD_CAPABILITY_EA				0x0000
#define IPOD_CAPABILITY_IPODOUT			0x0001
#define IPOD_CAPABILITY_STORAGE			0x0002
#define IPOD_CAPABILITY_IPODOUT_VBI		0x0003
#define IPOD_CAPABILITY_AUTH_COMPLETE	0x0004
#define IPOD_CAPABILITY_REQ_APP_LAUNCH	0x0005
#define IPOD_CAPABILITY_AVSYNC			0x0006
#define IPOD_CAPABILITY_AUDIOSWITCH		0x0007
#define IPOD_CAPABILITY_MAX				0x0007
//TODO: add all iPod capabilities (ie. enhanced trkinfo cmds)

/** iPod track info */
#define IPOD_DB_TRACK_INFO_CAPS						0x00000001
#define IPOD_DB_TRACK_INFO_NAME						0x00000002
#define IPOD_DB_TRACK_INFO_ARTIST					0x00000004
#define IPOD_DB_TRACK_INFO_ALBUM					0x00000008
#define IPOD_DB_TRACK_INFO_GENRE					0x00000010
#define IPOD_DB_TRACK_INFO_COMPOSER					0x00000020
#define IPOD_DB_TRACK_INFO_TOTAL_DURATION			0x00000040
#define IPOD_DB_TRACK_INFO_UNIQUE_INDENT			0x00000080
#define IPOD_DB_TRACK_INFO_CHAPTER_COUNT			0x00000100
#define IPOD_DB_TRACK_INFO_CHAPTER_TIMES			0x00000200
#define IPOD_DB_TRACK_INFO_CHAPTER_NAMES			0x00000400
#define IPOD_DB_TRACK_INFO_LYRICS					0x00000800
#define IPOD_DB_TRACK_INFO_DESCRIPTION				0x00001000
#define IPOD_DB_TRACK_INFO_ALBUM_TRACK_IDX			0x00002000
#define IPOD_DB_TRACK_INFO_DISCSET_IDX				0x00004000
#define IPOD_DB_TRACK_INFO_PLAYCOUNT				0x00008000
#define IPOD_DB_TRACK_INFO_SKIPCOUNT				0x00008000

/** iPod track capabilities */
#define IPOD_TRACK_INFO_CAPS_AUDIOBOOK				0x00000001
#define IPOD_TRACK_INFO_CAPS_CHAPTERS				0x00000002
#define IPOD_TRACK_INFO_CAPS_ALBART					0x00000004
#define IPOD_TRACK_INFO_CAPS_LYRICS					0x00000008
#define IPOD_TRACK_INFO_CAPS_PODCAST				0x00000010
#define IPOD_TRACK_INFO_CAPS_RELEASEDATE			0x00000020
#define IPOD_TRACK_INFO_CAPS_DESCRIPTION			0x00000040
#define IPOD_TRACK_INFO_CAPS_VIDEO					0x00000080
#define IPOD_TRACK_INFO_CAPS_QUEUEDVIDEO			0x00000100
#define IPOD_TRACK_INFO_CAPS_RESERVED1				0x00000200
#define IPOD_TRACK_INFO_CAPS_RESERVED2				0x00000400
#define IPOD_TRACK_INFO_CAPS_RESERVED3				0x00000800
#define IPOD_TRACK_INFO_CAPS_RESERVED4				0x00001000
#define IPOD_TRACK_INFO_CAPS_CREATE_GENIUS_PLT		0x00002000
#define IPOD_TRACK_INFO_CAPS_ITUNESU				0x00004000

/** iPod button settings */
#define IPOD_BUTTON_CONTEXT_PLAY_PAUSE			0x00000001
#define IPOD_BUTTON_CONTEXT_VOLUME_UP			0x00000002
#define IPOD_BUTTON_CONTEXT_VOLUME_DOWN			0x00000004
#define IPOD_BUTTON_CONTEXT_NEXT_TRACK			0x00000008
#define IPOD_BUTTON_CONTEXT_PREV_TRACK			0x00000010
#define IPOD_BUTTON_CONTEXT_NEXT_ALBUM			0x00000020
#define IPOD_BUTTON_CONTEXT_PREV_ALBUM			0x00000040
#define IPOD_BUTTON_CONTEXT_STOP				0x00000080
#define IPOD_BUTTON_CONTEXT_PLAY_RESUME			0x00000100
#define IPOD_BUTTON_CONTEXT_PAUSE				0x00000200
#define IPOD_BUTTON_CONTEXT_MUTE_TOGGLE			0x00000400
#define IPOD_BUTTON_CONTEXT_NEXT_CHAPTER		0x00000800
#define IPOD_BUTTON_CONTEXT_PREV_CHAPTER		0x00001000
#define IPOD_BUTTON_CONTEXT_NEXT_PLAYLIST		0x00002000
#define IPOD_BUTTON_CONTEXT_PREV_PLAYLIST		0x00004000
#define IPOD_BUTTON_CONTEXT_SHUFFLE_ADVANCE		0x00008000
#define IPOD_BUTTON_CONTEXT_REPEAT_ADVANCE		0x00010000
#define IPOD_BUTTON_CONTEXT_POWER_ON			0x00020000
#define IPOD_BUTTON_CONTEXT_POWER_OFF			0x00040000
#define IPOD_BUTTON_CONTEXT_BACKLIGHT_30SEC		0x00080000
#define IPOD_BUTTON_CONTEXT_BEGIN_FAST_FWD		0x00100000
#define IPOD_BUTTON_CONTEXT_BEGIN_REWIND		0x00200000
#define IPOD_BUTTON_CONTEXT_MENU				0x00400000
#define IPOD_BUTTON_CONTEXT_SELECT				0x00800000
#define IPOD_BUTTON_CONTEXT_UP_ARROW			0x01000000
#define IPOD_BUTTON_CONTEXT_DOWN_ARROW			0x02000000
#define IPOD_BUTTON_CONTEXT_BACKLIGHT_OFF		0x04000000

#define IPOD_BUTTON_IMAGE_PLAY_PAUSE			0x00000001
#define IPOD_BUTTON_IMAGE_NEXT_IMAGE			0x00000002
#define IPOD_BUTTON_IMAGE_PREV_IMAGE			0x00000004
#define IPOD_BUTTON_IMAGE_STOP					0x00000008
#define IPOD_BUTTON_IMAGE_PLAY_RESUME			0x00000010
#define IPOD_BUTTON_IMAGE_PAUSE					0x00000020
#define IPOD_BUTTON_IMAGE_SHUFFLE_ADVANCE		0x00000040
#define IPOD_BUTTON_IMAGE_REPEAT_ADVANCE		0x00000080

#define IPOD_BUTTON_VIDEO_PLAY_PAUSE			0x00000001
#define IPOD_BUTTON_VIDEO_NEXT_VIDEO			0x00000002
#define IPOD_BUTTON_VIDEO_PREV_VIDEO			0x00000004
#define IPOD_BUTTON_VIDEO_STOP					0x00000008
#define IPOD_BUTTON_VIDEO_PLAY_RESUME			0x00000010
#define IPOD_BUTTON_VIDEO_PAUSE					0x00000020
#define IPOD_BUTTON_VIDEO_BEGIN_FF				0x00000040
#define IPOD_BUTTON_VIDEO_BEGIN_REW				0x00000080
#define IPOD_BUTTON_VIDEO_NEXT_CHAPTER			0x00000100
#define IPOD_BUTTON_VIDEO_PREV_CHAPTER			0x00000200
#define IPOD_BUTTON_VIDEO_NEXT_FRAME			0x00000400
#define IPOD_BUTTON_VIDEO_PREV_FRAME			0x00000800

#define IPOD_BUTTON_AUDIO_PLAY_PAUSE			0x00000001
#define IPOD_BUTTON_AUDIO_VOLUME_UP				0x00000002
#define IPOD_BUTTON_AUDIO_VOLUME_DOWN			0x00000004
#define IPOD_BUTTON_AUDIO_NEXT_TRACK			0x00000008
#define IPOD_BUTTON_AUDIO_PREV_TRACK			0x00000010
#define IPOD_BUTTON_AUDIO_NEXT_ALBUM			0x00000020
#define IPOD_BUTTON_AUDIO_PREV_ALBUM			0x00000040
#define IPOD_BUTTON_AUDIO_STOP					0x00000080
#define IPOD_BUTTON_AUDIO_PLAY_RESUME			0x00000100
#define IPOD_BUTTON_AUDIO_PAUSE					0x00000200
#define IPOD_BUTTON_AUDIO_MUTE_TOGGLE			0x00000400
#define IPOD_BUTTON_AUDIO_NEXT_CHAPTER			0x00000800
#define IPOD_BUTTON_AUDIO_PREV_CHAPTER			0x00001000
#define IPOD_BUTTON_AUDIO_NEXT_PLAYLIST			0x00002000
#define IPOD_BUTTON_AUDIO_PREV_PLAYLIST			0x00004000
#define IPOD_BUTTON_AUDIO_SHUFFLE_ADVANCE		0x00008000
#define IPOD_BUTTON_AUDIO_REPEAT_ADVANCE		0x00010000
#define IPOD_BUTTON_AUDIO_BEGIN_FF				0x00020000
#define IPOD_BUTTON_AUDIO_BEGIN_REW				0x00040000
#define IPOD_BUTTON_AUDIO_RECORD				0x00080000

#define IPOD_BUTTON_LOCATION_CAR_CENTER			0x00
#define IPOD_BUTTON_LOCATION_STEERING_WHEEL		0x01
#define IPOD_BUTTON_LOCATION_CAR_DASHBOARD		0x02

#define IPOD_BUTTON_IPODOUT_SELECT_EVENT		0x00000001
#define IPOD_BUTTON_IPODOUT_LEFT_EVENT			0x00000002
#define IPOD_BUTTON_IPODOUT_RIGHT_EVENT			0x00000004
#define IPOD_BUTTON_IPODOUT_UP_EVENT			0x00000008
#define IPOD_BUTTON_IPODOUT_DOWN_EVENT			0x00000010
#define IPOD_BUTTON_IPODOUT_MENU_BUTTON			0x00000020

#define IPOD_IPODOUT_STATE_DISP_AWAY			0x00
#define IPOD_IPODOUT_STATE_DISP_BACK			0x01
#define IPOD_IPODOUT_STATE_AUDIO_AWAY			0x02
#define IPOD_IPODOUT_STATE_AUDIO_BACK			0x03
#define IPOD_IPODOUT_STATE_DAYTIME				0x04
#define IPOD_IPODOUT_STATE_NIGHTTIME			0x05

#define IPOD_IPODOUT_OPT_AUDIO					0x00000001
#define IPOD_IPODOUT_OPT_PHONEUI				0x00000002
#define IPOD_IPODOUT_OPT_MESSAGEUI				0x00000004

#define IPOD_WHEEL_TYPE_FREE					0x00
#define IPOD_WHEEL_TYPE_JOG						0x01

#define IPOD_WHEEL_ROTATION_COUNTER_CLOCKWISE	0x00
#define IPOD_WHEEL_ROTATION_CLOCKWISE			0x01

#define IPOD_WHEEL_ACTION_COMPLETE				0x00
#define IPOD_WHEEL_ACTION_INPROGRESS			0x01
#define IPOD_WHEEL_ACTION_REPEAT				0x02

#define IPOD_WHEEL_ROTATION_TYPE_DETENTS		0x00
#define IPOD_WHEEL_ROTATION_TYPE_DEGREES		0x01

#define IPOD_PREFERENCE_VIDEO_OUT				0x00
#define IPOD_PREFERENCE_VIDEO_OUT_OFF				0x00
#define IPOD_PREFERENCE_VIDEO_OUT_ON				0x01
#define IPOD_PREFERENCE_VIDEO_OUT_ASK				0x02
#define IPOD_PREFERENCE_SCREEN					0x01
#define IPOD_PREFERENCE_SCREEN_FILL					0x00
#define IPOD_PREFERENCE_SCREEN_FIT					0x01
#define IPOD_PREFERENCE_VIDEO_FORMAT			0x02
#define IPOD_PREFERENCE_VIDEO_FORMAT_NTSC			0x00
#define IPOD_PREFERENCE_VIDEO_FORMAT_PAL			0x01
#define IPOD_PREFERENCE_LINEOUT					0x03
#define IPOD_PREFERENCE_LINEOUT_OFF					0x00
#define IPOD_PREFERENCE_LINEOUT_ON					0x01
#define IPOD_PREFERENCE_VIDEO_CONN				0x08
#define IPOD_PREFERENCE_VIDEO_CONN_NONE				0x00
#define IPOD_PREFERENCE_VIDEO_CONN_COMPOSITE		0x01
#define IPOD_PREFERENCE_VIDEO_CONN_SVIDEO			0x02
#define IPOD_PREFERENCE_VIDEO_CONN_COMPONNT			0x03
#define IPOD_PREFERENCE_CLOSED_CAPTION			0x09
#define IPOD_PREFERENCE_CLOSED_CAPTION_OFF			0x00
#define IPOD_PREFERENCE_CLOSED_CAPTION_ON			0x01
#define IPOD_PREFERENCE_VIDEO_RATIO				0x0A
#define IPOD_PREFERENCE_VIDEO_RATIO_FULL			0x00
#define IPOD_PREFERENCE_VIDEO_RATIO_WIDE			0x01
#define IPOD_PREFERENCE_SUBTITLES				0x0C
#define IPOD_PREFERENCE_SUBTITLES_OFF				0x00
#define IPOD_PREFERENCE_SUBTITLES_ON				0x01
#define IPOD_PREFERENCE_VIDEO_ALTAUDIO			0x0D
#define IPOD_PREFERENCE_VIDEO_ALTAUDIO_OFF			0x00
#define IPOD_PREFERENCE_VIDEO_ALTAUDIO_ON			0x01

#define IPOD_STORAGE_FEATURE_TYPE_RESERVED			0x00
#define IPOD_STORAGE_FEATURE_TYPE_RADIO_TAGGING	0x01
#define IPOD_STORAGE_FEATURE_TYPE_RECORD_WORKOUT	0x02

/** iPod hierarchies for ResetDBSelectionHierarchy */
#define IPOD_HIER_AUDIO				0x01
#define IPOD_HIER_VIDEO				0x02

/** iPod category types for SelectDBRecord */
#define IPOD_CAT_NONE				0x00		/**< 1.14 */
#define IPOD_CAT_PLAYLIST			0x01		/**< 1.00 */
#define IPOD_CAT_ARTIST				0x02		/**< 1.00 */
#define IPOD_CAT_ALBUM				0x03		/**< 1.00 */
#define IPOD_CAT_GENRE				0x04		/**< 1.00 */
#define IPOD_CAT_TRACK				0x05		/**< 1.00 */
#define IPOD_CAT_COMPOSER			0x06		/**< 1.00 */
#define IPOD_CAT_AUDIOBOOK			0x07		/**< 1.06 */
#define IPOD_CAT_PODCAST			0x08		/**< 1.08 */
#define IPOD_CAT_NESTED_PLIST		0x09		/**< 1.13 */
#define IPOD_CAT_GENIUS_PLIST		0x0A		/**< 1.14 */
#define IPOD_CAT_ITUNESU			0x0B		/**< 1.14 */

/** iPod Lingos */
enum {
	LINGO_GENERAL			= 0x00,
	LINGO_MICROPHONE		= 0x01,
	LINGO_SIMPLE_REMOTE		= 0x02,
	LINGO_DISPLAY_REMOTE	= 0x03,
	LINGO_EXTENDED			= 0x04,
	LINGO_RF_TRANSMITTER	= 0x05,
	LINGO_USB_HOST_CTRL		= 0x06,
	LINGO_RF_TUNER			= 0x07,
	LINGO_ACCESSORY_EQ		= 0x08,
	LINGO_SPORTS			= 0x09,
	LINGO_DIGITAL_AUDIO		= 0x0a,
	LINGO_STORAGE			= 0x0c,
	LINGO_IPODOUT			= 0x0d,
	LINGO_LOCATION			= 0x0e,
	NLINGOES				= 0x10
};

/** Lingo options support */
#define IPOD_GENERAL_OPT_LINEOUT			0x0000000000000001
#define IPOD_GENERAL_OPT_VIDEOOUT			0x0000000000000002
#define IPOD_GENERAL_OPT_NTSC				0x0000000000000004
#define IPOD_GENERAL_OPT_PAL				0x0000000000000008
#define IPOD_GENERAL_OPT_VIDEO_COMPOSITE	0x0000000000000010
#define IPOD_GENERAL_OPT_VIDEO_SVIDEO		0x0000000000000020
#define IPOD_GENERAL_OPT_VIDEO_COMPONENT	0x0000000000000040
#define IPOD_GENERAL_OPT_VIDEO_CC			0x0000000000000080
#define IPOD_GENERAL_OPT_VIDEO_FULLSCREEN	0x0000000000000100
#define IPOD_GENERAL_OPT_VIDEO_WIDESCREEN	0x0000000000000200
#define IPOD_GENERAL_OPT_VIDEO_SUBTITLE		0x0000000000000400
#define IPOD_GENERAL_OPT_VIDEO_ALTAUDIO		0x0000000000000800
#define IPOD_GENERAL_OPT_CTA_SUPPORT		0x0000000000001000
#define IPOD_GENERAL_OPT_EAF				0x0000000000002000
#define IPOD_GENERAL_OPT_IPOD_NOTIFICATIONS	0x0000000000004000
#define IPOD_GENERAL_OPT_RESERVED1			0x0000000000008000
#define IPOD_GENERAL_OPT_RESERVED2			0x0000000000010000
#define IPOD_GENERAL_OPT_RESERVED3			0x0000000000020000
#define IPOD_GENERAL_OPT_RESERVED4			0x0000000000040000
#define IPOD_GENERAL_OPT_PAUSE_ON_POWER		0x0000000000080000
#define IPOD_GENERAL_OPT_RESERVED6			0x0000000000100000
#define IPOD_GENERAL_OPT_RESERVED7			0x0000000000200000
#define IPOD_GENERAL_OPT_RESERVED8			0x0000000000400000
#define IPOD_GENERAL_OPT_EXT_IDPS_TOKEN		0x0000000000800000
#define IPOD_GENERAL_OPT_REQ_APP_LAUNCH		0x0000000001000000
#define IPOD_GENERAL_OPT_RESERVED9			0x0000000002000000
#define IPOD_GENERAL_OPT_AUDIOSWITCH		0x0000000004000000
#define IPOD_SIMPLE_OPT_CONTEXT				0x0000000000000001
#define IPOD_SIMPLE_OPT_AUDIO_CTRL			0x0000000000000002
#define IPOD_SIMPLE_OPT_VIDEO_CTRL			0x0000000000000004
#define IPOD_SIMPLE_OPT_IMAGE_CTRL			0x0000000000000008
#define IPOD_SIMPLE_OPT_SPORTS_CTRL			0x0000000000000010
#define IPOD_SIMPLE_OPT_RESERVED1			0x0000000000000020
#define IPOD_SIMPLE_OPT_RESERVED2			0x0000000000000040
#define IPOD_SIMPLE_OPT_RESERVED3			0x0000000000000080
#define IPOD_SIMPLE_OPT_CAMERA_CTRL			0x0000000000000100
#define IPOD_SIMPLE_OPT_USB_HID				0x0000000000000200
#define IPOD_SIMPLE_OPT_ACC_CTRL			0x0000000000000400
#define IPOD_DISPLAY_OPT_UI_VOL_CTRL		0x0000000000000001
#define IPOD_DISPLAY_OPT_ABS_VOL_CTRL		0x0000000000000002
#define IPOD_DISPLAY_OPT_GENIUS_PLISTS		0x0000000000000004
#define IPOD_EXTENED_OPT_VIDEO_BROWSE		0x0000000000000001
#define IPOD_EXTENED_OPT_TRKINFO_ENHANCE	0x0000000000000002
#define IPOD_EXTENED_OPT_NESTED_PLISTS		0x0000000000000004
#define IPOD_EXTENED_OPT_GENIUS_PLISTS		0x0000000000000008
#define IPOD_EXTENED_OPT_SPLASH_SCREEN		0x0000000000000010
#define IPOD_EXTENED_OPT_LIST_DB_CATS		0x0000000000000020
#define IPOD_EXTENED_OPT_PCTRL_PLAYPAUSE	0x0000000000000040
#define IPOD_EXTENED_OPT_UID_BASED_CMDS		0x0000000000000080
#define IPOD_DIGITAL_OPT_AVSYNC				0x0000000000000001
#define IPOD_STORAGE_OPT_TAGGING			0x0000000000000001
#define IPOD_IPODOUT_OPT_VBI				0x0000000000000002
#define IPOD_LOCATION_OPT_RECV_GPS_NMEA		0x0000000000000001
#define IPOD_LOCATION_OPT_SEND_GPS_ASSIST	0x0000000000000002

/**
 * Provides a handle to the iPod driver server. 
 */
struct ipod_hdl_s;
typedef struct ipod_hdl_s ipod_hdl_t;		

// Authentication status
typedef enum ipod_auth_status {
	IPOD_AUTH_STATUS_NONE,
	IPOD_AUTH_STATUS_FAIL,
	IPOD_AUTH_STATUS_PENDING,				// Authentication version in progress
	IPOD_AUTH_STATUS_PARTIAL,				// Authentication version is validated
	IPOD_AUTH_STATUS_COMPLETE				// Challenge complete, fully authenticated
} ipod_auth_status_t;

// Playcontrol options
enum {
	IPOD_CONTROL_STOP	 			= 0x00,
	IPOD_CONTROL_NEXT_TRACK			= 0x01,
	IPOD_CONTROL_PREV_TRACK			= 0x02,
	IPOD_CONTROL_FFWD				= 0x03,
	IPOD_CONTROL_FBWD				= 0x04,
	IPOD_CONTROL_NEXT_CHAP			= 0x05,
	IPOD_CONTROL_PREV_CHAP			= 0x06,
	IPOD_CONTROL_PLAY				= 0x07,
	IPOD_CONTROL_RESUME				= 0x08,
	IPOD_CONTROL_PAUSE				= 0x09,
	IPOD_CONTROL_RESUME_MUSICAPP	= 0x0A
};

/** 
 * Shuffle settings
 */
typedef enum ipod_setting_shuffle {
	IPOD_SHUFFLE_SETTING_OFF				= 0x00,		/**< iPod/iPhone shuffle off. */
	IPOD_SHUFFLE_SETTING_TRACKS				= 0x01,		/**< iPod/iPhone shuffle tracks. */
	IPOD_SHUFFLE_SETTING_ALBUMS				= 0x02		/**< iPod/iPhone shuffle albums. */
} ipod_setting_shuffle_t;

/** 
 * Repeat settings
 */
typedef enum ipod_setting_repeat {
	IPOD_REPEAT_SETTING_OFF					= 0x00,		/**< iPod/iPhone repeat off. */
	IPOD_REPEAT_SETTING_ONE					= 0x01,		/**< iPod/iPhone repeat a single track. */
	IPOD_REPEAT_SETTING_ALL					= 0x02		/**< iPod/iPhone repeat all tracks. */
} ipod_setting_repeat_t;

/** 
 * Audiobook playback speeds
 */
typedef enum ipod_audiobook_speed {
	IPOD_AUDIOBOOK_SPEED_SLOWER				= 0xFF,
	IPOD_AUDIOBOOK_SPEED_NORMAL				= 0x00,
	IPOD_AUDIOBOOK_SPEED_FASTER				= 0x01
} ipod_audiobook_speed_t;

/** Enumerations marked *N/A are not currently supported. */
enum {
	IPOD_TRKINFO_CAPS,			/**< *N/A		Track information (IPOD_TRKINFO_*) can return as string or number; 
						                        for some things it doesn't make sense (e.g., name, artist, album) but 
									the function is provided for completeness*/
	IPOD_TRKINFO_NAME,			/**< String		Track name*/
	IPOD_TRKINFO_ARTIST,			/**< String		Artist name*/
	IPOD_TRKINFO_ALBUM,			/**< String		Album name*/
	IPOD_TRKINFO_GENRE,			/**< String		Genre name*/
	IPOD_TRKINFO_COMPOSER,			/**< String		Composer name*/
	IPOD_TRKINFO_DURATION,			/**< Number		Total track duration (ms)*/
	IPOD_TRKINFO_UID,			/**< Number		iTunes unique track ID*/
	IPOD_TRKINFO_CHP_COUNT,			/**< *N/A 		Chapter count*/
	IPOD_TRKINFO_CHP_TIMES,			/**< *N/A		Chapter times*/
	IPOD_TRKINFO_CHP_NAME,			/**< *N/A		Chapter names*/
	IPOD_TRKINFO_LYRICS,			/**< *N/A		Track lyrics (only for current track)*/
	IPOD_TRKINFO_DESCRIPTION,		/**< String		Description*/
	IPOD_TRKINFO_TRACK_NUM,			/**< Number		Album track index*/
	IPOD_TRKINFO_DISC_NUM,			/**< Number		Disc set album index*/
	IPOD_TRKINFO_PLAY_COUNT,		/**< Number		Play count (0 = track not played)*/
	IPOD_TRKINFO_SKIP_COUNT,		/**< Number		Skip count (0 = track not skipped)*/
	IPOD_TRKINFO_PODCAST_DATE,		/**< Number		Podcast release date (Year/Month/Day)*/
	IPOD_TRKINFO_LAST_PLAY,			/**< String		Last played date (Year/Month/Day)*/
	IPOD_TRKINFO_YEAR,			/**< Number		Year released*/
	IPOD_TRKINFO_STAR_RATING,		/**< Number		Star rating (0 -> 5)*/
	IPOD_TRKINFO_SERIES_NAME,		/**< String		Series name*/
	IPOD_TRKINFO_SEASON_NUM,		/**< Number		Season number (1 = 1st season)*/
	IPOD_TRKINFO_VOL_ADJUST,		/**< Number		Track volume adjust (-100, 0, 100)*/
	IPOD_TRKINFO_EQ_PRESET,			/**< Number		Track equalizer preset index*/
	IPOD_TRKINFO_BITRATE,			/**< Number		Track bit rate (kbps)*/
	IPOD_TRKINFO_BOOK_OFF,			/**< Number		Bookmark offset from start of track (ms)*/
	IPOD_TRKINFO_TIME_OFF,			/**< String		Start/stop time offset (start/stop)*/
	IPOD_TRKINFO_RESERVED1,			/**< */
	IPOD_TRKINFO_RESERVED2,			/**< */
	IPOD_TRKINFO_RESERVED3,			/**< */
	IPOD_TRKINFO_RESERVED4			/**< */
};
/** Track information  (IPOD_TRK_CAPS_*).*/
#define		IPOD_TRKINFO_MASK_CAPS				(1 << IPOD_TRKINFO_CAPS)

/** Track name. */			
#define		IPOD_TRKINFO_MASK_NAME				(1 << IPOD_TRKINFO_NAME)

/** Artist name. */
#define		IPOD_TRKINFO_MASK_ARTIST			(1 << IPOD_TRKINFO_ARTIST)

/** Album name. */
#define		IPOD_TRKINFO_MASK_ALBUM				(1 << IPOD_TRKINFO_ALBUM)

/** Genre name. */
#define		IPOD_TRKINFO_MASK_GENRE				(1 << IPOD_TRKINFO_GENRE)

/** Composer name. */
#define		IPOD_TRKINFO_MASK_COMPOSER			(1 << IPOD_TRKINFO_COMPOSER)

/** Total track duration (ms). */
#define		IPOD_TRKINFO_MASK_DURATION			(1 << IPOD_TRKINFO_DURATION)

/** iTunes unique track ID. */
#define		IPOD_TRKINFO_MASK_UID				(1 << IPOD_TRKINFO_UID)

/** Chapter count. */
#define		IPOD_TRKINFO_MASK_CHP_COUNT			(1 << IPOD_TRKINFO_CHP_COUNT)

/** Chapter times. */
#define		IPOD_TRKINFO_MASK_CHP_TIMES			(1 << IPOD_TRKINFO_CHP_TIMES)

/** Chapter names. */
#define		IPOD_TRKINFO_MASK_CHP_NAME			(1 << IPOD_TRKINFO_CHP_NAME)

/** Track lyrics (only for current track). */
#define		IPOD_TRKINFO_MASK_LYRICS			(1 << IPOD_TRKINFO_LYRICS)

/** Track description. */
#define		IPOD_TRKINFO_MASK_DESCRIPTION		(1 << IPOD_TRKINFO_DESCRIPTION)

/** Album track index. */
#define		IPOD_TRKINFO_MASK_TRACK_NUM			(1 << IPOD_TRKINFO_TRACK_NUM)

/** Disc set album index. */
#define		IPOD_TRKINFO_MASK_DISC_NUM			(1 << IPOD_TRKINFO_DISC_NUM)

/** Podcast release date (Year/Month/Day). */
#define		IPOD_TRKINFO_MASK_PODCAST_DATE		(1 << IPOD_TRKINFO_PODCAST_DATE)

/** Play count (0 = track not played). */
#define		IPOD_TRKINFO_MASK_PLAY_COUNT		(1 << IPOD_TRKINFO_PLAY_COUNT)

/** Skip count (0 = track not skipped). */
#define		IPOD_TRKINFO_MASK_SKIP_COUNT		(1 << IPOD_TRKINFO_SKIP_COUNT)

/** Last played date (Year/Month/Day). */
#define		IPOD_TRKINFO_MASK_LAST_PLAY			(1 << IPOD_TRKINFO_LAST_PLAY)

/** Year released. */
#define		IPOD_TRKINFO_MASK_YEAR				(1 << IPOD_TRKINFO_YEAR)

/** Star rating (0 -> 5). */
#define		IPOD_TRKINFO_MASK_STAR_RATING		(1 << IPOD_TRKINFO_STAR_RATING)

/** Series name. */
#define		IPOD_TRKINFO_MASK_SERIES_NAME		(1 << IPOD_TRKINFO_SERIES_NAME)

/** Season number (1 = 1st season). */
#define		IPOD_TRKINFO_MASK_SEASON_NUM		(1 << IPOD_TRKINFO_SEASON_NUM)

/** Track volume adjust (-100, 0, 100). */
#define		IPOD_TRKINFO_MASK_VOL_ADJUST		(1 << IPOD_TRKINFO_VOL_ADJUST)

/** Track equalizer preset index. */
#define		IPOD_TRKINFO_MASK_EQ_PRESET			(1 << IPOD_TRKINFO_EQ_PRESET)

/** Track bit rate (kbps). */
#define		IPOD_TRKINFO_MASK_BITRATE			(1 << IPOD_TRKINFO_BITRATE)

/** Bookmark offset from start of track (ms). */
#define		IPOD_TRKINFO_MASK_BOOK_OFF			(1 << IPOD_TRKINFO_BOOK_OFF)

/** Start/stop time offset (start/stop). */
#define		IPOD_TRKINFO_MASK_TIME_OFF			(1 << IPOD_TRKINFO_TIME_OFF)

// For IPOD_TRKINFO_MASK_CAPS

/** Track is an audiobook. */
#define		IPOD_TRK_CAPS_IS_AUDIOBOOK			0x00000001

/** Track has chapters. */
#define		IPOD_TRK_CAPS_HAS_CHAPTERS			0x00000002

/** Track has artwork. */
#define		IPOD_TRK_CAPS_HAS_ARTWORK			0x00000004

/** Track has lyrics. */
#define		IPOD_TRK_CAPS_HAS_LYRICS			0x00000008

/** Track is a podcast episode. */
#define		IPOD_TRK_CAPS_IS_PODCAST			0x00000010

/** Track has a release date. */
#define		IPOD_TRK_CAPS_HAS_RELEASE_DATE		0x00000020

/** Track has a description. */
#define		IPOD_TRK_CAPS_HAS_DESCRIPTION		0x00000040

/** Track is queued as video in playback engine. */
#define		IPOD_TRK_CAPS_IS_VIDEO				0x00000080

/** Track is capable of generating a Genius playlist. */
#define		IPOD_TRK_CAPS_IS_GENIUS_CAPABLE		0x00002000

/** Track is an iTunesU episode. */
#define		IPOD_TRK_CAPS_IS_ITUNESU_EPISODE	0x00004000

// Describes where the location of the track is
#define IPOD_TRK_IDENT_TYPE_UID			0x00
#define IPOD_TRK_IDENT_TYPE_PB			0x01
#define IPOD_TRK_IDENT_TYPE_DB			0x02
#define IPOD_TRK_IDENT_TYPE_ALL			0x03

/** 
 * Data structure for iPod/iPhone playback status. 
 */
typedef struct _ipod_play_status_s {

/** Capabilities of the playing track. One of:
 * @c IPOD_TRK_CAPS_IS_AUDIOBOOK		Track is an audiobook
 * @c IPOD_TRK_CAPS_HAS_CHAPTERS		Track has chapters
 * @c IPOD_TRK_CAPS_HAS_ARTWORK			Track has artwork
 * @c IPOD_TRK_CAPS_HAS_LYRICS			Track has lyrics
 * @c IPOD_TRK_CAPS_IS_PODCAST			Track is a podcast episode
 * @c IPOD_TRK_CAPS_HAS_RELEASE_DATE	Track has a release date
 * @c IPOD_TRK_CAP_HAS_DESCRIPTION		Track has a description
 * @c IPOD_TRK_CAPS_IS_VIDEO			Track is queued as video in playback engine
 * @c IPOD_TRK_CAPS_IS_GENIUS_CAPABLE	Track is capable of generating a Genius playlist
 * @c IPOD_TRK_CAPS_IS_ITUNESU_EPISODE	Track is an iTunesU episode
 */
	uint32_t			caps;

/** State of playback. One of:
 * @c IPOD_PLAYBACK_STATE_STOP			Pod/iPhone is in a stopped state
 * @c IPOD_PLAYBACK_STATE_PLAY			Pod/iPhone is in a playing state
 * @c IPOD_PLAYBACK_STATE_PAUSE			iPod/iPhone is in a paused state
 */
	uint32_t			state; 
	
/** iPod/iPhone is in a stopped state. */
#define IPOD_PLAYBACK_STATE_STOP		0

/** iPod/iPhone is in a playing state. */
#define IPOD_PLAYBACK_STATE_PLAY		1

/** iPod/iPhone is in a paused state. */
#define IPOD_PLAYBACK_STATE_PAUSE		2

/** Fast forward / Fast backward setting. One of:
 * @c IPOD_PLAYBACK_SPEED_REGULAR		Playing at regular speed
 * @c IPOD_PLAYBACK_SPEED_FASTFWD		Playing at fast forward
 * @c IPOD_PLAYBACK_SPEED_FASTREW		Playing fast backward
 */
	uint8_t				play_flags;
	
/** iPod/iPhone is playing at regular speed. */
#define IPOD_PLAYBACK_SPEED_REGULAR		0x00

/** iPod/iPhone is playing at fast forward. */
#define IPOD_PLAYBACK_SPEED_FASTFWD		0x01

/** iPod/iPhone is playing at fast rewind. */
#define IPOD_PLAYBACK_SPEED_FASTREW		0x02

	/** Total number of tracks in playback list. */
	uint32_t			trkidx_total;
	
	/** Currently playing track. */
	uint32_t			trkidx_current;
	
	/** Length of currently playing track (in ms). */
	uint32_t			trkpos_total;
	
	/** Position in currently playing track (in ms). */
	uint32_t			trkpos_current;
	
	
	uint32_t			chpidx_total;			/**<  Total number of chapters (0=no chapters). */
	uint32_t			chpidx_current;			/**<  Currently playing chapter. */
	uint32_t			chppos_total;			/**<  Length of currently playing chapter (in ms, -1 if unknown). */
	uint32_t			chppos_start;			/**<  Position from start of track to start of chapter (in ms, -1 if unknown). */
	uint8_t				repeat;					/**< If PLAYBACK_FLAG_SHUFFLE_REPEAT set, current repeat state. */
	uint8_t				shuffle;				/**< If PLAYBACK_FLAG_SHUFFLE_REPEAT set, current shuffle state. */
	uint8_t				reserved[16];
} ipod_play_status_t;					

#define IPOD_INFO_CONNECT_SERIAL		0x00000001
#define IPOD_INFO_CONNECT_USB			0x00000002
#define IPOD_INFO_AUDIO_ANALOG			0x00000004
#define IPOD_INFO_AUDIO_DIGITAL			0x00000008
#define IPOD_INFO_AUTH_TYPE			0x00000010
#define IPOD_INFO_SUPPORT_VIDEO			0x00000020

/** Data structure for image properties. */
struct _ipod_img_desc {
	uint32_t					width;			/**< Width in pixels. */
	uint32_t					height;			/**< Height in pixels. */
	uint32_t					size;			/**< Size in bytes. */
	uint32_t					reserved;		/**< Reserved */
	char						mimetype[64];	/**< Type of image */
};

#define ALBART_FLAG_POS_NONE		0x00000000	/**< No position information. */
#define ALBART_FLAG_POS_TRKPOS		0x00000001	/**< Position is ms from start of track. */
#define ALBART_FLAG_POS_CHPIDX		0x00000002	/**< Position is chapter number. */
#define ALBART_FLAG_POS_MASK		0x0000000f

/** 
 * Data structure for album art image properties.
 */
struct _ipod_albart_entry {

/** Image index */
	uint16_t					index;		
	
/** No specific index (used for DCMD_MEDIA_ALBART_LOAD to best-match). */  		 
	#define ALBART_INDEX_NONE           0xffff   		 
	
/** Reserved. */
	uint16_t					reserved[3];

/** Flags that describe a position (ALBART_FLAG_POS_*) */
	uint32_t					flags;		

/** Chapter number or time (described by flags). */
	uint32_t					pos;		

/** Structure describing image sizes */
	struct _ipod_img_desc		desc;
};

/** Data structure for album art image properties */
struct _ipod_albart {

/** Flags that describe pos (ALBART_FLAG_POS_*) */
	uint32_t					flags;	
	
/** Chapter number or time (described by flags) */
	uint32_t					pos;		
	
/** Reserved */
	uint32_t					reserved[6];
	
/** Description of image sizes. */
	struct _ipod_img_desc		desc;
	
/** Image data including header. */
	uint8_t						data[1];
};

#define IPOD_RESTART_LINGO_SAME			0x0000		// Remount with same lingoes
#define IPOD_RESTART_LINGO_GENERAL		0x0001		// Remount with general lingo
#define IPOD_RESTART_LINGO_EXTENDED		0x0002		// Remount with extended lingo

struct ipod_itunesdb_info {
	uint64_t			uid;			// Database Unique Identifier
	struct tm			sync_tm;		// Last sync date/time to iTunes
	uint32_t			num_audio;		// Total audio tracks including audio podcasts and audiobooks
	uint32_t			num_video;		// Total video tracks
	uint32_t			num_book;		// Total audiobook count
	uint32_t			num_photo;		// Total photo count
};

/* PPS objects */
#define IPOD_PPS_OBJ_PLAYBACK				"playback"
#define IPOD_PPS_OBJ_GENERAL				"general"

/* PPS Attribute strings*/
#define IPOD_PPS_ATTR_PLAYBACK_PLAYSTATE	"PlayState"
#define IPOD_PPS_ATTR_PLAYBACK_SEEKSTATE	"SeekState"
#define IPOD_PPS_ATTR_PLAYBACK_TRKINDEX		"TrackIndex"
#define IPOD_PPS_ATTR_PLAYBACK_CHPINDEX		"ChapIndex"
#define IPOD_PPS_ATTR_PLAYBACK_TRKPOSMS		"TrackOffsetMs"
#define IPOD_PPS_ATTR_PLAYBACK_CHPPOSMS		"ChapOffsetMs"
#define IPOD_PPS_ATTR_PLAYBACK_CHPTOTAL		"NumChapters"
#define IPOD_PPS_ATTR_PLAYBACK_PBCHANGE		"NumTracks"
#define IPOD_PPS_ATTR_PLAYBACK_SHUFFLE		"Shuffle"
#define IPOD_PPS_ATTR_PLAYBACK_REPEAT		"Repeat"
#define IPOD_PPS_ATTR_PLAYBACK_UID			"UID"

#define IPOD_PPS_ATTR_GENERAL_DBCHANGE		"DatabaseChanged"
#define IPOD_PPS_ATTR_GENERAL_NOWPLAYID		"NowPlayingAppBundleName"
#define IPOD_PPS_ATTR_GENERAL_NOWPLAYAPP	"NowPlayingAppDisplayName"

/* Values for IPOD_PPS_ATTR_PLAYBACK_PLAYSTATE */
#define IPOD_PPS_VAL_PLAYBACK_PLAYSTATE_STOPPED		"stopped"
#define IPOD_PPS_VAL_PLAYBACK_PLAYSTATE_PLAYING		"playing"
#define IPOD_PPS_VAL_PLAYBACK_PLAYSTATE_PAUSED		"paused"

/* Values for IPOD_PPS_ATTR_PLAYBACK_SEEKSTATE */
#define IPOD_PPS_VAL_PLAYBACK_SEEKSTATE_NONE		"none"
#define IPOD_PPS_VAL_PLAYBACK_SEEKSTATE_FFWD		"ffwd"
#define IPOD_PPS_VAL_PLAYBACK_SEEKSTATE_FREW		"frew"

/* Values for IPOD_PPS_ATTR_PLAYBACK_SHUFFLE */
#define IPOD_PPS_VAL_PLAYBACK_SHUFFLE_OFF			"off"
#define IPOD_PPS_VAL_PLAYBACK_SHUFFLE_TRACK			"tracks"
#define IPOD_PPS_VAL_PLAYBACK_SHUFFLE_ALBUM			"albums"

/* Values for IPOD_PPS_ATTR_PLAYBACK_REPEAT */
#define IPOD_PPS_VAL_PLAYBACK_REPEAT_OFF			"off"
#define IPOD_PPS_VAL_PLAYBACK_REPEAT_ONE			"one"
#define IPOD_PPS_VAL_PLAYBACK_REPEAT_ALL			"all"

__END_DECLS


#endif /* _IPOD_TYPES_H_INCLUDED */

/* __SRCVERSION("$URL$ $Rev: 230799 $"); */
