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

#ifndef _GL_PRIV_H_
#define _GL_PRIV_H_

#include <gfpr/gfpr.h>

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#define QNX_GLES1_FUNCTION_TABLE      0x6000
#define QNX_GLES1_CM_FUNCTION_TABLE   0x6001

enum {
    #define A(r,n,s,a) _GLES_##n,
    #include <GLES/gl_cm.defs>
    #undef A
    _GLES_CM_FUNCTION_TABLE_SIZE
};

/* Available in both Common and Common-Lite profiles */
enum {
    #define A(r,n,s,a) _GLES_##n,
    #include <GLES/gl_cl.defs>
    #undef A
    _GLES_FUNCTION_TABLE_SIZE
};

#define A(r,n,s,a) typedef r (GL_APIENTRYP PFNGL##n##PROC) s;
#include <GLES/gl_cl.defs>
#undef A

#define A(r,n,s,a) typedef r (GL_APIENTRYP PFNGL##n##PROC) s;
#include <GLES/gl_cm.defs>
#undef A

typedef void (* GL_APIENTRYP _gles1_fntbl_t)();
extern gfpr_thread_key_t _gles1_cm_fntbl;
extern gfpr_thread_key_t _gles1_fntbl;

#endif /* _GL_PRIV_H_ */
