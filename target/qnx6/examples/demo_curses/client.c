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


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "apis.h"

#include <unistd.h>
#include <sys/usbdi.h>

#define CFG_PATH	"/etc/mm/aoa.cfg"	/* Our configuration path */
#define CONFIG_ID	"NEXUS"			/* The name of the device we want to register (must match config) */
#define BUF_SZ		1024			/* Our maximum buffer size */


static const char	*dev_names[] = { CONFIG_ID };

/* Possible modes returned from the mode mask */
static const char *modes[] = {
	"Accessory",
	"Audio",

	NULL
};

/* Possible endpoints returned from the endpoint mask */
static const char *endpoints[] = {
	"Accessory BULK-IN",
	"Accessory BULK-OUT",
	"Accessory Control"
};


/*
 * This function is used to print an incoming message to the console window.
 */
static int print_data( const char *header, const uint8_t *data, uint32_t len ) {
	char	buf[BUF_SZ];
	size_t	sz;

	if ( len > 0 && *data ) {
		memcpy( buf, data, (sz = min(len, sizeof(buf) - 1)) );
		buf[sz] = '\0';
		write_console( "%s: > %s\n", header, buf );
	}
	else {
		write_console( "%s: >\n", header );
	}

	return 0;
}

/*
 * This function is used to print a list of masked names to the console window.
 */
static int print_list( const char *header, const char **array, uint32_t mask ) {
	int	i = 0;

	write_console( "%s", header );
	while ( array[i] ) {
		if ( mask & (1 << i) ) {
			write_console( "%s%s", (i == 0) ? " " : ", ",  array[i] );
		}
		i++;
	}
	write_console( "%s", "\n" );

	return 0;
}

/*
 * This function is used for USB transmission callbacks.  It will be called when
 * the transmission is complete.
 */
static void tx_clbk( aoa_hdl_t *hdl, uint8_t *data, uint32_t len, uint32_t status, const void *udata ) {
	if ( status != AOA_EOK ) {
		write_console( "%s: Error sending data: (%s).\n", get_device_name(hdl), aoa_err2str(status) );

		/* There was an error, let's stop handling the device */
		remove_device( hdl, false );
	}

	return;
}

/*
 * This function is used for USB receive callbacks.  It will be called when data
 * is received.  We handle three different messages: position of the slider 's',
 * the current color 'c' and a new message 'm'.  Notw how we make another request
 * for a receive after handling the data.  The library does not queue up data.
 */
static void rx_clbk( aoa_hdl_t *hdl, uint8_t *data, uint32_t len, uint32_t status, const void *udata ) {
	int		rc;

	if ( status == AOA_EOK ) {
		if ( data ) {
			/* If there's data, handle it based on the control byte */
			switch (*data) {
			case 't':
				/* Print incoming text */
				print_data( get_device_name(hdl), data + 1, len - 1 );
				break;
			case 's':
				/* Move the slider */
				write_slider( hdl, (int)data[1] );
				break;
			case 'c':
				/* Select the proper color */
				write_color( hdl, (int)data[1] );
				break;
			default:
				break;
			}
		}

		/* Setup for another non-blocking asynchronous callback */
		rc = aoa_bulk_rx( hdl, AOA_EPT_ACCESSORY_BULKIN, AOA_TIMEOUT_INFINITY, NULL, 0 );
		if ( rc != AOA_EOK ) {
			if ( rc == AOA_EINVALIDHDL ) {
				write_console( "%s: Device disconnected.\n", get_device_name(hdl) );
			}
			else {
				write_console( "%s: Error setting up a data callback: (%s).\n", get_device_name(hdl), aoa_err2str(rc) );
			}
			/*
			 * We need to have our ncurses module handle the removal
			 * as this device might be active.
			 */
			remove_device( hdl, false );
		}
	}
	else {
		write_console( "%s: Error receiving data: (%s).\n", get_device_name(hdl), aoa_err2str(status) );
		/*
		 * We need to have our ncurses module handle the removal
		 * as this device might be active.
		 */
		remove_device( hdl, false );
	}

	return;
}

/*
 * This is the main execution thread and will be called if a device matches our
 * registered device.  Once this thread is complete, the handle is destroyed
 * so we add a barrier to the end of this function and control when we want it
 * to end.
 */
