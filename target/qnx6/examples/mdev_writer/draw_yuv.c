/*
 * draw_yuv.c
 *
 *  Created on: Nov 8, 2012
 *      Author: feiwang
 */

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define MAX_NOBJECTS  6

//#define VYUY(v,y1,u, y2) ((v)<<24|(y1)<<16|(u)<<8|y2)
#define RGB(r, g, b)    ((((uint32_t)(r))<<16) | (((uint32_t)(g))<<8) | ((uint32_t)(b)))
#define RGB_R(c)     ((uint8_t)(((c)>>16)&0xFF))
#define RGB_G(c)     ((uint8_t)(((c)>>8)&0xFF))
#define RGB_B(c)     ((uint8_t)(c)&0xFF)

#define CROP(x)    (x) //((x) > 255 ? 255:((x)<0?0:(x)))

typedef struct {
    double angle, step;
    double left, top;
    int width, heigh;
    int color;
} flying_object_t;

flying_object_t objects[MAX_NOBJECTS];
int nobjects = 0;

static inline int rgb_to_y(uint8_t R, uint8_t G, uint8_t B) {
    return CROP(min(abs(R * 2104 + G * 4130 + B * 802 + 4096 + 131072) >> 13, 235));
}
static inline int rgb_to_cr(uint8_t R, uint8_t G, uint8_t B) {
    return CROP(min(abs(R * -1214 + G * -2384 + B * 3598 + 4096 + 1048576) >> 13, 240));
}
static inline int rgb_to_cb(uint8_t R, uint8_t G, uint8_t B) {
    return CROP(min(abs(R * 3598 + G * -3013 + B * -585 + 4096 + 1048576) >> 13, 240));
}

static void draw_background(uint32_t * canvas, int w, int h) {
    int r, c;
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) {
            *canvas++ = RGB((r)%255, (c)%255, (r+c)%255);
        }
    }
}

static void init_object(flying_object_t * obj, int w, int h) {

    obj->top = (rand() % (h - 50)) + 10;
    obj->left = (rand() % (w - 50)) + 10;

    //make sure w and h both in range of (5 - 55) and abs(w-h) < 10
    int wh = (rand() % 50) + 10;
    obj->width = wh + (rand() % 10 - 5);
    obj->heigh = wh + (rand() % 10 - 5);

    obj->step = (rand() % 8) + 8;
    obj->angle = M_PI / 180 * (rand() % 89 + 1);
    obj->color = (rand() % 100) + 100;
}
static void init_objects(int w, int h) {
    srand(time(NULL));
    nobjects = (rand() % (MAX_NOBJECTS - 2)) + 2;
    int i;
    for (i = 0; i < nobjects; i++) {
        init_object(objects + i, w, h);
    }
}

static void draw_object(flying_object_t * obj, uint32_t * canvas, int cw, int ch) {

    //draw shadow
    int top = obj->top + 10;
    int left = obj->left + 10;
    int bottom = min(top + obj->heigh, ch);
    int right = min(left + obj->width, cw);

    const uint32_t shadow = RGB(100, 100, 100);
    {
        int x, y;
        uint32_t * ptr = canvas + top * cw;
        for (y = top; y < bottom; y++) {
            uint32_t * dst = ptr + left;
            for (x = left; x <= right; x++) {
                *dst++ = shadow;
            }
            ptr += cw;
        }
    }

    //draw object
    top = obj->top;
    left = obj->left;
    bottom = min(top + obj->heigh, ch);
    right = min(left + obj->width, cw);
    {
        int x, y;
        uint32_t * ptr = canvas + top * cw;
        for (y = top; y < bottom; y++) {
            uint32_t * dst = ptr + left;
            for (x = left; x <= right; x++) {
                uint32_t src = * dst;
                //we do a 50% alpha blending for fun
                uint8_t r = ((RGB_R(src) + (x+obj->color)%255)>>1)%255;
                uint8_t g = ((RGB_G(src) + (x+y+obj->color)%255)>>1)%255;
                uint8_t b = ((RGB_B(src) + (y+obj->color)%255)>>1)%255;
                *dst++ = RGB(r, g, b);
            }
            ptr += cw;
        }
    }

    //calculate next position
    double dleft = obj->left + obj->step * cos(obj->angle);
    if (dleft <= cw - obj->width && dleft >= 0) {
        obj->left = dleft;
    } else {
        obj->angle = M_PI - obj->angle;
        obj->left += (obj->step * cos(obj->angle));
    }

    double dtop = obj->top + (obj->step * sin(obj->angle));
    if (dtop <= ch - obj->heigh && dtop >= 0) {
        obj->top = dtop;
    } else {
        obj->angle = M_PI * 2 - obj->angle;
        obj->top += (obj->step * sin(obj->angle));
    }
}

void draw_uyvy_img(uint8_t * dest, uint32_t * canvas, int w, int h, int stride) {

    if (!nobjects) {
        init_objects(w, h);
    }
    draw_background(canvas, w, h);
    int i;
    for (i = 0; i < nobjects; i++) {
        draw_object(objects + i, canvas, w, h);
    }

    //convert the RGB canvas to YVYU dest
    int r, c;
    uint8_t * ptr = dest;
    for (r = 0; r < h; r++) {
        uint8_t * dst = ptr;
        for (c = 0; c < w; c += 2) {
            uint32_t c1 = *canvas++;
            uint32_t c2 = *canvas++;

            uint8_t r1 = RGB_R(c1), r2 = RGB_R(c2);
            uint8_t g1 = RGB_G(c1), g2 = RGB_G(c2);
            uint8_t b1 = RGB_B(c1), b2 = RGB_B(c2);

            *dst++ = (rgb_to_cr(r1, g1, b1) + rgb_to_cr(r2, g2, b2)) / 2;
            *dst++ = rgb_to_y(r1, g1, b1);
            *dst++ = (rgb_to_cb(r1, g1, b1) + rgb_to_cb(r2, g2, b2)) / 2;
            *dst++ = rgb_to_y(r2, g2, b2);
        }
        ptr += stride;
    }
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/mmedia/streamers/mdev_streamer/mdev_writer/draw_yuv.c $ $Rev: 718372 $")
#endif
