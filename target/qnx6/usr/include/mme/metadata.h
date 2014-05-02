/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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


#ifndef _MME_METADATA_H_INCLUDED
#define _MME_METADATA_H_INCLUDED

#ifndef _MME_TYPES_H_INCLUDED
#include <mme/types.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

/*
 * This file contains the metadata API to the MME.
 */

__BEGIN_DECLS


/**
 * Metadata type names. SHOULD BE SOMEWHERE ELSE.
 */
#define	METADATA_TITLE			"title"			/*  METADATA_FORMAT_STRING */
#define	METADATA_ALBUM			"album"			/*  METADATA_FORMAT_STRING */
#define	METADATA_ARTIST			"artist"		/*  METADATA_FORMAT_STRING */
#define	METADATA_GENRE			"genre"			/*  METADATA_FORMAT_STRING */
#define	METADATA_COMPOSER		"composer"		/*  METADATA_FORMAT_STRING */
#define METADATA_PUBLISHER		"publisher"		/*  METADATA_FORMAT_STRING */
#define METADATA_NAME			"name"			/*  METADATA_FORMAT_STRING */
#define METADATA_RELEASE_DATE	"release_date"	/*  METADATA_FORMAT_TM */
#define METADATA_YEAR			"year"			/*  METADATA_FORMAT_UNSIGNED */
#define METADATA_DURATION		"duration"		/*  METADATA_FORMAT_UNSIGNED */
#define METADATA_COMMENT		"comment"		/*  same as 'description' elsewhere; METADATA_FORMAT_STRING */
#define METADATA_TRACK_NUMBER	"track_number"	/*  METADATA_FORMAT_UNSIGNED */
#define METADATA_PROTECTED		"protected"		/*  METADATA_FORMAT_UNSIGNED */

/**
 * The metadata structure.
 */
struct mme_metadata_hdl;
typedef struct mme_metadata_hdl mme_metadata_hdl_t;

/**
 * The formats of metadata.
 */
enum {
	METADATA_FORMAT_INVALID = 0,
	METADATA_FORMAT_DATA,		/*  void */
	METADATA_FORMAT_STRING,		/*  char[] */
	METADATA_FORMAT_TM,			/*  struct tm */
	METADATA_FORMAT_UNSIGNED,	/*  unsigned */
};




/**
 * Get metadata from a file.
 *
 * @param hdl	The MME connection handle
 * @param msid	The ID of the media store the file is on.
 * @param path	The filename, including path on media store. Not including the
 *           	media store's mountpath.
 * @param types	Pointer to comma-separated list of names of metadata to extract.
 * @param flags Flags that affect the behaviour of the call. None are currently defined.
 * @return NULL on failure
 * @return non-NULL on success
 */
mme_metadata_hdl_t *mme_ms_metadata_get(
	mme_hdl_t *hdl,
	uint64_t msid,
	const char *path,
	const char *types,
    uint32_t flags
);


/**
 * Finished with metadata.
 * 
 * @param	metadata	Handle to metadata returned by mme_ms_metadata_get().
 */
void mme_ms_metadata_done(
	mme_metadata_hdl_t *metadata
);

/**
 * Get string format metadata from the metadata handle.
 * 
 * If successful, the pointer is valid until the metadata handled is released.
 * (Release depends on how the handle was created in the first place.)
 * 
 * @param	metadata	Handle to metadata returned by mme_ms_metadata_get().
 * @param	type		The type of metadata to get.
 * @param	flags Flags that affect the behaviour of the call. None are currently defined.
 * @return	NULL if not found; errno is set.
 * @return	non-NULL on success.
 */
const char *mme_metadata_extract_string(
	const mme_metadata_hdl_t *metadata,
	const char *type,
	uint32_t flags
);

/**
 * Get unsigned format metadata from the metadata handle.
 * 
 * If successful, the pointer is valid until the metadata handled is released.
 * (Release depends on how the handle was created in the first place.)
 * 
 * @param	metadata	Handle to metadata returned by mme_ms_metadata_get().
 * @param	type		The type of metadata to get.
 * @param	flags		Flags that affect the behaviour of the call. None are 
 *       	    		currently defined.
 * @param	value		Place to return value. Must not be NULL. 
 * @return	0 on success 
 * @return	-1 on error; errno is set. 
 */
int mme_metadata_extract_unsigned(
	const mme_metadata_hdl_t *metadata,
	const char *type,
	uint32_t flags,
	unsigned *value
);

/**
 * Get data format metadata from the metadata handle.
 * 
 * If successful, the pointer is valid until the metadata handled is released.
 * (Release depends on how the handle was created in the first place.)
 * 
 * @param	metadata	Handle to metadata returned by mme_ms_metadata_get().
 * @param	type		The type of metadata to get.
 * @param	flags		Flags that affect the behaviour of the call. None are currently defined.
 * @param	length		Place to return the length. May be 0 for empty data.
 * @return	NULL if not found; errno is set.
 * @return	non-NULL on success.
 */
const void *mme_metadata_extract_data(
	const mme_metadata_hdl_t *metadata,
	const char *type,
	uint32_t flags,
	size_t *length
);

/** 
 * This function is used to allocate a copy of the specified metadata object. 
 *  
 * This function is necessary if the caller needs to save the returned metadata 
 * blob from an explorer API call, for example, since the returned structure in 
 * the explorer API call uses only a pointer to the metadata, and copying it 
 * does not save the metadata. 
 *  
 * The returned value from this function must be deallocated by the caller using 
 * free(). 
 * 
 * @param metadata	Pointer to metadata to copy.
 * @return non-NULL on success 
 * @return NULL on failure 
 */
mme_metadata_hdl_t *mme_metadata_alloc(const mme_metadata_hdl_t *metadata);

/** 
 * This function is used to query the MME to see what metadata groups might be 
 * extracted from media files, assuming the appropriate multimedia files are 
 * available to the MME. 
 *  
 * The possibly available groups are listed in the return string with spaces 
 * separating the groups. The return value is the length of the string required 
 * to list all groups, regardless of how much is actually returned.
 * 
 * @param hdl		The MME connection handle
 * @param groups	Place to return the groups. May be NULL.
 * @param groups_len	The buffer size available at groups. May be 0.
 * @return -1 on failure. 
 * @return >=0 on success; the length of the string needed to list all groups. 
 */
int mme_metadata_groups_query(mme_hdl_t *hdl, char *groups, size_t groups_len);


__END_DECLS

#endif /* _MME_METADATA_H_INCLUDED */

/* __SRCVERSION("mme_metadata.h $Rev:$"); */

