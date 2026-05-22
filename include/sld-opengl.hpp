#ifndef SLD_OPENGL_HPP
#define SLD_OPENGL_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>

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

    using gl_value         = GLint;
    using gl_object        = GLuint;
    using gl_type          = GLenum
    using gl_error         = gl_value;
    using gl_uniform       = gl_value;
    using gl_status        = gl_value; 
    using gl_program       = gl_object;
    using gl_shader        = gl_object;
    using gl_vertex        = gl_object; 
    using gl_attribute     = gl_object; 
    using gl_buffer        = gl_object;
    using gl_buffer_type   = gl_type;
    using gl_buffer_useage = gl_type;

    //--------------------------------------------------------------------
    // STRUCTURED TYPES
    //--------------------------------------------------------------------

    struct gl_context {
        gl_error   error;
        gl_program program;
        gl_buffer  buffer;
    };

    SLD_OPENGL_API void gl_context_init                   (gl_context* ctx);
    SLD_OPENGL_API void gl_context_clear_errors           (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_depth_buffering (gl_context* ctx);
    SLD_OPENGL_API void gl_context_enable_smoothing       (gl_context* ctx);
};

#endif //SLD_OPENGL_HPP