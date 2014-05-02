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
 *  @file            qwa_defs.h
 *  @author          QNX Wavemakers
 * 
 *  QWA data types and constants.
 */
/* ===========================================================================*/
/** @addtogroup DEF
 *  @{*/

#ifndef __QWADEFS_H__
#define __QWADEFS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/

#include <stddef.h>

/*----------------------------------------------------------------------------*/
/*     Constant definitions                                                   */
/*----------------------------------------------------------------------------*/

/** Maximum number of audio channels */
#define QWA_MAX_AUDIO_CNT       4
/** Maximum length of status string (including null termination) */
#define QWA_MAX_STRING_LEN    256
/** Length of send parametric EQ vector (5 nodes * 3 coefficients per node) */
#define QWA_SEND_PEQ_LEN       15
/** Length of receive parametric EQ vector (5 nodes * 3 coefficients per node) */
#define QWA_RECV_PEQ_LEN       15
/** True */
#define qwaTRUE                 1
/** False */
#define qwaFALSE                0

/*----------------------------------------------------------------------------*/
/* Signal types for generated diagnostic signals                              */
/*----------------------------------------------------------------------------*/

#define QWA_DIAG_SEND                   0    /**< Play the signal on microphone output */
#define QWA_DIAG_RECEIVE                1    /**< Play the signal on receive output */

#define QWA_DIAG_WHITE_NOISE            0    /**< White noise */
#define QWA_DIAG_WHITE_BAND_NOISE       1    /**< Pseudo white band-limited noise */
#define QWA_DIAG_PINK_NOISE             2    /**< Pseudo pink noise */
#define QWA_DIAG_SINE                   3    /**< Sine wave */
#define QWA_DIAG_SINE_AMP_SWEEP         4    /**< Sine wave with amplitude sweep */
#define QWA_DIAG_SINE_FREQ_SWEEP        5    /**< Sine wave with frequency sweep */
#define QWA_DIAG_SQUARE                 6    /**< Square wave */

/*----------------------------------------------------------------------------*/
/* qwaSetData() / qwaGetData() identification labels
     - RO - Read only
     - WB - Data can only be written before initialization, read anytime
     - WA - Data can only be written after initialization, read anytime
     - RW - Data can be written, read anytime
     - WO - Data can only be written after initialization, never read         */
/*----------------------------------------------------------------------------*/

