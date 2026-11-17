# SLD.OpenGL
Thin OpenGL wrappers for Windows

SLD.OpenGL creates an OpenGL 3.3 core context for a Win32 window, loads the OpenGL functions with GLEW, and wraps the calls a 2D/2.5D renderer needs: shaders and programs, vertex arrays, buffers, textures, framebuffers, uniforms, and draw calls. Each wrapper is a free function that takes a `gl_context*`, does one job, checks `glGetError`, and returns whether it worked.

It's a thin layer. The objects it hands back are plain OpenGL names (`GLuint`), and the header includes `GL/glew.h`, so you can call raw OpenGL next to it when a wrapper doesn't cover something.

Every function is listed in the [API reference](docs/api.md).

## Building and Linking

It's a CMake library with the target `SLD::OpenGL`. Add it as a subdirectory and link it:

```cmake
add_subdirectory(SLD.OpenGL)
target_link_libraries(my_target PRIVATE SLD::OpenGL)
```

| Setting | Description |
| --- | --- |
| `SLD_OPENGL_STATIC` | CMake option, off by default. Off builds `SLD.OpenGL.dll`, on builds a static library. When it's on, `SLD_OPENGL_STATIC` is also defined for consumers, so the header doesn't mark the functions `dllimport`. |
| Dependencies | `SLD::Core`, `GLEW::GLEW`, and `OpenGL::GL`, linked `PUBLIC` because `sld-opengl.hpp` includes `windows.h`, `GL/glew.h`, `GL/wglew.h`, and `sld.hpp`. `user32` and `gdi32` are linked privately. |
| SLD.Core | A git submodule. It's only added if the parent project hasn't made an `SLD::Core` target already, so a parent with its own copy shares it. |
| GLEW | Comes from vcpkg (`vcpkg.json`). |
| Language | C++17. The library is built with exceptions off (`/EHs-`, `_HAS_EXCEPTIONS=0`). |
| Outputs | The DLL goes in `${CMAKE_BINARY_DIR}/bin`, and the import or static library in `${CMAKE_BINARY_DIR}/lib`. |

To build it on its own, use the `debug` or `release` presets (Ninja, `cl`, the vcpkg toolchain from `VCPKG_ROOT`, triplet `x64-windows`), or the script. The script finds vcpkg on `PATH` if `VCPKG_ROOT` isn't set, and copies `compile_commands.json` to the project root.

```powershell
.\scripts\Build-SLDOpenGL.ps1 -Config Debug
.\scripts\Build-SLDOpenGL.ps1 -Clean
```

In It Flies By, the root `CMakeLists.txt` adds `SLD.OpenGL` after `SLD.Core`, and the engine gets it through the `IFB::Core` interface target.

## Layout

| Path | Contents |
| --- | --- |
| `include/sld-opengl.hpp` | The whole public API: types, constants, and every function |
| `src/sld-opengl.cpp` | The unity build. It defines `SLD_OPENGL_DLL_EXPORT` and includes the other source files. |
| `src/context.cpp` | Context creation, render state, binding, and drawing |
| `src/shader.cpp` | Shader stages and programs |
| `src/vertex.cpp` | Vertex arrays and their attributes |
| `src/buffer.cpp` | Vertex and element buffers |
| `src/texture.cpp` | 2D and layered (2D array) RGBA8 textures |
| `src/framebuffer.cpp` | Framebuffers and depth/stencil renderbuffers |
| `src/uniform.cpp` | Uniform locations and setters |
| `scripts/Build-SLDOpenGL.ps1` | Builds or cleans the project on its own |

Only `sld-opengl.cpp` is compiled. The other `.cpp` files are marked `HEADER_FILE_ONLY` in `CMakeLists.txt`. A new source file has to be added to `target_sources`, to the `HEADER_FILE_ONLY` list, and as an `#include` in `sld-opengl.cpp`.

## Conventions

- Everything is in the `sld` namespace, and every function is named `gl_<area>_<action>`.
- Every function takes the `gl_context*` first.
- Objects are OpenGL names behind typedefs (`gl_program`, `gl_vertex`, `gl_buffer`, `gl_texture`, …). `GL_ID_INVALID` (0) means no object.
- A **vertex** (`gl_vertex`) is a vertex array object (VAO), not a single vertex.
- Functions that can fail return `bool`. `create` functions return the new object, or `GL_ID_INVALID`.

## Usage

These come from how IFB.Engine uses the library.

### Creating the context

The platform layer creates the context once the window exists (`IFB.Engine/src/win32/win32-graphics.cpp`):

```cpp
color_rgba_u32 clear_color = 0x212121FF;

gl_context_init_win32             (ctx, window.handle);
gl_context_enable_depth_buffering (ctx);
gl_context_enable_smoothing       (ctx);
gl_context_set_clear_color_rgba   (ctx, clear_color);
gl_context_update_viewport        (ctx, 0, 0, viewport_width, viewport_height);
```

