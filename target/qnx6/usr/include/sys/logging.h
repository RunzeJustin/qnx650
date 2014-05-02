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

/***************************************************************************//** 
 * \brief
 * This is a generic logging facility that allows multiple independent logging
 * contexts to exist within a single executable.
 *
 * To use it, a call is made to log_init() to create and initialize a logging
 * context. A handle this context is then used as a parameter to the various
 * logging macros defined below.
 * 
 * Also, this module is QDB-aware, and so provides a special macro for logging
 * errors from QDB.
 * 
 * Using this library
 * ==================
 * 
 * In a source file, an instance of a log_hdl_t pointer must be created.
 * 

log_hdl_t	*some_submodule_log = NULL;

 *  This pointer must be initialized with a call to log_init().
 
some_submodule_log = log_init("PRFX", _SLOGC_MAJOR_CODE, MINOR_CODE,
							  initial_verbosity, initial_flags, "a_name", false); 
 
 *
 * The logging macros in this file may then be used referring to the pointer.
 * 
 * If the submodule that's been created is used outside of its creation, it will
 * have to be declared extern in a heade file.

extern log_hdl_t	*some_submodule_log;

 * In the same header file, it might make sense to define new macros for the
 * submodule logging. Only those needed should be defined.

#define SOME_SUBMODULE_LOG_INFO(verbose_level, format, args...) \
	LOG_EMIT_INFO(some_submodule_log, verbose_level, format, ## args)

#define SOME_SUBMODULE_LOG_WARNING(verbose_level, format, args...) \
	LOG_EMIT_WARNING(some_submodule_log, verbose_level, format, ## args)

#define SOME_SUBMODULE_LOG_ERROR(format, args...) \
	LOG_EMIT_ERROR(some_submodule_log, format, ## args)

#define SOME_SUBMODULE_LOG_CRITICAL(format, args...) \
	LOG_EMIT_CRITICAL(some_submodule_log, format, ## args)

#define	SOME_SUBMODULE_EMITS_TIMING() \
	((some_submodule_log->control_flags & LOG_EMIT_TIME_LOGS)!=0)

#define SOME_SUBMODULE_LOG_TIMING(format, args...) \
	LOG_EMIT_TIMING(some_submodule_log, format, ## args)

#define SOME_SUBMODULE_LOG_QDBERR(qdb_hdl_ptr, format, args...) \
	LOG_EMIT_QDBERR(some_submodule_log, qdb_hdl_ptr, format, args...)

 * 
 * This module provides a real example by providing an API logging submodule
 * that may be initialized if needed.
 */

#ifndef _H_LOGGING_H_
#define _H_LOGGING_H_

#include <stdio.h>
#include <stdbool.h>
#include "mm/mmsupport.h"

__BEGIN_DECLS

#ifndef __GNUC__
#define __attribute__(x) /*NOTHING*/
#endif

/**
 * Slog severities used to trigger internal operations.
 */

/** QDB Error logging. */
#ifdef __QNXNTO__
#define _SLOG_QDBERR			(_SLOG_SEVMAXVAL+1)
#else
#define _SLOG_QDBERR			(LOG_LOCAL0)
#endif

/** Performance timing log emission. */
#ifdef __QNXNTO__
#define _SLOG_TIMING			(_SLOG_QDBERR+1)
#else
#define _SLOG_TIMING			(LOG_LOCAL1)
#endif

/**
 * Useful #defines for time reporting.
 */
#ifndef BILLION
#define BILLION		1000000000LL
#endif
#ifndef MILLION
#define MILLION		1000000LL
#endif

/******************************************************************************/ 

/**
 * Maximum length of the context description string; it is used as a prefix to 
 * all the logs emitted through this context. 
 */
#define LOG_PREFIX_MAX_LENGTH	12
#define LOG_MAX_MODULE_NAME		32

/**
 * Control flags. Operational and behaviourial mixed!
 */
#define	LOG_EMIT_TO_STDERR		0x0001
#define	LOG_EMIT_TIME_LOGS		0x0002