static void run( aoa_hdl_t *hdl, const void *udata ) {
	int		rc;
	char		buf[32];
	acc_t		*dev = NULL;
	uint16_t	proto;
	uint32_t	mask;
	const char	*name;

	write_console( "%s: Device found, application is running...\n", (const char*)udata );

	/*
	 * Let's make our sends non-blocking as we're going to be using a mutex around them and
	 * don't want to block on USB errors.
	 */
	rc = aoa_set_callback( hdl, &tx_clbk, udata, AOA_EPT_ACCESSORY_BULKOUT );
	if ( rc == -1 ) {
		write_console( "%s: Error setting up asynchronous callback: (%s).\n", (const char*)udata, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		return;
	}

	/*
	 * Wait for incoming data in a new thread.  Let's do this before we add the device
	 * as an addition will promptly make a request for data
	 */
	rc = aoa_set_callback( hdl, &rx_clbk, udata, AOA_EPT_ACCESSORY_BULKIN );
	if ( rc == -1 ) {
		write_console( "%s: Error setting up asynchronous callback: (%s).\n", (const char*)udata, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		return;
	}
	rc = aoa_bulk_rx( hdl, AOA_EPT_ACCESSORY_BULKIN, AOA_TIMEOUT_INFINITY, NULL, 0 );
	if ( rc == -1 ) {
		write_console( "%s: Error requesting data: (%s).\n", (const char*)udata, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		return;
	}

	/* Add this device to our list of devices */
	dev = add_device( hdl, (const char*)udata );
	if ( !dev ) {
		write_console( "%s: Too many devices connected, ignoring\n", (const char*)udata );
		remove_device( dev->hdl, false );
		return;
	}
	name = get_device_name(hdl);

	/* Get a mask of supported modes (audio/accesory/debug) */
	rc = aoa_get_mode_mask( hdl, &mask );
	if ( rc == -1 ) {
		write_console( "%s: Error getting mode mask: (%s).\n", name, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		goto cleanup;
	}
	snprintf( buf, sizeof(buf), "%s: Modes:", name );
	print_list( buf, modes, mask );

	/* Get a mask of endpoints which we can send/receive on */
	rc = aoa_get_endpoint_mask( hdl, &mask );
	if ( rc == -1 ) {
		write_console( "%s: Error getting endpoint mask: (%s).\n", name, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		goto cleanup;
	}
	snprintf( buf, sizeof(buf), "%s: Endpoints:", name );
	print_list( buf, endpoints, mask );

	/* Get the protocol supported by the device (1 or 2) */
	rc = aoa_get_protocol( hdl, &proto );
	if ( rc == -1 ) {
		write_console( "%s: Error getting protocol: (%s).\n", name, aoa_err2str(rc) );
		remove_device( dev->hdl, false );
		goto cleanup;
	}
	write_console( "%s: Device Protocol: %d\n", name, proto );

	/*
	 * The handle will get invalidated as soon as this function returns so we need to keep
	 * it alive to keep our blocking receives alive until we no longer require the handle.
	 */
cleanup:
	pthread_mutex_lock( &dev->mutex );
	while ( dev->shutdown == 0 ) {
		pthread_cond_wait( &dev->cond, &dev->mutex );
	}

	/* We're all done with the device, let's clean up */
	destroy_device( dev );
	return;
}

/*
 * This function is used to clean up.  Currently is simply calls into the ncurses
 * module to cleanup the windows
 */
static int shutdown( void ) {
	/* Clean up our ncurses windows */
	destroy_windows();

	return 0;
}

/*
 * This function is used to initialize things.  This includes creating our ncurses
 * windows, initializing the AOA library, registering our devices, starting USB,
 * etc.
 */
static int startup( void ) {
	int	rc;

	/* Setup our ncurses windows */
	rc = setup_windows( );
	if ( rc == -1 ) {
		return -1;
	}

	/* Initialize the library */
	rc = aoa_init( CFG_PATH );
	if ( rc != AOA_EOK ) {
		destroy_windows();
		fprintf( stderr, "Unable to initialize AOA library (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	/* Register our devices */
	rc = aoa_register( &run, (const void *)dev_names[0], dev_names[0] );
	if ( rc != AOA_EOK ) {
		destroy_windows();
		fprintf( stderr, "Unable to register device: (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	rc = aoa_connect();
	if ( rc != AOA_EOK ) {
		destroy_windows();
		fprintf( stderr, "Unable to connect: (%s)\n", aoa_err2str(rc) );
		return -1;
	}

	return 0;
}

/*
 * This function is used to handle the SIGTERM and the SIGWINCH signals.  We don't
 * currently handle terminal resizes (SIGWINCH) so it will effectively shutdown
 * the application as well.
 */
static void sig_handler( int sig_no ) {
	if ( sig_no == SIGWINCH ) {
		/* Resize signal found */
		set_resize();
	}
	else {
		/* Unregister our device so no new connections come in */
		aoa_unregister( (const void *)dev_names[0] );

		/* Tell ncurses module to unblock/shutdown */
		set_shutdown();
	}
}

int send_data( acc_t *dev, uint8_t *buf, uint8_t ctrl, uint8_t val, uint32_t sz ) {
	int		rc;
	uint8_t		*pbuf = buf;
	uint8_t		tbuf[2];

	if ( !dev ) {
		return 0;
	}

	/* If we aren't sending a buffer, we're sending 2 bytes (control and data). */
	if ( !pbuf ) {
		pbuf = tbuf;
		tbuf[0] = ctrl;
		tbuf[1] = val;
		sz = 2;
	}

	/* Send the data to the device */
	rc = aoa_bulk_tx( dev->hdl, AOA_EPT_ACCESSORY_BULKOUT, AOA_TIMEOUT_DEFAULT, pbuf, &sz );
	if ( rc != AOA_EOK ) {
		if ( rc == AOA_EINVALIDHDL ) {
			write_console( "%s: Device disconnected.\n", get_device_name(dev->hdl) );
		}
		else {
			write_console( "%s: Error sending data to the device: (%s).\n", get_device_name(dev->hdl), aoa_err2str(rc) );
		}

		/* Regardless of error, let's remove the device.  We could also try re-sending here */
		remove_device( dev->hdl, true );
		return -1;
	}

	return 0;
}

int main( int argc, const char *argv[] ) {
	int	rc;

	/* Let's handle the interrupt signal via a handler */
	signal( SIGINT, &sig_handler );
	signal( SIGWINCH, &sig_handler );

	/* Connect and register for a specific device */
	rc = startup();
	if ( rc == -1 ) {
		return -1;
	}

	/*
	 * Blocking loop until SIGINT is received and the
	 * loop broken.
	 */
	read_loop();

	/*
	 * Let's make sure all of our worker threads exit as we have a
	 * barrier and aoa_shutdown() will block until the point where
	 * they have all exited.
	 */
	unblock_worker_threads();

	/*
	 * Shutdown the AOA library which will block until all worker
	 * threads have properly exited.
	 */
	aoa_shutdown();

	/* Do some final cleanup work (ncurses, condvars/mutexes, memory, etc.) */
	shutdown();

	return 0;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/aoa/examples/demo_curses/client.c $ $Rev: 734140 $")
#endif
