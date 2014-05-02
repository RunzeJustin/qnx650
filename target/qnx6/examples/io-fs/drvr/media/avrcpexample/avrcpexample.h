/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. All Rights Reserved.
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

#ifndef AVCP_H_INCLUDED
#define AVCP_H_INCLUDED

#ifndef DEVICE_T
#define DEVICE_T struct avrcp_device
#endif

#include <inttypes.h>
#include "media.h"

#define AVRCP_NAME        "AVRCPEXAMPLE"
#define NAME_BUF_SIZE     512
#define AVCP_METADATA_MAX 1024

/* Principal device structure. 
   This structure can be extended to hold data about the underlying device.
*/
struct avrcp_device {
	struct mediafsdevice        mediafs;    // Always needs to be present and first, 
	                                        // this is an opaque sturcture.

	char *                      devpath;    // Pathname to the avcp device resource manager.
	int                         fd;         // fd connection to device resource manager, 
	                                        // or -1 if not connected.

	char                        dname[AVCP_METADATA_MAX];   // Bluetooth Friendly name.
	char                        dserial[AVCP_METADATA_MAX]; // Bluetooth Address (used as serial).
	uint16_t                    verbose;    // Log level verbosity.
	unsigned                    track_index;   // Track Index of current song.
	unsigned                    meta_sequence; // Current metadata sequence number.
};

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/drvr/media/avrcpexample/avrcpexample.h $ $Rev: 680892 $")
#endif
