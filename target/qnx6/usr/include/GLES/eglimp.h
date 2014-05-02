#include <GLES/egl.h>
#include <GLES/glext.h>

#include <graphics/display.h>
#include <gf/gf.h>
#include <gf/gf_internals.h>

#define EGL_LOCK_DEVICE(mutex)      gfpr_mutex_lock(mutex)
#define EGL_UNLOCK_DEVICE(mutex)    gfpr_mutex_unlock(mutex)

#define EGL_NUM_APIS        2

typedef enum {
    EGL_APIIDX_OPENGL = 0x00000000,
    EGL_APIIDX_OPENVG = 0x00000001,
} egl_api_idx;

typedef enum {
    EGL_SFLAG_DESTROY_PENDING = 0x00000001, /* Surface will be destroyed when no longer in use */
} egl_surface_flags;

typedef struct {
    struct _gf_rendersurf   rsurf;
    EGLConfig       config;
    unsigned        type;
    EGLint          largest_pbuffer;
    egl_surface_flags   flags;
    EGLContext      bound_context;
    egl_api_idx     bound_api;
    egl_api_idx     bound_thread;
    int         swap_buffers;
    void            *driver_target;
    gf_layer_t      layer;
    void            (*swap_layer)(gf_layer_t layer,
                    disp_surface_t *surf, int no_wait_vsync);
    int         destroyed;
} egl_surface_t;

typedef enum {
    EGL_CFLAG_DESTROY_PENDING = 0x00000001, /* Context will be destroyed when no longer current */
} egl_context_flags;

typedef struct {
    egl_api_idx     bound_api;
    void            *api_ctx;
    egl_context_flags   flags;
    EGLConfig       config;
    egl_surface_t       *read_surf;
    egl_surface_t       *write_surf;
    gfpr_thread_t       bound_thread;
} egl_context_t;

typedef void (*egl_funcptr_t)();
struct egl_state;

typedef struct {
    int         (*init)(struct egl_state *estate, struct _gf_dev *gf);

    int         (*create_context)(struct egl_state *estate, egl_context_t *ctx, egl_context_t *share_ctx);
    void            (*destroy_context)(struct egl_state *estate, egl_context_t *ctx);
    int         (*make_current)(struct egl_state *estate, egl_context_t *ctx);
    egl_context_t *     (*get_current)(struct egl_state *estate);

    int         (*query_buffer_config)(struct egl_state *estate,
                    int config_idx, disp_rend_buffer_config_t *config);

    void *          (*create_target)(struct egl_state *estate, int config, int width, int height);
    void            (*destroy_target)(struct egl_state *estate, void *target);

    void            (*set_draw_surface)(struct egl_state *estate, egl_surface_t *esurf);
    void            (*post_color_buffer)(struct egl_state *estate, egl_surface_t *esurf);

    void            (*read_image)(struct egl_state *estate,
                    int sxoff, int syoff, int width, int height,
                    unsigned dformat, int dstride,
                    disp_surface_t * src, void *dst,
                    int y_order_ascending);

    egl_funcptr_t       (*get_proc_address)(struct egl_state *estate,
                    const char *procname);
} egl_apifuncs_t;

/* Global state structure */
typedef struct egl_state {
    struct _gf_dev      *gf;
    int         connected;
    int         initialized;
    GLint           lasterror;
    disp_draw_context_t draw_ctx;
    disp_draw_3dfuncs_t *rendfuncs;
    disp_draw_miscfuncs_t   *miscfuncs;
    disp_adapter_t      *adapter;
    get_corefuncs_t     get_corefuncs;
    int         xres, yres;
    int         num_config;
    disp_3d_caps_t      caps;
    void            *shmem;
    int         no_wait_vsync;
    int         default_api;
    int         cur_api;
    int         have_gl;
    int         have_vg;
    int         apis_registered;
    void            *apihandle[EGL_NUM_APIS];
    egl_apifuncs_t      apifuncs[EGL_NUM_APIS];
    void            (*destroy_surface_callback)
                    (struct egl_state *estate,
                    egl_surface_t *esurf);
} egl_state_t;

extern egl_state_t      egl_state;

/* Internal functions */
void egl_slog_perror(const char *errmsg);
void egl_slog_dlerror(const char *errmsg);
void egl_destroy_surface(egl_state_t *estate, egl_surface_t *esurf);
void egl_register_apis(egl_state_t *estate);

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/BX650_3549_pasa-ccr/lib/khronos/devg/gles/egl/private/GLES/eglimp.h $ $Rev: 219996 $" )
