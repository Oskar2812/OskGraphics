#ifndef INTERNAL_WINDOW_H
#define INTERNAL_WINDOW_H

#include <windows.h>
#include <GL/gl.h>

struct OskWindow {
    HWND WindowHandle;
    HGLRC GLContext;
    HDC DeviceContext;

    uint32_t Width;
    uint32_t Height;
    int IsResized;

    GLuint ShaderProgram;
};

#endif