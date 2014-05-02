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

#ifndef _H_LIB_MD_ERRORS_H_
#define _H_LIB_MD_ERRORS_H_

/**
 * The enumerated result codes.
 */
typedef enum mmmd_errcode {
	MMMD_ERR_NONE = 0,
	MMMD_ERR_OTHER,					/**< An error occured that's not listed here. */
	MMMD_ERR_NO_MDPS,				/**< There are no metadata plug-ins. */
	MMMD_ERR_NOT_SUPPORTED,			/**< The request is not supported. */
	MMMD_ERR_MALFORMED_REQUEST,		/**< The request is badly formed. */
	MMMD_ERR_NO_PARSERS,			/**< No parsers found for the request. */
	MMMD_ERR_CALLDEPTH_EXCEEDED,	/**< The derived metadata call depth was exceeded. */
	MMMD_ERR_NO_MEMORY,				/**< No memory available. */
	MMMD_ERR_CANT_OPEN_FILE,		/**< Unable to open file. */
	MMMD_ERR_CANT_READ_FILE,		/**< Unable to read from file. */
	MMMD_ERR_CANT_RECONFIGURE,		/**< Configuration already set. */

} mmmd_errcode_t;

/** 
 * This function returns an english language phrase version of the specified
 * error code.
 * 
 * @param errcode	String wanted.
 * @return non-NULL always
 */
const char *mmmd_error_str(mmmd_errcode_t errcode);


#endif /* _H_LIB_MD_ERRORS_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/md/lib/public/mm/md_errors.h $ $Rev: 680764 $")
#endif
