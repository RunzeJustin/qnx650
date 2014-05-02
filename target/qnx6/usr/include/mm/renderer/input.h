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


#if !defined(MM_RENDERER_INPUT_H_INCLUDED)
#define MM_RENDERER_INPUT_H_INCLUDED

/** @file input.h
 *  Input control plugin API
 *  @ingroup routingAPI Routing plugin API
 */

#if !defined(MM_RENDERER_ENGINE_H_INCLUDED)
#include <mm/renderer/engine.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup routingAPI Routing plugin API
 */
/*@{*/

/**
 *  Input control instance handle.
 */
typedef struct mmr_input_control mmr_input_control_t;

/**
 *  Input control interface calls.
 */
typedef struct mmr_input_control_calls {
	/**
	 *	Input-control interface name.
	 */
	const char *name;

	/**
	 *  Create an input-control object from a device URL.
	 *  If the URL is not the right type for this plugin,
	 *  the call succeeds (returns NULL) but sets *ihandle to a null pointer.
	 *  @param ihandle Address of a variable to store the new handle in
	 *  @param url The device URL
	 *  @param type The input type
	 *  @param eng Engine handle to use for callbacks
	 *  @param data Plugin's data pointer (as returned by this plugin's init() function)
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*open)( mmr_input_control_t **ihandle, const char *url, const char *type, mmr_engine_handle_t *eng, mmr_plugin_data_t *data );

	/**
	 *  Destroy an input-control object
	 *  @param handle A control handle
	 *  @return NULL on success, or a pointer to error info on error
	 *          (but the handle is destroyed either way)
	 */
	const mmr_error_info_t *(*destroy)( mmr_input_control_t *handle );

	/**
	 *  Start streaming
	 *  @param handle A control handle
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*start)( mmr_input_control_t *handle );

	/**
	 *  Stop the plugin
	 *  @param handle A control handle
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*stop)( mmr_input_control_t *handle );

	/**
	 *  Seek to a position
	 *  @param handle A control handle
	 *  @param position The position to seek to
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*seek)( mmr_input_control_t *handle, const char *position );

	/**
	 *  Change the speed.
	 *  Should call mmr_engine_update_speed() if the speed actually changes.
	 *  @param handle A control handle
	 *  @param speed The new speed
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*speed)( mmr_input_control_t *handle, int speed );

	/**
	 *  Send a command.
	 *  @param handle A control handle
	 *  @param command The command
	 *  @return NULL on success, or a pointer to error info on error
	 */
	const mmr_error_info_t *(*command)( mmr_input_control_t *handle, const char *command );
} mmr_input_control_calls_t, mmr_input_control_calls_200_t;

/**
 *  Register an input control interface.
 *  Interface is automatically deregistered when its plugin is unloaded.
 *  @param handle The plugin handle, as given to the plugin's init() call
 *  @param calls The call table to register
 *  @return 0 on success, -1 on error
 */
extern int mmr_input_control_register( mmr_plugin_t *plugin, const mmr_input_control_calls_t *calls );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/input.h $ $Rev: 680336 $")
#endif
