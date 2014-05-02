/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _GF_GF_INTERNALS_H_INCLUDED
#define _GF_GF_INTERNALS_H_INCLUDED

#include <gfpr/gfpr.h>

#ifndef _GF_GF_H_INCLUDED
#include <gf/gf.h>
#endif

#ifndef _GRAPHICS_DISPLAY_H_INCLUDED
#include <graphics/display.h>
#endif

#ifndef _GRAPHICS_DISPUTIL_H_INCLUDED
#include <graphics/disputil.h>
#endif

#ifndef _GRAPHICS_IOMSG_H_INCLUDED
#include <graphics/iomsg.h>
#endif

#ifndef _GRAPHICS_3D_H_INCLUDED
#include <graphics/3d.h>
#endif

/* macro which implements some common work that typically needs to be done
 * prior to each rendering call; verify that the hardware is locked by the
 * context, and also ensure that any pending updates to the context are
 * flushed out */

#define GF_CONTEXT_UPDATE(_cx)										\
	if ((_cx)->update_flags != GF_CONTEXT_DRAWING) {						\
		if ((_cx)->update_flags & GF_CONTEXT_DRAWING) {					\
			gf_context_update(_cx);									\
		} else {													\
			gf_context_set_error((_cx), GF_ERR_NOLOCK);	\
			return GF_ERR_NOLOCK;									\
		}															\
	}

#ifdef NDEBUG
#define GF_ASSERT(x)
#define GF_CONTEXT_SET_ERROR(ctx, err)	gf_context_set_error((context), (err))
#define _GF_DEV_SET_ERROR(gdev, err)	_gf_dev_set_error((gdev), (err))
#else
#define GF_ASSERT(x)	if (!(x)) { \
				fprintf(stderr, \
				    "%s, line %d: ASSERT failed: %s\n", \
				    __FILE__, __LINE__, #x); \
				*(int *)0 = 1; \
			}
#define GF_CONTEXT_SET_ERROR(ctx, err) { \
	gf_context_set_error((ctx), (err)); \
	fprintf(stderr, "Logging error 0x%08x in %s at line %d\n", \
	    (err), __FILE__, __LINE__); \
}
#define _GF_DEV_SET_ERROR(gdev, err) { \
	_gf_dev_set_error((gdev), (err)); \
	fprintf(stderr, "Logging error 0x%08x in %s at line %d\n", \
	    (err), __FILE__, __LINE__); \
}
#endif

#if defined __BIGENDIAN__
#define GF_FORMAT_SET_BYTEORDER(format, flags) \
{	if(((format != GF_FORMAT_ARGB8888) && (format != GF_FORMAT_BGRA8888)) && ((format & GF_FORMAT_PACK) == GF_FORMAT_PACK)) \
	{	format &= ~GF_FORMAT_PACK; \
		format |= (flags & DISP_SURFACE_BYTES_REVERSED) ? GF_FORMAT_PKLE : GF_FORMAT_PKBE; \
	} \
}
#else
#define GF_FORMAT_SET_BYTEORDER(format, flags) \
{	if(((format != GF_FORMAT_ARGB8888) && (format != GF_FORMAT_BGRA8888)) && ((format & GF_FORMAT_PACK) == GF_FORMAT_PACK)) \
	{	format &= ~GF_FORMAT_PACK; \
		format |= (flags & DISP_SURFACE_BYTES_REVERSED) ? GF_FORMAT_PKBE : GF_FORMAT_PKLE; \
	} \
}
#endif

#if defined __BIGENDIAN__
#define GF_FORMAT_IS_BYTESWAPPED(format) ((format == GF_FORMAT_ARGB8888) || (format & GF_FORMAT_PKBE)) ? 1 : 0
#else
#define GF_FORMAT_IS_BYTESWAPPED(format) ((format == GF_FORMAT_ARGB8888) || (format & GF_FORMAT_PKBE)) ? 1 : 0
#endif

