#include "../include/libOskGraphics.h"

#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

void RotatePointAround(float px, float py, float cx, float cy, float theta, float* outX, float* outY) {
    float relX = px - cx;
    float relY = py - cy;

    *outX = cx + (cosf(theta) * relX - sinf(theta) * relY);
    *outY = cy + (sinf(theta) * relX + cosf(theta) * relY);
}

int main() {
    const char* title = "Oskars Graphics Window";

    uint32_t width = 600;
    uint32_t height = 600;

    OskWindow* win = OpenWindow(width, height, title, RENDER_CPU);
    if (win == NULL) {
        printf("Failed to open window\n");
        return 1;
    }

    SetBackground(win, OSK_BLACK);
    int i = 0;
    while(PollEvents()) {

        float theta = M_PI * i / (100.0f);

        BeginFrame(win);

        float x0 = 300.0f, y0 = 100.0f;
        float x1 = 150.0f, y1 = 400.0f;
        float x2 = 450.0f, y2 = 400.0f;

        float centerX = (x0 + x1 + x2) / 3.0f;
        float centerY = (y0 + y1 + y2) / 3.0f;

        float newX0, newY0, newX1, newY1, newX2, newY2;
        RotatePointAround(x0, y0, centerX, centerY, theta, &newX0, &newY0);
        RotatePointAround(x1, y1, centerX, centerY, theta, &newX1, &newY1);
        RotatePointAround(x2, y2, centerX, centerY, theta, &newX2, &newY2);

        DrawTriangle(win, newX0, newY0, newX1, newY1, newX2, newY2, OSK_RED);

        i += 1;

        EndFrame(win);
    }

    return 0;
}