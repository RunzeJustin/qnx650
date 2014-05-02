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
 
/**
 @mainpage iPod Library
 
This library provides functionality for all communications with
an iPod. Two public header files are provided: ipod.h provides functions
to manage an iPod, and types.h defines constants and data types used
by the iPod interface.

*/

#if !defined(IPOD_H_INCLUDED)
#define IPOD_H_INCLUDED

#include <ipod/types.h>
#include <sys/slogcodes.h>
#include <sys/slog.h>
#include <sys/iomsg.h>

__BEGIN_DECLS

/**
 * @file ipod.h
 *
 * @brief Provides functions to manage an iPod, including iPod playback control.
 */
 
/**
 * @brief Set up a connection between an application and the iPod driver 
 *        server.
 *
 * @param path          Path to iPod mountpoint
 * @param flags         Reserved
 *
 * @return A valid iPod server connection handle structure (@c ipod_hdl_t) 
 * on success
 * @return NULL on error
 */
ipod_hdl_t * ipod_connect(const char *path, uint32_t flags);


/**
 * @brief Disconnect the iPod.
 *
 * Disconnect an application from the iPod driver server and releases the 
 * ipod_hdl_t connection handle.
 *
 * @param hdl           iPod driver server handle
 *
 * @return 0 on success
 * @return -1 on error
 */
int ipod_disconnect(ipod_hdl_t *hdl);


/**
 * @brief Arm the iPod notifications.  
 * 
 * Wrapper function for the standard @c ionotify().
 * 
 * @param hdl           iPod handle
 * @param action        The type of arming action to take.
 * @param flags         The types of conditions that can be checked for 
 *                      notification.
 * @param event         The notification sigevent; use NULL to disarm a 
 *                      notification.
 *
 * @return 0 on success
 * @return -1 on error
 */
int ipod_notify(ipod_hdl_t *hdl, int action, int flags, const struct sigevent *event);


/**
 * @brief Retrieve the protocol string for a given protocol ID.
 *
 * @param hdl           iPod handle
 * @param protocolid    ID of the desired protocol string
 * @param buf           A buffer of size @c len allocated by the caller; 
 *                      the string is written to this buffer
 * @param len           Size of the buffer
 *
 * @return The number of bytes in the protocol string on success
 * @return -1 on error
 */
int ipod_eaf_getprotocol(ipod_hdl_t *hdl, int protocolid, char *buf, int len);


/**
 * @brief Add a protocol string.
 * 
 * Once protocols have been added, @c ipod_reidentify() must be called to
 * transmit them to the iPod (doesn't update ipod.cfg).
 *
 * @param hdl           iPod handle
 * @param protocol      Protocol string to add
 *
 * @return The new protocol ID on success
 * @return -1 on error
 */
int ipod_eaf_addprotocol(ipod_hdl_t *hdl, char *protocol);


/**
 * @brief Retrieve information about all events.  
 * 
 * This function does not consume the events; calling it again 
 * will return the same set of events if nothing has changed.
 *
 * @param hdl           iPod handle
 * @param events        Array in which to store events
 * @param nevents       Size of the array
 *
 * @return The total number of events that could be retrieved on success
 * @return -1 on error
 */
ssize_t ipod_eaf_getevents(ipod_hdl_t *hdl, ipod_eaf_event_t *events, size_t nevents);


/**
 * @brief Add a new session request for a given protocol ID. 
 * 
 * Indicates to the driver that it should accept an additional new 
 * session request for the specified @c protocolid. Once a session 
 * request is accepted, an @c IPOD_EAF_EVENT_SESSION_OPEN will be 
 * reported. A subsequent call to @c ipod_eaf_session_open() will return the 
 * session ID for the waiting session. 
 *
 * @param hdl           iPod handle
 * @param protocolid    ID of the protocol
 * @param flags         None defined, pass in 0.
 *
 * @return 0 or a positive integer on success
 * @return -1 on error
 */
int ipod_eaf_session_accept(ipod_hdl_t *hdl, unsigned protocolid, unsigned flags);


/**
 * @brief Return the ID of the open session.
 * 
 * Claims and returns the session ID of an opened session for
 * the specified protoctol. If no sessions are ready it returns immediately
 * with an error.
 *
 * @param hdl           iPod handle
 * @param protocolid    ID of the protocol
 *
 * @return The new session ID on success.
 * @return -1 on error. 
 */
int ipod_eaf_session_open(ipod_hdl_t *hdl, unsigned protocolid);


/**
 * @brief Free all internal resources related to a session. 
 * 
 * The iPod driver will NACK all data transfered from the iPod on this session.
 * Only the iPod can close the session.
 *
 * @param hdl           iPod handle
 * @param sessionid     ID of the session to close.
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_eaf_session_free(ipod_hdl_t *hdl, unsigned sessionid);


/**
 * @brief Send data to the iPod/iPhone.
 *
 * @param hdl           iPod handle
 * @param sessionid     ID of the session over which to send data
 * @param data          Pointer to data to send
 * @param nbytes        Size of the data
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_eaf_send(ipod_hdl_t *hdl, unsigned sessionid, void *data, int nbytes);


/**
 * @brief Retrieve data sent by the iPod/iPhone.
 *
 * @param hdl           iPod handle
 * @param sessionid     ID of the session from which to retrieve data
 * @param data          A buffer of size @c nbytes allocated by the caller. 
 *                      The data is written to this buffer.
 * @param nbytes        Size of the buffer
 *
 * @return The number of bytes read on success
 * @return -1 on error
 */
