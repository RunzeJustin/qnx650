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

#ifndef _H_MMPLAYLIST_H
#define _H_MMPLAYLIST_H

#include <stdint.h>
#include <unistd.h>
#include "mm/mmsupport.h"

/** 
 * @file mmplaylist.h
 * Defines data types for session handles and for storing playlist formats or session properties,
 * as well as enumerations used for some function parameter or return types.
 * Defines functions for managing playlist sessions, navigating and retrieving information in playlists,
 * and retrieving error information.
 */

/**
 * This define is here for backwards compatibility, any code that uses the
 * old 'mmplaylist_buffer_too_small' error code will work properly with its
 * replacement, 'mmplaylist_entry_too_large'.
 */
#define mmplaylist_buffer_too_small	mmplaylist_entry_too_large

__BEGIN_DECLS

/**
 * The data type for a playlist session handle.
 */
typedef struct mmplaylist mmplaylist_t;

/**
 * Directives for seeking to playlist positions.
 */
typedef enum {
	MMPLAYLIST_SEEK_CUR = 0, ///< A position relative to the current position
	MMPLAYLIST_SEEK_ABS      ///< An absolute position in the playlist
} mmplaylist_seek_offset_t;

/**
 * Types of validation that can be performed on playlist entries.
 * This list might be extended at a future date.
 */
typedef enum {
	MMPLAYLIST_ENTRY_RAW_ENC = 0, ///< Return raw playlist entries to the caller
	MMPLAYLIST_ENTRY_UTF8_ENC,    ///< Return UTF-8-encoded entries to the caller
	MMPLAYLIST_ENTRY_VALIDATE,    ///< Use a helper function to validate the entry before returning it to the caller
} mmplaylist_validation_mode_t;

/**
 * Properties of retrieved playlist entries.
 */
typedef enum {
	MMPLAYLIST_ENTRY_RESOLVED = 0,          ///< The resolved entry is valid (no further processing is required)
	MMPLAYLIST_ENTRY_NOT_LOCATED = 0x01,    ///< The entry's track file wasn't found
	MMPLAYLIST_ENTRY_NOT_CONVERTED = 0x02,  ///< The entry couldn't be converted to the desired encoding
} mmplaylist_entry_validated_t;

/**
 * This data type specifies the prototype for the validation function.
 * See the mmplaylist_entry_next_get() description for an explanation of playlist entry validation.
 *
 * @param filename	The name being proposed as resolved.
 * @param cbk_data	Data for the callback (validation) function.
 * @return An enumerated value indicating the properties of the retrieved entry
 */
typedef mmplaylist_entry_validated_t mmplaylist_validation_fn_t(char *filename, void *cbk_data);

/**
 * Error information.
 */
typedef struct {
	int error_code; ///< A numeric code identifying the error that occurred
} mmplaylist_error_info_t;

/**
 * This structure is used to return the properties of a playlist session to the client application.
 * The operation to retrieve this information is always fast. By reading the properties returned, 
 * the client can choose to call certain library functions based on whether the corresponding 
 * operation is fast.
 */
typedef struct mmplaylist_props {
	int num_entries_get_fast; ///< 1 if the number of playlist entries can be retrieved quickly;
                              ///< 0 if it can't be.
	int seek_fast;            ///< 1 if the playlist allows the client to quickly jump to an
                              ///< arbitrary position; 0 if it doesn't.
	int rewind_fast;          ///< 1 if the playlist allows the client to quickly rewind to the
                              ///< beginning of the playlist; 0 if it doesn't.
} mmplaylist_props_t;

/**
 * This structure is used to return the list of supported playlist formats to the client application.
 */
typedef struct mmplaylist_fmt_list {
	int     num_entries;     ///< The number of extensions/formats that are supported
	char  **playlist_fmtstr; ///< An array of strings containing the supported playlist file extensions
} mmplaylist_fmt_list_t;

/**
 * This data structure is used to return a playlist entry to the client application.
 */
