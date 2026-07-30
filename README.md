# OskGraphics

A small 2D graphics library for Windows, written in C on top of Win32 and OpenGL.

This is a **personal learning project** — an excuse to get hands-on with low-level graphics
programming (software rasterization, the Win32 windowing API, and raw OpenGL) rather than a
production-ready library. Expect rough edges, missing error handling, and API changes without
notice.

## Status: incomplete

- **CPU backend (`RENDER_CPU`)** is the only backend that actually works end-to-end. It
  rasterizes shapes into a pixel buffer and blits it to the window with `StretchDIBits`.
  All shape drawing (`DrawTriangle`, `DrawQuad`, `DrawCircle`, `DrawLine`) is implemented
  here, and every example in [examples/](examples/) uses it.
- **GPU backend (`RENDER_GPU`)** is a work in progress. It can open a window with an OpenGL
  context and compile a shader program, and `BeginFrame`/`EndFrame`/`SetBackground` work, but
  none of the shape-drawing functions are wired up for it yet. Calling `DrawTriangle`,
  `DrawQuad`, `DrawCircle`, or `DrawLine` on a `RENDER_GPU` window is currently **undefined
  behaviour** — don't do it.
- Resizing, error handling, and cleanup paths are minimally tested.

## Building

Requires MinGW/gcc on Windows (uses `windows.h`, `GL/gl.h`, and links `user32`, `gdi32`,
`opengl32`).

```
make lib        # builds libOskGraphics.a
make examples   # builds the example programs into bin/
make main       # builds main.c into app.exe
make debug      # debug build (adds -g, disables optimization)
make clean      # removes build artifacts
```

## Examples

See [examples/](examples/) for small CPU-backend demos:

- `SpinningTriangle.c` — a rotating triangle
- `GrowingCircle.c` — a circle that grows over time
- `FunkyRhombus.c` — an animated quadrilateral
- `RandomWalk.c` — a random-walking point with a fading trail

Build and run one with, e.g.:

```
make examples
./bin/RandomWalk.exe
```

## API

See [include/libOskGraphics.h](include/libOskGraphics.h) for the public API and documentation
comments for each function.
