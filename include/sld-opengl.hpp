#ifndef SLD_OPENGL_HPP
#define SLD_OPENGL_HPP

#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglew.h>
#include <GL/wgl.h>
#include <GL/wglext.h>
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

    SLD_OPENGL_API void gl_context_init_win32             (gl_context* ctx, const HWND window_handle);
    SLD_OPENGL_API void gl_context_clear_errors           (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_depth_buffering (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_smoothing       (gl_context* ctx);
    SLD_OPENGL_API void gl_context_clear                  (gl_context* ctx);
    SLD_OPENGL_API void gl_context_set_clear_color_rgba   (gl_context* ctx, color_rgba_u32& color);
    SLD_OPENGL_API void gl_context_set_clear_color_hex    (gl_context* ctx, color_rgba_f32& color);
    SLD_OPENGL_API void gl_context_update_viewport        (gl_context* ctx, const u32 pos_x, const u32 pos_y, const u32 width, const u32 height);



};

#endif //SLD_OPENGL_HPP