int ipod_eaf_recv(ipod_hdl_t *hdl, unsigned sessionid, void *data, int nbytes);


/**
 * @brief Set an EAF configuration parameter.
 *
 * @param hdl           iPod handle
 * @param parameter     Name of the parameter to set
 * @param value         Value of the parameter
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_eaf_cfg_set(ipod_hdl_t *hdl, const char *parameter, const char *value);

/**
 * @brief Read an EAF configuration parameter.
 *
 * @param hdl           iPod handle
 * @param parameter     Name of the parameter to get
 * @param value         A buffer of size @c len allocated by the caller; 
 *                      the parameter is written to this buffer
 * @param len           Size of the buffer
 *
 * @return Number of bytes needed for value of paramater on success
 * @return -1 on error
 */
int ipod_eaf_cfg_get(ipod_hdl_t *hdl, const char *parameter, char *value, int len);

/**
 * @brief Set session-specific EAF configuration parameters.
 *
 * @param hdl           iPod handle
 * @param sessionid     ID of the session
 * @param parameter     Name of the parameter to set
 * @param value         Value of the parameter
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_eaf_cfg_session_set(ipod_hdl_t *hdl, unsigned sessionid, const char *parameter, const char *value);


/**
 * @brief Send a @c ContextButtonStatus command to the iPod using 
 *        Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param bitmask       Bitmask of set @c IPOD_BUTTON_CONTEXT_* buttons
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_button(ipod_hdl_t *hdl, uint32_t bitmask, unsigned delay, unsigned repeat);


/**
 * @brief Send a @c ImageButtonStatus command to the iPod using Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param bitmask       Bitmask of set @c IPOD_BUTTON_IMAGE_* buttons
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_imagebutton(ipod_hdl_t *hdl, uint32_t bitmask, unsigned delay, unsigned repeat);


/**
 * @brief Send a @c VideoButtonStatus command to the iPod using 
 *        Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param bitmask       Bitmask of set @c IPOD_BUTTON_VIDEO_* buttons
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_videobutton(ipod_hdl_t *hdl, uint32_t bitmask, unsigned delay, unsigned repeat);


/**
 * @brief Send a @c AudioButtonStatus command to the iPod using 
 *        Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param bitmask       Bitmask of set @c IPOD_BUTTON_AUDIO_* buttons
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_audiobutton(ipod_hdl_t *hdl, uint32_t bitmask, unsigned delay, unsigned repeat);


/**
 * @brief Send a @c PushUIButtonStatus command to the iPod using 
 *        Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param buttonsrc     Location of the button, one of @c IPOD_BUTTON_LOCATION_*
 * @param bitmask       Bitmask of set @c IPOD_BUTTON_IPODOUT_* buttons
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_pushuibutton(ipod_hdl_t *hdl, unsigned buttonsrc, uint32_t bitmask, unsigned delay, unsigned repeat);


/**
 * @brief Send a @c RotationInputStatus command to the iPod using Simple Remote Lingo.
 *
 * @param hdl           iPod handle
 * @param duration      Number of msec since start of current user action
 * @param buttonsrc     Location of the button; one of @c IPOD_BUTTON_LOCATION_*
 * @param ctrltype      Type of wheel; one of the @c IPOD_WHEEL_TYPE_* values
 * @param direction     Direction of rotation; one of @c IPOD_WHEEL_ROTATION_*
 * @param action        Rotation action; one of @c IPOD_WHEEL_ACTION_* values
 * @param rotationtype  Type of rotation; one of @c IPOD_WHEEL_ROTATION_TYPE_*
 * @param turnval       Amount of detents or degrees in the turn
 * @param turnmax       Constant amount of detents or degrees in full wheel 
 *                      turn
 * @param delay         Minimum delay since the last ContextButtonStatus was 
 *                      sent
 * @param repeat        Frequency at which to repeat/resend the button settings
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_smplrmt_rotationinput(ipod_hdl_t *hdl, unsigned duration, unsigned buttonsrc, unsigned ctrltype,
    unsigned direction, unsigned action, unsigned rotationtype, unsigned turnval,
    unsigned turnmax, unsigned delay, unsigned repeat);


/**
 * @brief Retrieve the iPod PushUI options.
 *
 * @param hdl           iPod handle
 * @param enabled       0 returns all possible options, 1 returns only the 
 *                      set options
 * @param options       Place to store the bitmask of set @c IPOD_IPODOUT_OPT_* 
 *                      options
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_getopt(ipod_hdl_t *hdl, unsigned enabled, uint32_t *options);


/**
 * @brief Set the iPod PushUI options.
 *
 * @param hdl           iPod handle
 * @param options       Bitmask of @c IPOD_IPODOUT_OPT_* options to set
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_setopt(ipod_hdl_t *hdl, uint32_t options);


/**
 * @brief Set the iPod PushUI device state.
 *
 * @param hdl           iPod handle
 * @param newstate      State to set; one of @c IPOD_IPODOUT_STATE_*
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_devstatechange(ipod_hdl_t *hdl, unsigned newstate);


/**
 * @brief Set new device screeninfo information at runtime.
 * 
 * This function leaves the configuration file unmodified.
 *
 * @param hdl               iPod handle
 * @param width_inches      Total screen width in inches.
 * @param height_inches     Total screen height in inches.
 * @param width_pixels      Total screen width in pixels.
 * @param height_pixels     Total screen height in pixels.
 * @param ipodout_width     Total iPodOut screen width in pixels.
 * @param ipodout_height    Total iPodOut screen height in pixels.
 * @param features          Bitmask of screen features.
 * @param gamma             Accessory display gamma value.
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_devvideoscreeninfo(ipod_hdl_t *hdl, unsigned width_inches, unsigned height_inches,
    unsigned width_pixels, unsigned height_pixels, unsigned ipodout_width, unsigned ipodout_height,
    uint32_t features, unsigned gamma);


/**
 * @brief Retrieve the UI version of the PushUI application.
 *
 * @param hdl           iPod handle
 * @param version       Version of the UI
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_getversion(ipod_hdl_t *hdl, uint32_t *version);


/**
 * @brief Retrieve the approval data for the specified approver.
 *
 * @param hdl           iPod handle
 * @param approver      Approver code to pass to iPod
 * @param data          A buffer of size @c nbytes allocated by the caller; 
 *                      the approval data is written to this buffer
 * @param nbytes        Size of the buffer
 *
 * @return Size of buffer on success
 * @return -1 on error
 */
