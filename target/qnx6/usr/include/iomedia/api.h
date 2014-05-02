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



#if !defined(IOMEDIA_API_H_INCLUDED)
#define IOMEDIA_API_H_INCLUDED

#if !defined(IOMEDIA_TYPES_H_INCLUDED)
#include <iomedia/types.h>
#include <mm/types.h>
#endif

#if !defined(__TYPES_H_INCLUDED)
#include <sys/types.h>
#endif

__BEGIN_DECLS

/** @file iomedia/api.h
 * io-media external API.
 * @ingroup extAPI External API
 */

/** @defgroup extAPI External API
 */
/*@{*/

/**
 * Create a new instance of a graph or attach to an existing one.
 * @param type The name of the graph class
 * @param name The name of the graph instance
 * @param flags See enum iom_graph_flags
 * @return A non-negative new graph handle or -1 on failure
 */
int             iom_create_graph(const char *type, const char *name, unsigned flags);

/**
 * Destroy a graph handle.
 * If the handle was opened without the \c IOM_GF_KEEP flag, this function
 * also removes the filter's name from the namespace.  The graph is not
 * actually destroyed (and may keep running) until its name is removed
 * and all handles pointing to it are destroyed.
 * @param graph_id The graph handle
 * @return 0 on success, -1 on error with errno set
 */
int             iom_destroy_graph(int graph_id);


/**
 * Get error information.
 * Retrieves additional error information.
 * This information is stored on a per-graph-handle basis,
 * and is only available if the most recent call failed and set errno to EIO
 * and \c iom_get_error_info() has not been called since then.
 * If you neglect to call \c iom_get_error_info() after an EIO failure
 * and call another API function instead, the error information will be lost.
 * \c iom_read_events is an exception in this scheme -- it neither sets the error
 * information on a failure (no need to check for \c EIO) nor clears it on success.
 *
 * @param id A graph or control point handle
 * @param buf Pointer to a buffer to place the information in
 * @return 0 on success, -1 on error with errno set (EINVAL if no error information was available)
 */
int iom_get_error_info( int id, iom_error_info_t *buf );

/**
 * Query, disable, or enable graph capabilities or functionality
 * @param id The graph handle
 * @param enable Zero or a bitwise OR of capabilities you want to enable
 * @param disable Zero or a bitwise OR of capabilities you want to disable
 * @return The enabled functionality on success, -1 on error with errno set
 */
_Int32t iom_graph_capabilities( int id, iom_graph_capability_t enable, iom_graph_capability_t disable );

/**
 * Set the input file for a graph.  This requires that there isn't
 * already an input file set.  To remove an input file see iom_detach_input.
 *
 * To support multi-track prebuffering, this needs to be called as soon
 * as the client receives the event \c IOM_EV_INPUT_EOF.
 *
 * @param graph_id The graph handle
 * @param inputURL The input URL for whatever supported type:
 *          - http://user:password@host:port/path
 *          - cdda:///path  (/net/host/fs/cd0/tracknum)
 *          - file:///path
 *
 * @param identifier This is a unique identifier that specifies the input file in the
 *        graph chains.  When the client asks for status info it can retrieve the
 *        identifier of the current playing track and current encoding track. 
 *        \c identifier is client specified so that it can be relevant to the client app.
 * @return 0 on success, -1 on error with errno set
 */
int             iom_attach_input(int graph_id, const char *inputURL, _Uint64t identifier);


/**
 * Remove a file from the graph.  If the file is being read from
 * actively this will give an error, if the file is in an EOF state then
 * it can be removed by this function.
 *
 * To remove an inputfile from a graph while playing, stop the graph
 * then remove the file.
 *
 * @param graph_id The graph handle
 * @return 0 on success, -1 on error with errno set
 */
int             iom_detach_input(int graph_id);

