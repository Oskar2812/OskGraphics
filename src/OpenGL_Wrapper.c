#include "../include/Internal_OpenGL.h"

#include <stdio.h>

static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLGETSHADERIVPROC glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLGETPROGRAMIVPROC glGetProgramiv;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLBINDBUFFERPROC glBindBuffer;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLDELETESHADERPROC glDeleteShader;

int LoadModernGLFunctions() {
    glCreateShader = (PFNGLCREATESHADERPROC)(void*)wglGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)(void*)wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)(void*)wglGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)(void*)wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)(void*)wglGetProcAddress("glGetShaderInfoLog");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)(void*)wglGetProcAddress("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)(void*)wglGetProcAddress("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)(void*)wglGetProcAddress("glLinkProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)(void*)wglGetProcAddress("glGetProgramiv");
    glUseProgram = (PFNGLUSEPROGRAMPROC)(void*)wglGetProcAddress("glUseProgram");
    glGenBuffers = (PFNGLGENBUFFERSPROC)(void*)wglGetProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)(void*)wglGetProcAddress("glBindBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC)(void*)wglGetProcAddress("glBufferData");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)(void*)wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)(void*)wglGetProcAddress("glBindVertexArray");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)(void*)wglGetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)(void*)wglGetProcAddress("glEnableVertexAttribArray");
    glDeleteShader = (PFNGLDELETESHADERPROC)(void*)wglGetProcAddress("glDeleteShader");

    if (!glCreateShader || !glShaderSource || !glCompileShader || !glGetShaderiv ||
        !glGetShaderInfoLog || !glCreateProgram || !glAttachShader || !glLinkProgram ||
        !glGetProgramiv || !glUseProgram || !glGenBuffers || !glBindBuffer ||
        !glBufferData || !glGenVertexArrays || !glBindVertexArray ||
        !glVertexAttribPointer || !glEnableVertexAttribArray || !glDeleteShader) {
        return -1;   
    }

    return 0;
}

const char* GetVertexShaderSource() {
    return 
        "#version 330 core\n"
        "layout (location = 0) in vec2 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "}\n";
}

const char* GetFragmentShaderSource() {
    return 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n";
}

GLuint CompileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compile error: %s\n", infoLog);
        return 0;
    }

    return shader;
}

GLuint CreateShaderProgram() {
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, GetVertexShaderSource());
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, GetFragmentShaderSource());
    if (vertexShader == 0 || fragmentShader == 0) {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        printf("Shader program link error\n");
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;

}