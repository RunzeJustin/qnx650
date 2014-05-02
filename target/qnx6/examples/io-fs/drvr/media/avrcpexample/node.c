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

// Copy device filename to inode. escape slash and percent if nessessary.
// Dest buffer must be large enough for fname_max
int
mediafs_cpyfname(char *name, int dsize, const struct media_readdir *rdp) {
	char			*to = name;
	char			*from = rdp->name;

	// special case files starting with dot
	if(*from == '.' && dsize > 3) {
		*to++ = '%';
		*to++ = '2'; 	// '.' == 0x2e
		*to++ = 'E';
		dsize -= 3;
		from++;
	}

	// Copy string escaping "/"->"%2F" and "%"->"%25"
	if(copyuri(to, dsize, from, "/") >= dsize) {
		return -1;
	}

	return path_sum(name);
}

int
mediafs_node_get(struct mediafsmount *fmp, struct mediafsinode *fip, unsigned flags, const char *name) {
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	struct mediafsattr		*fap;
	int						err;
	unsigned				handpath[MAXPATHLEVELS];

	// Allow common media files to be handled
	if(fip->fsinode.fid >= FID_MEDIA_ROOT && fip->fsinode.fid < FID_MEDIA_LAST) {
		return avrcpexample_media_node_get(fmp, fip, flags, name);
	}

	// We always generate the attributes so don't cache them
	fip->fsinode.flags &= ~NODE_GET_CACHE_ATTRS;

	// We need to get the name to check for a match
	if(name) {
		flags |= NODE_GET_NAME;
	}

	// default all files to regular files
	fip->fsinode.mode = S_IFREG | 0444;
	if((flags & NODE_GET_MODE) && fip->fsinode.fid != FID_FREE && hier_getdir(&fmp->fsmount, fip->fsinode.fid, 0)) {
		fip->fsinode.mode = S_IFDIR | 0555;
		flags &= ~NODE_GET_MODE;
	}

	// special case accessing the root inode
	handpath[1] = 0;
	if(fap = fip->fsinode.parent) {
		// Walk up the directory saving the handpath.
		for(; fap->fsattr.parent && handpath[1] < MAXPATHLEVELS - 1; fap = fap->fsattr.parent) {
			handpath[++handpath[1] + 1] = fap->fsattr.offset;
			if(handpath[1] >= MAXPATHLEVELS - 1) {
#ifdef DBG
printf("--readdir=error(line=%d)\n", __LINE__);
#endif
				return ENOENT;		// Got a better error?
			}
		}
	} else {
		fip->fsinode.name[0] = '\0';
		flags &= ~NODE_GET_NAME;
	}

	// If we need a name call readdir to get the name
	if(flags & NODE_GET_NAME) {
		struct media_readdir	rdir;

		rdir.handle = fip->fsinode.offset;
#ifdef DBG
printf("--readdir( %#x )\n", rdir.handle);
#endif
		if(dep->funcs.readdir(dep, handpath + 1, &rdir, 1, 0) == 0) {
#ifdef DBG
printf("--readdir=0\n");
#endif
			return ENOENT;
		}
#ifdef DBG
printf("--readdir=1 %#x,%#o,%s\n", rdir.handle, rdir.mode, rdir.name);
#endif

		fip->fsinode.mode = rdir.mode;
		if(mediafs_cpyfname(fip->fsinode.name, fmp->fsmount.fname_maxlen, &rdir) < 0) {
#ifdef DBG
printf("--readdir=error(line=%d)\n", __LINE__);
#endif
			return ENOENT;		// Too long or too short
		}

		// We got some attributes, unset them
		flags &= ~(NODE_GET_NAME|NODE_GET_MODE);
	}

	if(name && strcmp(fip->fsinode.name, name)) {
		return ENOENT;
	}

	// Not got the attributes if needed
	if(flags & NODE_GET_ATTRS) {
		fip->fsinode.size  = 0;
		fip->fsinode.uid   = 0;
		fip->fsinode.gid   = 0;
		fip->fsinode.nlink = 1;
		fip->fsinode.atime = fip->fsinode.mtime = fip->fsinode.ctime = fmp->fsmount.stats.s_time_mount;

		// Only call getattr if more than inode is needed
		if((flags & (NODE_GET_ATTRS & ~NODE_GET_INODE)) != 0) {
			handpath[0] = handpath[1];
			if(fip->fsinode.parent) {
				handpath[0]++;
				handpath[1] = fip->fsinode.offset;
			}
#ifdef DBG
printf("--getattr(%#x)\n", handpath[0] ? handpath[1] : 0);
#endif
			if(err = dep->funcs.getattr(dep, handpath, fip, 0)) {
#ifdef DBG
printf("--getattr=error(%d)\n", err);
#endif
				return err;
			}
#ifdef DBG
printf("--getattr=%#o,%d\n", fip->fsinode.mode, fip->fsinode.nlink);
#endif
		}

		// Don't allow lower level to set inode. This allows readdir to be faster because getattr is not needed
		fip->fsinode.ino   = fip->fsinode.fid;

		if(S_ISDIR(fip->fsinode.mode) && fip->fsinode.nlink == 1) {
			fip->fsinode.nlink = 2;
		}
	}

	return EOK;
}