__BEGIN_DECLS

/* linked list of core 2-d draw functions for various pixel formats encountered */

struct _gf_dev_corefuncs {
	 disp_draw_corefuncs_t		corefuncs, corefuncs_sw;
	 _uint32					pixel_format;
	 struct _gf_dev_corefuncs	*next;
};

struct _gf_dev {
	gf_dev_info_t				info;
	disp_adapter_t 				adapter;
	get_corefuncs_t				get_corefuncs;
	struct _gf_dev_corefuncs 	*cfuncs_cache;
	disp_draw_contextfuncs_t 	ctxfuncs, ctxfuncs_sw;
#ifdef _WIN32
	void (*sysram_workspace_realloc)(disp_draw_context_t *ctx, int newsize);
	void (*sysram_workspace_free)(char *ptr);
#endif
	disp_draw_miscfuncs_t 		miscf;
	disp_draw_3dfuncs_t 		rendf;
	gf_surface_t	 			surfaces;
	gf_display_t 				displays;
	gf_vcap_t					vcaps;
	void						*dlhandle;
	void						*handle_3d;
	char						*rendopts;
	char						*hook;
	void 						*soft3d_dlhandle;
	void						**hook_handle;
	_int32						n_hooks;
	_int32						fd;
	disp_shmem_t				*shmem;
	_uint32						shmemsize;
	_int32						n_apertures;
	disp_aperture_t				*aper;
	pid_t						pid;
	gfpr_mutex_t				mutex;
	gfpr_thread_key_t			pkey;
#ifndef NDEBUG
	gf_context_t				lock_ctx;
	gfpr_thread_t				lock_tid;
#endif
	_int32						need_io_privity;
	_int32						memory_zone;
	unsigned					dev_flags;
};

struct _gf_display {
	gf_dev_t			gdev;
	gf_display_info_t	info;
	_int32				index;
	gf_layer_t			layers;
	struct _gf_display	*next;
};

struct _gf_layer {
	gf_display_t		display;
	_int32				index;
	_int32				new_surfaces;
	disp_layer_state_t	state;
	_uint32				attach_flags;
	struct _gf_layer	*next;
};

struct _gf_vcap {
	gf_dev_t			gdev;
	_int32				index;
	disp_vcap_state_t	state;
	_uint32				attach_flags;
	struct _gf_vcap		*next;
};

#define GF_TRIED_VADDR_MMAP	0x0001

struct _gf_surface {
	disp_surface_t				surface;
	gf_format_t					format;
	gf_dev_t					gdev;
	disp_draw_corefuncs_t		*corefuncs, *corefuncs_sw;
	disp_draw_contextfuncs_t	*ctxfuncs;
	_uint32						sid;
	void						*shm_vidptr;
	void						*orig_vidptr;
	size_t						shm_size;
	gf_format_t					pal_cache_fmt;
	disp_color_t				*pal_cache;
	struct _gf_surface			*next,	*prev;
	_uint32						servergen;
	_uint32						vaddr_flags;
	_uint32						vaddr_size;
	void						*vaddr;
};
 
struct _gf_3d_target {
	struct _gf_layer	*layer;
	void				(*swap_layer)(struct _gf_layer *layer,
				    		disp_surface_t *surf, int no_wait_vsync);
	_int32				width, height;
	struct _gf_surface	**surfaces;
	_int32				nsurfaces;
	_int32				internal_alloced[2];
};

/*
 * Surface structure for 3D rendering.  An EGLSurface is really a pointer
 * to a structure of this type.
 *
 * When double-buffering, we toggle between cbuf and bkbuf.  When using
 * blits to post the color buffer, we always render to bkbuf, and post
 * the color buffer by blitting from bkbuf to cbuf.
 */
struct _gf_rendersurf {
	disp_surface_t		*bufs[2];