/**
 * Set output file
 *
 * For graphs that output to files rather than to devices this API sets the
 * output file to use and its format.
 *
 * @param graph_id The graph handle
 * @param filename The output filename
 * @param mimetype The mimetype of the output format
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_output_file(int graph_id, const char *filename, const char *mimetype);

/**
 * Set input device.
 *
 * For graphs that read from an audio input device such as a 2-wire iPod
 *
 * @param graph_id The graph handle
 * @param device The input device
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_input_device(int graph_id, const char *device);


/**
 * Start playing.
 * If the graph is stopped, this function asks it to go to the
 * "playing" or "paused" state (depending on the current play speed
 * established by the most recent call to iom_set_play_speed()).
 * If the graph is already playing or paused, this is a
 * no-op.
 * 
 * @param graph_id The graph handle
 * @return 0 on success, -1 on error with errno set
 */
int             iom_play(int graph_id);

/**
 * Stop a graph from playing and flush all its buffers.
 * Since this may position you in an unexpected spot in the track,
 * make sure to seek to a known place before calling iom_play() again.
 * If the graph is already stopped, this is a no-op.
 *
 * @param graph_id The graph handle
 * @return 0 on success, -1 on error with errno set
 */
int             iom_stop(int graph_id);

/**
 * Send a command to the graph.
 *
 * This is only applicable for media that supports commands such as next/prev.
 * Some examples:
 *    - iPod
 *    - DVD-V
 *
 * Media which don't:
 *    - Files on USB/Hard drive
 *    - Tracks on DVD-Audio
 *
 * @param graph_id The graph handle
 * @param command The command
 * @return 0 on success, -1 on error with errno set
 */
int             iom_send_command(int graph_id, mm_button_t command);

/**
 * Set the playback speed for the specified graph.
 *
 * The playback speed is a persistent parameter of the graph;
 * in most cases it remains constant between calls to
 * iom_set_play_speed().
 *
 * Changing the speed while the graph is stopped affects
 * the playback speed the next time iom_play() is called,
 * but it does not cause playback to start.
 *
 * Speeds are expressed in units of 1/1000 of normal speed,
 * and are associated with one of five speed ranges:
 *   - Normal speed -- 1000
 *   - Fast forward -- 1001 to INT_MAX (e.g. 2000 is 2x)
 *   - Slow -- 1 to 999
 *   - Paused -- 0
 *   - Reverse -- INT_MIN to -1
 *
 * A graph does not necessarily support all the speeds or
 * ranges listed above.
 *
 * If a graph does not support the requested speed, it selects,
 * from the appropriate range, the supported speed
 * that best matches the requested speed. For example, if a graph
 * supports only the fast forward speeds of 2x and 4x, a request
 * for a speed of 6000 is associated to fast forward range and
 * matched to the fast forward speed 4000.
 * If the graph does not support any speeds in the same range as
 * the requested speed, the call to iom_set_play_speed() fails.
 * For example, if a graph does not support any slow speeds, a
 * request for a speed of 999 will fail.
 *
 * The graph state reflects the adjusted (actual) speed, not
 * the requested speed.
 *
 * @param graph_id The graph handle
 * @param speed The speed to play at
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_play_speed(int graph_id, int speed);

/**
 * Used for still frames viewing.
 *
 * @param graph_id The graph handle
 * @param frames If positive moves forward that many frames, if negative goes backwards
 * @return 0 on success, -1 on error with errno set
 */
int             iom_jump_frames(int graph_id, int frames);


/**
 * Set the volume for a device that a graph is attached to.
 * If multiple graphs are playing to the same device,
 * this function only affects the volume of this graph.
 *
 * @param graph_id The graph handle
 * @param outputID Output ID obtained from iom_attach_output()
 * @param vol The volume information
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_volume(int graph_id, int outputID, iom_audio_volume_t const *vol);

/**
 * Get the volume for a device that a graph is attached to.
 *
 * @param graph_id The graph handle
 * @param outputID Output ID obtained from iom_attach_output()
 * @param vol Buffer for the volume information
 * @return 0 on success, -1 on error with errno set
 */
int             iom_get_volume(int graph_id, int outputID, iom_audio_volume_t * vol);

