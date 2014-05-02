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



#ifndef IOFS_H_INCLUDED
#define IOFS_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <limits.h>
#include <gulliver.h>
#include <unistd.h>
#include <spawn.h>
#include <dirent.h>
#include <libgen.h>
#include <fcntl.h>
#include <share.h>
#include <process.h>
#include <pthread.h>
#include <time.h>
#include <fnmatch.h>
#include <devctl.h>
#include <gulliver.h>
#include <cipher.h>
#include <sys/fs_stats.h>
#include <sys/mman.h>
#include <sys/dcmd_fsys.h>
#include <sys/dcmd_dio.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>
#include <sys/disk.h>
#include <sys/cache.h>

//#define IOFS_MULTITHREAD			// Support multithreaded locking
#define IOFS_CHECKLOCK				// Check to make sure lock inversions do not occur
//#define IOFUNC_MOUNT_LOCK_FUNCS		// iofunc layers support lock function callouts
//#define ENABLE_MISS_CACHE			// Enable miss cache

#if !defined(DEBUG)
#define IFDBG	if(0)
#undef IOFS_CHECKLOCK
#else
#define IFDBG	if(1)
#endif

#define FS_PATH_MAX			1024		// largest path iofs code can handle (for symlinks)
#define FS_MAX_TYPES		16			// maximum number of file systems types

//
// Override the default file attribute and mount structures so we can add
// information specific for the nand filesystem. This must proceed includes below.
//

#ifndef IOFUNC_ATTR_T
 #ifndef FS_ATTR_T
  #define IOFUNC_ATTR_T		struct fsattr
 #else
  #define IOFUNC_ATTR_T		FS_ATTR_T
 #endif
#endif

#ifndef IOFUNC_MOUNT_T
 #ifndef FS_MOUNT_T
  #define IOFUNC_MOUNT_T	struct fsmount
 #else
  #define IOFUNC_MOUNT_T	FS_MOUNT_T
 #endif
#endif

#ifndef IOFUNC_OCB_T
 #ifndef FS_OCB_T
  #define IOFUNC_OCB_T		struct fsocb
 #else
  #define IOFUNC_OCB_T		FS_OCB_T
 #endif
#endif

#ifndef FS_INODE_T
#define FS_INODE_T			struct fsinode
#endif
FS_INODE_T;

#ifndef FS_ATTR_T
#define FS_ATTR_T			struct fsattr
#endif
FS_ATTR_T;

#ifndef DRIVER_T
#define DRIVER_T			struct driver
#endif
DRIVER_T;

#ifndef DEVICE_T
#define DEVICE_T			struct device
#endif
DEVICE_T;

#ifndef FS_MOUNT_T
#define FS_MOUNT_T			struct fsmount
#define FS_MOUNT_MBR(fmp, mbr)	((fmp)->mbr)
#else
#define FS_MOUNT_MBR(fmp, mbr)	((fmp)->fsmount.mbr)
#endif
FS_MOUNT_T;

#ifndef FS_OCB_T
#define FS_OCB_T			struct fsocb
#endif
FS_OCB_T;


#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/procmgr.h>
#include <sys/pathmgr.h>
#include <sys/types.h>
#include <sys/rsrcdbmgr.h>
#include <_pack64.h>

extern char		*__progname;

#ifdef __ARM__
extern uint32_t	__cpu_flags;
#ifndef ARM_CPU_FLAG_V6
#define ARM_CPU_FLAG_V6	0x0002
#endif
#define ISARM9	((__cpu_flags & ARM_CPU_FLAG_V6) == 0)
#else
#define ISARM9	0
#endif

#define strdupa(_s)		(((_s) && *(_s)) ? strcpy(_alloca(strlen(_s) + 1), (_s)) : "")

// Make it a if(0) to have the compiler strip the code
#define IFCHECK	if(dcp->op.integrity)

// fixed number file name bytes to cache per fsattr
#define ATTR_CACHE_FNAME_LEN	16

//
// Handy size conversion macros. The cluster conversion macros require the
// CLUSTERBITS macros to be set in the filesystem specfic header file. Never
// define it in this file. It is only usable in a filesystem specific file.
// The cache has 4 basic sizes. Only PAGES are required to run.
//
//   PAGES    - 4K
//   BUNDLES  - 64K
//   WADS     - 256K
//   THRONGS  - 1024K
// 
#define BLKBITS					9
#define BLKSIZE					(1 << (BLKBITS))
#define BLKMASK					((BLKSIZE)-1)
#define PAGEBITS				12
#define PAGESIZE				(1 << (PAGEBITS))
#define PAGEMASK				((PAGESIZE)-1)
#define CLUSTERMASK				((CLUSTERSIZE)-1)

#define BITS2BLKS(bits)			((bits) >> ((BLKBITS)+3))
#define BITS2PAGES(bits)		((bits) >> ((PAGEBITS)+3))
#define BITS2CLUS(bits)			((bits) >> ((CLUSTERBITS)+3))

#define BYTES2BITS(bytes)		((bytes) << 3)
#define BYTES2BLKS(bytes)		((bytes) >> (BLKBITS))
#define BYTES2PAGES(bytes)		((bytes) >> (PAGESBITS))
#define BYTES2CLUS(bytes)		((bytes) >> (CLUSTERBITS))

#define BLKS2BITS(blks)			((blks) << ((BLKBITS)+3))
#define BLKS2BYTES(blks)		((blks) << (BLKBITS))
#define BLKS2BYTES64(blks)		(((off64_t)(blks)) << (BLKBITS))
#define BLKS2PAGES(blks)		((blks) >> ((PAGEBITS)-(BLKBITS)))
#define BLKS2CLUS(blks)			((blks) >> ((CLUSTERBITS)-(BLKBITS)))

#define PAGES2BITS(pages)		((pages) << ((PAGEBITS)+3))
#define PAGES2BYTES(pages)		((pages) << (PAGEBITS))
#define PAGES2BYTES64(pages)	(((off64_t)(pages)) << (PAGEBITS))
#define PAGES2BLKS(pages)		((pages) << ((PAGEBITS)-(BLKBITS)))

#define CLUS2BITS(clus)			((clus) << ((CLUSTERBITS)+3))
#define CLUS2BYTES(clus)		((clus) << (CLUSTERBITS))
#define CLUS2BYTES64(clus)		(((off64_t)(clus)) << (CLUSTERBITS))
#define CLUS2BLKS(clus)			((clus) << ((CLUSTERBITS)-(BLKBITS)))

// mod must be a power of 2
#define RUP(val, mod)			(((val) + (mod) - 1) & ~((mod)-1))
#define RDN(val, mod)			(((val) & ~((mod) - 1))
#define ISPOW2(val)				(((val) & ((val) - 1)) == 0)
#define KILO(val)				((val) << 10)
#define MEGA(val)				((val) << 20)
#define GIGA(val)				((val) << 30)

// Used by drm and crypto routines
#define XOR128(dst, src) \
					((uint64_t *)dst)[0] ^= ((uint64_t *)src)[0],\
					((uint64_t *)dst)[1] ^= ((uint64_t *)src)[1]

// Same as above for non-aligned data
#define XOR128b(dst, src) \
					((uint8_t *)dst)[0] ^= ((uint8_t *)src)[0],\
					((uint8_t *)dst)[1] ^= ((uint8_t *)src)[1],\
					((uint8_t *)dst)[2] ^= ((uint8_t *)src)[2],\
					((uint8_t *)dst)[3] ^= ((uint8_t *)src)[3],\
					((uint8_t *)dst)[4] ^= ((uint8_t *)src)[4],\
					((uint8_t *)dst)[5] ^= ((uint8_t *)src)[5],\
					((uint8_t *)dst)[6] ^= ((uint8_t *)src)[6],\
					((uint8_t *)dst)[7] ^= ((uint8_t *)src)[7],\
					((uint8_t *)dst)[8] ^= ((uint8_t *)src)[8],\
					((uint8_t *)dst)[9] ^= ((uint8_t *)src)[9],\
					((uint8_t *)dst)[10] ^= ((uint8_t *)src)[10],\
					((uint8_t *)dst)[11] ^= ((uint8_t *)src)[11],\
					((uint8_t *)dst)[12] ^= ((uint8_t *)src)[12],\
					((uint8_t *)dst)[13] ^= ((uint8_t *)src)[13],\
					((uint8_t *)dst)[14] ^= ((uint8_t *)src)[14],\
					((uint8_t *)dst)[15] ^= ((uint8_t *)src)[15]


// Macros that read/write little endian values that may be unaligned
#define CHRGETLE16(p)		ENDIAN_LE16(UNALIGNED_RET16(p))
#define CHRGETLE32(p)		ENDIAN_LE32(UNALIGNED_RET32(p))
#define CHRGETLE64(p)		ENDIAN_LE64(UNALIGNED_RET64(p))
#define CHRPUTLE16(p, v)	UNALIGNED_PUT16((p), ENDIAN_LE16(v))
#define CHRPUTLE32(p, v)	UNALIGNED_PUT32((p), ENDIAN_LE32(v))
#define CHRPUTLE64(p, v)	UNALIGNED_PUT64((p), ENDIAN_LE64(v))

