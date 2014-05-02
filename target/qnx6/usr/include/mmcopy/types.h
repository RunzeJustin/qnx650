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

#ifndef __MMCOPY_TYPES_H_INCLUDED
#define __MMCOPY_TYPES_H_INCLUDED

#include <stdint.h>

typedef enum mmcopy_error_code_e {
	MMCOPY_ERROR_NONE = 0,
	MMCOPY_ERROR_UNKNOWN,
	MMCOPY_ERROR_UNSUPPORTED,
	MMCOPY_ERROR_READ,
	MMCOPY_ERROR_WRITE,
	MMCOPY_ERROR_CORRUPTED,
	MMCOPY_ERROR_DRM,
	MMCOPY_ERROR_USER,
	MMCOPY_ERROR_SOURCE,
	MMCOPY_ERROR_DESTINATION,
	MMCOPY_ERROR_NO_MEMORY,
	MMCOPY_ERROR_PERMISSION,

	MMCOPY_ERROR_MAX
} mmcopy_error_code_t;

typedef enum mmcopy_state_e {
	MMCOPY_STATE_UNKNOWN = 0,
	MMCOPY_STATE_ERROR,
	MMCOPY_STATE_IDLE,
	MMCOPY_STATE_STOPPED,
	MMCOPY_STATE_COPYING,
	MMCOPY_STATE_FINISHED,

	MMCOPY_STATE_MAX
} mmcopy_state_t;

typedef struct mmcopy_status_s {
	mmcopy_state_t state;
	enum {
		MMCOPY_ITEM_PROGRESS_UNKNOWN = 0,
		MMCOPY_ITEM_PROGRESS_BYTES,
		MMCOPY_ITEM_PROGRESS_MILLISECONDS,
		MMCOPY_ITEM_PROGRESS_USER,
	} type;
	uint64_t current;
	uint64_t total;
	char     reserved[8];
} mmcopy_item_status_t;

typedef struct mmcopy_event_queue_status_s {
	mmcopy_state_t state;
	uint32_t cur_cid;
	uint32_t cur_item;	/* current item is 1-based offset */
	uint32_t total_items;
	char     reserved[16];
} mmcopy_queue_status_t;



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-copy/lib/public/mmcopy/types.h $ $Rev: 717349 $")
#endif
