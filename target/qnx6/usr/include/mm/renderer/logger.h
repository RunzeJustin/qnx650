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

#if !defined(MM_RENDERER_LOGGER_H_INCLUDED)
#define MM_RENDERER_LOGGER_H_INCLUDED

#if defined(MM_RENDERER_H_INCLUDED)
#error "Please don't mix plugin headers with <mm/renderer.h>"
#endif

#define MM_RENDERER_PLUGIN_HEADERS_INCLUDED

#if !defined(MM_RENDERER_TYPES_H_INCLUDED)
#include <mm/renderer/types.h>
#endif

#include <stdarg.h>
#include <sys/slog.h>
#define _SLOG_DEBUG3 (_SLOG_DEBUG2+1)
#define _SLOG_DEBUG4 (_SLOG_DEBUG2+2)

/** @file logger.h
 *  Logger API functions
 *  @ingroup pluginAPI Plugin API
 */

#if !defined(MMR_LOG_MIN)
 #if defined(NDEBUG) && 0 // Always enable full debug for now
  #define MMR_LOG_MIN _SLOG_INFO
 #else
  #define MMR_LOG_MIN _SLOG_DEBUG4
 #endif
#endif

#if defined(__GCC__)
  #define MMR_PRINTFLIKE( fmt, var ) __attribute__((format(__printf__,fmt,var)))
#else
  #define MMR_PRINTFLIKE( fmt, var )
#endif

__BEGIN_DECLS

/**
 *  Logger handle used by plugins
 */
typedef struct mmr_logger mmr_logger_t;

/**
 *  A function variant of the MMR_LOG() macro.  Use the macro instead.
 */
void MMR_PRINTFLIKE(3,4) mmr_log( mmr_logger_t *handle, int level, const char *fmt, ... );

/**
 *  A function variant of the MMR_LOGV() macro.  Use the macro instead.
 */
void mmr_logv( mmr_logger_t *handle, int level, const char *fmt, va_list ap );

#define MMR_LOG_ENABLED( level ) ( (level) <= MMR_LOG_MIN )

/**
 *  Log a message
 *  @param handle
 */
#define MMR_LOGV( handle, level, fmt, ap ) ( MMR_LOG_ENABLED(level)  ? mmr_logv( handle, level, fmt, ap ) : (void)0 )

#if defined(__cplusplus)
 static inline void MMR_PRINTFLIKE(3,4) MMR_LOG( mmr_logger_t *handle, int level, const char *fmt, ... ) {
	if ( MMR_LOG_ENABLED(level) ) {
		va_list ap;
		va_start( ap, fmt );
		mmr_logv( handle, level, fmt, ap );
		va_end( ap );
    }
 }
#else
 #define MMR_LOG( handle, level, ... )     ( MMR_LOG_ENABLED(level) ? mmr_log( handle, level, __VA_ARGS__ ) : (void)0 )
#endif

/**
 *  @brief Fill an error info structure
 *  @details Fill an error info structure with the provided information
 *  @param buf The structure to fill
 *  @param code The error code to store (may be replaced with MMR_ERROR_NO_MEMORY)
 *  @param extra_type A pointer to a type string, or NULL if it's no error or an errno
 *  @param extra_value The extra value
 *  @param extra_text The extra text or NULL
 *  @return buf
 */
extern mmr_error_info_t *mmr_error_fill( mmr_error_info_t *buf, mm_error_code_t code, const char *extra_type, int64_t extra_value, const char *extra_text );

/*@}*/

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mm-renderer/core/public/mm/renderer/logger.h $ $Rev: 680336 $")
#endif