#define UPCALL_GETCMD(val)                  ((val) & 0xff)
#define UPCALL_GETARG1(val)                 (((val) >> 8) & 0xff)
#define UPCALL_GETARG2(val)                 (((val) >> 16) & 0xff)
#define UPCALL_GETARG3(val)                 (((val) >> 24) & 0xff)
#define UPCALL_SETVAL(cmd, a1, a2, a3)      (((a3) << 24) | ((a2) << 16) | ((a1) << 8) | (cmd))
#define UPCALL_SEND(gop, val)               MsgSendPulse(gop->coid, 12, gop->upcode, val)

#define UPCALL_DEVICE_INIT		0	// ARG1 - device index (gop->devices, ->index)
#define UPCALL_DEVICE_DESTROY	1	// ARG1 - device index (gop->devices, ->index)
#define UPCALL_DEVICE_NOMEDIA	2	// ARG1 - device index (gop->devices, ->index)
#define UPCALL_DEVICE_VERIFY	3	// ARG1 - device index (gop->devices, ->index)
#define UPCALL_DRVR_START_TBL	4	// ARG1 - driver init index (gop->drvrinits, ->code)
#define UPCALL_DEVICE_REFRESH	5	// ARG1 - device index (gop->devices, ->index)

// Current IOFS version Major and Minor
#define IOFS_VER_MAJOR		1
#define IOFS_VER_MINOR		0
#define IOFS_VER_CURRENT	(((IOFS_VER_MAJOR) << 8) | (IOFS_VER_MINOR))

#ifdef VARIANT_dll
#define IOFS_MODULE1(x)		iofs_module
#else
#define IOFS_MODULE1(x)		iofs_module_##x
#endif
#define IOFS_MODULE(x)		IOFS_MODULE1(x)

#define IOFS_STR1(x)		#x
#define IOFS_STR(x)			IOFS_STR1(x)

#define IOFS_CAT1(x,y)		x ## y
#define IOFS_CAT(x,y)		IOFS_CAT1(x,y)

#define TFS1(x,y)			x##y
#define TFS(x, y)			TFS1(x, y)

#define IFACE_FSYS			"fsys"
#define IFACE_DRVR			"drvr"
#define IFACE_VOLMGR		"volmgr"
#define IFACE_CRYPTO		"crypto"

struct globals;
struct fsiface {
	const char				*type;
	struct fsiface			*next;
	struct globals			*gop;
	const struct fsmodule	*module;
	unsigned				index;
};

struct check {
	const char				*name;
	int						size;
};

#define CHECK_MATCH_NUM(_s,_n)		{ "=I" IOFS_STR(_s), (_n) }
#define CHECK_MATCH_TYPE(_t)		{ "=T" IOFS_STR(_t), sizeof(_t) }
#define CHECK_MATCH_STRUCT(_s)		{ "=S" IOFS_STR(_s), sizeof(struct _s) }
#define CHECK_MATCH_OFFSET(_s,_m)	{ "=S" IOFS_STR(_s), offsetof(struct _s, _m) }

#if defined(VARIANT_dll) || defined(DEBUG)
#define CHECK_MODULE_VALID
#endif

//
// These are the structures used by exported functions, or function callouts
//
#define CHECK_FSYS_STRUCTS				\
	CHECK_MATCH_STRUCT(fsys),			\
	CHECK_MATCH_STRUCT(fsocb),			\
	CHECK_MATCH_OFFSET(fsinode, name),	\
	CHECK_MATCH_OFFSET(fsattr, fname_len),	\
	CHECK_MATCH_STRUCT(fsmount),		\
	CHECK_MATCH_STRUCT(blkfsattr)

#define CHECK_DRVR_STRUCTS				\
	CHECK_MATCH_STRUCT(driver),			\
	CHECK_MATCH_STRUCT(device)

#define CHECK_IOFS_STRUCTS				\
	CHECK_MATCH_STRUCT(globals),		\
	CHECK_MATCH_STRUCT(hier_dir),		\
	CHECK_MATCH_OFFSET(pathnode, buf),	\
	CHECK_MATCH_STRUCT(cachenode)

#define CHECK_CRYPTO_STRUCTS			\
	CHECK_MATCH_STRUCT(cryptoiface),	\
	CHECK_MATCH_OFFSET(fsattr, fname_len),	\
	CHECK_MATCH_STRUCT(fsmount),		\
	CHECK_MATCH_STRUCT(fscrypto)

#define CHECK_COMMON_STRUCTS			\
	CHECK_IOFS_STRUCTS,					\
	CHECK_FSYS_STRUCTS,					\
	CHECK_DRVR_STRUCTS

struct fsmodule {
	const char				*name;
	uint16_t				version;
	uint16_t				flags;
	const struct check		*check;
	struct mfuncs {
		int						(*init)(struct fsiface *ifp, unsigned version, const char *options);
		void					(*destroy)(struct fsiface *ifp);
		void					(*reserved[2])(void);
	}						funcs;
	void					*reserved[2];
	struct fsiface			*ifaces[8];
};

struct fsys {
	struct fsiface			iface;		// Must be first
	unsigned				mount_size;
	unsigned				attr_size;
	unsigned				inode_size;
	unsigned				inode_private_off;	// Zero if no private data
	unsigned				maxfids;
	unsigned				data_shift;
	struct ffuncs {
		int						(*mount)(FS_MOUNT_T *fmp, int flags, char const *options);
	}						funcs;
} ;

#define VOLMGR_EXTRA_LEN	64			// Number of bytes a volume manager can add to blkfsattr for its own use...

struct volmgr {
	struct fsiface			iface;		// Must be first
	unsigned				attr_size;
	struct vfuncs {
		int						(*enumerate)(FS_ATTR_T *fap, struct volmgr *vmp, const char *options);
 		int						(*devctl)(FS_ATTR_T *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval);
		void					(*addinfo)(FS_ATTR_T *fap, FS_MOUNT_T *fmp);
	}						funcs;
} ;

struct object {
	struct object_free {
		struct object_free		*next;
	}						*free;
	int						size;
	int						numfree;
	int						numtot;
} ;

enum objects {
	OBJ_CACHEDMAP = 0,
	OBJ_WRITECACHE,
	OBJ_FSOCB,
	OBJ_FSATTR,
	OBJ_FSMOUNT,
} ;

// Some handy macros
#ifdef __BIGENDIAN__
  #define BITSET(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] |= 0x80000000 >> (bitnum)%32)
  #define BITCLR(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] &= ~ (0x80000000 >> (bitnum)%32))
  #define BITTST(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] & (0x80000000 >> (bitnum)%32))
#else
  #define BITSET(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] |= 1 << (bitnum)%32)
  #define BITCLR(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] &= ~ (1 << (bitnum)%32))
  #define BITTST(bmp, bitnum) (((uint32_t *)bmp)[(bitnum)/32] & (1 << (bitnum)%32))
#endif

struct bitrange {
	unsigned	off;
	unsigned	len;
} ;

#define FS_TICKMSEC		500
#define TICK2NSEC(t)	((uint64_t)(t) << 16)
#define NSEC2TICK(ns)	((unsigned)((ns) >> 16))
#define MSEC2NSEC(ms)	((uint64_t)(ms) * 1000000)
#define NSEC2MSEC(ns)	((unsigned)((ns) / 1000000))
#define MSEC2TICK(ms)	NSEC2TICK(MSEC2NSEC(ms))

#define VECD(vec)	((char *)((vec).cap->data) + (vec).doff)

#define FID_FREE			0
#define FID_ROOT			1
#define FID_FIRSTFILE		16	// First fid available for normal files


#define FID_MASK		0x00ffffff
#define FID_LDDIR		0x00ffffff	// Only in hier_dir child link
#define NAMESUM_MASK	0xff000000
#define NAMESUM_SHIFT	24

#define NAMESUM_EMPTY	0		// unlinked and not in use (placeholder for readdir)
#define NAMESUM_MOVE1	1
#define NAMESUM_UNLNK	0xff	// unlinked file still in use
#define NAMESUM_MOVE2	0xfe

#define NUM_SYNTHETIC_FIDS			32
#define FID_SYNTHETIC(fmp, n)		(FS_MOUNT_MBR((fmp), hier.file_maxfids) + ((n) + 1))

#define FID_MNTINFO_DIR(fmp)		FID_SYNTHETIC((fmp), 0)		// Synthetic mountpoint info directory
#define FID_MNTINFO_REAL(fmp)		FID_SYNTHETIC((fmp), 1)		// Redirection file to real directory
#define MNTINFO_DIR_NAME			".FS_info."
#define MNTINFO_DIR_NAMESUM			(path_sum(MNTINFO_DIR_NAME))

#define FID_MNTINFO(fmp)			FID_SYNTHETIC((fmp), 2)		// XML filesystem information
#define MNTINFO_NAME				"info.xml"
#define MNTINFO_NAMESUM				(path_sum(MNTINFO_NAME))

#define FID_MNTINFO_DEVLNK(fmp)		FID_SYNTHETIC((fmp), 3)		// Symlink pointing to blkdev
#define MNTINFO_DEVLNK_NAME			"dev"
#define MNTINFO_DEVLNK_NAMESUM		(path_sum(MNTINFO_DEVLNK_NAME))


