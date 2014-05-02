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


#if !defined(MM_RENDERER_ENGINE_H_INCLUDED)
#define MM_RENDERER_ENGINE_H_INCLUDED


/** @file engine.h
 *  Engine plugin API
 *  @ingroup engineAPI Engine plugin API
 */

#if !defined(MM_RENDERER_CONTEXT_H_INCLUDED)
#include <mm/renderer/context.h>
#endif

#if !defined(MM_RENDERER_PLUGIN_H_INCLUDED)
#include <mm/renderer/plugin.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup engineAPI Engine plugin API
 */
/*@{*/

/**
 *  @brief A plugin's handle for an engine instance.
 *
 *  @details A plugin's handle for an engine instance.
 *  Each engine defines its own version of this structure.
 */
typedef struct mmr_engine_handle mmr_engine_handle_t;

/**
 *  @brief Information on the input file.
 */
typedef struct mmr_engine_input_info {
	mmr_ctxt_t *ctxt;
	const char *url;
	const char *type;
	const strm_dict_t *trackparam0;
} mmr_engine_input_info_t;

/**
 *  @brief A plugin's internal rating data.
 *
 *  @details A plugin's internal rating data.
 *  Each engine defines its own version of this structure.
 */
typedef struct mmr_rating_data mmr_rating_data_t;

/**
 *  @brief References to the methods that implement engine configuration and playback operations. 
 *
 *  @details References to the methods that implement engine configuration and playback operations
 *  (the "vtable" of an engine plugin).
 *  Note that all these calls are made with the context locked,
 *  and they should not call mmr_context_lock() and mmr_context_unlock().
 *  The calls should use mmr_context_error_set() to make the API call fail.
 */
typedef struct mmr_engine_calls {
	/**
	 *	Engine name.
	 */
	const char *name;

	/**
	 *  Rate the engine's ability to handle the context's input and outputs.
	 *  @param info Information about the input
	 *  @param input_parm Initial input parameters
	 *  @param rating Initialized to best rating so far.
	 *                The plugin should overwrite it with its own rating of the input, on a scale of 0 to 100.
	 *  @param pdata Plugin's data pointer (as returned by the plugin's init() function)
	 *  @return A pointer that will be given back to either unrate() or create()
	 */
	mmr_rating_data_t *(*rate)( mmr_engine_input_info_t const *info, const strm_dict_t *input_parm, unsigned *rating, mmr_plugin_data_t *pdata );

	/**
	 *  Clean up after rating.
	 *  Called after rate() returns returns a non-NULL pointer without reporting an error,
	 *  to let the plugin know that create() will not be called.
	 *  @param pdata Plugin's data pointer (as returned by the plugin's init() function)
	 *  @param rdata The pointer returned by rate().
	 */
	void (*unrate)( mmr_plugin_data_t *pdata, mmr_rating_data_t *rdata );

	/**
	 *  Create an engine instance.
	 *  @param info Information about the input
	 *  @param input_parm Points to a variable holding a pointer to input parameters.
	 *                    The plugin can leave it alone or consume this pointer and replace it with a modified one.
	 *                    On error, it's also OK to consume it and set *input_param to NULL.
	 *  @param pdata Plugin's data pointer (as returned by the plugin's init() function)
	 *  @param rdata The pointer returned by rate().
	 *  @return Ignored upon error;
	 *          otherwise, an instance handle or NULL if not enough memory
	 */
	mmr_engine_handle_t *(*create)( mmr_engine_input_info_t const *info, strm_dict_t **input_parm, mmr_plugin_data_t *pdata, mmr_rating_data_t *rdata );

	/**
	 *  Destroy an engine instance.
	 *  Called after the playback is stopped.
	 *  @param handle The engine instance handle
	 */
	void (*destroy)( mmr_engine_handle_t *handle );

	/**
	 *  Get context handle
	 *  This function does not fail.
	 *  @param handle The engine instance handle
	 *  @return The context handle for this plugin
	 */
	mmr_ctxt_t *(*getctxt)( mmr_engine_handle_t *handle );

	/**
	 *  Accept new context parameters
	 *  @param handle The engine instance handle
	 *  @param oldparms A handle for the old parameters (call must consume, even on error)
	 *  @param newparms A handle for the new parameters (will remain valid until next call)
	 */
	void (*context_parameters)( mmr_engine_handle_t *handle, strm_dict_t *oldparms, const strm_dict_t *newparms );

	/**
	 *  Set input parameters.
	 *  @param handle The engine instance handle
	 *  @param newparms A handle for the new parameters (call must consume, even on error)
	 *  @return A new handle to keep (on an error, too).  May get destroyed shortly -- keep your own clone if needed.
	 */
	strm_dict_t *(*input_parameters)( mmr_engine_handle_t *handle, strm_dict_t *newparms );

	/**
	 *  Attach a new output.
	 *  @param handle The engine instance handle
	 *  @param output_id The ID of the new output
	 *  @param output The new output object
	 */
	void (*output_attach)( mmr_engine_handle_t *handle, unsigned output_id, mmr_output_t *output );

	/**
	 *  Detach an output.
	 *  @param handle The engine instance handle
	 *  @param output_id The ID of the output being detached
	 *  @param output The output object to detach
	 */
	void (*output_detach)( mmr_engine_handle_t *handle, unsigned output_id, mmr_output_t *output );

	/**
	 *  Set output parameters
	 *  @param handle The engine instance handle
	 *  @param output_id The ID of the output
	 *  @param output The output object
	 *  @param oldparms A handle for the old parameters
	 *  @param newparms A handle for the new parameters
	 */
	void (*output_parameters)( mmr_engine_handle_t *handle,
		unsigned output_id, struct mmr_output *output, const strm_dict_t *oldparms, const strm_dict_t *newparms );

	/**
	 *  Start the plugin
	 *  Will not be called if already playing.
	 *  Should either start playback or report a failure.
	 *  @param handle The engine instance handle
	 */
	void (*play)( mmr_engine_handle_t *handle );

	/**
	 *  Stop the plugin
	 *  Will not be called if already stopped.
	 *  Must stop playback, even on failure.
	 *  @param handle The engine instance handle
	 */
	void (*stop)( mmr_engine_handle_t *handle );

	/**
	 *  Seek to a position.
	 *  May be called while stopped or playing.
	 *  @param handle The engine instance handle
	 *  @param position The position to seek
	 */
	void (*seek)( mmr_engine_handle_t *handle, const char *position );

	/**
	 *  Change the speed.
	 *  Should call mmr_context_speed_set() if the speed actually changes.
	 *  May be called while stopped or playing.
	 *  @param handle The engine instance handle
	 *  @param speed The new speed
	 */
	void (*speed)( mmr_engine_handle_t *handle, int speed );

	/**
	 *  Send a command.
	 *  May be called while stopped or playing.
	 *  @param handle The engine instance handle
	 *  @param command The command
	 */
	void (*command)( mmr_engine_handle_t *handle, const char *command );
} mmr_engine_calls_t, mmr_engine_calls_200_t;


/**
 *  @brief Register an engine interface.
 *
 *  @details Register an engine interface.
 *  Adds the engine to the list of available engines.
 *  This must be called from the plugin's init() call.
 *  The interface will be automatically removed
 *  when the plugin is being deregistered.
 *
 *  @param plugin The plugin handle, as given to the plugin's init() call
 *  @param calls The engine call table to register
 *  @return 0 on success, -1 on error
 */
extern int mmr_engine_register( mmr_plugin_t *plugin, const mmr_engine_calls_t *calls );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/engine.h $ $Rev: 717696 $")
#endif
