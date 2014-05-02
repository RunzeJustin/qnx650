/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
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



/* Bitmask of types clients can register for */
#define DBNOTIFY_TYPE_ADDED			0x0001
#define DBNOTIFY_TYPE_DELETED			0x0002
#define DBNOTIFY_TYPE_UPDATED			0x0004

/* Potential status of the clients */
#define DBNOTIFY_STATUS_NONE			0
#define DBNOTIFY_STATUS_ERROR			-1
#define DBNOTIFY_STATUS_INVALID_HANDLE		-2
#define DBNOTIFY_STATUS_LOOKUP_EMPTY		-3

/* Potential flags used during unregistration */
#define DBNOTIFY_UNREG_LEAVE_CLIENT_DBENTRY	0x0001

/* Potential flags used during registration */
#define DBNOTIFY_REG_RESET_CLIENT_OFFSET	0x0001

/* Potential flags used during get_next */
#define DBNOTIFY_DONTSLEEP_ON_EMPTY		0x0001

__BEGIN_DECLS

/* Opaque handle */
typedef struct dbnotify_hdl_s dbnotify_hdl_t;

/* 
 * This function intializes the notification module.  It takes in a cache
 * size and the maximum number of entries a single block can hold.  Playing
 * with these values should help improve performance versus memory
 * restrictions.  An event handler thread is also started at this point
 * to try and use sync events as a hint as to when we should go look for
 * data.
 *
 * @param max_cahce_size 	The maximum size of the cache across all registered clients.
 * @param max_block_entries	The maximum number of DB entries to store in a single block.
 * @param max_clients		The maximum number of clients allowed to connect at once.
 * @param pps_path		Full path to the dbnotify PPS directory to use.
 *
 * return	-1 on error.
 * return	 0 on success.
 */  
int dbnotify_init( size_t max_cache_size, uint32_t max_block_entries, int max_clients, const char *pps_path );

/*
 * No cache memory is freed during the shutdown process.  This means that all registered
 * client must first call dbnotify_unregister() before calling the shutdown function
 * otherwise there will be lingering memory.
 *
 * return	-1 on error.
 * return	 0 on success.
 */
int dbnotify_shutdown( void );

/* 
 * This function  is used to register a client to start receiving notifications.
 * If this is the first client registered for a specific database, a new cache will be
 * created.
 *
 * @param dbname	The name of the database which sync is/will be taking place.
 * @param cname		A unique client name.
 * @write_frequency	Persistently keep track of offset in DB after this many lookups. (0 for none).
 * @types		Which types to register for.  Unregistered types will be ignored.
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */ 

dbnotify_hdl_t *dbnotify_register( const char *dbname, const char *cname, int write_frequency, uint32_t types, uint32_t flags );

/* 
 * This function should be called when a client no longer requires any database 
 * updates.  If this is the last client registered againsta cache, the cache will
 * get deleted.
 *
 * @param hdl		A valid dbnotify handle.
 * @param flags		Control flags.
 *
 * Note: All clients should call this function before calling
 *       dbnotify_shutdown or there will be lingereing memory.
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */ 
int dbnotify_unregister( dbnotify_hdl_t *hdl, uint32_t flags );

/*
 * Unblock any threads who may be sleeping waiting for work.  It is envisioned
 * that this function could be called when the database is updated outside of
 * sync.
 *
 * @param hdl		A valid dbnotify handle.
 * @param flags		Control flags (reserved for future use).
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */
int dbnotify_unblock( dbnotify_hdl_t *hdl, uint32_t flags );

/* 
 * This function should be called when a client no longer requires any database 
 * updates.  If this is the last client registered againsta cache, the cache will
 * get deleted.
 *
 * Note: All clients should call this function before calling
 *       dbnotify_shutdown or there will be lingereing memory.
 *
 * @param hdl		A valid dbnotify handle.
 * @param flags		Control flags.
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */ 
int dbnotify_destroy( dbnotify_hdl_t *hdl, uint32_t flags );

/*
 * Get the next entry and type from the database.  If the type isn't
 * registered by this fid, the function will continue looking until
 * a valid type is found or the database is exhausted.
 *
 * @param hdl		A valid dbnotify handle.
 * @param fid		A pointer to store the FID in.
 * @param type		A pointer to store the type in.
 * @param extdata	A pointer to a buffer to store user defined metadata.
 * @param flags		Control flags.
 *
 * return	DBNOTIFY err on error.
 * return	0 on success.
 */
int dbnotify_get_next( dbnotify_hdl_t *hdl, uint64_t *fid, uint32_t *type, uint64_t **extdata, uint32_t flags );

/*
 * Return the current global offset of the lookup handle.  This
 * offset is used to track where in the database the next entry
 * lies.
 *
 * @param hdl		A valid dbnotify handle.
 *
 * returns	offset.
 */
uint64_t dbnotify_get_offset( dbnotify_hdl_t *hdl );

/*
 * Write a specific offset to the database.  This is used to track
 * where the client was on a restart and is also used by a trigger
 * to cleanup any database entries no longer required.
 *
 * @param hdl		A valid dbnotify handle.
 * @param offset	The offset to write.
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */
int dbnotify_write_offset( dbnotify_hdl_t *hdl, uint64_t offset );

/*
 * Write the offset that the client has already handled to
 * the database.  This is used to track where the client
 * was on a restart and is also used by a trigger to cleanup
 * any database entries no longer required.
 *
 * @param hdl	A valid dbnotify handle.
 *
 * returns	-1 on error.
 * returns	 0 on success.
 */
int dbnotify_write_current_offset( dbnotify_hdl_t *hdl);

/*
 * This function is used to get the number of extra fields
 * found in the database which will be returned as a uint64_t
 * pointer.
 *
 * @param hdl	A valid dbnotify handle.
 *
 * @returns	number of extended fields.
 */
int dbnotify_get_extdata_count( dbnotify_hdl_t *hdl );

__END_DECLS

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/dbnotify/public/dbnotify/dbnotify.h $ $Rev: 680334 $")
#endif