//
// The entire file structure hierarchy is in memory so we pack it tight
// and use macros to access the components. The 23 bits limit us
// to 8 million entries. Plenty for desktop and medium server systems.
// File systems can request an additional word to be allocated adjacent
// to each fid. The 32 bit value is for the private use of the file system
// and is refered to as offset. The node_get() callout is passed to offset
// values. The offset for the fid being requested if usually used with the
// parent directory fattr to find the inode information needed to describe the file.
// NOTE: LTFS does not need offset as it uses the FID to locate the inode information.
//
struct hier_file {		// 4 (or 8) bytes per file
	uint32_t	data;
//  31            24      20      16               8               0
//   x x x x x x x X x x x x x x x X x x x x x x x X x x x x x x x X
//   - - - - namesum|X|- - - - - - - - - - - - - - - - - - sibling23    data
//
};

#define GET_HPTR(fmp, fid)	(&(fmp)->hier.file_base[(fid)<<(fmp)->hier.data_shift])
#define GET_FID(fmp, p)		(((p) - &(fmp)->hier.file_base[0]) >> (fmp)->hier.data_shift)
#define GET_NAMESUM(p)		((p)->data >> NAMESUM_SHIFT)
#define GET_SIBLING(p)		((p)->data & FID_MASK)
#define GET_OFFSET(p)		(((p)+1)->data)

#define SET_NAMESUM(p, sum)	((p)->data = ((p)->data & ~NAMESUM_MASK) | ((sum) << NAMESUM_SHIFT))
#define SET_SIBLING(p, fid)	((p)->data = ((p)->data & ~FID_MASK) | ((fid) & FID_MASK))
#define SET_OFFSET(p, val)	(((p)+1)->data = (val))


//
// The hier_dir mapping exists for each file system.
//
#define MAX_FS_DIRS		1000000
struct hier_dir {		// 16 bytes per dir
	struct hier_dir	*next;
	uint32_t		data[3];
// Layout of data which is accessed by the GET/SET/INC/DEC macros below.
// We make get/set on parent the worst because it is very rarely done.
//  31            24      20      16               8               0
//   x x x x x x x X x x x x x x x X x x x x x x x X x x x x x x x X
//   pare3|- - -free|- - - - - - - - - - - - - - - - - - - - - -me24    data[0]
//   - - - - parent8|- - - - - - - - - - - - - - - - - - - - child24    data[1]
//   - - - - - - - -parent13|- - - - - - - - - - - - - - - -nlinks19    data[2]
};
#define GET_ME(p)				((p)->data[0] & 0x00ffffff)
#define GET_CHILD(p)			((p)->data[1] & 0x00ffffff)
#define GET_NLINKS(p)			((p)->data[2] & 0x0007ffff)
#define GET_PARENT(p)			(((p)->data[2]>>19) | (((p)->data[1] & 0xff000000)>>11) | (((p)->data[0] & 0xe0000000)>>8))

#define SET_ME(p, fid)			((p)->data[0] = ((p)->data[0] & 0xff000000) | (fid))
#define SET_CHILD(p, fid)		((p)->data[1] = ((p)->data[1] & 0xff000000) | (fid))
#define SET_NLINKS(p, links)	((p)->data[2] = ((p)->data[2] & ~0x7ffff) | (links))
#define DEC_NLINKS(p)			(--(p)->data[2])
#define INC_NLINKS(p)			(++(p)->data[2])
#define SET_PARENT(p, fid)		((p)->data[0] = ((p)->data[0] & 0x1fffffff) | (((fid)&0x00e00000)<< 8),\
								 (p)->data[1] = ((p)->data[1] & 0x00ffffff) | (((fid)&0x001fe000)<< 11),\
								 (p)->data[2] = ((p)->data[2] & 0x0007ffff) | (((fid)&0x00001fff)<< 19))
#define NLINKS_MAX				0x7ffff

// Structure is always a multiple of 4 bytes (unit32_t aligned).
struct metanode {
	struct metanode	*next;
	uint32_t	tfid;		// 8 bits of type followed by 24 bits of fid
	uint32_t	len;		// Size of metanode in words
							// Variable length data follows here
};
#define MNODE_PTR(p, idx)	((struct metanode *)(&(p)->meta_base[idx]))
#define MNODE_IDX(p, nap)	((uint8_t *)(nap) - (p)->meta_base)
#define MNODE_FID(tfid)		(tfid & 0xffffff)
#define MNODE_ALIGN(len)	(((len) + 3) & ~3)
#define MNODE_HDRLEN		sizeof(struct metanode)
#define MNODE_MAXRECLEN		1024

#define MNODE_TYPE_DEAD		0
#define MNODE_TYPE_FSINODE	1
#define MNODE_TYPE_FIRST	16	// First available for fsys private use

//
// The io-fs core compiles with MAX_FNAME_LEN undefined so we set it to 1.
// Each fs will set MAX_FNAME_SIZE to be its maximum file name size. The core
// uses alloca to create this structure and does not create a static version on
// the stack. The size of the structure is defined by fmp->attr_size and is set
// by each fs.
//
#ifndef MAX_FNAME_LEN
	#define MAX_FNAME_LEN	1
#endif

struct fsinode {
	uint32_t	fid;			// I fileID (only zero during hier_build_node_get)
	uint32_t	offset;			// I Often an index into the directory block/cluster
	FS_ATTR_T	*parent;		// I pointer to parent
	unsigned	flags;			// O        Flags identifying valid fields and for special operations (NODE_GET_*)
	uint32_t	entsize;		// O ENTLEN Size of directory entry (used for hier_build_node_get, 0==EOF)
	// mode must be the 1st output member after entsize (these can be cached with MNODE_TYPE_FSINODE)
	uint32_t	mode;			// O MODE   File mode
	uint64_t	ino;			// O INODE  Inode
#define IOFS_DYNAMIC_SIZE  ~0ULL
	uint64_t	size;			// O MISC   File size (always 0 for directories, IOFS_DYNAMIC_SIZE for dynamic files)
	uint32_t	uid;			// O MISC   User ID of owner
	uint32_t	gid;			// O MISC   Group ID of owner
	dev_t		rdev;			// O MISC   rdev number (for S_ISNAM files)
	uint32_t	nlink;			// O MISC   Number of links to a file
	time_t		atime;			// O MISC   Time of last access
	time_t		mtime;			// O MISC   Time of last modification
	time_t		ctime;			// O MISC   Time of last change
	uint16_t	namelen;		// O NAME   If non-zero it is the length of the name
	char		name[MAX_FNAME_LEN + 1];	// O
};

struct pathnode {
	FS_ATTR_T			*target;
	FS_ATTR_T			*parent;
	char				*name;					// Last resolved component
	char				*symlink;				// New symlink
	char				*tail;					// Residue after symlink
	char				buf[FS_PATH_MAX + 1];
} ;

struct diobuf {
	unsigned			size;
	unsigned			scoid;
	void				*vaddr;
	unsigned			nvec;
	struct cachenode	**cavec;
	struct iovec		*iovec;
	struct cachenode	*capbase;
} ;

struct cachedmap {
	struct cachedmap	*next;
	uint32_t			blk;
	uint32_t			nblks;
} ;

struct cachenode {
	struct cachenode	*hash_next;		// Must be first item in structure!
	struct cachenode	*hash_prev;
	struct cachenode	*lru_next;
	struct cachenode	*lru_prev;
	paddr64_t			paddr;			// Physical addr of data
	struct cachedmap	dmap;			// The 1st disk map entry
	unsigned			blk;			// The blk relative to the file fid
	uint16_t			nblks;			// The number of blks vaddr/paddr point to
	int16_t				links;			// The number of active links
	void				*data;			// Where the data is in our address space
	struct fsattr		*fap;			// Used for rover verification
} ;

#define ATTR_VEC_SIZE	16
struct writecache {
	unsigned			nvec;
	struct cachenode	*cavec[ATTR_VEC_SIZE];
	struct iovec		iovec[ATTR_VEC_SIZE];
} ;

enum allocation_type {
	ATYPE_PAGE = 0, ATYPE_BUNDLE, ATYPE_WAD, ATYPE_THRONG, NUM_ATYPES
} ;
#define ATYPE_MASK	(NUM_ATYPES - 1)	// NUM_ATYPES must be a power of 2!

// Flags passed to cache routines.
#define CACHE_PAGE				0x001	// We insist on getting a cluster (no bundle, ..)
#define CACHE_DIO				0x004
#define CACHE_DISCARD			0x008
#define CACHE_NOPUTREL			0x010
#define CACHE_INVALIDATE		0x020
#define CACHE_REPLACE			0x040
#define CACHE_NOCRYPT			0x080
#define CACHE_PREREAD			0x100

struct mapnode {
	struct mapnode	*next;		// Must be first item in structure!
	struct extent {
		unsigned		beg;	// Usually a file relative cluster or blk - 0, 1, 2, ...
		unsigned		len;	// Usually number of clusters or blks mapped by val at beg
		unsigned		val;	// An index into mappings (eg: ltfs) or a blk (eg: qnx4)
	} ext;
} ;
#define MK_FSFID(fmp, fid)	(fid)
#define MAP_BEFORE	0
#define MAP_HIT		1
#define MAP_MISS	2

