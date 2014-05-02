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

int
mediafs_mapping_mapfile(struct mediafsmount *fmp, struct mediafsattr *fap, unsigned fblk, struct span *sap) {

	sap->fblk  = 0;
	sap->dblk  = 0;
	sap->nblks = BYTES2BLKS(fap->fsattr.attr.nbytes + (CLUS2BYTES(1) - 1));
	if(fblk >= sap->nblks)
		sap->nblks = 0;

	return EOK;
}


int
mediafs_override_io(struct mediafsattr *fap, unsigned flags, struct cachenode *cavec[], struct iovec iovec[], int nvec) {
	struct mediafsmount		*fmp = fap->fsattr.attr.mount;
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	struct mediafsattr		*fap2;
	unsigned				i;
	unsigned				handpath[MAXPATHLEVELS];

IFDBG if(fap->fsattr.fid == FID_ROOT) abort();

	// Walk up the directory saving the handpath.
	for(handpath[0] = 0, fap2 = fap; handpath[0] < MAXPATHLEVELS && fap2->fsattr.parent; fap2 = fap2->fsattr.parent) {
		handpath[++handpath[0]] = fap2->fsattr.offset;
		if(handpath[0] >= MAXPATHLEVELS) {
			return ENOENT;		// Got a better error?
		}
	}

	for(i = 0 ; i < nvec ; ++i) {
		struct cachenode	*cap = cavec[i];

		if(flags & _IO_FLAG_RD) {
			if(cap->links & 0x8000) {
				int				nbytes = BLKS2BYTES(cap->dmap.nblks);
				off64_t			off = BLKS2BYTES64(cap->dmap.blk);

				if(fap->fsattr.attr.nbytes - off < nbytes) {
					nbytes = fap->fsattr.attr.nbytes - off;
				}
IFDBG if(nbytes <= 0) abort();
				if(dep->funcs.read(dep, &handpath[0], cap->data, nbytes, off) != nbytes) {
					return EIO;
				}
			}
		} else {
			;
		}
	}

	return EOK;
}


void
mediafs_attr_open(struct mediafsmount *fmp, struct mediafsattr *fap, const struct mediafsinode *fip) {
	// Set flags for media special files
	if(avrcpexample_media_attr_open(fmp, fap, fip) == EOK) {
		return;
	}

	fap->fsattr.override_io = mediafs_override_io;
}


void
mediafs_attr_close(struct mediafsmount *fmp, struct mediafsattr *fap, unsigned flags) {
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;

	if(dep->funcs.close) {
		struct mediafsattr		*fap2;
		unsigned				handpath[MAXPATHLEVELS];

		// Walk up the directory saving the handpath.
		for(handpath[0] = 0, fap2 = fap; handpath[0] < MAXPATHLEVELS && fap2->fsattr.parent; fap2 = fap2->fsattr.parent) {
			handpath[++handpath[0]] = fap2->fsattr.offset;
			if(handpath[0] >= MAXPATHLEVELS) {
				return;
			}
		}
#ifdef DBG
printf("--close(%#x)\n", handpath[0] ? handpath[1] : 0);
#endif

		dep->funcs.close(dep, &handpath[0]);
	}
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/mapping.c $ $Rev: 680334 $")
#endif
