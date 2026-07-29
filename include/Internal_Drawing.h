#ifndef INTERNAL_DRAWING_H
#define INTERNAL_DRAWING

#include "libOskGraphics.h"

int BeginFrameGPU(OskWindow* window);

int EndFrameGPU(OskWindow* window);

int SetBackgroundGPU(OskWindow* window, OskColour colour);

int BeginFrameCPU(OskWindow* window);

int EndFrameCPU(OskWindow* window);

int SetBackgroundCPU(OskWindow* window, OskColour colour);

#endif