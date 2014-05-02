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


#if !defined(MM_RENDERER_ROUTING_H_INCLUDED)
#define MM_RENDERER_ROUTING_H_INCLUDED

/** @file routing.h
 *  Routing plugin API
 *  @ingroup routingAPI Routing plugin API
 */

#if !defined(MM_RENDERER_CONTEXT_H_INCLUDED)
#include <mm/renderer/context.h>
#endif

#if !defined(MM_RENDERER_PLUGIN_H_INCLUDED)
#include <mm/renderer/plugin.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup routingAPI Routing plugin API
 */
/*@{*/

/**
 *  Routing handle (opaque -- private in the plugin).
 */
typedef struct mmr_routing_handle mmr_routing_handle_t;

typedef struct mmr_routing_params mmr_routing_params_t; // Details below


/**
 *  Public data of a routing plugin instance.
 *  Do not look at the contents until after mmr_routing_create() has succeeded.
 *  Do not modify them yourself, ever.
 */
typedef struct mmr_routing_inst mmr_routing_inst_t;  // Details below

/**
 *  A plugin's private rating data
 */
typedef struct mmr_rating_private mmr_rating_private_t;

/**
 *  Routing interface calls
 */
typedef struct mmr_routing_calls {
	/**
	 *	Routing interface name.
	 */
	const char *name;

	/**
	 *  Rate an input.
	 *  @param pdata Plugin's data pointer (as returned by this plugin's init() function)
	 *  @param params Information about the input, context, and callbacks
	 *  @param track_parm Initial track parameters
	 *  @param rating Initialized to best rating so far.
	 *                The plugin should overwrite it with its own rating of the input, on a scale of 0 to 100.
	 *  @param err Buffer to return error information in
	 *  @return A pointer that will be given back to either unrate() or create(), or NULL on error
	 */
	mmr_rating_private_t *(*rate)( mmr_plugin_data_t *pdata, mmr_routing_params_t const *params, const strm_dict_t *track_parm, unsigned *rating, mmr_error_info_t *err );

	/**
	 *  Clean up after rating.
	 *  Called after rate() returns returns a non-NULL pointer,
	 *  to let the plugin know that create() will not be called.
	 *  @param pdata Plugin's data pointer (as returned by the plugin's init() function)
	 *  @param rdata The pointer returned by rate().
	 */
	void (*unrate)( mmr_plugin_data_t *pdata, mmr_rating_private_t *rdata );

	/**
	 *  Create a plugin instance.
	 *  @param pdata Plugin's data pointer (as returned by the plugin's init() function)
	 *  @param params Information about the input, context, and callbacks
	 *  @param track_parm Points to a variable holding a pointer to track parameters.
	 *                    The plugin can leave it alone or consume this pointer and replace it with a modified one.
	 *  @param rdata The pointer returned by rate().
	 *  @param err Buffer to return error information in
	 *  @return A new plugin handle, or NULL on error
	 */
	mmr_routing_handle_t *(*create)( mmr_plugin_data_t *pdata, mmr_routing_params_t const *params, strm_dict_t **track_parm, mmr_rating_private_t *rdata, mmr_error_info_t *err );

	/**
	 *  Destroy a plugin instance.
	 *  @param handle The plugin handle
	 */
	void (*destroy)( mmr_routing_handle_t *handle );

	/**
	 *  Prepare plugin instance for playback.
	 *  Called before start(), when the plugin is in a fully stopped state.
	 *  If seek() has not been called since the playback last stopped,
	 *  rewinds to the beginning (or the end, if speed is negative).
	 *  @param handle A plugin handle
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*prepare)( mmr_routing_handle_t *handle, int speed );

	/**
	 *  Start streaming.
	 *  Called after prepare().
	 *  If fails, the plugin is assumed to go to the fully stopped ("unprepared") state.
	 *  @param handle A plugin handle
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*start)( mmr_routing_handle_t *handle );

	/**
	 *  Stop the plugin.
	 *  May be called after prepare(), to indicate that start() will not be called,
	 *  or after nexttrk(), to prevent this track from playing next.
	 *  @param handle A plugin handle
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*stop)( mmr_routing_handle_t *handle );

	/**
	 *  Seek to a position.
	 *  May be called when stopped or playing, or even between prepare() and play().
	 *  @param handle A plugin handle
	 *  @param position The position to seek to, in milliseconds
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*seek)( mmr_routing_handle_t *handle, uint64_t position );

	/**
	 *  Change the speed.
	 *  May be called when stopped or playing, between prepare() and play(),
	 *  or even after the track is scheduled to play via the nexttrk() call.
	 *  @param handle A plugin handle
	 *  @param speed The new speed
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*speed)( mmr_routing_handle_t *handle, int speed );

	/**
	 *  Send a command.
	 *  May be called when stopped or playing, or even between prepare() and play().
	 *  @param handle A plugin handle
	 *  @param command The command
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*command)( mmr_routing_handle_t *handle, const char *command );

	/**
	 *  Set track parameters.
	 *  @param handle A plugin handle
	 *  @param track_parm Points to a variable holding a pointer to track parameters.
	 *                    The plugin can leave it alone or consume this pointer and replace it with a modified one.
	 *                    Either way, this object may be destroyed shortly -- make your clone if you need to keep it.
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*trkparams)( mmr_routing_handle_t *handle, strm_dict_t **parms );

	/**
	 *  Deal with a context-parameter change.
	 *  Note that returning an error does not prevent the operation.
	 *  If the caller decides to abort (or, more accurately, undo),
	 *  this function will be called again with oldparms and newparms reversed.
	 *  @param handle A plugin handle
	 *  @param oldparms Old context parameters
	 *  @param newparms New context parameters
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*ctxtparams)( mmr_routing_handle_t *handle,
		const strm_dict_t *oldparms, const strm_dict_t *newparms );

	/**
	 *  Deal with an output change.
	 *  Note that returning an error does not prevent the operation.
	 *  If the caller decides to abort (or, more accurately, undo),
	 *  this function will be called again with oldparms and newparms reversed.
	 *  @param handle A plugin handle
	 *  @param output_id The ID of the output being changed
	 *  @param output The output handle
	 *  @param oldparms Old output parameters, or NULL if the output is being attached
	 *  @param newparms New output parameters, or NULL if the output is being detached
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*output)( mmr_routing_handle_t *handle,
		unsigned output_id, mmr_output_t *output,
		const strm_dict_t *oldparms, const strm_dict_t *newparms );

	/**
	 *  Schedule a track to automatically play after this one ends, if possible.
	 *  The current track must have reported the eof state via the eof callback.
	 *  The next track is automatically unscheduled if the playing track receives
	 *  any of the calls that cancel the eof state (stop(), speed(), or seek()),
	 *  or when it calls the finished(), error(), or paused() callback.
	 *  @param handle A plugin handle
	 *  @param trk plugin info of the track to play next, or NULL to cancel
	 *  @param speed The speed to play that track at
	 *  @return NULL on success, or a pointer to error information
	 */
	const mmr_error_info_t *(*nexttrk)( mmr_routing_handle_t *handle, const mmr_routing_inst_t *trk, int speed );

} mmr_routing_calls_t, mmr_routing_calls_200_t;

