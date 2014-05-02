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

#ifndef __MMCOPY_RESOURCE_H_INCLUDED
#define __MMCOPY_RESOURCE_H_INCLUDED

#include <stdint.h>
#include <sys/cdefs.h>


typedef struct mmcopy_resource_list mmcopy_resource_list_t;


__BEGIN_DECLS

/* Returns number of resources in list. */
int mmcopy_resource_list_count(const mmcopy_resource_list_t *res);

/* Sets resource "key" to value "val".
 *
 * If val is NULL the resource "key" is deleted.
 *
 * Returns -1 on error, 0 on success.
 */
int mmcopy_resource_list_set(mmcopy_resource_list_t *res, const char *key, const char *val);

/* Creates a resource list.
 *
 * If base is NULL a new list is created; if not null the new list is seeded with
 * a copy of the "base" list.
 *
 * Returns NULL on error, list pointer on success.
 */
mmcopy_resource_list_t *mmcopy_resource_list_create(const mmcopy_resource_list_t *base);

/* Destroy a resource list.
 *
 * Returns -1 on error, 0 on success.
 */
int mmcopy_resource_list_destroy(mmcopy_resource_list_t *res);

/* Get a resource value by key.
 *
 * Returns NULL on error, string pointer on success.
 */
const char *mmcopy_resource_list_get_bykey(const mmcopy_resource_list_t *res, const char *key);

/* Get a resource value by index.
 *
 * If key is not NULL the resource key will be stored.
 *
 * Returns NULL on error, string pointer on success.
 */
const char *mmcopy_resource_list_get_byindex(const mmcopy_resource_list_t *res, uint32_t index, const char **key);

/* Combine the older and newer resource lists to create a new list.
 *
 * If the same key exists in newer and older the value from newer is used.
 * No list is consumed by this function; a new list is created.
 *
 * If either list is NULL this is the same as calling list_create() with the non-null list.
 * If both lists are NULL then this is the same as calling list_create() with a NULL list.
 *
 * Returns NULL on error, a new list pointer on success.
 */
mmcopy_resource_list_t *mmcopy_resource_list_combine(const mmcopy_resource_list_t *older, const mmcopy_resource_list_t *newer);

__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-copy/lib/public/mmcopy/resource.h $ $Rev: 680828 $")
#endif
