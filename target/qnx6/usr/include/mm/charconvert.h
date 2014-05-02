/*
 * $QNXLicenseC:  
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
 */
#ifndef _MM_CHARCONVERT_H_INCLUDED
#define _MM_CHARCONVERT_H_INCLUDED

__BEGIN_DECLS

/**
 * DEPRECATED
 *
 * The interface provided here has been deprecated.  Please see the
 * header file <mm/charconvert2.h> for the new interface.
 */


#define CHAR_CONVERT_FUNCTION_NAME ("convert_to_utf8")
#define CHAR_CONVERT_SETUP_FUNCTION_NAME ("convert_setup")

/**
 * Function prototype for external DLL that can provide character conversion
 * routine.
 * 
 * @param in_str The input string
 * @param out_str The output string in UTF-8 encoding
 * @param in_size The input string size in bytes
 * @param out_size The output string size in bytes
 * @param in_str_encoding_hint In situations where the string's encoding is
 *        indicated, the MME will pass along with the request the encoding format
 *        of the in_str.  See CHAR_FORMAT_*.
 * @return -1 on error.
 */
typedef int f_external_convert_utf8_t(const unsigned char *in_str,
									   unsigned char *out_str,
									   uint16_t in_size, uint16_t out_size,
									   const char *in_str_encoding_hint);

typedef f_external_convert_utf8_t *external_convert_utf8_t;
extern f_external_convert_utf8_t convert_to_utf8; /* Function defined in the DLL */

/**
 * The MME's mme_charconvert_setup( ) API passes through to this interface where
 * it can pass into the charconvert DLL the default encoding string, and 
 * the option to allow detection of string encoding.
 * 
 * This function can be called at any time, the MME provides no locking mechanism
 * and therefore the DLL should be careful about its own variables.
 * 
 * @param default_encoding The format of this string is defined by the implementor of
 *        the charconvert DLL.  This can include any information of interest to the DLL
 * @param allow_detection 0 = do not allow detection, 1 = allow detection
 * @return -1 on error, 0 on success.
 */
typedef int f_external_convert_setup_t(const char *default_encoding, int allow_detection);
typedef f_external_convert_setup_t *external_convert_setup_t;
extern f_external_convert_setup_t convert_setup; /* Function defined in the DLL */


/**
 * This is a list of currently defined input formats
 */
#define CHAR_FORMAT_ISO8859_1  ("iso8859-1")
#define CHAR_FORMAT_ISO8859_2  ("iso8859-2")
#define CHAR_FORMAT_UTF16BE  ("utf16be")
#define CHAR_FORMAT_UTF16LE  ("utf16le")
#define CHAR_FORMAT_UTF16    ("utf16")
#define CHAR_FORMAT_SHIFTJIS ("shift_jis")
#define CHAR_FORMAT_KOI8U    ("koi8-u")
#define CHAR_FORMAT_ISO2022_CN  ("iso2022-cn")
#define CHAR_FORMAT_WINDOWS_1251  ("windows-1251")
#define CHAR_FORMAT_UTF8     ("utf8")


__END_DECLS

#endif /* #ifndef _MM_CHARCONVERT_H_INCLUDED */

/* __SRCVERSION("charconvert.h $Rev: 680764 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/support/public/mm/charconvert.h $ $Rev: 680764 $")
#endif
