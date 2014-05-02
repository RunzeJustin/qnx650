/*
 * $QNXLicenseC:
 * Copyright 2011, QNX Software Systems. All Rights Reserved.
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


#ifndef TRKMGR_TYPES_H_
#define TRKMGR_TYPES_H_

#include <stdint.h>

__BEGIN_DECLS

struct _trks_hdl;
typedef struct _trks_hdl trks_hdl_t;

// track read types
enum {
	TRKS_READ_ENTRY_SEQ         = 0x01,
	TRKS_READ_ENTRY_RAND        = 0x02,
	TRKS_READ_INDEX_SEQ         = 0x03,		// Get equivalent indexes from sequential list
	TRKS_READ_INDEX_RAND        = 0x04		// Get equivalent indexes from the random list
};

// track write types
enum {
	TRKS_WRITE_ENTRY_DELETE     = 0x01,
	TRKS_WRITE_ENTRY_REPLACE    = 0x02,
	TRKS_WRITE_ENTRY_INSERT     = 0x03,
	TRKS_WRITE_ENTRY_APPEND     = 0x04
};

/* Track shuffle option flags */
#define TRKS_SHUFFLE_FIRST_TRK_SEQ      0x0001      /* Move a sequential index to the top of the random list */
#define TRKS_SHUFFLE_FIRST_TRK_RAND     0x0002      /* Move a random index to the top of the random list */

typedef struct {
	char        *entry;
	uint64_t    userdata;
} trksession_entry_t;

typedef struct {
	union {
		uint32_t    sequentialid;
		uint32_t    randomid;
	};
} trksession_index_t;

__END_DECLS

#endif /*TRKMGR_TYPES_H_*/

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-trkmgr/clientlib/public/trkmgr/types.h $ $Rev: 689495 $")
#endif
