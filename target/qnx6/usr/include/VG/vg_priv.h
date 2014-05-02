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

#ifndef _VG_PRIV_H_
#define _VG_PRIV_H_

#include <gfpr/gfpr.h>

#ifndef VG_API_ENTRYP
#   define VG_API_ENTRYP VG_API_ENTRY*
#endif

#define QNX_VG_FUNCTION_TABLE      0x6000

enum {
    #define A(r,n,s,a) _VG_##n,
    #include <VG/vg.defs>
    #undef A
    _VG_FUNCTION_TABLE_SIZE
};

#define A(r,n,s,a) typedef r (VG_API_ENTRYP PFNVG##n##PROC) s;
#include <VG/vg.defs>
#undef A

typedef void (* VG_API_ENTRYP _vg_fntbl_t)();
extern gfpr_thread_key_t _vg_fntbl;

#endif /* _VG_PRIV_H_ */
