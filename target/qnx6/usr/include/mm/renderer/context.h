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


#if !defined(MM_RENDERER_CONTEXT_H_INCLUDED)
#define MM_RENDERER_CONTEXT_H_INCLUDED


/** @file context.h
 *  Context API functions
 *  @ingroup engineAPI Engine plugin API
 */

#include <stdint.h>
#include <stdarg.h>

#include <pthread.h>

#if !defined(MM_RENDERER_OUTPUT_H_INCLUDED)
#include <mm/renderer/output.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup engineAPI Engine plugin API
 */
/*@{*/

/**
 *  @brief The context pointer as seen by plugins.
 */
typedef struct mmr_ctxt mmr_ctxt_t;

/**
 *  @brief Publish the context status.
 *  @details Publish the context status.
 *  An engine calls this function periodically during playback.
 *  This call must be made with the context locked.
 *  @param ctxt The context handle
 *  @param position NULL, or the current position
 *  @param morestatus NULL, or status to publish (handle gets consumed)
 */
extern void mmr_context_update_status( mmr_ctxt_t *ctxt,
	const char *position, strm_dict_t *morestatus );

/**
 * @brief Publish the context parameters.
 * @details Publish the context parameters.
 * A plugin  calls this function to extract parameters applied to the given context.
 * This call must be made with the context locked.
 * @param ctxt The context handle
 * @return a pointer to a structure containing the context parameters.
 */ 
extern const strm_dict_t *mmr_context_parameters_get( mmr_ctxt_t *ctxt );

/**
 *  @brief Publish the input metadata.
 *  @details Publish the input metadata.
 *  This call must be made with the context locked
 *  and can be made during the create() call as long as it returns success.
 *  @param ctxt The context handle
 *  @param mdata A handle to a metadata object (consumed by the function)
 */
extern void mmr_context_update_metadata( mmr_ctxt_t *ctxt, strm_dict_t *mdata );

/**
 *  @brief Publish a speed change.
 *  @details Publish a speed change.
 *  An engine calls this function every time its speed changes,
 *  including when the change was requested explicitly.
 *  This call must be made with the context locked.
 *  @param ctxt The context handle
 *  @param newspeed The new speed
 */
extern void mmr_context_speed_set( mmr_ctxt_t *ctxt, int newspeed );

/**
 *  @brief Get the current speed.
 *  @details Get the current speed.
 *  @param ctxt The context handle
 *  @return The current speed
 */
extern int mmr_context_speed_get( mmr_ctxt_t *ctxt );

/**
 *  @brief Publish the stopped state.
 *  @details Publish the stopped state.
 *  An engine calls this function to report that it has stopped
 *  because of an error at the end of media (but not when stopped via API).
 *  @param ctxt The context handle
 *  @param error NULL on end of media, or an error description to be sent to PPS
 */
extern void mmr_context_stopped( mmr_ctxt_t *ctxt, const mmr_error_info_t *error );

/**
 *  @brief Publish a warning.
 *  @details Publish a warning.
 *  An engine calls this function to publish a warning during playback.
 *  @param ctxt The context handle
 *  @param warning The warning description to be sent to PPS
 *                 (the warning position comes from mmr_context_update_status())
 */
extern void mmr_context_warning( mmr_ctxt_t *ctxt, const char *warning );

/**
 *  @brief Lock a context.
 *  @details Lock a context.
 *  Prevents any API calls from being delivered to the context until it is unlocked
 *  @param ctxt The context handle
 *  @return 0 on success, or an errno
 */
extern int mmr_context_lock( mmr_ctxt_t *ctxt );

/**
 *  @brief Unlock a context.
 *  @details Unlock a context.
 *  Allows API calls to being delivered again
 *  @param ctxt The context handle
 *  @return 0 on success, or an errno
 */
extern int mmr_context_unlock( mmr_ctxt_t *ctxt );

/**
 *  @brief Wait on a condition variable.
 *  @details Wait on a condition variable.
 *  Uses the context lock instead of a mutex.
 *  @param ctxt The context handle
 *  @param cond The condition variable
 *  @param timespec NULL or a timeout
 */
extern int mmr_context_wait( mmr_ctxt_t *ctxt, pthread_cond_t *cond, const struct timespec *timeout );

/**
 *  @brief Get the context name.
 *  @details Get the context name.
 *  @param ctxt The context handle
 *  @return The name of the context
 */
extern const char *mmr_context_name( mmr_ctxt_t *ctxt );

/**
 *  @brief Return information about the context's creator.
 *  @details Return information about the context's creator.
 *  @param ctxt The context handle
 *  @param cinfo Buffer for the info
 */
void mmr_client_info( mmr_ctxt_t *ctxt, mmr_client_info_t *cinfo );

/**
 *  @brief Match the user and group ids of the context owner.
 *  @details Temporarily fix the process euid:egid to the context owner,
 *  or to the default "idle" IDs if the context is NULL.
 *  Must be called with the context locked (if not NULL).
 *  This also acts as a lock that can be used to protect global process-wide resources,
 *  such as environment variables.
 *  Revert to the normal state by calling mmr_client_unbecome().
 *  Do not call any mm-renderer library functions or callbacks between those two calls.
 *  @param ctxt The context or NULL.
 *  @return 0 on success, or an error code
 */
int mmr_client_become( mmr_ctxt_t *ctxt );

/**
 *  @brief Allow the process euid:egid "float" again.
 *  @details Allow the process euid:egid "float" again.
 *  @param ctxt The context or NULL (same as you passed to mmr_client_become()).
 *  @return 0 on success, or an error code
 */
int mmr_client_unbecome( mmr_ctxt_t *ctxt );

/**
 *  @brief Return the outputs of the context.
 *  @details Return the outputs of the context.
 *  @param ctxt The context handle
 *  @param len If not NULL, a pointer where to store the length of the returned array
 *  @param count If not NULL, a pointer where to store the number of outputs in the array
 *  @return Pointer to an array of outputs (some elements may be null pointers)
 */
extern mmr_output_t *const *mmr_context_outputs( mmr_ctxt_t *ctxt, size_t *len, size_t *count );

/**
 *  @brief Set error status and information.
 *  @details Set error status and information.
 *  This function should only be called from an interface call.
 *  @param ctxt The context handle
 *  @param error The error information
 *  @param fmt NULL or a printf-style format and argument list (no newline at the end)
 */
extern void mmr_context_error_set( mmr_ctxt_t *ctxt, const mmr_error_info_t *error, const char *fmt, ... );

/**
 *  @brief Set error status and information.
 *  @details Set error status and information.
 *  This function should only be called from an interface call.
 *  @param ctxt The context handle
 *  @param error The error information
 *  @param fmt A printf-style format (no newline at the end)
 *  @param ap A variable-argument vector
 */
extern void mmr_context_error_setv( mmr_ctxt_t *ctxt, const mmr_error_info_t *error, const char *fmt, va_list ap );

/**
 *  @brief Clear error status.
 *  @details Clear error status.
 *  This function should only be called from an interface call.
 *  It unsets any error status that may have been set in the current call.
 *  @param ctxt The context handle
 */
extern void mmr_context_error_clear( mmr_ctxt_t *ctxt );

/**
 *  @brief Check error status and information.
 *  @details Check error status and information.
 *  This function should only be called from an interface call.
 *  @param ctxt The context handle
 *  @return Error information for the current interface call, or NULL if none set.
 */
extern const mmr_error_info_t *mmr_context_error_get( mmr_ctxt_t *ctxt );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/context.h $ $Rev: 680336 $")
#endif
