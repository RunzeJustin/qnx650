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
#include <sys/syspage.h>

#define READDIR_CHUNK		64

int
mediafs_hier_build(struct mediafsmount *fmp, struct mediafsattr *fap, struct hier_file *last_hfp, unsigned index) {
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	struct mediafsattr		*fap2;
	unsigned				handpath[MAXPATHLEVELS];
	struct mediafsinode		*fip = alloca(fmp->fsmount.inode_size);
	int						num;
	struct media_readdir	*rdp;
	struct media_readdir	rdirs[READDIR_CHUNK];

	// Populate special files in .FS_info.
	if(fap->fsattr.fid == FID_MNTINFO_DIR(fmp)) {
		return avrcpexample_media_hier_build(fmp, fap, last_hfp);
	}

	// Walk up the directory saving the handpath.
	for(handpath[0] = 0, fap2 = fap; handpath[0] < MAXPATHLEVELS && fap2->fsattr.parent; fap2 = fap2->fsattr.parent) {
		handpath[++handpath[0]] = fap2->fsattr.offset;
		if(handpath[0] >= MAXPATHLEVELS) {
			return ENOENT;		// Got a better error?
		}
	}

	rdp = rdirs;
	num = sizeof rdirs / sizeof *rdirs;

	rdp->handle = last_hfp ? GET_OFFSET(last_hfp) : READDIR_FIRST;
	rdp->mode = index;
	num = dep->funcs.readdir(dep, handpath, rdp, num, last_hfp ? READDIR_FLAG_BUILD : READDIR_FLAG_FIRST | READDIR_FLAG_BUILD);
	if(num < 0) {
		int					status = errno;

		if(status == EAGAIN) {
			// device may take a while to read entries, if it takes too long it will stop short (e.g. ipod @ 57600 baud)
			SET_SIBLING(last_hfp, FID_LDDIR);
		}
		// io error from filesystem
		return status;
	}
	if(num > sizeof rdirs / sizeof *rdirs) {
		// Bad filesystem returning more than allowed to (past end of buffer...)
		fs_log(dep->device.driver->iface.module->name, _SLOG_ERROR, "Too many files returned %d", num);
		return EBADFSYS;
	}
	if(num == 0) {
		// No more files to read...
		return EOK;
	}

	for(; num--; rdp++) {
		unsigned				namesum, fid;

		namesum = mediafs_cpyfname(fip->fsinode.name, fmp->fsmount.fname_maxlen, rdp);
		if(namesum == -1) {
			fs_log(dep->device.driver->iface.module->name, _SLOG_ERROR, "Filename to long '%s', ignoring", fip->fsinode.name);
			// Name too long
			continue;
		}

		if((fid = hier_alloc(&fmp->fsmount, namesum, rdp->handle)) == FID_FREE) {
			return ENFILE;
		}

		if(S_ISDIR(rdp->mode)) {
			struct hier_dir				*hdp;

			if(!(hdp = hier_getdir(&fmp->fsmount, fid, 1))) {
				hier_free(&fmp->fsmount, fid);
				return ENFILE;
			}
			INC_NLINKS(fap->fsattr.dir);
			SET_PARENT(hdp, fap->fsattr.fid);
			SET_CHILD(hdp, FID_LDDIR);
		} else if(!S_ISREG(rdp->mode)) {
			// Media has some non-regular files
			dep->flags |= MEDIA_NONREG;
		}

		if(last_hfp) {
			SET_SIBLING(last_hfp, fid);
		} else {
			SET_CHILD(fap->fsattr.dir, fid);
		}
		last_hfp = GET_HPTR(&fmp->fsmount, fid);

		fip->fsinode.namelen = strlen(fip->fsinode.name);
		fip->fsinode.flags = NODE_GET_NAME | NODE_GET_CACHE_NAME;
		mcache_fsinode_set(&fmp->fsmount, fid, fip);
	}

	// Not finished yet
	SET_SIBLING(last_hfp, FID_LDDIR);

	return EOK;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/hier.c $ $Rev: 680334 $")
#endif