int ipod_pushui_get_approval(ipod_hdl_t *hdl, int approver, void *data, int nbytes);


/**
 * @brief Set the iPod mode.
 *
 * @param hdl           iPod handle
 * @param mode          Mode to set (one of @c IPOD_MODE_* values)
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_set_ui_mode(ipod_hdl_t *hdl, uint8_t mode);


/**
 * @brief Retrieve the iPod mode.
 *
 * @param hdl           iPod handle
 * @param mode          Place to store the current mode 
 *                      (one of @c IPOD_MODE_* values)
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_get_ui_mode(ipod_hdl_t *hdl, uint8_t *mode);


/**
 * @brief Retrieve the audio URL used for reading in the iPod PCM data.
 *
 * @param hdl           iPod handle
 * @param alternate     0 for standard audio URL, 1 for alternate URL
 * @param url           A buffer of size @c len allocated by the caller; 
 *                      the URL is written to this buffer 
 * @param len           Size of the buffer
 *
 * @return Number of bytes required to store the full URL on success
 * @return -1 on error
 */
int ipod_cfg_audio_in_get(ipod_hdl_t *hdl, int alternate, char *url, int len);


/**
 * @brief Retrieve an array of iPod capabilities (@c IPOD_CAPABILITY_*)
 *
 * @param hdl           iPod handle
 * @param caps          Pointer to an array of @c uint16_t to be filled in
 * @param ncaps         Size of the caps array
 * @param reserved      Reserved, pass in 0
 *
 * @return Number of total caps on success (could be > ncaps)
 * @return -1 on error
 */
int ipod_get_capabilities(ipod_hdl_t *hdl, uint16_t *caps, size_t ncaps, int reserved);


/**
 * @brief Retrieve the iPod software version. 
 * 
 * The version format is 0x00AABBCC where AA is the major version, 
 * BB is the minor version, and CC is the revision number.
 *
 * @param hdl           iPod handle
 * @param version       Pointer to a 32-bit integer in which to store 
 *                      the version
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_get_software_version(ipod_hdl_t *hdl, uint32_t *version);


/**
 * @brief Retrieve the iPod model ID and model ID string.
 *
 * @param hdl           iPod handle
 * @param modelid       Pointer to a 32-bit integer to store the model ID
 * @param modelstring   Model in string format, as per iPod specification
 * @param len           Size of @c modelstring buffer in bytes.
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_get_model(ipod_hdl_t *hdl, uint32_t *modelid, char *modelstring, int len);


/**
 * @brief Restart the iPod communication.
 *
 * @param hdl           iPod handle
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_reidentify(ipod_hdl_t *hdl);


/**
 * @brief Change the iPod preference.
 *
 * @param hdl           iPod handle
 * @param classid       The preference class ID (@c IPOD_PREF_* classes)
 * @param settingid     The setting ID to set (@c IPOD_PREF_*_* specifiers)
 * @param restore       1 indicates restore previous setting on disconnect; 
 *                      0 otherwise
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_preference_set(ipod_hdl_t *hdl, unsigned classid, unsigned settingid, unsigned restore);


/**
 * @brief Return the iPod preference.
 *
 * @param hdl           iPod handle
 * @param classid       The preference class ID of the preference to get
 *
 * @return The preference setting on success
 * @return -1 on error
 */
int ipod_preference_get(ipod_hdl_t *hdl, unsigned classid);


