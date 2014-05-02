/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef _WINMGR_IOMSG_H_INCLUDED
#define _WINMGR_IOMSG_H_INCLUDED

#ifndef _WIN32
#include <sys/iomsg.h>
#include <_pack64.h>
#else
    #ifdef _MSC_VER
    typedef int pid_t;
    #endif
#endif

#ifndef _IOMGR_WINDOW
#define _IOMGR_WINDOW  0x16
#endif

#define IOW_MAX_MSG_SIZE           (2048) 

#define IOW_HOLD_WINDOW_UPDATE         2 

/*
 * This version number is used to detect version mismatches between
 * OpenKODE and io-winmgr. At every release, the number should be incremented.
 */
#define IOW_VERSION                 0x00000001

#define IOW_PATH_NAME               "/dev/winmgr"

#define WIN_IOMSG_SIZEOF(u_type) \
    (sizeof(io_msg_t) + sizeof(int) + sizeof(int) + sizeof(u_type))

#ifdef _WIN32
/*
 * Message of _IO_MSG
 */
struct _io_msg {
    _Uint16t                    type;
    _Uint16t                    combine_len;
    _Uint16t                    mgrid;      /* manager id (sys/iomgr.h) */
    _Uint16t                    subtype;    /* manager specific subtype */
};

typedef union {
    struct _io_msg              i;
} io_msg_t;

#endif /* WIN32 */

enum {
    IOW_CONNECT                         = 0x0001,
    IOW_DISCONNECT                      = 0x0002,
    IOW_TERM                            = 0x0003,
    IOW_DUMP                            = 0x0004,
    IOW_CONFIG                          = 0x0005,
    IOW_CREATE                          = 0x0006,
    IOW_SET_PROPERTY                    = 0x0007,
    IOW_GET_PROPERTY                    = 0x0008,
    IOW_REALIZE                         = 0x0009,
    IOW_DESTROY                         = 0x000A,
    IOW_GET_EVENT                       = 0x000B,
    IOW_SET_EVENT                       = 0x000C,
    IOW_POST                            = 0x000D,
    IOW_GET_STATE                       = 0x000E,
    IOW_SET_STATE                       = 0x000F,
    IOW_ZORDER                          = 0x0010,
    IOW_DEBUG                           = 0x0011,
    IOW_SIDLIST                         = 0x0012,

    /* 
     * This is a multi-part request that can contain a mix of IOW_SET_PROPERTY 
     * and IOW_POST requests. This enables a number of property changes to a 
     * single window to be synchronized with content updates for that window 
     * (IOW_POST). 
     */ 
    IOW_TRANSACT                        = 0x0015, 
};

enum
{
    IOW_WINDOW_FLAG_DELEGATE            = (1 << 0),
    IOW_WINDOW_FLAG_MANAGED             = (1 << 1),
    IOW_WINDOW_FLAG_VISIBLE             = (1 << 2),
    IOW_WINDOW_FLAG_FOCUS               = (1 << 3),
    IOW_WINDOW_FLAG_SOURCE_ALPHA        = (1 << 4),
    IOW_WINDOW_FLAG_FOCUS_IMMUNE        = (1 << 5),
    IOW_WINDOW_FLAG_POINTER_FOCUS       = (1 << 6),
    IOW_WINDOW_FLAG_FREEZE              = (1 << 7),
    IOW_WINDOW_FLAG_MULTISAMPLED        = (1 << 8),
};

enum
{
    IOW_WINDOW_USAGE_CPU                = (1 << 0),
    IOW_WINDOW_USAGE_NATIVE             = (1 << 1),
    IOW_WINDOW_USAGE_OPENGL_ES1         = (1 << 2),
    IOW_WINDOW_USAGE_OPENGL_ES2         = (1 << 3),
    IOW_WINDOW_USAGE_OPENVG             = (1 << 4),
    IOW_WINDOW_USAGE_VIDEO              = (1 << 5),
    IOW_WINDOW_USAGE_CAPTURE            = (1 << 6),
};

enum
{
    IOW_ATTRIB_VALID_CLASS              = (1 << 0),
    IOW_ATTRIB_VALID_ID_STRING          = (1 << 1),
    IOW_ATTRIB_VALID_TITLE              = (1 << 2),
    IOW_ATTRIB_VALID_DISPLAY            = (1 << 3),
    IOW_ATTRIB_VALID_DELEGATE           = (1 << 4),
    IOW_ATTRIB_VALID_SURFACE_SIZE       = (1 << 5),
    IOW_ATTRIB_VALID_SOURCE_POSITION    = (1 << 6),
    IOW_ATTRIB_VALID_SOURCE_SIZE        = (1 << 7),
    IOW_ATTRIB_VALID_WINDOW_POSITION    = (1 << 8),
    IOW_ATTRIB_VALID_WINDOW_SIZE        = (1 << 9),
    IOW_ATTRIB_VALID_FORMAT             = (1 << 10),
    IOW_ATTRIB_VALID_USER_POINTER       = (1 << 11),
    IOW_ATTRIB_VALID_DELEGATE_POINTER   = (1 << 12),
    IOW_ATTRIB_VALID_GLOBAL_ALPHA       = (1 << 13),
    IOW_ATTRIB_VALID_SWAP_INTERVAL      = (1 << 14),
    IOW_ATTRIB_VALID_BRIGHTNESS         = (1 << 15),
    IOW_ATTRIB_VALID_CONTRAST           = (1 << 16),
    IOW_ATTRIB_VALID_HUE                = (1 << 17),
    IOW_ATTRIB_VALID_SATURATION         = (1 << 18),
    IOW_ATTRIB_VALID_LAYER              = (1 << 19),
    IOW_ATTRIB_VALID_USAGE              = (1 << 20),