#define qwaFrameInfo            0x0001 /* RO structure containing data about current frame    (tQwaFrameInfo)*/
#define qwaMicInCnt             0x0003 /* WB count of microphone input channels               (tQwaU16)*/
#define qwaRecvInCnt            0x0004 /* WB count of receive input channels                  (tQwaU16)*/
#define qwaOpMode               0x0008 /* WB operation mode (qwaHandsFree, qwaVoiceRecog)     (tQwaI32)*/  
#define qwaNRSwitch             0x0009 /* RW on/off switch for noise reduction                (tQwaI32)*/           
#define qwaAECSwitch            0x000A /* RW on/off switch for acoustic echo cancellation     (tQwaI32)*/                    
#define qwaRECSwitch            0x000C /* RW on/off switch for residual echo suppression      (tQwaI32)*/
#define qwaMixSwitch            0x0016 /* WB on/off switch for complex mixer                  (tQwaI32)*/          
#define qwaWNDBSwitch           0x0018 /* RW on/off switch for windbuffet suppression         (tQwaI32)*/
#define qwaAGCSwitch            0x0019 /* RW on/off switch for send agc                       (tQwaI32)*/              
#define qwaFrameShiftIn         0x001E /* WB input frame shift                                (tQwaU16)*/           
#define qwaSampleRateIn         0x001F /* WB input sample rate                                (tQwaU16)*/            
#define qwaMicClipStats         0x0020 /* RO mic clipping statistics structure                (tQwaClipStats)*/          
#define qwaRefClipStats         0x0021 /* RO reference clipping statistics structure          (tQwaClipStats)*/
#define qwaSendLimitMode        0x002A /* WB send limiter mode                                (tQwaI32)*/
#define qwaRecvEQSwitch         0x0026 /* RW on/off switch for receive equalization           (tQwaI32)*/
#define qwaRecvAGCSwitch        0x0027 /* RW on/off switch for receive agc                    (tQwaI32)*/
#define qwaWNDBMode             0x0029 /* WB windbuffet removal mode                          (tQwaI32)*/
#define qwaSendMuteSwitch       0x0034 /* RW send mute switch                                 (tQwaI32)*/
#define qwaRecvMuteSwitch       0x0035 /* RW receive mute switch                              (tQwaI32)*/
#define qwaFrameShiftOut        0x0037 /* RO output frame shift                               (tQwaU16)*/           
#define qwaSampleRateOut        0x0038 /* RO output sample rate                               (tQwaU16)*/            
#define qwaHFESwitch            0x0039 /* RW on/off switch for high frequency encoding        (tQwaI32)*/ 
#define qwaPostConfig           0x003B /* WO post configuration tuning data                   (tQwaI8[])*/
#define qwaRecvBWESwitch        0x003C /* RW on/off switch for receive bandwidth extension    (tQwaI32)*/
#define qwaAECFiltLen           0x003D /* WB acoustic echo cancellation filter length         (tQwaU16)*/
#define qwaPassThruSwitch       0x0041 /* WA on/off switch for pass-thru mode                 (tQwaI32)*/
#define qwaMaxFreqProc          0x0042 /* WB maximum frequency processed                      (tQwaU16)*/ 
#define qwaSendEQSwitch         0x0043 /* RW on/off switch for send equalization              (tQwaI32)*/           
#define qwaMaxCoreBinCnt        0x0044 /* RO max number of frequency bins                     (tQwaU16)*/             
#define qwaRefSampleRateIn      0x0046 /* WB reference input sample rate                      (tQwaU16)*/             
#define qwaRecvSampleRateIn     0x0047 /* WB receive input sample rate                        (tQwaU16)*/             
#define qwaRefFrameShiftIn      0x0048 /* RO reference input frame shift                      (tQwaU16)*/             
#define qwaRecvFrameShiftIn     0x0049 /* RO receive input frame shift                        (tQwaU16)*/             
#define qwaDiagSwitch           0x004A /* RW on/off switch for diagnostics                    (tQwaI32)*/
#define qwaRecvDLCSwitch        0x004B /* RW on/off switch for receive dynamic level control  (tQwaI32)*/
#define qwaMixFiltSwitch        0x004D /* RW on/off switch for complex mixer post filter      (tQwaI32)*/         
#define qwaRecvSampleRateOut    0x004E /* RO receive output sample rate                       (tQwaU16)*/             
#define qwaRecvFrameShiftOut    0x004F /* RO receive output frame shift                       (tQwaU16)*/             
#define qwaRecvClipStats        0x0052 /* RO receive clipping statistics structure            (tQwaClipStats)*/          
#define qwaSendDynEQSwitch      0x0053 /* RW on/off switch for send dynamic EQ                (tQwaI32)*/           
#define qwaRecvDTFSwitch        0x0055 /* RW on/off switch for receive double talk filter     (tQwaI32)*/
#define qwaRecvENSSwitch        0x0056 /* RW on/off switch for receive elect. noise suppress. (tQwaI32)*/

#define qwaMicResetClipStats    0x0800 /* WO reset mic clipping statistics                    (tQwaU16)*/
#define qwaMicInRMS             0x0802 /* RO mic input RMS                                    (tQwaI16)*/
#define qwaMicClipStatsMode     0x0803 /* WA mic clipping statistics reset mode               (tQwaU16)*/  

#define qwaRefResetClipStats    0x0C00 /* WO reset reference clipping statistics              (tQwaU16)*/
#define qwaRefDelay             0x0C02 /* RW reference delay in ms                            (tQwaI32)*/
#define qwaRefMaxDelay          0x0C03 /* WB maximum reference delay in ms                    (tQwaI32)*/
#define qwaRefInRMS             0x0C04 /* RO reference input RMS                              (tQwaI16)*/
#define qwaRefClipStatsMode     0x0C05 /* WA reference clipping statistics reset mode         (tQwaU16)*/   

