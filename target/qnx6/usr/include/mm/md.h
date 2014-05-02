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

#ifndef _H_LIB_MD_H_
#define _H_LIB_MD_H_

#include <stdint.h>
#include <unistd.h>
#include "mm/mmsupport.h"
#include "md_errors.h"
#include "sys/strm.h"

/* A keyword used for returning coverart by reference (MDPs will
 * not write the coverart to a file if specified).
 *   ex) md_artwork::image?file=BYREF
 */
#define MD_COVERART_BYREF	"BYREF"


__BEGIN_DECLS


/**
 * This function initializes the library for use.
 *
 * This function loads any dynamically loaded MDPs into the library.
 * 
 * The default path for its configuration is "/etc/mm/mm-md.conf".
 * 
 * Under that there is a directory called "plugins" where plugins are to be
 * configured by providing configuration object.
 * 
 * DLL configuration objects' names must match the name of the plugin. In
 * addition, the configuration object must provide an attribute called
 * "pathname" that specifies where the plug-in's DLL can be found for loading.
 * All other attributes are ignored by the library and may be used by the
 * plug-in itself.
 *
 * @param config	Path to the configuration of the library in PPS. May be NULL.
 * @return 0 on success
 * @return -1 on error; errno is set
 */
int mmmd_init(const char *config);

/**
 * This function terminates the library from use.
 *
 * This function unloads all loaded MDPs from the library.
 *
 * @return 0 on success
 * @return -1 on error
 */
int mmmd_terminate(void);

/**
 * This is a diagnostic function used to list the MDPs successfully loaded
 * and initialized.
 * 
 * @param buffer	Place to put comma-separated list of MDP names (may be NULL)
 * @param buf_len	Length of buffer (may be 0)
 * @return -1 on error
 * @return >=0 on success; length of buffer needed to list all MDPs
 */
ssize_t mmmd_mdps_list(char *buffer, size_t buf_len);

/**
 * Session handle. Opaque to callers.
 */
struct mmmd_hdl;
typedef struct mmmd_hdl mmmd_hdl_t;

/**
 * This function opens a metadata extraction session.
 *
 * @param mediastore URL or media store mount path.
 * @param flags  Session control flags; values to be determined.
 * @return non-NULL on success
 * @return NULL on failure; errno is set; values to be determined.
 */
mmmd_hdl_t *mmmd_session_open(const char *mediastore, uint32_t flags);

/**
 * This function sets parameters on a session.
 *
 * NOTE: For now, once they are set, they cannot be unset or changed.
 * Further, they will be applied only to any MDPs for which sessions are not
 * already created. Therefore, this call should be made before any mmmd_get()
 * call.
 *
 * @param hdl    Pointer to session to set parameters on
 * @param dict   Dictionary of key-value pairs of parameters.
 * @return 0 on success
 * @return -1 on failure
 */
int mmmd_session_params_set(mmmd_hdl_t *hdl, const strm_dict_t *dict);

/**
 * This function closes a metadata extraction session opened with 
 * mmmd_session_open().
 *
 * @param hdl    Pointer to session to close.
 * @return 0 on success
 * @return -1 on failure
 */
int mmmd_session_close(mmmd_hdl_t *hdl);

/**
 * Structure that describes errors during session use.
 * 
 * This structure may evolve over time.
 */
typedef struct mmmd_error_info {
	mmmd_errcode_t  code;	/**< Numeric code for the error. */
	int64_t extended_code;	/**< Extended numeric error code. */
	char extended_type[16];	/**< Extended error type string for above code. */
	char extended_msg[256];	/**< Extended error message. */
} mmmd_error_info_t;

/**
 * This function returns information that describes the last error
 * that occurred when using a session.
 *
 * @param hdl	Pointer to session error occured on.
 * @return Pointer to error information structure
 */ 
const mmmd_error_info_t* mmmd_error_info(mmmd_hdl_t *hdl);

/**
 * Old, deprecated error structure, kept for backward compatibility.
 */
typedef struct mmmd_error {
	mmmd_errcode_t  code;	/**< Numeric code for the error. */
} mmmd_error_t;

/**
 * ---- NOW DEPRECATED IN FAVOUR OF mmmd_error_info() ----
 * This function returns information that describes the last error
 * that occurred when using a session.
 *
 * @param hdl	Pointer to session error occured on.
 * @param error	Place to put the error.
 */ 
void mmmd_last_error(mmmd_hdl_t *hdl, mmmd_error_t *error) __attribute__((__deprecated__));

/**
 * This function is used to get metadata for the specified types on the
 * specified item.
 *
 * Initially, it is assumed that the item string is to an item on the media
 * store the session was opened on.
 * 
 * The returned pointer should be de-allocated by the caller using free()
 * when they are done with it. It is non-NULL only if the return value is
 * greater than 0.
 *
 * @param hdl    Pointer to session opened on media store.
 * @param item   URL or absolute path to item for which metadata is wanted.
 * @param types  Description of metadata types for which metadata is wanted.
 * @param source Specification of the source of metadata; NULL to indicate any
 *               or all sources.
 * @param count  The number of desired matches.
 *               If source is non-NULL, this value is ignored and only the
 *               highest rated response from that source is returned.
 *               If source is NULL and count is 0, all responses are collated
 *               to return the highest rated response.
 *               If source is NULL and count is non-zero, that many results are
 *               returned, starting with the highest rated. No collation is
 *               performed.
 * @param md     Place to return the metadata.
 * @return -1 on error
 * @return 0 on failure to get any metadata but no errors occurred
 * @return >0 on success; the number of responses
 *               (is <= count unless count == 0 or source != NULL)
 */
int mmmd_get(mmmd_hdl_t *hdl, const char *item, const char *types,
			 const char *source, uint32_t count, char **md);

/*******************************************************************************
 *
 * Flags control interface.
 *
 * This interface is for setting control flags that are normally used for
 * diagnostic purposes only.
 */

typedef enum {
	MMMD_FLAG_EMIT_TIMING_LOGS = 0x01	/**< Tell library to emit timing logs. */
} mmmd_flags_t;

/** 
 * This function is used to set control logs for the library.
 * 
 * @param new_flags	New flags value
 * @return old flags value.
 */
mmmd_flags_t mmmd_flags_set(mmmd_flags_t new_flags);

__END_DECLS

#endif /* _H_LIB_MD_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/md/lib/public/mm/md.h $ $Rev: 703226 $")
#endif