/**
 * Structure that defines a logging context. 
 *  
 * This is not defined as opaque to the user so that macros rather than 
 * functions can be used to determine if logging should take place. However, 
 * users should generally treat this as an opaque object. 
 * 
 * Having said that, it may be possible to define additional control flags
 * and use them from here...
 */
typedef struct log_hdl {
	char        prefix[LOG_PREFIX_MAX_LENGTH];	/**< A string used as a prefix for all logs. */
	int         slogcode;		/**< The slogcode value (from slogcodes.h or other) */
	unsigned    verbosity;		/**< The current verbosity setting of the context. */
	unsigned    control_flags;	/**< Set of the LOG_EMIT_XXX flags. */
	char        name[LOG_MAX_MODULE_NAME];	/**< Name of the log module. */
	bool        hidden;						/**< If true, module is not listed when queried */
} log_hdl_t;


/** 
 * This function assigns the logging options string that may have been collected
 * at startup. Any values found in this string will over-ride any initialization
 * set in the log_init() function for the subnodules.
 * 
 * Note that the string must exist during the log_init() calls for each module
 * that follow; only a pointer to it is saved.
 * 
 * The options string contains one or more of the following  groups separated by
 * the ';' character:
 *      <modulename1>@<verbosity>:<flags>
 * 
 * @param logging_option	Options string normally found at startup.
 */
void log_options_set(const char *logging_option);

/** 
 * This function is called once for each logging submodule that is wanted 
 * within the code.
 *  
 * @param prefix		String to use in prefix of slogs for identifying 
 *                      the source of the log. May be NULL for no prefix.
 * @param major			The major slogcode value to use for the module. This
 *                      would normally be the same for all components in the
 *                      process that includes the library.
 * @param minor			The minor slogcode value to use for the module.
 * @param verbosity		Initial value of verbosity.
 * @param control_flags	Initial value of control flags.
 * @param name          Name of the logging module, queried when listing or
 *                      setting levels.
 * @param hidden        On a request to list the modules, if true this 
 *                      module will not appear.
 * @return NULL on failure 
 * @return non-NULL pointer to log_hdl_t structure on success. 
 */
log_hdl_t *log_init(const char *prefix, int major, int minor, unsigned verbosity,
					unsigned control_flags, const char *name, bool hidden);

/** 
 * Terminates use of the logging context.
 * 
 * @param hdl	Pointer to context created by log_init();
 * @return 0 on success
 */
int log_terminate(log_hdl_t *hdl);

/** 
 * The generic log emission function.
 * 
 * @param hdl		Pointer to context created by log_init();
 * @param severity	Severity as defined by the slogf() function. 
 * @param func		The function name emitting the log. 
 * @param line		The line number where the log is being emitted. 
 * @param fmt		Format as in printf(). 
 * @param ...		Parameters to the format as in printf() 
 */
void log_emit(const log_hdl_t *hdl, int severity, const char *func, int line, const char *fmt, ...)
	__attribute__ ((format(printf, 5, 6)));

/** 
 * This function queries which modules have been registered for logging.
 * 
 * This could be used to provide configuration feedback to an end user for
 * debugging or monitoring purposes.
 * 
 * @param buffer	Buffer to place the list of logging modules, comma deliminated.
 * @param size		Size of the buffer to place the list of logging modules in.
 * @return the length of the complete list (less than size, or buffer contains a truncated string)
 */
size_t log_modules_query(char *buffer, size_t size);

/** 
 * This function sets the levels for a given logging submodule.
 * 
 * This is used to change the levels at run time.
 * 
 * @param name		Name of the logging module. If NULL, all submodules are set.
 * @param verbosity	Verbosity level setting
 * @param flags		Control flags value
 * @return 0
 */
int log_module_set(const char *name, unsigned verbosity, unsigned flags);

