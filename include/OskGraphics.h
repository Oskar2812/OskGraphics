#ifndef OSK_GRAPHICS_H
#define OSK_GRAPHICS_H

#include <inttypes.h>

//######################################## OskGraphics Window #########################################################################################

typedef struct OskWindow OskWindow;

/// @brief Opens a window with an attached OpenGL context
/// @param width width of the window in pixels
/// @param height height of the window in pixels
/// @param title title displayed on the window
/// @return pointer to the created window, or NULL on failure
OskWindow* OpenWindow(uint32_t width, uint32_t height, const char* title);

/// @brief Destroys a window and releases its associated resources
/// @param window the window to destroy
void DestroyOskWindow(OskWindow* window);

/// @brief Polls and processes pending window events
/// @return 0 on success, -1 otherwise
int PollEvents();

#endif