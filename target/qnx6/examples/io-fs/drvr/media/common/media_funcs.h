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



#ifndef MEDIA_FUNCS_H
#define MEDIA_FUNCS_H

enum {
	FID_MEDIA_ROOT = FID_ROOT + 1,

	FID_CONTROL = FID_MEDIA_ROOT,
#define FNAME_CONTROL	"control"

#ifdef MEDIA_CURRENT
	FID_CURRENT,
#define FNAME_CURRENT	"current"
#endif

#ifdef MEDIA_PLAYBACK
	FID_PLAYBACK,
#define FNAME_PLAYBACK	"playback"
#endif

	FID_MEDIA_LAST
};


#define MEDIAFS_MOUNT_SET_FLAGS(fmp)		(fmp)->fsmount.flags |= FSMOUNT_MNTINFO

/* Provided by media_funcs.ci */
int IOFS_CAT(MODULE_NAME, _media_node_get)(FS_MOUNT_T *fmp, FS_INODE_T *fip, unsigned flags, const char *name);
int IOFS_CAT(MODULE_NAME, _media_hier_build)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, struct hier_file *last_hfp);
int IOFS_CAT(MODULE_NAME, _media_attr_open)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, const FS_INODE_T *fip);

#ifdef MEDIA_CONTROL
void IOFS_CAT(MODULE_NAME, _control_notify)(FS_MOUNT_T *fmp);
#endif

#ifdef MEDIA_CURRENT
int IOFS_CAT(MODULE_NAME, _current_symlink_get)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, char *sympath, unsigned len);
/* To be supplied by the media filesystem */
int IOFS_CAT(MODULE_NAME, _playback_current)(FS_MOUNT_T *fmp, char *buf, size_t bufmax);
#endif

#ifdef MEDIA_PLAYBACK
void IOFS_CAT(MODULE_NAME, _playback_clean)(FS_MOUNT_T *fmp, unsigned *freelist);
#endif

#endif

/* __SRCVERSION("media_funcs.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/common/media_funcs.h $ $Rev: 680334 $")
#endif