typedef struct mmplaylist_entry {
	uint32_t    props;  ///< The properties of the entry
	char        name[]; ///< The extracted entry
} mmplaylist_entry_t;


/**
 * @brief Initialize the library
 *
 * @details Initialize the playlist library. This function loads the character converter library, 
 * parses the libmmplaylist configuration file, and tries to load each PLP named in the 
 * configuration file.
 *
 * You must call this function once, and it must be the first function you call.
 * Calling it multiple times will result in unpredictable behaviour.
 *
 * @param config The path of the configuration file to use. 
 *               Set this parameter to NULL to make the library use the file specified in the
 *               MM_PLAYLIST environment variable or if that variable isn't defined, 
 *               the default file.
 *
 * @return 0 (mmplaylist_ok) on success
 * @return A nonzero mmplaylist_rc error code on failure
 */
int mmplaylist_init(const char *config);

/**
 * @brief Terminate the library
 *
 * @details Terminate the playlist library from use.
 * You must call this function once, and it must be the last function you call.
 * This function unloads all PLPs from the library.
 *
 * @param (None)
 *
 * @return 0 (mmplaylist_ok) on success
 *         A nonzero mmplaylist_rc error code on failure
 */
int mmplaylist_terminate(void);

/**
 * @brief List available playlist plugins
 *
 * @details List available playlist plugins (PLPs).
 * This diagnostic function returns a list of all PLPs that were successfully loaded and 
 * initialized.
 *
 * @param buffer  A pointer to memory for storing a comma-separated list of PLP names.
 *                Set this pointer to NULL to make libmmplaylist return the buffer size required
 *                for holding all PLP names. Then, allocate the right amount of memory for the 
 *                buffer and call mmplaylist_plps_list() a second time, passing in a pointer to 
 *                the buffer to make libmmplaylist populate it with the list of PLP names.
 * @param buf_len Length of buffer (can be 0)
 *
 * @return A nonnegative value on success; this value indicates the buffer length needed to list
 *         all available plugins
 * @return -1 on error
 */
ssize_t mmplaylist_plps_list(char *buffer, size_t buf_len);

/**
 * @brief Open a session on a playlist
 *
 * @details Open a session on a playlist.
 * This function creates and returns a handle to represent the new playlist session.
 * Internally, the function queries the available plugins to identify which ones
 * support this playlist format. If multiple plugins support the format, the highest-ranked one
 * is selected for use with this session.
 *
 * @param base_name A string containing the base directory for the mediastore that contains
 *                  this playlist.
 * @param playlist_name A string that contains the full path to the playlist. This path can be an
 *                      absolute filepath or a URL.
 * @param validation_mode The method that libmmplaylist must use to resolve the playlist entries.
 *                        See mmplaylist_validation_mode_t for the list of acceptable values.
 *
 * Here, validation means identifying a potential target file corresponding to a playlist entry. 
 * The default validation function used is stat() but the caller can name another function to use.
 *
 * @param validate_fn The callback function to use for validating playlist entries.
 *                    This optional parameter can be set to NULL, in which case the library uses 
 *                    stat() to validate entries. Also, entry validation is done only when  
 *                    validation_mode is set to MMPLAYLIST_ENTRY_VALIDATE.
 * @param cbk_data Data for the callback function. This data gets passed unmodified to the 
 *                 validation function. The data can be NULL.
 *
 * @return A handle to a playlist, if the playlist is supported
 * @return NULL on error
 */
mmplaylist_t *mmplaylist_open(const char *base_name,
							  const char *playlist_name,
							  mmplaylist_validation_mode_t validation_mode,
							  mmplaylist_validation_fn_t *validate_fn,
							  void *cbk_data);

/**
 * @brief Close a playlist session
 *
 * @details Close an active playlist session.
 * If an error occurs, the function returns an error code but the session handle still becomes
 * invalid. The application should not, under any circumstances, use the handle after calling this
 * function.
 *
 * @param pl A valid session handle
 *
 * @return 0 (mmplaylist_ok) on success
 * @return A nonzero mmplaylist_rc error code on failure
 */
