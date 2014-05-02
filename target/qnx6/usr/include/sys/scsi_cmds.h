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



#ifndef __SCSI_CMDS_H_INCLUDED
#define __SCSI_CMDS_H_INCLUDED

#include <inttypes.h>
#include <gulliver.h>

#define ENDIAN_RET24(__x)		(((__x) >> 16) & 0xff) | \
								((__x) & 0xff00) | \
								(((__x) & 0xff) << 16))
#define ENDIAN_SWAP24(__x)		{ uint8_t __tmpx = ((uint8_t *)(__x))[0]; \
								((uint8_t *)(__x))[2] = ((uint8_t *)(__x))[0]; \
								((uint8_t *)(__x))[0] = __tmpx; }

#if defined(__LITTLEENDIAN__)
#define ENDIAN_LE24(__x)		(__x)
#define ENDIAN_BE24(__x)		ENDIAN_RET24(__x)

#define UNALIGNED_RET24(__p)	(((uint8_t volatile *)(__p))[0] | \
								(((uint8_t volatile *)(__p))[1] << 8) | \
								(((uint8_t volatile *)(__p))[2] << 16))

#ifndef __CPU_UNALIGNED_PUT24
#define UNALIGNED_PUT24(__p,__x) (((uint8_t volatile *)(__p))[0] = (__x) & 0xff, \
								((uint8_t volatile *)(__p))[1] = ((__x) >> 8) & 0xff, \
								((uint8_t volatile *)(__p))[2] = ((__x) >> 16) & 0xff)
#endif

#elif defined(__BIGENDIAN__)
#define ENDIAN_LE24(__x)		ENDIAN_RET24(__x)
#define ENDIAN_BE24(__x)		(__x)

#define UNALIGNED_RET24(__p)	((((uint8_t volatile *)(__p))[0] << 16) | \
								(((uint8_t volatile *)(__p))[1] << 8) | \
								((uint8_t volatile *)(__p))[2])

#ifndef __CPU_UNALIGNED_PUT24
#define UNALIGNED_PUT24(__p,__x) (((uint8_t volatile *)(__p))[0] = ((__x) >> 16) & 0xff, \
								((uint8_t volatile *)(__p))[1] = ((__x) >> 8) & 0xff, \
								((uint8_t volatile *)(__p))[2] = (__x) & 0xff)
#endif
#else
#error ENDIAN Not defined for system
#endif


#define SCSI_PUT16(cdb,off,v)	ENDIAN_RET16(__x)
#define SCSI_PUT16(cdb,off,v)	ENDIAN_RET16(__x)
#define SCSI_PUT16(cdb,off,v)	ENDIAN_RET16(__x)

#define SC_LUN_CDB(__x)			((__x) << 5)	// convert lun to CDB format

// SCSI Command Code definitions
// The first byte of the CDB is the operation code.  The top 3 bits
// are the group code field and the bottom 5 bits are the command code
// field.
// Group 0 - six-byte commands
// Group 1 - ten-byte commands
// Group 2 - ten-byte commands
// Group 3 - reserved
// Group 4 - reserved
// Group 5 - twelve-byte commands
// Group 6 - vendor specific
// Group 7 - vendor specific

// Group 0 Command Codes (00H - 1FH) (six byte commands)
#define SC_UNIT_RDY		0x00	// Test Unit Ready
#define SC_REZERO		0x01	// Rezero Unit
#define SC_REWIND		0x01	// Rewind (sequential-access device)
#define SC_VEN_02		0x02	// Vendor specific
#define SC_RQ_SENSE		0x03	// Request Sense
#define SC_FORMAT		0x04	// Format unit
#define SC_LIMITS		0x05	// Read Block Limits (sequential-access device)
#define SC_VEN_06		0x06	// Vendor specific
#define SC_REASSIGN		0x07	// Reassign Blocks
#define SC_READ			0x08	// Read
#define SC_VEN_09		0x09	// Vendor specific
#define SC_WRITE		0x0a	// Write
#define SC_SEEK			0x0b	// Seek
#define SC_TRACK_SEL	0x0b	// Track Select (sequential-access device)
#define SC_VEN_0C		0x0C	// Vendor specific
#define SC_VEN_0D		0x0D	// Vendor specific
#define SC_VEN_0E		0x0E	// Vendor specific
#define SC_RD_REVERSE	0x0f	// Read Reverse (sequential-access device)
#define SC_WR_FM		0x10	// Write Filemarks (sequential-access device)
#define SC_SPACE		0x11	// Space (sequential-access device)
#define SC_INQUIRY		0x12	// Inquiry
#define SC_VERIFY		0x13	// Verify
#define SC_RECOVER_BD	0x14	// Recover Buffered Data (sequential-access device)
#define SC_MSELECT		0x15	// Mode Select
#define SC_RES_UNIT		0x16	// Reserve Unit
#define SC_REL_UNIT		0x17	// Release Unit
#define SC_COPY			0x18	// Copy
#define SC_ERASE		0x19	// Erase (sequential-access device)
#define SC_MSENSE		0x1a	// Mode Sense
#define SC_SPINDLE		0x1b	// Start/Stop Unit
#define SC_LOAD			0x1b	// Load/Unload (sequential-access device)
#define SC_RCV_DIAG		0x1c	// Receive Diagnostic Results
#define SC_SND_DIAG		0x1d	// Send Diagnostic
#define SC_REMOVAL		0x1e	// Prevent/Allow Medium Removal
#define SC_RES_1F		0x1f	// (reserved)

