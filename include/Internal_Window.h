#ifndef INTERNAL_WINDOW_H
#define INTERNAL_WINDOW_H

#include "libOskGraphics.h"
#include <windows.h>
#include <GL/gl.h>

typedef struct {
    int (*BeginFrame)(OskWindow* window);
    int (*EndFrame)(OskWindow* window);
    int (*SetBackground)(OskWindow* window, OskColour colour);
    int (*DrawTriangle)(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour color);
    int (*DrawQuad)(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour color);
    int (*DrawCircle)(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour);
} RenderBackend;

struct OskWindow {
    RenderType RenderType;
    RenderBackend Backend;

    HWND WindowHandle;
    
    uint32_t Width;
    uint32_t Height;
    int IsResized;

    // GPU only
    GLuint ShaderProgram;
    HGLRC GLContext;
    HDC DeviceContext;

    // CPU only
    uint8_t* PixelBuffer;
    OskColour BackGroundColour;
};

#endif