/**
 * @brief Set the VBI output byte.
 *
 * @param hdl           iPod handle
 * @param auth          The VBI byte
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_pushui_setvideoauth(ipod_hdl_t *hdl, uint8_t auth);


/**
 * @brief Set iPod driver configuration parameters.
 *
 * @param hdl           iPod handle
 * @param parameter     Name of the parameter to set
 * @param value         Value of the parameter
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_cfg_set(ipod_hdl_t *hdl, const char *parameter, const char *value);


/**
 * @brief Retrieve iPod driver configuration parameters.
 *
 * @param hdl           iPod handle
 * @param parameter     Name of the parameter to get
 * @param value         Buffer of size @c len allocated by the caller; 
 *                      the parameters are written to this buffer 
 * @param len           size of the buffer
 *
 * @return Buffer size on success
 * @return -1 on error
 */
int ipod_cfg_get(ipod_hdl_t *hdl, const char *parameter, char *value, int len);


/**
 * @brief Send a request to the iPod to launch the specified application.
 *
 * @param hdl           iPod handle
 * @param appid         Application ID of the app to launch
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_request_app_launch(ipod_hdl_t *hdl, const char *appid);


/**
 * @brief Return the application ID of the nowplaying app that has focus.
 *
 * @param hdl           iPod handle
 * @param appid         Buffer of size @len allocated by the caller; 
 *                      the ID is written to the buffer
 * @param len           Size of the buffer
 *
 * @return Buffer size on success
 * @return -1 on error
 */
int ipod_get_nowplaying_app(ipod_hdl_t *hdl, char *appid, int len);

/**
 * @brief Write a feature to the storage component.
 *
 * @param hdl           iPod handle
 * @param feature       The feature to write
 * @param data          Buffer of size @nbytes allocated by the caller; 
 *                      the feature data is written to the buffer
 * @param nbytes        Size of the buffer
 *
 * @return An integer not equal to -1 on success
 * @return -1 on error
 */
int ipod_write_feature(ipod_hdl_t *hdl, int feature, char *data, int nbytes);


/**
 * @brief Set the verbosity of the client library API.
 *
 * @param hdl           iPod driver server handle
 * @param verbosity     Level of verbosity

 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_set_verbose_level(ipod_hdl_t *hdl, int verbosity);

/**
 * @brief Retrieve the iPod device name.
 *
 * @param hdl           iPod handle
 * @param buf           Buffer of size @c bsize allocated by the caller; 
 *                      the name is written to this buffer
 * @param bsize         Size of the buffer
 *
 * @return Number of bytes used on success.
 * @return -1 on failure.
 */
int ipod_get_device_name(ipod_hdl_t *hdl, char *buf, size_t bsize);


/** @brief Retrieve the serial number of the iPod.
 *
 * @param hdl           iPod handle
 * @param buf           Buffer of size @c bsize allocated by the caller; 
 *                      the serial number (null-terminated string) 
 *                      is written to the buffer
 * @param bsize         Size of the buffer
 *
 * @return Number of bytes used to store the serial number on success
 * @return -1 on failure.
 */
int ipod_get_device_serialnum(ipod_hdl_t *hdl, char *buf, size_t bsize);

/**
 * @brief Retrieve the option bits that the iPod supports for a specific lingo.
 *
 * Lingo bits are described with the @c LINGO_* flags
 * 
 * @param hdl           iPod handle
 * @param lingo         The requested lingo
 * @param options       Bitmask of @c IPOD_<lingo>_OPT_* options
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_get_lingo_options(ipod_hdl_t *hdl, uint32_t lingo, uint64_t *options);

/**
 * @brief Stop the iPod.
 * 
 * Send a stop command to the iPod and clears the contents in the playback 
 * engine. You cannot resume the Apple iPod/iPhone once it is stopped; a new 
 * track list needs to selected and played.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_stop(ipod_hdl_t *hdl);


/**
 * @brief Jump to the next track in the playback engine of the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_next_track(ipod_hdl_t *hdl);


/**
 * @brief Jump to the previous track in the playback engine of the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_prev_track(ipod_hdl_t *hdl);


/**
 * @brief Activate fast forward on the current track on the iPod.
 *
 * NOTE: Use @c ipod_resume() to end fast forward.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_fast_forward(ipod_hdl_t *hdl);


/**
 * @brief Activate fast backward on the current track on the iPod.
 *
 * NOTE: Use @c ipod_resume() to end fast backward.
 * 
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_fast_backward(ipod_hdl_t *hdl);


/**
 * @brief Jump to the next chapter on the current track on the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_next_chapter(ipod_hdl_t *hdl);


/**
 * @brief Jump to the previous chapter on the current track on the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_prev_chapter(ipod_hdl_t *hdl);

/**
 * Seek to specified chapter on the current track on the iPod.
 *
 * @param hdl		Handle to the iPod
 * @param chapter	Desired chapter index (first chapter = 0)
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_set_chapter(ipod_hdl_t *hdl, uint32_t chapter);

/**
 * @brief Send a play command to the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_play(ipod_hdl_t *hdl);


/**
 * @brief Send a resume command to the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_resume(ipod_hdl_t *hdl);

/**
 * @brief Send a music application resume command to the iPod.
 *
 * Resume the music application if a third-party application
 * currently has audio control/focus.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_resume_musicapp(ipod_hdl_t *hdl);

/**
 * @brief Send a pause command to the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_pause(ipod_hdl_t *hdl);


/**
 * @brief Send a control command to the iPod.
 *
 * @param hdl           iPod handle
 * @param command       Control command to send to the iPod (@c IPOD_CONTROL_*)
 *
 * @return 0 on success
 * @return -1 on failure
 */