// Group 1 Command Codes (20H - 3FH) (ten byte commands)
#define SC_VEN_20		0x20	// Vendor specific
#define SC_VEN_21		0x21	// Vendor specific
#define SC_VEN_22		0x22	// Vendor specific
#define SC_VEN_23		0x23	// Vendor specific
#define SC_READ_FORMATED_CAPACITIES		0x23
#define SC_SET_WIN		0x24	// Set Window (scanner device)
#define SC_GET_WIN		0x25	// Get Window (scanner device)
#define SC_RD_CAP		0x25	// Read Capacity
#define SC_VEN_26		0x26	// Vendor specific
#define SC_VEN_27		0x27	// Vendor specific
#define SC_READ10		0x28	// Read 10 byte
#define SC_RD_GEN		0x29	// Read Generation (optical-memory device)
#define SC_WRITE10		0x2a	// Write
#define SC_SEEK10		0x2b	// Seek
#define SC_POSITION		0x2b	// Position to Element
#define SC_LOCATE		0x2b	// Locate (sequential-access)
#define SC_ERASE10		0x2c	// Erase (optical-memory)
#define SC_RD_UB		0x2d	// Read Updated Block (optical-memory)
#define SC_WR_VER		0x2e	// Write with Verify
#define SC_VERIFY10		0x2f	// Verify
#define SC_SRCH_HI		0x30	// Search Data High
#define SC_SRCH_EQ		0x31	// Search Data Equal
#define SC_SRCH_LO		0x32	// Search Data Low
#define SC_LIMITS10		0x33	// Set Limits
#define SC_PREFETCH		0x34	// Pre-fetch (pre-read into cache)
#define SC_RD_POS		0x34	// Read position (sequential-access device)
#define SC_SYNC			0x35	// Synchronize Cache
#define SC_CACHE		0x36	// Lock/Unlock Cache
#define SC_RD_DEF		0x37	// Read Defect Data
#define SC_SCAN			0x38	// Medium Scan (optical-memory)
#define SC_COMPARE		0x39	// Compare
#define SC_CPY_VER		0x3a	// Copy and Verify
#define SC_WR_BUF		0x3b	// Write Buffer
#define SC_RD_BUF		0x3c	// Read Buffer
#define SC_UPD_BLK		0x3d	// Update Block (optical-memory)
#define SC_RD_LONG		0x3e	// Read long
#define SC_WR_LONG		0x3f	// Write long

// Group 2 Command Codes (40H - 5FH) (ten byte commands)
#define SC_CHG_DEF		0x40	// Change definition (SCSI-1, SCSI-2, CCS)
#define SC_WR_SAME		0x41	// Write same
#define SC_RD_SUBCH		0x42	// Read Sub-Channel (cd-rom)
#define SC_RD_TOC		0x43	// Read TOC (cd-rom)
#define SC_RD_HDR		0x44	// Read Header (cd-rom)
#define SC_REPORT_DENSITY	0x44	// Report Density Support
#define SC_PLAY			0x45	// Play Audio(10) (cd-rom)
#define SC_RES_46		0x46	// (reserved)
#define SC_GET_CONFIGURATION	0x46
#define SC_PLAY_MSF		0x47	// Play Audio MSF (cd-rom)
#define SC_PLAY_TI		0x48	// Play Audio Track Index (cd-rom)
#define SC_PLAY_TR		0x49	// Play Track Relative(10) (cd-rom)
#define SC_RES_4A		0x4a	// (reserved)
#define SC_PAUSE		0x4b	// Pause Resume (cd-rom)
#define SC_LSELECT		0x4c	// Log Select
#define SC_LSENSE		0x4d	// Log Sense
#define SC_RES_4E		0x4e	// (reserved)
#define SC_STOP_PLAY_SCAN 0x4e	// Stop Play/Scan (ATAPI)
#define SC_RES_4F		0x4f	// (reserved)
#define SC_MSELECT10	0x55	// Mode Select
#define SC_MSENSE10		0x5a	// Mode Sense
#define SC_PER_RES_IN   0x5e	// Persistent Reserve In
#define SC_PER_RES_OUT  0x5f	// Persistent Reserve Out

// Group 3 and 4, command codes 60H-9FH are reserved

// Group 5 command codes (A0H - BFH) (twelve byte commands)
#define SC_RES_A0		0xa0	// (reserved)
#define SC_RES_A1		0xa1	// (reserved)
#define SC_RES_A2		0xa2	// (reserved)
#define SC_RES_A3		0xa3	// (reserved)
#define SC_RES_A4		0xa4	// (reserved)
#define SC_MOVE			0xa5	// Move Medium (media-changer)
#define SC_PLAY12		0xa5	// Play Audio (cd-rom)
#define SC_EXCHANGE		0xa6	// Exchange Medium (media-changer)
#define SC_RES_A7		0xa7	// (reserved)
#define SC_GET_MSG		0xa8	// Get Message (communications device)
#define SC_READ12		0xa8	// Read (cd-rom)
#define SC_PLAY_TR12	0xa9	// Play Track Relative (cd-rom)
#define SC_SEND_MSG		0xaa	// Send Message (communications device)
#define SC_WRITE12		0xaa	// Write (optical-memory)
#define SC_RES_AB		0xab	// (reserved)
#define SC_ERASE12		0xac	// Erase (optical-memory)
#define SC_RES_AD		0xad	// (reserved)
#define SC_WR_VER12		0xae	// Write and Verify (optical-memory)
#define SC_VERIFY12		0xaf	// Verify (optical-memory)
#define SC_SRCH_HI12	0xb0	// Search Data High (cd-rom)
#define SC_SRCH_EQ12	0xb1	// Search Data Equal (cd-rom)
#define SC_SRCH_LO12	0xb2	// Search Data Low (cd-rom)
#define SC_LIMITS12		0xb3	// Set Limits (cd-rom)
#define SC_CD_SPEED		0xbb	// Set CD Speed (ATAPI)
#define SC_PLAY_CD		0xbc	// Play CD (ATAPI)
#define SC_READ_CD_MSF	0xb9	// Read CD MSF (ATAPI)
#define SC_CD_SCAN		0xba	// Scan (ATAPI)
#define SC_MECHANISM_STATUS	0xbd	// Mechanism Status (ATAPI)
#define SC_READ_CD		0xbe	// Read CD (ATAPI)

// Group 6 and 7, command codes C0H-FFH are vendor specific (Some WORMs)
#define SC_STANDBY		0xce	// Standby Check
#define SC_LOAD_G6		0xcf	// Load/Unload Unit
#define SC_RWD_DCB		0xd2	// Read DCB
#define SC_DREAD		0xee	// Disk Read
#define SC_DWRITE		0xef	// Disk Write

