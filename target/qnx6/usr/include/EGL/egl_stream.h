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

#ifndef _EGL_STREAM_H_
#define _EGL_STREAM_H_

#include <gfpr/gfpr.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EGL_QNX_image_stream
#define EGL_QNX_image_stream 0

typedef void *EGLImageStreamQNX;

#define EGL_NO_IMAGE_STREAM_QNX              ((EGLImageStreamQNX)0)
#define EGL_BAD_IMAGE_STREAM_QNX             0x32FF

/**
 * Producer and consumer attributes accepted by eglCreateImageStreamEAB
 */
#define EGL_API_ID_QNX                       0x32F0
#define EGL_GLES_MIPMAP_TEXTURE_QNX          0x32F1
#define EGL_WFC_CONTEXT_QNX                  0x32F2
#define EGL_WFD_PIPELINE_QNX                 0x32F3
#define EGL_WF_USAGE_QNX                     0x32F4

/**
 * Accepted by the EGL_API_ID attribute list value of eglCreateImageStreamEAB in
 * addition to the existing API bit flags.
 */
//#define EGL_OPENGL_ES_BIT                  0x0001  /* EGL_RENDERABLE_TYPE mask bits */
//#define EGL_OPENVG_BIT                     0x0002  /* EGL_RENDERABLE_TYPE mask bits */
//#define EGL_OPENGL_ES2_BIT                 0x0004  /* EGL_RENDERABLE_TYPE mask bits */
//#define EGL_OPENGL_BIT                     0x0008  /* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENMAX_IL_BIT_QNX               0x0010
#define EGL_OPENMAX_AL_BIT_QNX               0x0020
#define EGL_OPENWFC_BIT_QNX                  0x0040
#define EGL_OPENWFD_BIT_QNX                  0x0080
#define EGL_CLIENT_BIT_QNX                   0x0100  /* Client/User/Application? */

/**
 * Accepted by the EGL_WF_USAGE attribute list value of eglCreateImageStreamEAB.
 */
#define EGL_WF_USAGE_SOURCE_BIT_QNX          0x0001
#define EGL_WF_USAGE_MASK_BIT_QNX            0x0002

/**
 * Stream attributes accepted by eglQueryStream and eglStreamAttrib
 */
#define EGL_IMAGE_STREAM_PRIORITY_QNX        0x32F6
#define EGL_IMAGE_STREAM_FRAME_RATE_QNX      0x32F7
#define EGL_IMAGE_STREAM_NATIVE_FORMAT_QNX   0x32F8

/**
 * Base priorities
 */
#define EGL_IMAGE_STREAM_PRIORITY_LOW_QNX    0x32F8
#define EGL_IMAGE_STREAM_PRIORITY_NORMAL_QNX 0x32F9
#define EGL_IMAGE_STREAM_PRIORITY_HIGH_QNX   0x32FA

/* EGL Stream Functions */

#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageStreamQNX EGLAPIENTRY eglCreateImageStreamQNX(EGLDisplay dpy, const EGLint *stream_attrib_list, const EGLint *producer_attrib_list, const EGLint *consumer_attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglInitializeImageStreamQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR *images, EGLint num_images);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageStreamQNX(EGLDisplay dpy, EGLImageStreamQNX stream);
EGLAPI EGLImageKHR EGLAPIENTRY eglAcquireImageStreamBackBufferQNX(EGLDisplay dpy, EGLImageStreamQNX stream);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseImageStreamBackBufferQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR image, const EGLint *dirty_rect);
EGLAPI EGLImageKHR EGLAPIENTRY eglAcquireImageStreamFrontBufferQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLint *dirty_rect);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseImageStreamFrontBufferQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR image);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryImageStreamQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLint attribute, EGLint *value);
EGLAPI EGLBoolean EGLAPIENTRY eglImageStreamAttribQNX(EGLDisplay dpy, EGLImageStreamQNX stream, EGLint attribute, EGLint value);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLImageStreamQNX (EGLAPIENTRYP PFNEGLCREATEIMAGESTREAMQNXPROC) (EGLDisplay dpy, const EGLint *stream_attrib_list, const EGLint *producer_attrib_list, const EGLint *consumer_attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEIMAGESTREAMQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR *images, EGLint num_images);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGESTREAMQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream);
typedef EGLImageKHR (EGLAPIENTRYP PFNEGLACQUIREIMAGESTREAMBACKBUFFERQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLRELEASEIMAGESTREAMBACKBUFFERQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR image, const EGLint *dirty_rect);
typedef EGLImageKHR (EGLAPIENTRYP PFNEGLACQUIREIMAGESTREAMFRONTBUFFERQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLint *dirty_rect);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLRELEASEIMAGESTREAMFRONTBUFFERQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLImageKHR image);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYIMAGESTREAMQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLint attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLIMAGESTREAMATTRIBQNXPROC) (EGLDisplay dpy, EGLImageStreamQNX stream, EGLint attribute, EGLint value);
#endif /* EGL_QNX_image_stream */

#ifdef __cplusplus
}
#endif

#endif /* _EGL_STREAM_H_ */
