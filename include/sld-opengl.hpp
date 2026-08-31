#ifndef SLD_OPENGL_HPP
#define SLD_OPENGL_HPP

#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <assert.h>
#include <sld.hpp>

#ifdef SLD_OPENGL_STATIC
#   define SLD_OPENGL_API
#elif defined(SLD_DLL_EXPORT)
#   define SLD_OPENGL_API __declspec(dllexport)
#else
#   define SLD_OPENGL_API __declspec(dllimport)
#endif

namespace sld {

    //--------------------------------------------------------------------
    // PRIMITIVE TYPES
    //--------------------------------------------------------------------

    using gl_value            = GLint;
    using gl_object           = GLuint;
    using gl_type             = GLenum;
    using gl_id               = GLuint;
    using gl_error            = gl_value;
    using gl_uniform          = gl_value;
    using gl_status           = gl_value; 
    using gl_program          = gl_object;
    using gl_shader           = gl_object;
    using gl_vertex           = gl_object; 
    using gl_attribute        = gl_object; 
    using gl_buffer           = gl_object;
    using gl_buffer_type      = gl_type;
    using gl_buffer_useage    = gl_type;
    using gl_platform_handle  = HGLRC;

    //--------------------------------------------------------------------
    // STRUCTURED TYPES
    //--------------------------------------------------------------------

    struct gl_viewport {
        u32 pos_x;
        u32 pos_y;
        u32 width;
        u32 height;
    };
    struct gl_context {
        gl_platform_handle platform_handle;
        gl_error           error;
        gl_program         program;
        gl_vertex          vertex;
        gl_buffer          vertex_buffer;
        gl_buffer          element_buffer;
        gl_viewport        viewport;
        color_rgba_f32     clear_color;
    };
    
    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr gl_error   GL_ERROR_SUCCESS   = 0;
    constexpr gl_id      GL_ID_INVALID      = 0;
    constexpr f32        GL_NORMAL_FACTOR   = (1.0f / 255.0f);
    constexpr gl_uniform GL_UNIFORM_INVALID = -1;

    //--------------------------------------------------------------------
    // CONTEXT
    //--------------------------------------------------------------------

