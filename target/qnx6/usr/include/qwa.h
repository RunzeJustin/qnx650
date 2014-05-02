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
 *  @file            qwa.h
 *  @author          Leona Neufeld
 *
 *  QWA prototypes for core library functions
 */
/*============================================================================*/

#ifndef __QWAPROC_H__
#define __QWAPROC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

#include "qwa_defs.h"
#include "qwa_err.h"

/*--- Constructor ------------------------------------------------------------*/
QWA_STATUS qwaCreate( tQwa* phQwa );

/*--- Initialization ---------------------------------------------------------*/
QWA_STATUS qwaInitialize( tQwa           hQwa,
                          const tQwaCfg* pQwaCfg );

/*--- Destructor -------------------------------------------------------------*/
QWA_STATUS qwaDestroy( tQwa* phQwa );

/*--- Reset ------------------------------------------------------------------*/
QWA_STATUS qwaReset( tQwa hQwa );

/*--- Pass audio into QWA ----------------------------------------------------*/
QWA_STATUS qwaAudioIn( tQwa            hQwa,
                       void*           pUserData,
                       const tQwaAudio MicIn,
                       const tQwaAudio RecvIn,
                       const tQwaAudio RefIn );

/*--- Retrieve audio from QWA ------------------------------------------------*/
QWA_STATUS qwaAudioOut( tQwa      hQwa,
                        void**    ppUserData,
                        tQwaAudio MicOut,
                        tQwaAudio RecvOut );

/*--- Pass parameter data into QWA -------------------------------------------*/
QWA_STATUS qwaSetData( tQwa        hQwa,
                       tQwaDataID  iDataID,
                       tQwaInt     iChannel,
                       tQwaU32     ulSize,
                       const void* pData );

/*--- Retrieve parameter data from QWA ---------------------------------------*/
QWA_STATUS qwaGetData( tQwa       hQwa,
                       tQwaDataID iDataID,
                       tQwaInt    iChannel,
                       tQwaU32*   pulSize,
                       void*      pData );

/*--- Get an extended status message -----------------------------------------*/
QWA_STATUS qwaGetStatusMessage( const tQwa hQwa, 
                                tQwaChar   szStatusMessage[QWA_MAX_STRING_LEN]);

/*--- Get the QWA version ----------------------------------------------------*/
QWA_VOID qwaGetVersion( const tQwaU16*   pusVersionArray[4],
                        const tQwaChar** pszVersionString,
                        const tQwaChar** pszVersionComment );
                              
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
