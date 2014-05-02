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


#if !defined(MM_RENDERER_PLUGIN_H_INCLUDED)
#define MM_RENDERER_PLUGIN_H_INCLUDED
#include "mm/mmsupport.h"

/** @file plugin.h
 *  Plugin API functions
 *  @ingroup pluginAPI Plugin API
 */

#if !defined(MM_RENDERER_LOGGER_H_INCLUDED)
#include <mm/renderer/logger.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup pluginAPI Plugin API
 */
/*@{*/

/**
 *  Internal handle representing a loaded plugin
 */
typedef struct mmr_plugin mmr_plugin_t;

/**
 *  A plugin's pointer to any private data it needs.
 *  Each plugin defines its own version of this structure.
 */
typedef struct mmr_plugin_data mmr_plugin_data_t;

/**
 *  The call table exported by a plugin.
 */
typedef struct mmr_plugin_calls {
	/**
	 *	Plugin name.
	 */
	const char *name;

	/**
	 *  Initialize the plugin.
	 *  @param handle A handle representing this plugin.
	 *                Useful for calling mmr_plugin_ref().
	 *  @param logger A handle the plugin can use for logging
	 *  @param cfg The plugin's configuration parameters (plugin consumes the handle on success)
	 *  @return NULL on a failure (plugin will be unloaded)
	 */
	mmr_plugin_data_t *(*init)( mmr_plugin_t *handle, mmr_logger_t *logger, strm_dict_t *cfg );

	/**
	 *  Register any interfaces.
	 *  If not NULL, this function is called right after init(),
	 *  and then possibly again at some point after deregistered().
	 *  @param handle A handle, needed to register interfaces.
	 *  @param data The pointer returned by the plugin's init() call
	 *  @return 0 on success (any registered interfaces will be unregistered on failure)
	 */
	int (*register_interfaces)( mmr_plugin_t *handle, mmr_plugin_data_t *data );
	
	/**
	 *  Interface deregistration.
	 *  If not NULL, this is called when the plugin is scheduled for being unloaded,
	 *  after its interfaces have been deregistered.
	 *  @param data The pointer returned by the plugin's init() call
	 */
	void (*interfaces_deregistered)( mmr_plugin_data_t *data );

	/**
	 *  Accept configuration changes
	 *  @param data The pointer returned by the plugin's init() call
	 *  @param cfg The plugin's configuration parameters (plugin consumes the handle)
	 */
	void (*config)( mmr_plugin_data_t *data, strm_dict_t *cfg );

	/**
	 *  Clean up before getting unloaded.
	 *  @param data The pointer returned by the plugin's init() call
	 */
    void (*cleanup)( mmr_plugin_data_t *data );
} mmr_plugin_calls_t, mmr_plugin_calls_200_t;

#define MMR_PLUGIN_CALL_TABLE_NAME "mmr_plugin_200"
#define MMR_PLUGIN_CALL_TABLE       mmr_plugin_200
extern const mmr_plugin_calls_t MMR_PLUGIN_CALL_TABLE;

/**
 *  Increment the reference count of a plugin.
 *  A nonzero reference count prevents a plugin
 *  from being unloaded.
 *  @param plugin the plugin handle
 */
void mmr_plugin_ref( mmr_plugin_t *plugin );

/**
 *  Decrement the reference count of a plugin.
 *  When the reference count reaches zero,
 *  and the plugin has been flagged for unloading,
 *  it is unloaded and the plugin handle becomes invalid.
 *  @param plugin the plugin handle
 */
void mmr_plugin_unref( mmr_plugin_t *plugin );


/**
 *  Get the plugin name.
 *  This is a copy of the string that was passed to dlopen().
 *  @param plugin the plugin handle
 */
const char *mmr_plugin_dllname( mmr_plugin_t *plugin );

/**
 *  Export plugin properties.
 *  @param plugin The plugin handle
 *  @param props The properties to export (consumed by the call)
 */
void mmr_plugin_properties( mmr_plugin_t *plugin, strm_dict_t *props );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/plugin.h $ $Rev: 680336 $")
#endif
