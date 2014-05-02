/*
 * $QNXLicenseC:  
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
 */
#ifndef _MM_CHARCONVERT2_H_INCLUDED
#define _MM_CHARCONVERT2_H_INCLUDED

#include <stdint.h>
#include <sys/types.h>

__BEGIN_DECLS

/* Multimedia Framework Character Conversion Interface
 * 
 * Version History
 * - 2.0 - Added grouping of strings for better encoding detection.
 *
 */
#define CHAR_CONVERT_VER_2_0		(((2) << 8) | (0))

#define CHAR_CONVERT_DLL		"charconvert_functions"
#define CHAR_CONVERT_MODULE		charconvert_functions

typedef struct convert_group convert_group_t;

/* Bytes-per-character enumeration */
typedef enum {
	CHAR_CONVERT_BPC_UNKNOWN    = 0, // unknown
	CHAR_CONVERT_BPC_SINGLEBYTE = 1, // one byte per character
	CHAR_CONVERT_BPC_MULTIBYTE  = 2, // variable byte encoding, such as utf-8
	CHAR_CONVERT_BPC_WIDE16     = 3, // 16-bit character encoding
	CHAR_CONVERT_BPC_WIDE32     = 4, // 32-bit character encoding
} convert_bpc_t;

/* convert_string() flags */
enum convert_string_flags {
	/* Caller does not want a truncated string.
	 * 
	 * If the library is unable to save the entire converted
	 * string into the buffer size given it is not necessary for
	 * the library save the truncated string into buffer.  This
	 * is provided as a hint to the library and can be ignored.
	 *
	 * Setting this flag does not change the expected return
	 * value of convert_string().
	 */
	CHAR_CONVERT_FLAG_NOTRUNCATE = 0x00000001,

	/* A hint to the library that the fully converted string
	 * length need not be returned if it does not fit in the
	 * provided buffer.
	 *
	 * If the library is unable to save the fully converted
	 * string in the provided buffer the library can return
	 * a value equal to or greater than the "blen" argument
	 * without computing the full length of the converted
	 * string.
	 */
	CHAR_CONVERT_FLAG_NOLENGTH   = 0x00000002,

	/* Caller wants the accurate length of the truncated string, 
	 * rather than the full string, when the buffer is not large 
	 * enough to store the fully converted string.
	 * 
	 * When this flag is set, convert_string() should always return 
	 * the length of the string that it stores in the buffer (or, 
	 * if a string is not stored because CONVERT_NOTRUNCATE is also 
	 * set, the truncated string that it would store if that flag 
	 * weren't set). This value, therefore, will always be smaller 
	 * than the "blen" argument.
	 */
	CHAR_CONVERT_FLAG_DSTLENGTH  = 0x00000004,
};

/* Version and all function pointers are required. */
typedef struct s_charconvert_functions {
	/**
	 * The version implemented by this library.  Should be set to
	 * CHAR_CONVERT_VER_X_Y .
	 */
	uint32_t version;

	/**
	 * Initialize the library.  No other function in the DLL will be called 
	 * unless this function has been called and succeeded.
	 *
	 * @return 0 on success.
	 * @return -1 on error.
	 */
	int (*initialize)(void);

	/**
	 * Change any translation parameters.  Translation parameters apply to
	 * the global library operation.  It is implementation-specific as to
	 * whether these parameters apply to existing groups.
	 *
	 * @param params A string pointer which points to a string whose syntax
	 *               and meaning is library-dependent.
	 * @return 0 on success.
	 * @return -1 on failure; errno should be set.
	 */
	int (*setparams)(const char *params);

	/**
	 * Instruct the library to perform any necessary cleanup.  After
	 * this call the DLL will be unloaded or initialize() will be called.
	 */
	void (*cleanup)(void);

	/**
	 * Create a group object corresponding to a file or other container.
	 * The library should support creating and destroying groups in a
	 * thread-safe way.  It is up to the program using these groups (not
	 * the library) to ensure that access to the groups between threads
	 * is synchronized.
	 * 
	 * @param srctype A string pointer which points to a string that 
	 *                describes the nature of the container that this group
	 *                is created to analyze.
	 * @return on success, pointer to a group object.
	 * @return NULL on failure; errno should be set.
	 */
	convert_group_t * (*newgroup)(const char *srctype);

	/**
	 * Destroy the group object, freeing any associated resources.
	 * All groups will be destroyed before cleanup() is called.
	 * 
	 * @param grp Pointer to the group object to be destroyed.
	 */
	void (*endgroup)(convert_group_t *grp);

	/**
	 * Analyze a source string and add its information to the group object.
	 * 
	 * @param grp Pointer to the group object.
	 * @param data Pointer to the source data.
	 * @param len Number of bytes in source data; if the caller knows the
	 *            string to be null-terminated len will include the
	 *            terminator.
	 * @param bpc Number of bytes per code point in the encoding 
	 *            corresponding to the given hint.
	 * @param hint A string that describes the expected encoding of the
	 *             source string.
	 * @return 0 on success.
	 * @return -1 on error.  The group will be destroyed.
	 */
	int (*detect_string)(convert_group_t *grp, const void *data, size_t len, convert_bpc_t bpc, const char *hint);

	/**
	 * Convert a source string to a null-terminated utf-8 string.
	 *
	 * @param grp Pointer to the group object.
	 * @param src Pointer to the source data.
	 * @param len Number of bytes in source data; if the caller knows the
	 *            string to be null-terminated len should include the 
	 *            terminator.
	 * @param buf Output buffer in which to save the converted string.
	 * @param blen Size of output buffer in bytes.  If the converted
	 *             string will not fit into the buffer including the null
	 *             terminator the default action is to truncate the 
	 *             string on a character boundary.
	 * @param hint A string that describes the expected encoding of the
	 *             source string.
	 * @param flags Flags to monitor the function behaviour.
	 * @return The full length of the translated string, in bytes, 
	 *         not including the null terminator.  This may be greater 
	 *         than the size of the buffer.
	 * @return -1 on error; errno should be set.
	 */
	ssize_t (*convert_string)(convert_group_t *grp, const void *src, size_t len, convert_bpc_t bpc, const char *hint, unsigned char *buf, size_t blen, unsigned flags);
} charconvert_functions_t;


__END_DECLS

#endif /* #ifndef _MM_CHARCONVERT2_H_INCLUDED */

/* __SRCVERSION("charconvert2.h $Rev: 680336 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/support/public/mm/charconvert2.h $ $Rev: 680336 $")
#endif
