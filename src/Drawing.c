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

int DrawQuad(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour colour) {
    ASSERT_SUCCESS(window->Backend.DrawQuad(window, x0, y0, x1, y1, x2, y2, x3, y3, colour));

    return 0;
}

int DrawCircle(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour) {
    ASSERT_SUCCESS(window->Backend.DrawCircle(window, cx, cy, radius, segments, colour));

    return 0;
}

int DrawLine(OskWindow* window, float x0, float y0, float x1, float y1, float thickness, OskColour colour) {
    ASSERT_SUCCESS(window->Backend.DrawLine(window, x0, y0, x1, y1, thickness, colour));

    return 0;
}