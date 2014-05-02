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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/iomsg.h>
#include <sys/siginfo.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

#include <mmsync/mmsyncclient.h>

#define EVENT_PULSE_CODE _PULSE_CODE_MINAVAIL+5

#define LOG(fmt, ...)   printf(fmt"\n", ##__VA_ARGS__)

void print_usage() {
	printf("Usage:\n");
	printf("\tmmsyncclient [-e] <mmsync_dev> [<command> [<command_args>]]\n\n");
	printf("Options:\n");
	printf("\t-e\tEvent listen mode.\n\n");
	printf("Commands:\n");
	printf("\t%-26s%s", "sync_start",		"<db> <mountpoint> <syncpath> <options>\n");
	printf("\t%-26s%s", "sync_suspend", 		"<op_id> [flags]\n");
	printf("\t%-26s%s", "sync_resume", 		"<op_id> [flags]\n");
	printf("\t%-26s%s", "sync_cancel", 		"<op_id> [flags]\n");
	printf("\t%-26s%s", "sync_status_get_byid",	"<op_id> [flags]\n");
	printf("\t%-26s%s", "sync_status_get_bydbname",	"<db_name> [flags]\n");
	printf("\t%s",	    "sync_status_get\n");
	printf("\t%-26s%s", "sync_status_get_dbname",	"<op_id> [flags]\n");
	printf("\t%-26s%s", "sync_debug_set",	"<verbose> <debug>\n");
	printf("\t%s",	    "sync_debug_get\n");
	printf("\t%-26s%s", "sync_control",		"<op_id> <extended_options> [flags]\n");
}

const char* getSyncErrorString(mmsync_sync_error_type_t type) {
	const char* ptr = "unknown sync error string";
	switch (type) {
	case MMSYNC_SYNC_ERROR_NONE:
		ptr = "none";
		break;
	case MMSYNC_SYNC_ERROR_MEDIABUSY:
		ptr = "media is busy";
		break;
	case MMSYNC_SYNC_ERROR_READ:
		ptr = "read";
		break;
	case MMSYNC_SYNC_ERROR_NETWORK:
		ptr = "network";
		break;
	case MMSYNC_SYNC_ERROR_UNSUPPORTED:
		ptr = "unsupported media";
		break;
	case MMSYNC_SYNC_ERROR_USERCANCEL:
		ptr = "user cancelled";
		break;
	case MMSYNC_SYNC_ERROR_NOTSPECIFIED:
		ptr = "not specified";
		break;
	case MMSYNC_SYNC_ERROR_LIB_LIMIT:
		ptr = "library limit reached";
		break;
	case MMSYNC_SYNC_ERROR_FOLDER_LIMIT:
		ptr = "folder limit reached";
		break;
	case MMSYNC_SYNC_ERROR_DATABASE:
		ptr = "database error";
		break;
	case MMSYNC_SYNC_ERROR_FOLDER_DEPTH_LIMIT:
		ptr = "folder depth limit reached";
		break;
	case MMSYNC_SYNC_ERROR_FOLDER_NONMEDIA_LIMIT:
		ptr = "folder non-media file limit reached";
		break;
	case MMSYNC_SYNC_ERROR_FOLDER_MEDIA_LIMIT:
		ptr = "folder media file limit reached";
		break;
	case MMSYNC_SYNC_ERROR_DB_LIMIT:
		ptr = "maximum db size reached";
		break;
	case MMSYNC_SYNC_ERROR_MEMORY_ALLOCATION:
		ptr = "memory allocation error";
		break;
	}
	return ptr;
}