#define qwaSendLimitThresh      0x1003 /* WA send limiter threshold in amplitude              (tQwaU16)*/                
#define qwaMicOutRMS            0x1006 /* RO mic output RMS                                   (tQwaI16)*/
#define qwaSendParamEQNodes     0x1007 /* WA send parametric EQ nodes                         (tQwaI16[QWA_SEND_PEQ_LEN])*/
#define qwaSendEQCurve          0x1008 /* RO send EQ curve in cdB                             (tQwaI16[])*/
#define qwaSendGain             0x1009 /* WA send fixed gain in cdB                           (tQwaI16)*/                
#define qwaMicOutClipStats      0x100B /* RO mic out clipping statistics                      (tQwaClipStats)*/          
#define qwaMicOutResetClipStats 0x100C /* WO reset mic out clipping statistics                (tQwaU16)*/
#define qwaMicOutClipStatsMode  0x100D /* WA mic out clipping statistics mode                 (tQwaI16)*/  
#define qwaSendParamEQ2Nodes    0x100E /* WA send parametric EQ2 nodes                        (tQwaI16[QWA_SEND_PEQ_LEN])*/
#define qwaSendEQ2Curve         0x100F /* RO send EQ2 curve in cdB                            (tQwaI16[])*/
#define qwaSendDynEQCurve       0x1010 /* RO send dynamic EQ curve in cdB                     (tQwaI16[])*/
#define qwaSendDynEQMinMaxSNR   0x1011 /* WA send dynamic EQ low and high SNR thresholds      (tQwaI16[2])*/

#define qwaRecvInRMS            0x1403 /* RO receive input RMS                                (tQwaU16)*/
#define qwaRecvOutRMS           0x1404 /* RO receive output RMS                               (tQwaU16)*/
#define qwaRecvLimitThresh      0x1405 /* WA receive limiter threshold in amplitude           (tQwaU16)*/  
#define qwaRecvParamEQNodes     0x1406 /* WA receive parametric EQ nodes                      (tQwaI16[QWA_RECV_PEQ_LEN])*/
#define qwaRecvEQCoeff          0x1407 /* RO receive EQ filter coefficients                   (tQwaI16[])*/
#define qwaRecvGain             0x1408 /* WA receive fixed gain in cdB                        (tQwaI16)*/
#define qwaRecvResetClipStats   0x1409 /* WO reset receive clipping statistics                (tQwaU16)*/
#define qwaRecvClipStatsMode    0x140B /* WA receive clipping statistics reset mode           (tQwaI16)*/  
#define qwaRecvOutClipStats     0x140D /* RO recv out clipping statistics                     (tQwaClipStats) */          
#define qwaRecvOutResetClipStats 0x140E /* WO reset recv out clipping stats                   (tQwaU16)*/
#define qwaRecvOutClipStatsMode 0x140F /* WA recv out clipping stats mode                     (tQwaI16)*/  

#define qwaAECEchoAlign         0x1800 /* RO estimated echo-alignment in ms                   (tQwaI16)*/
#define qwaAECResEchoRT60ms     0x1803 /* WA estimated resecho decay, in ms                   (tQwaU16)*/

#define qwaNRAtten              0x3000 /* WA target NR floor in cdB                           (tQwaI16)*/
#define qwaRECSuppress          0x3001 /* WA suppression of residual echo 0-100               (tQwaI16)*/

#define qwaWNDBSuppress         0x4000 /* WA suppression of wind buffets 0-100                (tQwaI16)*/

#define qwaSendAGCGainCur       0x4800 /* WA current AGC gain in cdB                          (tQwaI16)*/
#define qwaSendAGCGainVals      0x4801 /* WA AGC min, start and max gain in cdB               (tQwaI16[3])*/
#define qwaSendAGCAmpTgts       0x4802 /* WA AGC amp. target output range (min,max) in cdB    (tQwaI16[2])*/
#define qwaSendAGCMaxRates      0x4803 /* WA AGC max rise and fall rates in cdB/s             (tQwaI16[2])*/

