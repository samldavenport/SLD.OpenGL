# SLD.OpenGL API Reference

Everything here is declared in `include/sld-opengl.hpp`, in the `sld` namespace. Every function takes a `gl_context* ctx` first, which is left out of the tables. See the [README](../README.md) for building, usage examples, and the rules about binding order and threads.

## Types

| Type | Description |
| --- | --- |
| `gl_context` | What the library knows about the context: the `HGLRC` (`platform_handle`), the last error, the bound program, vertex array, vertex and element buffers, framebuffer, last texture and its slot, the viewport, and the clear color |
| `gl_viewport` | `pos_x`, `pos_y`, `width`, `height` |
| `gl_program`, `gl_shader` | A program and a shader stage |
| `gl_vertex` | A vertex array object (VAO) |
| `gl_buffer` | A vertex or element buffer |
| `gl_texture` | A 2D or 2D array texture |
| `gl_framebuffer`, `gl_renderbuffer` | A framebuffer and a renderbuffer |
| `gl_uniform` | A uniform location (`GLint`) |
| `gl_error` | `GL_ERROR_SUCCESS`, an OpenGL error code, `GL_ERROR_COMPILE`, or `GL_ERROR_LINK` |

The object types are all `GLuint`, so they aren't checked against each other.

## Constants

| Constant | Value | Use |
| --- | --- | --- |
| `GL_ERROR_SUCCESS` | 0 | No error |
| `GL_ERROR_COMPILE` | -1 | A shader stage failed to compile. Read `gl_shader_stage_get_info_log`. |
| `GL_ERROR_LINK` | -2 | A program failed to link. Read `gl_shader_program_get_info_log`. |
| `GL_ID_INVALID` | 0 | No object |
| `GL_UNIFORM_INVALID` | -1 | No uniform with that name |
| `GL_NORMAL_FACTOR` | 1 / 255 | Turns a byte color channel into 0 to 1 |

## Context

| Function | Description |
| --- | --- |
| `gl_context_init_win32(ctx, window_handle)` | Zeroes `ctx`, sets the window's pixel format, loads GLEW through a temporary context, then creates an OpenGL 3.3 core profile context and makes it current on this thread. Asserts if either context can't be created or made current, or GLEW doesn't load. |
| `gl_context_clear_errors(ctx)` | Empties OpenGL's error queue and sets `ctx->error` to `GL_ERROR_SUCCESS` |
| `gl_context_enable_depth_buffering(ctx)` | Turns on the depth test with `glDepthFunc(GL_ALWAYS)` |
| `gl_context_enable_smoothing(ctx)` | Turns on `GL_MULTISAMPLE` and alpha blending |
| `gl_context_update_viewport(ctx, pos_x, pos_y, width, height)` | Sets the viewport and stores it in `ctx->viewport`. Does nothing before the context is created. |
| `gl_context_clear_viewport(ctx)` | Clears the color and depth buffers of whatever is bound |
| `gl_context_set_clear_color_rgba(ctx, color)` | Sets the clear color from a `color_rgba_u32`, one byte per channel |
| `gl_context_set_clear_color_hex(ctx, color)` | Sets the clear color from a `color_rgba_f32` |
| `gl_context_get_texture_slot_count(ctx)` | `GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS` |

### Binding

Each of these binds an object and stores it in the context. On failure the stored binding becomes `GL_ID_INVALID`.

| Function | Description |
| --- | --- |
| `gl_context_set_shader_program(ctx, program)` | Uses the program. The uniform setters act on it. |
| `gl_context_set_vertex_object(ctx, vertex)` | Binds the vertex array |
| `gl_context_set_buffer_vertex(ctx, buffer)` | Binds the buffer to `GL_ARRAY_BUFFER` |
| `gl_context_set_buffer_element(ctx, buffer)` | Binds the buffer to `GL_ELEMENT_ARRAY_BUFFER`, which is stored in the bound vertex array |
| `gl_context_set_texture_active(ctx, texture, slot)` | Makes `slot` the active texture unit and binds a 2D texture to it. Asserts `slot` is below the slot count. |
| `gl_context_set_layered_texture_active(ctx, texture, slot)` | The same, for a texture made with the `rgba8_layered` functions (`GL_TEXTURE_2D_ARRAY`) |
| `gl_context_set_framebuffer(ctx, framebuffer)` | Draws to the framebuffer from now on |
| `gl_context_set_framebuffer_default(ctx)` | Draws to the window again |

### Drawing

Each draw asserts that what it needs is set in the context, binds it again, draws, and returns whether the draw raised an error.

| Function | Needs | Draws |
| --- | --- | --- |
| `gl_context_draw_elements(ctx, count)` | Program, vertex array, vertex buffer, element buffer | `count` `u32` indices as triangles |
| `gl_context_draw_elements_instanced(ctx, count_elmnt_per_inst, count_inst)` | Program, vertex array | `count_elmnt_per_inst` `u32` indices as triangles, `count_inst` times. It doesn't bind the buffers, so it uses the element buffer stored in the vertex array. |
| `gl_context_draw_vertices(ctx, count)` | Program, vertex array, vertex buffer | `count` vertices as triangles, from the first |
| `gl_context_draw_vertices_instanced(ctx, count_elmnt_per_inst, count_inst)` | Program, vertex array, vertex buffer | `count_elmnt_per_inst` vertices as triangles, `count_inst` times |
| `gl_context_draw_lines(ctx, count)` | Program, vertex array, vertex buffer | `count` vertices as lines, from the first |