void log_event(mmsync_event_type_t type, void* event_data) {
	switch (type) {
	case MMSYNC_EVENT_NONE:
		break;
	case MMSYNC_EVENT_MS_UPDATE:
		LOG("MMSYNC_EVENT_MS_UPDATE(Flags %u; Op ID: %u; files %llu/%llu; folders %llu/%llu; playlists %llu/%llu, playlist_items %llu, time %llu.)",
				((mmsync_ms_update_data_t*)event_data)->flags,
				((mmsync_ms_update_data_t*)event_data)->operation_id,
				((mmsync_ms_update_data_t*)event_data)->added_filecount,
				((mmsync_ms_update_data_t*)event_data)->pass_added_filecount,
				((mmsync_ms_update_data_t*)event_data)->added_foldercount,
				((mmsync_ms_update_data_t*)event_data)->pass_added_foldercount,
				((mmsync_ms_update_data_t*)event_data)->playlist_count,
				((mmsync_ms_update_data_t*)event_data)->pass_playlist_count,
				((mmsync_ms_update_data_t*)event_data)->playlist_item_count,
				((mmsync_ms_update_data_t*)event_data)->timestamp);
		break;
	case MMSYNC_EVENT_SYNCABORTED:
		LOG("MMSYNC_EVENT_SYNCABORTED(operation ID %u, error %u)",
				((mmsync_sync_data_t*)event_data)->operation_id,
				((mmsync_sync_data_t*)event_data)->error);
		break;
	case MMSYNC_EVENT_MS_SYNC_PENDING:
		LOG("MMSYNC_EVENT_MS_SYNC_PENDING(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_SYNC_STARTED:
		LOG("MMSYNC_EVENT_MS_SYNC_STARTED(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_1PASSCOMPLETE:
		LOG("MMSYNC_EVENT_MS_1PASSCOMPLETE(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_2PASSCOMPLETE:
		LOG("MMSYNC_EVENT_MS_2PASSCOMPLETE(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_3PASSCOMPLETE:
		LOG("MMSYNC_EVENT_MS_3PASSCOMPLETE(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_SYNCCOMPLETE:
		LOG("MMSYNC_EVENT_MS_SYNCCOMPLETE(operation ID %u)",
				((mmsync_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_SYNCFIRSTFID:
		LOG("MMSYNC_EVENT_MS_SYNCFIRSTFID(%llu, operation ID %u)",
				((mmsync_first_fid_data_t*)event_data)->fid,
				((mmsync_first_fid_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_SYNC_FIRST_EXISTING_FID:
		LOG("MMSYNC_EVENT_MS_SYNC_FIRST_EXISTING_FID(%llu, operation ID %u, count %u)",
				((mmsync_first_fid_data_t*)event_data)->fid,
				((mmsync_first_fid_data_t*)event_data)->operation_id,
				((mmsync_first_fid_data_t*)event_data)->count);
		break;
	case MMSYNC_EVENT_SYNC_ERROR:
		LOG("MMSYNC_EVENT_SYNC_ERROR(%s; opid: %u; param: %u)",
				getSyncErrorString(((mmsync_sync_error_t*)event_data)->type),
				((mmsync_sync_error_t*)event_data)->operation_id,
				((mmsync_sync_error_t*)event_data)->param);
		break;
	case MMSYNC_EVENT_SYNC_SKIPPED:
		LOG("MMSYNC_EVENT_SYNC_SKIPPED(%lld)",
				*(uint64_t*)event_data);
		break;
	case MMSYNC_EVENT_SHUTDOWN:
		LOG("MMSYNC_EVENT_SHUTDOWN");
		break;
	case MMSYNC_EVENT_SHUTDOWN_COMPLETED:
		LOG("MMSYNC_EVENT_SHUTDOWN_COMPLETED");
		break;
	case MMSYNC_EVENT_MS_SYNC_FOLDER_STARTED:
		LOG("MS_SYNC_FOLDER_STARTED(Operation ID %u; folder %llu, pass %u)",
				((mmsync_folder_sync_data_t*)event_data)->operation_id,
				((mmsync_folder_sync_data_t*)event_data)->folderid,
				((mmsync_folder_sync_data_t*)event_data)->pass);
		break;
	case MMSYNC_EVENT_MS_SYNC_FOLDER_COMPLETE:
		LOG("MS_SYNC_FOLDER_COMPLETE(Operation ID %u; folder %llu, pass %u, files %u, folders %u, playlists %u)",
				((mmsync_folder_sync_data_t*)event_data)->operation_id,
				((mmsync_folder_sync_data_t*)event_data)->folderid,
				((mmsync_folder_sync_data_t*)event_data)->pass,
				((mmsync_folder_sync_data_t*)event_data)->num_files,
				((mmsync_folder_sync_data_t*)event_data)->num_folders,
				((mmsync_folder_sync_data_t*)event_data)->num_playlists);
		break;
	case MMSYNC_EVENT_MS_SYNC_PRIORITY_FOLDER_STARTED:
		LOG("MS_SYNC_PRIORITY_FOLDER_STARTED(folder %llu, pass %u, operation id %u)",
				 ((mmsync_folder_sync_data_t*)event_data)->folderid,
				 ((mmsync_folder_sync_data_t*)event_data)->pass,
				 ((mmsync_folder_sync_data_t*)event_data)->operation_id);
		break;
	case MMSYNC_EVENT_MS_SYNC_PRIORITY_FOLDER_COMPLETE:
		LOG("MS_SYNC_PRIORITY_FOLDER_COMPLETE(folder %llu, pass %u, operation id %u, files %u, folders %u, playlists %u)",
				 ((mmsync_folder_sync_data_t*)event_data)->folderid,
				 ((mmsync_folder_sync_data_t*)event_data)->pass,
				 ((mmsync_folder_sync_data_t*)event_data)->operation_id,
				 ((mmsync_folder_sync_data_t*)event_data)->num_files,
				 ((mmsync_folder_sync_data_t*)event_data)->num_folders,
				 ((mmsync_folder_sync_data_t*)event_data)->num_playlists);
		break;
	case MMSYNC_EVENT_MS_SYNC_FOLDER_CONTENTS_COMPLETE:
		LOG("MS_SYNC_FOLDER_CONTENTS_COMPLETE(Operation ID %u; folder %llu, pass %u, folders %u)",
				((mmsync_folder_sync_data_t*)event_data)->operation_id,
				((mmsync_folder_sync_data_t*)event_data)->folderid,
				((mmsync_folder_sync_data_t*)event_data)->pass,
				((mmsync_folder_sync_data_t*)event_data)->num_folders);
		break;
	case MMSYNC_EVENT_MS_SYNC_FOLDER_TRIM_COMPLETE:
		LOG("MS_SYNC_FOLDER_TRIM_COMPLETE(Operation ID: %u;"
				" folder %llu, del files %u, del folders %u, del pls %u, timestamp %llu)",
				((mmsync_folder_sync_data_t*)event_data)->operation_id,
				((mmsync_folder_sync_data_t*)event_data)->folderid,
				((mmsync_folder_sync_data_t*)event_data)->num_files,
				((mmsync_folder_sync_data_t*)event_data)->num_folders,
				((mmsync_folder_sync_data_t*)event_data)->num_playlists,
				((mmsync_folder_sync_data_t*)event_data)->timestamp);
		break;
		/*
		 * // NOTE: If you don't define a default, compiler will automatically give a compile warning for
		 * // additional types that are defined in this switch. This will ensure this list is up to date.
		 * default:
		 * LOG("MMSYNC_EVENT %d", type);
		 * break;
		 */
	case MMSYNC_EVENT_BUFFER_TOO_SMALL: // currently never delivered to this function, here for completeness.
		LOG( "MMSYNC_EVENT_BUFFER_TOO_SMALL");
		break;
	case MMSYNC_EVENT_DB_RESET:
	       LOG("MMSYNC_EVENT_DB_RESET(Operation ID: %u; timestamp %llu)",
				 ((mmsync_reset_sync_data_t*)event_data)->operation_id,
				 ((mmsync_reset_sync_data_t*)event_data)->timestamp);
		break;
	}
}

void listen_event(mmsync_hdl_t * hdl) {
	int chid, coid, rcvid;
	struct sigevent event;
	struct _pulse pulse;
	mmsync_event_t * mmsync_event;

	if ((chid = ChannelCreate(0)) == -1) {
		fprintf(stderr, "ChannelCreate() failed %d %s\n", errno,
				strerror(errno));
		exit(-1);
	}

	if ((coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		fprintf(stderr, "ConnectAttach() failed %d %s\n", errno,
				strerror(errno));
		exit(-1);
	}

	// fill in the event structure for a pulse
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, EVENT_PULSE_CODE, 0);

	mm_sync_events_register(hdl, &event);
	printf("Event listen mode, Ctrl + C to exit.\n");
	while (1) {
		if ((rcvid = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL)) != 0) {
			fprintf(stderr, "MsgReceivePulse() failed. rcvid=%d\n", rcvid);
			continue;
		}
		if (mm_sync_events_get(hdl, &mmsync_event) == -1) {
			fprintf(stderr, "mm_sync_events_get() failed %d %s\n", errno,
					strerror(errno));
			exit(-1);
		}

		log_event(mmsync_event->type, mmsync_event->data);
	}
}

static strm_dict_t *arg_to_dict(const char *arg) {
	char local_arg[strlen(arg) + 1];
	char *p, *key, *val = "";
	strm_dict_t *dict = strm_dict_new();

	strcpy(local_arg, arg);
	p = key = local_arg;

	while (*p) {
		switch(*p) {
		case '=':
			*p = '\0';
			p++;
			val = p;
			break;
		case ',':
			*p = '\0';
			if ((dict = strm_dict_set(dict, key, val)) == NULL)
				return NULL;
			p++;
			key = p;
			val = "";
			break;
		default:
			p++;
		}
	}

	if (*key) {
		dict = strm_dict_set(dict, key, val);
	}

	return dict;
}

int sync_start(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	const char *db, *mountpath, *syncpath;
	uint32_t options;
	int rc;
	strm_dict_t *extended_options = NULL;

	if (argc < 5) {
		print_usage();
		return -1;
	}
	db = argv[1];
	mountpath = argv[2];
	syncpath = argv[3];
	options = strtoul(argv[4], NULL, 0);
	if (argc > 5) {
		/* parse dict */
		extended_options = arg_to_dict(argv[5]);
	}

	rc = mm_sync_start(hdl, db, mountpath, syncpath, options, extended_options);
	if (rc >= 0) {
		printf("sync operation id: %d\n", rc);
	} else {
		printf("mm_sync_start() failed. %d\n", rc);
	}
	return rc;
}

#define	MMECLI_GET_SYNC_STATUS_SIZE	16
static int print_status(mmsync_status_t *status, size_t status_count) {
	int	i;
	int	min_count;

	min_count = min(status_count, MMECLI_GET_SYNC_STATUS_SIZE);
	printf("Found %d results; displaying %d:\n", status_count, min_count);

	for (i = 0; i < min_count; ++i) {
		printf("op_id: %u: Completed: %u; Current: %u; Pending: %u; Suspended: %s.\n",
				status[i].operation_id, status[i].passes_done,
				status[i].current_pass, status[i].passes_to_do,
				(status[i].flags & MM_SYNC_THREAD_IS_SUSPENDED) ? "Yes" : "No");
	}
	return 0;
}

int sync_status_get(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	int rc;
	mmsync_status_t status[MMECLI_GET_SYNC_STATUS_SIZE];

	rc = mm_sync_status_get(hdl, status, MMECLI_GET_SYNC_STATUS_SIZE, 0);
	if (rc > 0) {
		print_status(status,rc); 
	} else {
		printf("rc: %d, errno: %d\n", rc, errno);
	}
	return rc;
}

int sync_status_get_byid(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	int		op_id, rc;
	uint32_t	flags = 0;
	mmsync_status_t status;

	if (argc < 2) {
		print_usage();
		return -1;
	}
	if (argc > 2) {
		flags = strtoul(argv[2], NULL, 0);
	}
	op_id = strtoul(argv[1], NULL, 0);

	rc = mm_sync_status_get_byid(hdl, &status, op_id, flags);
	if (rc > 0) {
		print_status(&status,1); 
	} else {
		printf("rc: %d, errno: %d\n", rc, errno);
	}
	return rc;
}

int sync_status_get_bydbname(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	int		rc;
	char		*dbname;
	uint32_t	flags = 0;
	mmsync_status_t status;

	if (argc < 2) {
		print_usage();
		return -1;
	}
	if (argc > 2) {
		flags = strtoul(argv[2], NULL, 0);
	}
	dbname = argv[1];

	rc = mm_sync_status_get_bydbname(hdl, &status, dbname, flags);
	if (rc > 0) {
		print_status(&status,1);
	} else {
		printf("rc: %d, errno: %d\n", rc, errno);
	}
	return rc;
}

int sync_status_get_dbname( mmsync_hdl_t * hdl, int argc, char * argv[]) {
	char		buf[1024];
	int		op_id, rc;
	uint32_t	flags = 0;

	if (argc < 2) {
		print_usage();
		return -1;
	}
	if (argc > 2) {
		flags = strtoul(argv[2], NULL, 0);
	}

	op_id = strtoul(argv[1], NULL, 0);
	rc = mm_sync_status_get_dbname(hdl, op_id, buf, sizeof(buf), flags);
	if (rc == -1) {
		printf("rc: %d, errno: %d\n", rc, errno);
	}
	else {
		printf("rc: %d, errno: %d\n", rc, errno);
		printf( "Found dbname of \"%s\" for op_id=%d\n", buf, op_id);
	}

	return rc;
}

int sync_suspend(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	unsigned op_id;
	uint32_t flags = 0;
	int rc;
	if (argc < 2) {
		print_usage();
		return -1;
	}
	op_id = strtoul(argv[1], NULL, 0);
	if (argc > 2)
		flags = strtoul(argv[2], NULL, 0);
	rc = mm_sync_suspend(hdl, op_id, flags);
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int sync_resume(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	unsigned op_id;
	uint32_t flags = 0;
	int rc;
	if (argc < 2) {
		print_usage();
		return -1;
	}
	op_id = strtoul(argv[1], NULL, 0);
	if (argc > 2)
		flags = strtoul(argv[2], NULL, 0);
	rc = mm_sync_resume(hdl, op_id, flags);
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int sync_cancel(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	unsigned op_id;
	uint32_t flags = 0;
	int rc;
	if (argc < 2) {
		print_usage();
		return -1;
	}
	op_id = strtoul(argv[1], NULL, 0);
	if (argc > 2)
		flags = strtoul(argv[2], NULL, 0);
	rc = mm_sync_cancel(hdl, op_id, flags);
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int sync_debug_set(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	unsigned	verbose;
	uint32_t	debug;
	int 		rc;

	if (argc < 3) {
		print_usage();
		return -1;
	}
	verbose = strtoul(argv[1], NULL, 0);
	debug = strtoul(argv[2], NULL, 0);
	rc = mm_sync_debug_set(hdl, verbose, debug);
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int sync_debug_get(mmsync_hdl_t* hdl, int argc, char * argv[]) {
	uint8_t verbose;
	uint8_t debug;
	int     rc;

	rc = mm_sync_debug_get(hdl, &verbose, &debug);
	if(rc != -1) {
		printf("verbose level: %u, debug flags: 0x%.2x\n", verbose, debug);
	}
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int sync_control(mmsync_hdl_t * hdl, int argc, char * argv[]) {
	uint32_t op_id;
	uint32_t flags = 0;
	int rc;
	strm_dict_t *extended_options = NULL;

	if (argc < 3) {
		print_usage();
		return -1;
	}
	op_id = strtoul(argv[1], NULL, 0);
	/* parse dict */
	extended_options = arg_to_dict(argv[2]);
	if (argc > 3)
		flags = strtoul(argv[3], NULL, 0);

	rc = mm_sync_control(hdl, op_id, extended_options, flags);
	printf("rc: %d, errno: %d\n", rc, errno);
	return rc;
}

int main(int argc, char * argv[]) {
	const char *mmsync_dev;
	mmsync_hdl_t *hdl;
	int c;
	int event_mode = 0;

	while ((c = getopt(argc, argv, "e")) != -1) {
		switch (c) {
		case 'e':
			event_mode = 1;
			break;
		default:
			break;
		}
	}
	if (argc <= optind) {
		print_usage();
		return 0;
	}

	mmsync_dev = argv[optind];

	hdl = mm_sync_connect(mmsync_dev, 0);
	if (hdl == NULL) {
		perror("mm_sync_connect()");
		return -1;
	}

	if (argc <= optind + 1) {
		if (event_mode) {
			listen_event(hdl);
		} else {
			print_usage();
		}
		mm_sync_disconnect(hdl);
		return 0;
	}

	const char *mmsync_cmd = argv[optind + 1];
	static const struct {
		const char * cmd;
		int (*handler)(mmsync_hdl_t * hdl, int argc, char * argv[]);
	} hnd_table[] = {
			{ "sync_start",      sync_start },
			{ "sync_status_get", sync_status_get },
			{ "sync_status_get_byid", sync_status_get_byid },
			{ "sync_status_get_bydbname", sync_status_get_bydbname },
			{ "sync_status_get_dbname", sync_status_get_dbname },
			{ "sync_suspend", sync_suspend },
			{ "sync_resume", sync_resume },
			{ "sync_cancel", sync_cancel },
			{ "sync_debug_set", sync_debug_set },
			{ "sync_debug_get", sync_debug_get },
			{ "sync_control", sync_control },
	};

	int i;
	for (i = 0; i < sizeof(hnd_table) / sizeof(hnd_table[0]); i++) {
		if (strcmp(mmsync_cmd, hnd_table[i].cmd) == 0) {
			hnd_table[i].handler(hdl, argc - optind - 1, argv + optind + 1);
			break;
		}
	}

	if (i >= sizeof(hnd_table) / sizeof(hnd_table[0])) {
		printf("Unknown command: %s\n", mmsync_cmd);
	}

	if (event_mode) {
		listen_event(hdl);
	}
	mm_sync_disconnect(hdl);

	return 0;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/mm-sync/cli/mmsyncclient.c $ $Rev: 721150 $")
#endif
