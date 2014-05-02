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


#if !defined(MM_RENDERER_CORE_H_INCLUDED)
#define MM_RENDERER_CORE_H_INCLUDED

/** @file core.h
 *  mm-renderer extended API functions
 *  These functions exist in the core library but not in the client library.
 *  @ingroup ExtAPI Extended API
 */

#if defined(MM_RENDERER_PLUGIN_HEADERS_INCLUDED)
#error "Please don't mix plugin headers with <mm/renderer/core.h>"
#endif

#if !defined(MM_RENDERER_H_INCLUDED)
#include <mm/renderer.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup ExtAPI Extended API
 */
/*@{*/

/**
 *  Typedef for a logger function
 *
 *  @param arg The user argument passed to mmr_logger_set()
 *  @param level Severity level as defined in <sys/slog.h>
 *  @param msg The message to log
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
typedef void mmr_logger_f( void *arg, int level, const char *msg );

/**
 *  Set up a logger function.
 *  This function is <i>not</i> thread safe.
 *  Call it before creating any contexts.
 *
 *  @param ctxt A context handle, or NULL to set up a default for subsequently created handles
 *  @param logger A pointer to the logger function
 *  @param arg The user argument to pass to the logger function
 */
void mmr_logger_set( mmr_connection_t *cnct, mmr_logger_f *logger, void *arg );

/**
 *  Set a group-ID override
 *  Set group ID of the context directories and make them accessible to that group.
 *  Must be called before mmr_connect().
 *
 *  @param: gid The group ID to use for the override
 */
void mmr_gid_override( gid_t gid );

/**
 *  Set client info.
 *  Affects any contexts subsequently created using the same connection.
 *  Also used to decide whether to let the client open a context.
 *  Note that currently the core library supports only a single connection object.
 *  @param cnct The connection handle
 *  @param info Client info to record with the connection object
 *  @return Zero on success, -1 on error (errno is set)
 */
int mmr_client_set( mmr_connection_t *cnct, mmr_client_info_t const *info );

/**
 *  Set the effective user and group ids to run with
 *  The core library will switch to these IDs whenever it does not need
 *  to be running with a client's credentials.
 *  (It will also occassionally switch to the credentials
 *  you called mmr_connect() with, presumably with root privileges.)
 *  @param cnct The connection handle
 *  @param uid The user ID to use
 *  @param gid The group ID to use
 *  @param grps An array of gids to use for supplementary groups
 *  @param ngrps The number of gids in the grps array
 *  @return Zero on success, -1 on error (errno is set)
 */
int mmr_user_set( mmr_connection_t *cnct, uid_t uid, gid_t gid, size_t ngrps, const gid_t grps[ngrps] );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/core.h $ $Rev: 691619 $")
#endif