## Shaders

| Function | Description |
| --- | --- |
| `gl_shader_stage_create_vertex(ctx)` | A new vertex stage |
| `gl_shader_stage_create_fragment(ctx)` | A new fragment stage |
| `gl_shader_stage_create_geometry(ctx)` | A new geometry stage |
| `gl_shader_stage_create_compute(ctx)` | A new compute stage. Compute shaders need OpenGL 4.3, and the context only asks for 3.3. |
| `gl_shader_stage_create_tess_ctrl(ctx)` | A new tessellation control stage. Needs OpenGL 4.0, like the next one. |
| `gl_shader_stage_create_tess_eval(ctx)` | A new tessellation evaluation stage |
| `gl_shader_stage_destroy(ctx, shader)` | Deletes the stage. It's safe once the program it's attached to is linked. |
| `gl_shader_stage_compile_from_source(ctx, shader, src_ptr, src_size)` | Compiles `src_size` characters of source. The source doesn't need a null terminator. |
| `gl_shader_stage_get_info_log(ctx, shader, log_ptr, log_size)` | Copies the compile log into `log_ptr` (at most `log_size` bytes, null terminated) and returns its length without the terminator |
| `gl_shader_program_create(ctx)` | A new program |
| `gl_shader_program_destroy(ctx, program)` | Deletes the program |
| `gl_shader_program_attach_stage(ctx, program, shader)` | Attaches a compiled stage |
| `gl_shader_program_link(ctx, program)` | Links the attached stages |
| `gl_shader_program_get_info_log(ctx, program, log_ptr, log_size)` | Copies the link log, like `gl_shader_stage_get_info_log` |

## Vertices

| Function | Description |
| --- | --- |
| `gl_vertex_create(ctx)` | A new vertex array |
| `gl_vertex_destroy(ctx, vertex)` | Deletes the vertex array |
| `gl_vertex_divisor(ctx, vertex, index, divisor)` | Sets attribute `index` to advance once every `divisor` instances (0 is once per vertex). It acts on the **bound** vertex array, not `vertex`. |
| `gl_vertex_add_<type>x<n>(ctx, vertex, vertex_size, attrib_index, attrib_offset)` | Describes and enables attribute `attrib_index`: `n` values of `type`, `attrib_offset` bytes into each vertex, with vertices `vertex_size` bytes apart. Binds `vertex` first if it isn't bound, and reads from the bound vertex buffer. |

The `gl_vertex_add_*` types, each with `x1` to `x4`:

| Type | OpenGL type | Shader sees |
| --- | --- | --- |
| `s8`, `u8` | `GL_BYTE`, `GL_UNSIGNED_BYTE` | Integers (`int`, `uint`, `ivecN`, `uvecN`) |
| `s16`, `u16` | `GL_SHORT`, `GL_UNSIGNED_SHORT` | Integers |
| `s32`, `u32` | `GL_INT`, `GL_UNSIGNED_INT` | Integers |
| `f32` | `GL_FLOAT` | Floats |
| `normalized_bytes` | `GL_BYTE`, normalized | Floats from -1 to 1 |

The integer types use `glVertexAttribIPointer`, so the shader input has to be an integer type. The `normalized_bytes` functions are named `gl_vertex_add_normalized_bytes_x1` to `_x4`.

## Buffers

| Function | Description |
| --- | --- |
| `gl_buffer_create(ctx)` | A new buffer |
| `gl_buffer_destroy(ctx, buffer)` | Deletes the buffer |
| `gl_buffer_set_vertex_data(ctx, buffer, data_ptr, data_size)` | Binds the buffer as the vertex buffer, then allocates `data_size` bytes and copies `data_ptr` in (`GL_STATIC_DRAW`) |
| `gl_buffer_set_element_data(ctx, buffer, data_ptr, data_size)` | The same, as the element buffer |
| `gl_buffer_update_vertex_data(ctx, buffer, data_ptr, data_size)` | Binds the buffer as the vertex buffer, then copies `data_size` bytes over the start of it. It has to fit in what was allocated. |
| `gl_buffer_update_element_data(ctx, buffer, data_ptr, data_size)` | The same, as the element buffer |

## Textures

All the textures are RGBA8, with linear filtering and edges clamped. Pixels are 4 bytes, `R`, `G`, `B`, `A`, in rows with no padding. Each `set` function binds the texture to the active slot to change it, then unbinds it.

