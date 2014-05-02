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

#ifndef _EGL_GF_H_
#define _EGL_GF_H_

#include <unistd.h>
#include <graphics/display.h>
#include <gf/gf.h>
#include <gf/gf_internals.h>
#include <winmgr/iow.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/egl_backend.h>

typedef EGLint EGLbitmask;

#define EGL_NO_THREAD (0)

#define EGL_NUM_APIS EGL_OPENGL_API-EGL_OPENGL_ES_API+1

#define EGL_GLOBAL_LOCK()            gfpr_mutex_lock(&egl_globals.mutex);
#define EGL_GLOBAL_UNLOCK()          gfpr_mutex_unlock(&egl_globals.mutex);
#define EGL_LOCK_DISPLAY(egl_disp)   gfpr_mutex_lock(&(egl_disp)->mutex)
#define EGL_UNLOCK_DISPLAY(egl_disp) gfpr_mutex_unlock(&(egl_disp)->mutex)
#define EGL_LOCK_SURFACE(egl_surf)   gfpr_mutex_lock(&(egl_surf)->mutex)
#define EGL_UNLOCK_SURFACE(egl_surf) gfpr_mutex_unlock(&(egl_surf)->mutex)

#define EGL_SIGNATURE_QNX            (1<<28)
#define EGL_GF_SIGNATURE             (EGL_SIGNATURE_QNX|(0<<24))
#define EGL_IOW_SIGNATURE            (EGL_SIGNATURE_QNX|(1<<24))
#define EGL_PHOTON_SIGNATURE         (EGL_SIGNATURE_QNX|(2<<24))
#define EGL_MASK_SIGNATURE           (0xff000000)
#define EGL_DISPLAY_SIGNATURE(x)     ((EGLint)(x) & 0xf0000000)

#define EGL_CONFIG_MAX_SWAP_INTERVAL 255

enum {
    EGL_OPENGL_ES_INTERFACE,
    EGL_OPENVG_INTERFACE,
    EGL_OPENGL_ES2_INTERFACE,
    EGL_OPENGL_INTERFACE,
    EGL_NUM_INTERFACES
};

enum {
    EGL_PBUFFER_SURFACE_TYPE,
    EGL_PIXMAP_SURFACE_TYPE,
    EGL_NATIVE_WINDOW_TYPE,
    EGL_COMPOSITED_WINDOW_TYPE,
};

enum {
    EGL_WFD_LAYER,
    EGL_NATIVE_LAYER,
    EGL_GLES1_LAYER,
    EGL_GLES2_LAYER,
    EGL_VG_LAYER,
};

enum {
    EGL_BLIT_BACK_TO_SINGLE,
    EGL_BLIT_SINGLE_TO_BACK,
    EGL_BLIT_SINGLE_TO_MAP,
    EGL_BLIT_BACK_TO_MAP,
    EGL_BLIT_MAP_TO_SINGLE,
    EGL_BLIT_MAP_TO_BACK
};

#ifdef NDEBUG
#define EGL_LOG_ERROR(err) \
    if (state->egl_errcode == EGL_SUCCESS) { \
        state->egl_errcode = err; \
    }
#else
#define EGL_LOG_ERROR(err) \
{ \
    fprintf(stderr, "EGL error [0x%04x] @%s:%d\n", err, __FILE__, __LINE__); \
    if (state->egl_errcode == EGL_SUCCESS) { \
        state->egl_errcode = err; \
    } \
}
#endif

/*
 * Description of capabilities associated with a pixel format.
 */

typedef struct egl_config {
    EGLint     egl_buffer_size;
    EGLint     egl_red_size;
    EGLint     egl_green_size;
    EGLint     egl_blue_size;
    EGLint     egl_luminance_size;
    EGLint     egl_alpha_size;
    EGLint     egl_alpha_mask_size;
    EGLBoolean egl_bind_to_texture_rgb;
    EGLBoolean egl_bind_to_texture_rgba;
    EGLenum    egl_color_buffer_type;
    EGLenum    egl_config_caveat;
    EGLint     egl_config_id;
    EGLbitmask egl_conformant;
    EGLint     egl_depth_size;
    EGLint     egl_level;
    EGLint     egl_max_pbuffer_width;
    EGLint     egl_max_pbuffer_height;
    EGLint     egl_max_pbuffer_pixels;
    EGLint     egl_max_swap_interval;
    EGLint     egl_min_swap_interval;
    EGLint     egl_match_native_pixmap;
    EGLBoolean egl_native_renderable;
    EGLint     egl_native_visual_id;
    EGLint     egl_native_visual_type;
    EGLbitmask egl_renderable_type;
    EGLint     egl_sample_buffers;
    EGLint     egl_samples;
    EGLint     egl_stencil_size;
    EGLbitmask egl_surface_type;
    EGLenum    egl_transparent_type;
    EGLint     egl_transparent_red;
    EGLint     egl_transparent_green;
    EGLint     egl_transparent_blue;
} egl_config_t;