#define qwaGSMBuzzStats         0x5C01 /* RO GSM buzz statistics                              (tQwaU32[2])*/
#define qwaResetGSMBuzzStats    0x5C02 /* WO reset GSM statistics                             (tQwaU16)*/
#define qwaNCGainFactor         0x5C03 /* RO noise compensation gain factor                   (tQwaU16)*/
#define qwaNCNoiseLevel         0x5C04 /* RO noise compensation current noise level           (tQwaI16)*/
#define qwaNCParams             0x5C05 /* WA noise compensation calibration parameters        (tQwaI16[5])*/

#define qwaHFEExtent            0x6000 /* WA extent of high-frequency encoding 0-100          (tQwaI16)*/

#define qwaDiagActive           0x6800 /* RO diagnostic activity flag                         (tQwaU16)*/
#define qwaDiagStop             0x6801 /* WO stop active diagnostic                           (tQwaU16)*/
#define qwaDiagPlaySignal       0x6802 /* WO play generated signal                            (tQwaI32[6])*/
#define qwaDiagLatencyTest      0x6803 /* WO start latency measurement for recv->mic          (tQwaI16[2])*/
#define qwaDiagLatencyEst       0x6804 /* RO latency estimate                                 (tQwaI16[3])*/
#define qwaDiagLatencyTestRef   0x6805 /* WO start latency measurement for recv->ref          (tQwaI16[2])*/

#define qwaMixFiltAtten         0x6C00 /* WA post filtering gain of mixer output in cdB       (tQwaI16)*/         

#define qwaRecvAGCGainCur       0x7000 /* WA current AGC gain in cdB                          (tQwaI16)*/
#define qwaRecvAGCGainVals      0x7001 /* WA AGC min, start and max gain in cdB               (tQwaI16[3])*/
#define qwaRecvAGCAmpTgts       0x7002 /* WA AGC amp. target output range (min,max) in cdB    (tQwaI16[2])*/
#define qwaRecvAGCMaxRates      0x7003 /* WA AGC max rise and fall rates in cdB/s             (tQwaI16[2])*/

#define qwaRecvBWEBrightness    0x7400 /* WA receive BWE brightness 0-100                     (tQwaI16)*/
#define qwaRecvBWEWarmth        0x7401 /* WA receive BWE warmth 0-100                         (tQwaI16)*/

#define qwaRecvDTFMaxAtten      0x8400 /* WA recv DTF maximum atten. in cdB                   (tQwaI16)*/
#define qwaRecvDTFMaxEchoRatio  0x8401 /* WA recv DTF max. echo to local ratio in cdB         (tQwaI16)*/
#define qwaRecvDTFResponse      0x8402 /* WA recv DTF responsiveness 0-100                    (tQwaI16)*/

#define qwaRecvENSSuppress      0x8800 /* WA receive ENS threshold                            (tQwaI16)*/
#define qwaRecvENSActivityRatio 0x8801 /* WA receive ENS speech activity ratio                (tQwaI16)*/

/*----------------------------------------------------------------------------*/
/*     Basic interface types                                                  */
/*----------------------------------------------------------------------------*/

typedef size_t                 tQwaSize;
typedef signed char            tQwaChar;
typedef int                    tQwaBool;
typedef unsigned char          tQwaU8;
typedef signed char            tQwaI8;
typedef unsigned int           tQwaU32;
typedef int                    tQwaI32;
typedef int                    tQwaInt;
typedef unsigned short         tQwaU16;
typedef short                  tQwaI16;

/*----------------------------------------------------------------------------*/
/*     QWA Types                                                              */
/*----------------------------------------------------------------------------*/

/** Handle to QWA library returned by qwaCreate() */
typedef void* tQwa; 

/** Audio pointer array used with qwaAudioIn() and qwaAudioOut() */
typedef tQwaI16* tQwaAudio[QWA_MAX_AUDIO_CNT];

/** Data identification parameter used with qwaSetData() and qwaGetData() */
typedef tQwaInt tQwaDataID;

