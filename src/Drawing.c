#include "../include/libOskGraphics.h"
#include "../include/Internal_Window.h"


int BeginFrame(OskWindow* window) {
    if(!wglMakeCurrent(window->DeviceContext, window->GLContext)) {
        return -1;
    }

    if (window->IsResized) {
        glViewport(0, 0, window->Width, window->Height);
        window->IsResized = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    return 0;
}

int EndFrame(OskWindow* window) {
    if(!SwapBuffers(window->DeviceContext)) {
        return -1;
    };

    return 0;
}

int SetBackground(OskWindow* window, OskColour colour) {
    if(!wglMakeCurrent(window->DeviceContext, window->GLContext)) {
        return -1;
    }

    glClearColor(colour.r, colour.g, colour.b, colour.a);

    return 0;
}