int ipod_play_control(ipod_hdl_t *hdl, uint32_t command);


/** 
 * @brief Retrieve the iPod playback status.
 *
 * @param hdl           iPod handle
 * @param status        Pointer to store the data
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_get_play_status(ipod_hdl_t *hdl, ipod_play_status_t *status);


/**
 * @brief Set the repeat setting of the iPod.
 *
 * @param hdl           iPod handle
 * @param setting       Type of repeat setting
 *
 * @return Repeat setting on success.
 * @return -1 on failure.
 */
int ipod_set_repeat(ipod_hdl_t *hdl, ipod_setting_repeat_t setting);


/**
 * @brief Provide the repeat setting of the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return Repeat setting on success.
 * @return -1 on failure.
 */
ipod_setting_repeat_t ipod_get_repeat(ipod_hdl_t *hdl);


/**
 * @brief Set the shuffle setting of the iPod.
 *
 * @param hdl           iPod handle
 * @param setting       Type of shuffle to set.
 *
 * @return Shuffle setting on success.
 * @return -1 on failure.
 */
int ipod_set_shuffle(ipod_hdl_t *hdl, ipod_setting_shuffle_t setting);


/**
 * @brief Retrieve the shuffle setting of the iPod.
 *
 * @param hdl           iPod handle
 *
 * @return Shuffle setting on success.
 * @return -1 on failure.
 */
ipod_setting_shuffle_t ipod_get_shuffle(ipod_hdl_t *hdl);


/**
 * @brief Seek to a specific time of the current track. 
 * 
 * The Apple iPod/iPhone must be in a playing or paused state.
 *
 * @param hdl           iPod handle
 * @param time          Time (ms) to seek to
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_seek_time(ipod_hdl_t *hdl, uint32_t time);


/**
 * @brief Provide the number of tracks in the iPod playback engine. 
 * 
 * If the device is in a stopped state, there will be 0 tracks in the 
 * playback engine.
 *
 * @param hdl           iPod handle
 * @param ntracks       Place to store the number of tracks
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_pb_get_numtracks(ipod_hdl_t *hdl, uint32_t *ntracks);


/**
 * @brief Set the track to play in the iPod playback engine. 
 * 
 * Tracks must be present in the playback engine.
 *
 * @param hdl           iPod handle
 * @param index         Index (0-based) of track to play
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_pb_play_track(ipod_hdl_t *hdl, uint32_t index);


/**
 * @brief Select the video or audio hierachy and clears any previous 
 *        category selections.
 *
 * @param hdl           iPod handle
 * @param hier          Hierarchy (audio or video) selection (@c IPOD_DB_HIER_*)
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_browse_reset(ipod_hdl_t *hdl, uint32_t hier);


/**
 * @brief Set options for the @c ipod_browse_* APIs to use. 
 * 
 * This data will be cached in the ipod_hdl_t structure.
 *
 * @param hdl           iPod handle
 * @param category      Set the current category 
 * @param loadnum       Number of records to load at once as a hint (0=all)
 *
 * Since the category has changed, the index for ipod_browse_get_record() 
 * will be reset to 0.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_browse_set_options(ipod_hdl_t *hdl, uint32_t category, uint32_t loadnum);


/**
 * @brief Retrieve the number of records for a chosen category.
 * 
 * The category is set using @c ipod_browse_set_options().
 *
 * @param hdl           iPod handle
 * @param num           Pointer to store data (number of entries)
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_browse_get_numrecords(ipod_hdl_t *hdl, uint32_t *num);


/**
 * @brief Select a record belonging to a specified category in the iPod 
 * database.
 * 
 * The category is set using the most recent call to @c ipod_browse_set_options().
 *
 * NOTE: If the category has been set to @c IPOD_CAT_TRACK, the iPod will copy 
 * the current tracklist to the playback engine. With subsequent 
 * calls to this function, record selection will be based 
 * on the subset of records from previous selections, not the 
 * entire database. To undo the previous selection, specifying index = -1 and 
 * the current category can be used.  This cannot be done if the last selection 
 * was from the Track or Audiobook category. Selecting an index from a track 
 * category will automatically copy the track at that index and the track 
 * list to the playback engine.  The currently playing index will be the track 
 * that was selected.
 *
 * @param hdl           iPod handle
 * @param index         Category index
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_browse_select_record(ipod_hdl_t *hdl, uint32_t index);


/**
 * @brief Provide the name of the current record and increments to the next. 
 *
 * Note that memory is not owned by the caller and is invalid if 
 * the caller moves to the next record.* The caller must duplicate 
 * or copy the data if required for 
 * future use. Setting a category using @c ipod_browse_set_options() will 
 * also reset the index back to 0. Selecting a record using 
 * @c ipod_browse_select_record() will also reset the index back to 0, 
 * as the list of records will differ after a selection. Use 
 * @c ipod_browse_set_record_index() to jump to a particular index.
 *
 * @param hdl           iPod handle
 * @param ptr           Pointer to the name of the record
 *
 * @return 1 on success.
 * @return 0 on end of records.
 * @return -1 on failure.
 */