/**
 * Set the output device for the graph.
 * Some graphs may support playing to more than one output device
 * and changing them on the fly.
 *
 * @param graph_id The graph handle
 * @param device Specifies the output device
 * @param flags Device flags -- see enum iom_output_flags
 * @return a non-negative output ID, or -1 on error with errno set
 */
int             iom_attach_output(int graph_id, const char *device, unsigned flags);

/**
 * Detach an output device for the graph.
 *
 * @param graph_id The graph handle
 * @param outputID Output ID obtained from iom_attach_output()
 * @return 0 on success, -1 on error with errno set
 */
int             iom_detach_output(int graph_id, int outputID);

#define iom_detach_output_from_graph iom_detach_output

/**
 * Get the time information of the graph.
 *
 * @param graph_id The graph handle
 * @param time The time information is set on return
 * @return 0 on success, -1 on error with errno set
 */
int             iom_get_time(int graph_id, iom_graph_time_t * time);



/**
 * Get information about a track
 *
 * If url is NULL, information about the current track is returned
 * (i.e. the currently playing track, even if different from the current input;
 * or the current input track if nothing is playing).
 * If url is not NULL, information about the specified track is returned,
 * if the graph supports that.  Graphs may choose to reject calls with an URL
 * unless you have disabled playback (by asking iom_graph_capabilities() to
 * unset the IOM_GC_PLAYBACK flag).
 *
 * The information is returned in a re-useable buffer allocated by the function
 * (you must <em>not</em> allocate your own buffer and pass it in).  Reusing
 * the buffer may reduce the number of messages that need to be sent to io-media
 * to retrieve the information.  After you don't need the buffer any more,
 * don't forget to release it using iom_free_track_info().
 *
 * @param graph_id The graph handle
 * @param url The track to get information about, or NULL for the current input
 * @param info NULL, or a pointer to a buffer allocated by a previous call to iom_get_track_info()
 * @return NULL on error, or a buffer containing the information (same as info if not NULL)
 */
iom_track_info_t *iom_get_track_info(int graph_id, const char *url, iom_track_info_t *info);

/**
 * Free a track info buffer
 *
 * @param info NULL, or a buffer created by a call to iom_get_track_info()
 */
void iom_free_track_info( iom_track_info_t *info );

/**
 * Get the URL for an image.
 *
 * If the image is flagged as IOM_IMAGE_ONDEMAND and hasn't been loaded
 * (see below), this function fails and returns 0. On success, the
 * function returns the length of the URL and if the buffer is large
 * enough, copies the URL into it.
 * @param graph_id The graph handle
 * @param image_id The image ID
 * @param buf Buffer to hold the URL
 * @param blen The size of the bufefr
 * @return The length of the full URL (even if greater than blen),
 *         or zero of nailure
 */
_Sizet iom_get_image_url( int graph_id, _Uint32t image_id, char buf[], _Sizet blen );

/**
 * Save an image.
 *
 * This function asks the graph to save a copy of the image to the given
 * file or URL. The file is considered to be owned by the caller.
 * @param graph_id The graph handle
 * @param image_id The image ID
 * @param url The URL of the file to save the file to
 * @param load_id A cookie to be returned in an event
 * @return 0 on success, -1 on error with errno set
 */
int iom_save_image( int graph_id, _Uint32t image_id, const char *url, _Uint32t load_id );

/**
 * Load an image.
 *
 * This function asks the graph to start loading the given image. The
 * image ID must match an entry returned by the most recent
 * iom_getr_track_info() call for the current input, or the most recent
 * call with a specific URL.
 * If the load is successful, iom_unload_image() must eventually be called
 * with the same arguments to avoid resource leaks.
 * @param graph_id The graph handle
 * @param image_id The image ID
 * @param load_id A cookie to be returned in an event
 * @return 0 on success, -1 on error with errno set
 */
int iom_load_image( int graph_id, _Uint32t image_id, _Uint32t load_id );