/*
 * Container for state information necessary to perform rendering with one
 * of the supported APIs (OpenGL ES 1.X, OpenGL ES 2.X, OpenVG, OpenGL)
 */

typedef struct egl_context {
    struct egl_display *egl_disp;
    struct egl_surface *egl_read_surf;
    struct egl_surface *egl_draw_surf;
    struct egl_config  *egl_conf;
    EGLenum             egl_api;
    EGLint              egl_api_version;

    void               *api_ctx;
    egl_interface_t    *api_funcs;
    gfpr_thread_t       bound_thread;
    EGLBoolean          destroyed;
    struct egl_context *next;
} egl_context_t;

/*
 * Represents a connection to a device capable of blitting.
 */

typedef struct egl_device {
    int                gf_dev_idx;
    gf_dev_t           gf_dev;
    gf_dev_info_t      gf_dev_info;
    disp_3d_caps_t     gf_disp_caps;

    EGLint             refcnt;
    struct egl_device *next;
} egl_device_t;

/*
 * Stores information about how composition manager uses a layer.
 */

typedef struct iow_layer {
    int type;
    int format;
} iow_layer_t;

/*
 * Represents a connection to a display/windowing system.
 */

typedef struct egl_display {
    struct egl_device     *egl_dev;
    struct egl_context    *egl_ctx_list;
    struct egl_surface    *egl_surf_list;
    struct egl_image      *egl_img_list;
    EGLNativeDisplayType   egl_display_id;
    EGLint                 egl_num_configs;
    egl_config_t         **egl_configs;
    EGLBoolean             egl_initialized;
    EGLbitmask             egl_client_apis;

    struct {
        void              *handle;
        egl_interface_t    funcs;
        EGLBoolean         ready;
    } egl_ifaces[EGL_NUM_INTERFACES];

    struct {
        int                disp_idx;
        gf_display_t       disp;
        gf_display_info_t  info;
        useconds_t         swap_period;
    } gf;

    struct {
        iow_context_t      ctx;
        int                nlayers;
        iow_layer_t       *layers;
    } iow;

    struct egl_blit_op    *blit_ops_head;
    struct egl_blit_op    *blit_ops_tail;
    struct egl_blit_op    *free_blitop_head;
    struct egl_blit_op    *free_blitop_tail;

    gf_context_t           gf_ctx;
    gfpr_mutex_t           mutex;
    EGLint                 refcnt;
    struct egl_display    *next;
} egl_display_t;

/*
 * Holds a single buffer that contains pixel data.
 */

typedef struct egl_image {
    struct egl_display *egl_disp;
    EGLBoolean          egl_allocated;

    struct _gf_surface *gf_surf;
    struct egl_image   *next;
} egl_image_t;

/*
 * Container for images required to perform rendering. The number of images
 * required depends on the rendering API. Most APIs will require a color
 * buffer which could be double buffered. A multi-sampling buffer may be
 * stored in a surface. Finally, a depth, stencil, or combined depth and
 * stencil buffers may also be stored in a surface.
 */

typedef struct egl_surface {
    /* must be first argument for gf_context_set_surface_3d to work */
    struct _gf_rendersurf  gf_rsurf;

    gf_surface_t           gf_single;
    gf_surface_t           gf_back;
    gf_surface_t           gf_map_surf;

    struct egl_display    *egl_disp;
    struct egl_config     *egl_conf;
    struct egl_context    *egl_ctx;
    EGLenum                egl_vg_alpha_format;
    EGLenum                egl_vg_colorspace;
    EGLint                 egl_height;
    EGLint                 egl_hres;
    EGLBoolean             egl_largest_pbuf;
    EGLBoolean             egl_mipmap_tex;
    EGLint                 egl_mipmap_level;
    EGLenum                egl_multisample_resolve;
    EGLint                 egl_pixel_aspect;
    EGLenum                egl_render_buf;
    EGLint                 egl_swap_interval;
    EGLenum                egl_swap_behavior;
    EGLenum                egl_tex_fmt;
    EGLenum                egl_tex_target;
    EGLint                 egl_vres;
    EGLint                 egl_width;
    EGLBoolean             egl_locked;
    EGLBoolean             egl_lock_preserve_pixels;
    EGLbitmask             egl_lock_usage;
    uint64_t               egl_last_swap;

    union {
        struct {
            iow_window_t   win;
            EGLBoolean     hwvsync;
        } iow;
        struct {
            int            index;
            gf_layer_t     layer;
        } gf;
    } data;

    struct egl_blit_op    *last_blit_op;
    int                    flushed_blitops;
    EGLenum                type;
    EGLint                 posts;
    void                  *target;
    gfpr_mutex_t           mutex;
    EGLBoolean             destroyed;
    struct egl_surface    *next;
} egl_surface_t;

