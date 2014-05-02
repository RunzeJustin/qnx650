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
 *  QWA RCS data types, constants and interface definitions.
 */
/* ===========================================================================*/

#ifndef __QWA_RCS_H__
#define __QWA_RCS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup RCSDEF
 *  @{*/

/*----------------------------------------------------------------------------*/

#include "qwa_defs.h"
#include "qwa_rcs_err.h"

/*----------------------------------------------------------------------------*/
/*     Constants                                                              */
/*----------------------------------------------------------------------------*/

/** Maximum number of QWA_RCS audio paths (see #tQwaRcsAudioPath) */
#define QWA_RCS_NUM_AUDIO_PATHS        5
/** Maximum size of buffer transferred with qwaRcsSetBinary() or qwaRcsGetBinary() */
#define QWA_RCS_MAX_BUFFER             2048

/** Default #tQwaRcsInjectFlags status */
#define QWA_RCS_FLAG_NONE              0x00U
/** Flag set in #tQwaRcsInjectFlags when audio is injected */
#define QWA_RCS_FLAG_INJECT            0x01U

/*----------------------------------------------------------------------------*/
/*     Types                                                                  */
/*----------------------------------------------------------------------------*/

/** Handle to QWA RCS returned by qwaRcsCreate() */
typedef void* tQwaRcs;

/** QWA RCS application control signals */
typedef enum tQwaRcsSignal
{
    qwaRcsNone,             /**< None. */
    qwaRcsReset,            /**< Reset. */
    qwaRcsRestart,          /**< Restart. */
    qwaRcsRestartCfg,       /**< Restart and initialize with binary configuration. */
    qwaRcsCfgAvailable,     /**< Retrieve binary configuration data downloaded from QWA RCS client. */
    qwaRcsCfgRequested,     /**< Reserved for future use. */
    qwaRcsConnect,          /**< Issued on client connection. */
    qwaRcsDisconnect        /**< Issued on client disconnection. */

} tQwaRcsSignal;

/** Binary buffer type used with qwaRcsSetBinary() and qwaRcsGetBinary(). 
    Currently only #qwaRcsBufferConfig is implemented.  There is the possibility of
    other buffer types in future releases.  */
typedef enum tQwaRcsBufferType
{
   qwaRcsBufferUndefined,   /**< Undefined. */
   qwaRcsBufferConfig,      /**< Binary configuration. */
} tQwaRcsBufferType;

/** QWA RCS audio channel enumeration.  
    Used to access @a iFrameShift in #tQwaRcsAudio. */
typedef enum tQwaRcsAudioPath
{
   qwaRcsPathMicIn,         /**< Microphone input */
   qwaRcsPathRecvIn,        /**< Receive input */
   qwaRcsPathRefIn,         /**< Reference input */
   qwaRcsPathMicOut,        /**< Microphone output */
   qwaRcsPathRecvOut,       /**< Receive output */
   qwaRcsPathUndefined,     /**< Undefined channel */

} tQwaRcsAudioPath;

/** QWA RCS audio data structure for streaming and injection */
typedef struct tQwaRcsAudio
{
   tQwaAudio MicIn;                                /**< Microphone input streaming/injection audio data */
   tQwaAudio RecvIn;                               /**< Receive input streaming/injection audio data */
   tQwaAudio RefIn;                                /**< Reference input streaming/injection audio data */
   tQwaAudio MicOut;                               /**< Microphone output streaming/injection audio data */
   tQwaAudio RecvOut;                              /**< Receive output streaming audio/injection data */
   tQwaInt   iFrameShift[QWA_RCS_NUM_AUDIO_PATHS]; /**< Frameshift values for each audio path type */

} tQwaRcsAudio;

/** QWA RCS injection flags.
    This structure is used in qwaRcsAudioInjectCreate() to specify which audio 
    paths are enabled for audio injection. Flags are set to 
    QWA_RCS_FLAG_INJECT to enable injection for the accessed audio path and channel.

    This structure is also used in qwaRcsProcessAudioInject() to specify on
    which path audio injection has occurred. Flags are set to 
    QWA_RCS_FLAG_INJECT if injection occurred on the accessed audio path and channel. */
typedef tQwaU8 tQwaRcsInjectFlags[QWA_RCS_NUM_AUDIO_PATHS][QWA_MAX_AUDIO_CNT];

/**@}*/

/*----------------------------------------------------------------------------*/
/*     Interface                                                              */
/*----------------------------------------------------------------------------*/

/*--- QWA_RCS module constructor ---------------------------------------------*/
QWA_STATUS qwaRcsCreate( tQwaRcs*                 phQwaRcs,
                         tQwaU16                  usServerPort );

/*--- QWA_RCS audio injection constructor ------------------------------------*/
QWA_STATUS qwaRcsAudioInjectCreate( tQwaRcs       hQwaRcs,
                                    tQwaU32       ulBufSize,
                                    tQwaRcsInjectFlags pFlags );
   
/*--- QWA RCS process init function ------------------------------------------*/
QWA_STATUS qwaRcsProcessInit( tQwa                hQwa,
                              tQwaRcs             hQwaRcs );

/*--- QWA_RCS main processing function w/ audio streaming --------------------*/
QWA_STATUS qwaRcsProcess( tQwa                    hQwa,
                          tQwaRcs                 hQwaRcs,
                          tQwaRcsSignal*          pSignal,
                          const tQwaRcsAudio*     pAudio );

/*--- QWA RCS audio injection processing -------------------------------------*/
QWA_STATUS qwaRcsProcessAudioInject( tQwaRcs      hQwaRcs,
                                     tQwaRcsInjectFlags  pFlags,
                                     const tQwaRcsAudio* pAudio );

/*--- QWA RCS audio injection destructor -------------------------------------*/
QWA_STATUS qwaRcsAudioInjectDestroy( tQwaRcs      hQwaRcs );

/*--- QWA RCS module destructor ----------------------------------------------*/
QWA_STATUS qwaRcsDestroy( tQwaRcs*                phQwaRcs );



/*--- Send notification to the QWA RCS client --------------------------------*/
QWA_STATUS qwaRcsNotifyUserError( tQwaRcs         hQwaRcs,
                                  const tQwaChar* szText );

/*--- Get binary data downloaded from the QWA RCS client ---------------------*/
QWA_STATUS qwaRcsGetBinary( tQwaRcs               hQwaRcs,
                            tQwaRcsBufferType     buffType,
                            tQwaU8*               data,
                            tQwaU16*              pusBufSize );

/*--- Get the QWA RCS version ------------------------------------------------*/
QWA_VOID qwaRcsGetVersion( const tQwaU16*         pusVersionArray[4],
                           const tQwaChar**       pszVersionString,
                           const tQwaChar**       pszVersionComment );

/*--- QWA_RCS audio injection initialization (deprecated) --------------------*/
QWA_STATUS qwaRcsAudioInjectInit( tQwaRcs         hQwaRcs,
                                  tQwaU32         ulBufSize );
   
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
