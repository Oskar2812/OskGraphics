#ifndef INTERNAL_DRAWING_H
#define INTERNAL_DRAWING

#include "libOskGraphics.h"

int BeginFrameGPU(OskWindow* window);

int EndFrameGPU(OskWindow* window);

int SetBackgroundGPU(OskWindow* window, OskColour colour);

int BeginFrameCPU(OskWindow* window);

int EndFrameCPU(OskWindow* window);

int SetBackgroundCPU(OskWindow* window, OskColour colour);

int DrawTriangleCPU(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour colour);

int DrawQuadCPU(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour colour);

int DrawCircleCPU(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour);

int DrawLineCPU(OskWindow* window, float x0, float y0, float x1, float y1, float thickness, OskColour colour);

#endif