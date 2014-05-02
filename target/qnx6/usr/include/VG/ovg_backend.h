/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _OVG_BACKEND_H
#define _OVG_BACKEND_H

#include "VG/ovg11_api_backend.h"

// GN TODO The egl.h include needs to go in the egl_backend, but it would break GLES
// GN TODO so for now it can go here...
#include <EGL/egl.h>
#include <EGL/egl_backend.h>

#include <graphics/display.h>

struct ovg_context;

typedef struct ovg_backend_interface
{
    int (*init)(int pulseprio);
	void (*fini)();
	void (*terminate)();
	struct ovg_context *(*create_context)();
	void (*destroy_context)(struct ovg_context *ctx);
	int (*wait_idle)(struct ovg_context *ctx);
	int (*get_alloc_info)(int width, int height, unsigned format, unsigned flags,
							unsigned user_flags, disp_alloc_info_t *info);
	void (*terminate_notify)(pid_t pid);
	int (*blit2)(struct ovg_context *ctx, disp_surface_t *src, disp_surface_t *dst,
					int sx, int sy, int dx, int dy, int width, int height, int ignoreAlpha, int blockOnIrq);
} ovg_backend_interface_t;

typedef int (*get_ovg_vg11_funcs_t)(ovg11_interface_t *funcs, int tabsize);
typedef int (*get_ovg_vg_egl14backend_funcs_t)(egl_interface_t *funcs, int tabsize);
typedef int (*get_ovg_backend_funcs_t)(ovg_backend_interface_t *funcs, int tabsize);

extern int ovg_get_vg11_funcs(ovg11_interface_t *funcs, int tabsize);
extern int ovg_get_vg_egl14backend_funcs(egl_interface_t *funcs, int tabsize);
extern int ovg_get_backend_funcs(ovg_backend_interface_t *funcs, int tabsize);

typedef struct ovg_backend_interfaces
{
	ovg11_interface_t vg11_funcs;
	egl_interface_t egl14_vgfuncs;
	ovg_backend_interface_t ovg_backend_funcs;
} ovg_backend_interfaces_t;

#endif // _OVG_BACKEND_H

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/trunk/lib/openvg/G12/ovg/bb2d/gx_2d.h $ $Rev: 219724 $" )