struct span {
	unsigned	fblk;			// Span start relative to the file - 0, 1, 2, ...
	unsigned	nblks;			// Size of span
	unsigned	dblk;			// Disk blk for start of span
#define SPAN_NOT_MAPPED	(~0u-1)	// May be returned in dblk in etfs
} ;

struct growsize {
	unsigned	fsize;
	unsigned	gsize;
};

struct fsattr {
	iofunc_attr_t		attr;		// Used by iofunc layer
	FS_ATTR_T	 		*next;		// Attributes are linked together
	FS_ATTR_T			*parent;	// pointer to parent fsattr
	unsigned			child_inuse;// count of every open file underneath this directory in the hier
	struct hier_dir		*dir;		// Pointer to my dir or NULL if a file
	struct hier_dir		*pdir;		// Pointer to parent in hier
	int					(*override_io)(FS_ATTR_T *fap, unsigned flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
	uint32_t			fid;
	uint32_t			offset;		// Often an index into the directory block/cluster
	unsigned			flags;		// FSATTR_*
	int					err;
	unsigned			tick;
	unsigned			rdblk;
	off64_t				preread_end;
	off64_t				predict_off;
	uint32_t			rdir_fid;
	uint32_t			rdir_off;

	uint8_t			 	dynamic;	// dynamic file (TRUE if file size can grow with reads)
#define IOFS_NO_EOF     0           // read of dynamic file has not found EOF
#define IOFS_SOFT_EOF   1           // read of dynamic file has found temporary EOF
#define IOFS_HARD_EOF   2           // read of dynamic file has found premanent EOF
	uint8_t			 	eof;   		// EOF status for dynamic file reads
	uint8_t			 	reserved1;  // 
	uint8_t			 	reserved2;  // 

	unsigned			shrink_seq;	// the transaction sequence number during last shrink.
	struct writecache	*wcache;
	struct cachenode	*cache;
	struct cachenode	*rover;		// Hold last hit. Really speeds up sequential IO.
	struct mapnode		*mapping;
	struct fscrypto		*crypto;
	struct span			span;
	unsigned			nblks;		// Approx blks in mappings. May be <= but never > reality
	iofunc_notify_t		notify[3];
	const struct fnametype	*ftp;
	uint16_t			fname_len;
#define FSATTR_FNAME_WILD	0xffff
	char				fname[ATTR_CACHE_FNAME_LEN];
};

struct fsocb {
	iofunc_ocb_t		ocb;
	// Add future stuff if any here
};

// Definitions for fsattr flags
#define FSATTR_LOCK_NLINK				0x00010000	// Don't allow user (even root) to unlink/link the file
#define FSATTR_LOCK_SIZE				0x00020000	// Don't allow user (even root) to adjust file size
#define FSATTR_LOCK_MODE				0x00040000	// Don't allow user (even root) to change file perms
#define FSATTR_NOCALLOUT				0x00080000	// Don't call filesystem callouts
#define FSATTR_FORCE_PERM				0x00100000	// Force even root to obey the file permissions
#define FSATTR_SPECIAL					0x00200000	// Special file, use filesystem's mountpoint
#define FSATTR_KEEP_PDIR				0x00400000	// Keep fid associated with its parent directory when unlinked
#define FSATTR_ISMOUNTED				0x00800000	// This attribute has a filesystem mounted on it (e.g. blk device)
#define FSATTR_NOCACHE					0x01000000	// Underling storage can change without notification so don't cache
#define FSATTR_PERSISTENT_MASK			0x09ff00ff	// These flags should not be cleared on close
#define FSATTR_NOFLUSH					0x02000000	// used to stop cache flushing during an io_write
#define FSATTR_SHRINK_ONCLOSE			0x04000000	// file size does not match on-disk mappings
#define FSATTR_ENCRYPTED				0x08000000	// File is mount key encryped
#define FSATTR_PWAIT					0x10000000	// waiting to lock the parent
#define FSATTR_WALKED					0x20000000	// Attribute has been walked during a call to attr_walk
#define FSATTR_WALK_LOCK				0x40000000	// Attribute has been left locked during attr_walk
#define FSATTR_NOTIFY					0x80000000	// A ionotify is active for this attribute
#define FSATTR_IOFS_MASK				0xffff0000	// Reserved for use by IOFS


#define DEVICE_NAME_LEN		64
#define MOUNT_NAME_LEN		64

// There is one "device" for each physical device a driver has
struct device {
	struct device	*next;
	DRIVER_T		*driver;
	const char		*bus;
	unsigned		busdevno;
	const char		*class;
	const char		*type;
	char			*forcemnt;	// Simple devices (ipod, tmpfs) can auto-mount
	char			*fsname;	// Only needed for automnt
	unsigned		unit;
	int				index;		// Device index for mount/umount upcall
	unsigned		tickcnt;
	unsigned		blksize;	// The devices atomic block size
	unsigned		blkshift;	// Shift amount to convert from BLKSIZE to device block size
	unsigned		numblks;	// Zero if no media in device
	unsigned		flags;		// DEVICE_*
	void			(*refresh_complete)(DEVICE_T *dep, int flags, unsigned *handles[], unsigned num_handles);
} ;

// Definitions for fsattr flags
#define DEVICE_READONLY			0x00000001	// Set if the device is read-only.
#define DEVICE_ISMOUNTED		0x00000002	// Set only when mounted.
#define DEVICE_NOBLKDEV			0x00000004	// Don't try to read blocks from this device


// There is one "blkfsattr" for each device and for each partition in the device
struct blkfsattr {
	struct fsattr		fsattr;
	DEVICE_T			*dev;
	struct blkfsattr	*blkdev;	// Only set if attr is a partition
	struct volmgr		*volmgr;	// Only set if attr is a volume with partitions
	unsigned			begblk;
	char				mntname[MOUNT_NAME_LEN];
	char				devname[DEVICE_NAME_LEN];
} ;

// There os one "driver" for each kind of hardware (e.g. ide, scsi, file)
struct driver {
	struct fsiface	iface;			// Must be first
	int				device_size;
	struct dfuncs {
		int			(*mount)(DRIVER_T *drp, int flags, const char *options);
		int			(*open)(struct blkfsattr *fap, unsigned ioflag, unsigned sflag);
		int			(*close)(struct blkfsattr *fap);
		int			(*iov)(FS_ATTR_T *fap, unsigned flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
 		int			(*devctl)(resmgr_context_t *ctp, struct blkfsattr *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval);
		int			(*flush)(struct blkfsattr *fap, unsigned flag);
		int			(*abort)(struct blkfsattr *fap, unsigned blk[]);
		int			(*msg)(struct blkfsattr *fap, unsigned ioflag, io_msg_t *msg);
		unsigned	(*timer)(DEVICE_T *dep);
		void		(*addinfo)(DEVICE_T *dep, FS_MOUNT_T *fmp);
		int			(*umount)(DEVICE_T *dep, int flags);
	} funcs;
} ;

#define DEVCTL(fmp, dcmd, data, pretval) 	(FS_MOUNT_MBR(fmp, blkdev)->dev->driver->funcs.devctl(0, FS_MOUNT_MBR(fmp, blkdev),  _IO_FLAG_RD|_IO_FLAG_WR, (dcmd), (data), sizeof *(data), (pretval)))

// The top 4 bits of uint16_t ocb->flags are for each resmgrs private use.
// We use them for inmplementing posix_fadvise()
#define OCB_NOREUSE				0x0800
#define OCB_TYPE_SEQUENTIAL		0x1000
#define OCB_TYPE_RANDOM			0x2000
#define OCB_TYPE_MASK			0x3000
// These flags are for internal non-persistent use, they are not stored in ocb->flags is it is only 16 bite
#define OCB_NOZERO				0x00010000	

#define IS_NORMAL(x)			(((x) & OCB_TYPE_MASK) == 0)
#define IS_SEQUENTIAL(x)		(((x) & OCB_TYPE_MASK) == OCB_TYPE_SEQUENTIAL)
#define IS_RANDOM(x)			(((x) & OCB_TYPE_MASK) == OCB_TYPE_RANDOM)
#define IS_NOREUSE(x)			((x)  & OCB_NOREUSE)

struct cryptoiface {
	struct fsiface			iface;		// Must be first
	struct {
		int		(*init)(FS_MOUNT_T *fmp, struct fsattr *fap, uint64_t keyarea_beg, unsigned keyarea_len);
	} funcs;
} ;

// ECB is very weak (but fast) while LRW is strong (but slower)
enum {
	CIPHER_MODE_ECB, CIPHER_MODE_CBC, CIPHER_MODE_CTR, CIPHER_MODE_LRW
} ;

struct fscrypto {
	struct cipher		*cipher;
	int					type;		// Type of CIPHER
	uint64_t			keyarea_beg;// On disk from partition start
	unsigned			keyarea_len;// Area available to store key in
	struct cachenode	*cap;		// Temp block used during encryption
	void				*lks;		// Secondary key sequence used by lrw mode.
	struct {
		int			(*create)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, uint64_t keyoff, unsigned keysize);
		void		(*destroy)(FS_MOUNT_T *fmp, FS_ATTR_T *fap);
		int			(*passphrase)(FS_MOUNT_T *fmp, struct fscrypto *crp, uint8_t *userpass, int userpasslen, int action);
		int			(*crypt_iov)(struct blkfsattr *blkdev, struct fsattr *fap, unsigned flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
		void		(*blk_encrypt)(struct fscrypto *crp, const uint8_t *ibuf, uint8_t *obuf, int len, unsigned blk);
		void		(*blk_decrypt)(struct fscrypto *crp, const uint8_t *ibuf, uint8_t *obuf, int len, unsigned blk);
		int			(*lrw_setkey)(struct fscrypto *crp, uint8_t *key);
		void		(*hash)(uint8_t *pass, int passbytes, uint8_t *hash);
		void		(*random)(uint8_t *buf, int nbytes);
		void		(*salt)(uint8_t *buf, int nbytes);
	} cfuncs;
} ;

struct keynode {
	uint8_t		master_key[32];		// 256 bits
	uint8_t		lrw_key[16];		// 128 bits
	uint8_t		validation[16];		// 128 bits
} ;


#define TRANS_MAX_PAGES		507
#define TRANS_NUM_PAGES		16		// Should be a runtime variable
#define TRANS_NUM_CNTS		5

#define TRANSTYPE_ADD		0		// Type of a trans_add(). An fsys may create others.

//
// The transaction region is a reserved area which must be contiguious and large
// enough to hold TRANS_NUM_PAGES 4K pages. The last page holds control information
// defined by struct transarea. The pages always written right justified at the end.
//
//                                              fmp->trans.endblk in mount struct
//                                                              v
//      |      |      |      |      | page | page | page | page | ctrl |
//                                  <----------numtrans--------->
//
// This area is ALWAYS LITTLE ENDIAN
struct transarea {
	uint32_t	begseq;
	uint32_t	numtrans;
	struct transmap {
		uint32_t	blk;
		uint16_t	off;
		uint16_t	len;
	} pages[TRANS_MAX_PAGES + 1];		// + 1 for control page at the end
	// The following MUST be in the last 512 bytes (disk blk).
	uint32_t	counts[TRANS_NUM_CNTS];	// Filesystem specific stuff associated with meta data
	uint32_t	endseq;
};


struct xmlbuf {
	char		*buff;
	int			buffsize;
	int			len;
	int			pos;
	int			level;
};


struct subopt {
	const char		*name;			// name to display if invalid option found
	int				skip;			// skip options
	const char		*conditions;	// comma seperated list of currently true conditions
};
#define SUBOPT_TYPE_FS	1


#define DIR_HASHSIZE		256
struct fsmount {
	iofunc_mount_t		mount;			// Normal mount structure
	struct fsmount		*next;
	struct globals		*gop;
	struct blkfsattr	*blkdev;
	const char			*fsname;
	int32_t				lock_tid;
	uint16_t			lock_count;
	uint16_t			unused;
	FS_ATTR_T			*fattrlist;
	FS_ATTR_T			*fs_attr;
	unsigned			openfiles;
	unsigned			numattrs;
	unsigned			writers;
	unsigned			flags;
#define FSMOUNT_TMPFS			0x00000001	// There is no backing store
#define FSMOUNT_RAW_FSATTR		0x00000002	// Pass the raw fsattr to any IO commands instead of the block device
#define FSMOUNT_MNTINFO			0x00000004	// Filesystem wants to add and handle entries in MNTINFO_DIR
#define FSMOUNT_STRICMP			0x00000008	// Use stricmp for comparing names
#define FSMOUNT_DIRTY_DATA		0x00000010	// There is a dirty fsattr requiring a flushwrite
#define FSMOUNT_WALKING			0x00000020	// A thread is walking the mountpount
#define FSMOUNT_FSINODE_NOCACHE	0x00000040	// Don't cache the fsinode
	unsigned			mountid;
	int					fname_maxlen;
	int					symlink_maxlen;
	int					inode_size;
	struct fsys			*fsys;
	unsigned			clustersize;
	unsigned			clusterbits;
	uint64_t			bavail;
	unsigned			ticktrans;
	unsigned			tickputv;
	unsigned			tickcnt;
	unsigned			sequence;
	struct xmlbuf		info;
	struct uuid			uuid;
#define UUID_NULL		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

