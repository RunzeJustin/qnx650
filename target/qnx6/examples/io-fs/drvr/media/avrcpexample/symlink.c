/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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

#include "mediafs.h"

#ifdef MEDIA_CURRENT
int mediafs_playback_current(struct mediafsmount *fmp, char *buf, size_t bufmax) {
	return straddstr(".", 0, &buf, &bufmax);
}
#endif

int
mediafs_symlink_get(struct mediafsmount *fmp, struct mediafsattr *fap, char *sympath, unsigned len) {
	struct mediafsdevice		*dep = fmp->fsmount.blkdev->dev;
	unsigned				handpath[MAXPATHLEVELS];

	if(!dep->funcs.readlink) {
		return ENOSYS;
	}

IFDBG if(fap->fsattr.fid == FID_ROOT) abort();

	// Walk up the directory saving the handpath.
	for(handpath[0] = 0; handpath[0] < MAXPATHLEVELS && fap->fsattr.parent; fap = fap->fsattr.parent) {
		handpath[++handpath[0]] = fap->fsattr.offset;
		if(handpath[0] >= MAXPATHLEVELS) {
			return ENOENT;		// Got a better error?
		}
	}

	return dep->funcs.readlink(dep, &handpath[0], sympath, len);
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/symlink.c $ $Rev: 680334 $")
#endif