// Command Descriptor Block structure definitions

// CDB Flags
#define CF_LINK			0x01	// Linked-command indication
#define CF_FLAG			0x02	// Linked-command with flag bit
#define CF_VENDOR0		0x40	// Vendor unique bits
#define CF_VENDOR1		0x80

#define CF_FUA			0x08
#define CF_DPO			0x10

#include <_pack1.h>

typedef union _cdb {
	// generic 6 byte command descriptor block
	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		lba_byte1;
		uint8_t		lba_byte0;				// LSB
		uint8_t		transfer_len;
		uint8_t		control;
	} gen6;

	// generic 10 byte command descriptor block
	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		lba_byte3;
		uint8_t		lba_byte4;
		uint8_t		lba_byte1;
		uint8_t		lba_byte0;
		uint8_t		rsvd;
		uint8_t		transfer_len[2];
		uint8_t		control;
	} gen10;

	// generic 12 byte command descriptor block
	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		lba_byte3;
		uint8_t		lba_byte4;
		uint8_t		lba_byte1;
		uint8_t		lba_byte0;
		uint8_t		transfer_len[4];
		uint8_t		rsvd10;
		uint8_t		control;
	} gen12;

	struct _format_unit {
        uint8_t         op_code;
#define FU_RSVD0        0xc0                    // reserved bits
#define FU_FMTDAT       0x10
#define FU_CMPLIST      0x08
        uint8_t         defect_list_fmt;
        uint8_t         track_num;
        uint16_t        interleave;
        uint8_t         rsvd1[7];
	} format_unit;

	struct _format_unit_old {
        uint8_t         op_code;
        uint8_t         rsvd0;
        uint8_t         medium_type_code;
        uint8_t         rsvd1;
        uint8_t         interleave;
        uint8_t         rsvd2;
#define FMT_RSVD3               0x80
#define FMT_SECT_SIZE_CD        0x70
#define FMT_IMMED               0x08
#define FMT_HEAD                0x04
#define FMT_ST                  0x02
#define FMT_CERT                0x01
        uint8_t         cert;
        uint8_t         track_addr;
        uint8_t         rsvd4[4];
	} format_unit_old;

#define RW_OPT_RELADR	0x01
#define RW_OPT_CORRCT	0x02					// Disable Corrections
#define RW_OPT_FUA		0x08					// Force Unit Access
#define RW_OPT_DPO		0x10					// Disable Page Out
	struct {
		uint8_t		opcode;
		uint8_t		lun_lba;
		uint8_t		lba[2];
		uint8_t		transfer_len;
		uint8_t		control;
	} read_write6;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		lba[4];
		uint8_t		rsvd2;
		uint8_t		transfer_len[2];
		uint8_t		control;
	} read_write10;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		lba[4];
		uint8_t		transfer_len[4];
		uint8_t		rsvd2;
		uint8_t		control;
	} read_write12;

#define MSEL_OPT_PF		0x10			// Page Format
#define MSEL_OPT_SP		0x01			// Save Page
	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		param_length;
		uint8_t		control;
	} mode_select;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		param_length[2];
		uint8_t		control;
	} mode_select10;

	struct {
		uint8_t		opcode;
#define MSNS_OPT_DBD	0x08			// Disable Block Descriptors
		uint8_t		lun_opt;
#define PC_CURRENT		0x00
#define PC_CHANGEABLE	0x40
#define PC_DEFAULT		0x80
#define PC_SAVED		0xC0
		uint8_t		pc_page;
		uint8_t		rsvd3;
		uint8_t		allocation_length;
		uint8_t		control;
	} mode_sense;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		pc_page;
		uint8_t		rsvd3;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		allocation_length[2];
		uint8_t		control;
	} mode_sense10;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		prevent;
		uint8_t		control;
	} removal;

	struct {
		uint8_t		opcode;
#define LD_OPT_IMMED	0x01
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
#define LD_CMD_LOEJ		0x02
#define LD_CMD_START	0x01

// Sequential-Access
#define LD_CMD_SA_HOLD		0x08
#define LD_CMD_SA_EOT		0x04
#define LD_CMD_SA_RT		0x02			// re-tension
#define LD_CMD_SA_LOEJ		0x01
		uint8_t		cmd;
		uint8_t		control;
	} load;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
#define SC_OPT_RELADR	0x01
#define SC_OPT_IMMED	0x02
		uint8_t		lba[4];
		uint8_t		num_blocks[2];
		uint8_t		control;
	} synchronize_cache;

