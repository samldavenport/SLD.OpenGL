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

    //--------------------------------------------------------------------
    // SHADERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_shader   gl_shader_stage_create_vertex             (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_fragment           (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_geometry           (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_compute            (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_tess_ctrl          (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_create_tess_eval          (void);
    SLD_OPENGL_API gl_shader   gl_shader_stage_destroy                   (const gl_shader shader);
    SLD_OPENGL_API void        gl_shader_stage_compile_from_source       (const gl_shader shader, const byte* src_ptr, const u32 src_size);
    SLD_OPENGL_API gl_program  gl_shader_program_create                  (void);
    SLD_OPENGL_API void        gl_shader_program_destroy                 (const gl_program program);
    SLD_OPENGL_API void        gl_shader_program_attach_stages           (const gl_program program, const gl_shader* shader_ptr, const u32 shader_count);
    SLD_OPENGL_API void        gl_shader_program_link                    (const gl_program program);
};

#endif //SLD_OPENGL_HPP