	disp_surface_t		*cbuf;		/* Color buffer */
	disp_surface_t		*bkbuf;		/* Back buffer */

	disp_surface_t		*cur_surf;	/* Current render target */
};

struct _gf_context {
	disp_draw_context_t	ctx;
	_uint8				pattern[8];
	_uint32				flags, update_flags;
	_int32				penwidth;
	gf_color_t			fgcolor;
	gf_color_t			bgcolor;
	_int32				clip_x1, clip_y1, clip_x2, clip_y2;
	gf_surface_t		surface;
	_int32				flush_x1, flush_y1, flush_x2, flush_y2;
#ifdef _WIN32
	void (*sysram_workspace_realloc)(disp_draw_context_t *ctx, int newsize);
	void (*sysram_workspace_free)(char *ptr);
#endif
	struct _gf_context	*next;
};

/* context update_flags bit manifests */
#define GF_CONTEXT_UPDATE_FGCOLOR		0x00000001	/* foreground color */
#define GF_CONTEXT_UPDATE_BGCOLOR		0x00000002	/* background color */
#define GF_CONTEXT_UPDATE_CLIPPING		0x00000004	/* clipping rectange */
#define GF_CONTEXT_UPDATE_ROP			0x00000008	/* raster operation */
#define GF_CONTEXT_UPDATE_PATTERN		0x00000010	/* ROP pattern */
#define GF_CONTEXT_UPDATE_CHROMA		0x00000020	/* chroma operation */
#define GF_CONTEXT_UPDATE_ALPHA			0x00000040	/* alpha operation */
#define GF_CONTEXT_UPDATE_LINE			0x00000080	/* thick line properties (join, dash, antialias) */
#define GF_CONTEXT_UPDATE_TRANSFORM		0x00000100	/* transform or x,y translation */
#define GF_CONTEXT_UPDATE_SURFACE		0x00000200	/* target surface */
#define GF_CONTEXT_UPDATE_POLYFILL		0x00000400	/* polyfill algorithm */
#define GF_CONTEXT_UPDATE_PLANEMASK		0x00000800	/* plane mask */
#define GF_CONTEXT_UPDATE_GENERAL		0x00001000	/* context has changed */
#define GF_CONTEXT_UPDATE_MASK			0x00001fff
#define GF_CONTEXT_DRAWING				0x80000000	/* h/w locked via this context */

/* context flags bit manifests */
#define GF_CONTEXT_BGCOLOR_NATIVE		0x00000001	/* do not convert bgcolor */
#define GF_CONTEXT_FGCOLOR_NATIVE		0x00000002	/* do not convert fgcolor */
#define GF_CONTEXT_AA_POLYFILL			0x00000004	/* Apply antialiasing to filled polygons */
#define GF_CONTEXT_HW_POLY				0x00000008	/* Do not generate/draw polygons in software */

#define GF_NO_LAYER_FORMAT				0x00000001
#define GF_NO_SURFACE_FORMAT			0x00000002

/* Global objects */
extern gf_context_t	_gf_context_list;
extern gfpr_mutex_t	_gf_global_mutex;

extern void gf_context_update(gf_context_t context);
extern int gf_color_translate(gf_color_t *scolor,unsigned ncolors,disp_color_t *dcolors,gf_format_t dformat);
extern void gf_context_set_error(gf_context_t context, int err);

extern void _gf_layer_detach(gf_layer_t layer);
extern void _gf_display_detach(gf_display_t display);
extern int _gf_dev_get_corefuncs(gf_dev_t gdev,unsigned pixel_format,disp_draw_corefuncs_t **corefuncs,disp_draw_corefuncs_t **corefuncs_sw);
extern void _gf_dev_set_error(gf_dev_t gdev, int err);
extern int _gf_get_disp_format(gf_format_t gf_format, unsigned *disp_surface_format, unsigned *disp_layer_format);
extern gf_format_t _gf_get_format(unsigned disp_format);
extern int gf_dev_islocked(gf_dev_t gdev);