static int mediafs_notify_handler(void *handle) {
	struct mediafsattr		*fap = handle;

	notify(&fap->fsattr);
	return EOK;
}

int
mediafs_notify(struct mediafsmount *fmp, struct mediafsattr *fap) {
	struct mediafsattr		*fap2;
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	unsigned				handpath[MAXPATHLEVELS];

	// Walk up the directory saving the handpath.
	for(handpath[0] = 0, fap2 = fap; handpath[0] < MAXPATHLEVELS && fap2->fsattr.parent; fap2 = fap2->fsattr.parent) {
		handpath[++handpath[0]] = fap2->fsattr.offset;
		if(handpath[0] >= MAXPATHLEVELS) {
			return ENOENT;		// Got a better error?
		}
	}
#ifdef DBG
printf("--notify(%#x)\n", handpath[0] ? handpath[1] : 0);
#endif

	if(dep->funcs.notify) {
		return dep->funcs.notify(dep, &handpath[0], mediafs_notify_handler, (fap->fsattr.flags & FSATTR_NOTIFY) ? fap : 0);
	}

	return EOK;
}

int
mediafs_devctl(struct mediafsmount *fmp, resmgr_context_t *ctp, struct mediafsattr *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval) {
	struct mediafsattr		*fap2;
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	unsigned				handpath[MAXPATHLEVELS];

	// Walk up the directory saving the handpath.
	for(handpath[0] = 0, fap2 = fap; handpath[0] < MAXPATHLEVELS && fap2->fsattr.parent; fap2 = fap2->fsattr.parent) {
		handpath[++handpath[0]] = fap2->fsattr.offset;
		if(handpath[0] >= MAXPATHLEVELS) {
			return ENOENT;		// Got a better error?
		}
	}
#ifdef DBG
printf("--devctl(%#x,%#x)\n", handpath[0] ? handpath[1] : 0, dcmd);
#endif

	// Allow the media filesystem to do fast nfiles counts for directories
	if(dcmd == DCMD_FSYS_DIR_NFILES) {
		if(dep->funcs.nfiles) {
			int						nfiles;

			// First see if we already know the answer
			if((nfiles = hier_nfiles(&fmp->fsmount, &fap->fsattr, 0)) == -1) {
				return errno;
			}

			// If we didn't get a value, ask the media driver
			if(nfiles < 0) {
				nfiles = dep->funcs.nfiles(dep, &handpath[0]);
				if(nfiles >= 0 && fap->fsattr.attr.nlink != 0) {
					// adjust for . and ..
					nfiles += 2;
				}
			}

			// If we got a value return it, otherwise allow normal processing
			if(nfiles >= 0) {
				*retval = nfiles;
				return EOK;
			}
		}
		return _RESMGR_DEFAULT;
	}

	return dep->funcs.devctl(dep, &handpath[0], ioflag, dcmd, data, nbytes, retval);
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/node.c $ $Rev: 680334 $")
#endif
