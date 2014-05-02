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

#ifndef _EGL_BACKEND_H_
#define _EGL_BACKEND_H_

#include <gf/gf.h>
#include <gf/gf_internals.h>

typedef struct {
    int (*init)(gf_dev_t gf_dev);

    int (*query_config)(gf_dev_t gf_dev,
        int idx, disp_rend_buffer_config_t *config);

    void *(*create_context)(gf_dev_t gf_dev,
        disp_rend_buffer_config_t *info, void *share_ctx);

    void (*destroy_context)(void *api_ctx);

    void *(*create_target)(gf_dev_t gf_dev, int config, int width, int height, const EGLint *attrib_list);

    void (*destroy_target)(gf_dev_t gf_dev, void *target);

    void (*make_current)(gf_dev_t gf_dev, void *api_ctx, void *taget,
        struct _gf_rendersurf *draw, struct _gf_rendersurf *read);

    void (*render_target)(disp_surface_t *surf);

    void (*flush)(void);

    void (*wait)(void);

    void (*(*get_proc_address)(gf_dev_t gf_dev, const char *procname))(void);
} egl_interface_t;

struct egl_display;
struct egl_surface;

typedef struct {
    void (*get_configs)(struct egl_display *egl_disp);

    int (*create_window)(struct egl_display *egl_disp,
        struct egl_surface *egl_surf, void *win);

    int (*post_window)(struct egl_surface *egl_surf);

    int (*swap_interval)(struct egl_surface *egl_surf);

    void (*free_window)(struct egl_surface *egl_surf);

    void (*detach)(struct egl_display *egl_disp);
} egl_winsys_t;

#endif /* _EGL_BACKEND_H_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/BX650_3549_pasa-ccr/lib/khronos/devg/egl/private/EGL/egl_backend.h $ $Rev: 230895 $" )
