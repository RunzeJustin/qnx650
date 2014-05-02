/*
 * Copyright 2003, QNX Software Systems Ltd. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems Ltd.  (QSSL) and its licensors. Any use, reproduction,
 * modification, disclosure, distribution or transfer of this software,
 * or any software which includes or is based upon any of this code, is
 * prohibited unless expressly authorized by QSSL by written agreement. For
 * more information (including whether this source code file has been
 * published) please email licensing@qnx.com.
 */

/*
 *  dcmd_fsys.h   Non-portable low-level devctl definitions
 *
 */

#ifndef __DCMD_FSYS_H_INCLUDED
#define __DCMD_FSYS_H_INCLUDED

#ifndef __DCMD_BLK_H_INCLUDED
#include <sys/dcmd_blk.h>		/* Include older defined _DCMD_FSYS entries */
#endif
#ifndef __UUID_H_INCLUDED
#include <sys/uuid.h>
#endif

struct dcmd_pass {
	short int	passlen;
	char		passdat[256];
} ;

#define DCMD_FSYS_UUID			__DIOF(_DCMD_FSYS,  21, struct uuid)	// Get the filesystem UUID
#define DCMD_FSYS_DIR_NFILES	__DION(_DCMD_FSYS,  22)					// Return number of files in a directory
#define DCMD_FSYS_PASS_USE		__DIOT(_DCMD_FSYS,  23, struct dcmd_pass)	// Use this as outer key
#define DCMD_FSYS_PASS_CHG		__DIOT(_DCMD_FSYS,  24, struct dcmd_pass[2])	// Change outer key
#define DCMD_FSYS_PASS_NEW		__DIOT(_DCMD_FSYS,  25, struct dcmd_pass[2])	// Change inner key
#define DCMD_FSYS_CACHE_SET		__DIOTF(_DCMD_FSYS,  26, unsigned[8])	// Set num cache blks

/* For DCMD_FSYS_CACHE_SET */
#define CACHE_NUM_NOCHG		~0
enum { CACHE_PAGE = 0, CACHE_BUNDLE, CACHE_WAD, CACHE_THRONG };	// Only 4 of 8 defined

#define FS_FLAGS_ENCRYPTED	0x0004

#endif

/* __SRCVERSION("dcmd_fsys.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/lib/public/sys/dcmd_fsys.h $ $Rev: 680334 $")
#endif
