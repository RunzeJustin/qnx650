/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _GF_IOD_H_INCLUDED
#define _GF_IOD_H_INCLUDED

#ifndef __DISPLAY_H_INCLUDED
#include <graphics/display.h>
#endif

#ifndef _GF_INTERNALS_H_INCLUDED
#include <gf/gf_internals.h>
#endif

__BEGIN_DECLS

extern int iod_msg(int fd, disp_iomsg_t *msg, int len, void *rep, int rlen, unsigned subtype);
extern int iod_register(gf_dev_t gfx, char **dllpath, char **rendopts, char **hook);
extern void iod_unregister(gf_dev_t dev);
extern int iod_query(int fd, int *ndisplays);
extern void iod_wait_idle(int fd);
extern int iod_mem_info(int fd, unsigned * total, unsigned * avail);

extern int iod_open(const char *nbuf, int flags);
extern int iod_close(int fd);
extern int iod_get_path(const char *name, char *n_name);

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/private/gf/iod.h $ $Rev: 224586 $" )
