#pragma once

#include "sld-opengl.hpp"

namespace sld {

    //--------------------------------------------------------------------
    // RENDERBUFFERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_renderbuffer
    gl_renderbuffer_create(
        gl_context* ctx) {

        assert(ctx);
        gl_context_clear_errors(ctx);

        gl_renderbuffer renderbuffer = GL_ID_INVALID;
        glGenRenderbuffers(1, &renderbuffer);

        ctx->error = (renderbuffer == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(renderbuffer);
    }

    SLD_OPENGL_API bool
    gl_renderbuffer_destroy(
        gl_context*           ctx,
        const gl_renderbuffer renderbuffer) {

        assert(ctx && renderbuffer);
        gl_context_clear_errors(ctx);

        glDeleteRenderbuffers(1, &renderbuffer);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_renderbuffer_set_storage_depth_stencil(
        gl_context*           ctx,
        const gl_renderbuffer renderbuffer,
        const u32             width,
        const u32             height) {

        assert(ctx          != NULL);
        assert(renderbuffer != GL_ID_INVALID);
        assert(width        != 0);
        assert(height       != 0);

        gl_context_clear_errors(ctx);

        glBindRenderbuffer    (GL_RENDERBUFFER, renderbuffer);
        glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer    (GL_RENDERBUFFER, GL_ID_INVALID);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    //--------------------------------------------------------------------
    // FRAMEBUFFERS
    //--------------------------------------------------------------------

    SLD_OPENGL_API gl_framebuffer
    gl_framebuffer_create(
        gl_context* ctx) {

        assert(ctx);
        gl_context_clear_errors(ctx);

        gl_framebuffer framebuffer = GL_ID_INVALID;
        glGenFramebuffers(1, &framebuffer);

        ctx->error = (framebuffer == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(framebuffer);
    }

    SLD_OPENGL_API bool
    gl_framebuffer_destroy(
        gl_context*          ctx,
        const gl_framebuffer framebuffer) {

        assert(ctx && framebuffer);
        gl_context_clear_errors(ctx);

        glDeleteFramebuffers(1, &framebuffer);

        // a deleted framebuffer that was bound reverts to the default
        if (ctx->framebuffer == framebuffer) {
            ctx->framebuffer = GL_ID_INVALID;
        }

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_framebuffer_attach_color_texture(
        gl_context*          ctx,
        const gl_framebuffer framebuffer,
        const gl_texture     texture) {

        assert(ctx         != NULL);
        assert(framebuffer != GL_ID_INVALID);
        assert(texture     != GL_ID_INVALID);

        gl_context_clear_errors(ctx);

        // attach the texture, then put back whatever the context was drawing to
        glBindFramebuffer      (GL_FRAMEBUFFER, framebuffer);
        glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
        glBindFramebuffer      (GL_FRAMEBUFFER, ctx->framebuffer);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_framebuffer_attach_depth_stencil(
        gl_context*           ctx,
        const gl_framebuffer  framebuffer,
        const gl_renderbuffer renderbuffer) {

        assert(ctx          != NULL);
        assert(framebuffer  != GL_ID_INVALID);
        assert(renderbuffer != GL_ID_INVALID);

        gl_context_clear_errors(ctx);

        // attach the renderbuffer, then put back whatever the context was drawing to
        glBindFramebuffer         (GL_FRAMEBUFFER, framebuffer);
        glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
        glBindFramebuffer         (GL_FRAMEBUFFER, ctx->framebuffer);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_framebuffer_is_complete(
        gl_context*          ctx,
        const gl_framebuffer framebuffer) {

        assert(ctx         != NULL);
        assert(framebuffer != GL_ID_INVALID);

        gl_context_clear_errors(ctx);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        const gl_type status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        glBindFramebuffer(GL_FRAMEBUFFER, ctx->framebuffer);

        ctx->error = glGetError();
        return(status == GL_FRAMEBUFFER_COMPLETE);
    }

    SLD_OPENGL_API bool
    gl_context_set_framebuffer(
        gl_context*          ctx,
        const gl_framebuffer framebuffer) {

        gl_context_clear_errors(ctx);

        assert(ctx && framebuffer != GL_ID_INVALID);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        ctx->error = glGetError();

        const bool did_set = (ctx->error == GL_ERROR_SUCCESS);
        ctx->framebuffer = did_set ? framebuffer : GL_ID_INVALID;

        return(did_set);
    }

    // draw to the window again
    SLD_OPENGL_API bool
    gl_context_set_framebuffer_default(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        assert(ctx);

        glBindFramebuffer(GL_FRAMEBUFFER, GL_ID_INVALID);
        ctx->framebuffer = GL_ID_INVALID;

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }
};
