#include "../include/libOskGraphics.h"
#include "../include/Internal_Drawing.h"
#include "../include/Internal_Window.h"

#include <math.h>

void ResizeCpuBuffer(OskWindow* window) {
    uint8_t* newBuffer = malloc(window->Width * window->Height * 4);
    if (newBuffer == NULL) {
        return;  
    }

    free(window->PixelBuffer);
    window->PixelBuffer = newBuffer;
}

int BeginFrameCPU(OskWindow* window) {
    if (window->IsResized) {
        ResizeCpuBuffer(window);
        window->IsResized = 0;
    }

    OskColour colour = window->BackGroundColour;
    uint8_t b = (uint8_t)(colour.b * 255.0f);
    uint8_t g = (uint8_t)(colour.g * 255.0f);
    uint8_t r = (uint8_t)(colour.r * 255.0f);
    uint8_t a = (uint8_t)(colour.a * 255.0f);

    uint32_t pixelCount = window->Width * window->Height;
    for (uint32_t i = 0; i < pixelCount; i++) {
        uint32_t idx = i * 4;
        window->PixelBuffer[idx + 0] = b;
        window->PixelBuffer[idx + 1] = g;
        window->PixelBuffer[idx + 2] = r;
        window->PixelBuffer[idx + 3] = a;
    }

    return 0;
}

int EndFrameCPU(OskWindow* window) {
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = window->Width;
    bmi.bmiHeader.biHeight = -window->Height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HDC deviceContext = GetDC(window->WindowHandle);

    StretchDIBits(
        deviceContext,
        0, 0, window->Width, window->Height,
        0, 0, window->Width, window->Height,
        window->PixelBuffer,
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    ReleaseDC(window->WindowHandle, deviceContext);

    return 0;
}

int SetBackgroundCPU(OskWindow* window, OskColour colour) {
    window->BackGroundColour = colour;

    return 0;
}

float EdgeFunction(float ax, float ay, float bx, float by, float px, float py) {
    return (px - ax) * (by - ay) - (py - ay) * (bx - ax);
}

int DrawTriangleCPU(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, OskColour color) {
    uint8_t b = (uint8_t)(color.b * 255.0f);
    uint8_t g = (uint8_t)(color.g * 255.0f);
    uint8_t r = (uint8_t)(color.r * 255.0f);
    uint8_t a = (uint8_t)(color.a * 255.0f);

    uint32_t minX = (uint32_t)fminf(x0, fminf(x1, x2));
    uint32_t maxX = (uint32_t)fmaxf(x0, fmaxf(x1, x2));
    uint32_t minY = (uint32_t)fminf(y0, fminf(y1, y2));
    uint32_t maxY = (uint32_t)fmaxf(y0, fmaxf(y1, y2));

    if (maxX >= window->Width) maxX = window->Width - 1;
    if (maxY >= window->Height) maxY = window->Height - 1;

    for (uint32_t y = minY; y <= maxY; y++) {
        for (uint32_t x = minX; x <= maxX; x++) {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float w0 = EdgeFunction(x1, y1, x2, y2, px, py);
            float w1 = EdgeFunction(x2, y2, x0, y0, px, py);
            float w2 = EdgeFunction(x0, y0, x1, y1, px, py);

            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                uint32_t idx = (y * window->Width + x) * 4;
                window->PixelBuffer[idx + 0] = b;
                window->PixelBuffer[idx + 1] = g;
                window->PixelBuffer[idx + 2] = r;
                window->PixelBuffer[idx + 3] = a;
            }
        }
    }

    return 0;
}

int DrawQuadCPU(OskWindow* window, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, OskColour colour) {
    DrawTriangleCPU(window, x0, y0, x1, y1, x3, y3, colour);
    DrawTriangleCPU(window, x1, y1, x2, y2, x3, y3, colour);

    return 0;
}

int DrawCircleCPU(OskWindow* window, float cx, float cy, float radius, int segments, OskColour colour) {
    for (int i = 0; i < segments; i++) {
        float angle0 = (2.0f * OSK_PI * i) / segments;
        float angle1 = (2.0f * OSK_PI * (i + 1)) / segments;

        float x0 = cx + radius * cosf(angle0);
        float y0 = cy + radius * sinf(angle0);
        float x1 = cx + radius * cosf(angle1);
        float y1 = cy + radius * sinf(angle1);

        DrawTriangle(window, cx, cy, x0, y0, x1, y1, colour);
    }

    return 0;
}

int DrawLineCPU(OskWindow* window, float x0, float y0, float x1, float y1, float thickness, OskColour colour) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float length = sqrtf(dx * dx + dy * dy);

    if (length < 0.0001f) {
        return -1;
    } 

    float nx = -dy / length * (thickness / 2.0f);   
    float ny = dx / length * (thickness / 2.0f);

    DrawQuad(window,
        x0 + nx, y0 + ny,
        x1 + nx, y1 + ny,
        x1 - nx, y1 - ny,
        x0 - nx, y0 - ny,
        colour);

    return 0;
}