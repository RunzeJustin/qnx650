/* =============================================================================
 * QNX Wavemakers Audio Library
 *
 * Copyright 2007-2009, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software 
 * Systems (QSS) and its licensors.  Any use, reproduction, modification, 
 * disclosure, distribution or transfer of this software, or any software 
 * that includes or is based upon any of this code, is prohibited unless 
 * expressly authorized by QSS by written agreement.  For more information 
 * (including whether this source code file has been published) please
 * email licensing@qnx.com.
 * ---------------------------------------------------------------------------*/
/**
 *  @internal
 *  @file            qwa_rcs.h
 * 
 *  QWA RCS error codes
 */
/* ===========================================================================*/
/** @addtogroup RCSERROR QWA_RCS Error Codes
 *  @{*/

#ifndef __QWA_RCS_ERR_H__
#define __QWA_RCS_ERR_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*----------------------------------------------------------------------------*/

    /** No error. */
#define QWA_RCS_OK                        0x0000

    /** Invalid pointer.
        An illegal pointer function argument has been used. */
#define QWA_RCS_ERR_INV_POINTER           0x0001

    /** Socket error.
        A TCP/IP socket operation has failed. */
#define QWA_RCS_ERR_SOCKET                0x0002

    /** Thread error.
        A thread operation has failed.  */
#define QWA_RCS_ERR_THREAD                0x0003

    /** Mutex error.
        A mutex operation has failed.  */
#define QWA_RCS_ERR_MUTEX                 0x0004

    /** Semaphore error.
        A semaphore operation has failed.  */
#define QWA_RCS_ERR_SEMA                  0x0006

    /** Invalid command.
        Server only. An invalid command has been requested. */
#define QWA_RCS_ERR_INV_COMMAND           0x0007

    /** Invalid get operation.
        Server only. An operation to get a QWA parameter has failed. */
#define QWA_RCS_ERR_INVALID_GET           0x0008

    /** Invalid set operation.
        Server only. An operation to set a QWA parameter has failed. */
#define QWA_RCS_ERR_INVALID_SET           0x0009

    /** Server busy.
        Server only. The server could not perform the specified 
        operation. */
#define QWA_RCS_ERR_BUSY                  0x000A

    /** Invalid audio path.
        Server only. An invalid audio path has been requested. */
#define QWA_RCS_ERR_INVALID_AUDIO_CHANNEL 0x000B

    /** User message.
        Server only. The user application has issued a message using 
        qwaRcsNotifyUserError(). */
#define QWA_RCS_ERR_USER                  0x000C

    /** Audio path busy.
        Server only. The audio queues are full and the requested 
        operation could not be performed. */
#define QWA_RCS_ERR_AUDIO_PATH_BUSY       0x000D

    /** Invalid audio buffer size.
        The function qwaRcsAudioInjectCreate() with an injection buffer size 
        which is not a power of two or a frameshift specified in the @a pAudio 
        argument to qwaRcsProcess() is unrealistic. */
#define QWA_RCS_ERR_INVALID_AUDIO_SIZE    0x000E

    /** Audio injection not initialized.
        The function qwaRcsProcessAudioInject() without first calling 
        qwaRcsAudioInjectCreate() or qwaRcsAudioInjectInit(). */
#define QWA_RCS_ERR_AUDIO_INJECT_NOT_INIT 0x000F

    /** Invalid buffer size.
        The function qwaRcsGetBinary() has been called with an invalid 
        buffer size. */
#define QWA_RCS_ERR_INVALID_BUFFSIZE      0x0011

    /** Invalid binary data buffer type. 
        The function qwaRcsGetBinary() has been called with an invalid 
        buffer type. */
#define QWA_RCS_ERR_INVALID_BUFFTYPE      0x0012

    /** Invalid injection client.
        Server only. The client does not have ownership of the audio 
        injection buffers. */
#define QWA_RCS_ERR_INVALID_INJECT_CLIENT 0x0013

    /** Allocation error.
        A memory allocation error occurred. */
#define QWA_RCS_ERR_ALLOC                 0x0014

    /** Audio path unavailable.
        Server only. The audio path specified for injection or streaming 
        is unavailable.  If streaming, a pointer to an audio buffer is not 
        available in the @a pAudio argument passed to qwaRcsProcss().  
        If injecting, the specified audio path has not been enabled with 
        qwaRcsAudioInjectCreate(). */
#define QWA_RCS_ERR_AUDIO_PATH_UNAVAILABLE 0x0015

    /** Unspecified error. 
        Internal server error. */
#define QWA_RCS_ERR_UNSPECIFIED           0x0010

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif
/**@}*/
