#pragma once

#include "sld-opengl.hpp"

namespace sld {

    SLD_OPENGL_API void
    gl_context_init_win32(
        gl_context* ctx,
        const HWND  window_handle) {

        assert(ctx != NULL && window_handle != NULL);

        // reset the context
        zero_memory((void*)ctx, sizeof(gl_context));

        // get the device context
        const HDC  device_context = GetDC(window_handle);

        //set our preferred format descriptor
        PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
        preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
        preferred_format_descriptor.nVersion   = 1;
        preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
        preferred_format_descriptor.cColorBits = 32;
        
        // set the pixel format
        const s32   chosen_pixel_format   = ChoosePixelFormat (device_context, &preferred_format_descriptor);
        const bool  is_pixel_format_set   = SetPixelFormat    (device_context, chosen_pixel_format, &preferred_format_descriptor);
        
        // create a dummy context so we can initialize glew
        const HGLRC gl_context_dummy            = wglCreateContext (device_context);
        const bool  gl_context_dummy_is_current = wglMakeCurrent   (device_context, gl_context_dummy); 

        // initialize glew
        glewExperimental = true;
        const bool glew_is_init = (glewInit() == GLEW_OK); 
        assert(
            gl_context_dummy != NULL    &&
            gl_context_dummy_is_current &&
            glew_is_init
        );

        // create actual context
        const s32   wgl_attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        const HGLRC gl_context_actual            = wglCreateContextAttribsARB (device_context, NULL, wgl_attribs);
        const bool  gl_context_actual_is_current = wglMakeCurrent             (device_context, gl_context_actual);
        const bool  gl_context_dummy_is_deleted  = wglDeleteContext           (gl_context_dummy);
        assert(
            gl_context_actual != NULL    &&
            gl_context_actual_is_current &&
            gl_context_dummy_is_deleted
        );

        ctx->platform_handle = gl_context_actual;
    }

    SLD_OPENGL_API void
    gl_context_clear_errors(
        gl_context* ctx) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        ctx->error = GL_ERROR_SUCCESS;

        constexpr s32 MAX_ERRORS = 0x7FFFFFFF;

        for (
            u32 index = 0;
                index < MAX_ERRORS;
              ++index) {

            if (glGetError() == GL_ERROR_SUCCESS) {
                break;
            }
        }
    }

    SLD_OPENGL_API void
    gl_context_enable_depth_buffering(
        gl_context* ctx) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        gl_context_clear_errors(ctx);

	    glEnable(GL_DEPTH_TEST);
        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);

	    glDepthFunc (GL_LESS);
        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API void
    gl_context_enable_smoothing(
        gl_context* ctx) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        gl_context_clear_errors(ctx);

	    glEnable(GL_MULTISAMPLE);
        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);

	    glEnable(GL_BLEND);
        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);

	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);        
        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API void
    gl_context_clear(
        gl_context* ctx) {
        
    }

    SLD_OPENGL_API void
    gl_context_set_clear_color_rgba(
        gl_context*     ctx,
        color_rgba_u32& color) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        gl_context_clear_errors(ctx);
        
        ctx->clear_color.r = (GL_NORMAL_FACTOR * color.r);
        ctx->clear_color.g = (GL_NORMAL_FACTOR * color.g);
        ctx->clear_color.b = (GL_NORMAL_FACTOR * color.b);
        ctx->clear_color.a = (GL_NORMAL_FACTOR * color.a);
    }

    SLD_OPENGL_API void
    gl_context_set_clear_color_hex(
        gl_context*     ctx,
        color_rgba_f32& color) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        gl_context_clear_errors(ctx);
        
        ctx->clear_color.r = (color.r);
        ctx->clear_color.g = (color.g);
        ctx->clear_color.b = (color.b);
        ctx->clear_color.a = (color.a);
    }

    SLD_OPENGL_API void
    gl_context_update_viewport(
        gl_context* ctx,
        const u32   pos_x,
        const u32   pos_y,
        const u32   width,
        const u32   height) {

        assert(ctx != NULL && ctx->platform_handle != NULL);
        gl_context_clear_errors(ctx);

        ctx->viewport.pos_x  = pos_x;
        ctx->viewport.pos_y  = pos_y;
        ctx->viewport.width  = width;
        ctx->viewport.height = height;

        glViewport(
            ctx->viewport.pos_x,
            ctx->viewport.pos_y,
            ctx->viewport.width,
            ctx->viewport.height            
        );

        ctx->error = glGetError();
        assert(ctx->error == GL_ERROR_SUCCESS);
    }
};