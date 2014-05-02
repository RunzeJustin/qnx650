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



#ifndef MEDIAFS_H_INCLUDED
#define MEDIAFS_H_INCLUDED

#define CLUSTERBITS		9
#define CLUSTERSIZE		(1 << CLUSTERBITS)

#define MAX_FNAME_LEN	1024

#ifndef FS_ATTR_T
#define FS_ATTR_T		struct mediafsattr
#endif
#ifndef FS_INODE_T
#define FS_INODE_T		struct mediafsinode
#endif
#ifndef FS_MOUNT_T
#define FS_MOUNT_T		struct mediafsmount
#endif
#ifndef DEVICE_T
#define DEVICE_T		struct mediafsdevice
#endif

#include "iofs.h"

#define MEDIA_CONTROL	// Support media control file
//#define MEDIA_CURRENT	// Support media current symlink
//#define MEDIA_PLAYBACK	// Support media playback directory
#include "media_funcs.h"

#define MAXPATHLEVELS	32

struct mediafsinode {
	struct fsinode		fsinode;
};

struct mediafsattr {
	struct fsattr		fsattr;
};

struct media_readdir {
	unsigned			handle;
	unsigned			mode;
	char				*name;
};

struct mediafsmount {
	struct fsmount			fsmount;
};

#define HANDPATH_NENTS(hp)		((hp)[0])
#define HANDPATH_ENT(hp,e)		((hp)[(e)+1])
#define HANDPATH_TARGET(hp)		HANDPATH_ENT((hp),0)

#define HANDPATH_ROOT			(0)				// NENTS when handpath is for root directory
#define HANDPATH_BLKDEV			((unsigned)-1)	// NENTS when handpath is for block device (only for devctl when
												// DEVICE_NOBLKDEV is unset in mediafsdevice.device.flags)
#define HANDPATH_ISROOT(hp)		(HANDPATH_NENTS(hp)==HANDPATH_ROOT)
#define HANDPATH_ISBLKDEV(hp)	(HANDPATH_NENTS(hp)==HANDPATH_BLKDEV)


#define MEDIA_NONREG	0x00000001		// Device contains non-regular files (e.g. links)
struct mediafsdevice {
	struct device		device;
	struct mediafsmount	*notify_fmp;
	unsigned			flags;
	struct {
		int					(*getattr)(DEVICE_T *dep, unsigned handpath[], struct mediafsinode *fip, unsigned flags);
//		int					(*setattr)(FS_ATTR_T *fap);
//		int					(*lookup)(FS_ATTR_T *fap);
		int					(*readlink)(DEVICE_T *dep, unsigned handpath[], char *symlink, int len);
		int					(*read)(DEVICE_T *dep, unsigned handpath[], char *buf, int size, off64_t off);
		int					(*write)(DEVICE_T *dep, unsigned handpath[], char *buf, int size, off64_t off);
//		int					(*create)(FS_ATTR_T *fap);
//		int					(*remove)(FS_ATTR_T *fap);
		int					(*readdir)(DEVICE_T *dep, unsigned handpath[], struct media_readdir *rdirs, unsigned nrdir, unsigned flags);
#define READDIR_FLAG_BUILD	0x00000001
#define READDIR_FLAG_FIRST	0x00000002
#define READDIR_FIRST		((unsigned)-1)
//		int					(*fsstat)(FS_ATTR_T *fap);
//		int					(*access)(FS_ATTR_T *fap);
//		int					(*commit)(FS_ATTR_T *fap);
//		int					(*fsinfo)(FS_ATTR_T *fap);
		int					(*devctl)(DEVICE_T *dep, unsigned handpath[], unsigned ioflag, int dcmd, void *data, int nbytes, int *retva);
		int					(*getinfo)(DEVICE_T *dep, struct xmlbuf *xp);
		int					(*notify)(DEVICE_T *dep, unsigned handpath[], int (*func)(void *handle), void *handle);
		unsigned			(*timer)(DEVICE_T *dep);
		int					(*nfiles)(DEVICE_T *dep, unsigned handpath[]);
		void				(*close)(DEVICE_T *dep, unsigned handpath[]);
		void				(*destroy)(DEVICE_T *dep);
	}					funcs;
};

#define CAT2(a,b) a ## b
#define CAT(a,b) CAT2(a,b)
#define media_devio_mount		CAT(MODULE_NAME,_devio_mount)
#define media_devio_umount		CAT(MODULE_NAME,_devio_umount)
#define media_devio_device		CAT(MODULE_NAME,_devio_device)
#define media_devio_alloc		CAT(MODULE_NAME,_devio_alloc)
#define media_devio_destroy		CAT(MODULE_NAME,_devio_destroy)
#define media_devio_devctl		CAT(MODULE_NAME,_devio_devctl)
#define media_devio_timer		CAT(MODULE_NAME,_devio_timer)
#define media_addinfo			CAT(MODULE_NAME,_devio_addinfo)
#define mediafs_fsys			CAT(MODULE_NAME,_fs_fsys)
#define mediafs_hier_build		CAT(MODULE_NAME,_fs_hier_build)
#define mediafs_node_get		CAT(MODULE_NAME,_fs_node_get)
#define mediafs_cpyfname		CAT(MODULE_NAME,_fs_cpyfname)
#define mediafs_notify			CAT(MODULE_NAME,_fs_notify)
#define mediafs_mapping_mapfile	CAT(MODULE_NAME,_fs_mapping_mapfile)
#define mediafs_attr_open		CAT(MODULE_NAME,_fs_attr_open)
#define mediafs_attr_close		CAT(MODULE_NAME,_fs_attr_close)
#define mediafs_symlink_get		CAT(MODULE_NAME,_fs_symlink_get)
#define mediafs_devctl			CAT(MODULE_NAME,_fs_devctl)
#define mediafs_mount			CAT(MODULE_NAME,_fs_mount)
#define mediafs_notify_handler	CAT(MODULE_NAME,_fs_notify_handler)
#define mediafs_options			CAT(MODULE_NAME,_fs_options)
#define mediafs_override_io		CAT(MODULE_NAME,_fs_override_io)
#define mediafs_umount			CAT(MODULE_NAME,_fs_umount)

/* init.c */
extern struct fsys mediafs_fsys;

/* hier.c */
int mediafs_hier_build(struct mediafsmount *fmp, struct mediafsattr *fap, struct hier_file *last_hfp, unsigned index);

/* node.c */
int mediafs_node_get(struct mediafsmount *fmp, struct mediafsinode *fip, unsigned flags, const char *name);
int mediafs_cpyfname(char *name, int dsize, const struct media_readdir *rdp);
int mediafs_notify(struct mediafsmount *fmp, struct mediafsattr *fap);
int mediafs_devctl(struct mediafsmount *fmp, resmgr_context_t *ctp, struct mediafsattr *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval);

/* mapping.c */
int mediafs_mapping_mapfile(struct mediafsmount *fmp, struct mediafsattr *fap, unsigned fblk, struct span *sap);
void mediafs_attr_open(struct mediafsmount *fmp, struct mediafsattr *fap, const struct mediafsinode *fip);
void mediafs_attr_close(struct mediafsmount *fmp, struct mediafsattr *fap, unsigned flags);

/* symlink.c */
int mediafs_symlink_get(struct mediafsmount *fmp, struct mediafsattr *fap, char *sympath, unsigned len);

#endif

/* __SRCVERSION("mediafs.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/mediafs.h $ $Rev: 680334 $")
#endif