/*
 * blit op state data
 */

typedef struct egl_blit_op {
    struct egl_blit_op *next;
    egl_surface_t      *egl_src;
    egl_surface_t      *egl_dst;
    int                 sx1; 
    int                 sy1;
    int                 sx2;
    int                 sy2;
    int                 dx1;
    int                 dy1;
    int                 dx2;
    int                 dy2;
    gf_alpha_t          alpha;
    unsigned            filtering;
    EGLenum             type;
} egl_blit_op_t;

/*
 * Represents a mutex and condvar pair.
 */

typedef struct egl_sync {
    struct egl_display *egl_disp;
    EGLint              egl_type;
    EGLint              egl_status;
    EGLint              egl_condition;

    gfpr_mutex_t        mutex;
    gfpr_cond_t         condvar;
} egl_sync_t;

/*
 * This is the state the EGL needs to track on a per-thread basis.
 */

typedef struct egl_thread_state {
    EGLint              egl_errcode;
    EGLenum             egl_cur_api;
    struct egl_context *egl_cur_ctx[EGL_NUM_APIS];
} egl_thread_state_t;

/*
 * This is the state that is available to all threads.
 */

typedef struct egl_global_state {
    struct egl_device  *egl_dev_list;
    struct egl_display *egl_disp_list;
    EGLbitmask          egl_client_apis;
    EGLint              thread_count;
    gfpr_mutex_t        mutex;
} egl_global_state_t;

/* EGL global (per-process) state */
extern egl_global_state_t egl_globals;

/* EGL internal */
void eglAddConfig(egl_display_t *egl_disp, egl_config_t *egl_conf);

void eglBlit(egl_display_t *egl_disp, egl_surface_t *egl_surf, EGLint direction);

egl_config_t *eglConfig(egl_display_t *egl_disp, EGLConfig config);

egl_context_t *eglContext(egl_display_t *egl_disp, EGLContext ctx);

egl_display_t *eglDisplay(EGLDisplay dpy);

void eglFreeContext(egl_display_t *egl_disp, egl_context_t *egl_ctx);

void eglFreeDevice(egl_device_t *egl_dev);

void eglFreeDisplay(egl_display_t *egl_disp);

void eglFreeImage(struct egl_display *egl_disp, egl_image_t *egl_image);

void eglFreeSurface(egl_display_t *egl_disp, egl_surface_t *egl_surf);

egl_thread_state_t *eglGetState(void);

egl_image_t *eglImage(struct egl_display *egl_disp, EGLImageKHR image);

egl_surface_t *eglSurface(egl_display_t *egl_disp, EGLSurface surf);

void eglFlushBlitOps(egl_surface_t *egl_surf);

void eglDestroyFreeBlitList(egl_display_t *egl_disp);

/* EGL <-> windowing system interfaces */
int egl_gf_attach(egl_display_t *egl_disp);

int egl_gf_create_window(egl_display_t *egl_disp, egl_surface_t *egl_surf, EGLNativeWindowType win);

void egl_gf_free_window(egl_surface_t *egl_surf);

int egl_gf_post_window(egl_surface_t *egl_surf);

int egl_gf_swap_interval(egl_surface_t *egl_surf);

void egl_gf_detach(egl_display_t *egl_disp);

int egl_iow_create_window(egl_display_t *egl_disp, egl_surface_t *egl_surf, EGLNativeWindowType win);

void egl_iow_free_window(egl_surface_t *egl_surf);

int egl_iow_post_window(egl_surface_t *egl_surf);

int egl_iow_swap_interval(egl_surface_t *egl_surf);

void egl_iow_detach(egl_display_t *egl_disp);

#endif /* _EGL_GF_H_ */
