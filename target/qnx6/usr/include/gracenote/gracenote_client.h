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


#ifndef GRACENOTE_CLIENT_H_
#define GRACENOTE_CLIENT_H_

#include <inttypes.h>
#include <stdbool.h>
#include <sys/slogcodes.h>
#include <sys/slog.h>

/* Some logging macros */
#define GNC_INFO( verbose_level, format, args... ) 									\
	do { 														\
		if ( verbose >= verbose_level ) {									\
			gnc_log( _SLOG_INFO, __PRETTY_FUNCTION__, __LINE__, verbose_level, format, ##args );		\
		}													\
	 } while(0)
#define GNC_WARNING( verbose_level, format, args... ) 									\
	do { 														\
		if ( verbose >= verbose_level ) {									\
			gnc_log( _SLOG_WARNING, __PRETTY_FUNCTION__, __LINE__, verbose_level, format, ##args );	\
		}													\
	 } while(0)
#define GNC_ERROR( format, args... ) 											\
	do { 														\
		gnc_log( _SLOG_WARNING, __PRETTY_FUNCTION__, __LINE__, 0, format, ##args );				\
	 } while(0)


#define GNS_DEFAULT_MOUNTPATH			"/dev/gracenote"
#define GNS_TAGID_RESERVED_KEY			"reserved_album_tagid"
#define GNC_DATABASE_UNIQUE_ID 			"gracenote_plp"
#define GNC_MAX_COLLECTIONS			1024
#define GNC_PLAYLIST_MAX_RESULTS		30

/* Playlist options */
#define GNC_PLAYLIST_SEED_TYPE_ENTRYDATA	0
#define GNC_PLAYLIST_SEED_TYPE_ARTIST		1
#define GNC_PLAYLIST_SEED_TYPE_ALBUM		2

#define GNC_LOG_LEVEL				2

/* Album art options */
#define GNS_ALBUMART_FORMAT_UNKNOWN		0
#define GNS_ALBUMART_FORMAT_JPEG		1

#define GNS_ALBUMART_DIMENSION_UNKNOWN		0	/* Unknown */
#define GNS_ALBUMART_DIMENSION_THUMB		1	/* Approx 75x75 */
#define GNS_ALBUMART_DIMENSION_SMALL		2	/* Approx 170x170 */
#define GNS_ALBUMART_DIMENSION_MEDIUM		3	/* Approx 450x450 */
#define GNS_ALBUMART_DIMENSION_300		6	/* Approx 300x300 */

#define GNS_ALBUMART_PIXELS_UNKNOWN		0	/* Unknown */
#define GNS_ALBUMART_PIXELS_THUMB		75	/* Approx. 75x75 pixels */
#define GNS_ALBUMART_PIXELS_SMALL		170	/* Approx. 170x170 pixels */
#define GNS_ALBUMART_PIXELS_MEDIUM		450	/* Approx. 450x450 pixels */
#define GNS_ALBUMART_PIXELS_300			300	/* Approx. 300x300 pixels */

#define GNS_ALBUMART_ODL_SOURCE_UNKNOWN		0	/* Coverart location is unknown */
#define GNS_ALBUMART_ODL_SOURCE_FILE		1	/* Coverart is coming from a file */
#define GNS_ALBUMART_ODL_SOURCE_URL		2	/* Coverart is coming from a URL */
#define GNS_ALBUMART_ODL_SOURCE_PACKAGE		3	/* Coverart is inline with a Package */

#define GNS_ALBUMART_MATCH_UNKNOWN		0	/* Coverart is unknown (online) */
#define GNS_ALBUMART_MATCH_ALBUM		1	/* Coverart is for the album */
#define GNS_ALBUMART_MATCH_ARTIST		2	/* Coverart is for the artist */
#define GNS_ALBUMART_MATCH_GENRE		3	/* Coverart is for the genre */

/* Fingerprinting source types */
#define GNS_FPT_ALG_UNKNONWN			0	/* Unknown Algorithm */
#define GNS_FPT_ALG_FILE_FIXED			1	/* Fixed File */
#define GNS_FTP_ALG_FILE_FLOAT			2	/* Floating File */
#define GNS_FTP_ALG_STREAM_LOW			3	/* Low quality stream ( Microphone ) 3 second block */
#define GNS_FTP_ALG_STREAM_MED			4	/* Medium quality stream ( FM/MP3 ) 3 second block */
#define GNS_FTP_ALG_STREAM_HIGH			5	/* High quality stream ( FM/MP3 ) 6 second  block */

/* Fingerprint encoding types */
#define GNS_FPT_ENC_UNKNOWN			0	/* Unknown Encoding */
#define GNS_FPT_ENC_PCM8			1	/* PCM8bit encoding */
#define GNS_FPT_ENC_PCM16			2	/* PCM16bit encoding */
#define GNS_FPT_ENC_ALAW			3	/* A-law encoding */
#define GNS_FPT_ENC_ULAW			4	/* u-law encoding */

/* Fingerprint types */
#define GNS_FINGERPRINT_RAW_PCM			0	/* PCM data which needs to be hashed */
#define GNS_FINGERPRINT_PRE_ENCODED		1	/* Pre-encoded fingerprint */

/* On-Demand Lookup types */
#define GNS_ODL_UPDATE_SOURCE_UNKNOWN		0	/* Package source is unknown */
#define GNS_ODL_UPDATE_SOURCE_FILE		1	/* Package source is from a file */
#define GNS_ODL_UPDATE_SOURCE_URL		2	/* Package source is from a URL */


/** 
 * Potential flags to set when requesting
 * data from the server. 
 */
#define GNS_METADATA_ALBUM			0x00000001	/* Return album level metadata 	   		*/
#define GNS_METADATA_TRACK			0x00000002	/* Return track level metadata	   		*/
#define GNS_METADATA_MATCHED_TRACK		0x00000004	/* Return only matched track metadata  		*/
#define GNS_METADATA_FIRST_ALBUM_TRACK		0x00000008	/* Return full track level metadata for 
							     	   first album and only album metadata 
							     	   for subsequent albums 			*/
#define GNS_METADATA_NORMALIZED			0x00000010	/* Return normalized metadata during a textid
							     	   lookup from the DBS plugin			*/
#define GNS_METADATA_ALBUMID			0x00000020	/* Return an albumid even if it's not
							   	   configured in the gracenote.conf for 
							   	   quick lookups.				*/

#define GNS_PHONETIC_DATA_ALBUM			0x00000040	/* Return album level phonetic data  		*/
#define GNS_PHONETIC_DATA_TRACK			0x00000080	/* Return track level phonetic data  		*/
#define GNS_PHONETIC_DATA_MATCHED_TRACK		0x00000100  	/* Return only matched track phonetic data 	*/
#define GNS_PHONETIC_DATA_FIRST_ALBUM_TRACK	0x00000200  	/* Return full track level phonetic data for
							     	   first album and only album phonetic data 
							     	   for subsequent albums 			*/

#define GNS_COVERART_INFO			0x00000400	/* Return coverart info only 			*/
#define GNS_COVERART_ALL			0x00000800	/* Return actual coverart 		 	*/

/**
 * Miscellaneous Gracenote specific
 * lookup options
 */
#define GNS_LOOKUP_BEST_RESULT			0x0010000	/* Return only the best result from an
								   online lookup				*/

/**
 * The flags are used as control flags for
 * targetting specific lookup methods.
 */
#define GNS_LOOKUP_LOCAL_ODL_CACHE		0x01000000	/* Perform a lookup in the ODL cache		*/
#define GNS_LOOKUP_LOCAL_TEXTID			0x02000000	/* Perform a local textid lookup		*/
#define GNS_LOOKUP_LOCAL_TOC			0x04000000	/* Perform a local TOC lookup			*/
#define GNS_LOOKUP_ONLINE_TOC			0x08000000	/* Perform a TOC lookup online			*/
#define GNS_LOOKUP_ONLINE_MUSICID		0x10000000	/* Perform an online musicid lookup		*/
#define GNS_LOOKUP_LOCAL_AND_LUCACHE		0x20000000	/* Perform a TOC lookup both local and in cache */

/**
 * Flags used for selecting version info
 * return data.
 */
#define GNS_VERSION_INFO_BUILD_DATE		1	/* Return build date				*/
#define GNS_VERSION_INFO_EMMS			2	/* Return emmslib version			*/
#define GNS_VERSION_INFO_DB_LFS			3	/* Return installed gracenote db lfs version	*/
#define GNS_VERSION_INFO_DB_BASE		4	/* Return installed gracenote db base version	*/
#define GNS_VERSION_INFO_DB_DATE		5	/* Return installed gracenote db snapshot date	*/
#define GNS_VERSION_INFO_DB_UPDATE_COUNT	6	/* Return number of incremental updates applied
							   to installed gracenote db			*/
#define GNS_VERSION_INFO_DB_INC_UPDATE		7	/* Return revision number of specified
							   incremental update applied to installed db	*/

/**
 * Some masks encompassing all the lookup
 * options grouped together and all the return
 * options grouped together.
 */
#define GNS_LOOKUP_LOCATION_ALL			(GNS_LOOKUP_LOCAL_ODL_CACHE	 | GNS_LOOKUP_LOCAL_TEXTID 	       | \
						 GNS_LOOKUP_LOCAL_TOC		 | GNS_LOOKUP_ONLINE_TOC   	       | \
						 GNS_LOOKUP_ONLINE_MUSICID	 | GNS_LOOKUP_LOCAL_AND_LUCACHE)

#define GNS_RETURN_DATA_ALL			(GNS_METADATA_ALBUM 	   	 | GNS_METADATA_TRACK 	     	       | \
						 GNS_METADATA_MATCHED_TRACK	 | GNS_METADATA_FIRST_ALBUM_TRACK      | \
						 GNS_METADATA_NORMALIZED	 | GNS_METADATA_ALBUMID		       | \
						 GNS_PHONETIC_DATA_ALBUM    	 | GNS_PHONETIC_DATA_TRACK	       | \
						 GNS_PHONETIC_DATA_MATCHED_TRACK | GNS_PHONETIC_DATA_FIRST_ALBUM_TRACK | \
						 GNS_COVERART_INFO		 | GNS_COVERART_ALL)

__BEGIN_DECLS


struct _gns_hdl;
typedef struct _gns_hdl gns_hdl_t;

typedef struct gns_playlist_fields {
	uint64_t	fid;
	char		*filename;
} gns_playlist_fields_t;

typedef struct gns_playlist {
	uint32_t		num_fields;
	gns_playlist_fields_t	*field;
} gns_playlist_t;

typedef struct gns_collection_list {
	uint32_t		num_collections;
	uint32_t		*collection;
} gns_collection_list_t;

typedef struct gns_metadata_string {
	char	*key;
	char	*value;
} gns_metadata_string_t;

typedef struct gns_work_metadata {
	uint32_t		num_strings;
	gns_metadata_string_t	*string;
} gns_work_metadata_t;

typedef struct gns_track_metadata {
	uint32_t		num_works;
	uint32_t		num_strings;
	gns_metadata_string_t	*string;
	gns_work_metadata_t	*work;
} gns_track_metadata_t;

typedef struct gns_album_metadata {
	uint32_t		num_tracks;
	uint32_t		num_strings;
	gns_metadata_string_t	*string;
	gns_track_metadata_t	*track;
} gns_album_metadata_t;

typedef struct gns_generic_metadata {
	uint32_t		num_strings;
	gns_metadata_string_t	string[];
} gns_generic_metadata_t;

typedef struct gns_transcript {
	uint32_t	correct_pronunciation;
	char		*data;
} gns_transcript_t;

typedef struct gns_transcript_array {
	uint32_t		num_transcripts;
	char			*language;
	char			*orthography;
	gns_transcript_t	*transcript;
} gns_transcript_array_t;

typedef struct gns_phonetic_data_t {
	uint32_t			num_elements;
	int32_t				type;
	char				*key;
	gns_transcript_array_t		*array;
} gns_phonetic_data_t;

typedef struct gns_genre_representation {
	uint32_t		num_phonemes;
	gns_phonetic_data_t	*phoneme;
} gns_genre_representation_t;

typedef struct gns_work_representation {
	uint32_t		num_phonemes;
	gns_phonetic_data_t	*phoneme;
} gns_work_representation_t;

typedef struct gns_track_representation {
	uint32_t			num_phonemes;
	uint32_t			num_works;
	gns_phonetic_data_t		*phoneme;
	gns_work_representation_t	*work_representation;
	gns_genre_representation_t	*genre_representation;
} gns_track_representation_t;

typedef struct gns_album_representation {
	uint32_t			num_phonemes;
	uint32_t			num_tracks;
	gns_phonetic_data_t		*phoneme;
	gns_track_representation_t	*track_representation;
	gns_genre_representation_t	*genre_representation;
} gns_album_representation_t;

typedef struct gns_coverart_info {
	uint32_t	coverart_size;
	uint32_t	coverart_format;
	uint32_t	coverart_dimension;
	uint32_t	coverart_source;
	char		*album_tagid;
	char		*album_fetchid;
	char		*filename;
} gns_coverart_info_t;

typedef struct gns_coverart {
	gns_coverart_info_t	info;
	char			*coverart;
} gns_coverart_t;

typedef struct gns_metadata {
	gns_album_metadata_t		*album_metadata;
	gns_album_representation_t	*album_representation;
	gns_coverart_t			*album_coverart;
} gns_metadata_t;

typedef struct gns_metadata_container {
	uint32_t		num_results;
	gns_metadata_t		metadata[];
} gns_metadata_container_t;

typedef struct gns_fingerprint_options {
	uint32_t	algorithm;
	uint32_t	encoding_format;
	uint32_t	sample_rate;
	uint32_t	channels;
	uint32_t	type;
} gns_fingerprint_options_t;

typedef struct gns_ondemand_config {
	uint32_t	full_data_on_multi;
	uint32_t	single_match;
	uint32_t	coverart_dimension_on_partial;
	uint32_t	coverart_source;
	uint32_t	coverart_dimension;
	uint32_t	multi_match_limit;
	uint32_t	update_source;
} gns_ondemand_config_t;

/**
 * Free all allocated memory associated with a fid metadata
 * structure.  NULL values are checked so incomplete
 * data is allowed. 
 *
 * Arguments IN:
 *	metadata	A fid metdata structure.
 */
void gnc_metadata_fid_free( gns_generic_metadata_t *metadata );

/**
 * Acquire a connection handle to the gracenote server 
 *
 * Arguments IN:
 *	path	Path to the resource manager mount path.
 *	flags	Reserved for future use.
 *
 * Returns:
 * 	NULL 	on error.
 * 	!NULL  	on success.
 */
gns_hdl_t *gnc_connect( const char *path, uint32_t flags );

/**
 * Disconnect from the gracenote server.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_disconnect( gns_hdl_t *hdl );

/**
 * Call into the server to initialize Gracenote.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_init( gns_hdl_t *hdl );

/**
 * Call into the server to safely perform a shutdown.
 * The emmslib will be shutdown as well.  The server
 * will continue running and can be re-initialized with
 * gnc_init() which will also reload the config file.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_shutdown( gns_hdl_t *hdl );

/**
 * Call into the server to install gracenote databases.
 * The source and destination locations can be specified
 * as arguments are negated to attempt to use those in the
 * gracenote.cfg.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	lfs_id		A lfs_id for the databases, provided by GN.	(Optional).
 *	install_dir	The install location to use.			(Optional).
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_install( gns_hdl_t *hdl, const char *lfs_id, const char *install_dir ); 

/**
 * Call into the server to uninstall Gracenote databases.
 * The source and destination locations are handled on the 
 * server side.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_uninstall( gns_hdl_t *hdl ); 

/**
 * Call into the server to check the init status.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Returns:
 * 	  0	on uninitialized.
 * 	  1  	on initialized.
 */
int gnc_status_get( gns_hdl_t *hdl );

/**
 * Call into the server to return version data for the 
 * emmslib and the installed db.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	size		Size of buffer.
 *	index		Index describing which incremental update to be returned.
 *	flags		Flags describing which data to return.
 *
 * Arguments OUT:
 *	buffer		Buffer to hold returned value.
 *
 * Returns:
 * 	 -1	on failure.
 *	  0	if value of index is too large.
 * 	 >0  	required size of buffer for full return data.
 */
int gnc_version_info_get( gns_hdl_t *hdl, char *buffer, size_t size, uint32_t index, uint32_t flags );

/**
 * Call into the server to open an existing Gracenote MLDB
 * collection.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0  	on success.
 */
int gnc_collection_open( gns_hdl_t *hdl, uint64_t cid );

/**
 * Call into the server to close an existing Gracenote MLDB
 * collection or all collections.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID or "0" to close
 *		all open collections.
 *
 * Returns:
 * 	 -1	on error.
 * 	>=0 	number of collections closed.
 */
int gnc_collection_close( gns_hdl_t *hdl, uint64_t cid );

/**
 * Call into the server to request the creation of a new Gracenote 
 * MLDB collection.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *
 * Arguments OUT:
 *	cid	A new collection ID.
 *
 * Returns:
 * 	 -1	on error (cid set to 0).
 * 	  0  	on success (cid > 0 ).
 */
int gnc_collection_create( gns_hdl_t *hdl, uint64_t *cid );

/**
 * Call into the server to delete an existing Gracenote MLDB
 * collection or all collections.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID or "0" to delete
 *		all available collections.
 *
 * Returns:
 * 	 -1	on error.
 * 	>=0 	number of collections deleted.
 */
int gnc_collection_delete( gns_hdl_t *hdl, uint64_t cid );

/**
 * Call into the server to flush any uncommited data to the 
 * collection MLDB.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID or "0" to commit all
 *		open collections.
 *
 * Returns:
 * 	 -1	on error.
 * 	>=0  	number of collections removed.
 */
int gnc_collection_commit( gns_hdl_t *hdl, uint64_t cid );

/**
 * Call into the server to backup 1 or all MLDBS data to the 
 * configured location.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID or "0" to backup all
 *		collections.
 *
 * Returns:
 * 	 -1	on error.
 * 	>=0  	number of collections backed up.
 */
int gnc_collection_backup( gns_hdl_t *hdl, uint64_t cid );

/**
 * Add a fid to an open MLDB collection and possibly receive some normalized
 * metadata back.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	cid		Valid collection ID.
 *	fid		Valid fid.
 *	in_metadata	Metadata to use for textid lookup.
 *	fetch_id	Use a specific album identifier to pull in the results.	(Optional)
 *	track_id	Use a specific track identifier to pull in the results. (Optional)
 *	flags		Specify what data to return if available
 * 			( refer to defines at top of this header file )
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on no textid lookup found.
 * 	  1	textid lookup successful and added.
 */
int gnc_collection_entry_add( gns_hdl_t *hdl, uint64_t cid, uint64_t fid, gns_generic_metadata_t *in_metadata, const char *fetch_id, 
												const char *track_id, uint32_t flags );

/**
 * Update a fid to an open MLDB collection and possibly receive some normalized
 * metadata back.  If the fid doesn't exist in the MLDB collection, it will be
 * removed as it is not longer available for playlisting. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	cid		Valid collection ID.
 *	fid		Valid fid.
 *	in_metadata	Metadata to use for textid lookup.
 *	fetch_id	Use a specific album identifier to pull in the results.	(Optional)
 *	track_id	Use a specific track identifier to pull in the results. (Optional)
 *	flags		Specify what data to return if available.
 * 			( refer to defines at top of this header file )
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	no updates and original item removed.
 * 	  1	on item updated.
 */
int gnc_collection_entry_update( gns_hdl_t *hdl, uint64_t cid, uint64_t fid, gns_generic_metadata_t *in_metadata, const char *fetch_id, 
												const char *track_id, uint32_t flags );

/**
 * Add an existing musicID result to the MLDB. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	cid		Valid collection ID.
 *	fid		Valid fid.
 *	ser_data	A buffer containing the serialized musicID result.
 *	data_path	A path to a file containing the serialized musicID result.
 *	match		The match to use for multihit results.
 *	flags		Specify what data to return if available.
 * 			( refer to defines at top of this header file )
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on item added.
 */
int gnc_collection_entry_add_result( gns_hdl_t *hdl, uint64_t cid, uint64_t fid, const char *ser_data, const char *data_path, 
												uint32_t match, uint32_t flags );

/**
 * Delete a fid from an open MLDB collection
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	cid		Valid collection ID.
 *	fid		Valid fid.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on no textid lookup found.
 * 	  1	textid lookup successful and added.
 */
int gnc_collection_entry_delete( gns_hdl_t *hdl, uint64_t cid, uint64_t fid );

/**
 * Get a list of available MLDB collections
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 * 
 */
int gnc_collection_list_get( gns_hdl_t *hdl );

/**
 * Call into the server to compact an existing Gracenote MLDB
 * collection or all collections.
 *
 * Arguments IN:
 *	hdl	A valid handle to the server.
 *	cid	A valid collection ID or "0" to compact
 *		all available collections.
 *
 * Returns:
 *	 -1	on error.
 *	>=0	number of collections compacted.
 */
int gnc_collection_compact( gns_hdl_t *hdl, uint64_t cid );

/**
 * Add a fid to an open MLDB collection and possibly receive some normalized
 * metadata back.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	in_metadata	Metadata to use for textid lookup.
 *	fetc_id		Use a specific album identifier to pull in the results.	(Optional)
 *	max_results	The maximum number of results to return. 		(0 = all)
 *	coverart_path	Filename to use for coverart write.			(Optional)
 *	flags		Specify what data to return if available,
 *			default is album level metadata.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on no textid lookup found.
 * 	  1	textid lookup successful.
 */
int gnc_textid_lookup( gns_hdl_t *hdl, gns_generic_metadata_t *in_metadata, const char *fetch_id, uint32_t max_results, 
										const char *coverart_path, uint32_t flags );

/**
 * Generate a playlist from an open MLDB collection
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	cid		Valid collection ID.
 *	fid		Valid fid 				(Optional).
 *	seed1		Some seed data (generaly artist)	(Optional).
 *	seed2		Some seed data (generaly album)		(Optional).
 *	max_fids	Maximum number of results to generate
 *	seed_type	Define the seed data to use.  Refer to
 *			gracenote_srvr.h for types.
 *	flags		Reserved.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: The optional arguments required are based on the seed type.  If the seed
 *       is of type ENTRYDATA only a fid is required.  For seed types ARTIST, seed1
 *       must containg the artist.  For seed type ALUBM, seed1 must contain the artist
 *       while seed2 must contains the album.
 */
int gnc_playlist_generate( gns_hdl_t *hdl, uint64_t cid, uint64_t fid, const char *seed1, const char *seed2, 
								uint32_t max_fids, uint32_t seed_type, uint32_t flags ); 

/**
 * Query Gracenote online for information based on a CD TOC.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	toc		A string representing the TOC to lookup.
 *	album_id	Use a specific album identifier to pull in the results.	(Optional)
 *	max_results	The maximum number of results to return.		(0 = all)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	flags		Specify what data to return if available,
 *			default is album and track level metadata.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_cd_lookup_online( gns_hdl_t *hdl, const char *toc, const char *album_id, uint32_t max_results, const char *coverart_path, uint32_t flags ); 

/**
 * Query Gracenote for information based on a CD TOC.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	toc		A string representing the TOC to lookup.
 *	album_id	Use a specific album identifier to pull in the results.	(Optional)
 *	max_results	The maximum number of results to return.		(0 = all)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	flags		Specify what data to return if available,
 *			default is album and track level metadata.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_cd_lookup( gns_hdl_t *hdl, const char *toc, const char *album_id, uint32_t max_results, const char *coverart_path, uint32_t flags ); 

/**
 * Query Gracenote for album art information using either metadata or
 * a TOC.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	in_metadata	Metadata to use for textid lookup. 			(Optional)
 *	toc		A string representing the TOC to lookup. 		(Optional)
 *	album_id	Use a specific album identifier to pull in the results.	(Optional)
 *	track_id	Use a specific track identifier to pull in the results.	(Optional)
 *	fetch_id	Use a specific album identifier to pull in the results. (Optional)
 *	max_results	The maximum number of results to return. 		(0 = all)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	flags		Specify what data to return if available,
 *			default is coverart and coverart information.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_coverart_lookup( gns_hdl_t *hdl, gns_generic_metadata_t *in_metadata, const char *toc, const char *album_id, const char *track_id, const char *fetch_id, 
											uint32_t max_results, const char *coverart_path, uint32_t flags ); 

/**
 * Query Gracenote for data from a fingerprint lookup (PCM data).
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	in_metadata	Metadata used to assist the fingerprint lookup		(Optional)
 *	fp_options	Data describing the PCM fingerprint.			(Optional)
 *	data		Buffer file containing PCM data or a fingerprint.	(Optional)
 *	data_sz		The size of the data buffer.				(Optional)
 *	data_path	A path to the file containing PCM data or a fingerprint (Optional)
 *	max_results	The maximum number of results to return. 		(0 = all)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	flags		Specify what data to return if available,
			default is track level metadata.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: The data can be either raw PCM data or a pre-encoded fingerprint.
 *       If it's raw PCM data, fp_options cannot be NULL.
 *       Either a buffer containing the data and a size or a path to the data 
 *       can be passed in.
 */
int gnc_fingerprint_lookup( gns_hdl_t *hdl, gns_generic_metadata_t *in_metadata, gns_fingerprint_options_t *fp_options, const char *data, size_t data_sz, const char *data_path,
													uint32_t max_results, const char *coverart_path, uint32_t flags );

/**
 * Query Gracenote for data from a fingerprint lookup (PCM data) and return the
 * serialized musicID data for a future MLDB addition.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	in_metadata	Metadata used to assist the fingerprint lookup		(Optional)
 *	fp_options	Data describing the PCM fingerprint.			(Optional)
 *	data		Buffer file containing PCM data or a fingerprint.	(Optional)
 *	data_sz		The size of the data buffer.				(Optional)
 *	data_path	A path to the file containing PCM data or a fingerprint (Optional)
 *	max_results	The maximum number of results to return. 		(0 = all)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	out_buf		A buffer to store the serialized data in.		(Optional)
 *	dst_file	A path to a file to store the serialized data in.	(Optional)
 *	
 *	flags		Specify what data to return if available,
			default is track level metadata.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: The data can be either raw PCM data or a pre-encoded fingerprint.
 *       If it's raw PCM data, fp_options cannot be NULL.
 *       Either a buffer containing the data and a size or a path to the data 
 *       can be passed in.
 */
int gnc_fingerprint_lookup_serialized( gns_hdl_t *hdl, gns_generic_metadata_t *in_metadata, gns_fingerprint_options_t *fp_options, const char *data, size_t data_sz,
											const char *data_path, uint32_t max_results, const char *coverart_path,
											unsigned char **out_buf, const char *dst_file, uint32_t flags );

/**
 * Delete a list of entries from the on-demand cache based on their TOC
 * identifiers.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	toc_list	A list of TOCs to process.
 *	num_tocs	The number of tocs in the toc_list.
 *	flags		Reserved for future use.
 *
 * Returns:
 * 	-1			on error.
 * 	entries_deleted		on success.
 */
int gnc_ondemand_toc_entries_delete( gns_hdl_t *hdl, const char **toc_list, int num_tocs, uint32_t flags );

/**
 * Turn a list of missed TOCS into a serialized stream of bytes.  The 
 * stream can be used to perform and on-demand lookup on the internet
 * or through a proxy.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	toc_list	A list of TOCs to process.
 *	id_list		A list of strings to add to the lookups for later
 *			retrieval.
 *	num_tocs	The number of tocs in the toc_list.
 *	config		A configuration structure describing the required
			options.
 *	dst_file	A file to write to the results to. 			(Optional)
 *	flags		Reserved for future use.
 *      
 * Arguments OUT:
 * 	out_buf		A buffer to contain the serialized data.		(Optional)
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: Either a buffer or a file is required but not both. If both
 *       are passed in, the output will be written to the file.  If
 *	 a buffer is used, the data is owned by the caller and must be
 *	 free'd after use. 
 */
int gnc_ondemand_toc_requests_serialize( gns_hdl_t *hdl, const char **toc_list, const char **id_list, int num_tocs, gns_ondemand_config_t *config,
										unsigned char **out_buf, const char *dst_file, uint32_t flags );

/**
 * Generate a new request package based on the partial results from
 * a previous response package. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	request_id	A unique ID to identify a particular result.  If
 *			left NULL, the first item in the package is used.	(Optional)
 *	config		A configuration structure describing the required
 *			options.
 *	in_buf		A buffer containing the response package.		(Optional)
 *	in_buf_sz	The size of the in_buf.
 *	src_file	A file to read the response data from. 			(Optional)
 *	dst_file	A file to write to the results to. 			(Optional)
 *	match		The match to use for multihit results.
 *	flags		Reserved for future use.
 *      
 * Arguments OUT:
 * 	out_buf		A buffer to contain the serialized data.		(Optional)
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: Either a buffer or a file is required but not both. If both
 *       are passed in, the output will be written to the file.  If
 *	 a buffer is used, the data is owned by the caller and must be
 *	 free'd after use. 
 */
int gnc_ondemand_response_serialize_match( gns_hdl_t *hdl, const char *request_id, gns_ondemand_config_t *config, const unsigned char *in_buf,
										size_t in_buf_sz, unsigned char **out_buf, const char *src_file,
												const char *dst_file, uint32_t match, uint32_t flags );

/**
 * Parse an already acquired ondemand response package into a
 * gns_metadata_t structure (metadata/album art/phonetic data). 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	request_id	An identifier for selecting the proper element
 *			within the response package.
 *	max_results	The maximum number of results to return.		(0 = ALL)
 *	in_buf		A buffer containing the response data.			(Optional)
 *	in_buf_sz	The size of the response data buffer.
 *	src_file	A file to read the response data from. 			(Optional)
 *	coverart_path	Filename to use for coverart write. 			(Optional)
 *	flags		Specify what data to return if available,
 *			default is album and track level metadata.
 *      
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: Either a buffer or a file is required but not both. If both
 *       are passed in, the output will be read from the file.
 */
int gnc_ondemand_response_parse( gns_hdl_t *hdl, const char *request_id, uint32_t max_results, const unsigned char *in_buf, size_t in_buf_sz,
										const char *src_file, const char *coverart_path, uint32_t flags );

/**
 * Add a list of on-demand responses which where acquired when the 
 * an internet connection was available to the target system or 
 * matches were found via a proxy server.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	buf		A buffer containing the serialized data.		(Optional)
 *	sz		The size of the buffer	.				(Optioanl)
 *	src_file	A file to read the response data from. 			(Optional)
 *	request_id	A unique ID to identify a particular result.		(Optional)
 *			If left NULL, all items will be cached.
 *	match		The match to use for multihit results.  If
 *			request_id is NULL, the first multihit match
 *			will be used for all instances.
 *	flags		Reserved for future use.     
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 *
 * Note: Either a file or a buffer/size is required but not both. If both
 *       are passed in, the input will be read from the file. 
 */
int gnc_ondemand_lookups_cache( gns_hdl_t *hdl, const unsigned char *buf, size_t sz, const char *src_file, const char *request_id, uint32_t match, uint32_t flags );

/**
 * Get the size of the on-demand cache.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Arguments OUT:
 *	sz		The size of the cache in bytes.
 * 
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_ondemand_cache_size_get( gns_hdl_t *hdl, uint32_t *sz );

/**
 * Delete everything from the on-demand cache.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_ondemand_cache_delete( gns_hdl_t *hdl );

/**
 * Backup the on-demand cache to the file location specified
 * the gracenote configuration file.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_ondemand_cache_backup( gns_hdl_t *hdl );

/**
 * Revert the current on-demand cache to the backup up one.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_ondemand_cache_revert( gns_hdl_t *hdl );

/**
 * Compact the on-demand cache.  Refer to the Gracenote
 * documentation for information on size gains.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_ondemand_cache_compact( gns_hdl_t *hdl );


/**
 * Delete a list of entries from the lookup cache based on their TOC
 * identifiers.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	toc_list	A list of TOCs to process.
 *	num_tocs	The number of tocs in the toc_list.
 *	flags		Reserved for future use.
 *
 * Returns:
 * 	-1			on error.
 * 	entries_deleted		on success.
 */
int gnc_lucache_toc_entries_delete( gns_hdl_t *hdl, const char **toc_list, int num_tocs, uint32_t flags );

/**
 * Get the current configuration setting for the maximum size of the lookup cache.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Arguments OUT:
 *	sz		The configuration setting for the maximum size of the lookup cache in bytes.
 * 
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_get_max_size( gns_hdl_t *hdl, uint32_t *sz );

/**
 * Get the current configuration setting for the warning size of the lookup cache.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Arguments OUT:
 *	sz		The configuration setting for the warning size of the lookup cache in bytes.
 * 
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_get_warning_size( gns_hdl_t *hdl, uint32_t *sz );

/**
 * Delete everything from the lookup cache.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_delete( gns_hdl_t *hdl );

/**
 * Backup the lookup cache to the file location specified
 * in the gracenote configuration file.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_backup( gns_hdl_t *hdl );

/**
 * Revert the current lookup cache to the backup up one.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_revert( gns_hdl_t *hdl );

/**
 * Compact the lookup cache.  Refer to the Gracenote
 * documentation for information on size gains.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *
 * Returns:
 * 	 -1	on error.
 * 	  0	on success.
 */
int gnc_lucache_compact( gns_hdl_t *hdl );


/**********************************************************
 * The following APIs are used for accessing data returned 
 * via the previous lookups.
 **********************************************************/

/**
 * Get the index of the album currently set.  This will change with
 * calls to gnc_next_album() and gnc_set_album_index().
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on nothing set.
 * 	index		on success.
 */
int gnc_get_album_index( gns_hdl_t *hdl );

/**
 * Get the index of the track currently set.  This will change with
 * calls to gnc_next_track() and gnc_set_track_index().
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on nothing set.
 * 	index		on success.
 */
int gnc_get_track_index( gns_hdl_t *hdl );

/**
 * Get the index of the work currently set.  This will change with
 * calls to gnc_next_work() and gnc_set_work_index().
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on nothing set.
 * 	index		on success.
 */
int gnc_get_work_index( gns_hdl_t *hdl ); 

/**
 * Query the results to see how many albums were
 * returned. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 * 	num_albums.
 */
int gnc_get_album_count( gns_hdl_t *hdl ); 

/**
 * Query the results to see if metadata has been returned
 * for the selected album. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	 0		on no metadata returned.
 * 	 1		on metadata returned.
 *	-1		on error.
 */
int gnc_album_has_metadata( gns_hdl_t *hdl );

/**
 * Query the results to see if a representation has been
 * returned for the selected album.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	 0		on no representation(s) returned.
 * 	 1		on repreentation(s) returned.
 *	-1		on error.
 */
int gnc_album_has_representation( gns_hdl_t *hdl );

/**
 * Query the results to see if cover art has been returned
 * for the selected album.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	 0		on no coverart returned.
 * 	 1		on coverart returned.
 *	-1		on error.
 */
int gnc_album_has_coverart( gns_hdl_t *hdl );

/**
 * Query the results to see if metadata has been returned
 * for a particular album
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	album_index	The index of the album to query.
 *      
 * Returns:
 *	 0		on no metadata returned.
 * 	 1		on metadata returned.
 *	-1		on error.
 */
int gnc_album_has_metadata_at_index( gns_hdl_t *hdl, int album_index );

/**
 * Query the results to see if a representation has been
 * returned for a particular album.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	album_index	The index of the album to query.
 *      
 * Returns:
 *	 0		on no representation(s) returned.
 * 	 1		on repreentation(s) returned.
 *	-1		on error.
 */
int gnc_album_has_representation_at_index( gns_hdl_t *hdl, int album_index );

/**
 * Query the results to see if cover art has been returned
 * for a particular album.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	album_index	The index of the album to query.
 *      
 * Returns:
 *	 0		on no metadata returned.
 * 	 1		on metadata returned.
 *	-1		on error.
 */
int gnc_album_has_coverart_at_index( gns_hdl_t *hdl, int album_index );

/**
 * Query the results to see how many tracks were returned
 * for a specific album. An album must first be selected to 
 * obtain this data as each album can have multiple tracks.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on no album selected.
 * 	num_tracks	on success.
 */
int gnc_get_track_count( gns_hdl_t *hdl );

/**
 * Query the results to see how many works were returned
 * for a specific track. A track must first be selected to 
 * obtain this data as each track can have multiple works.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on no track selected.
 * 	num_works	on success.
 */
int gnc_get_work_count( gns_hdl_t *hdl ); 

/**
 * Query the results to see how many tracks were
 * returned for a specific album. No album need be
 * previously selected. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	album_index	The index of the album to query.
 *      
 * Returns:
 *	-1		on error.
 * 	num_tracks	on success.
 */
int gnc_get_track_count_at_index( gns_hdl_t *hdl, int album_index ); 

/**
 * Query the results to see how many works were
 * returned for a specific album/track. No album/track
 * need be previously selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	album_index	The index of the album to query.
 *	track_index	The index of the track to query.
 *      
 * Returns:
 *	-1		on error.
 * 	num_works	on success.
 */
int gnc_get_work_count_at_index( gns_hdl_t *hdl, int album_index, int track_index );

/**
 * Iterate through the albums using this function.  Once a
 * full iteration is complete and 0 is returned, the function
 * can be re-called to start back at the beginning.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 *	 0		on end-of-list.
 * 	 1		on successful change.
 */
int gnc_next_album( gns_hdl_t *hdl );

/**
 * Iterate through the tracks using this function. An album
 * must first be selected in order to iterate the tracks.
 * Once a full iteration is complete and 0 is returned, the  
 * function can be re-called to start back at the beginning.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 *	 0		on end-of-list.
 * 	 1		on successful change.
 */
int gnc_next_track( gns_hdl_t *hdl );

/**
 * Iterate through the works using this function. A track
 * must first be selected in order to iterate the works.
 * Once a full iteration is complete and 0 is returned, the  
 * function can be re-called to start back at the beginning.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 *	 0		on end-of-list.
 * 	 1		on successful change.
 */
int gnc_next_work( gns_hdl_t *hdl );

/**
 * Set the index of the album to query/access.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	index		The album index to set.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_set_album_index( gns_hdl_t *hdl, int index ); 

/**
 * Set the index of the track to query/access. An album
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	index		The track index to set.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_set_track_index( gns_hdl_t *hdl, int index );

/**
 * Set the index of the work to query/access. A track
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	index		The work index to set.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_set_work_index( gns_hdl_t *hdl, int index );

/**
 * Get a particular album string based on a given key.
 * An album must first be selected. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	key		The key used for finding a particular result.
 *      
 * Arguments OUT:
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the string.
 */
int gnc_get_album_string_by_key( gns_hdl_t *hdl, const char *key, char **value );

/**
 * Get a particular track string based on a given key.
 * A track must first be selected. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	key		The key used for finding a particular result.
 *      
 * Arguments OUT:
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the string.
 */
int gnc_get_track_string_by_key( gns_hdl_t *hdl, const char *key, char **value );

/**
 * Get a particular work string based on a given key.
 * A work must first be selected. 
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	key		The key used for finding a particular result.
 *      
 * Arguments OUT:
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the string.
 */
int gnc_get_work_string_by_key( gns_hdl_t *hdl, const char *key, char **value );

/**
 * Get the next album key/value pair.  An album must first be
 * selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	key		The key used for obtaining a particular result.
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value and key populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free either string.
 */
int gnc_get_next_album_string( gns_hdl_t *hdl, char **key, char **value );

/**
 * Get the next track key/value pair.  An track must first be
 * selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	key		The key used for obtaining a particular result.
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value and key populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free either string.
 */
int gnc_get_next_track_string( gns_hdl_t *hdl, char **key, char **value );

/**
 * Get the next work key/value pair.  An work must first be
 * selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	key		The key used for obtaining a particular result.
 *	value		A string containing a result.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on no results.
 *	 1		result found (value and key populated).
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free either string.
 */
int gnc_get_next_work_string( gns_hdl_t *hdl, char **key, char **value );

/**
 * Get the phonetic data representation for an indexed album. No album
 * need first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	index		An album index.
 *      
 * Arguments OUT:
 *	metadata	An album representation structure.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the representation structure.
 */
int gnc_get_representation_at_index( gns_hdl_t *hdl, int index, gns_album_representation_t **metadata );

/**
 * Get the phonetic data representation for the selected album. An album
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	metadata	An album representation structure.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the representation structure.
 */
int gnc_get_representation( gns_hdl_t *hdl, gns_album_representation_t **metadata );

/**
 * Get the coverart data for a selected album. An album
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	metadata	A coverart structure.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the coverart structure.
 */
int gnc_get_coverart_at_index( gns_hdl_t *hdl, int index, gns_coverart_t **metadata );

/**
 * Get the coverart data for an index album. No album
 * need first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Arguments OUT:
 *	metadata	A coverart structure.
 *
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the coverart structure.
 */
int gnc_get_coverart( gns_hdl_t *hdl, gns_coverart_t **metadata );

/**
 * Get the number of abailable album strings for the selected album. An album
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 num_strings	on success.
 */
int gnc_get_num_album_strings( gns_hdl_t *hdl );

/**
 * Get the number of abailable track strings for the selected track. A track
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 num_strings	on success.
 */
int gnc_get_num_track_strings( gns_hdl_t *hdl );

/**
 * Get the number of abailable work strings for the selected work. A work
 * must first be selected.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 num_strings	on success.
 */
int gnc_get_num_work_strings( gns_hdl_t *hdl );

/**
 * Get the number of playlist fields.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 * 	 num_fields.
 */
int gnc_get_num_playlist_fields( gns_hdl_t *hdl );

/**
 * Get the next playlist fid and file name.
 *
 * Note: To save space, the file name is not stored
 *       in the MLDBs at the current time so it will
 *	 always be NULL.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the coverart structure.
 */
int gnc_get_next_playlist_field( gns_hdl_t *hdl, uint64_t *fid, char **filename );

/**
 * Get the playlist fid and file name at a specific
 * index.
 *
 * Note: To save space, the file name is not stored
 *       in the MLDBs at the current time so it will
 *	 always be NULL.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 *
 * NOTE: The memory is not owned by the caller, do not attempt
 *	 to free the coverart structure.
 */
int gnc_get_playlist_field_at_index( gns_hdl_t *hdl, int index, uint64_t *fid, char **filename );

/**
 * Get the number of collections returned.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 * 	 num_collections.
 */
int gnc_get_num_collections( gns_hdl_t *hdl );

/**
 * Get the next collection.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_get_next_collection( gns_hdl_t *hdl, uint32_t *collection );

/**
 * Get the collection at a specific index.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_get_collection_at_index( gns_hdl_t *hdl, int index, uint32_t *collection );

/**
 * Set the target spoken language of the system.  This will
 * affect the language of the phonetic data being returned.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	language	A language ID string defined by Gracenote.
 *	flags		Reserved for future use.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_spoken_language_set( gns_hdl_t *hdl, const char *language, uint32_t flags );

/**
 * Get the currently set target spoken language of the system.
 *
 * Arguments IN:
 *	hdl		A valid handle to the server.
 *	sz		The size of the language buffer.
 *	flags		Reserved for future use.
 *
 * Arguments OUT:
 *	language	A buffer used to store the language string in.
 *      
 * Returns:
 *	-1		on error.
 * 	 0		on success.
 */
int gnc_spoken_language_get( gns_hdl_t *hdl, char *language, size_t sz, uint32_t flags );

__END_DECLS
#endif /*GRACENOTE_CLIENT_H_*/

__SRCVERSION("gracenote_client.h $Rev: $");


