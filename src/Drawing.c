#include "../include/libOskGraphics.h"
#include "../include/Internal_Window.h"

#define ASSERT_SUCCESS(x) \
    do { if ((x) == -1) return -1; } while (0)

int BeginFrame(OskWindow* window) {
    ASSERT_SUCCESS(window->Backend.BeginFrame(window));

    return 0;
}

int EndFrame(OskWindow* window) {
    ASSERT_SUCCESS(window->Backend.EndFrame(window));

    return 0;
}

int SetBackground(OskWindow* window, OskColour colour) {
    ASSERT_SUCCESS(window->Backend.SetBackground(window, colour));

    return 0;
}

int DrawTriangle(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour colour) {
    ASSERT_SUCCESS(window->Backend.DrawTriangle(window, x0, y0, x1, y1, x2, y2, colour));

    return 0;
}