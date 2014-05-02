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

#ifndef _EGL_IMAGE_H_
#define _EGL_IMAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define EGL_NEW_IMAGE_KHR                     0x32D2

#define EGL_DATA_TYPE_KHR                     0x32D3
#define EGL_ELEMENT_TYPE_KHR                  0x32D4
#define EGL_COMPONENTS_KHR                    0x32D5
#define EGL_COMPRESSION_TYPE_KHR              0x32D6
#define EGL_MIN_X_BITS_KHR                    0x32D7
#define EGL_MIN_Y_BITS_KHR                    0x32D8
#define EGL_MIN_Z_BITS_KHR                    0x32D9
#define EGL_MIN_W_BITS_KHR                    0x32DA
#define EGL_MIN_SAMPLES_KHR                   0x32DB
#define EGL_IMAGE_FORMAT_KHR                  0x32DC
#define EGL_PREMULTIPLICATION_ORDER_KHR       0x32DD

/* EGL_DATA_TYPE_KHR values */
#define EGL_UNSIGNED_NORMALIZED_KHR           0x32DE
#define EGL_FLOAT_KHR                         0x32DF

/* EGL_ELEMENT_TYPE_KHR values */
#define EGL_COLOR_KHR                         0x32E0
#define EGL_DEPTH_KHR                         0x32E1
#define EGL_STENCIL_KHR                       0x32E2
#define EGL_DEPTH_STENCIL_KHR                 0x32E3

/* EGL_COMPRESSION_TYPE_KHR values */
#define EGL_UNCOMPRESSED_KHR                  0x32E4

/* EGL_PREMULTIPLICATION_ORDER_KHR */    
#define EGL_BEFORE_COLORSPACE_CONVERSION_KHR  0x32E5
#define EGL_AFTER_COLORSPACE_CONVERSION_KHR   0x32E6

/* Usage attributes */
#define EGL_SHARED_KHR                        0x32E7
#define EGL_OPENGL_USE_KHR                    0x32E8
#define EGL_OPENMAX_IL_USE_KHR                0x32E9
#define EGL_OPENVG_USE_KHR                    0x32EA
#define EGL_OPENWFD_USE_KHR                   0x32EB
#define EGL_CPU_USE_KHR                       0x32EC

/* EGL_OPENGL_USE_KHR bit values */
#define EGL_OPENGL_TEXTURE_BIT_KHR            (1 << 0)
#define EGL_OPENGL_RENDERBUFFER_BIT_KHR       (1 << 1)

/* EGL_OPENMAX_IL_USE_KHR bit values */
#define EGL_OPENMAX_IL_INPUT_BUFFER_BIT_KHR   (1 << 0) 
#define EGL_OPENMAX_IL_OUTPUT_BUFFER_BIT_KHR  (1 << 1) 

/* EGL_OPENVG_USE_KHR bit values */
#define EGL_OPENVG_IMAGE_BIT_KHR              (1 << 0)
#define EGL_OPENVG_RENDERBUFFER_BIT_KHR       (1 << 1)

/* EGL_OPENWFD_USE_KHR */
#define EGL_OPENWFD_INPUT_BUFFER_BIT_KHR      (1 << 0)

/* Other */
#define EGL_UNSUPPORTED_CODE_KHR              0x32ED

/* Client API-specific usage attributes */
#define EGL_OPENWFD_PIPELINE_KHR              0x32EE

#ifdef __cplusplus
}
#endif

#endif /*_EGL_IMAGE_H_*/