int ipod_browse_get_record(ipod_hdl_t *hdl, char **ptr);


/**
 * @brief Set the index of the records list to query/access. 
 *
 * This function affects the next use of @c ipod_browse_get_record().
 *
 * @param hdl           iPod handle
 * @param index         The record index to set
 *
 * @return 0            on success.
 * @return -1           on failure.
 */
int ipod_browse_set_record_index(ipod_hdl_t *hdl, uint32_t index);


/**
 * @brief Provide the index of the records list.
 *
 * @param hdl           iPod handle
 *
 * @return index        on success.
 * @return -1           on failure.
 */
int ipod_browse_get_record_index(ipod_hdl_t *hdl);

/**
 * @brief Copy the track list. 
 * 
 * The function uses the specified database selections from 
 * the highest category to lowest category.  To skip a particular category, 
 * use an index of -1.
 *
 * @param hdl           iPod handle
 * @param hier          Audio / Video hierarchy
 * @param playlist      Index of the playlist (-1 to skip)
 * @param genre         Index of the genre (-1 to skip)
 * @param artist        Index of the artist (-1 to skip)
 * @param album         Index of the album (-1 to skip)
 * @param track         Index of the track
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_browse_play(ipod_hdl_t *hdl, uint32_t hier, uint32_t playlist, uint32_t genre, uint32_t artist, uint32_t album, uint32_t track);

/**
 * @brief Set options for subsequent function calls. 
 * 
 * The @c ipod_trkinfo_load() and @c ipod_uid_get_trkinfo() functions depend
 * on this function. The options will apply until they are changed.
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param md_types      Type(s) of track information to retrieve 
 *                      (@c IPOD_TRKINFO_MASK_*)
 * @param num           Number of tracks to get at one time
 *
 * NOTE: Not all iPods support trkinfo from the database/UIDs.  Need to use
 * the @c ipod_browse_*() APIs to navigate.
 * 
 * NOTE: Database track list will change if @c ipod_browse_*() APIs are used.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_trkinfo_set_options(ipod_hdl_t *hdl, uint32_t trktype, uint32_t md_types, uint32_t num);


/**
 * @brief Load track metadata.
 *
 * Load metadata info for track(s) in the iPod's database or playback 
 * engine. The type of information is specified with a mask for multiple 
 * types using @c ipod_trkinfo_set_options(). To retrieve the track 
 * information, use @c ipod_trkinfo_get_number() and 
 * @c ipod_trkinfo_get_string() depending on the metadata type. To iterate 
 * to the next track, use @c ipod_trkinfo_next(). A call to 
 * @c ipod_trkinfo_set_options() will clear any track information that 
 * was previously loaded.

 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param trk           Starting track to get metadata for
 *
 * NOTE: Not all iPods support getting metadata from the database.  Need to use
 * the @c ipod_browse_*() APIs to navigate.
 *
 * NOTE: Database track list will change if @c ipod_browse_*() APIs are used.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_trkinfo_load(ipod_hdl_t *hdl, uint32_t trktype, uint32_t trk);


/**
 * @brief Iterate to the next track.
 *
 * Note that you must call @c ipod_trkinfo_load() first.
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 *
 * @return 1 on success.
 * @return 0 on end of tracks.
 * @return -1 on failure.
 */
int ipod_trkinfo_next(ipod_hdl_t *hdl, uint32_t trktype);


/**
 * @brief Jump to the specified track index.
 * 
 * You must first call @c ipod_trkinfo_load(). 
 * To retrieve the track information, use @c ipod_trkinfo_get_number() and 
 * @c ipod_trkinfo_get_string() depending on the metadata type.
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param index         Index into the records list
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_trkinfo_set_index(ipod_hdl_t *hdl, uint32_t trktype, uint32_t index);


/**
 * @brief Return the current track index.
 * 
 * Return the current track index during the iteration of track metadata 
 * after @c ipod_trkinfo_load() has been called. To retrieve the track 
 * information, use @c ipod_trkinfo_get_number() and 
 * @c ipod_trkinfo_get_string() depending on the metadata type.

 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 *
 * @return index on success
 * @return -1 on failure.
 */
int ipod_trkinfo_get_index(ipod_hdl_t *hdl, uint32_t trktype);


