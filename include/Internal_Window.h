#ifndef INTERNAL_WINDOW_H
#define INTERNAL_WINDOW_H

#include "libOskGraphics.h"
#include <windows.h>
#include <GL/gl.h>

typedef struct {
    int (*BeginFrame)(OskWindow* window);
    int (*EndFrame)(OskWindow* window);
    int (*SetBackground)(OskWindow* window, OskColour colour);
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
};

#endif