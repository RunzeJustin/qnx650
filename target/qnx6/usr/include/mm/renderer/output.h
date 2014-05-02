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


#if !defined(MM_RENDERER_OUTPUT_H_INCLUDED)
#define MM_RENDERER_OUTPUT_H_INCLUDED

/** @file output.h
 *  Output-access plugin API
 *  @ingroup outputAPI Output-access plugin API
 */

#if !defined(MM_RENDERER_LOGGER_H_INCLUDED)
#include <mm/renderer/logger.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup outputAPI Output-access plugin API
 */
/*@{*/

/**
 *  Handle for an output access plugin library.
 */
typedef struct mmr_output_access_plugin mmr_output_access_plugin_t;

/**
 *  The registry's output handle.
 *  Represents an output attached (or being attached) to a context.
 *  Note that if a device supports multiple channels,
 *  each channel will have its own handle.
 */
typedef struct mmr_output mmr_output_t;

/**
 *  A plugin's handle for an output device.
 *  Each output-access plugin defines its own version of this structure.
 */
typedef struct mmr_output_access_handle mmr_output_access_handle_t;

struct mmr_plugin;

/**
 *  The "vtable" of an output access plugin library.
 */
typedef struct mmr_output_access_calls {
	/**
	 *  Plugin name
	 */
	const char *name;

	/**
	 *  Initialize a plugin being registered.
	 *  This function, if not NULL, is called only once per plugin,
	 *  regardless of how many clients ask to register it.
     *  @param logger A logger handle to use for logging
	 *  @return zero on success
	 */
	int (*init)( mmr_logger_t *logger );

	/**
	 *  Clean up a plugin.
	 *  If not NULL, is called once when the plugin is being deregistered.
	 */
	void (*cleanup)( void );

	/**
	 *  Get this plugin's handle for an output being attached to a context.
	 *  @param url The device URL (valid until the output detached or URL changed)
     *  @param type The output type, as specified by the client
	 *  @param outp The output handle
	 *  @return A handle, or NULL if this plugin does not support this device
	 */
	mmr_output_access_handle_t *(*gethandle)( const char *url, const char *type, mmr_output_t *outp );

	/**
	 *  Delete this plugin's handle for an output being detached from a context.
	 *  @param handle A handle previously returned by a gethandle call.
	 *  @return NULL, or a plugin handle to pass to mmr_plugin_unref()
	 */
	struct mmr_plugin *(*delhandle)( mmr_output_access_handle_t *handle );

	/**
	 *  Get this plugin's approval to change the output parameters.
	 *
	 *  There will always be a "url" and "type" in the output parameters object.
	 *  If a plugin does not support changing URLs, it shall reject attempts to change it.
	 *  The "type" will always match the original type; no need to check it.
	 *
	 *  A plugin should ignore any parameters with names that it does not recognize.
	 *  They may be meant for another plugin.
	 *
	 *  @param handle A handle previously returned by a gethandle call.
	 *  @param oldparms A handle for the old parameters.
	 *  @param newparms A new parameters.
	 */
	_Bool (*approveparams)( mmr_output_access_handle_t *handle,
			const strm_dict_t *oldparms, const strm_dict_t *newparms );

	/**
	 *  Set the output parameters, e.g. the URL of an existing output.
	 *  The parameters have been approved by a approveparams() call.
	 *  @param oldparms A handle for the old parameters.
	 *  @param newparms A handle for the new parameters.
	 */
    void (*changeparams)( mmr_output_access_handle_t *handle,
            const strm_dict_t *oldparms, const strm_dict_t *newparms );
} mmr_output_access_calls_t;


/*  Functions to be used by engine modules  */

/**
 *  Register a plugin.
 *  If this plugin is not registered yet,
 *  it will be initialized
 *  and added to the list of known plugins.
 *  @param calls A pointer to the plugin's call table
 *  @return the output registry's handle for this plugin,
 *           or NULL on error (errno is ENOMEM, or EIO if the init call failed).
 */
extern mmr_output_access_plugin_t *mmr_output_plugin_register( 
	const mmr_output_access_calls_t *calls );

/**
 *  Deregister a plugin.
 *  When the last client deregisters it, the cleanup function is called.
 *  Don't deregister a plugin if you're still using it!!!
 *  @param plugin 
 */
extern void mmr_output_plugin_deregister( mmr_output_access_plugin_t *plugin );

/**
 *  Get the URL of an output device
 *  @param rdev An output handle
 *  @return The URL of that output
 */
extern const char *mmr_output_url( mmr_output_t *rdev );

/**
 *  Get the output ID of the device
 *  @param rdev An output handle
 *  @return the output ID of this output
 */
extern unsigned mmr_output_id( mmr_output_t *rdev );

/**
 *  Get the context that the output is attached to
 *  @param rdev An output handle
 *  @return the context
 */
extern struct mmr_ctxt *mmr_output_context( mmr_output_t *rdev );

/**
 *  Get the output type of the device
 *  @param rdev An output handle
 *  @return the output type of this output
 */
extern const char *mmr_output_type( mmr_output_t *rdev );

/**
 *  Get the parameters of the device
 *  The returned handle is valid until the device is detached
 *  or its parameters changed
 *  @param rdev An output handle
 *  @return A handle for the parameters object
 */
extern const strm_dict_t *mmr_output_params( mmr_output_t *rdev );

/**
 *  Check if a plugin supports a device
 *  @param rdev The output handle of an output	 
 *  @param plugin A plugin handle
 *  @return What the plugin's gethandle() returned for this output
 */
extern mmr_output_access_handle_t *mmr_output_access(
	mmr_output_t *rdev, mmr_output_access_plugin_t *plugin );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/output.h $ $Rev: 680336 $")
#endif