/**
 * @brief Provide the requested metadata type as a UTF-8 string.  
 * 
 * The memory that @c ptr 
 * references is not owned by the caller. The memory is not valid if 
 * @c ipod_trkinfo_next(), @c ipod_trkinfo_set_index(), 
 * @c ipod_trkinfo_set_options() are called. If the trktype is 
 * @c IPOD_TRK_IDENT_TYPE_DB, @c ipod_browse_select_record() will 
 * cause the memory referenced by @c ptr to be 
 * invalid. If the trktype is @c IPOD_TRK_IDENT_TYPE_PB, 
 * @c ipod_browse_select_record()  with a category of @c IPOD_CAT_TRACK will cause 
 * the memory referenced by @c ptr to be invalid.
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param md_type       Type of track information to return 
 *                      (@c IPOD_TRKINFO_MASK_*)
 * @param ptr           Pointer to store the string data (not owned by caller)
 *
 * NOTE: The memory is not owned by the caller and will not be valid
 *  if the caller selects a new index.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_trkinfo_get_string(ipod_hdl_t *hdl, uint32_t trktype, uint32_t md_type, char **ptr);


/**
 * @brief Retrieve metadata in numerical format for the currently set track.
 * 
 * Track info needs to be loaded first (@c ipod_load_trkinfo()).
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param md_type       Type of track information (@c IPOD_TRKINFO_MASK_*)
 * @param num           Address of a 64-bit integer to store the data
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_trkinfo_get_number(ipod_hdl_t *hdl, uint32_t trktype, uint32_t md_type, uint64_t *num);


/**
 * @brief Retrieve any album art info for a track in the iPod database or playback engine. 
 * 
 * The information returned contains the size and pixel format of each image.  
 * Only some iPods/iPhones support retrieval of album art from the database 
 * engine. Support can be queried as follows: 
@code
 *    ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 *    if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *        // Supports ipod_get_albart_image(
 *        //   hdl, IPOD_TRK_IDENT_TYPE_DB, md_type, num)
 *    }
@endcode
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param trk           Starting track 
 * @param artinfo       Buffer of size @c size allocated by the caller; 
 *                      the album art data is written to this buffer 
 * @param size          Size of the buffer
 *
 * @return Number of album art covers available on success.
 * @return -1 on failure.
 */
int ipod_get_albart_info(ipod_hdl_t *hdl, uint32_t trktype, uint32_t trk, struct _ipod_albart_entry *artinfo, size_t size);


/**
 * @brief Retrieve album art image for a track in the iPod database engine. 
 * 
 * Only some iPods/iPhones support retrieval of album art from the 
 * database engine and can be queried using: 
 *
@code
 *    ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 *    if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *        // Supports ipod_get_albart_image(
 *        //   hdl, IPOD_TRK_IDENT_TYPE_DB, md_type, num)
 *    }
@endcode
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param trk           Starting track 
 * @param imgidx        Image index to retrieve
 * @param aep           Buffer of size @c size allocated by the caller; 
 *                      the image is written to this buffer 
 * @param size          Size of the buffer
 *
 * @return number of bytes copied.
 */
size_t ipod_get_albart_image(ipod_hdl_t *hdl, uint32_t trktype, uint32_t trk, uint32_t imgidx, struct _ipod_albart *aep, size_t size);


/**
 * @brief Create a Genius playlist using a track index from the database.
 * 
 * If the trktype is @c IPOD_TRK_IDENT_TYPE_DB, the index is based on the 
 * current track list, based on the current category selections.
 * To determine if an iPod/iPhone supports this functionality, the 
 * following query can be done.  An error will also be returned if 
 * the iPod does not support this function.
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *     // Supports ipod_uid_play_trk_list()
 * }
@endcode
 *
 * @param hdl           iPod handle
 * @param trktype       Type of request (@c IPOD_TRK_IDENT_TYPE_*)
 * @param trk           Starting track to get metadata for
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_create_genius_playlist(ipod_hdl_t *hdl, uint32_t trktype, uint32_t trk);


/** 
 * @brief Provide track metadata from a UID. 
 * 
 * The type of information is specified 
 * using a mask for multiple types using @c ipod_trkinfo_set_options(). To 
 * retrieve the track information, use @c ipod_trkinfo_get_number() and 
 * @c ipod_trkinfo_get_string() depending on the metadata type.
 *
 * @param hdl           iPod handle
 * @param uid           UID of the track
 *
 * NOTE: Use @c ipod_trkinfo_get_string() and @c ipod_trkinfo_get_number() to
 * extract the metadata.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_uid_get_trkinfo(ipod_hdl_t *hdl, uint64_t uid);


/**
 * @brief Provide any album art info from a UID in the iPod database engine.
 * 
 * The information returned contains the various sizes and pixel format 
 * of each image.  Only some iPods/iPhones support retrieval of album 
 * art using from an UID and can be queried using: 
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *     // Supports ipod_uid_get_albart_info()
 * }
@endcode
 *
 * @param hdl           iPod handle
 * @param uid           UID of the track
 * @param artinfo       A buffer of size @c size allocated by the caller; 
 *                      the album art info is written to this buffer 
 * @param size          Size of the buffer
 *
 * @return Number of album art covers available on success.
 * @return -1 on failure.
 */
int ipod_uid_get_albart_info(ipod_hdl_t *hdl, uint64_t uid, struct _ipod_albart_entry *artinfo, size_t size);


/**
 * @brief Provide the album art image for a track in the iPod database engine. 
 *
 * Only some iPods/iPhones support retrieval of album art from a
 * UID and can be queried using: 
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *     // Supports ipod_uid_get_albart_image()
 * }
@endcode
 *
 * @param hdl           iPod handle
 * @param uid           UID of the track
 * @param imgidx        Image index to retrieve
 * @param aep           A buffer of size @c size allocated by the caller; 
 *                      the album art image is written to this buffer
 * @param size          Size of the buffer
 *
 * @return number of bytes copied.
 */
