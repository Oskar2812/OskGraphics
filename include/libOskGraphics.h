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
/// @param render rendering backend to use for this window (RENDER_CPU or RENDER_GPU)
/// @return pointer to the created window, or NULL on failure
/// @note Only the CPU backend currently implements the Draw* functions below; calling
///       them on a RENDER_GPU window is undefined behaviour
OskWindow* OpenWindow(uint32_t width, uint32_t height, const char* title, RenderType render);

/// @brief Polls and processes pending window events for all open windows
/// @return 1 if the application should keep running, or 0 once a quit message has been received
int PollEvents();

//######################################## OskGraphics Drawing #########################################################################################

/// @brief RGBA colour, with each channel in the range [0.0, 1.0]
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

/// @brief Begins a new frame: clears the CPU pixel buffer (RENDER_CPU) or the GL colour
///        buffer (RENDER_GPU) using the window's current background colour, and resizes
///        the backing buffer/viewport if the window has been resized since the last frame
/// @param window window to begin the frame for
/// @return 0 on success, -1 on failure
int BeginFrame(OskWindow* window);

/// @brief Ends the current frame and presents it: blits the pixel buffer to the window
///        (RENDER_CPU) or swaps the GL buffers (RENDER_GPU)
/// @param window window to end the frame for
/// @return 0 on success, -1 on failure
int EndFrame(OskWindow* window);

/// @brief Sets the colour that BeginFrame clears the window to
/// @param window window to set the background colour for
/// @param colour colour to clear the frame with
/// @return 0 on success, -1 on failure
int SetBackground(OskWindow* window, OskColour colour);

/// @brief Draws a filled triangle with the given vertices
/// @param window window to draw into (must be a RENDER_CPU window)
/// @param x0 x coordinate of the first vertex, in pixels
/// @param y0 y coordinate of the first vertex, in pixels
/// @param x1 x coordinate of the second vertex, in pixels
/// @param y1 y coordinate of the second vertex, in pixels
/// @param x2 x coordinate of the third vertex, in pixels
/// @param y2 y coordinate of the third vertex, in pixels
/// @param colour fill colour of the triangle
/// @return 0 on success, -1 on failure
int DrawTriangle(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour colour);

/// @brief Draws a filled quadrilateral by splitting it into two triangles: (x0,y0)-(x1,y1)-(x3,y3)
///        and (x1,y1)-(x2,y2)-(x3,y3)
/// @param window window to draw into (must be a RENDER_CPU window)
/// @param x0 x coordinate of the first vertex, in pixels
/// @param y0 y coordinate of the first vertex, in pixels
/// @param x1 x coordinate of the second vertex, in pixels
/// @param y1 y coordinate of the second vertex, in pixels
/// @param x2 x coordinate of the third vertex, in pixels
/// @param y2 y coordinate of the third vertex, in pixels
/// @param x3 x coordinate of the fourth vertex, in pixels
/// @param y3 y coordinate of the fourth vertex, in pixels
/// @param color fill colour of the quad
/// @return 0 on success, -1 on failure
/// @note Vertices must be supplied in order (e.g. all clockwise or all counter-clockwise)
///       around the quad, since the shape is drawn as the two triangles described above
int DrawQuad(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour color);

/// @brief Draws a filled circle approximated by a fan of triangles centred on (cx, cy)
/// @param window window to draw into (must be a RENDER_CPU window)
/// @param cx x coordinate of the circle's centre, in pixels
/// @param cy y coordinate of the circle's centre, in pixels
/// @param radius radius of the circle, in pixels
/// @param segments number of triangles used to approximate the circle; higher values give a smoother circle
/// @param colour fill colour of the circle
/// @return 0 on success, -1 on failure
int DrawCircle(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour);

/// @brief Draws a line of the given thickness between two points, rendered as a quad
/// @param window window to draw into (must be a RENDER_CPU window)
/// @param x0 x coordinate of the start point, in pixels
/// @param y0 y coordinate of the start point, in pixels
/// @param x1 x coordinate of the end point, in pixels
/// @param y1 y coordinate of the end point, in pixels
/// @param thickness width of the line, in pixels
/// @param colour colour of the line
/// @return 0 on success, or -1 if the start and end points are (almost) coincident
int DrawLine(OskWindow* window, float x0, float y0, float x1, float y1, float thickness, OskColour colour);

#endif