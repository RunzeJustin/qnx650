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

static int
mediafs_options(struct mediafsmount *fmp, char *optargs, const char *cond) {
	char					*value;
	int						err;
	struct subopt			subopt = {
		.name = fmp->fsmount.fsname,
		.conditions = cond,
	};
	enum {
		OPT_USE,
		LAST_OPT
	};
	static const char		* const opts[] ={
		[OPT_USE] = "use",
		[LAST_OPT] = 0
	};

	while(optargs && *optargs) {
		if(subopt.skip) {
			if((err = suboptif(&subopt, &optargs)) != EOK) {
				return err;
			}
			continue;
		}

		switch(getsubopt(&optargs, (char * const *)opts, &value)) {
		case OPT_USE:
			fs_log(subopt.name, _SLOG_INFO,
				"options: use"
			);
			return EL2HLT;

		default:
			// Check for common fs options then conditionals
			if(suboptfs(&fmp->fsmount, &subopt, &value) != EOK) {
				if((err = suboptif(&subopt, &value)) != EOK) {
					return err;
				}
			}
			break;
		}
	}

	return EOK;
}


static void
mediafs_umount(struct mediafsmount *fmp, int flags) {
	struct mediafsdevice		*dep = fmp->fsmount.blkdev->dev;

#ifdef MEDIA_CONTROL
	avrcpexample_control_notify(fmp);
#endif

	dep->notify_fmp = 0;

	if(dep->funcs.destroy) {
		dep->funcs.destroy(dep);
	}
}


static int
mediafs_mount(struct mediafsmount *fmp, int flags, const char *options) {
	struct mediafsdevice	*dep = fmp->fsmount.blkdev->dev;
	int						err;
	char					*s;

	s = strdupa(options);
	if((err = mediafs_options(fmp, s, 0)) != EOK) {
		return err;
	}

	dep->notify_fmp = fmp;

	fmp->fsmount.clustersize = CLUSTERSIZE;
	fmp->fsmount.clusterbits = CLUSTERBITS;
	fmp->fsmount.fname_maxlen = MAX_FNAME_LEN;

	fmp->fsmount.funcs.node_get          = mediafs_node_get;
	fmp->fsmount.funcs.mapping_mapfile   = mediafs_mapping_mapfile;
	fmp->fsmount.funcs.hier_build        = mediafs_hier_build;
	fmp->fsmount.funcs.symlink_get       = mediafs_symlink_get;
	fmp->fsmount.funcs.attr_open         = mediafs_attr_open;
	fmp->fsmount.funcs.attr_close        = mediafs_attr_close;
	fmp->fsmount.funcs.notify            = mediafs_notify;
	fmp->fsmount.funcs.devctl            = mediafs_devctl;
	fmp->fsmount.funcs.umount            = mediafs_umount;

	// because the media filesystem is just code to handle media devices, change the fsname to match the device
	// fmp->fsmount.fsname = dep->device.driver->iface.module->name;

	MEDIAFS_MOUNT_SET_FLAGS(fmp);

	// Allow device to stuff xml info file only once
	if(dep->funcs.getinfo) {
		int						err;

		if((err = dep->funcs.getinfo(dep, &fmp->fsmount.info)) != EOK) {
			return err;
		}
	}

	return EOK;
}

struct fsys mediafs_fsys =  {
	.iface = {.type = IFACE_FSYS, },
	.mount_size = sizeof(struct mediafsmount),
	.attr_size = sizeof(struct mediafsattr),
	.inode_size = sizeof(struct mediafsinode),
	.data_shift = 1,
	.funcs = {
		.mount = mediafs_mount,
	}
};

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/init.c $ $Rev: 680334 $")
#endif