Each frame starts with `gl_context_clear_viewport` and ends with `SwapBuffers` on the window's device context. Swapping isn't part of this library.

### Building a shader

From the quad renderer (`renderer-quad.cpp`). The stages can be destroyed once the program is linked.

```cpp
program             = gl_shader_program_create        (gl);
const gl_shader vtx = gl_shader_stage_create_vertex   (gl);
const gl_shader frg = gl_shader_stage_create_fragment (gl);

bool gl_ok = true;
gl_ok &= gl_shader_stage_compile_from_source (gl, vtx, src_vertex.data,   src_vertex.size);
gl_ok &= gl_shader_stage_compile_from_source (gl, frg, src_fragment.data, src_fragment.size);
gl_ok &= gl_shader_program_attach_stage      (gl, program, vtx);
gl_ok &= gl_shader_program_attach_stage      (gl, program, frg);
gl_ok &= gl_shader_program_link              (gl, program);
gl_shader_stage_destroy                      (gl, vtx);
gl_shader_stage_destroy                      (gl, frg);
assert(gl_ok);

unif_mat4_model = gl_uniform_get_location(gl, program, "u_mat4_model");
```

If a compile or link fails, `gl_shader_stage_get_info_log` or `gl_shader_program_get_info_log` copies the driver's message into your buffer.

### Describing vertices

