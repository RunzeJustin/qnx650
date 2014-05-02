/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */

#ifndef __PDBP_API_H__
#define __PDBP_API_H__

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include "mme/event.h"
#include "gracenote/gracenote_client.h"

#define GNDBP_PDBP_NAME			gndbp_pdbp
#define GNDBP_PDBP_NAME_STR		"gndbp_pdbp"

__BEGIN_DECLS

typedef struct s_pdbp_session pdbp_session_t;

typedef struct gndbp_metadata_ids {
	uint64_t	album_id;
	uint64_t	artist_id;
	uint64_t	genre_id;
} gndbp_metadata_ids_t;

typedef struct pdbp_table {
	/** 
	 * An initialization function that may be needed by the plug-in.
	 * 
	 * Optional.
	 * 
	 * @return 0 on success.
	 * @return -1 on failure.
	 */
	int	(*init)(void);

	/** 
	 * An termination function that may be needed by the plug-in.
	 * 
	 * Optional.
	 * 
	 * @return 0 on success.
	 * @return -1 on failure.
	 */
	int	(*terminate)(void);

	/** 
	 * A function to tell the plug-in about mediastore state changes. This 
	 * function is not optional. 
	 * 
	 * The intent of this function is to let the external database know the
	 * state with respect to the database. However, it is not provided in a
	 * distilled form here; the plug-ins may choose to interpret the transitions
	 * as they need.
	 *  
	 * @param msid		ID of the media store that has changed state. 
	 * @param old_state	The initial state of the transition. 
	 * @param new_state	The final state of the transition. 
	 * @return 		0 on success.
	 * @return 		-1 on failure.
	 */
	int	(*ms_state_change)(uint64_t msid, mme_ms_state_t old_state, mme_ms_state_t new_state);

	/** 
	 * This function is used to open a synchronization session on the plugin.
	 * 
	 * @param msid		ID of the media store the entry has been added to. 
	 * @param session 	Place to return session pointer to be used for add and 
	 *                	update calls.
	 * @return 		0 on success.
	 * @return 		-1 on failure.
	 */
	int	(*session_open)(pdbp_session_t **session, uint64_t msid);

	/** 
	 * This function is used to close a synchronization session on the plugin. 
	 *  
	 * It indicates to the plugin that all synchronization calls are done until 
	 * a new session is opened. 
	 * 
	 * @param msid	ID of the media store the entry has been added to. 
	 * @param 	session The session pointer for the session that is being closed. 
	 * @return 	0 on success.
	 * @return 	-1 on failure.
	 */
	int	(*session_close)(pdbp_session_t *session);

	/** 
	 * Function to indicate the addition of a library table entry. Not optional. 
	 *  
	 * The implementation of the plug-in may access the database to get more 
	 * information about the library table entry as needed. 
	 * 
	 * @param session	The session pointer. 
	 * @param fid		ID of the library table entry that has been added. 
	 * @param phonemes	Phonetic data return from external DB
				normalized_metadata
	 * @return 		0 on success.
	 * @return 		-1 on failure.
	 */
	int	(*fid_added)(pdbp_session_t *session, uint64_t fid, gns_album_representation_t *representation);

	/** 
	 * Function to indicate a change to a library table entry. 
	 *  
	 * The implementation of the plug-in may access the database to get more 
	 * information about the library table entry as needed. 
	 * 
	 * @param session 	The session pointer. 
	 * @param fid		ID of the library table entry that has been added. 
	 * @param phonemes	Phonetic data return from external DB
				normalized_metadata
	 * @return 		0 on success.
	 * @return 		-1 on failure.
	 */
	int	(*fid_changed)(pdbp_session_t *session, uint64_t fid, gns_album_representation_t *representation);

	/** 
	 * Function to indicate the removal of a library table entry. Not optional.
	 *  
	 * @param session	The session pointer. 
	 * @param fid		ID of the library table entry that has been removed. 
	 * @return		0 on success.
	 * @return		-1 on failure.
	 */
	int	(*fid_removed)(pdbp_session_t *session, uint64_t fid);

} pdbp_table_t;

__END_DECLS

#endif /* __PDBP_API_H__ */

__SRCVERSION("pdbp_api.h $Rev: $");
