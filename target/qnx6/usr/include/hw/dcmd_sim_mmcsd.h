/*
 * $QNXLicenseC: 
 * Copyright 2008, QNX Software Systems.  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License"). You  
 * may not reproduce, modify or distribute this software except in  
 * compliance with the License. You may obtain a copy of the License  
 * at: http://www.apache.org/licenses/LICENSE-2.0  
 *  
 * Unless required by applicable law or agreed to in writing, software  
 * distributed under the License is distributed on an "AS IS" basis,  
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied. 
 * 
 * This file may contain contributions from others, either as  
 * contributors under the License or as licensors under other terms.   
 * Please review this entire file for other proprietary rights or license  
 * notices, as well as the QNX Development Suite License Guide at  
 * http://licensing.qnx.com/license-guide/ for other information. 
 * $ 
 */

/*
 *  dcmd_sim_mmcsd.h   Non-portable low-level devctl definitions
 *
*/

#ifndef __DCMD_SIM_MMCSD_H_INCLUDED
#define __DCMD_SIM_MMCSD_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#include <_pack64.h>

#define MMCSD_MAX_SLOTNAME_LEN	32
/* CID reg values of the card */
typedef struct _mmcsd_cid {
	_Uint32t		flags;	/*set MMCSD_FULL_CID flag t0 return raw/full cid contents */
	_Uint8t         rsvd[4];
	union{
		struct{
			_Uint32t            cid[4];
		}full_cid;
		union{
			struct{
				uint8_t 	mid;		// Manufacture ID
				uint8_t 	oid[3]; 	// OEM/Application ID
				uint8_t 	pnm[6]; 	// Product name
				uint8_t 	prv;		// Product revision
				uint32_t	psn;		// Product serial number
				uint16_t	mdt;		// Manufacture date
			}sd_cid;
			struct{
				uint32_t	mid;		// Manufacture ID
				uint16_t	oid;		// OEM ID
				uint8_t 	pnm[8]; 	// Product name
				uint8_t 	hwr;		// HW revision
				uint8_t 	fwr;		// FW revision
				uint32_t	psn;		// Product serial number
				uint8_t 	mcd;		// Month code
				uint16_t	ycd;		// Year code
			}mmc_cid;
		}parsed_cid;
	}cid;
	pid_t		pid;    			/* Store PID of driver process for this device */
	_Uint32t	speed; 				/*  Card speed currently working at */
	_Uint32t	media_change; 		/* Media change counter */
	_Uint8t		hwspec_version;		/* physical layer spec */
	_Uint8t		csd_version;		/* CSD structure version */
	_Uint8t		mmcprot_version;	/* MMC proto version */
	_Uint8t	type;				/* card type, MMC or SD for now */
	char		slotname[MMCSD_MAX_SLOTNAME_LEN];		/* slot name */
} MMCSD_CID;

/*flags definition */
#define MMCSD_FULL_CID			0x80000000	/* The client request a raw/full CID instead of parsed CID*/
#define MMCSD_DEV_RDONLY        0x00000001 /* write protected */
#define MMCSD_DEV_NO_MEDIA      0x00000002 /* no media inserted */
#define MMCSD_DEV_RDY      		0x00000004 /* Media is ready to accept IO */
#define MMCSD_DEV_PRELOAD      	0x00000008 /* device is in the slot before the driver started */
#define MMCSD_DEV_LOCKED        0x00000010 /* device is locked */
#define MMCSD_DEV_MEDIA_ERROR   0x00000020 /* device inserted but there are error when identify it */

#define MMCSD_CARD_TYPE_UNKNOWN	0x0
#define MMCSD_CARD_TYPE_MMC		0x1
#define MMCSD_CARD_TYPE_SD		0x2

#define DCMD_MMCSD_GET_CID       	__DIOTF(_DCMD_CAM, _SIM_MMCSD + 0, struct _mmcsd_cid)

#include <_packpop.h>

#endif
