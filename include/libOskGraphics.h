#ifndef OSK_GRAPHICS_H
#define OSK_GRAPHICS_H

#include <inttypes.h>

#define OSK_PI 3.14159265358979323846

//######################################## OskGraphics Window #########################################################################################

typedef struct OskWindow OskWindow;

typedef enum {
    RENDER_CPU,
    RENDER_GPU
} RenderType;

/// @brief Opens a window with an attached OpenGL context
/// @param width width of the window in pixels
/// @param height height of the window in pixels
/// @param title title displayed on the window
/// @return pointer to the created window, or NULL on failure
OskWindow* OpenWindow(uint32_t width, uint32_t height, const char* title, RenderType render);

/// @brief Polls and processes pending window events
/// @return 0 on success, -1 otherwise
int PollEvents();

//######################################## OskGraphics Drawing #########################################################################################

typedef struct {
    float r;
    float g;
    float b;
    float a;
} OskColour;

static const OskColour OSK_BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
static const OskColour OSK_WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
static const OskColour OSK_RED   = {1.0f, 0.0f, 0.0f, 1.0f};
static const OskColour OSK_GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
static const OskColour OSK_BLUE  = {0.0f, 0.0f, 1.0f, 1.0f};

int BeginFrame(OskWindow* window);

int EndFrame(OskWindow* window);

int SetBackground(OskWindow* window, OskColour colour);

int DrawTriangle(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour colour);

int DrawQuad(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour color);

int DrawCircle(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour);

int DrawLine(OskWindow* window, float x0, float y0, float x1, float y1, float thickness, OskColour colour);

#endif