    SLD_OPENGL_API void gl_context_init_win32              (gl_context* ctx, const HWND window_handle);
    SLD_OPENGL_API void gl_context_clear_errors            (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_depth_buffering  (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_smoothing        (gl_context* ctx);
    SLD_OPENGL_API void gl_context_clear_viewport          (gl_context* ctx);
    SLD_OPENGL_API void gl_context_update_viewport         (gl_context* ctx, const u32 pos_x, const u32 pos_y, const u32 width, const u32 height);
    SLD_OPENGL_API bool gl_context_draw_vertices           (gl_context* ctx, const u32 count);
    SLD_OPENGL_API bool gl_context_draw_elements           (gl_context* ctx, const u32 count);
    SLD_OPENGL_API bool gl_context_draw_elements_instanced (gl_context* ctx, const u32 count);
    SLD_OPENGL_API bool gl_context_draw_lines              (gl_context* ctx, const u32 count);
    SLD_OPENGL_API void gl_context_set_clear_color_rgba    (gl_context* ctx, color_rgba_u32& color);
    SLD_OPENGL_API void gl_context_set_clear_color_hex     (gl_context* ctx, color_rgba_f32& color);
    SLD_OPENGL_API bool gl_context_set_shader_program      (gl_context* ctx, const gl_program program);
    SLD_OPENGL_API bool gl_context_set_vertex_object       (gl_context* ctx, const gl_vertex  vertex);
    SLD_OPENGL_API bool gl_context_set_buffer_vertex       (gl_context* ctx, const gl_buffer  buffer);
    SLD_OPENGL_API bool gl_context_set_buffer_element      (gl_context* ctx, const gl_buffer  buffer);

    //--------------------------------------------------------------------
    // SHADERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_shader  gl_shader_stage_create_vertex       (gl_context* ctx);
    SLD_OPENGL_API gl_shader  gl_shader_stage_create_fragment     (gl_context* ctx);
    SLD_OPENGL_API gl_shader  gl_shader_stage_create_geometry     (gl_context* ctx);
    SLD_OPENGL_API gl_shader  gl_shader_stage_create_compute      (gl_context* ctx);
    SLD_OPENGL_API gl_shader  gl_shader_stage_create_tess_ctrl    (gl_context* ctx);
    SLD_OPENGL_API gl_shader  gl_shader_stage_create_tess_eval    (gl_context* ctx);
    SLD_OPENGL_API void       gl_shader_stage_destroy             (gl_context* ctx, const gl_shader shader);
    SLD_OPENGL_API bool       gl_shader_stage_compile_from_source (gl_context* ctx, const gl_shader shader, const cchar* src_ptr, const u32 src_size);
    SLD_OPENGL_API gl_program gl_shader_program_create            (gl_context* ctx);
    SLD_OPENGL_API void       gl_shader_program_destroy           (gl_context* ctx, const gl_program program);
    SLD_OPENGL_API bool       gl_shader_program_attach_stage      (gl_context* ctx, const gl_program program, const gl_shader shader);
    SLD_OPENGL_API bool       gl_shader_program_link              (gl_context* ctx, const gl_program program);

    //--------------------------------------------------------------------
    // VERTICES
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_vertex gl_vertex_create                  (gl_context* ctx);
    SLD_OPENGL_API bool      gl_vertex_destroy                 (gl_context* ctx, const gl_vertex vertex);
    SLD_OPENGL_API bool      gl_vertex_divisor                 (gl_context* ctx, const gl_vertex vertex, const u32 index, const u32 divisor);
    SLD_OPENGL_API bool      gl_vertex_add_s8x1                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s8x2                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s8x3                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s8x4                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u8x1                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u8x2                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u8x3                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u8x4                (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s16x1               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s16x2               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s16x3               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s16x4               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u16x1               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u16x2               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u16x3               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u16x4               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s32x1               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s32x2               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s32x3               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_s32x4               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u32x1               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u32x2               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u32x3               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_u32x4               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_f32x1               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_f32x2               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_f32x3               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_f32x4               (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_normalized_bytes_x1 (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_normalized_bytes_x2 (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_normalized_bytes_x3 (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    SLD_OPENGL_API bool      gl_vertex_add_normalized_bytes_x4 (gl_context* ctx, const gl_vertex vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset);
    
    //--------------------------------------------------------------------
    // BUFFERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_buffer gl_buffer_create              (gl_context* ctx);
    SLD_OPENGL_API bool      gl_buffer_destroy             (gl_context* ctx, const gl_buffer buffer);
    SLD_OPENGL_API bool      gl_buffer_set_vertex_data     (gl_context* ctx, const gl_buffer buffer, const byte* data_ptr, const u32 data_size);
    SLD_OPENGL_API bool      gl_buffer_set_element_data    (gl_context* ctx, const gl_buffer buffer, const byte* data_ptr, const u32 data_size);
    SLD_OPENGL_API bool      gl_buffer_update_vertex_data  (gl_context* ctx, const gl_buffer buffer, const byte* data_ptr, const u32 data_size);
    SLD_OPENGL_API bool      gl_buffer_update_element_data (gl_context* ctx, const gl_buffer buffer, const byte* data_ptr, const u32 data_size);

    //--------------------------------------------------------------------
    // UNIFORMS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_uniform gl_uniform_get_location (gl_context* ctx, const gl_program prog,    const cchar* uniform_cstr);
    SLD_OPENGL_API bool       gl_uniform_set_u32x1    (gl_context* ctx, const gl_uniform uniform, const f32  val);
    SLD_OPENGL_API bool       gl_uniform_set_u32x2    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_u32x3    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_u32x4    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_s32x1    (gl_context* ctx, const gl_uniform uniform, const f32  val);
    SLD_OPENGL_API bool       gl_uniform_set_s32x2    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_s32x3    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_s32x4    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_f32x1    (gl_context* ctx, const gl_uniform uniform, const f32  val);
    SLD_OPENGL_API bool       gl_uniform_set_f32x2    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_f32x3    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_f32x4    (gl_context* ctx, const gl_uniform uniform, const f32* val);
    SLD_OPENGL_API bool       gl_uniform_set_mat4     (gl_context* ctx, const gl_uniform uniform, const f32* val);
};

#endif //SLD_OPENGL_HPP