// cdrom commands
	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		rsvd7;
		uint8_t		resume;
		uint8_t		control;
	} pause_resume;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		start_minute;
		uint8_t		start_second;
		uint8_t		start_frame;
		uint8_t		end_minute;
		uint8_t		end_second;
		uint8_t		end_frame;
		uint8_t		control;
	} play_audio_msf;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		start_track;
		uint8_t		start_index;
		uint8_t		rsvd6;
		uint8_t		end_track;
		uint8_t		end_index;
		uint8_t		control;
	} play_audio_ti;

	struct {
		uint8_t		opcode;
#define RTOC_OPT_MSF	0x02
		uint8_t		lun_opt;
#define RTOC_FMT_TOC		0x0
#define RTOC_FMT_SESSION	0x1
#define RTOC_FMT_QSUBCODE	0x2
#define RTOC_FMT_QSUBCHNL	0x3
#define RTOC_FMT_ATIP		0x4
#define RTOC_FMT_CDTEXT		0x5
		uint8_t		format;
		uint8_t		rsvd3;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		start_track;
		uint8_t		allocation_length[2];
#define RTOC_CNTL_FMT_SESSION	0x40
		uint8_t		control_format;
	} read_toc;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2[6];
		uint8_t		allocation_length[2];
		uint8_t		rsvd3[2];
	} mechanism_status;

	struct {
		uint8_t		opcode;
#define EXCHANGE_OPT_IMMED	0x01
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
#define EXCHANGE_CMD_START	0x01
#define EXCHANGE_CMD_LOEJ		0x02
		uint8_t		cmd;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		rsvd7;
		uint8_t		slot;
		uint8_t		rsvd9;
		uint8_t		rsvd10;
		uint8_t		rsvd11;
	} exchange;

	struct {
		uint8_t		opcode;
		uint8_t		rt;
		uint8_t		feature_number[2];
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		allocation_length[2];
		uint8_t		control;
	} get_configuration;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		rsvd2;
		uint8_t		rsvd3;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		rsvd6;
		uint8_t		allocation_length[2];
		uint8_t		control;
	} read_formated_capacities;

	struct {
		uint8_t		opcode;
		uint8_t		lun_opt;
		uint8_t		read_speed[2];
		uint8_t		write_speed[2];
		uint8_t		rsvd2[6];
	} cd_speed;		

	struct {
		uint8_t		opcode;
#define RSCHNL_OPT_MSF		0x02
		uint8_t		lun_opt;
#define RSCHNL_DATA_SUBQ	0x40
		uint8_t		data;
		uint8_t		data_format;
		uint8_t		rsvd4;
		uint8_t		rsvd5;
		uint8_t		track;
		uint8_t		allocation_length[2];
		uint8_t		control;
	} read_subchannel;

	struct {
		uint8_t		opcode;
		uint8_t		lun_stype;
// expected sector type
#define RDCD_EST_ANY_SECTOR				(0 << 2)
#define RDCD_EST_CDDA_SECTOR			(1 << 2)
#define RDCD_EST_YELLOW_MODE1_SECTOR	(2 << 2)
#define RDCD_EST_YELLOW_MODE2_SECTOR	(3 << 2)
#define RDCD_EST_XA_SECTOR				(4 << 2)
#define RDCD_EST_XA_FORM2_SECTOR		(5 << 2)
		uint8_t		lba[4];
		uint8_t		transfer_len[3];
		uint8_t		flags;
#define RDCD_FLG_UDATA	0x10
#define RDCD_FLG_ECC	0x08
#define RDCD_FLG_SYNC	0x80
#define RDCD_FLG_HC_NONE		( 0x00 << 5 )
#define RDCD_FLG_HC_HDR			( 0x01 << 5 )
#define RDCD_FLG_HC_SUBHEADER	( 0x02 << 5 )
#define RDCD_FLG_HC_ALL_HEADERS	( 0x03 << 5 )
		uint8_t		subch_selection;
		uint8_t		rsvd3;
	} read_cd;

// sequential access commands
	struct {
		uint8_t		opcode;
#define ERASE_OPT_LONG	0x01
		uint8_t		opt;
		uint8_t		rsvd[3];
		uint8_t		control;
	} erase;

	struct {
		uint8_t		opcode;
#define LOCATE_OPT_CP	0x2
#define LOCATE_OPT_BT	0x4
		uint8_t		opt;
		uint8_t		rsvd2;
		uint8_t		ba[4];			// block address
		uint8_t		rsvd7;
		uint8_t		partition;
		uint8_t		control;
	} locate;

	struct {
		uint8_t		opcode;
		uint8_t		opt;
		uint8_t		rsvd2[3];
		uint8_t		control;
	} read_block_limits;

#define RP_OPT_BT	0x01			// block address type
#define RP_OPT_LNG	0x02			// long format
#define RP_OPT_TCLP	0x04			// total current logical position
	struct {
		uint8_t		opcode;
		uint8_t		opt;
		uint8_t		rsvd2[7];
		uint8_t		control;
	} read_position;

#define SRW_OPT_FIXED	0x01
#define SRW_OPT_SILI	0x02
	struct {
		uint8_t		opcode;
		uint8_t		opt;
		uint8_t		transfer_len[3];
		uint8_t		control;
	} sa_read_write6;

	struct {
		uint8_t		opcode;
		uint8_t		opt;
		uint8_t		rsvd[3];
		uint8_t		control;
	} rewind;

	struct {
		uint8_t		opcode;
#define SPACE_CODE_BLOCKS		0x00
#define SPACE_CODE_FMRKS		0x01
#define SPACE_CODE_SEQ_FMRKS	0x02
#define SPACE_CODE_EOD			0x03
#define SPACE_CODE_SMRKS		0x04
#define SPACE_CODE_SEQ_SMRKS	0x05
		uint8_t		code;
		uint8_t		count[3];
		uint8_t		control;
	} space;

	struct {
		uint8_t		opcode;
#define WF_OPT_IMMED	0x01
#define WF_OPT_WSMK		0x02
		uint8_t		opt;
		uint8_t		transfer_length[3];
		uint8_t		control;
	} write_filemarks;

	struct {
		uint8_t		opcode;
#define RD_OPT_MEDIA	0x01
		uint8_t		opt;
		uint8_t		rsvd[5];
		uint8_t		allocation_length[2];
		uint8_t		control;
	} report_density;

	struct {
		uint8_t		opcode;
#define FM_OPT_IMMED	0x01
#define FM_OPT_VERIFY	0x02
		uint8_t		opt;
#define FM_FMT_DFLT				0x00
#define FM_FMT_PARTITION		0x01
#define FM_FMT_FORMAT_PARTITION	0x02
		uint8_t		format;
		uint8_t		transfer_length[2];
		uint8_t		control;
	} format_media;
} CDB;

// SCSI status bytes
// (as per X3T9.2 revision 10 -- Table 27)
#define SCS_MASK		0x3e	// Mask valid bits
#define SCS_GOOD		0x00	// Good
#define SCS_CHECK		0x02	// Check Condition
#define SCS_MET			0x04	// Condition Met/Good
#define SCS_BUSY		0x08	// Target/LUN is Busy
#define SCS_INTER		0x10	// Intermediate/Good
#define SCS_INTERMET	0x14	// Intermediate/Condition Met/Good
#define SCS_CONFLICT	0x18	// Reservation Conflict
#define SCS_TERM		0x21	// Command Terminated
#define SCS_QUEUEFULL	0x28	// Queue Full

