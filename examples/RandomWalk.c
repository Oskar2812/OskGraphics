#include "../include/libOskGraphics.h"

#include <stdlib.h>
#include <time.h>

#define TRAIL_LENGTH 200

typedef struct {
    float x, y;
} TrailPoint;

typedef struct {
    TrailPoint points[TRAIL_LENGTH];
    int count;
    int nextIndex;
} Trail;

void AddTrailPoint(Trail* trail, float x, float y) {
    trail->points[trail->nextIndex] = (TrailPoint){x, y};
    trail->nextIndex = (trail->nextIndex + 1) % TRAIL_LENGTH;
    if (trail->count < TRAIL_LENGTH) {
        trail->count++;
    }
}

void DrawTrail(OskWindow* window, Trail* trail) {
    for (int i = 0; i < trail->count - 1; i++) {
        int idx0 = (trail->nextIndex - trail->count + i + TRAIL_LENGTH) % TRAIL_LENGTH;
        int idx1 = (idx0 + 1) % TRAIL_LENGTH;

        // oldest point (i = 0) -> alpha near 0, newest point -> alpha near 1
        float alpha = (float)(i + 1) / (float)(trail->count - 1);

        OskColour fadedWhite = { 1.0f, 1.0f, 1.0f, alpha };

        DrawLine(window,
            trail->points[idx0].x, trail->points[idx0].y,
            trail->points[idx1].x, trail->points[idx1].y,
            2.0f, fadedWhite);
    }
}

int main() {
    OskWindow* win = OpenWindow(600, 600, "Trail Demo", RENDER_CPU);

    Trail trail = {0};
    float x = 300.0f, y = 300.0f;

    srand((unsigned int)time(NULL));

    while (PollEvents()) {
        BeginFrame(win);
        SetBackground(win, OSK_BLACK);   // dark background so a fading white line is visible

        // random walk: nudge x/y by a small random amount each frame
        float dx = ((float)rand() / RAND_MAX) * 6.0f - 3.0f;   // -3.0 to 3.0
        float dy = ((float)rand() / RAND_MAX) * 6.0f - 3.0f;

        x += dx;
        y += dy;

        // keep it roughly on screen
        if (x < 0.0f) x = 0.0f;
        if (x > 600.0f) x = 600.0f;
        if (y < 0.0f) y = 0.0f;
        if (y > 600.0f) y = 600.0f;

        AddTrailPoint(&trail, x, y);
        DrawTrail(win, &trail);

        EndFrame(win);
    }

    return 0;
}