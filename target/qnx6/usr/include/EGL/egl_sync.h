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

#ifndef _EGL_SYNC_H_
#define _EGL_SYNC_H_

#ifndef EGL_KHR_sync
#define EGL_KHR_sync 1
typedef void* EGLSyncKHR;
typedef uint64_t EGLTimeKHR;
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR    0x30F0
#define EGL_SYNC_STATUS_KHR                     0x30F1
#define EGL_SIGNALED_KHR                        0x30F2
#define EGL_UNSIGNALED_KHR                      0x30F3
#define EGL_AUTO_RESET_KHR                      0x30F4
#define EGL_SYNC_FLUSH_COMMANDS_BIT_KHR         0x0001
#define EGL_FOREVER_KHR                         (~0)
#define EGL_TIMEOUT_EXPIRED_KHR                 0x30F5
#define EGL_CONDITION_SATISFIED_KHR             0x30F6
#define EGL_SYNC_TYPE_KHR                       0x30F7
#define EGL_SYNC_CONDITION_KHR                  0x30F8
#define EGL_SYNC_FENCE_KHR                      0x30F9
#define EGL_NO_SYNC_KHR                         ((EGLSyncKHR)0)
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateFenceSyncKHR (EGLDisplay dpy, EGLenum condition, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATEFENCESYNCKHRPROC) (EGLDisplay dpy, EGLenum condition, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLFENCEKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value);
#endif /* EGL_KHR_sync */

#endif /* _EGL_SYNC_H_*/