int mmplaylist_close(mmplaylist_t *pl);

/**
 * @brief Get information on the last error
 *
 * @details Get information on the last error that occurred in an API call that used this session
 * handle. Note that reading the last error value clears it as well.
 *
 * @param pl A valid session handle
 * @param error_info A pointer to a structure for storing the error information
 */
void mmplaylist_last_error_get(mmplaylist_t *pl, mmplaylist_error_info_t *error_info);

/**
 * @brief Get properties of a playlist session
 *
 * @details Get properties of a playlist session.
 * This function lists the properties of the session in a data structure that it returns to 
 * the caller. Applications can read these properties to learn which operations are fast in 
 * the current session and then provide a better user experience by avoiding slow operations.
 *
 * The function allocates memory for the structure that it returns.
 * The caller should free this memory using free().
 *
 * @param pl A valid session handle
 * @return A pointer to an mmplaylist_props_t structure, on success
 * @return NULL on failure (use mmplaylist_last_error_get() to get error information)
 */
mmplaylist_props_t *mmplaylist_props_get(mmplaylist_t *pl);

/**
 * @brief Get the number of entries in a playlist
 *
 * @details Get the number of entries in a playlist.
 * This operation can be very expensive, so the application should first check 
 * the num_entries_get_fast field in the mmplaylist_props_t structure to determine whether this
 * operation can be completed quickly or not.
 *
 * Note that calling this function on an empty playlist returns a value of 0.
 *
 * @param pl A valid session handle
 *
 * @return A nonegative value indicating the number of playlist entries
 * @return -1 on error (use mmplaylist_last_error_get() to get error information)
 */
int mmplaylist_num_entries_get(mmplaylist_t *pl);

/**
 * @brief Get the position of the current playlist entry
 *
 * @param pl A valid session handle
 *
 * @return A nonnegative value for the position of the current entry, on success
 * @return -1 on error (use mmplaylist_last_error_get() to get error information).
 *         When the current position is at the end of the playlist, this function returns -1
 *         and sets an error code of mmplaylist_end_of_playlist.
 */
int mmplaylist_current_pos_get(mmplaylist_t *pl);

/**
 * @brief Jump to a position in the playlist
 *
 * @details Jump to a position in the playlist.
 * This operation can be very expensive, so the application should first check the value of the
 * seek_fast field in the mmplaylist_props_t structure to determine whether this operation can be
 * completed quickly or not.
 *
 * @param pl A valid session handle
 * @param new_pos The new position in the playlist to jump to. 
 *                Negative numbers are allowed for moving backwards.
 * @param whence The reference point for the new position. See mmplaylist_seek_offset_t for
 *               the list of acceptable values.
 *
 * @return 0 on success
 *         -1 on error (use mmplaylist_last_error_get() to get error information)
 */
int mmplaylist_current_pos_set(mmplaylist_t *pl, int new_pos,
							   mmplaylist_seek_offset_t whence);

/**
 * @brief Get the next entry from a playlist
 *
 * @details Get the next entry from a playlist.
 * The data structure filled in by this function contains the next entry from the playlist file and
 * a flag field that describes the properties of this entry.
 *
 * When an application requests the next playlist entry, the plugin:
 * 1. Retrieves the next entry from the playlist file
 * 2. Identifies and modifies the character encoding of the entry, based on the preferences given
 *    when the playlist session was created
 * 3. If necessary, validates the entry to identify its possible track file by using either the
 *    specified callback or the stat() function. See mmplaylist_entry_validated_t for 
 *    the list of properties that the validation function can set.
 *
 * This last step repeats until either the callback determines that the entry is valid or
 * the playlist manager has iterated through the character conversion and/or validation routines.
 * At this point, the function returns the raw entry to the caller.
 *
 * The caller must use mmplaylist_entry_release() to free the memory for a playlist entry when 
 * they're done with it. They must not free the memory themselves; doing so will result in 
 * unpredictable behaviour.
 *
 * @param pl A valid session handle
 * @param entry	A pointer for storing a reference to the entry pointer defined by this function
 *
 * @return 1 on success (i.e., the entry was retrieved)
 * @return 0 on end of playlist
 * @return -1 on error (use mmplaylist_last_error_get() to get error information)
*/
int mmplaylist_entry_next_get(mmplaylist_t *pl, mmplaylist_entry_t **entry);