/**
 * Unload an image.
 *
 * This function tells the graph that the client no longer needs this  
 * image.  If the load ID matches a job created by a previous
 * iom_save_image() or iom_load_image() call for the same image ID that
 * hasn't completed yet, it will be canceled.  If the load ID matches a
 * completed load job, it decrements the usage count associated with the 
 * saved image; if the IOM_IMAGE_ONDEMAND flag is set, the client should
 * not attempt to access the image file after calling this function.
 * @param graph_id The graph handle
 * @param image_id The image ID
 * @param image_id The job ID
 * @return 0 on success, -1 on error with errno set
 */
int iom_unload_image( int graph_id, _Uint32t image_id, _Uint32t load_id );

/**
 * Set metadata information.
 * Used with graphs that write to a file.
 *
 * @param graph_id The graph handle
 * @param data The metadata to save
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_metadata(int graph_id, const mm_metadata_t *data);

/**
 * Seek to a specific time location in the given file
 *
 * @param graph_id The graph handle
 * @param track_id The input file that the position applies to.
 *                 If that's not the currently playing file, the function may fail
 * @param milliseconds The time offset in milliseconds to seek to.  If 0 then beginning.
 *                     If the time offset is greater than the duration of the file, 
 *                     seek to the end. 
 * @return 0 on success, -1 on error with errno set
 */
int             iom_seek_time(int graph_id, _Uint64t track_id, _Uint64t milliseconds);

/**
 * Seek to a specific time location in the given title (applies to DVD, VCD, etc.)
 *
 * @param graph_id The graph handle
 * @param title The title number that the position is relative to
 * @param milliseconds The time offset in milliseconds to seek to.  If 0 then beginning.
 *                     If the time offset is greater than the duration of the file,
 *                     seek to the end.
 *                     
 * @return 0 on success, -1 on error with errno set
 */
int             iom_seek_title(int graph_id, _Uint16t title, _Uint64t milliseconds);

/**
 * Seek to a specific time location in the given chapter (applies to DVD, VCD, etc.)
 *
 * @param graph_id The graph handle
 * @param title The title number
 * @param chapter The chapter number within that title
 * @param milliseconds The time offset in milliseconds to seek to.  If 0 then beginning.
 *                     If the time offset is greater than the duration of the chapter,
 *                     seek to the end.
 * @return 0 on success, -1 on error with errno set
 */
int             iom_seek_chapter(int graph_id, _Uint16t title, _Uint16t chapter, _Uint64t milliseconds);

/**
 * Get the chapter and time information of the graph (applies to DVD, VCD, etc)
 *
 * @param graph_id The graph handle
 * @param time The time information is set on return
 * @param chapter   The title and chapter information is set on return
 * @return 0 on success, -1 on error with errno set
 */
int             iom_get_chapter_time(int graph_id, iom_graph_time_t * time, iom_chapter_time_t * chapter);

/**
 * Gets the status for the graph
 *
 * @param graph_id The graph to get the status for
 * @param status The graph status
 * @return 0 on success, -1 on error with errno set
 */
int             iom_get_status(int graph_id, iom_graph_status_t * status);

/**
 * Set track transition for a graph.
 * Controls options such as are cross-fade, gapless, and fade,
 * as well as scan mode (automatic switching to the next track
 * after playing a few seconds of the current one).
 *
 * @param graph_id The graph handle
 * @param trans Transition parameters to set
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_transition(int graph_id, iom_track_transition_t const *trans);

/**
 * Get track transition for a graph.
 *
 * @param graph_id The graph handle
 * @param trans Buffer to return transition parameters in
 * @return 0 on success, -1 on error with errno set
 */
int             iom_get_transition(int graph_id, iom_track_transition_t * trans);

/**
 * Set the notification interval.
 *
 * The time notification interval is the time between notifications when io-media
 * will notify clients during file play.
 *
 * @param graph_id The graph handle
 * @param interval The time interval in milliseconds
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_time_notification(int graph_id, _Uint32t interval);
int             iom_get_time_notification(int graph_id, _Uint32t * interval);

/**
 * Set Timeshifting Parameters for graphs that support timeshifting
 *
 * @param graph_id The graph handle
 * @param enable If true enables timeshifting support
 * @param bufferSize The maximum buffer size of the ring buffer on the hard drive, in KB
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_time_shifting(int graph_id, int enable, _Uint32t bufferSize);

/**
 * Set the value of a resource
 *
 * @param id A graph or control point handle
 * @param name The name of the resource
 * @param data The data to send as the value
 * @param len The number of bytes to send
 * @return 0 on success, -1 on error with errno set
 */
