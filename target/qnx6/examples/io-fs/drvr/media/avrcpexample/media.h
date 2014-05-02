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



#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "mediafs.h"
#include <sys/dcmd_media.h>

// fsio.c
int			media_devio_mount(struct mediafsdevice *dep);
int			media_devio_umount(struct mediafsdevice *dep);
DEVICE_T	*media_devio_device(struct driver *drp, unsigned unit);
DEVICE_T	*media_devio_alloc(struct driver *drp, char *options);
int			media_devio_destroy(struct mediafsdevice *dep);
#endif

/* __SRCVERSION("media.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/media.h $ $Rev: 680334 $")
#endif
