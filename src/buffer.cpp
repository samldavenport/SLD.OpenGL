#pragma once

#include "sld-opengl.hpp"

namespace sld {

    SLD_OPENGL_API gl_buffer
    gl_buffer_create(
        gl_context* ctx) {

        assert(ctx);
        gl_context_clear_errors(ctx);

        gl_buffer buffer;
        glGenBuffers(1, &buffer);

        ctx->error = (buffer == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(buffer);
    }

    SLD_OPENGL_API bool
    gl_buffer_destroy(
        gl_context*     ctx,
        const gl_buffer buffer) {

        assert(ctx && buffer);
        gl_context_clear_errors(ctx);

        glDeleteBuffers(1, &buffer);

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_buffer_set_vertex_data(
        gl_context*     ctx,
        const gl_buffer buffer,
        const byte*     data_ptr,
        const u32       data_size) {
        
        assert(ctx       != NULL);
        assert(buffer    != GL_ID_INVALID);
        assert(data_ptr  != NULL);
        assert(data_size != 0);

        gl_context_clear_errors(ctx);

        const bool did_set = gl_context_set_buffer_vertex(ctx, buffer);
        assert(did_set);

        glBufferData(
            GL_ARRAY_BUFFER,
            data_size,
            data_ptr,
            GL_STATIC_DRAW
        );

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }
    
    SLD_OPENGL_API bool
    gl_buffer_set_element_data(
        gl_context*     ctx,
        const gl_buffer buffer,
        const byte*     data_ptr,
        const u32       data_size) {
        
        assert(ctx       != NULL);
        assert(buffer    != GL_ID_INVALID);
        assert(data_ptr  != NULL);
        assert(data_size != 0);

        gl_context_clear_errors(ctx);

        const bool did_set = gl_context_set_buffer_element(ctx, buffer);
        assert(did_set);

        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            data_size,
            data_ptr,
            GL_STATIC_DRAW
        );

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

    
    SLD_OPENGL_API bool
    gl_buffer_update_vertex_data(
        gl_context*     ctx,
        const gl_buffer buffer,
        const byte*     data_ptr,
        const u32       data_size) {
        
        assert(ctx       != NULL);
        assert(buffer    != GL_ID_INVALID);
        assert(data_ptr  != NULL);
        assert(data_size != 0);

        gl_context_clear_errors(ctx);

        const bool did_set = gl_context_set_buffer_vertex(ctx, buffer);
        assert(did_set);

        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            data_size,
            data_ptr
        );

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

        
    SLD_OPENGL_API bool
    gl_buffer_update_element_data(
        gl_context*     ctx,
        const gl_buffer buffer,
        const byte*     data_ptr,
        const u32       data_size) {
        
        assert(ctx       != NULL);
        assert(buffer    != GL_ID_INVALID);
        assert(data_ptr  != NULL);
        assert(data_size != 0);

        gl_context_clear_errors(ctx);

        const bool did_set = gl_context_set_buffer_element(ctx, buffer);
        assert(did_set);

        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            0,
            data_size,
            data_ptr
        );

        ctx->error = glGetError();
        return(ctx->error == GL_ERROR_SUCCESS);
    }

};