int             iom_set_resource(int id, const char *name, const void *data, _Sizet len);

/**
 * Get the value of a resource
 *
 * @param id A graph or control point handle
 * @param name The name of the resource
 * @param data The buffer to receive the value in
 * @param len The size of the buffer
 * @return The actual number of bytes in the resource (possibly greater than len),
 *         or -1 on error with errno set
 */
_Ssizet         iom_get_resource(int id, const char *name, void *data, _Sizet len);

/**
 * Set device.
 *
 * For graphs with their own navigation, such as DVD or iPod,
 * this function specifies the device to use.  For DVDs,
 * specify a mountpoint (such as /fs/cd0) rather than a block device
 * (such as /dev/cd0).
 *
 * @param graph_id The graph handle
 * @param device The device to use
 */
int             iom_set_device(int graph_id, const char *device);

/**
 *  Get the device information (disc, iPod, etc.)
 */
int             iom_get_device_info(int graph_id, iom_device_info_t * info);
#define iom_get_disc_info iom_get_device_info

/**
 *  Get the title information
 */
int             iom_get_title_info(int graph_id, _Uint32t title, iom_title_info_t * info);


/**
 *  Get the title information
 */
int             iom_get_chapter_info(int graph_id, _Uint32t title, _Uint32t chapter, iom_chapter_info_t * info);


/**
 *  Get the angle information for the current position
 */
int             iom_get_angle_info(int graph_id, mm_video_angle_info_t * info);

/**
 * Get the audio channel information for the given title
 */
int             iom_get_audio_info(int graph_id, int title, mm_video_audio_info_t * info);

/**
 * Get the audio channel information for the given title
 */
int             iom_get_subtitle_info(int graph_id, int title, mm_video_subtitle_info_t * info);



/* These fail if the title doesn't match the currently playing title */
int             iom_set_angle(int graph_id, int32_t title, int index);
int             iom_set_audio(int graph_id, int title, int index);
int             iom_set_subtitle(int graph_id, int title, int index);

/**
 * Get all the DVD system registers
 */
int             iom_get_sprms(int graph_id, _Uint16t sprms[24]);
/**
 * Get the DVD information for the current play state
 */
int		iom_get_dvd_status(int graph_id, mm_dvd_status_t *dvd_status);
/**
 * Get the video information for the given title
 */
int		iom_get_video_status(int graph_id, mm_video_status_t *video_status); 

/**
 *  Save playback state.
 *  Saves all the detail needed to resume playback from the current position,
 *  with the same angle, audio channel, subtitles, etc.
 *  @param graph_id The graph handle
 *  @param buf Buffer to save the state information in
 *  @param buflen The size of the buffer in bytes
 *  @return The number of bytes it takes to save the state
 *          (could be greater than buflen), or -1 on error
 */
_Ssizet    iom_save_state(int graph_id, void *buf, _Sizet buflen);

/**
 *  Resume from the saved state.
 *  Restores all the saved settings.
 *  @param graph_id The graph handle
 *  @param buf Buffer containing the saved state information
 *  @param buflen The length of the data in bytes
 *  @return 0 on success, -1 on error with errno set
 */
int        iom_restore_state(int graph_id, const void *buf, _Sizet buflen);