/**
 * An information log, corresponding to slogf() severity _SLOG_INFO. 
 *  
 * @param hdl		Pointer to context created by log_init();
 * @param verbose_level	The verbosity level required for this log to be 
 *                      emitted.
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_INFO(hdl, verbose_level, format, args...) \
( (hdl)->verbosity >= (verbose_level) ? \
	log_emit((hdl), _SLOG_INFO, __PRETTY_FUNCTION__, __LINE__, format, ##args) : (void)0 )

/**
 * A warning log, corresponding to slogf() severity _SLOG_WARNING. 
 *  
 * @param hdl			Pointer to context created by log_init();
 * @param verbose_level	The verbosity level required for this log to be emitted.
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_WARNING(hdl, verbose_level, format, args...) \
( (hdl)->verbosity >= (verbose_level) ? \
	log_emit(hdl, _SLOG_WARNING, __PRETTY_FUNCTION__, __LINE__, format, ##args) : (void) 0 )

/**
 * An error log, corresponding to slogf() severity _SLOG_ERROR. These are 
 * emitted at all levels of verbosity. 
 *  
 * @param hdl			Pointer to context created by log_init();
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_ERROR(hdl, format, args...) \
log_emit(hdl, _SLOG_ERROR, __PRETTY_FUNCTION__, __LINE__, format, ##args)

/**
 * An critical log, corresponding to slogf() severity _SLOG_CRITICAL. These are
 * emitted at all levels of verbosity. 
 *  
 * @param hdl			Pointer to context created by log_init();
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_CRITICAL(hdl, format, args...) \
log_emit(hdl, _SLOG_CRITICAL, __PRETTY_FUNCTION__, __LINE__, format, ##args)

/**
 * A database error log, corresponding to slogf() severity _SLOG_QDBERR. These
 * are emitted at all levels of verbosity. 
 *  
 * @param hdl			Pointer to context created by log_init();
 * @param qdb_hdl_ptr	Database handle. 
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_QDBERR(hdl, qdb_hdl_ptr, format, args...) \
do { \
	const char* qdberr = qdb_geterrmsg(qdb_hdl_ptr); \
	log_emit(hdl, _SLOG_QDBERR, __PRETTY_FUNCTION__, __LINE__, format" (qdb error: %s)" , ##args, qdberr ? qdberr : "<none>" ); \
} while(0)

/**
 * A time log, corresponding to slogf() severity _SLOG_INFO. These are emitted 
 * at all levels of verbosity, but only if the log_emit_time_logs flag is set.
 * 
 * @param hdl			Pointer to context created by log_init();
 * @param format		Format as in printf(). 
 * @param ...			Parameters to the format as in printf() 
 */
#define LOG_EMIT_TIMING(hdl, format, args...) \
( (hdl)->control_flags & LOG_EMIT_TIME_LOGS ? \
	log_emit(hdl, _SLOG_TIMING, __PRETTY_FUNCTION__, __LINE__, format, ##args) : (void) 0 )

/**
 * Define _LOGGING_NO_INCLUDE_API_ to stop a pre-defined API logging context
 * from being added.
 */
#ifndef	_LOGGING_NO_INCLUDE_API_

/*
 * The handle to the API logging submodule. User must create this somewhere and
 * initialize it.
 * 

log_hdl_t	*api_log = NULL;

{...
	api_log = log_init("myAPI", _SLOGC_MAJOR_CODE, MINOR_CODE, initial_verbosity,
						initial_flags, "api", false); 
 ...
}
 */
extern log_hdl_t *api_log;

#define API_LOG_INFO(verbose_level, format, args...) \
	LOG_EMIT_INFO(api_log, verbose_level, format, ## args)

#define API_LOG_WARNING(verbose_level, format, args...) \
	LOG_EMIT_WARNING(api_log, verbose_level, format, ## args)

#define API_LOG_ERROR(format, args...) \
	LOG_EMIT_ERROR(api_log, format, ## args)

#define API_LOG_CRITICAL(format, args...) \
	LOG_EMIT_CRITICAL(api_log, format, ## args)

#define	API_EMITS_TIMING() \
	((api_log->control_flags & LOG_EMIT_TIME_LOGS)!=0)

#define API_LOG_TIMING(format, args...) \
	LOG_EMIT_TIMING(api_log, format, ## args)

/* No QDB macro created; it's assumed the API doesn't need to log those kinds
of things. */

#endif	/* ! _LOGGING_NO_INCLUDE_API_ */


__END_DECLS

#endif /* _H_LOGGING_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/logging/public/sys/logging.h $ $Rev: 691213 $")
#endif
