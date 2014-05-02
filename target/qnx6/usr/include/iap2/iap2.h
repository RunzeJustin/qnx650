/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

/**
 @mainpage iAP2 iPod Library

This library provides functionality for all communications with
an iPod via IAP2. Two public header files are provided: iap2.h provides functions
to manage an iPod, and iap2_types.h defines constants and data types used
by the iPod interface.

*/

#ifndef _IAP2_H_INCLUDED
#define _IAP2_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _IAP2_TYPES_H_INCLUDED
#include <iap2/iap2_types.h>
#endif

#include <sys/strm.h>

__BEGIN_DECLS

/**
 * @brief Set up a connection between an application and the iPod driver
 *        server for iAP2 communication.
 *
 * @param path          Path to iPod mountpoint
 * @param flags         Reserved, set to 0
 *
 * @return A valid iPod server connection handle structure (@c iap2_hdl_t)
 * on success
 * @return NULL on error
 */
iap2_hdl_t * iap2_connect(const char *path, uint32_t flags);

/**
 * @brief Disconnect the iPod.
 *
 * Disconnect an application from the iPod driver server and releases the
 * iap2_hdl_t connection handle.
 *
 * @param hdl           iAP2 iPod driver server handle
 *
 * @return 0 on success
 * @return -1 on error
 */
int iap2_disconnect(iap2_hdl_t *hdl);

/**
 * @brief Send a play command to the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_play(iap2_hdl_t *hdl);

/**
 * @brief Send a pause command to the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_pause(iap2_hdl_t *hdl);

/**
 * @brief Jump to the next track/chapter in the playback engine of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_next(iap2_hdl_t *hdl);

/**
 * @brief Jump to the previous track/chapter in the playback engine of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_prev(iap2_hdl_t *hdl);

/**
 * @brief Activate fast forward on the current track on the iPod.
 *
 * NOTE: Use @c iap2_fastend() to end fast forward.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_fastfwd(iap2_hdl_t *hdl);

/**
 * @brief Activate fast backward on the current track on the iPod.
 *
 * NOTE: Use @c iap2_fastend() to end fast backward.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_fastbwd(iap2_hdl_t *hdl);

/**
 * @brief End fast forward or backward on the current track on the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int iap2_fastend(iap2_hdl_t *hdl);

/**
 * @brief Toggle the shuffle setting of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_shuffle(iap2_hdl_t *hdl);

/**
 * @brief Toggle the repeat setting of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_repeat(iap2_hdl_t *hdl);

/**
 * @brief Increase the volume of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * Note: Not applicable to digital audio.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_volup(iap2_hdl_t *hdl);

/**
 * @brief Decrease the volume of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 *
 * Note: Not applicable to digital audio.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_voldown(iap2_hdl_t *hdl);

/**
 * @brief Initialize a custom HID interface
 *
 * @param hdl           iAP2 iPod handle
 * @param name          Name of the HID interface matching the entry in the configuration file
 *
 * @return id for future hid access.
 * @return -1 on failure.
 */
int iap2_hid_init(iap2_hdl_t *hdl, const char *name);

/**
 * @brief Enable the custom HID interface
 *
 * @param hdl           iAP2 iPod handle
 * @param id            ID associated with the custom HID interface
 * @param data          The full HID report descriptor to use associated with this ID
 * @param size          Size of the HID descriptor
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_hid_start(iap2_hdl_t *hdl, uint16_t id, const uint8_t *data, size_t size);

/**
 * @brief Send a HID report
 *
 * @param hdl           iAP2 iPod handle
 * @param id            ID associated with the custom HID interface
 * @param desc          HID report to send
 * @param size          Size of the HID report
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_hid_sendreport(iap2_hdl_t *hdl, uint16_t id, const uint8_t *data, size_t size);

/**
 * @brief Disable the custom HID interface
 *
 * @param hdl           iAP2 iPod handle
 * @param id            ID associated with the custom HID interface
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_hid_stop(iap2_hdl_t *hdl, uint16_t id);


/**
 * @brief Set the current language on the iPod.
 *
 * @param hdl           iAP2 iPod handle
 * @param lang          New language to set
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_language_set(iap2_hdl_t *hdl, const char *lang);

/**
 * @brief Set the power settings of the iPod.
 *
 * @param hdl           iAP2 iPod handle
 * @param current       Available current for iPod
 * @param charge        Should iPod charge battery
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_power_set(iap2_hdl_t *hdl, uint16_t current, bool charge);

/**
 * @brief Retrieve the artwork associated with the currently playing track.
 *
 * @param hdl           iAP2 iPod handle
 * @param buf           Buffer to return the artwork data (jpeg)
 * @param buflen        Size of buffer
 *
 * Notes:
 *  - Can provide a buffer of size 0 to return the total size required.
 *  - If buffer provided, returns the number of bytes copied
 *
 * @return number of bytes required or bytes copied on success.
 * @return -1 on failure.
 */
