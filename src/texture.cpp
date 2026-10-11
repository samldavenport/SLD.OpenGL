#pragma once

#include "sld-opengl.hpp"

namespace sld {

    SLD_OPENGL_API gl_texture
    gl_texture_create(
        gl_context* ctx) {

        assert(ctx);
        gl_context_clear_errors(ctx);

        gl_texture texture = GL_ID_INVALID;
        glGenTextures(1, &texture);

        ctx->error = (texture == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(texture);
    }

    SLD_OPENGL_API bool
    gl_texture_destroy(
        gl_context*      ctx,
        const gl_texture texture) {

        assert(ctx && texture);
        gl_context_clear_errors(ctx);

        glDeleteTextures(1, &texture);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_texture_set_storage_rgba8(
        gl_context*      ctx,
        const gl_texture texture,
        const u32        width,
        const u32        height) {

        assert(ctx     != NULL);
        assert(texture != GL_ID_INVALID);
        assert(width   != 0);
        assert(height  != 0);

        gl_context_clear_errors(ctx);

        // allocate the pixels, there is no data to copy
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, GL_ID_INVALID);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }
};
