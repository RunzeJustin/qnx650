/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
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

#include <aoa/aoa.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define CFG_PATH	"/etc/mm/aoa.cfg"	/* Our configuration path */
#define CONFIG_ID	"NEXUS"			/* The name of the device we want to register (must match config) */

/*
 * This is the main execution thread and will be called if a device matches our
 * registered device.  Once this thread is complete, the handle is destroyed.
 */
static void run( aoa_hdl_t *hdl, const void *udata ) {
	int rc;
	uint8_t *buf;
	uint32_t bufsz;

	printf("ENTER run(hdl %p, udata %p)\n", hdl, udata);

	/* This is a blocking read as the callback functions haven't been setup.
	 * The intention here is to keep this thread running while the device
	 * is connected.
	 */
	while ((rc = aoa_bulk_rx( hdl, AOA_EPT_ACCESSORY_BULKIN, AOA_TIMEOUT_INFINITY, &buf, &bufsz)) == AOA_EOK) {
		printf("Handle %p read %d bytes.\n", hdl, bufsz);
	}
	printf("Error calling aoa_bulk_rx(hdl %p): %s (%d)\n", hdl, aoa_err2str(rc), rc);

	printf(" EXIT run(hdl %p)\n", hdl);
	return;
}

int main( int argc, const char *argv[] ) {
	int	rc;

	/* Initialize the library */
	rc = aoa_init( CFG_PATH );
	if ( rc != AOA_EOK ) {
		fprintf( stderr, "Unable to initialize AOA library (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	/* Register our devices */
	rc = aoa_register( &run, NULL, CONFIG_ID );
	if ( rc != AOA_EOK ) {
		fprintf( stderr, "Unable to register device: (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	/* Connect to USB stack */
	rc = aoa_connect();
	if ( rc != AOA_EOK ) {
		fprintf( stderr, "Unable to connect: (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	/* Wait for signal to quit */
	int sig;
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGTERM);
	sigwait(&sigset, &sig);

	/* Shutdown AOA library */
	aoa_shutdown();

	return 0;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/aoa/examples/aoa_swaponly/swaponly.c $ $Rev: 735812 $")
#endif
