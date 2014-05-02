/*
 * $QNXLicenseC:
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


#ifndef _MMSYNC_TYPES_H_INCLUDED
#define _MMSYNC_TYPES_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

/**
 * Status flag to indicate that the current sync operation has a
 * suspected sync thread.
 */
#define MM_SYNC_THREAD_IS_SUSPENDED		0x00000001

__BEGIN_DECLS

struct _mmsync_hdl;

/**
 * @brief The mm-sync connection handle type.
 */
typedef struct _mmsync_hdl mmsync_hdl_t;


/**
 * @brief The synchronization status for a single mediastore.
 */
typedef struct s_mmsync_status {
	uint32_t	operation_id;	///< The synchronization operation ID
	uint16_t	passes_done;	///< Flags indicating which synchronization passes have been completed
	uint16_t	current_pass;	///< Flag indicating which pass, if any, is in progress
	uint16_t	passes_to_do;	///< Flags indicating the synchronization passes that have not yet been started
	uint16_t	reserved[1];	///< Packing element
	uint32_t	flags;		///< Operation status flags (MM_SYNC_THREAD_IS_SUSPENDED)
} mmsync_status_t;


__END_DECLS

#endif /* _MMSYNC_TYPES_H_INCLUDED */

/* __SRCVERSION("types.h $Rev: 689495 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/lib/public/mmsync/types.h $ $Rev: 689495 $")
#endif