	struct funcs {
		void              (*attr_open)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, const FS_INODE_T *fip);
		void              (*attr_sync)(FS_MOUNT_T *fmp, const FS_ATTR_T *fap, FS_INODE_T *fip);
		int               (*attr_rename)(FS_MOUNT_T *fmp, FS_ATTR_T *sfap, FS_ATTR_T *dfap);
		void              (*attr_close)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, unsigned ocbflags);
		int               (*devctl)(FS_MOUNT_T *fmp, resmgr_context_t *ctp, FS_ATTR_T *fap, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval);
		int               (*msg)(FS_MOUNT_T *fmp, resmgr_context_t *ctp, FS_ATTR_T *fap, unsigned ioflag, io_msg_t *msg);
		int               (*notify)(FS_MOUNT_T *fmp, FS_ATTR_T *fap);
		int               (*attr_flags)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, uint32_t *pbits, uint32_t mask);
		int               (*hier_build)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, struct hier_file *hfp, unsigned index);
		int               (*node_get)(FS_MOUNT_T *fmp, FS_INODE_T *fip, unsigned flags, const char *name);
/* flags for fsmount.funcs.node_get(,,flags,)  also used in struct fsinode.flags */
#define NODE_GET_MISC			0x00000100	// Need fsinode.{rdev,size,uid,gid,nlink,[amc]time,private data}
#define NODE_GET_MODE			0x00000200	// Need fsinode.mode
#define NODE_GET_INODE			0x00000800	// Need fsinode.ino
#define NODE_GET_ATTRS			(NODE_GET_MISC|NODE_GET_MODE|NODE_GET_INODE)
#define NODE_GET_NAME			0x00002000	// Need fsinode.name
#define NODE_GET_ALL			(NODE_GET_ATTRS|NODE_GET_NAME)
#define NODE_GET_ENTSIZE		0x00001000	// Need fsinode.entsize entry length for building hier (from hier_build_node_get)
#define NODE_GET_CHK_WEIRD		0x00020000	// (set for 2nd pass at resolving ignoring namesum, only used if fsmount.op.weird_fnames is set)
#define NODE_GET_MCACHE_ONLY	0x00040000	// set to have node_get return if the fid is not in the meta cache
#define NODE_GET_CACHE_ATTRS	0x01000000	// If set iofs will try to cache the attributes (NODE_GET_ATTRS)
#define NODE_GET_CACHE_NAME		0x02000000	// If set iofs will try to cache the name (NODE_GET_NAME)
#define NODE_GET_CACHE_ALL		(NODE_GET_CACHE_ATTRS|NODE_GET_CACHE_NAME)
#define NODE_GET_ALLOC			0x10000000	// Allocate a new unlinked attribute when opening the device.
		int               (*node_set)(FS_MOUNT_T *fmp, FS_INODE_T *inp);
		int               (*node_new)(FS_MOUNT_T *fmp, struct pathnode *pnp, FS_INODE_T *inp, unsigned namesum);
		int               (*node_del)(FS_MOUNT_T *fmp, FS_ATTR_T *fap);
		int               (*node_unlnk)(FS_MOUNT_T *fmp, struct pathnode *pnp);
		int               (*node_lnk)(FS_MOUNT_T *fmp, struct pathnode *pnp);
		int               (*node_mov)(FS_MOUNT_T *fmp, struct pathnode *spnp, struct pathnode *dpnp);
		int               (*mapping_mapfile)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, unsigned fblk, struct span *sap);
		int               (*mapping_grow)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, unsigned totblks, unsigned flags);
		int               (*mapping_shrink)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, unsigned totblks, unsigned flags);
		int               (*symlink_get)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, char *sympath, unsigned len);
		int               (*symlink_set)(FS_MOUNT_T *fmp, FS_ATTR_T *fap, char *sympath, unsigned len);
		int               (*trans_commit)(FS_MOUNT_T *fmp);
		unsigned          (*timer)(FS_MOUNT_T *fmp);
		int               (*verify)(FS_MOUNT_T *fmp);
		void              (*umount)(FS_MOUNT_T *fmp, int flags);
		void              (*activity)(FS_MOUNT_T *fmp, int active);
		int               (*connect_close_ext)(FS_MOUNT_T *fmp, uint64_t connectid);
	} funcs;

	struct hier {
		struct hier_file	*file_base;
		unsigned			mapsize;
		unsigned			file_numfids;
		unsigned			file_maxfids;
		unsigned			file_freefids;
		unsigned			data_shift;

		struct hier_dir		*dir_base;
		unsigned			dir_maxdirs;
		struct hier_dir		*dir_free;
		struct hier_dir		*dir_last;
		struct hier_dir		*dir_hash[DIR_HASHSIZE];
	} hier;

	struct transaction {
		unsigned			endblk;		// points at ctrl:  | page | page | page | ctrl |
		unsigned			maxtrans;
		unsigned			restrans;
		unsigned			numtrans;
		unsigned			sequence;
		struct transarea	*tap;
		struct cachenode	*cavec[TRANS_NUM_PAGES+1];
		struct iovec		iovec[TRANS_NUM_PAGES+1];
		struct fsattr		*fap[TRANS_NUM_PAGES+1];
		unsigned			types[TRANS_NUM_PAGES+1];
		unsigned			counts[TRANS_NUM_CNTS];
	} trans;

	struct metacache {
		uint8_t				*meta_base;
		unsigned			meta_size;
		unsigned			meta_putidx;
		unsigned			meta_hashsize;
		struct metanode		**meta_hash;
	} mcache;

	struct fs_stats_v1	stats;

	struct options {
		char		*mountpoint;
		int			numtrans;
		int			sync;
		unsigned	ticks;		// Holds tick nano-seconds >> 16. (this allows up to 15 mins)
		int			verbose;
		int			verify;
		int			weird_fnames;
		int			test;
		unsigned	exitcnt;	// Driver exit when exitcnt!=0 && --exitcnt==0
		unsigned	meta_size;
		int         mnt_fail_exit;
	} op;
} ;