/*----------------------------------------------------------------------------*/
/*     QWA enums                                                              */
/*----------------------------------------------------------------------------*/

/** On / Off / Idle switch settings */
typedef enum tQwaSwitch
{
   qwaOff             = 1,       /**< Off (default for most switches) */
   qwaOn              = 2,       /**< On */
   qwaIdle            = 3        /**< Initialized but inactive */
} tQwaSwitch;

/** Operation mode settings */
typedef enum tQwaOperationMode
{
   qwaHandsFree       = 1,       /**< Hands-free mode (default) */
   qwaVoiceRecog      = 2        /**< Voice-recognition mode */
} tQwaOperationMode;

/** Limiter mode settings */
typedef enum tQwaLimiterMode 
{
   qwaHardLimit       = 1,       /**< Hard threshold limiter (default) */
   qwaSoftLimit       = 2        /**< Dynamic threshold limiter */
} tQwaLimiterMode;

/** Windbuffet suppression mode settings */
typedef enum tQwaWindSuppressMode
{
   qwaSingleChannel   = 1,       /**< Windbuffet suppression in conjunction with noise reduction (default) */
   qwaMultiChannel    = 2,       /**< Windbuffet suppression in conjunction with mixer/beamformer */
   qwaCombined        = 3        /**< Both single- and multi-channel suppression */
} tQwaWindSuppressMode;

/*----------------------------------------------------------------------------*/
/*     Function return types                                                  */
/*----------------------------------------------------------------------------*/

#ifndef QWA_STATUS
/** Return type for QWA API calls that have a result status */
#define QWA_STATUS  tQwaInt
/** Return type for QWA API calls that do not return a value */
#define QWA_VOID    void
#endif

/*----------------------------------------------------------------------------*/
/*     Structure types                                                        */
/*----------------------------------------------------------------------------*/

/** Binary information structure. Used with qwaInitialize() to load a binary
    configuration.  Will overwrite any configuration settings previously set
    using qwaSetData(). */
typedef struct tQwaCfg 
{
   tQwaU16   usSize;                     /**< Binary configuration size */
   tQwaU8*   pData;       	         /**< Pointer to binary configuration data */
} tQwaCfg;

/** Frame information structure. You can retrieve general information regarding the current frame 
    by calling qwaGetData() with #qwaFrameInfo. */
typedef struct tQwaFrameInfo 
{
   tQwaU32   FrameCounter;               /**< Number of frames processed since initialization, or since reset */
   tQwaI16   VoicePresent;               /**< True if the frame is considered "voiced" */
   tQwaI16   AboveBackgroundNoise;       /**< True if the frame is considered "above background noise" */
   tQwaI16   PercentClipping;            /**< Percentage of clipped samples in the current frame */
   tQwaI16   InstantaneousSNR;           /**< Raw instantaneous Signal to Noise Ratio estimate in cdB for the current frame */
   tQwaI16   SmoothVNR;                  /**< Smoothed voice-to-noise ratio in cdB for the current frame */
   tQwaI16   ValidOutputCountdown;       /**< Number of frames until valid output, or 0 if output is valid */
} tQwaFrameInfo;

/** Clipping statistics structure. Clipping statistics are continuously gathered and stored for each
    microphone and reference channel. You can retrieve them by calling qwaGetData() with #qwaMicClipStats 
    or #qwaRefClipStats, and reset them with #qwaMicResetClipStats or #qwaRefResetClipStats. 
    
    An input sample is flagged as a clipping when its absolute value is greater than 32000. */
typedef struct tQwaClipStats
{
   tQwaU32   ClipFrames;                 /**< Number of frames since initialization, or since ClipStats reset */
   tQwaU32   ClipCount;                  /**< Number of clipped samples in last ClipFrames, or 0 on reset */
   tQwaI16   MaxAmp;                     /**< Max amplitude for last ClipFrames, or -32768 on reset */
   tQwaI16   MinAmp;                     /**< Min amplitude for last ClipFrames, or 32767 on reset */
} tQwaClipStats;

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
/**@}*/