// SCSI Message Description
// (as per X3T9.2 revision 10 -- Table 10)
// The first byte in the message determines the message format.
// 		One-Byte Message (COMMAND COMPLETE)		0x00
//		Extended Message						0x01
//		One-Byte Message						0x02 - 0x1F
//		Two-Byte Message						0x20 - 0x2F
//		Reserved								0x30 - 0x7F
//		One-Byte Message (IDENTIFY)				0x80 - 0xFF
#define SCM_COMMAND_COMPLETE		0x00
#define SCM_EXTENDED_MSG			0x01
	#define SCM_MODIFY_DATA_POINTER	0x00
	#define SCM_SYNC_XFER_REQUEST	0x01
	#define SCM_EXTENDED_IDENTIFY	0x02
	#define SCM_WIDE_XFER_REQUEST	0x03
	#define SCM_WIDE_LEN			0x02
	#define SCM_SYNC_LEN			0x03
	#define SCM_MODIFY_LEN			0x05
#define SCM_SAVE_DATA_POINTER		0x02
#define SCM_RESTORE_POINTERS		0x03
#define SCM_DISCONNECT				0x04
#define SCM_INITIATOR_DETECTED_ERR	0x05
#define SCM_ABORT					0x06
#define SCM_MESSAGE_REJECT			0x07
#define SCM_NO_OPERATION			0x08
#define SCM_MESSAGE_PARITY_ERROR	0x09
#define SCM_LINKED_CMD_COMPLETE		0x0a
#define SCM_LINKED_CMD_COMPLETE_FL	0x0b
#define SCM_BUS_DEVICE_RESET		0x0c
#define SCM_ABORT_TAG				0x0d
#define SCM_CLEAR_QUEUE				0x0e
#define SCM_INITIATE_RECOVERY		0x0f
#define SCM_RELEASE_RECOVERY		0x10
#define SCM_TERM_IO_PROCESS			0x11
#define SCM_SIMPLE_QUEUE_TAG		0x20
#define SCM_HEAD_OF_QUEUE_TAG		0x21
#define SCM_ORDERED_QUEUE_TAG		0x22
#define SCM_IGNORE_WIDE_RESIDUE		0x23
#define SCM_IDENTIFY				0x80
	#define SCM_DISC_PRIV			0x40


// Definition of the SCSI-2 INQUIRY data format
typedef struct _scsi_inquiry {
	uint8_t peripheral;				// Peripheral Qualifier/Device Type
	uint8_t	rmb;					// Removable Medium
	uint8_t	version;				// Versions (ISO, ECMA, ANSI)
	uint8_t	rdf;					// Response Data Format/Flags
	uint8_t	adlen;					// Additional Data Length
	uint8_t	rsvd1[2];
	uint8_t	flags;
	uint8_t	vend_id[8];				// Vendor identification
	uint8_t	prod_id[16];			// Product identification
	uint8_t	prod_rev[4];			// Product revision level
	uint8_t	vend_spc[20];			// Vendor Specific
	uint8_t	rsvd3[40];
} SCSI_INQUIRY;

#define INQ_DTYPE_MSK		0x1f
#define INQ_DTYPE_WILDCARD	0xff

// INQUIRY Data flags
#define INQ_QUAL_MSK		0xe0
#define INQ_QUAL_AVAIL		0x00
#define INQ_QUAL_NOTAVAIL	0x20
#define INQ_QUAL_RESERVED	0x40
#define INQ_QUAL_NOTSUP		0x60
#define INQ_QUAL_VENDOR		0x80
#define INQ_RMB				0x80	// Removable Medium Bit
#define INQ_VANSI			0x07	// ANSI Approved Version
#define INQ_VECMA			0x38	// ECMA
#define INQ_VISO			0xc0	// ISO
#define INQ_AENC			0x80	// Asynchronous Event Notificaton Capability
#define INQ_TRM_IOP			0x40	// Terminate I/O Process bit
#define INQ_RDF				0x0f	// Response Data Format mask
#define INQ_REL_ADR			0x80	// Relative Addressing bit
#define INQ_WBUS32			0x40	// Wide Bus 32 (32 bit bus) support
#define INQ_WBUS16			0x20	// Wide Bus 16 (16 bit bus) support
#define INQ_SYNC			0x10	// Synchronous Data Transfers supported
#define INQ_LINKED			0x08	// Linked commands supported
#define INQ_RES				0x04	// (reserved)
#define INQ_CMD_QUE			0x02	// Tagged Command Queuing supported
#define INQ_SFT_RST			0x01	// Soft RESET alternative supported

// Sense Keys
#define SK_MSK			0x0F	// mask to sd_sense field for key
#define SK_NO_SENSE		0		// No sense data (no error)
#define SK_RECOVERED	1		// Recovered error
#define SK_NOT_RDY		2		// Device not ready
#define SK_MEDIUM		3		// Medium error
#define SK_HARDWARE		4		// Hardware error
#define SK_ILLEGAL		5		// Illegal Request (bad command)
#define SK_UNIT_ATN		6		// Unit Attention
#define SK_DATA_PROT	7		// Data Protect
#define SK_BLNK_CHK		8		// Blank Check
#define SK_VENDOR		9		// Vendor Specific
#define SK_CPY_ABORT	10		// Copy Aborted
#define SK_CMD_ABORT	11		// Aborted Command
#define SK_EQUAL		12		// Equal
#define SK_VOL_OFL		13		// Volume Overflow
#define SK_MISCMP		14		// Miscompare
#define SK_RESERVED		15		// Reserved

#define ASC_NO_SEEK_COMPLETE				0x02
#define ASC_NOT_READY						0x04
#define ASC_INVALID_COMMAND					0x20
#define ASC_INVALID_FIELD					0x24
#define ASC_INVALID_FIELD_PARAMETER			0x26
#define ASC_MEDIUM_CHANGED					0x28
#define ASC_BUS_RESET						0x29
#define ASC_INSUFFICIENT_TIME_FOR_OPERATION	0x2e
#define ASC_MEDIA_FORMAT					0x30	// bad format
#define ASC_MEDIA_NOT_PRESENT				0x3a
#define ASC_NOT_CONFIGURED					0x3e
#define ASC_OPERATOR_REQUEST				0x5a
#define ASC_INCOMPATIBLE_MEDIUM				0x64
#define ASC_COPY_PROTECTION					0x6f