/**
 * @brief Release memory for a playlist entry
 *
 * @details Release memory for a playlist entry. This memory was allocated in an earlier
 * mmplaylist_entry_next_get() call.
 *
 * @param pl A valid session handle
 * @param entry A pointer to the entry whose memory is being released (freed)
 *
 * @return 0 if the memory was freed properly
 *         -1 on error (use mmplaylist_last_error_get() to get error information)
 */
int mmplaylist_entry_release(mmplaylist_t *pl, mmplaylist_entry_t *entry);

/**
 * @brief Get the list of supported playlist formats 
 *
 * @details Get the list of playlist formats supported by the library.
 * The data structure filled in by this function contains the number of supported playlist types and 
 * a pointer to an array of strings containing the file extensions of the supported playlist types.
 * 
 * The function allocates memory for the data structure and returns a pointer to it.
 * The caller must use mmplaylist_supported_fmts_release() to release the memory when they're done 
 * with it. They must not modify or free the memory themselves; doing so will result in 
 * unpredictable behavior.
 *
 * @param (None)
 * @return A pointer to an mmplaylist_fmt_list_t structure on success
 *         NULL on error (use mmplaylist_last_error_get() to get error information)
 */
mmplaylist_fmt_list_t *mmplaylist_supported_fmts_get(void);

/**
 * @brief Release memory for the list of supported playlist formats
 *
 * @details Release memory for the list of playlist formats supported by the library.
 * This list was returned by an earlier mmplaylist_supported_fmts_get() call.
 *
 * @param extn_list The list of supported playlist formats
 * @return 0 if the memory was freed properly
 *         -1 on error (use mmplaylist_last_error_get() to get error information)
 */
int mmplaylist_supported_fmts_release(mmplaylist_fmt_list_t *extn_list);

/**
 * Enumerated codes for playlist session errors
 */
typedef enum {
	mmplaylist_ok = 0,                  ///< The operation was successful
	mmplaylist_err,                     ///< An unexpected error occurred (e.g., initialization failed or a plugin couldn't
                                        ///< complete the requested operation)
	mmplaylist_no_memory,               ///< The library couldn't allocate enough memory to store the requested information
	mmplaylist_char_conv_failure,       ///< The character converter service failed
	mmplaylist_entry_conf_failure,      ///< An error occured while converting a playlist entry to the requested encoding
	mmplaylist_entry_validation_failure,///< An error occured while validating a playlist entry 
	mmplaylist_config_error,            ///< The library couldn't read the configuration file or a plugin failed to load
	mmplaylist_entry_too_large,         ///< The entry was too large for the library to process, so the caller should skip
                                        ///< this entry and get the next one
	mmplaylist_read_error,              ///< A plugin encountered an error while parsing the next entry 
	mmplaylist_end_of_playlist,         ///< The end of the playlist was reached
	mmplaylist_position_too_short,      ///< The requested new position is before the beginning of the playlist
	mmplaylist_position_too_long,       ///< The requested new position is after the end of the playlist
	mmplaylist_file_system_error,       ///< An error occurred while parsing the playlist file
	mmplaylist_invalid_input,           ///< An invalid argument was given
	mmplaylist_session_invalid          ///< The playlist session is invalid
} mmplaylist_rc;

__END_DECLS

#endif /* _H_MMPLAYLIST_H */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmplaylist/lib/public/mm/mmplaylist.h $ $Rev: 733565 $")
#endif
