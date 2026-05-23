#pragma once

#include "sld-opengl.hpp"

namespace sld {
  
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_vertex(
        void) {

    }
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_fragment(
        void) {

    }
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_geometry(
        void) {

    }
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_compute(
        void) {

    }
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_tess_ctrl(
        void) {

    }
    SLD_OPENGL_API gl_shader
    gl_shader_stage_create_tess_eval(
        void) {

    }
    
    SLD_OPENGL_API gl_shader
    gl_shader_stage_destroy(
        const gl_shader shader) {

    }

    SLD_OPENGL_API void
    gl_shader_stage_compile_from_source(
        const gl_shader shader,
        const byte*     src_ptr,
        const u32       src_size) {

    }

    SLD_OPENGL_API gl_program
    gl_shader_program_create(
        void) {

    }
    
    SLD_OPENGL_API void
    gl_shader_program_destroy(
        const gl_program program) {

    }

    SLD_OPENGL_API void
    gl_shader_program_attach_stages(
        const gl_program program,
        const gl_shader* shader_ptr,
        const u32        shader_count) {

    }

    SLD_OPENGL_API void
    gl_shader_program_link(
        const gl_program program) {
        
    }

};