    IOW_ATTRIB_VALID_MULTISAMPLED_FLAG  = (1 << 23),
    IOW_ATTRIB_VALID_DELEGATE_FLAG      = (1 << 24),
    IOW_ATTRIB_VALID_MANAGED_FLAG       = (1 << 25),
    IOW_ATTRIB_VALID_VISIBLE_FLAG       = (1 << 26),
    IOW_ATTRIB_VALID_FOCUS_FLAG         = (1 << 27),
    IOW_ATTRIB_VALID_SOURCE_ALPHA_FLAG  = (1 << 28),
    IOW_ATTRIB_VALID_FOCUS_IMMUNE_FLAG  = (1 << 29),
    IOW_ATTRIB_VALID_POINTER_FOCUS_FLAG = (1 << 30),
    IOW_ATTRIB_VALID_FREEZE_FLAG        = (1 << 31),
};

enum {
    IOW_L8                              = 0,
    IOW_R4_G4_B4_A4                     = 1,
    IOW_R5_G5_B5_A1                     = 2,
    IOW_R5_G6_B5                        = 3,
    IOW_R8_G8_B8                        = 4,
    IOW_R8_G8_B8_A8                     = 5,
    IOW_YVU9                            = 6,
    IOW_YVU9_INTERLACED                 = 7,
    IOW_YUV420                          = 8,
    IOW_YUV420_INTERLACED               = 9,
    IOW_NV12                            = 10,
    IOW_NV12_INTERLACED                 = 11,
    IOW_YV12                            = 12,
    IOW_YV12_INTERLACED                 = 13,
    IOW_UYVY                            = 14,
    IOW_UYVY_INTERLACED                 = 15,
    IOW_YUY2                            = 16,
    IOW_YUY2_INTERLACED                 = 17,
    IOW_YVYU                            = 18,
    IOW_YVYU_INTERLACED                 = 19,
    IOW_V422                            = 20,
    IOW_V422_INTERLACED                 = 21,
    IOW_AYUV                            = 22,
    IOW_AYUV_INTERLACED                 = 23,
};

enum {
    IOW_EVENT_NONE                      = 0,
    IOW_EVENT_CREATE                    = 1,
    IOW_EVENT_REALIZE                   = 2,
    IOW_EVENT_PROPERTY                  = 3,
    IOW_EVENT_FOCUS                     = 4,
    IOW_EVENT_REDRAW                    = 5,
    IOW_EVENT_CLOSE                     = 6,
    IOW_EVENT_STATE                     = 7,
    IOW_EVENT_INPUT                     = 8,
    IOW_EVENT_JOG                       = 9,
    IOW_EVENT_POINTER                   = 10,
    IOW_EVENT_JOYSTICK                  = 11,
    IOW_EVENT_KEYBOARD                  = 12,
    IOW_EVENT_USER                      = 13,
};

enum {
    IOW_INT32                           = 0,
    IOW_INT64                           = 1,
    IOW_FLOAT32                         = 2,
};

enum {
    IOW_BOTTOM                          = 0,
    IOW_LOWER_WINDOW                    = 1,
    IOW_RAISE_WINDOW                    = 2,
    IOW_TOP                             = 3,
    IOW_BELOW_WINDOW                    = 4,
};

typedef struct {
    _Uint32t                    valid;
    _Uint8t                     class[64];
    _Uint8t                     id_string[64];
    _Uint8t                     title[128];
    _Uint32t                    flags;
    _Int32t                     display;
    _Int32t                     delegate;
    _Int16t                     buf_size[2];
    _Int16t                     src_pos[2];
    _Int16t                     src_size[2];
    _Int16t                     win_pos[2];
    _Int16t                     win_size[2];
    _Uint8t                     alpha;
    _Uint8t                     interval;
    _Int16t                     brightness;
    _Int8t                      contrast;
    _Int8t                      hue;
    _Int8t                      saturation;
    _Int16t                     layer;
    _Int32t                     format;
    _Int32t                     usage;
    void                       *userptr;
    void                       *delegptr;
    _Uint8t                     hwvsync;
    _Uint8t                     reserved[7];
} win_properties_t;

typedef struct {
    _Uint8t                     type;
    union {
        _Int32t                 i;
        _Int64t                 l;
        float                   f;
    } u;
} win_state_t;

/*
 * IOW_SET_PROPERTY
 */
struct win_set_property_msg {
            _Uint32t            wid;
            win_properties_t    attribs;
};


/*
 * IOW_POST
 */