#define ASCQ_CAUSE_NOT_REPORTABLE			0x00
#define ASCQ_BECOMING_READY					0x01
#define ASCQ_INIT_COMMAND_REQUIRED			0x02
#define ASCQ_MANUAL_INTERVENTION_REQUIRED	0x03
#define ASCQ_FORMAT_IN_PROGRESS				0x04
#define ASCQ_READ_SCRAMBLED					0x03
#define ASCQ_UNKNOWN_CHANGED				0xff	// NTO extension for fdc's

#define ASCQ_FILEMARK_DETECTED				0x01
#define ASCQ_EOPM_DETECTED					0x02	// End of Partition/Medium Detected
#define ASCQ_SETMARK_DETECTED				0x03
#define ASCQ_BOPM_DETECTED					0x04	// Beginning of Partition/Medium Detected

// SENSE error member
#define SENSE_EVALID	0x80		// Error Valid
#define SENSE_ECODE		0x7f		// Error Code Mask

// SENSE sense member
#define SENSE_FILEMARK	0x80		// Filemark
#define SENSE_EOM		0x40		// End-of-Medium (end/beginning of partition)
#define SENSE_ILI		0x20		// Incorect Length Indicator

// SENSE sks member
#define SENSE_BP		0x07		// Bit Pointer
#define SENSE_BPV		0x08		// Bit Pointer Valid
#define SENSE_CD		0x40		// Command Data


#define SENSE_SKSV		0x80

// Definition of the SCSI-2 Sense Data Structure
// Note: The field "sd_err" has the following format:
//        bit    7	- Address valid bit
//		  bits 6-4  - Error class
//		  bits 3-0  - Error code 
//
// Error classes 0-6 are vendor unique and also indicate that the
// sense data is in _nonextended_ format. (i.e. not usually used)
//		struct _scsi_nonextended_sense {
//			uint8_t	sd_err;
//			ulong_t	sd_block_address;
//		};
//
//	An error class of 7 and an error code of 0 (70H) indicate SCSI-1
//	extended sense data format (or SCSI-2 sense data format).
//
//	An error class of 7 and an error code of 1 (71H) indicate SCSI-2
//	deferred errors.
//
//	Error codes 72H to 7EH are reserved and error code 7FH indicates
//	a vendor-specific sense data format.
typedef struct _scsi_sense {
	uint8_t		error;				// Error Code
	uint8_t		segment;			// Segment number
	uint8_t		sense;				// Sense key/flags
	uint8_t		info[4];			// Information (32bit big-endian value)
	uint8_t		asl;				// Additional Sense Length
	uint8_t		csinfo[4];			// Command-Specific Information
	uint8_t		asc;				// Additional Sense Code
	uint8_t		ascq;				// Additional Sense Code Qualifier
	uint8_t		fruc;				// Field Replaceable Unit Code
	uint8_t		sks;				// Sense Key Specific
	uint16_t	sks_data;			// Sense Key Specific Data (16bit big-endian)
	uint16_t	asb;				// Additional Sense uint8_ts (Max 256-18)
} SCSI_SENSE;

// Mode Page Codes
#define MP_RW_ERR			0x01	// Read-Write error recovery page
#define MP_CONNECT			0x02	// Disconnect-reconnect page
#define MP_FMT_DEV			0x03	// Format device page
#define MP_GEOMETRY			0x04	// Rigid disk geometry page
#define MP_FLEX_DSK			0x05	// Flexible disk page
#define MP_RESERVED			0x06	// (reserved)
#define MP_VFY_ERR			0x07	// Verify error recovery page
#define MP_CACHING			0x08	// Caching page
#define MP_PERIPHERAL		0x09	// Peripheral device page
#define MP_CONTROL			0x0a	// Control mode page
#define MP_MEDIUM			0x0b	// Medium types supported page
#define MP_PARTITION		0x0c	// Notch and Partition page
#define MP_CD				0x0d	// CD-ROM Parameters page
#define MP_AUDIO_CONTROL	0x0e	// Audio Control page
#define MP_CD_CAP        	0x2a	// CD Capabilities and Mechanical Status
#define MP_SMART			0x2f	// SMART page
#define MP_ALL				0x3f	// Return all pages ("mode sense" only)

// Device Specific
#define MP_DS_WP			0x80	// Write Protected
	// Sequential Access
#define MP_DS_SA_BM_MSK		0x30	// Buffered Mode Mask
#define MP_DS_SA_BM_NONE	0x00	// return GOOD status after data xferd to media
#define MP_DS_SA_BM_TGT		0x10    // return GOOD status when data in target buffer

// Mode parameter header (6)
typedef struct _mode_param_header_6 {
	uint8_t		sense_len;
	uint8_t		medium_type;
	uint8_t		device_specific;
	uint8_t		block_desc_length;
} MODE_PARM_HEADER6;

// Mode sense parameter header (10)
typedef struct _mode_parm_header_10 {
	uint8_t		data_len[2];
	uint8_t		medium_type;
	uint8_t		device_specific;
	uint8_t		zero1;
	uint8_t		zero2;
	uint16_t	block_desc_length;
} MODE_PARM_HEADER10;

#define MP_BD_DENSITY_NOCHNG	0x7f
// Mode sense block descriptor
typedef struct _mode_block_descriptor {
	uint8_t		density;
	uint8_t		num_blocks[3];
	uint8_t		zero1;
	uint8_t		block_len[3];
} MODE_BLOCK_DESCRIPTOR;

#define MPAGE_PAGE_MSK		0x3f

typedef struct _mode_page_caching {
#define MP_PC_SAVE		0x80
	uint8_t		pc_page;
	uint8_t		page_length;
	uint8_t		cache;
#define MP_CACHE_RCD	0x01		// Read Cache Disable
#define MP_CACHE_MF		0x02		// Multiplication Factor
#define MP_CACHE_WCE	0x04		// Write Cache Enable
	uint8_t		retension_prio;
	uint8_t		disable_prefetch[2];
	uint8_t		min_prefetch[2];
	uint8_t		max_prefetch[2];
	uint8_t		max_prefetch_ceiling[2];
} MPAGE_CACHING;

