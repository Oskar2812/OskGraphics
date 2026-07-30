#include "../include/libOskGraphics.h"
#include "../include/Internal_Window.h"
#include "../include/Internal_OpenGL.h"
#include "../include/Internal_Drawing.h"

void DestroyOskWindow(OskWindow* window) {
    DestroyWindow(window->WindowHandle);
    free(window->PixelBuffer);
    free(window);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    OskWindow* window = (OskWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            if (window != NULL) {
                DestroyOskWindow(window);
            }
            else {
                DestroyWindow(hwnd);
            }
            
            return 0;
        case WM_SIZE:
            if (window != NULL) {
                window->Width = LOWORD(lParam);
                window->Height = HIWORD(lParam);
                window->IsResized = 1;
            }
            return 0;   
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int CreateOpenGlContext(OskWindow* window) {
    HDC deviceContext = GetDC(window->WindowHandle);
    if (deviceContext == NULL) {
        return -1;
    }
    window->DeviceContext = deviceContext;

    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
    if (pixelFormat == 0) {
        return -1;
    }

    if (!SetPixelFormat(deviceContext, pixelFormat, &pfd)) {
        return -1;
    }

    HGLRC glContext = wglCreateContext(deviceContext);
    if (glContext == NULL) {
        return -1;
    }

    if (!wglMakeCurrent(deviceContext, glContext)) {
        return -1;
    }

    window->GLContext = glContext;


    if (LoadModernGLFunctions() == -1) {
        return -1;
    }

    GLuint shaderProgram = CreateShaderProgram();
    if (shaderProgram == 0) {
        return -1;
    }
    window->ShaderProgram = shaderProgram;

    return 0;
}

void AssignGPUBackend(OskWindow* window) {
    window->Backend.BeginFrame = BeginFrameGPU;
    window->Backend.EndFrame = EndFrameGPU;
    window->Backend.SetBackground = SetBackgroundGPU;
}

void AssignCPUBackend(OskWindow* window) {
    window->Backend.BeginFrame = BeginFrameCPU;
    window->Backend.EndFrame = EndFrameCPU;
    window->Backend.SetBackground = SetBackgroundCPU;
    window->Backend.DrawTriangle = DrawTriangleCPU;
    window->Backend.DrawQuad = DrawQuadCPU;
}

OskWindow* OpenWindow(uint32_t width, uint32_t height, const char* title, RenderType render) {
    const char className[] = "OskGraphicsClass";
    HINSTANCE instance = GetModuleHandle(NULL);
    if (instance == NULL) {
        return NULL;
    }

    WNDCLASS winClass = {0};
    winClass.lpfnWndProc = WindowProc;
    winClass.hInstance = instance;
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.lpszClassName = className;

    if (RegisterClass(&winClass) == 0) {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
            return NULL;
        }
    }

    HWND windowHandle = CreateWindowExA(
        0, className, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, instance, NULL);

    if (windowHandle == NULL) {
        return NULL;
    }

    OskWindow* win = malloc(sizeof(OskWindow));
    if (win == NULL) {
        DestroyWindow(windowHandle);
        return NULL;
    }

    win->Width = width;
    win->Height = height;

    win->WindowHandle = windowHandle;
    win->IsResized = 0;

    win->RenderType = render;
    switch (render) {
        case RENDER_GPU:
            if (CreateOpenGlContext(win) == -1) {
                DestroyWindow(windowHandle);
                free(win);
                return NULL;
            }

            AssignGPUBackend(win);
            break;

        case RENDER_CPU:
            win->PixelBuffer = malloc(width * height * 4);
            if (win->PixelBuffer == NULL) {
                return NULL;
            }

            AssignCPUBackend(win);
            break;
        default:
            return NULL;
    }

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)win);

    ShowWindow(windowHandle, SW_SHOW);

    return win;
}

int PollEvents() {
    int running = 1;
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            running = 0;
            continue;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return running;
}

