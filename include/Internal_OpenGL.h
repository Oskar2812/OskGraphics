#include <windows.h>
#include <GL/gl.h>

typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82

typedef GLuint (WINAPI *PFNGLCREATESHADERPROC)(GLenum type);
typedef void (WINAPI *PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (WINAPI *PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (WINAPI *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
typedef void (WINAPI *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef GLuint (WINAPI *PFNGLCREATEPROGRAMPROC)(void);
typedef void (WINAPI *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (WINAPI *PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (WINAPI *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
typedef void (WINAPI *PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (WINAPI *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (WINAPI *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (WINAPI *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (WINAPI *PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (WINAPI *PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (WINAPI *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (WINAPI *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (WINAPI *PFNGLDELETESHADERPROC)(GLuint shader);

int LoadModernGLFunctions();

const char* GetVertexShaderSource();

const char* GetFragmentShaderSource();

GLuint CreateShaderProgram();