typedef struct _mode_page_flexible_disk {
	uint8_t		pc_page;
	uint8_t		page_length;
	uint8_t		transfer_rate[2];
	uint8_t		number_heads;
	uint8_t		sectors_track;
	uint16_t	bytes_per_sector;
	uint16_t	number_cylinders;
	uint8_t		write_precomp[2];			// starting cylinder-write precompensation
	uint8_t		write_current[2];			// starting cylinder-reduced write current
	uint8_t		step_rate[2];				// drive step rate
	uint8_t		pulse_width;				// drive step pulse width
	uint8_t		head_settle[2];				// head settle delay
	uint8_t		motor_on_delay;				// motor on delay
	uint8_t		motor_off_delay;			// motor off delay
	uint8_t		rsvd1					:5,
				mo						:1,	// motor on
				ssn						:1,	// start sector number
				trdy					:1;	// true ready
	uint8_t		spc						:4,	// step pulse per cylinder
				rsvd2					:4;
	uint8_t		write_compensation;
	uint8_t		head_load;					// head load delay
	uint8_t		head_unload;				// head unload delay
	uint8_t		pin2					:4,
				pin34					:4;
	uint8_t		pin1					:4,
				pin4					:4;
	uint8_t		medium_rate[2];				// medium rotation rate
	uint8_t		rsvd3[2];
} MPAGE_FLEXIBLE_DISK;

typedef struct _mode_page_device_configuration {
	uint8_t		pc_page;
	uint8_t		page_length;
#define MP_DC_CAP		0x40				// change active partition
#define MP_DC_CAF		0x20				// change active format
	uint8_t		format;
	uint8_t		partition;					// active partition
	uint8_t		write_bfr;					// write buffer full ratio
	uint8_t		read_bfr;					// read buffer full ratio
	uint8_t		write_delay[2];				// write delay time

#define MP_DC_DBR		0x80				// data buffer recovery
#define MP_DC_BIS		0x40				// block identifiers supported
#define MP_DC_RSMK		0x20				// report setmarks
#define MP_DC_AVC		0x10				// automatic velocity control
#define MP_DC_SOCF_MSK	0x0c				// stop on consecutive filemarks mask
#define MP_DC_RBO		0x02				// recover buffer order
#define MP_DC_REW		0x01				// report early warning
	uint8_t		byte8;
	uint8_t		gap_size;					// gap size
#define MP_DC_EOD_MSK	0xe0				// end of data mask
#define MP_DC_EEG		0x10				// enable EOD generation (EEG)
#define MP_DC_SEW		0x08				// synchronize early warning
	uint8_t		byte10;
	uint8_t		ewarning[3];				// buffer size at early warning
	uint8_t		compression;				// select data compression algorithm
	uint8_t		rsvd15;
} MPAGE_DEVICE_CONFIGURATION;

typedef struct _partition_size_descriptor {
	uint8_t		partition_size[2];
} PARTITION_SIZE_DESCRIPTOR;

typedef struct _mode_page_medium_partition {
	uint8_t						pc_page;
	uint8_t						page_length;
	uint8_t						maximum_partitions;
	uint8_t						partitions_defined;
#define MP_MP_FDP		0x80				// fixed data partitions
#define MP_MP_SDP		0x40				// select data partitions
#define MP_MP_IDP		0x20				// initiator defined partitions
#define MP_MP_PSUM_MSK	0x18				// partition size unit of measure
	#define MP_PSUM_BYTES	0x00
	#define MP_PSUM_KBYTES	0x08
	#define MP_PSUM_MBYTES	0x10
	uint8_t						byte4;
	uint8_t						recognition;		// medium format recognition
	uint8_t						rsvd6;
	uint8_t						rsvd7;
	PARTITION_SIZE_DESCRIPTOR	partition_sizes[64];
} MPAGE_MEDIUM_PARTITION;

typedef struct _mode_page_data_compression {
	uint8_t		pc_page;
	uint8_t		page_length;
#define MP_DC_DCE		0x80				// data compression enable
#define MP_DC_DCC		0x40				// data compression capable
	uint8_t		byte2;
#define MP_DC_DDE		0x80				// data decompression enable
	uint8_t		byte3;
#define MP_DC_CMPR_DFLT				0x01
#define MP_DC_CMPR_IBM_ALDC_512		0x03
#define MP_DC_CMPR_IBM_ALDC_1024	0x04
#define MP_DC_CMPR_IBM_ALDC_2048	0x05
#define MP_DC_CMPR_IBM_IDRC			0x10
#define MP_DC_CMPR_DCLZ				0x20
	ulong_t		compression;				// compression algorithm
	ulong_t		decompression;				// decompression algorithm	
	uint8_t		rsvd[4];
} MPAGE_DATA_COMPRESSION;

typedef struct _mode_page_audio_control {
	uint8_t		pc_page;
	uint8_t		page_length;
	uint8_t		reserved1				:1,
				sotc					:1,
				immed					:1,
				reserved2				:5;
	uint8_t		reserved3;
	uint8_t		reserved4;
	uint8_t		format_lba				:4,
				reserved5				:3,
				aprval					:1;
	uint8_t		lba_per_sec[2];
	uint8_t		port0;
	uint8_t		volume0;
	uint8_t		port1;
	uint8_t		volume1;
	uint8_t		port2;
	uint8_t		volume2;
	uint8_t		port3;
	uint8_t		volume3;
} MPAGE_AUDIO_CONTROL;

typedef struct _mode_page_cd_cap {
	uint8_t		pc_page;
	uint8_t		page_length;
} MPAGE_CD_CAP;

typedef struct _mode_page_cd {
	uint8_t		pc_page;
	uint8_t		page_length;
	uint8_t		reserved1;
	uint8_t		multiplier;				// Inactivity Time Multiplier
	uint8_t		msf_s[2];				// Number of MSF - S Units per MSF - M Unit
	uint8_t		msf_f[2];				// Number of MSF - F Units per MSF - S Unit
} MPAGE_CD;

