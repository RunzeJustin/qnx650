/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _EGL_PRIV_H_
#define _EGL_PRIV_H_

#include <gfpr/gfpr.h>

#define QNX_EGL_FUNCTION_TABLE 0x6000

enum {
    #define A(r,n,s,a) _EGL_##n,
    #include <EGL/egl.defs>
    #undef A
    _EGL_FUNCTION_TABLE_SIZE
};

typedef struct egl_disp_list {
    EGLNativeDisplayType  display_id;
    EGLDisplay            dpy;

    /* OpenGL ES 1.X Common Model and Common Lite profiles */
    void                 *gles1_handle;
    void               (**gles1_fntbl)();
    EGLBoolean            gles1_fntbl_allocated;
    void               (**gles1cm_fntbl)();
    EGLBoolean            gles1cm_fntbl_allocated;

    /* OpenVG */
    void                 *vg_handle;
    void               (**vg_fntbl)();
    EGLBoolean            vg_fntbl_allocated;
    EGLBoolean            vg_amanith;
    struct egl_disp_list *next;

    /* OpenGL ES 2.X */
    void                 *gles2_handle;
    void               (**gles2_fntbl)();
    EGLBoolean            gles2_fntbl_allocated;
} *egl_disp_list_t;

#define A(r,n,s,a) typedef r (EGLAPIENTRYP PFNEGL##n##PROC) s;
#include <EGL/egl.defs>
#undef A

typedef void (* EGLAPIENTRYP _egl_fntbl_t)();
extern _egl_fntbl_t _egl_fntbl;

KHRONOS_APICALL EGLBoolean __eglLoadGLES1FunctionTable(egl_disp_list_t disp);

KHRONOS_APICALL EGLBoolean __eglLoadGLES2FunctionTable(egl_disp_list_t disp);

KHRONOS_APICALL EGLBoolean __eglLoadVGFunctionTable(egl_disp_list_t disp);

KHRONOS_APICALL void __eglUnloadGLES1FunctionTable(egl_disp_list_t disp);

KHRONOS_APICALL void __eglUnloadGLES2FunctionTable(egl_disp_list_t disp);

KHRONOS_APICALL void __eglUnloadVGFunctionTable(egl_disp_list_t disp);

#endif /* _EGL_PRIV_H_ */