int iap2_nowplay_getartwork(iap2_hdl_t *hdl, void *buf, size_t buflen);

/**
 * @brief Request the iPod to launch an application.
 *
 * @param hdl           iAP2 iPod handle
 * @param appid         Application ID to launch
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_app_launch(iap2_hdl_t *hdl, const char *appid);

/**
 * @brief Send NMEA sentence to the iPod.
 *
 * @param hdl           iAP2 iPod handle
 * @param nmea          NMEA sentence to send
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_gps_data_send(iap2_hdl_t *hdl, const char *nmea);

/*
 * @brief Request infomartion on all the Media Libraries present on the device.
 *
 * @param hdl           iAP2 iPod handle
 * @param info          Pointer to store the data
 *
 * Notes:
 *  This API will allocate memory on the caller's behalf.
 *  Use iap2_medialib_freeinfo() to free the memory.
 *
 * @returns the number of Media Libraries present on the device
 * @returns -1 on failure
 */
int iap2_medialib_getinfo(iap2_hdl_t *hdl, iap2_medialib_info_t **info);

/*
 * @brief Free the Media Libraries information structure.
 *
 * @param hdl           iAP2 iPod handle
 * @param info          Pointer that was used with iap2_medialib_getinfo()
 *
 * @returns 0 on success
 * @returns -1 on failure
 */
int iap2_medialib_freeinfo(iap2_hdl_t *hdl, iap2_medialib_info_t *info);

/**
 * @brief Resume playback of a specific Media Library.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media Library to resume
 *
 * Notes:
 *  - Can be used to resume a media library on the device when a 3rd party application has focus.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_play_resume(iap2_hdl_t *hdl, const char *library_uid);

/**
 * @brief Play a list of tracks.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media Library to play from
 * @param trk_uids      Array of Track UIDs to load the playback engine with
 * @param start_index   Index of the array to start playing from
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_play_tracks_str(iap2_hdl_t *hdl, const char *library_uid, const char **trk_uids, uint32_t ntrks, uint32_t start_index);

/**
 * @brief Play a list of tracks.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media Library to play from
 * @param trk_uids      Array of Track UIDs to load the playback engine with
 * @param start_index   Index of the array to start playing from
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_play_tracks_num(iap2_hdl_t *hdl, const char *library_uid, uint64_t *trk_uids, uint32_t ntrks, uint32_t start_index);

/**
 * @brief Play a collection.
 *
 * @param hdl               iAP2 iPod handle
 * @param library_uid       Media Library to play from
 * @param collection_uid    UID of the collection to play
 * @param type              Type of collection
 * @param start_index       Index of the track to start playing from
 *
 * Notes:
 *  - type = "Playlist", "Artist", "Album", "AlbumArtist", "Genre", "Composer"
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_play_collection(iap2_hdl_t *hdl, const char *library_uid, const char *collection_uid, const char *type, uint32_t start_index);

/*
 * @brief Start media library updates from the iPod.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media library uid
 * @param rev           Start revision (NULL for full sync)
 * @param trk_types     Types of metadata for Tracks (MEDIALIB_ITEM_*)
 * @param plist_types   Types of metadata for Playlists (MEDIALIB_PLIST_*)
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_sync_start(iap2_hdl_t *hdl, const char *library_uid, const char *lib_rev, uint32_t trk_types, uint32_t plist_types);

/*
 * @brief Move to next item for sync.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media library uid
 *
 * @returns iap2_medialib_sync_info_e:
 *  IAP2_MEDIALIB_NODATA
 *  IAP2_MEDIALIB_COMPLETE
 *  IAP2_MEDIALIB_RESET
 *  IAP2_MEDIALIB_REV
 *  IAP2_MEDIALIB_ITEM_ADD
 *  IAP2_MEDIALIB_PLIST_ADD
 *  IAP2_MEDIALIB_ITEM_DEL
 *  IAP2_MEDIALIB_PLIST_DEL
 *  IAP2_MEDIALIB_PLIST_CONTENT
 *  IAP2_MEDIALIB_PLIST_CONTENTEND
 *
 * @return -1 on failure.
*/
iap2_medialib_sync_info_e iap2_medialib_next(iap2_hdl_t *hdl, const char *library_uid);

