#include "../include/libOskGraphics.h"

#include <stdio.h>
#include <math.h>

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
    int frame = 0;
    while(PollEvents()) {
        BeginFrame(win);

        float x0 = 300.0f, y0 = 300.0f;

        DrawCircle(win, x0, y0, 100, i % 50, OSK_RED);

        frame += 1;
        i += (frame % 40) == 39 ? 1 : 0;

        EndFrame(win);
    }

    return 0;
}