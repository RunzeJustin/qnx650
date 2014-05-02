/* =============================================================================
 * QNX Wavemakers Audio Library
 *
 * Copyright 2007-2008, QNX Software Systems. All Rights Reserved.
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
 *  @file            qwa_err.h
 *  @author          Leona Neufeld
 * 
 *  QWA error codes.
 *
 */
/* ===========================================================================*/

 /**  @addtogroup QWAERROR QWA Error Codes
 *  @{
 */


#ifndef __QWAERR_H__
#define __QWAERR_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*              Non-fatal error codes (0x0000 - 0x000F)                       */
/*----------------------------------------------------------------------------*/

    /** No error. */
#define QWA_OK                                 0x0000

    /** Result not ready. 
        Returned by qwaAudioOut() when audio data is not ready for output
        (qwaAudioOut() is called out of sequence with qwaAudioIn()). */
#define QWA_NO_RESULT                          0x0002

    /** Only size information is valid. 
        Returned by the qwaGetData() when a null is input for the data 
        output pointer, and valid size information is returned for the 
        specified data ID. */
#define QWA_SIZE_ONLY                          0x119A

/*----------------------------------------------------------------------------*/
/*              General error codes (0x0100 - 0x01FF)                         */
/*----------------------------------------------------------------------------*/

    /** A memory allocation error has occurred. */
#define QWA_ERR_ALLOC                          0x0100

    /** An illegal null-pointer function argument has been used. */
#define QWA_ERR_NULL_POINTER                   0x0101

    /** Handle not initialized. 
        An attempt has been made to access functionality that is not 
        initialized (@a qwaOff at initialization). */
#define QWA_ERR_NOT_INIT                       0x0102

    /** Handle not created.
        Returned by qwaInitialize() if qwaCreate() is not called successfully 
        first. */
#define QWA_ERR_NOT_CREATED                    0x0103

    /** Handle already initialized. 
        Returned by qwaCreate() if @a phQwa points to a non-NULL value.
        Returned by qwaInitialize() if you called qwaInitialize() twice. */
#define QWA_ERR_ALREADY_INIT                   0x0104

    /** Invalid handle. */
#define QWA_ERR_INVALID_HANDLE                 0x0105

    /** Destruction failure.
        Returned by qwaDestroy() if an error occurs during destruction. */
#define QWA_ERR_DESTRUCTION_FAILED             0x0106

    /** Reset failure.
        Returned by qwaReset() if an error occurs during reset. */
#define QWA_ERR_RESET_FAILED                   0x0107

    /** Illegal set request. 
        Returned by the qwaSetData() if the specified data ID is 
        read-only or the requested parameter change is not allowed. */
#define QWA_ERR_ILLEGAL_SET_PARAM              0x0108

    /** Illegal set request before initialization. 
        Returned by the qwaSetData() when the specified data ID can
        be set only after qwaInitialize() has been called. */
#define QWA_ERR_ILLEGAL_SET_BEFORE_INIT        0x0109

    /** Illegal set request after initialization. 
        Returned by qwaSetData() when the specified data ID must be set  
        before qwaInitialize() is called. */
#define QWA_ERR_ILLEGAL_SET_AFTER_INIT         0x010A

    /** Invalid data ID. 
        Returned by qwaSetData() or qwaGetData() when the specified data ID 
        is invalid. */
#define QWA_ERR_INVALID_ID                     0x010B

    /** Invalid channel number. 
        Returned by qwaSetData() or qwaGetData() when the channel 
        number is invalid for the specified data ID. The channel 
        number should be between 0 and the maximum of valid channels 
        for which the specified parameter exists, minus 1. */
#define QWA_ERR_INVALID_CHANNEL                0x010C

    /** Invalid operation mode for set request.
        Returned by qwaSetData() if the requested parameter change
        is illegal given the current operation mode.  
        Also returned if qwaSetData() is called between 
        qwaAudioIn() and qwaAudioOut(). */
#define QWA_ERR_INVALID_OPERATION_MODE         0x010D

    /** Invalid size information.
        Returned by qwaSetData() or qwaGetData() when the size is invalid for 
        the specified data ID. */
#define QWA_ERR_INVALID_SIZE                   0x010E

    /** Invalid parameter.
        Returned at initialization if there is an error in the configuration 
        parameters. 
        Returned by the qwaSetData() if there was an error in the data
        for the specified data ID. */
#define QWA_ERR_PARAM                          0x010F

    /** Invalid sample rate. */
#define QWA_ERR_INVALID_SAMPLE_RATE            0x0111

    /** Invalid frame shift. */
#define QWA_ERR_INVALID_FRAME_SHIFT            0x0112

    /** Invalid number of input or output channels. */
#define QWA_ERR_INVALID_CHANNEL_CNT            0x0113

    /** Invalid FFT length. */
#define QWA_ERR_INVALID_FFT_LENGTH             0x0114

    /** Invalid filter length. */
#define QWA_ERR_INVALID_FILTER_LENGTH          0x0115

    /** Invalid endianness in binary configuration data or that used with @c qwaPostConfig. */
#define QWA_ERR_INVALID_ENDIANNESS             0x011A

    /** Invalid AEC filter length. */
#define QWA_ERR_AEC_FILTER_LEN                 0x0402

/*----------------------------------------------------------------------------*/
/*              Binary configuration error codes (0x0300 - 0x03FF)            */
/*----------------------------------------------------------------------------*/

    /** Invalid binary config id string. */
#define QWA_ERR_CFG_INVALID_IDSTR              0x0300

    /** Error in binary config data format. */
#define QWA_ERR_CFG_INVALID_FORMAT             0x0301

    /** Error in binary config header. */
#define QWA_ERR_CFG_INVALID_HEADER             0x0302

    /** Non-fatal error indicating that one or more binary configuration
        parameters were skipped because the feature associated with them 
        was not initialized.
        (e.g. The parameter qwaRecvBWEBrightness is specified in the 
              configuration but BWE is not turned on or set to idle.) 
        All other parameters were set successfully. */
#define QWA_ERR_CFG_PARAM_NOT_INITIALIZED      0x0304

    /** Non-fatal error indicating that one or more binary configuration
        were skipped because they were either unknown to this library version
        or they were of the wrong type (RO or WO). Only RW, WA or WB parameters
        are valid. This error would occur if a newer configuration was passed 
        to an older version of the library where the parameter is not yet 
        implemented. All other parameters were set successfully. */
#define QWA_ERR_CFG_UNKNOWN_PARAM              0x0307

    /** Binary config checksum error. */
#define QWA_ERR_CFG_INVALID_CHECKSUM           0x0308

    /** Length of binary configuration is too short or
        does not match that in configuration header. */
#define QWA_ERR_CFG_INVALID_SIZE               0x030B

    /** Invalid binary config version. */
#define QWA_ERR_CFG_INVALID_VERSION            0x030C

/*----------------------------------------------------------------------------*/
/*              Diagnostic error codes (0x0700 - 0x07FF)                      */
/*----------------------------------------------------------------------------*/

    /** Diagnostic activity in progress.  Wait for current test to complete
        or stop current test before starting new test. */
#define QWA_ERR_DIAGNOSTIC_ACTIVE             0x0700

    /** Diagnostic result data is not ready. The test may have not been started
        or may currently be in progress.  Also returned if diagnostic module
        is switched off. */
#define QWA_ERR_DIAGNOSTIC_NOT_READY          0x0701

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif
/**@}*/