struct drvrinit {
	struct drvrinit	*next;
	char			*drvr;
	char			*options;
	unsigned		code;
	char			buf[1];		// Variable length
};

struct mntrule {
	struct mntrule	*next;
	char			*fsname;
	char			*rule;
	char			*options;
	char			pat[1];		// Variable length (fsname,rule, options point into here).
} ;


struct fnametype {
	struct fnametype	*next;
	uint16_t			flags1;
	uint16_t			flags2;
	struct growsize		growsizes[3];
	unsigned			prereadsize;
};

struct fnamerule {
	struct fnamerule	*next;
	struct fnametype	*type;
	int					len;
	char				pat[1];		// Variable length
};
#define FNAMERULE(s, t)	{ sizeof(s)-1, s, t }

struct ldmodule {
	struct ldmodule			*next;
	const struct fsmodule	*fsmodule;
	void					*dll;
	const struct check		*check;
};

#define MAX_OPTIONS		31	// Maximum number of "-o" options
#define MAX_DIO			64
struct globals {
	struct fsmount			*mountlist;		// Must be the first member!!!
	int32_t					lock_tid;
	uint16_t				lock_count;
	uint16_t				reserved;
	int						os_major;
	int						os_minor;
	sleepon_t				*sleepon;
	dispatch_t				*dispatch;
	struct fsmount			*blkfs;
	struct device			*devices;
	struct fsiface			*ifaces;
	const struct fsmodule	* const *builtin_modules;
	struct ldmodule			*loaded_modules;
	uint16_t				numdrvrs;
	uint16_t				autodrvrs;
	struct drvrinit			*drvrinits;
	struct mntrule			*mntrules;
	struct fnametype		*fnametypes;
	struct fnamerule		*fnamerules;
	struct diobuf			*dio[MAX_DIO];
	struct cache_ctrl		cinfo;
	struct fsobjs {
		struct object			cachedmap;
		struct object			writecache;
		struct object			fsocb;
		struct object			fsattr[FS_MAX_TYPES];
		struct object			fsmount[FS_MAX_TYPES];
	}						objs;
	int						coid;
	int						upcode;
	int						flushing;
	int						ticker_active;
	int						timer_id;
	unsigned				sequence;
	unsigned				msgnum;
	void					*shortlived_addr;
	struct lrunode {
		int						num;
		struct cachenode		*list;
	} cachelru[NUM_ATYPES];
	struct mapnode			*mapping;
	unsigned				tick;
	resmgr_attr_t			res_attr;
	resmgr_connect_funcs_t	connect_funcs;
	resmgr_io_funcs_t		io_funcs;
	iofunc_funcs_t			mount_funcs;
	char					*cmdname;
	struct goptions {
		int						verbose;
		int						nobackground;
		int						notimers;
		unsigned				cache_numfreeattrs;
		unsigned				cache_nummaps;
		unsigned				cache_numnodes[NUM_ATYPES];
		int						integrity;
		unsigned				maxfids;
		int						metasync;			// 0 for async, O_SYNC to sync on chmod/chown/utime/unlink...
		char					*drvr_file;
		char					*mnt_file;
		char					*fname_file;
		unsigned				meta_size;
	}						op;
	char					*options[MAX_OPTIONS + 1];
} ;

// Make sure that there is no lock inversions. if fap is locked, fmp and gop must be unlocked.
// if fmp is locked, gop must be unlocked.
#if defined(IOFS_CHECKLOCK)
#define check_locks(_gop, _fmp, _fap) if( \
	( \
		(_fap) && \
			( \
				( \
					((struct fsmount *)(_fmp))->lock_count != 0 && ((struct fsattr *)(_fap))->attr.lock_tid == ((struct fsmount *)(_fmp))->lock_tid \
				) \
			|| \
				( \
					(_gop)->lock_count != 0 && ((struct fsattr *)(_fap))->attr.lock_tid == (_gop)->lock_tid \
				) \
			) \
	) \
	|| \
	( \
		((_fmp) && !(_fap)) && \
			( \
				(_gop)->lock_count != 0 && ((struct fsmount *)(_fmp))->lock_tid == (_gop)->lock_tid \
			) \
	) \
) abort();
#else
#define check_locks(fop, fmp, fap)
#endif

#define ATTR_ISLOCKED(fap)		((fap)->attr.lock_count != 0 && (fap)->attr.lock_tid == pthread_self())
#if defined(IOFS_MULTITHREAD)
#if defined(IOFUNC_MOUNT_LOCK_FUNCS)
#define ATTR_LOCK(fmp, fap)		(fmp)->mount.funcs->attr_lock(&(fap)->attr); check_locks((fmp)->gop, (fmp), (fap))
#define ATTR_TRYOCK(fmp, fap)	(fmp)->mount.funcs->attr_trylock(&(fap)->attr)
#define ATTR_UNLOCK(fmp, fap)	(fmp)->mount.funcs->attr_unlock(&(fap)->attr)
#else
#define ATTR_LOCK(fmp, fap)		iofunc_attr_lock(&(fap)->attr); check_locks((fmp)->gop, (fmp), (fap))
#define ATTR_TRYLOCK(fmp, fap)	iofunc_attr_trylock(&(fap)->attr)
#define ATTR_UNLOCK(fmp, fap)	iofunc_attr_unlock(&(fap)->attr)
#endif
#define MOUNT_LOCK(fmp)			fslock((fmp)->gop, &(fmp)->lock_tid, &(fmp)->lock_count); check_locks((fmp)->gop, (fmp), 0)
#define MOUNT_UNLOCK(fmp)		fsunlock((fmp)->gop, &(fmp)->lock_tid, &(fmp)->lock_count)
#define GLOBAL_LOCK(gop)		fslock((gop), &(gop)->lock_tid, &(gop)->lock_count); check_locks((gop), 0, 0)
#define GLOBAL_UNLOCK(gop)		fsunlock((gop), &(gop)->lock_tid, &(gop)->lock_count)
#else
#define ATTR_LOCK(fmp, fap)		(fap)->attr.lock_tid = pthread_self(), (fap)->attr.lock_count++; check_locks((fmp)->gop, (fmp), (fap))
#define ATTR_TRYLOCK(fmp, fap)	(((fap)->attr.lock_tid = pthread_self()) + ((fap)->attr.lock_count++) > 0 ? EOK : EOK)
#define ATTR_UNLOCK(fmp, fap)	(fap)->attr.lock_count--
#define MOUNT_LOCK(fmp)			(fmp)->lock_tid = pthread_self(), (fmp)->lock_count++; check_locks((fmp)->gop, (fmp), 0)
#define MOUNT_UNLOCK(fmp)		(fmp)->lock_count--
#define GLOBAL_LOCK(gop)		(gop)->lock_tid = pthread_self(), (gop)->lock_count++; check_locks((gop), 0, 0)
#define GLOBAL_UNLOCK(gop)		(gop)->lock_count--
#endif


/* attr.c */
int				attr_init(struct fsmount *fmp);
unsigned attr_reset(struct fsmount *fmp, unsigned *hier_handles[], unsigned max_handles);
#define ATTR_ATTACH_ALLOC			0x00000001
#define ATTR_ATTACH_FSINODE_VALID	0x00000002
struct fsattr	*attr_attach(struct fsmount *fmp, struct fsinode *fip, const char *fname, unsigned flags, struct hier_dir *hdp);
FS_ATTR_T		*attr_open(FS_MOUNT_T *fmp, struct hier_dir *hdp, unsigned fid);
void			attr_close(FS_MOUNT_T *fmp, FS_ATTR_T *fap, int syncflag, unsigned ocbflags);
ssize_t			attr_read(FS_MOUNT_T *fmp, FS_ATTR_T *fap, off64_t off, size_t size, void *buf);
void			attr_detach(struct fsmount *fmp, struct fsattr *fap, int syncflag, unsigned ocbflags);
void 			attr_trim(struct fsmount *fmp);
int				attr_sync(struct fsmount *fmp, struct fsattr *fap, int type);
int				attr_flushwrite(struct fsmount *fmp, struct fsattr *fap);
int				attr_flushwrites(struct fsmount *fmp);
int				attr_flushallwrites(struct globals *gop);
int				attr_zero(struct fsmount *fmp, struct fsattr *fap, off64_t start, off64_t end, int cflags);
int				attr_growdat(struct fsmount *fmp, struct fsattr *fap, off64_t fsize, int cflags);
int				attr_growmap(struct fsmount *fmp, struct fsattr *fap, off64_t fsize);
int				attr_walk(struct fsmount *fmp, int (*func)(FS_ATTR_T *fap, void *data), void *data);
void			attr_unlock_walked(struct fsmount *fmp);
struct fsmount	*attr_lock_mounted(struct fsattr *fap, unsigned ioflag, unsigned blk, unsigned nblks);
void			attr_syncall(struct fsmount *fmp);
int				attr_flags(struct fsmount *fmp, struct fsattr *fap, uint32_t *pbits, uint32_t mask, uint32_t current, uint32_t changable);