extern void _gf_surface_free(gf_surface_t surface);
extern int _gf_get_crtc_settings(disp_adapter_t *adapter, disp_crtc_settings_t *settings);
extern void *_gf_driver_callback(void *handle, unsigned cmd, void *data);

extern void _gf_vcap_detach(gf_vcap_t vcap);

extern int iod_surface_alloc(gf_dev_t gfx, int *dispno, int *layer, int nlayers,
    int surface_idx, gf_surface_t surface, int width, int height,
    gf_format_t format, unsigned surface_flags, unsigned hint_flags, unsigned flags, int hw_locked);
extern int iod_surface_free(int fd, gf_surface_t surface, int hw_locked);
extern int iod_surface_get_by_sid(gf_dev_t gfx, gf_surface_t surface,gf_sid_t sid);
extern int iod_cursor_set_bitmap(int fd, int dispno, unsigned cursor_index, 
    const uint8_t *fg_bmp, const uint8_t *bg_bmp,
    unsigned fg_color, unsigned bg_color, int hotspot_x, int hotspot_y,
    int w, int h, int stride);
extern int iod_cursor_set_pos(int fd, int dispno, unsigned cursor_index, int x, int y);
extern int iod_cursor_enable(int fd, int dispno, unsigned cursor_index, int enabled);
extern int iod_display_query(int fd, int *dispno, int *xres, int *yres,
    int *refresh, unsigned *format, int *nlayers, int *main_layer);
extern int iod_display_set_layer_order(int fd, int dispno,
    int nlayers, const unsigned *order, int wait_vsync, int wait_idle);
extern int iod_display_get_layer_order(int fd, int dispno, int nlayers, unsigned *order);
extern int iod_layer_query(int fd, int dispno,
    int layer, int format_index, gf_layer_info_t *info);
extern int iod_layer_attach(int fd, int dispno, int layer, unsigned flags);
extern int iod_layer_detach(int fd, int dispno, int layer);
extern int iod_layer_update(int fd, int dispno, int layer_idx[],
    disp_layer_state_t *state[], unsigned nlayers, unsigned flags);
extern int iod_vcap_update(int fd,
    int unit, disp_vcap_state_t *state, int wait_vsync);
extern int iod_layer_query_state(int fd,
    int dispno, int layer, disp_layer_state_t *state);
extern int iod_layer_flushrect(int fd, int dispno, int layer,
	int x1, int y1, int x2, int y2, unsigned lock);

/*
 * structures and enums for line and polygon clipping 
 */
typedef struct {
	int XMin, YMin, XMax, YMax;
} gf_region_t;

enum gf_clip_code {TOP = 0x1, BOTTOM = 0x2, RIGHT = 0x4, LEFT = 0x8};

void 		gf_polygon_clip(gf_context_t context, gf_point_t *pts, int npts,
								gf_point_t *rpts, int *rnpts);
int 		gf_line_clip(gf_context_t context, gf_point_t *pC0, gf_point_t *pC1);		
gf_color_t 	gf_read_pixel(gf_context_t context, unsigned x, unsigned y);
void 		gf_read_pixels(gf_context_t context, unsigned char *buf, 
								unsigned x, unsigned y, unsigned size);
void 		gf_write_pixels(gf_context_t context, unsigned char *buf, 
								unsigned x, unsigned y, unsigned size);								
void 		gf_write_pixel(gf_context_t context, gf_color_t clr, unsigned x, unsigned y);
void 		gf_blend_pixel(gf_context_t context, unsigned x, unsigned y, uint8_t alph);
void		gf_quad_to_cubic(gf_point_t *pt);
gf_point_t 	*gf_bezier_to_polyline(gf_point_t *ctrlPts, int *num);

__END_DECLS

#endif /* _GF_GF_INTERNALS_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/private/gf/gf_internals.h $ $Rev: 224586 $" )
