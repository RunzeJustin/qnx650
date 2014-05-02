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


#ifndef __AOA__H_
#define __AOA__H_

#include <stdint.h>
#include <stdbool.h>

/* Mask of possible Endpoints connections */
#define AOA_EPT_ACCESSORY_BULKIN		0x0001
#define AOA_EPT_ACCESSORY_BULKOUT		0x0002
#define AOA_EPT_ACCESSORY_CONTROL		0x0004

/* Mask of Supported Modes */
#define AOA_MODE_ACCESSORY			0x0001
#define AOA_MODE_AUDIO				0x0002
#define AOA_MODE_DEBUG				0x0004

/* Timeout values */
#define AOA_TIMEOUT_DEFAULT			0x00000000
#define AOA_TIMEOUT_INFINITY			0xffffffff

__BEGIN_DECLS

enum {
	AOA_EOK,		/* No error */
	AOA_ECFG,		/* XML configuration error */
	AOA_ENOCFG,		/* Missing configuration error */
	AOA_EMEM,		/* Memory allocation error */
	AOA_EUSBPERM,		/* Invalid permissions error */
	AOA_EUSBURB,		/* USB URB creation error */
	AOA_EUSBPIPE,		/* USB pipe creation error */
	AOA_EUSBMEM,		/* USB memory creation error */
	AOA_EUSBSETUP,		/* USB transfer setup error */
	AOA_EUSBIO,		/* USB I/O error */
	AOA_EUSBTIMEOUT,	/* USB transfer timeout error */
	AOA_ELOCK,		/* Locking error */
	AOA_ESIGNAL,		/* Signaling error */
	AOA_EUSBCONNECT,	/* USB connection error */
	AOA_EDEVEXIST,		/* Device does not exist error */
	AOA_EDEVEPT,		/* Invalid device endpoint error */
	AOA_EDEVNOSUP,		/* Device not supported error */
	AOA_EPARAM,		/* Invalid parameter error */
	AOA_EINVALIDHDL,	/* Handle invalidated error */

	AOA_ERROR_COUNT
};

/* Opaque handle */
typedef struct aoa_hdl_s aoa_hdl_t;

/*
 * Callback function prototype used for notifying the caller of any available
 * USB data when it becomes available.  A callback can be enabled by calling
 * aoa_set_rx_callback().
 */
typedef void (*data_clbk_t)( aoa_hdl_t *hdl, uint8_t *data, uint32_t sz, uint32_t status, const void *udata );

/*
 * This function is used to define a callback function which will be called when
 * USB data becomes avaiable or a send has completed.  A call to an aoa_*_rx() or
 * aoa_*_tx() function still needs to be made following a call to this function in
 * order enable a USB transfer.  To disable callbacks, simply pass in a callback
 * function of NULL.
 *
 * Note:  Once data has been consumed in the callback function, a subsequent call
 *        to aoa_*_rx() must be made if more USB data is required.
 *
 * @param hdl		A valid AOA handle.
 * @param clbk		The function to call back into when data is available.
 * @param udata		User data which will get passed to the call back function.
 * @param endpoint	The USB endpoint to set the transfer for.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error.
 */
int aoa_set_callback( aoa_hdl_t *hdl, data_clbk_t clbk, const void *udata, uint32_t endpoint );

/*
 * This function is used to check whether a handle is still valid.  When a device gets
 * disconnected, the handle will automatically be invalidated.  Calls to any of the
 * aoa_*_rx() or  aoa_*_tx() functions will notify us if the handle has been invalidated
 * as well.
 *
 * @param hdl		A valid AOA handle.
 * @param valid		Pointer to a boolean to return the response.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_get_valid( aoa_hdl_t *hdl, bool *valid );

/*
 * This function is used to get a bitmask of available modes which the device supports
 * Currently only accessory and audio mode are available which can be controlled via
 * the aoa.cfg file.
 *
 * @param hdl		A valid AOA handle.
 * @param mode		A pointer to return the mode mask in.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_get_mode_mask( aoa_hdl_t *hdl, uint32_t *modes );

/*
 * This function is used to get a bitmask of available endpoints which the device
 * supports in its current mode.
 *
 * @param hdl		A valid AOA handle.
 * @param endpoints	A pointer to return the endpoint mask in.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_get_endpoint_mask( aoa_hdl_t *hdl, uint32_t *endpoints );

/*
 * This function is used to return the maximum data packet size for a specific endpoint.
 * Data being returned will never be larger than this value for one transfer
 *
 * @param hdl		A valid AOA handle.
 * @param endpoints	The endpoint to get the size for.
 * @param sz		A pointer to a integer to store the value in.
 *
 * @return	0 on success.
 * @return	errno on failure.
 */
int aoa_get_endpoint_bufsz( aoa_hdl_t *hdl, uint32_t endpoint, uint32_t *sz );