typedef struct _mode_page_format_device {
	uint8_t		pc_page;
	uint8_t		page_length;
	uint16_t	tracks;						// tracks per zone
	uint16_t	sectors;					// sectors per zone
	uint16_t	alt_tracks;					// alternate tracks per zone
	uint16_t	alt_sectors;				// alternate sectors per zone
	uint16_t	sectors_per_track;
	uint16_t	bytes_per_sector;
	uint16_t	interleave;
	uint16_t	track_skew_factor;
	uint16_t	cylinder_skew_factor;
	uint8_t		flags;						// surf, rmb, hsec, ssec
	uint8_t		rsvd2[3];
} MPAGE_FORMAT_DEVICE;

typedef struct _read_capacity {
	ulong_t		lba;
	ulong_t		blk_size;
} READ_CAPACITY;

typedef struct _read_header_data {
	uint8_t		data_mode;
	uint8_t		rsvd[3];
	uint16_t	addr;
} READ_HEADER_DATA;

typedef struct capacity_list_header {
	uint8_t		rsvd[3];
	uint8_t		capacity_list_length;
} CAPACITY_LIST_HEADER;

#define FEATURE_RANDOM_WRITABLE	0x20
#define FCD_UNFORMATTED			0x01
#define FCD_FORMATTED			0x02
#define FCD_NO_MEDIA			0x03
#define FCD_MSK					0x03
typedef struct formatted_capacity_descriptor {
	ulong_t		num_blocks;
	uint8_t		descriptor_type;
	uint8_t		block_length[3];
} FORMATED_CAPACITY_DESCRIPTOR;

#define RWD_RT_SFN				0x02
#define RWD_CURRENT				0x01
#define RWD_PERSISTENT			0x02
#define RWD_VERSION_MASK		0x3c
typedef struct random_writable_descriptor {
	uint16_t			feature_code;
	uint8_t				flags;
	uint8_t				additional_length;
	uint8_t				lba[4];
	ulong_t				blk_size;
	uint16_t			blocking;
	uint8_t				rsvd14;
	uint8_t				rsvd15_pp;
} RANDOM_WRITABLE_DESCRIPTOR;

typedef struct feature_header {
	uint8_t			data_length[4];
	uint8_t			rsvd4;
	uint8_t			rsvd5;
	uint8_t			current_profile[2];
} FEATURE_HEADER;

// ATAPI changer
#define MSH_CHANGER_READY			(0x0 << 5)
#define MSH_CHANGER_LOADING			(0x1 << 5)
#define MSH_CHANGER_UNLOADING		(0x2 << 5)
#define MSH_CHANGER_INITIALIZING	(0x3 << 5)
#define MSH_MECHANISM_IDLE			(0x0 << 5)
#define MSH_MECHANISM_AUDIO			(0x1 << 5)
#define MSH_MECHANISM_AUDIO_SCAN	(0x2 << 5)
#define MSH_MECHANISM_HOST			(0x3 << 5)
#define MSH_MECHANISM_UNKNOWN		(0x7 << 5)
typedef struct _mechanism_status_header {
	uint8_t		changer_state_slot;
	uint8_t		mech_state;
	uint8_t		current_lba[3];
	uint8_t		num_slots;
	uint8_t		slot_table_len[2];
} MECHANISM_STATUS_HEADER;

#define STR_DISC_PRESENT  0x80
#define STR_DISC_CHANGED  0x01
typedef struct _slot_table_response {
	uint8_t		flags;
	uint8_t		rsvd[3];
} SLOT_TABLE_RESPONSE;

typedef struct _read_position_data_shrt {
#define RPD_BOP		0x80		// begining of partition
#define RPD_EOP		0x40		// end of partition
#define RPD_BPU		0x04		// block position unknown
	uint8_t		flags;
	uint8_t		partition_number;
	uint8_t		rsvd2;
	uint8_t		rsvd3;
	uint8_t		first_block_location[4];
	uint8_t		last_block_location[4];
	uint8_t		rsvd12;
	uint8_t		number_blocks_buffer[3];
	uint8_t		number_bytes_buffer[4];
} READ_POSITION_DATA_SHRT;

typedef struct _read_position_data_lng {
#define RPD_BOP		0x80		// begining of partition
#define RPD_EOP		0x40		// end of partition
#define RPD_BPU		0x04		// block position unknown
	uint8_t		flags;
	uint8_t		rsvd1;
	uint8_t		rsvd2;
	uint8_t		rsvd3;
	uint8_t		partition_number[4];
	uint8_t		block_number[8];
	uint8_t		file_number[8];
	uint8_t		set_number[8];
} READ_POSITION_DATA_LNG;

typedef struct _density_support_header {
	uint16_t	density_support_length;
	uint8_t		rsvd1;
	uint8_t		rsvd2;
} DENSITY_SUPPORT_HEADER;

typedef struct _density_support_descriptor {
	uint8_t		primary_density_code;
	uint8_t		secondary_density_code;
#define DSD_CAP_WRTOK		0x80
#define DSD_CAP_DUP			0x40
#define DSD_CAP_DEFLT		0x20
	uint8_t		capabilities;
	uint8_t		rsvd3;
	uint8_t		rsvd4;
	uint8_t		bits_per_mm[3];
	uint8_t		media_width[2];
	uint8_t		tracks[2];
	uint8_t		capacity[4];
	uint8_t		assigning_organization[8];
	uint8_t		density_name[8];
	uint8_t		description[20];
} DENSITY_SUPPORT_DESCRIPTOR;

typedef struct _read_block_limits_data {
	uint8_t		granularity;
	uint8_t		maximum_block_length[4];
	uint8_t		minimum_block_length[2];
} READ_BLOCK_LIMITS_DATA;

#include <_packpop.h>

#endif

/* __SRCVERSION("scsi_cmds.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/lib/public/sys/scsi_cmds.h $ $Rev: 680334 $")
#endif
