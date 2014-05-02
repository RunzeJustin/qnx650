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
#ifndef _GF_GFI_INTERNALS_H_INCLUDED
#define _GF_GFI_INTERNALS_H_INCLUDED

struct _gfi_group {
	int			fd;
};

struct _gfi_layer {
	struct _gfi_group	*group;
	int			z_pos;
};

#ifdef __QNXNTO__
#include<sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/private/gf/gfi_internals.h $ $Rev: 244324 $" )
#endif
#endif /* _GF_INTERNALS_H_INCLUDED */
