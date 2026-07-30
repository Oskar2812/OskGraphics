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
        BeginFrame(win);

        float x0 = 200.0f, y0 = 100.0f;
        float x1 = 50.0f, y1 = 400.0f;
        float x2 = 350.0f, y2 = 400.0f;
        float x3 = 500.0f, y3 = 100.0f;
        

        DrawQuad(win, x0, y0, fmodf(x1 + i, width), y1, fmodf(x2 + i, width), y2, x3, y3, OSK_RED);

        i += 1;

        EndFrame(win);
    }

    return 0;
}