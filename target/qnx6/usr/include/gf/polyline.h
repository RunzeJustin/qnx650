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

#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#include <stdlib.h>
#include <gf/gf.h>
#include <gf/gf_internals.h>

#ifndef __FIXEDPOINT_H_INCLUDED
#include "fxpt/fxpt_math.h"
#endif

#ifndef bool
typedef _uint32	bool;
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#define SIGN(a) 			((a>0)?1:((a<0)?-1:0))
#define MIN(a, b)			((a)<(b)?(a):(b))
#define MAX(a, b)			((a)>(b)?(a):(b))	

/* definitions for rasterizing polylines/polygons, with anti-aliasing built in */
/*
 * \brief	Converts a set of edges to coverage values for each pixel and
 *			calls pixelPipe() for painting a pixel.
 * \param	
 * \return	
 * \note		
 */

typedef struct Edge
{
	gf_fxpt_t		v0;
	gf_fxpt_t		v1;
} edge;

typedef struct ScissorEdge
{
	_int32		x;
	_int32		miny;
	_int32		maxy;
	_int32		direction;		//1 start, -1 end
} scissorEdge;

typedef struct ActiveEdge
{
	gf_fxpt_t		v0;				/* start point */
	gf_fxpt_t		v1;				/* end point */
	gf_fxpt_t		vd;				/* vector representation of the edge */
	_int32			direction;		/* -1 down, 1 up */
	fxpt_real		minx;			/* for the current scanline */
	fxpt_real		maxx;			/* for the current scanline */
	gf_fxpt_t		n;
	fxpt_real		cnst;			/* distance */
	fxpt_real		inv;			/* inverse of v1.y - v0.y */
	fxpt_real		bminx;
	fxpt_real		bmaxx;
} activeEdge;

typedef struct Sample
{
	fxpt_real		x;
	fxpt_real		y;
	fxpt_real		weight;
} sample;

typedef struct 
{
	_uint32			m_indexEdge;
	_uint32			m_sizeEdge;
	activeEdge		**m_edges;
	_uint32			m_indexScissor;	
	_uint32			m_sizeScissor;
	scissorEdge		*m_scissorEdges;
	bool			m_scissor;
	fxpt_real		m_surfMinx;
	fxpt_real		m_surfMiny;
	fxpt_real		m_surfMaxx;
	fxpt_real		m_surfMaxy;			
} rasterizer;

/*
 * \brief	definitions and operations for gf stroked polyline/polygon.
 * \param	
 * \return	
 * \note		
 */
enum VertexFlags
{
	START_POLY				= (1<<0),
	END_POLY				= (1<<1),
	START_SEGMENT			= (1<<2),
	END_SEGMENT				= (1<<3),
	CLOSE_POLY				= (1<<4),
	IMPLICIT_CLOSE_POLY		= (1<<5),
	IN_DASH					= (1<<6)
}eVertexFlags;

typedef struct
{
	gf_fxpt_t		userPosition;
	gf_fxpt_t		userTangent;
	fxpt_real 		polyLength;
	_uint32			flags;
} Vertex;


typedef struct
{
	gf_fxpt_t		p;
	gf_fxpt_t		t;
	gf_fxpt_t		ccw;
	gf_fxpt_t		cw;
	fxpt_real		polyLength;
	_uint32			flags;
	bool			inDash;
}StrokeVertex;

typedef struct
{
    _int32	start;
    _int32	end;
}VertexIndex;

typedef enum {
  CLOSE           	= ( 0 << 1),
  MOVE_TO       	= ( 1 << 1),
  LINE_TO      		= ( 2 << 1),
} ePolySegment;
    
typedef struct
{
	/* input data */
	unsigned int		m_caps;
	VertexIndex			*m_segmentToVertex;
	/* data produced by tessellation */
	Vertex				*m_vertices;
	_int32				m_vtxSize;	
	_int32				m_curVtxSize;
	fxpt_real			m_userMinx;
	fxpt_real			m_userMiny;
	fxpt_real			m_userMaxx;
	fxpt_real			m_userMaxy;
	gf_context_t		ctx;	
	rasterizer			*ras;
}strokedPoly;
/* Vector substraction */
static gf_fxpt_t fxpt_minus(gf_fxpt_t t1, gf_fxpt_t t2)
{
	gf_fxpt_t tmp;
	tmp.x = t1.x - t2.x;
	tmp.y = t1.y - t2.y;
	return tmp;
}
/* Vector normaliztion */
static gf_fxpt_t fxpt_norm(gf_fxpt_t t)
{
	gf_fxpt_t tmp;
	fxpt_real lx, ly;
	
	if(t.x == 0){
		tmp.x = 0;
		tmp.y = SIGN(t.y) * FXP_ONE;
		return tmp;
	}
	if(t.y == 0){
		tmp.x = SIGN(t.x) * FXP_ONE;
		tmp.y = 0;
		return tmp;
	}
	lx = FXP_REALDIV(t.y, t.x);
	lx = FXP_SQRT(FXP_ONE + FXP_REALMUL(lx, lx));
	ly = FXP_REALDIV(t.x, t.y);
	ly = FXP_SQRT(FXP_ONE + FXP_REALMUL(ly, ly));
	if(lx == 0){
		tmp.x = 0;
		tmp.y = SIGN(t.y) * FXP_ONE;
		return tmp;
	}
	if(ly == 0){
		tmp.y = 0;
		tmp.x = SIGN(t.x) * FXP_ONE;
		return tmp;
	}
	tmp.x = SIGN(t.x) * FXP_REALDIV(FXP_ONE, lx); 
	tmp.y = SIGN(t.y) * FXP_REALDIV(FXP_ONE, ly); 
	return tmp; 	
}
/* Vector setting */
static gf_fxpt_t fxpt_vector_set(fxpt_real x, fxpt_real y)
{	
	gf_fxpt_t t;
	t.x = x;
	t.y = y;
	return t;
}
/* Vector dot product */
static fxpt_real fxpt_vdot(gf_fxpt_t v1, gf_fxpt_t v2)
{
	return (FXP_REALMUL(v1.x, v2.x) + FXP_REALMUL(v1.y, v2.y));
}
strokedPoly *normalize_poly(gf_context_t ctx, const gf_point_t *pts, 
							size_t npoints, unsigned flags);
bool rasSet(rasterizer *ras);							
bool rasSetScissor(rasterizer *ras, scissorEdge *edges, unsigned int size);							
void rasAddEdge(strokedPoly *poly, gf_fxpt_t *v0, gf_fxpt_t *v1);
int rasFill(strokedPoly *poly, int vpx, int vpy, int vpwidth, int vpheight, int fillRule);
void rasDestroy(rasterizer *ras);							
#endif //_POLYLINE_H_

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/private/gf/polyline.h $ $Rev: 236566 $" )