size_t ipod_uid_get_albart_image(ipod_hdl_t *hdl, uint64_t uid, uint32_t imgidx, struct _ipod_albart *aep, size_t size);

/**
 * @brief Provide a list of UIDs for the iPod to play.
 *
 * Need to call @c ipod_uid_play_trk_list() to initiate playback.
 * To determine if an iPod/iPhone supports this functionality, 
 * the following query can be done.  An error will also be returned 
 * if the iPod does not support this function.
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *     // Supports ipod_uid_play_trk_list()
 * }
@endcode
 *
 * @param hdl           iPod handle
 * @param uid_list      Array of UIDs
 * @param num           Number of UIDs
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_uid_set_trk_list(ipod_hdl_t *hdl, uint64_t *uid_list, uint32_t num);


/**
 * @brief Start playback from list of UIDs. 
 *
 * A UID playlist needs to be created first 
 * using @c ipod_uid_set_trk_list(). To determine if an iPod/iPhone supports 
 * this functionality, the following query can be done.  An error will 
 * be returned if the iPod does not support this function.
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *     // Supports ipod_uid_play_trk_list()
 * }
@endcode
 *
 * @param hdl iPod handle
 * @param uid UID to start playback from
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_uid_play_trk_list(ipod_hdl_t *hdl, uint64_t uid);


/**
 * @brief Clear the list of UIDs. 
 *
 * This function does not stop playback of the current track.
 * To determine if an iPod/iPhone supports this functionality, the 
 * following query can be done.  An error will also be returned if 
 * the iPod does not support this function.
@code
 * ipod_get_lingo_options(hdl, LINGO_EXTENDED, &options);
 * if (options & IPOD_EXTENED_OPT_UID_BASED_CMDS) {
 *   // Supports ipod_uid_play_trk_list()
 * }
@endcode
 *
 * @param hdl           iPod handle
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_uid_clear_trk_list(ipod_hdl_t *hdl);

/*
 * This function returns the current control settings as updated by the Apple device
 *
 * @param hdl			Handle to the iPod
 * @param loc_type		Location type
 * @param ctrl_data		Pointer to store the data
 *
 * @return -1 on error, otherwise success
 */
int ipod_gps_get_ctrl(ipod_hdl_t *hdl, int loc_type, uint64_t *ctrl_data);

/*
 * This function sends GPS data to the Apple device
 *
 * @param hdl			Handle to the iPod
 * @param loc_type		Capability type
 * @param data_type		Data type
 * @param buf			Buffer that holds the data
 * @param nbytes		Length of the buffer
 *
 * @return -1 on error, otherwise success
 */
int ipod_gps_send(ipod_hdl_t *hdl, int loc_type, int data_type, void *data, int nbytes);

/*
 * This function retrieves GPS data from the Apple device
 *
 * @param hdl			Handle to the iPod
 * @param loc_type		Location type
 * @param data_type		Data type
 * @param buf			Buffer that holds the data 
 * 						(format: char *, ipod_gps_points_t *, ipod_gps_time_t *)
 * @param nbytes		Length of the buffer
 * @param bytes_req		Number of bytes required
 *
 * @return -1 on error, otherwise returns the number of bytes read.
 */
int ipod_gps_recv(ipod_hdl_t *hdl, int loc_type, int data_type, void *data, int nbytes, int *bytes_req);

/*
 * This function returns information about which events need to be serviced.
 *
 * @param fd			File descriptor of connection to .FS_info./events file
 * @param event			Array in which to store events
 * @param nevents		Size of the array
 *
 * @return -1 on error, number of events retrieved on success
 */
int ipod_get_events(int fd, ipod_event_t *events, size_t nevents);

/*
 * This function restarts the iPod communication.  The mountpoint will be removed
 * and remounted when completed.  Any previous connections will be terminated.
 *
 * @param fd			File descriptor of connection to .FS_info./control file
 * @param flags			For future use.
 *
 */
void ipod_restart(ipod_hdl_t *hdl, int flags);

/**
 * Get the authentication status of the connected iPod.
 *
 * @param hdl		Handle to the iPod
 *
 * @return auth status on success.
 * @return -1 on failure.
 */
ipod_auth_status_t ipod_get_auth_status(ipod_hdl_t *hdl);

/**
 * Get information about the database on the connected iPod.
 *
 * @param hdl		Handle to the iPod
 * @param dbinfo	Pointer to store the data
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int ipod_get_itunesdb_info(ipod_hdl_t *hdl, struct ipod_itunesdb_info *dbinfo);

/**
 * @brief Retrieve the PPS directory which holds the PPS objects for notifications.
 *
 * @param hdl           iPod handle
 * @param url           A buffer of size @c len allocated by the caller; 
 *                      the URL is written to this buffer 
 * @param len           Size of the buffer
 *
 * @return Number of bytes required to store the full URL on success
 * @return -1 on error
 */
int ipod_pps_path_get(ipod_hdl_t *hdl, char *url, int len);

__END_DECLS

#endif // IPOD_H_INCLUDED

/* __SRCVERSION("$URL$ $Rev: 227826 $"); */

