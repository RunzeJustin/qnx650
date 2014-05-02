/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
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

#ifndef __MMCOPY_MMCOPY_H_INCLUDED
#define __MMCOPY_MMCOPY_H_INCLUDED

#include <stdint.h>
#include <sys/cdefs.h>

#define MMCOPY_EVENTS_RESOURCE_QUEUESIZE	"mmcopy_events_queuesize"
#define MMCOPY_EVENTS_DEFAULT_QUEUESIZE		(80)

#define MMCOPY_TEMPLATE_DELIM			'$'

typedef struct mmcopy_hdl mmcopy_hdl_t;


__BEGIN_DECLS

/* Initialize mmcopy.
 *
 * cfgpath - path to configuration file to load; cannot be NULL.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_init(const char *cfgfile);

/* Open a connection to mmcopy.
 *
 * path - path to mmcopy or NULL if a local connection.
 * flags - must be 0.
 *
 * returns NULL on failure, mmcopy handle on success.
 */
mmcopy_hdl_t *mmcopy_connect(const char *path, uint32_t flags);

/* Close a connection to mmcopy.
 *
 * hdl - an mmcopy connection handle.
 */
void mmcopy_disconnect(mmcopy_hdl_t *hdl);

__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-copy/lib/public/mmcopy/mmcopy.h $ $Rev: 680828 $")
#endif
