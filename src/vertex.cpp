#pragma once

#include "sld-opengl.hpp"

namespace sld {

    SLD_OPENGL_API gl_vertex
    gl_vertex_create(
        gl_context* ctx) {
        
        assert(ctx);       
        gl_context_clear_errors(ctx);

        gl_vertex vtx;            
        glCreateVertexArrays(1, &vtx);

        ctx->error = (vtx == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(vtx);        
    }

    SLD_OPENGL_API bool
    gl_vertex_destroy(
        gl_context*     ctx,
        const gl_vertex vertex) {
        
        assert(ctx && vertex != GL_ID_INVALID);
        gl_context_clear_errors(ctx);

        glDeleteVertexArrays(1, &vertex);

        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_vertex_add_attribute_s8(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx);

        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_BYTE,                          // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_vertex_add_attribute_u8(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx);

        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_UNSIGNED_BYTE,                 // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }
    
    SLD_OPENGL_API bool
    gl_vertex_add_attribute_s16(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx);
        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_SHORT,                         // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }
    
    SLD_OPENGL_API bool
    gl_vertex_add_attribute_u16(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx);
        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_UNSIGNED_SHORT,                // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_vertex_add_attribute_s32(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx);

        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_INT,                           // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_vertex_add_attribute_u32(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx); 
        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_UNSIGNED_INT,                  // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }

    SLD_OPENGL_API bool
    gl_vertex_add_attribute_f32(
        gl_context*      ctx,
        const gl_vertex  vertex,
        const u32        vertex_size,
        const u32        attrib_index,
        const u32        attrib_offset,
        const u32        attrib_count) {

        assert(
            ctx &&
            vertex       != GL_ID_INVALID &&
            attrib_count > 0              &&
            attrib_count < 5            
        );
        gl_context_clear_errors(ctx); 
        if (ctx->vertex != vertex) {
            gl_context_set_vertex_object(ctx, vertex);
        }
        assert(ctx->vertex == vertex);
 
        glVertexAttribPointer(
            attrib_index,                     // index
            attrib_count,                     // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized
            vertex_size,                      // stride
            (void*)((byte*)0 + attrib_offset) // pointer
        );
        ctx->error = glGetError();
        if (ctx->error != GL_ERROR_SUCCESS) {
            return(false);
        }

        glEnableVertexAttribArray(attrib_index);
        ctx->error = glGetError();

        return(ctx->error == GL_ERROR_SUCCESS);
    }
};