/*
 * @brief Get associated data for an item.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media library uid
 * @param type          Data to retrieve (depends on current item type; see iap2_medialib_next()
 *
 * Note: The data returned is not owned by the caller, and is only valid up until medialib_next() is called.
 * @returns string representation of data
 */
const char * iap2_medialib_getdata(iap2_hdl_t *hdl, const char *library_uid, uint32_t type);

/*
 * @brief Stop media library updates from the iPod.
 *
 * @param hdl           iAP2 iPod handle
 * @param library_uid   Media library uid
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_medialib_sync_stop(iap2_hdl_t *hdl, const char *library_uid);

/*
 * @brief Get audio URL used for reading in the iPod PCM data.
 *
 * @param hdl           Handle to the iPod
 * @param buf           Buffer to store the url into
 * @param buflen        Length of the buffer
 *
 * @return number of bytes needed to store the full URL on success.
 * @return -1 on failure.
 */
int iap2_devaudio_geturl(iap2_hdl_t *hdl, void *buf, size_t buflen);

/*
 * @brief Start USB device side audio
 *
 * @param hdl           iAP2 iPod handle
 *
 * Note: This can only be used when the accessory is the USB host.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_devaudio_start(iap2_hdl_t *hdl);

/*
 * @brief Stop USB device side audio
 *
 * @param hdl           iAP2 iPod handle
 *
 * Note: This can only be used when the accessory is the USB host.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_devaudio_stop(iap2_hdl_t *hdl);

/*
 * @brief Send vehicle parameters
 *
 * @param hdl           Handle to the iPod
 * @param dict
 *
 * @ return
 */
int iap2_vehicle_update(iap2_hdl_t *hdl, strm_dict_t *dict);

/**
 * @brief Claims the session associated with the specified protocol.
 *        If no sessions are ready, this will block until a session is
 *        initiated by the device.
 *
 * @param path          Path to iPod mountpoint
 * @param protocol      Protocol Name
 * @param flags         Reserved, set to 0
 *
 * @return A valid iPod server connection handle structure (@c iap2_hdl_t)
 * on success
 * @return NULL on error
 */
iap2ea_hdl_t * iap2_eap_open(const char *path, const char *protocol, uint32_t flags);

/**
 * @brief Free all internal resources related to a session. Note the driver will
 *        discard all data transfered from the iPod for this session.
 *
 * @param hdl          iAP2 iPod handle
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int iap2_eap_close(iap2ea_hdl_t *ehdl);

/**
 * @brief Send data to the Apple device
 *
 * @param hdl           iAP2 iPod handle
 * @param buf           Data to send
 * @param buflen        Size of the buffer
 *
 * @return 0 for success.
 * @return -1 on failure.
 */
int iap2_eap_send(iap2ea_hdl_t *ehdl, void *buf, size_t buflen);

/**
 * @brief Retrieves data sent by the Apple device
 *
 * @param hdl           iAP2 iPod handle
 * @param buf           Buffer to store data
 * @param buflen        Size of the buffer
 *
 * @return number of bytes copied to buffer
 * @return -1 on failure.
 */
int iap2_eap_recv(iap2ea_hdl_t *ehdl, void *buf, size_t buflen);

/**
 * @brief Arm for input notifications.
 *
 * @param hdl           iAP2 iPod handle
 * @param event         Event to send for notification
 *
 * @return 0 if successfully armed
 * @return 1 if data is available (not armed)
 * @return -1 on failure.
 */
int iap2_eap_event_arm(iap2ea_hdl_t *ehdl, struct sigevent const *sev);

/**
 * @brief Retrieve the data associated with the specified ID published by PPS.
 *        This can be the vCard identifier or Album Artwork identifier
 *
 * @param hdl           iAP2 iPod handle
 * @param buf           Buffer to return the data
 * @param buflen        Size of buffer
 *
 * Notes:
 *  - Can provide a buffer of size 0 to return the total size required.
 *  - If buffer provided, returns the number of bytes copied
 *
 * @return number of bytes required or bytes copied on success.
 * @return -1 on failure.
 */
int iap2_filexfer_read(iap2_hdl_t *hdl, uint8_t id, void *buf, size_t buflen);

__END_DECLS

#endif /* _IAP2_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product_with_ipod/mainline/services/mm-ipod/ipod-drvr/iap2/clientlib/public/iap2/iap2.h $ $Rev: 299766 $")
#endif