| Function | Description |
| --- | --- |
| `gl_texture_create(ctx)` | A new texture |
| `gl_texture_destroy(ctx, texture)` | Deletes the texture |
| `gl_texture_set_storage_rgba8(ctx, texture, width, height)` | Allocates a 2D texture with no pixels, for rendering into or filling in later |
| `gl_texture_set_data_rgba8(ctx, texture, width, height, pixels_rgba)` | Allocates a 2D texture, copies the pixels in, and builds mipmaps |
| `gl_texture_set_storage_rgba8_layered(ctx, texture, width, height, layer_count)` | Allocates a 2D array texture with `layer_count` layers and no pixels |
| `gl_texture_set_data_rgba8_layered(ctx, texture, width, height, pixels_rgba, layer_count)` | Allocates a 2D array texture and copies the layers in. The layers are back to back in `pixels_rgba`, `width * height * 4` bytes each. |
| `gl_texture_set_repeat_horizontally(ctx, texture)` | Makes a **layered** texture repeat along `s` (horizontally). It only works on 2D array textures. |

## Framebuffers

| Function | Description |
| --- | --- |
| `gl_renderbuffer_create(ctx)` | A new renderbuffer |
| `gl_renderbuffer_destroy(ctx, renderbuffer)` | Deletes the renderbuffer |
| `gl_renderbuffer_set_storage_depth_stencil(ctx, renderbuffer, width, height)` | Allocates it as 24 bit depth and 8 bit stencil (`GL_DEPTH24_STENCIL8`) |
| `gl_framebuffer_create(ctx)` | A new framebuffer |
| `gl_framebuffer_destroy(ctx, framebuffer)` | Deletes the framebuffer. If it's the one the context has bound, the context goes back to the window. |
| `gl_framebuffer_attach_color_texture(ctx, framebuffer, texture)` | Attaches a 2D texture as color attachment 0 |
| `gl_framebuffer_attach_depth_stencil(ctx, framebuffer, renderbuffer)` | Attaches a renderbuffer as the depth/stencil attachment |
| `gl_framebuffer_is_complete(ctx, framebuffer)` | True if the framebuffer can be drawn to |

The attach functions and `gl_framebuffer_is_complete` bind the framebuffer they're given, then put back the one the context had bound. `gl_context_set_framebuffer` and `gl_context_set_framebuffer_default` are under [Binding](#binding).

## Uniforms

The setters set the uniform on the program in use (see `gl_context_set_shader_program`), and assert the location isn't negative.

| Function | Description |
| --- | --- |
| `gl_uniform_get_location(ctx, prog, uniform_cstr)` | The location of a uniform, or `GL_UNIFORM_INVALID` if the program doesn't have it |
| `gl_uniform_set_u32x1(ctx, uniform, val)` | One `uint`, passed by value |
| `gl_uniform_set_u32x2/x3/x4(ctx, uniform, val)` | A `uvec2`, `uvec3`, or `uvec4`, from a pointer to 2, 3, or 4 values |
| `gl_uniform_set_s32x1(ctx, uniform, val)` | One `int`, passed by value. Samplers are set with this, to their texture slot. |
| `gl_uniform_set_s32x2/x3/x4(ctx, uniform, val)` | An `ivec2`, `ivec3`, or `ivec4`, from a pointer |
| `gl_uniform_set_f32x1(ctx, uniform, val)` | One `float`, passed by value |
| `gl_uniform_set_f32x2/x3/x4(ctx, uniform, val)` | A `vec2`, `vec3`, or `vec4`, from a pointer |
| `gl_uniform_set_f32_array(ctx, uniform, val, count)` | An array of `count` `vec4`s, from `count * 4` floats |
| `gl_uniform_set_mat4(ctx, uniform, val)` | One `mat4` from 16 floats in row major order. It's transposed on the way up. |

## Error Checking

Most functions clear the error queue first, then set `ctx->error` from `glGetError` and return whether it's `GL_ERROR_SUCCESS`. These are different:

| Function | Difference |
| --- | --- |
| The `create` functions | `ctx->error` is only read from OpenGL if the new object is `GL_ID_INVALID` |
| `gl_shader_stage_compile_from_source`, `gl_shader_program_link` | Return the compile or link status. `ctx->error` is `GL_ERROR_COMPILE` or `GL_ERROR_LINK` on failure, unless OpenGL had an error. |
| `gl_framebuffer_is_complete` | Returns the framebuffer status. `ctx->error` is still set from `glGetError`. |
| `gl_uniform_get_location` | `ctx->error` is only read if the location is negative. A missing name isn't an OpenGL error, so it stays `GL_ERROR_SUCCESS`. |
| `gl_context_clear_viewport` | No asserts and no error check |
| `gl_context_set_clear_color_rgba`, `gl_context_set_clear_color_hex` | Clear the queue, but don't check `glClearColor` |
| `gl_shader_program_destroy` | Clears the queue, but doesn't check `glDeleteProgram` |
| `gl_shader_stage_get_info_log`, `gl_shader_program_get_info_log`, `gl_context_get_texture_slot_count` | Don't touch `ctx->error` |
| `gl_texture_set_repeat_horizontally` | Doesn't clear the queue first, so an earlier error can make it return false |
| `gl_context_enable_depth_buffering`, `gl_context_enable_smoothing`, `gl_context_update_viewport` | Return nothing, and assert there was no error |
