#pragma once

#include "sld-opengl.hpp"

namespace sld {

    SLD_OPENGL_API gl_uniform
    gl_uniform_get_location(
        gl_context* ctx,
        const gl_program prog,
        const cchar* uniform_cstr) {

        gl_context_clear_errors(ctx);
        assert(ctx && prog && uniform_cstr);

        const gl_uniform u = glGetUniformLocation(prog, uniform_cstr);
        if (u < 0) {
            ctx->error = glGetError();
        }
        return(u);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_u32x1(
        gl_context*      ctx,
        const gl_uniform uniform,
        const u32        val) {

        assert(ctx && uniform >= 0);

        gl_context_clear_errors(ctx);
        glUniform1ui(uniform, val);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_u32x2(
        gl_context*      ctx,
        const gl_uniform uniform,
        const u32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform2ui(uniform, val[0], val[1]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_u32x3(
        gl_context*      ctx,
        const gl_uniform uniform,
        const u32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform3ui(uniform, val[0], val[1], val[2]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_u32x4(
        gl_context*      ctx,
        const gl_uniform uniform,
        const u32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform4ui(uniform, val[0], val[1], val[2], val[3]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }
    
    SLD_OPENGL_API bool
    gl_uniform_set_s32x1(
        gl_context*      ctx,
        const gl_uniform uniform,
        const s32        val) {

        assert(ctx && uniform >= 0);

        gl_context_clear_errors(ctx);
        glUniform1i(uniform, val);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_s32x2(
        gl_context*      ctx,
        const gl_uniform uniform,
        const s32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform2i(uniform, val[0], val[1]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_s32x3(
        gl_context*      ctx,
        const gl_uniform uniform,
        const s32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform3i(uniform, val[0], val[1], val[2]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_s32x4(
        gl_context*      ctx,
        const gl_uniform uniform,
        const s32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform4i(uniform, val[0], val[1], val[2], val[3]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);

    }
    
    SLD_OPENGL_API bool
    gl_uniform_set_f32x1(
        gl_context*      ctx,
        const gl_uniform uniform,
        const f32        val) {

        assert(ctx && uniform >= 0);

        gl_context_clear_errors(ctx);
        glUniform1f(uniform, val);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_f32x2(
        gl_context*      ctx,
        const gl_uniform uniform,
        const f32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform2f(uniform, val[0], val[1]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_f32x3(
        gl_context*      ctx,
        const gl_uniform uniform,
        const f32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform3f(uniform, val[0], val[1], val[2]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_f32x4(
        gl_context*      ctx,
        const gl_uniform uniform,
        const f32*       val) {

        assert(ctx && uniform >= 0 && val);

        gl_context_clear_errors(ctx);
        glUniform4f(uniform, val[0], val[1], val[2], val[3]);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_uniform_set_mat4(
        gl_context*      ctx,
        const gl_uniform uniform,
        const f32*       val) {

        assert(ctx && uniform >= 0);

        gl_context_clear_errors(ctx);
        glUniformMatrix4fv(
            uniform, // uniform location
            1,       // number of matrices
            GL_TRUE, // transpose?
            val      // pointer to 16 floats
        );
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

};
