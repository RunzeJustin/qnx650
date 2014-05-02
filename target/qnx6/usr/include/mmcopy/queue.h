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

#ifndef __MMCOPY_QUEUE_H_INCLUDED
#define __MMCOPY_QUEUE_H_INCLUDED

#include <mmcopy/types.h>
#include <mmcopy/mmcopy.h>
#include <mmcopy/resource.h>
#include <stdint.h>
#include <sys/cdefs.h>

typedef enum mmcopy_queue_item_status_e {
	MMCOPY_QUEUE_ITEM_STATUS_UNKNOWN = 0,
	MMCOPY_QUEUE_ITEM_STATUS_ERROR,
	MMCOPY_QUEUE_ITEM_STATUS_READY,
	MMCOPY_QUEUE_ITEM_STATUS_COPYING,
	MMCOPY_QUEUE_ITEM_STATUS_COMPLETE,
} mmcopy_queue_item_status_t;

typedef struct mmcopy_queue_resolved_item_s {
	unsigned                      id;
	unsigned                      srcid;
	const char                   *src;
	const char                   *dst;
	const mmcopy_resource_list_t *res;
	mmcopy_queue_item_status_t    status;
	char                          reserved[8];
} mmcopy_queue_resolved_item_t;

typedef uint32_t mmcopy_queue_t;

#define MMCOPY_QUEUE_ERRORID			(0)
#define MMCOPY_QUEUE_COPY_STOP_FLAGS_TERMINATE	(0x00000001)


__BEGIN_DECLS

/* Create a copy queue with the given "name".
 *
 * Seed the queue with resources given by res or NULL for an empty resource list.
 * returns MMCOPY_QUEUE_ERRORID on error, qid on success.
 */
mmcopy_queue_t mmcopy_queue_create(mmcopy_hdl_t *hdl, const char *name, const mmcopy_resource_list_t *res);

/* Destroy a copy queue given by qid.
 *
 * This releases all resources associated with the queue and its items
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_destroy(mmcopy_hdl_t *hdl, mmcopy_queue_t qid);

/* Open an existing queue by name.
 *
 * returns MMCOPY_QUEUE_ERRORID on error, qid on success.
 */
mmcopy_queue_t mmcopy_queue_open(mmcopy_hdl_t *hdl, const char *name);

/* Add items to the queue.
 *
 * usrc is the unresolved source; this will be resolved using a resolver to 0 or more items
 * dstt is the destination template; the destination will be expanded for each resolved item
 * res are the resources that apply only to items added from this source.  it is not necessary
 * to duplicate resources that already apply to the global queue.  This may be NULL if no resources
 * apply to this source.  The resource list is not consumed.
 *
 * returns -1 on error, the number of items added on success (>= 0)
 */
int mmcopy_queue_items_add(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, const char *usrc, const char *dstt, const mmcopy_resource_list_t *res);

/* Get items from the queue.
 *
 * qid - queue id
 * offset - offset, 0-based, of items to get information for
 * itembuf - pointer to a buffer of sizeof(*itembuf) * itembuf_cnt
 * itembuf_cnt - number of items that can fit in itembuf
 * returns number of items in total available from the given offset
 * (if 10 items in queue, and offset is 0, returns 10; if offset is 4, returns 6)
 * returns -1 on error.
 */
int mmcopy_queue_items_get(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned offset, mmcopy_queue_resolved_item_t *itembuf, int itembuf_cnt);

/* Get a single item by copy id.
 *
 * hdl - connection to mmcopy
 * qid - queue from which to get items
 * cid - copy id of the item to get.
 * itembuf - pointer to a buffer to store the resolved item details.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_item_get(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned cid, mmcopy_queue_resolved_item_t *itembuf);

/* Delete items from the queue.
 *
 * hdl - connection to mmcopy
 * qid - queue from which to delete items
 * cids - pointer to array of cids_cnt copy ids to delete
 * cids_cnt - number of copy ids in cids array.
 *
 * returns -1 on error, number of items deleted on success (>= 0)
 * If return is less than cids_cnt, some items failed to be removed.
 */
int mmcopy_queue_items_delete(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned *cids, unsigned cids_cnt);

/* Set a resource for a given copy id.
 *
 * hdl - connection to mmcopy
 * qid - queue containing the item cid
 * cid - copy id of the item on which to set the resource.
 * key - key of the resource to set.
 * val - value of the resource to set; NULL to remove an item.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_item_resource_set(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned cid, const char *key, const char *val);

/* Start copying.
 *
 * If res is NULL, the current copy resource list is not changed.
 * If resuming copy in a stopped state and you would like to clear the existing
 * resources specific to that copy you must pass in an empty resource list.
 * The resource list is duplicated by the copier and is not consumed by this function.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_copy_start(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, const mmcopy_resource_list_t *res);

/* Stop copying.
 *
 * If flags is 0, the copy is stopped but not terminated.  The copy can be resumed with a call to start.
 * If flags is MMCOPY_QUEUE_COPY_STOP_FLAGS_TERMINATE, the copy is stopped and terminated.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_copy_stop(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned flags);

/* Reset an item status to READY.
 *
 * If an item has an error that has been dealt with, the item's status can be reset to READY.
 *
 * hdl - connection to mmcopy
 * qid - queue on which to operate
 * cid - copy id of the item on which to set the resource.
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_item_status_reset(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, unsigned cid);

/* Get the current queue status.
 *
 * hdl - connection to mmcopy
 * qid - queue on which to operate
 * status - pointer to a buffer to store current status in
 *
 * returns -1 on error, 0 on success.
 */
int mmcopy_queue_status_get(mmcopy_hdl_t *hdl, mmcopy_queue_t qid, mmcopy_queue_status_t *status);


__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-copy/lib/public/mmcopy/queue.h $ $Rev: 697505 $")
#endif
