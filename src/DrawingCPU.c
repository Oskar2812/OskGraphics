#include "../include/libOskGraphics.h"
#include "../include/Internal_Drawing.h"
#include "../include/Internal_Window.h"

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
    uint8_t b = (uint8_t)(colour.b * 255.0f);
    uint8_t g = (uint8_t)(colour.g * 255.0f);
    uint8_t r = (uint8_t)(colour.r * 255.0f);
    uint8_t a = (uint8_t)(colour.a * 255.0f);

    int pixelCount = window->Width * window->Height;
    for (int i = 0; i < pixelCount; i++) {
        int idx = i * 4;
        window->PixelBuffer[idx + 0] = b;
        window->PixelBuffer[idx + 1] = g;
        window->PixelBuffer[idx + 2] = r;
        window->PixelBuffer[idx + 3] = a;
    }

    return 0;
}