/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _OVG11_API_BACKEND_H
#define _OVG11_API_BACKEND_H

#include "VG/openvg.h"
#include "VG/vgu.h"

typedef struct ovg11_interface
{
	VGErrorCode (*vgGetError)(void);

	void (*vgFlush)(void);
	void (*vgFinish)(void);

	/* Getters and Setters */
	void (*vgSetf)(VGParamType type, VGfloat value);
	void (*vgSeti)(VGParamType paramType, VGint value);
	void (*vgSetfv)(VGParamType type, VGint count, const VGfloat *values);
	void (*vgSetiv)(VGParamType type, VGint count, const VGint *values);

	VGfloat (*vgGetf)(VGParamType type);
	VGint (*vgGeti)(VGParamType type);
	VGint (*vgGetVectorSize)(VGParamType type);
	void (*vgGetfv)(VGParamType type, VGint count, VGfloat *values);
	void (*vgGetiv)(VGParamType type, VGint count, VGint *values);

	void (*vgSetParameterf)(VGHandle object, VGint paramType, VGfloat value);
	void (*vgSetParameteri)(VGHandle object, VGint paramType, VGint value);
	void (*vgSetParameterfv)(VGHandle object, VGint paramType, VGint count, const VGfloat *values);
	void (*vgSetParameteriv)(VGHandle object, VGint paramType, VGint count, const VGint *values);

	VGfloat (*vgGetParameterf)(VGHandle object, VGint paramType);
	VGint (*vgGetParameteri)(VGHandle object, VGint paramType);
	VGint (*vgGetParameterVectorSize)(VGHandle object, VGint paramType);
	void (*vgGetParameterfv)(VGHandle object, VGint paramType, VGint count, VGfloat *values);
	void (*vgGetParameteriv)(VGHandle object, VGint paramType, VGint count, VGint *values);

	/* Matrix Manipulation */
	void (*vgLoadIdentity)(void);
	void (*vgLoadMatrix)(const VGfloat *m);
	void (*vgGetMatrix)(VGfloat *m);
	void (*vgMultMatrix)(const VGfloat *m);
	void (*vgTranslate)(VGfloat tx, VGfloat ty);
	void (*vgScale)(VGfloat sx, VGfloat sy);
	void (*vgShear)(VGfloat shx, VGfloat shy);
	void (*vgRotate)(VGfloat angle);

	/* Masking and Clearing */
	void (*vgMask)(VGImage mask, VGMaskOperation operation, VGint x, VGint y, VGint width, VGint height);
	void (*vgClear)(VGint x, VGint y, VGint width, VGint height);

	/* Paths */
	VGPath (*vgCreatePath)(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias,
							VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities);
	void (*vgClearPath)(VGPath path, VGbitfield capabilities);
	void (*vgDestroyPath)(VGPath path);
	void (*vgRemovePathCapabilities)(VGPath path, VGbitfield capabilities);
	VGbitfield (*vgGetPathCapabilities)(VGPath path);
	void (*vgAppendPath)(VGPath dstPath, VGPath srcPath);
	void (*vgAppendPathData)(VGPath dstPath, VGint numSegments, const VGubyte *pathSegments, const void *pathData);
	void (*vgModifyPathCoords)(VGPath dstPath, VGint startIndex, VGint numSegments, const void *pathData);
	void (*vgTransformPath)(VGPath dstPath, VGPath srcPath);
	VGboolean (*vgInterpolatePath)(VGPath dstPath, VGPath startPath, VGPath endPath, VGfloat amount);
	VGfloat (*vgPathLength)(VGPath path, VGint startSegment, VGint numSegments);
	void (*vgPointAlongPath)(VGPath path, VGint startSegment, VGint numSegments, VGfloat distance,
								VGfloat *x, VGfloat *y, VGfloat *tangentX, VGfloat *tangentY);
	void (*vgPathBounds)(VGPath path, VGfloat *minX, VGfloat *minY, VGfloat *width, VGfloat *height);
	void (*vgPathTransformedBounds)(VGPath path, VGfloat *minX, VGfloat *minY, VGfloat *width, VGfloat *height);
	void (*vgDrawPath)(VGPath path, VGbitfield paintModes);

	/* Paint */
	VGPaint (*vgCreatePaint)(void);
	void (*vgDestroyPaint)(VGPaint paint);
	void (*vgSetPaint)(VGPaint paint, VGbitfield paintModes);
	VGPaint (*vgGetPaint)(VGPaintMode paintMode);
	void (*vgSetColor)(VGPaint paint, VGuint rgba);
	VGuint (*vgGetColor)(VGPaint paint);
	void (*vgPaintPattern)(VGPaint paint, VGImage pattern);

	/* Images */
	VGImage (*vgCreateImage)(VGImageFormat format, VGint width, VGint height, VGbitfield allowedQuality);
	void (*vgDestroyImage)(VGImage image);
	void (*vgClearImage)(VGImage image, VGint x, VGint y, VGint width, VGint height);
	void (*vgImageSubData)(VGImage image, const void *data, VGint dataStride, VGImageFormat dataFormat,
							VGint x, VGint y, VGint width, VGint height);
	void (*vgGetImageSubData)(VGImage image, void *data, VGint dataStride, VGImageFormat dataFormat,
								VGint x, VGint y, VGint width, VGint height);
	VGImage (*vgChildImage)(VGImage parent, VGint x, VGint y, VGint width, VGint height);
	VGImage (*vgGetParent)(VGImage image); 
	void (*vgCopyImage)(VGImage dst, VGint dx, VGint dy, VGImage src, VGint sx, VGint sy,
						VGint width, VGint height, VGboolean dither);
	void (*vgDrawImage)(VGImage image);
	void (*vgSetPixels)(VGint dx, VGint dy, VGImage src, VGint sx, VGint sy, VGint width, VGint height);
	void (*vgWritePixels)(const void *data, VGint dataStride, VGImageFormat dataFormat,
							VGint dx, VGint dy, VGint width, VGint height);
	void (*vgGetPixels)(VGImage dst, VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height);
	void (*vgReadPixels)(void *data, VGint dataStride, VGImageFormat dataFormat, VGint sx, VGint sy, VGint width, VGint height);
	void (*vgCopyPixels)(VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height);

	/* Image Filters */
	void (*vgColorMatrix)(VGImage dst, VGImage src, const VGfloat *matrix);
	void (*vgConvolve)(VGImage dst, VGImage src, VGint kernelWidth, VGint kernelHeight, VGint shiftX, VGint shiftY,
						const VGshort *kernel, VGfloat scale, VGfloat bias, VGTilingMode tilingMode);
	void (*vgSeparableConvolve)(VGImage dst, VGImage src, VGint kernelWidth, VGint kernelHeight, VGint shiftX, VGint shiftY,
								const VGshort *kernelX, const VGshort *kernelY, VGfloat scale, VGfloat bias,
								VGTilingMode tilingMode);
	void (*vgGaussianBlur)(VGImage dst, VGImage src, VGfloat stdDeviationX, VGfloat stdDeviationY, VGTilingMode tilingMode);
	void (*vgLookup)(VGImage dst, VGImage src, const VGubyte *redLUT, const VGubyte *greenLUT, const VGubyte *blueLUT,
						const VGubyte *alphaLUT, VGboolean outputLinear, VGboolean outputPremultiplied);
	void (*vgLookupSingle)(VGImage dst, VGImage src, const VGuint *lookupTable, VGImageChannel sourceChannel,
							VGboolean outputLinear, VGboolean outputPremultiplied);

	/* Hardware Queries */
	VGHardwareQueryResult (*vgHardwareQuery)(VGHardwareQueryType key, VGint setting);

	/* Renderer and Extension Information */
	const VGubyte *(*vgGetString)(VGStringID name);

	VGMaskLayer (*vgCreateMaskLayer)(VGint width, VGint height);
	void (*vgDestroyMaskLayer)(VGMaskLayer maskLayer);
	void (*vgRenderToMask)( VGPath path, VGbitfield paintModes, VGMaskOperation operation);
	void (*vgFillMaskLayer)(VGMaskLayer maskLayer, VGint x, VGint y, VGint width, VGint height, VGfloat value);
	void (*vgCopyMask)(VGMaskLayer maskLayer, VGint sx, VGint sy, VGint dx, VGint dy, VGint width, VGint height);

	/* Text */
	VGFont (*vgCreateFont)(VGint glyphCapacityHint);
	void (*vgDestroyFont)(VGFont font);
	void (*vgSetGlyphToPath)(VGFont font, VGuint glyphIndex, VGPath path, VGboolean isHinted,
								VGfloat glyphOrigin[2], VGfloat escapement[2]);
	void (*vgSetGlyphToImage)(VGFont font, VGuint glyphIndex, VGImage image, VGfloat glyphOrigin[2], VGfloat escapement[2]);
	void (*vgClearGlyph)(VGFont font,VGuint glyphIndex);
	void (*vgDrawGlyph)(VGFont font, VGuint glyphIndex, VGbitfield paintModes, VGboolean allowAutoHinting);
	void (*vgDrawGlyphs)(VGFont font, VGint glyphCount, VGuint *glyphIndices, VGfloat *adjustments_x, VGfloat *adjustments_y,
							VGbitfield paintModes, VGboolean allowAutoHinting);

	/* VGU */
	VGUErrorCode (*vguLine)(VGPath path, VGfloat x0, VGfloat y0, VGfloat x1, VGfloat y1);
	VGUErrorCode (*vguPolygon)(VGPath path, const VGfloat *points, VGint count, VGboolean closed);
	VGUErrorCode (*vguRect)(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height);
	VGUErrorCode (*vguRoundRect)(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height,
									VGfloat arcWidth, VGfloat arcHeight);
	VGUErrorCode (*vguEllipse)(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height);
	VGUErrorCode (*vguArc)(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height,
							VGfloat startAngle, VGfloat angleExtent, VGUArcType arcType);
	VGUErrorCode (*vguComputeWarpQuadToSquare)(VGfloat sx0, VGfloat sy0, VGfloat sx1, VGfloat sy1, VGfloat sx2, VGfloat sy2,
												VGfloat sx3, VGfloat sy3, VGfloat *matrix);
	VGUErrorCode (*vguComputeWarpSquareToQuad)(VGfloat dx0, VGfloat dy0, VGfloat dx1, VGfloat dy1, VGfloat dx2, VGfloat dy2,
												VGfloat dx3, VGfloat dy3, VGfloat *matrix);
	VGUErrorCode (*vguComputeWarpQuadToQuad)(VGfloat dx0, VGfloat dy0, VGfloat dx1, VGfloat dy1, VGfloat dx2, VGfloat dy2,
												VGfloat dx3, VGfloat dy3, VGfloat sx0, VGfloat sy0, VGfloat sx1, VGfloat sy1,
												VGfloat sx2, VGfloat sy2, VGfloat sx3, VGfloat sy3, VGfloat *matrix);
} ovg11_interface_t;

#endif // _OVG11_API_BACKEND_H

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/trunk/lib/openvg/G12/ovg/bb2d/gx_2d.h $ $Rev: 219724 $" )