Bind the vertex array, then the buffers, then upload and add the attributes. The order matters (see [Binding order](#binding-order)). The quad vertex is a `vec3` position, a `color_rgba_f32`, a `vec2` UV, and an `f32`:

```cpp
gl_ok &= gl_context_set_vertex_object  (gl, vertex);
gl_ok &= gl_context_set_buffer_vertex  (gl, buf_vertex);
gl_ok &= gl_context_set_buffer_element (gl, buf_element);
gl_ok &= gl_buffer_set_vertex_data     (gl, buf_vertex,  vtx_data,   vtx_capacity);
gl_ok &= gl_buffer_set_element_data    (gl, buf_element, elmnt_data, elmnt_capacity);
gl_ok &= gl_vertex_add_f32x3           (gl, vertex, vertex_size, 0, 0);
gl_ok &= gl_vertex_add_f32x4           (gl, vertex, vertex_size, 1, sizeof(vec3));
gl_ok &= gl_vertex_add_f32x2           (gl, vertex, vertex_size, 2, sizeof(vec3) + sizeof(color_rgba_f32));
gl_ok &= gl_vertex_add_f32x1           (gl, vertex, vertex_size, 3, sizeof(vec3) + sizeof(color_rgba_f32) + sizeof(vec2));
```

The engine sizes its OpenGL buffers to the CPU buffer's capacity at startup, then uploads just the used part each frame with `gl_buffer_update_vertex_data`.

For per-instance data, the tile renderer (`renderer-tile.cpp`) gives the attributes a divisor of 1:

```cpp
gl_ok &= gl_vertex_add_u32x1 (gl, vertex, stride, 0, 0);
gl_ok &= gl_vertex_add_f32x4 (gl, vertex, stride, 1, sizeof(u32));
gl_ok &= gl_vertex_divisor   (gl, vertex, 0, 1);
gl_ok &= gl_vertex_divisor   (gl, vertex, 1, 1);
```

### Drawing

Set the program before setting its uniforms, and bind everything the draw needs:

```cpp
gl_context_set_shader_program (gl, program);
gl_context_set_vertex_object  (gl, vertex);
gl_context_set_buffer_vertex  (gl, buf_vertex);
gl_context_set_buffer_element (gl, buf_element);
gl_buffer_update_vertex_data  (gl, buf_vertex, vtx_data, vtx_size);
gl_uniform_set_mat4           (gl, unif_mat4_model,     model.m);
gl_uniform_set_mat4           (gl, unif_mat4_view_proj, view_proj.m);
gl_context_draw_elements      (gl, element_count);
```

### Drawing to a texture

The map view and the particle view draw into a texture, with a depth/stencil renderbuffer (`renderer-map-view.cpp`):

```cpp
// once
gl_ok &= gl_texture_set_storage_rgba8              (gl, texture,       width, height);
gl_ok &= gl_renderbuffer_set_storage_depth_stencil (gl, depth_stencil, width, height);
gl_ok &= gl_framebuffer_attach_color_texture       (gl, framebuffer, texture);
gl_ok &= gl_framebuffer_attach_depth_stencil       (gl, framebuffer, depth_stencil);
gl_ok &= gl_framebuffer_is_complete                (gl, framebuffer);

// each frame
color_rgba_f32 window_clear_color = gl->clear_color;
gl_context_set_framebuffer     (gl, framebuffer);
gl_context_update_viewport     (gl, 0, 0, width, height);
gl_context_set_clear_color_hex (gl, view_clear_color);
gl_context_clear_viewport      (gl);
gl_context_set_clear_color_hex (gl, window_clear_color);
// ... draw ...
gl_context_set_framebuffer_default(gl);
```

## Rules and Gotchas

### Threads and the context

- `gl_context_init_win32` makes the new context current on the thread that calls it. Every other function calls OpenGL on the calling thread, so call them on that thread, with that context current.
- Nothing is locked. A `gl_context` isn't safe to share between threads.
- `gl_context_init_win32` zeroes the `gl_context` before filling it in. It asks for a double buffered pixel format with 32 bit color, 24 bit depth, and 8 bit stencil, and an OpenGL 3.3 core profile context.
- There's no function to destroy the context.
- `gl_context_update_viewport` does nothing until the context is created, so it's safe to call from a resize before then.

### Ownership

- The library doesn't keep track of the objects it creates. Each `create` has a `destroy` that you call yourself.
- `gl_context` only remembers what's bound (the program, vertex array, vertex and element buffers, framebuffer, and the last texture and its slot), the viewport, the clear color, and the last error. Destroying an object doesn't clear it from there, except `gl_framebuffer_destroy`, which forgets the bound framebuffer if it's the one destroyed.

### Errors

- Most functions start by draining OpenGL's error queue (`gl_context_clear_errors`), then store `glGetError` in `ctx->error` and return whether it's `GL_ERROR_SUCCESS`. The [API reference](docs/api.md#error-checking) lists the ones that don't.
- A failed compile or link doesn't raise an OpenGL error, so `ctx->error` is set to `GL_ERROR_COMPILE` or `GL_ERROR_LINK` instead, unless the queue had a real error.
- Bad arguments (a null context, `GL_ID_INVALID` objects, zero sizes and counts) are caught with `assert`, so they're only checked in debug builds.
- The uniform setters assert that the location isn't negative. `gl_uniform_get_location` returns `GL_UNIFORM_INVALID` (-1) for a name the program doesn't have, including a uniform the shader compiler removed because it isn't used.
- When a `gl_context_set_*` call fails to bind its object, the matching binding in the context is set to `GL_ID_INVALID`.

### Binding order

- `gl_vertex_add_*` reads the attribute from whatever is bound as the vertex buffer when it's called, so call `gl_context_set_buffer_vertex` first.
- The element buffer binding is stored in the vertex array, so call `gl_context_set_vertex_object` before `gl_context_set_buffer_element` or `gl_buffer_set_element_data`.
- `gl_vertex_divisor` ignores its `vertex` argument and changes the vertex array that's bound. Bind it first.
- `gl_vertex_add_*` only binds the vertex array if `ctx->vertex` is different. If raw OpenGL changed the binding, the context doesn't know.
- `gl_buffer_set_*_data` and `gl_buffer_update_*_data` bind the buffer they're given and record it in the context.
- The texture upload functions bind the texture to the active slot and then unbind it. Call `gl_context_set_texture_active` (or the layered one) again before drawing with a texture you just uploaded to.
- The uniform setters set the uniform on the program that's in use, not one you pass, so call `gl_context_set_shader_program` first.
- `gl_context_set_framebuffer` doesn't change the viewport. Set it to the target's size, and back afterwards.

### Render state

- `gl_context_enable_depth_buffering` turns on the depth test with `glDepthFunc(GL_ALWAYS)`, so depth is written but every fragment passes and draw order decides what's on top. To really depth test, change `glDepthFunc` yourself. The engine's tile renderer switches to `GL_LESS` for the map and back to `GL_ALWAYS` after.
- `gl_context_enable_smoothing` turns on `GL_MULTISAMPLE` and alpha blending (`GL_SRC_ALPHA`, `GL_ONE_MINUS_SRC_ALPHA`). The pixel format doesn't ask for any multisample buffers.
- `gl_context_clear_viewport` clears color and depth, not stencil.
- `gl_context_set_clear_color_hex` takes a `color_rgba_f32`, not a hex value. A `color_rgba_f32` can be made from `0xRRGGBBAA`. Both clear color setters take a non-const reference, so pass a variable, not a temporary.

### Data formats

- Element buffers hold `u32` indices. All the draw functions draw triangles, except `gl_context_draw_lines`.
- `gl_buffer_set_*_data` allocates with `GL_STATIC_DRAW`. `gl_buffer_update_*_data` writes from offset 0, and the data has to fit in what was allocated.
- Textures are RGBA8 with linear filtering and clamped edges. `gl_texture_set_data_rgba8` also builds mipmaps, but the min filter is `GL_LINEAR`, so they aren't sampled.
- `gl_uniform_set_mat4` uploads 16 floats with transpose on, so it takes a row major matrix, like SLD.Math's `mat4`.
- `gl_uniform_set_f32_array` uploads an array of `vec4`s. `count` is the number of `vec4`s, and `val` holds `count * 4` floats.
- `gl_vertex_add_normalized_bytes_*` reads signed bytes and maps them to -1 to 1.
