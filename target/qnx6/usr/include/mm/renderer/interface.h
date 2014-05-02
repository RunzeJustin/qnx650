/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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

#if !defined(MM_RENDERER_INTERFACE_H_INCLUDED)
#define MM_RENDERER_INTERFACE_H_INCLUDED

/** @file interface.h
 *  Interface registry
 *  @ingroup interfaceAPI Interface registry API
 */

#if !defined(MM_RENDERER_PLUGIN_H_INCLUDED)
#include <mm/renderer/plugin.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup interfaceAPI Interface registry API
 */
/*@{*/

/**
 *  Interface handle representing a registered plugin interface (engine, routing, etc)
 */
typedef struct mmr_plugin_interface mmr_plugin_interface_t;

/**
 *  A list of all registered interfaces of the same type.
 *  This must be a static object that doesn't get unloaded
 *  until all the interfaces on its list are deregistered.
 *  Consider all the members of this structure private.
 */
typedef struct mmr_interface_list {
	union {
		struct {
			mmr_plugin_interface_t *ifaces;      ///< Yes, this is the list pointer
			struct mmr_interface_list *nextlist; ///< Next registered list object
		} p;
		void *q[ 4 ];
	} u;
} mmr_interface_list_t;

/**
 *  Add an interface to a list.
 *  This must be called from a plugin's register() call.
 *  @param list The list to add the interface to
 *  @param calls A pointer to the call table of this interface
 *  @param owner The handle for the plugin that owns this interface
 */
mmr_plugin_interface_t *mmr_plugin_interface_register( mmr_interface_list_t *list, void const *calls, mmr_plugin_t *owner );

/**
 *  Increment the number of refs (e.g. instances) of an interface.
 *  @param iface The interface handle
 */
void mmr_plugin_interface_ref( mmr_plugin_interface_t *iface );

/**
 *  Decrement the number of refs (e.g. instances) of an interface.
 *  Note that the interface handle remains valid
 *  until the plugin has been deregistered and the ref count reaches zero.
 *  @param iface The interface instance handle
 */
void mmr_plugin_interface_unref( mmr_plugin_interface_t *iface );

/**
 *  Retrieve the call table of an interface.
 *  @param iface The interface handle
 *  @returns The calls pointer registered for this interface
 *           with the mmr_plugin_interface_register() call
 */
const void *mmr_plugin_interface_calls( mmr_plugin_interface_t *iface );

/**
 *  Retrieve the owner of an interface.
 *  @param iface The interface handle
 *  @returns The plugin handle that this interface belongs to
 */
mmr_plugin_t *mmr_plugin_interface_owner( mmr_plugin_interface_t *iface );

/**
 *  Retrieve the plugin data pointer
 *  @param iface The interface instance handle
 *  @returns The data pointer returned by the owning plugin's init() call
 */
mmr_plugin_data_t *mmr_plugin_data( mmr_plugin_interface_t *iface );

/**
 *  Iterate all plugins on a list.
 *  The list of interfaces is locked until iteration ends
 *  (don't try to register on unregister interfaces
 *  in a thread that has a started iteration).
 *  @param list The list to iterate
 *  @returns The first interface on the list (NULL if list empty)
 */
mmr_plugin_interface_t *mmr_interface_first( mmr_interface_list_t *list );

/**
 *  Get the next item on the list.
 *  @param iface The interface returned from the previous
 *               mmr_interface_first() or mmr_interface_next() call
 *  @returns The next interface of the list
 */
mmr_plugin_interface_t *mmr_interface_next( mmr_plugin_interface_t *iface );

/**
 *  End the iteration.
 *  This function must be called to unlock the list,
 *  even if mmr_interface_first() returned NULL.
 *  @param iface The interface returned from the previous
 *               mmr_interface_first() or mmr_interface_next() call
 */
void mmr_interface_stop( mmr_plugin_interface_t *last );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/interface.h $ $Rev: 680336 $")
#endif