/**
 *  Handle to pass to callback (opaque)
 */
typedef struct mmr_routing_cbdata mmr_routing_cbdata_t;

/**
 *  Callbacks.
 *  The first three provide a mutex-like locking mechanism associated with the plugin instance,
 *  and a condvar wait.
 *  The router plugin and its user must follow these rules:
 *
 *    * Plugin interface calls and callbacks are called with the
 *      instance locked.  Callbacks must not unlock it; interface calls
 *      are allowed to temporarily unlock it.
 *
 *    * The plugin can call the callbacks either from an interface call
 *      or from its own thread (after calling lock()).
 *
 *    * The plugin must not call the status(), warning(), eof(), finished(), or
 *      error() callbacks before its prepare() is called or after the
 *      stop() call or the finished() or error() callback has returned.
 *      The finished() callback must not be called before start() has returned.
 *
 *    * The metadata() callback can be called at any time during or after
 *      a successful create() call, but before destroy() returns.
 *
 *    * The eof() playback may be called when the plugin knows that it can complete
 *      the playback without more reading from the input.  Reading is assumed to be
 *      necessary after a prepare(), seek(), or speed() call -- the plugin can
 *      call eof() again from those calls when they don't create a need for reading.
 *
 *    * The plugin is free to use the lock and the wait() callback for
 *      its own private purposes.  They can be called at any time
 *      between the time create() is called and destroy() returns.
 *
 *    * The metadata callback consumes the mdata handle.
 *
 *    * Only the current track is allowed to call paused().
 */
