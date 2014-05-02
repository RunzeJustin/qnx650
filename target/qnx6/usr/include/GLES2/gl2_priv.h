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

#ifndef _GL2_PRIV_H_
#define _GL2_PRIV_H_

#include <gfpr/gfpr.h>

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#define QNX_GLES2_FUNCTION_TABLE      0x6000

enum {
    #define A(r,n,s,a) _GLES2_##n,
    #include <GLES2/gl2.defs>
    #undef A
    _GLES2_FUNCTION_TABLE_SIZE
};

#define A(r,n,s,a) typedef r (GL_APIENTRYP PFNGL##n##PROC) s;
#include <GLES2/gl2.defs>
#undef A

typedef void (* GL_APIENTRYP _gles2_fntbl_t)();
extern gfpr_thread_key_t _gles2_fntbl;

#endif /* _GL2_PRIV_H_ */
