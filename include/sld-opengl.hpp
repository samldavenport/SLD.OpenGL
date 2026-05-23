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
        gl_buffer          buffer;
        gl_viewport        viewport;
        color_rgba_f32     clear_color;
    };
    
    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr gl_error GL_ERROR_SUCCESS      = 0;
    constexpr gl_id    GL_ID_INVALID         = 0;
    constexpr f32      GL_NORMAL_FACTOR      = (1.0f / 255.0f);

    //--------------------------------------------------------------------
    // CONTEXT
    //--------------------------------------------------------------------

    SLD_OPENGL_API void        gl_context_init_win32                     (gl_context* ctx, const HWND window_handle);
    SLD_OPENGL_API void        gl_context_clear_errors                   (gl_context* ctx);
    SLD_OPENGL_API void        gl_context_enable_depth_buffering         (gl_context* ctx);
    SLD_OPENGL_API void        gl_context_enable_smoothing               (gl_context* ctx);
    SLD_OPENGL_API void        gl_context_clear                          (gl_context* ctx);
    SLD_OPENGL_API void        gl_context_set_clear_color_rgba           (gl_context* ctx, color_rgba_u32& color);
    SLD_OPENGL_API void        gl_context_set_clear_color_hex            (gl_context* ctx, color_rgba_f32& color);
    SLD_OPENGL_API void        gl_context_update_viewport                (gl_context* ctx, const u32 pos_x, const u32 pos_y, const u32 width, const u32 height);
    SLD_OPENGL_API bool        gl_context_set_shader_program             (gl_context* ctx, const gl_program program);
    SLD_OPENGL_API bool        gl_context_set_vertex_object              (gl_context* ctx, const gl_vertex  vertex);

    //--------------------------------------------------------------------
    // SHADERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_shader   gl_shader_stage_create_vertex             (gl_context* ctx);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_fragment           (gl_context* ctx);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_geometry           (gl_context* ctx);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_compute            (gl_context* ctx);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_tess_ctrl          (gl_context* ctx);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_tess_eval          (gl_context* ctx);
    SLD_OPENGL_API void        gl_shader_stage_destroy                   (gl_context* ctx, const gl_shader shader);
    SLD_OPENGL_API bool        gl_shader_stage_compile_from_source       (gl_context* ctx, const gl_shader shader, const byte* src_ptr, const u32 src_size);
    SLD_OPENGL_API gl_program  gl_shader_program_create                  (gl_context* ctx);
    SLD_OPENGL_API void        gl_shader_program_destroy                 (gl_context* ctx, const gl_program program);
    SLD_OPENGL_API bool        gl_shader_program_attach_stages           (gl_context* ctx, const gl_program program, const gl_shader* shader_ptr, const u32 shader_count);
    SLD_OPENGL_API bool        gl_shader_program_link                    (gl_context* ctx, const gl_program program);

    //--------------------------------------------------------------------
    // VERTICES
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_vertex  gl_vertex_object_create            (gl_context* ctx);
    SLD_OPENGL_API void       gl_vertex_object_destroy           (gl_context* ctx, const gl_vertex);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_s8  (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_u8  (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_s16 (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_u16 (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_s32 (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_u32 (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
    SLD_OPENGL_API void       gl_vertex_object_add_attribute_f32 (gl_context* ctx, const gl_vertex, const u32 vertex_size, const u32 attrib_index, const u32 attrib_offset, const u32 attrib_count);
};

#endif //SLD_OPENGL_HPP