/**
 *  Read one or more events from the graph
 *
 *  Each event consists of a iom_event_header_t possibly followed by
 *  additional data, and then possibly a few bytes of padding to ensure
 *  alignment.  If more than one event is returned, use the
 *  iom_event_rounded_size() macro or the iom_next_header() function to
 *  find the next header based on the previous header's address and
 *  contents.
 *
 *  This function never returns partial events, except that instead of
 *  the first event that doesn't fit into the remaining space in the buffer,
 *  it may return just its length.  In particular, that's what happens when the
 *  first event doesn't fit into the given buffer: the function returns four
 *  and stores the 32-bit event length in the buffer.  This allows the client
 *  to reallocate the buffer and retry the read.
 *
 *  @param graph_id The graph handle
 *  @param buf Buffer to read events into
 *  @param buf_len Length of the buffer, in bytes
 *  @param arm Defines what to do if there are no events available immediately:
 *        - If \c NULL or points to a \c SIGEV_UNBLOCK event, the function blocks until an event arrives.
 *        - If points to an \c SIGEV_UNBLOCK event, the function just returns zero.
 *        - If points to some other event, the function returns zero and arms the given event.
 *
 *        At any given time, you can have at most one thread waiting for events or at most
 *        one sigevent armed.
 *
 *        There's a limit to the total size of unread events that io-media will
 *        hold for a client; when a graph overflows that limit, all unread events
 *        and any subsequent events are thrown away.   If the client then calls
 *        iom_read_events(), it fails with an \c EOVERFLOW, and then the queuing of
 *        events resumes.
 *
 *  @return The number of bytes read, or -1 on error
 */
_Ssizet         iom_read_events(int graph_id, void *buf, _Sizet buf_len, struct sigevent const *arm);

/**
 * Find the next event in the buffer
 *
 * Before calling this function, you need to
 * ensure that you have at least \c hdr->length
 * bytes of event data where \c hdr points to.
 * @param hdr The previous event header
 * @return The pointer to the next event header
 */
static inline iom_event_header_t *iom_next_header(iom_event_header_t * hdr) {
	return (iom_event_header_t *) ((char *)hdr + iom_event_rounded_size(hdr->length));
}


/**
 * Attach to a control point.
 *
 * Creates a handle that can be passed to 
 * iom_get_resource(), iom_set_resource(), and iom_read_events().
 * @param name The name of the control point
 * @param flags Must be zero for now
 * @return A non-negative new handle, or -1 on failure (errno is set)
 */
int iom_open_ctrlpnt( const char *name, unsigned flags );

/**
 * Detach from a control point.
 *
 * @param ctrlpnt_id A handle returned by iom_open_ctrlpnt()
 * @return 0 on success, -1 on error with errno set
 */
int iom_close_ctrlpnt( int ctrlpnt_id );

/**
 * Send a message to a control point.
 *
 * @param ctrlpnt_id A handle returned by iom_open_ctrlpnt()
 * @param msg The message
 * @param msg_len The length of the message in bytes
 * @param reply Reply buffer
 * @param reply_len The size of the reply buffer in bytes
 * @return Reply length on success (as specified by the control point), -1 on error with errno set
 */
ssize_t iom_ctrlmsg( int ctrlpnt_id, const void *msg, size_t msg_len, void *reply, size_t reply_len );

int iom_set_dvd_region_code (char const *iomedia_path, uint8_t dvd_region_code);

/**
* Set  Parental controls
*@param iomedia_path The full path to the io-media mount point or NULL for a local io-media
*@param pc a structure containing
* - \c country_code a representation of the 2 byte country codes defined by ISO 3166, the first character stored to the high order byte, the second to the low order byte 
*   (ie \c "US" would be \code ('U'<<8)|'S' \endcode )
* - \c level A value from 1 (most restrictive for audiences such as young children) to 8 (least restrictive, for mature audiences)
*/
int iom_set_parental_control (char const *iomedia_path, mm_parental_control_t const * const pc);

int iom_set_cppm_crypted_key(char const *io_media_path, void const * const data, size_t data_len);

int iom_set_video_properties( int graph_id, mm_video_properties_t *vattrs);

int iom_get_video_info( int graph_id, mm_video_info_t *vattrs);

int iom_get_time_shifting_extents(int graph_id, _Uint64t *earliestSeek, _Uint64t *latestSeek);

int iom_get_buffering_status(int graph_id, _Uint32t *state); /* state is one of iom_buffering_state_t */

/*@}*/

__END_DECLS

#endif
/* __SRCVERSION("api.h $Rev: 263760 $"); */
