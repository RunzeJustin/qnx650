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


/* dcmd_dio.h Non-portable low-level devctl definitions */ 

#ifndef __DCMD_DIO_H_INCLUDED
#define __DCMD_DIO_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
#include <devctl.h>
#endif


#define DIO_FLAGS_NOCACHE	0x00000001
struct dio_alloc {
	off64_t		offset;
	size_t		nbytes;
	unsigned	flags;
	unsigned	spare[2];
	char		name[1];
} ;

#define DIO_FLAGS_WRITE		0x00000001
struct dio_io {
	off64_t		offset;
	int			flags;
	int			handle;
	size_t		nbytes;
	unsigned	spare[2];
} ;

// Only usefull for tmpfs on a file which is is not changed.
#define DIO_MAX_PADDR_NVEC 16
struct dio_paddr {
	off64_t		offset;
	unsigned	flags;		// _IO_FLAG_RD or _IO_FLAG_WR
	unsigned	zero;
	struct	{
		off64_t		paddr;
		void		*vaddr;
		size_t		nbytes;
		unsigned	zero;		// Future expansion
	} pvec[DIO_MAX_PADDR_NVEC];
} ;


//just until devctl.h updated
#define _DCMD_DIO	0xF


#define DCMD_DIO_DEVICE						__DIOF(_DCMD_DIO, 1, char[256])
#define DCMD_DIO_ALLOC						__DIOT(_DCMD_DIO, 2, struct dio_alloc)
#define DCMD_DIO_IO							__DIOT(_DCMD_DIO, 3, struct dio_io)
#define DCMD_DIO_PADDR						__DIOTF(_DCMD_DIO, 4, struct dio_paddr)
#define DCMD_DIO_GROW						__DIOT(_DCMD_DIO, 5, off64_t)

#endif 

/* __SRCVERSION("dcmd_dio.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/lib/public/sys/dcmd_dio.h $ $Rev: 680334 $")
#endif