typedef struct mmr_routing_callbacks {
	/** Lock the engine */
	int (*lock)( mmr_routing_cbdata_t *cbdata );
	/** Unlock the engine */
	int (*unlock)( mmr_routing_cbdata_t *cbdata );
	/** Wait on a condvar, up to the absolute time specified in timeout if not NULL */
	int (*wait)( mmr_routing_cbdata_t *cbdata, pthread_cond_t *cond, const struct timespec *timeout );
	/** Report the current position and status (if morestatus is not NULL, it gets consumed) */
	void (*status)( mmr_routing_cbdata_t *cbdata, uint64_t position, strm_dict_t *morestatus );
	/** Report that no more reading is needed to complete the playback.
	    Can happen at any point after prepare() is caled.
	    This condition is assumed to be implicitly cancelled by any speed(), seek() or stop() call.
	    The calls can re-issue this callback to re-report the EOF status. */
	void (*eof)( mmr_routing_cbdata_t *cbdata );
	/** Report that the playback of the current track has completed.
	    @param nexttrk NULL if playback stopped, or the next track if started automatically */
	void (*finished)( mmr_routing_cbdata_t *cbdata, mmr_routing_cbdata_t *nexttrk );
	/** Report a warning.  A warning implies that the playback continues. */
	void (*warning)( mmr_routing_cbdata_t *cbdata, const char *warning );
	/** Report that the playback has stopped due to an error.
	    @param error error info */
	void (*error)( mmr_routing_cbdata_t *cbdata, const mmr_error_info_t *error );
	/** Report new metadata for the track. */
	void (*metadata)( mmr_routing_cbdata_t *cbdata, strm_dict_t *mdata );
	/** Report that the track has spontaneously paused.  */
	void (*paused)( mmr_routing_cbdata_t *cbdata );
} mmr_routing_callbacks_t;

struct mmr_routing_params { // a.k.a. mmr_routing_params_t;
	const char *track_url;
	const char *track_type;
	mmr_ctxt_t *ctxt; // Use this to access outputs
	mmr_routing_callbacks_t const *callbacks;
	mmr_routing_cbdata_t *cbdata;

	/** An existing plugin instance, or NULL.
	    When passed to create(), it's a hint that nexttrk() will likely be called with this track */
	const mmr_routing_inst_t *oldinst;
};

/**
 *  Register a routing interface.
 *  Called by a routing plugin's init() function.
 *  Interface is automatically deregistered when its plugin is unloaded.
 *  @param handle The plugin handle, as given to the plugin's init() call
 *  @param calls The routing call table to register
 *  @return 0 on success, -1 on error
 */
extern int mmr_routing_register( mmr_plugin_t *plugin, const mmr_routing_calls_t *calls );

struct mmr_routing_inst { // mmr_routing_inst_t
	const mmr_routing_calls_t *calls;
	mmr_routing_handle_t *handle;
	struct mmr_plugin_interface *plugin;
};

/**
 *  Query plugins and find the best-rated one.
 *  After this returns a positive rating, you *must* call either mmr_routing_create() or mmr_routing_unrate().
 *  @param params Information about the input and context to rate
 *  @param track_parm Initial track parameters for this track
 *  @param instdata Buffer for plugin information -- do not look at the contents
 *                  until after mmr_routing_create() has succeeded
 *  @return: the rating (greater than zero if a plugin was found), or -1 on error
 */
int mmr_routing_rate( mmr_routing_params_t const *params, const strm_dict_t *track_parm, mmr_routing_inst_t *instdata, mmr_error_info_t *err );

/**
 *  Clean up the rating information.
 *  You *must* call this function after mmr_routing_rate() returns a positive rating,
 *  if you decide not to call mmr_routing_create(). 
 *  It's safe to call it after mmr_routing_rate() fails or returns a zero rating,
 *  or after calling mmr_routing_create(), but it's a no-op.
 *
 *  @param instdata The plugin information stored by mmr_routing_rate() (a copy is fine too).
 */
void mmr_routing_unrate( mmr_routing_inst_t *instdata );

/**
 *  Create an instance of the best-rated routing plugin.
 *  The initial position is at the beginning of the track
 *  if the current speed is non-negative, or at the end otherwise.
 *  @param params Information about the input and context
 *                (must be identical to what you gave to mmr_routing_rate())
 *  @param track_parm Must point to a variable holding a pointer to track parameters.
 *                    The plugin will either leave it alone or consume this pointer and replace it with a modified one.
 *  @param instdata The plugin information stored by mmr_routing_rate() (a copy is fine too).
 *  @return instdata on success, NULL on error
 */
mmr_routing_inst_t *mmr_routing_create( mmr_routing_params_t const *params, strm_dict_t **track_parm, mmr_routing_inst_t *instdata, mmr_error_info_t *err );

/**
 *  Safely destroy a plugin instance.
 *  An engine plugin should not call a routing plugin's destroy function directly!
 *  @param instdata The plugin information stored by mmr_routing_create() (a copy is fine too).
 */
void mmr_routing_destroy( mmr_routing_inst_t *instdata );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/routing.h $ $Rev: 680336 $")
#endif