/* bitmap.c */
int		bitmap_alloc1(uint8_t  *bmp, unsigned bmsize, struct bitrange *brp);
int		bitmap_alloc16c(uint8_t *bmp, unsigned bmsize, unsigned begbit, unsigned numbits, struct bitrange *brp);
int		bitmap_alloc64c(uint8_t *bmp, unsigned bmsize, unsigned begbit, unsigned numbits, struct bitrange *brp);
int		bitmap_alloc256c(uint8_t *bmp, unsigned bmsize, unsigned begbit, unsigned numbits, struct bitrange *brp);
int		bitmap_allocnc(uint8_t *bmp, unsigned bmsize, unsigned bitbeg, unsigned numbits, struct bitrange *brp);
int		bitmap_allocn(uint8_t  *bmp, unsigned bmsize, unsigned numbits, struct bitrange *brp);
int		bitmap_setn(uint8_t  *bmp, unsigned bmsize, unsigned bitbeg, unsigned numbits, int setting);
void	bitmap_set1(uint8_t  *bmp, unsigned bitnum, int setting);
int		bitmap_countbits(uint8_t *bmp, unsigned bmsize);

/* cache.c */
int		cache_growlru(unsigned num_nodes, unsigned blks2node, struct lrunode *lru, int mapphys);
int		cache_getv(struct fsmount *fmp, struct fsattr *fap, off64_t off64, unsigned size, int flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
int		cache_putv(struct fsmount *fmp, struct fsattr *fap, int flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
void	cache_delcache(struct fsmount *fmp, struct fsattr *fap, unsigned totblks);
void	cache_relv(struct fsmount *fmp, struct cachenode *cavec[], int nvec, unsigned flags);
void	cache_purge(struct fsmount *fmp, struct fsattr *fap, off64_t nbytes);
int		cache_getdmaps(struct fsmount *fmp, struct fsattr *fap, struct cachenode *cap);
int		cache_adjdmaps(struct fsmount *fmp, struct fsattr *fap);
void	cache_reldmaps(struct fsmount *fmp, struct cachenode *cap);
struct cachenode *cache_getlru(struct fsmount *fmp, struct fsattr *fap, struct cachenode *prev, int atype);

/* check.c */
int		check_inlru(struct fsmount *fmp, struct cachenode *tcap);
int		check_infap(struct globals *gop, struct cachenode *cap);
void	check_cache(struct fsmount *fmp, struct fsattr *fap, int nolinks);
void	check_cacheall(struct fsmount *fmp);
void	check_fattrs(struct fsmount *fmp);

/* default.c */
void	default_attr_open(struct fsmount *fmp, struct fsattr *fap, const struct fsinode *fip);
void	default_attr_sync(struct fsmount *fmp, const struct fsattr *fap, struct fsinode *fip);
int		default_attr_rename(struct fsmount *fmp, struct fsattr *sfap, struct fsattr *dfap);
void	default_attr_close(struct fsmount *fmp, struct fsattr *fap, unsigned ocbflags);
int		default_attr_flags(struct fsmount *fmp, struct fsattr *fap, uint32_t *pbits, uint32_t mask);
int		default_node_get(struct fsmount *fmp, struct fsinode *fip, unsigned flags, const char *name);
int		default_node_new(struct fsmount *fmp, struct pathnode *pnp, struct fsinode *fip, unsigned namesum);
int		default_node_del(struct fsmount *fmp, struct fsattr *fap);
int		default_node_lnk(struct fsmount *fmp, struct pathnode *pnp);
int		default_node_unlnk(struct fsmount *fmp, struct pathnode *pnp);
int		default_node_mov(struct fsmount *fmp, struct pathnode *spnp, struct pathnode *dpnp);
int		default_symlink_get(struct fsmount *fmp, struct fsattr *fap, char *sympath, unsigned len);
int		default_symlink_set(struct fsmount *fmp, struct fsattr *fap, char *sympath, unsigned len);
int		default_mapping_mapfile(struct fsmount *fmp, struct fsattr *fap, unsigned fblk, struct span *sap);
int		default_mapping_grow(struct fsmount *fmp, struct fsattr *fap, unsigned totblks, unsigned flags);
int		default_mapping_shrink(struct fsmount *fmp, struct fsattr *fap, unsigned totblks, unsigned flags);
int		default_trans_commit(struct fsmount *fmp);
void	default_activity(struct fsmount *fmp, int active);
int     default_msg(struct fsmount *fmp, resmgr_context_t *ctp, FS_ATTR_T *fap, unsigned ioflag, io_msg_t *msg);

/* device.c */
int		upcall(message_context_t *ctp, int code, unsigned flags, void *handle);
int		device_string(struct device *dep, char *buff, int buffsize);
DEVICE_T *device_alloc(struct driver *drp, const char *options);
void	device_free(DEVICE_T *dep);
void	device_init(DEVICE_T *dep);
void	device_destroy(DEVICE_T *dep);
void	device_nomedia(DEVICE_T *dep);
void	device_verify(DEVICE_T *dep);
void    device_refresh(DEVICE_T *dep, int flags, void *id,   // flags and id for future use (use 0 for default)
		void (*completion_callback)(DEVICE_T *dep, int flags, unsigned *hier_handles[], unsigned num_handles));

/* dio.c */
int dio_open(struct fsmount *fmp, resmgr_context_t *ctp, struct fsattr *fap, unsigned ioflag, struct dio_alloc *dap, int *phandle);
void dio_close(struct fsmount *fmp, struct fsattr *fap, int handle);
int dio_io(resmgr_context_t *ctp, struct dio_io *dip, struct fsocb *ocb, int *nbytes);

/* fsmain.c */
void	terminate_handler(int signo);
int		fsmain(int argc, char *argv[], void (*config_get)(struct globals *gop));

/* hier.c */
struct hier_dir *hier_getdir(struct fsmount *fmp, unsigned fid, int create);
void		hier_reldir(struct fsmount *fmp, unsigned fid);
unsigned	hier_alloc(struct fsmount *fmp, unsigned namesum, unsigned offset);
void		hier_free_children(struct fsmount *fmp, struct hier_dir *hdp);
void		hier_free(struct fsmount *fmp, unsigned fid);
int			hier_children(struct fsmount *fmp, struct hier_dir *hdp);
void		hier_link(struct fsmount *fmp, struct hier_dir *hdp, unsigned fid);
void		hier_unlink(struct fsmount *fmp, struct hier_dir *hdp, unsigned fid);
int			hier_build(struct fsmount *fmp, struct fsattr *fap, struct hier_file *hfp, unsigned index);
int			hier_build_node_get(struct fsmount *fmp, struct fsattr *fap, struct hier_file *hfp, unsigned index);
int			hier_nfiles(struct fsmount *fmp, struct fsattr *fap, int load);

/* lock.c */
#if defined(IOFS_MULTITHREAD)
int		fslock(struct globals *gop, int32_t *ptid, uint16_t *pcount);
int		fsunlock(struct globals *gop, int32_t *ptid, uint16_t *pcount);
int		fstrylock(struct globals *gop, int32_t *ptid, uint16_t *pcount);
#endif
#if defined(IOFUNC_MOUNT_LOCK_FUNCS)
int		fs_attr_lock(struct fsattr *fap);
int		fs_attr_unlock(struct fsattr *fap);
int		fs_attr_trylock(struct fsattr *fap);
#endif
int		fs_attr_lock_below(struct fsattr *fap);
int		fs_attr_lock_parent(struct fsattr *fap);

/* mapping.c */
int	mapping_init(struct globals *gop);
int mapping_getcache(struct fsmount *fmp, struct fsattr *fap, unsigned beg, struct extent *exp);
void mapping_addcache(struct fsmount *fmp, struct fsattr *fap, struct extent *exp);
void mapping_delcache(struct fsmount *fmp, struct fsattr *fap, unsigned beg);

/* misc.c */
struct fsocb *fs_ocb_calloc(resmgr_context_t *ctp, struct fsattr *fap);
void fs_ocb_free(struct fsocb *ocb);
void	fs_log(const char *name, int severity, const char *fmt, ...) __attribute__((format (printf, 3, 4)));
int		global_sync(message_context_t *ctp, int code, unsigned flags, void *handle);
int		copyuri(char *d, int size, const char *s, const char *esc);
unsigned strtosize(const char *str, char **ptr, unsigned minsize, unsigned maxsize);
struct fsiface *iface_find(struct globals *gop, const char *type, const char *name);
DRIVER_T *driver_find(struct globals *gop, const char *drvr);
struct fsys *fsys_find(struct globals *gop, const char *fsys);
struct volmgr *volmgr_find(struct globals *gop, const char *volmgr);
struct crypt *crypt_find(struct globals *gop, const char *crypt);
int crypto_create(struct fsmount *fmp, struct fsattr *fap, char *cipher, uint64_t keyoff, unsigned keysize);
int suboptif(struct subopt *sop, char **poptstr);
int suboptfs(struct fsmount *fmp, struct subopt *sop, char **poptstr);
void subopthelp(struct subopt *sup, const char * const opts[], const char * const examples[], int type);
void notify(struct fsattr *fap);
int blks2atype(int blks);
int atype2blks(int atype);
int struuid(char *buff, int buffsize, const struct uuid *uuid);
void random_get(uint8_t *buf, int nbytes);
void *shobj_addr_init(void);
int lockdown(struct globals *gop, void *vaddr, unsigned size, int usemmap);

/* rule.c */
enum { RULE_DRVR=0, RULE_MNT, RULE_FNAME } ;
void rule_add_file(struct globals *gop, int type, char *file);
int rule_add_fname(struct globals *gop, char *buf);
int rule_add_mnt(struct globals *gop, char *buf);
int rule_add_drvr(struct globals *gop, char *buf);
void rule_add_defaults(struct globals *gop);

/* modules.o */
extern const struct fsmodule	* const iofs_modules[];

/* mount.c */
int		mount_create(struct globals *gop, struct blkfsattr *fap, struct fsys *fsp, char *mount_rule, const char *options);
int		mount_destroy(struct fsmount *fmp, int flags);
void 	mount_reset(struct fsmount *fmp);
int mount_info_io(struct fsattr *fap, unsigned flags, struct cachenode *cavec[], struct iovec iovec[], int nvec);
struct blkfsattr *mount_find(struct device *dep, unsigned begblk);
FS_ATTR_T *mount_device(struct device *dep, struct blkfsattr *blkfap, const char *ext, unsigned begblk, unsigned numblks);
void umount_device(struct device *dep);
void mount_verify(struct device *dep);
void refresh_device(struct device *dep);

/* mcache.c */
void mcache_init(struct fsmount *fmp);
void mcache_reset(struct fsmount *fmp);
int mcache_get(struct fsmount *fmp, unsigned fid, unsigned type, void **data, int *datalen);
int mcache_set(struct fsmount *fmp, unsigned fid, unsigned type, const void *data, int datalen);
int mcache_fsinode_get(struct fsmount *fmp, unsigned fid, FS_INODE_T *fip);
int mcache_fsinode_set(struct fsmount *fmp, unsigned fid, FS_INODE_T *fip);
int mcache_fsinode_update(struct fsmount *fmp, unsigned fid, FS_INODE_T *fip);

/* node.c */
int node_attr(struct fsmount *fmp, const struct fsinode *fip, iofunc_attr_t *attr);
int node_get(struct fsmount *fmp, struct fsinode *fip, unsigned flags, const char *name);

/* object.c */
void			*fsobject_alloc(struct fsys *fsp, enum objects type);
void			fsobject_free(struct fsys *fsp, enum objects type, void *ptr);

/* path.c */
#define PATH_OPEN_IFLNK			0x00000001		// Always target the symlink if it is the final path component
#define PATH_OPEN_MKDIR			0x00000002		// Called as a mkdir
int		path_open_connect(struct fsmount *fmp, resmgr_context_t *ctp, struct _io_connect *cmsg, struct pathnode *pnp, struct _client_info *cip, unsigned flags);
int		path_open_path(struct fsmount *fmp, resmgr_context_t *ctp, char *path, struct pathnode *pnp, struct _client_info *cip);
int		path_unlock(int status, struct pathnode *pnp);
int		path_link(struct fsmount *fmp, struct pathnode *pnp, struct _client_info *info);
int		path_mknod(struct fsmount *fmp, struct pathnode *pnp, iofunc_attr_t *newattr, struct _client_info *info);
int		path_rmnod(struct fsmount *fmp, struct pathnode *pnp);
int		path_sum(const char *path);
void	path_fnamerules(struct fsmount *fmp, char *fname, struct fsattr *fap, struct fsocb *ocb);
int		path_mntinfo_devlnk(struct fsmount *fmp, struct fsattr *fap, char *sympath, unsigned len);

/* print.c */
void	print_mounted(const char *file, const DEVICE_T *dep);
void	print_hierarchy(struct fsmount *fmp, struct hier_dir *hdp, int getinode, int level);
void	print_hierarchy_all(struct fsmount *fmp);
void	print_inode(unsigned fid, struct fsinode *inp);
void	print_cache(struct globals *gop);
void	print_stats(struct fsmount *fmp);
void	print_debug(int val, int gdb);
void	print_msg(void *vmsg, unsigned len);
void	print_context(dispatch_context_t *ctp);
void	print_namecache(struct fsmount *fmp, int byhash, int print);
void	print_tables(struct globals *gop, int level);
void	print_trans(struct fsmount *fmp);
void	gdb(struct globals *gop);

/* timer.c */
unsigned systime_ms(void);
uint64_t systime_ns(void);
void	timer_init(struct globals *gop);
void	timer_setflush(struct fsmount *fmp, struct fsattr *fap);
void	timer_setdev(struct device *dep, unsigned msec);

/* trans.c */
int trans_recover(struct fsmount *fmp);
unsigned trans_beg(struct fsmount *fmp, int needed);
unsigned trans_end(struct fsmount *fmp, int needed);
unsigned trans_seq(struct fsmount *fmp);
int trans_commit(struct fsmount *fmp);
int trans_commit2(struct fsmount *fmp);
void trans_add(struct fsmount *fmp, unsigned fid, struct cachenode *cap, struct iovec *ivp, struct fsattr *fap);
void trans_resadd(struct fsmount *fmp, unsigned fid, struct cachenode *cap, struct iovec *ivp, struct fsattr *fap);
void trans_rem(struct fsmount *fmp, unsigned fid, struct cachenode *cap, struct fsattr *fap, unsigned type);

/* xmlbuf.c */
int xmlbuf_add(struct xmlbuf *x, const char *key, const char *data);
int xmlbuf_pos(struct xmlbuf *x, const char *key);
int xmlbuf_del(struct xmlbuf *x, const char *key);
int xmlbuf_addf(struct xmlbuf *x, const char *key, const char *fmt, ...) __attribute__((format (printf, 3, 4)));
void xmlbuf_free(struct xmlbuf *x);

/* co_*.c */
int		co_link(resmgr_context_t *ctp, io_link_t *msg, struct fsattr *mountattr, io_link_extra_t *extra);
int		co_mknod(resmgr_context_t *ctp, io_mknod_t *msg, struct fsattr *mountattr, void *extra);
int		co_open(resmgr_context_t *ctp, io_open_t *msg, struct fsattr *mountattr, void *extra);
int		co_readlink(resmgr_context_t *ctp, io_readlink_t *msg, struct fsattr *mountattr, void *reserved);
int		co_rename(resmgr_context_t *ctp, io_rename_t *msg, struct fsattr *mountattr, io_rename_extra_t *extra);
int		co_unlink(resmgr_context_t *ctp, io_unlink_t *msg, struct fsattr *mountattr, void *reserved);
int		co_mount(resmgr_context_t *ctp, io_mount_t *msg, struct fsattr *mountattr, io_mount_extra_t *extra);

/* io_*.c */
int		io_close_ocb(resmgr_context_t *ctp, void *reserved, struct fsocb *ocb);
int		io_close_dup(resmgr_context_t *ctp, io_close_t *msg, struct fsocb *ocb);
int		io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, struct fsocb *ocb);
int		io_devctl_common(resmgr_context_t *ctp, struct fsattr *fap, struct fsocb *ocb, unsigned ioflag, int dcmd, void *data, int nbytes, int *retval);
int		io_fdinfo(resmgr_context_t *ctp, io_fdinfo_t *msg, struct fsocb *ocb);
int		io_notify(resmgr_context_t *ctp, io_notify_t *msg, struct fsocb *ocb);
int		io_pathconf(resmgr_context_t *ctp, io_pathconf_t*msg, struct fsocb *ocb);
int		io_read(resmgr_context_t *ctp, io_read_t *msg, struct fsocb *ocb);
int		io_space(resmgr_context_t *ctp, io_space_t *msg, struct fsocb *ocb);
int		io_sync(resmgr_context_t *ctp, io_sync_t *msg, struct fsocb *ocb);
int		io_chmod(resmgr_context_t *ctp, io_chmod_t *msg, struct fsocb *ocb);
int		io_chown(resmgr_context_t *ctp, io_chown_t *msg, struct fsocb *ocb);
int		io_utime(resmgr_context_t *ctp, io_utime_t *msg, struct fsocb *ocb);
int		io_write(resmgr_context_t *ctp, io_write_t *msg, struct fsocb *ocb);

#include <_packpop.h>

#endif

/* __SRCVERSION("iofs.h $Rev: 680334 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/services/io-fs/iofs.h $ $Rev: 680334 $")
#endif
