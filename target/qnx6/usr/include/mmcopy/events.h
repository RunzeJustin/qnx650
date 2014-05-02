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

#ifndef __MMCOPY_EVENT_H_INCLUDED
#define __MMCOPY_EVENT_H_INCLUDED

#include <mmcopy/mmcopy.h>
#include <mmcopy/types.h>
#include <mmcopy/queue.h>
#include <stdint.h>
#include <sys/siginfo.h>
#include <sys/cdefs.h>

/* The comments beside the event types refer to the name of the item(s)
 * in the mmcopy_event_t union that are used for that event type.
 */
typedef enum mmcopy_event_type_e {
	MMCOPY_EVENT_TYPE_UNKNOWN = 0,
	MMCOPY_EVENT_TYPE_QUEUE_CREATED,
	MMCOPY_EVENT_TYPE_QUEUE_DESTROYED,
	MMCOPY_EVENT_TYPE_QUEUE_COPY_STARTED,
	MMCOPY_EVENT_TYPE_QUEUE_COPY_STOPPED,
	MMCOPY_EVENT_TYPE_QUEUE_COPY_STATUS,	/* queue_status */
	MMCOPY_EVENT_TYPE_ITEM_ADDED,		/* item */
	MMCOPY_EVENT_TYPE_ITEM_REMOVED,		/* item */
	MMCOPY_EVENT_TYPE_ITEM_COPY_SKIPPED,	/* item */
	MMCOPY_EVENT_TYPE_ITEM_COPY_STARTED,	/* item */
	MMCOPY_EVENT_TYPE_ITEM_COPY_STOPPED,	/* item */
	MMCOPY_EVENT_TYPE_ITEM_COPY_ERROR,	/* item_error */
	MMCOPY_EVENT_TYPE_ITEM_COPY_STATUS,	/* item_status */
	MMCOPY_EVENT_TYPE_USER,			/* item, data */

	MMCOPY_EVENT_TYPE_MAX
} mmcopy_event_type_t;

typedef struct mmcopy_event_s {
	uint64_t  type; /* mmcopy_event_type_t */
	uint32_t  size;
	mmcopy_queue_t qid;

	union mmcopy_event_details_u {
		mmcopy_queue_status_t queue_status;
		struct mmcopy_event_item_s {
			uint32_t cid;
		} item;
		struct mmcopy_event_item_error_s {
			uint32_t cid;
			mmcopy_error_code_t error;
		} item_error;
		struct mmcopy_event_item_status_s {
			uint32_t cid;
			mmcopy_item_status_t status;
		} item_status;
	} details;
	unsigned char data[];
} mmcopy_event_t;


__BEGIN_DECLS

/* Register for mmcopy events.
 *
 * hdl - an mmcopy connection handle.
 * event - event to deliver when an event is available.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_events_register(mmcopy_hdl_t *hdl, struct sigevent *event);

/* Read an mmcopy event.
 *
 * hdl - an mmcopy connection handle.
 * event - pointer to store event buffer pointer in.
 *
 * returns -1 on error, number of events returned on success.
 */
int mmcopy_events_get(mmcopy_hdl_t *hdl, mmcopy_event_t **event);

__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-copy/lib/public/mmcopy/events.h $ $Rev: 680828 $")
#endif