/*
 * This function is used to get the current Android Open Accessory protocol supported
 * by the connected device.  Currently devices will return either 1.0 or 2.0.
 *
 * @param hdl		A valid AOA handle.
 * @param protocol	A pointer to return the protocol in.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_get_protocol( aoa_hdl_t *hdl, uint16_t *protocol );

/*
 * This function is used to transmit data to a control endpoint.  If the buffer is larger than the
 * endpoint packet size, multiple sends will be performed.
 *
 * @param hdl		A valid AOA handle.
 * @param endpoint	The endpoint to send to.
 * @param timeout	The USB timeout value for the transmission in ms.
 * @param request	The USB reequest value (refer to USB docs).
 * @param value		The USB value (refer to USB docs).
 * @param index		The USB index (refer to USB docs).
 * @param addr		A pointer to the data to send.
 * @param len		The size of the buffer to send and how much data was sent (in/out).
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_control_tx( aoa_hdl_t *hdl, uint32_t endpoint, uint32_t timeout, uint16_t request, uint16_t value, uint16_t index, uint8_t *addr, uint32_t *len );

/*
 * This function is used to receive data from a control endpoint.  Control transmissions
 * are always blocking so no callbacks can be configured for a control endpoint.
 *
 * Note: The return data is not owned by the caller and must be copied if it is to be
 *       modified in any way.
 *
 * @param hdl		A valid AOA handle.
 * @param endpoint	The endpoint to send to.
 * @param timeout	The USB timeout value for the transmission in ms.
 * @param request	The USB request value (refer to USB docs).
 * @param value		The USB value (refer to USB docs).
 * @param index		The USB index (refer to USB docs).
 * @param addr		A pointer to a pointer to the return buffer.
 * @param len		The size of the return buffer.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_control_rx( aoa_hdl_t *hdl, uint32_t endpoint, uint32_t timeout,  uint16_t request, uint16_t value, uint16_t index, uint8_t **addr, uint32_t *len );

/*
 * This function is used to transmit data to a bulk endpoint.  If the buffer is larger
 * than the endpoint packet size, multiple sends will be performed.
 *
 * @param hdl		A valid AOA handle.
 * @param endpoint	The endpoint to send to.
 * @param timeout	The USB timeout value for the transmission in ms.
 * @param addr		A pointer to the data to send.
 * @param len		The size of the buffer to send and how much data was sent (in/out).
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_bulk_tx( aoa_hdl_t *hdl, uint32_t endpoint, uint32_t timeout, uint8_t *addr, uint32_t *len );

/*
 * This function is used to receive data from a bulk endpoint.  The transmission can
 * either be synchronous or asynchronous depending on whether a callback was defined
 * via aoa_set_rx_callback() or not.
 *
 * Note: The return data is not owned by the caller and must be copied if it is to be
 *       modified in any way.
 *
 * @param hdl		A valid AOA handle.
 * @param endpoint	The endpoint to send to.
 * @param timeout	The USB timeout value for the transmission in ms.
 * @param addr		A pointer to a pointer to the return buffer.
 * @param len		The size of the return buffer.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_bulk_rx( aoa_hdl_t *hdl, uint32_t endpoint, uint32_t timeout, uint8_t **addr, uint32_t *len );


/*
 * This function is used to unregister from a particular cofinguration ID defined in
 * the aoa.cfg.
 *
 * @param cfg_id	The accessory identifier from aoa.cfg.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_unregister( const char *cfg_id );

/*
 * This function is used to register a particular accessory defined in the aoa.cfg.
 * If a matching accessory is found, the proper control strings will be sent to the
 * device to have it re-enumerate itself on the USB bus as an Android Accessory.
 * Once it comes back on the bus in accessory mode, the library will attach to it will
 * be available for communication.
 *
 * @param ctrl_clbk	A callback function to run when a registered device is found.
 * @param udata		User defined data to be passed into the callback.
 * @param cfg_id	The accessory ID to register for found in aoa.cfg.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_register( void (*ctrl_clbk)(aoa_hdl_t *hdl, const void *udata), const void *udata, const char *cfg_id );

/*
 * This function is used to shutdown the library.  This call will block until all
 * callback functions which are called when a device becomes available have exited.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_shutdown( void );

/*
 * This function is used to connect to the USB stack.  It should be called after all
 * devices are registered.
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error.
 */ 
int aoa_connect( void );

/*
 * This function is used to intialize the library.  A configuration is required to
 * handle device discovery and can be supplied here or left NULL to use the default
 * location of /etc/mm/aoa.cfg,
 *
 * @param cfg_path	The configuration path to use (NULL for default).
 *
 * @return	AOA_ERR_OK on success.
 * @return	AOA_ERR_* on error;
 */
int aoa_init( const char *cfg_path );

/*
 * This function is used to return a string representation of the AOA_ERR_* value returned
 * by the AOA library.
 *
 * @return	Error string on success.
 * @return	'Unknown error' on invalid error.
 */
const char *aoa_err2str( int error );

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/aoa/lib/public/aoa/aoa.h $ $Rev: 733727 $")
#endif
