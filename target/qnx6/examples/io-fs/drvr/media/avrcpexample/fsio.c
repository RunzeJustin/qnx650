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



#include "media.h"

int
media_devio_mount(struct mediafsdevice *dep) {
	if(dep->device.forcemnt == NULL || dep->device.fsname == NULL) {
		fs_log(dep->device.class, _SLOG_ERROR, "Missing mount option on driver.");
		return EINVAL;
	}
	dep->device.fsname = (char *)dep->device.driver->iface.module->name;
	device_init(dep);
	return EOK;
}

int
media_devio_umount(struct mediafsdevice *dep) {
	device_nomedia(dep);
	return EOK;
}

static int
media_devio_devctl(resmgr_context_t *ctp, struct blkfsattr *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval) {
	unsigned				handpath[1] = { ~0 };

	if(fap->dev->device.flags & DEVICE_NOBLKDEV) {
		return _RESMGR_DEFAULT;
	}
	return fap->dev->funcs.devctl(fap->dev, handpath, ioflag, dcmd, data, nbytes, retval);
}

static unsigned
media_devio_timer(struct mediafsdevice *dep) {
	return dep->funcs.timer(dep);
}

static void
media_addinfo(struct mediafsdevice *dep, struct mediafsmount *fmp) {
	xmlbuf_add(&fmp->fsmount.info, "catagory", "media");
}

struct mediafsdevice *
media_devio_alloc(struct driver *drp, char *options) {
	struct mediafsdevice		*dep;

	if(dep = device_alloc(drp, options)) {
		drp->funcs.devctl = media_devio_devctl;
		drp->funcs.timer = media_devio_timer;
		drp->funcs.addinfo = media_addinfo;
		dep->device.flags |= DEVICE_NOBLKDEV;
		dep->device.blksize = 4096;
		dep->device.class = dep->device.driver->iface.module->name;
		dep->device.fsname = (char *)dep->device.driver->iface.module->name;
		dep->device.type = "media";
	}
	return dep;
}

int
media_devio_destroy(struct mediafsdevice *dep) {
	device_destroy(dep);
	return 0;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/fsio.c $ $Rev: 680334 $")
#endif
