#pragma once

#include "sld-opengl.hpp"

namespace sld {
  
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_vertex(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_VERTEX_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }

    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_fragment(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_FRAGMENT_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }
    
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_geometry(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_GEOMETRY_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }
    
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_compute(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_COMPUTE_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }
    
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_tess_ctrl(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }
    
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_tess_eval(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_shader shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        
        ctx->error = (shader == GL_ID_INVALID)
            ? glGetError()
            : ERROR_SUCCESS; 

        return(shader);
    }
    
    SLD_OPENGL_API void
    gl_shader_stage_destroy(
        gl_context*     ctx,
        const gl_shader shader) {

        gl_context_clear_errors(ctx);

        glDeleteShader(shader);

        ctx->error = glGetError();
    }

    SLD_OPENGL_API bool
    gl_shader_stage_compile_from_source(
        gl_context*     ctx,
        const gl_shader shader,
        const char*     src_ptr,
        const u32       src_size) {

        gl_context_clear_errors(ctx);

        const GLchar** gl_src_src_ptr = &src_ptr;
        const GLint*   gl_src_size    = (GLint*)&src_size;
        glShaderSource(shader, 1, gl_src_src_ptr, gl_src_size);
    
        s32 success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        ctx->error = success ? GL_ERROR_SUCCESS : glGetError();

        return(success);
    }

    SLD_OPENGL_API gl_program
    gl_shader_program_create(
        gl_context* ctx) {

        gl_context_clear_errors(ctx);

        const gl_program prog = glCreateProgram();

        ctx->error = (prog == GL_ID_INVALID)
            ? glGetError()
            : GL_ERROR_SUCCESS;

        return(prog);
    }
    
    SLD_OPENGL_API void
    gl_shader_program_destroy(
        gl_context*      ctx,
        const gl_program program) {

        gl_context_clear_errors(ctx);    

        glDeleteProgram(program);
    }

    SLD_OPENGL_API bool
    gl_shader_program_attach_stages(
        gl_context*      ctx,
        const gl_program program,
        const gl_shader* shader_ptr,
        const u32        shader_count) {

        gl_context_clear_errors(ctx);    

        for (
            u32 index = 0;
                index < shader_count;
              ++index) {

            const gl_shader shader = shader_ptr[index];

            glAttachShader(program, shader);
        
            ctx->error = glGetError();
            if (ctx->error != GL_ERROR_SUCCESS) {
                return(false);
            }
        }

        return(true);
    }

    SLD_OPENGL_API bool
    gl_shader_program_link(
        gl_context*      ctx,
        const gl_program program) {
        
        gl_context_clear_errors(ctx);

        s32 success;
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        ctx->error = success ? GL_ERROR_SUCCESS : glGetError();

        return(success); 
    }

};