struct win_post_msg {
            _Uint32t            wid;
            _Int32t             sid;
            _Int16t             dirty_rect[4];
           _Uint32t            flags;
};

struct win_post_reply {
    _Int32t sid;
};

/*
 * IOW_TRANSACT
 */

/*
 * Each IOW_TRANSACT message has 'count' number of sub-messages. Each of these
 * messages start with the following header. The subtype can either be IOW_POST
 * or IOW_SET_PROPERTY. The data following the reserved field must be
 * interpreted as a win_post_msg or a win_set_property_msg depending on the
 * subtype.
 */
struct win_transact_part {
    _Int16t                         subtype;
    _Int16t                         size;
    _Int16t                         reserved[2];
    union {
        struct win_post_msg         post;
        struct win_set_property_msg set_property;
    } u;
};

struct win_transact_msg {
    _Uint32t                 count;
    _Int32t                  reserved;
    struct win_transact_part parts[0];
};

typedef struct {
    io_msg_t                    iomsg;
    _Int32t                     connection;
    _Int32t                     reserved;
    union {
        struct {
            _Uint32t            version;
        } connect;
        struct {
            _Uint8t             verbose;
            _Uint8t             reserved[11];
        } debug;
        struct {
            _Uint32t            wid;
        } destroy;
        struct {
            _Uint8t             filename[64];
        } dump;
        struct {
            _Uint64t            timeout;
        } get_event;
        struct {
            _Int32t             index;
        } get_state;
        struct {
            _Uint32t            wid;
        } get_property;
        struct win_post_msg           post;
        struct {
            _Uint32t            wid;
        } realize;
        struct {
            _Int32t             wid;
            _Int32t             type;
            _Int64t             timestamp;
            union {
                struct {
                    _Int32t     sid;
                } realize;
                struct {
                    _Int32t     pname;
                } property;
                struct {
                    _Int32t     state;
                } focus;
                struct {
                    _Int32t     index;
                    win_state_t value;
                } state;
                struct {
                    _Int32t     index;
                    win_state_t value;
                } input;
                struct {
                    _Int32t     index;
                    _Int32t     count;
                } jog;
                struct {
                    _Int32t     index;
                    _Int32t     select;
                    _Int32t     x;
                    _Int32t     y;
                } pointer;
                struct {
                    _Int32t     index;
                    _Int32t     x;
                    _Int32t     y;
                    _Int32t     z;
                } joystick;
                struct {
                    _Int32t     index;
                    _Uint32t    flags;
                    _Uint32t    modifiers;
                    _Uint32t    key_cap;
                    _Uint32t    key_scan;
                    _Uint32t    key_sym;
                } keyboard;
                struct {
                    _Int32t     data[4];
                } user;
            } data;
        } set_event;
        struct win_set_property_msg   set_property;
        struct {
            _Int32t             index;
            win_state_t         value;
        } set_state;
        struct {
            _Uint32t            wid;
        } sidlist;
        struct {
            _Uint32t            wid;
            _Int32t             order;
            _Uint32t            above;
        } zorder;
        struct win_transact_msg       transact;
    } u;
} win_iomsg_t;

typedef struct {
    union {
        struct {
            _Int32t             connection;
        } connect;
        struct {
            _Uint32t            wid;
        } create;
        struct {
            _Int32t             type;
            _Int32t             delegate;
            _Uint64t            timestamp;
            void               *ptr;
            union {
                struct {
                    _Int32t     wid;
                } close;
                struct {
                    _Int32t     qid;
                    _Uint32t    wid;
                } create;
                struct {
                    _Uint32t    wid;
                    _Int32t     sid;
                } realize;
                struct {
                    _Uint32t    wid;
                    _Int32t     pname;
                } property;
                struct {
                    _Uint32t    wid;
                    _Int32t     state;
                } focus;
                struct {
                    _Int32t     index;
                    win_state_t value;
                } state;
                struct {
                    _Int32t     index;
                    win_state_t value;
                } input;
                struct {
                    _Int32t     index;
                    _Int32t     count;
                } jog;
                struct {
                    _Int32t     index;
                    _Int32t     select;
                    _Int32t     x;
                    _Int32t     y;
                } pointer;
                struct {
                    _Int32t     index;
                    _Int32t     x;
                    _Int32t     y;
                    _Int32t     z;
                } joystick;
                struct {
                    _Int32t     index;
                    _Uint32t    flags;
                    _Uint32t    modifiers;
                    _Uint32t    key_cap;
                    _Uint32t    key_scan;
                    _Uint32t    key_sym;
                } keyboard;
                struct {
                    _Int32t     data[4];
                } user;
            } data;
        } get_event;
        struct {
            win_properties_t    attribs;
        } get_property;
        struct {
            win_state_t         value;
        } get_state;
        struct win_post_reply         post;
        struct {
            _Int32t             sid;
        } realize;
        struct {
            _Int32t             count;
            _Int32t             sids[32];
            _Int32t             reserved[2];
        } sidlist;
    } u;
} win_iomsg_reply_t;

#ifndef _WIN32
#include <_packpop.h>
#endif

#endif /* _WINMGR_IOMSG_H_INCLUDED */
