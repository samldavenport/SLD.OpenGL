cmake_minimum_required(VERSION 3.21)

project(SLD.OpenGL VERSION 0.1.0 LANGUAGES CXX)

option(SLD_OPENGL_STATIC "Build SLD.OpenGL as a static library instead of a DLL" OFF)

# exceptions are disabled, so drop the /EHsc that cmake adds by default
if(MSVC)
    string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# SLD.Core is a submodule; skip it if a parent project already provides it
if(NOT TARGET SLD::Core)
    add_subdirectory(SLD.Core)
endif()

# glew comes from vcpkg (see vcpkg.json)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)

if(SLD_OPENGL_STATIC)
    add_library(sld_opengl STATIC)
else()
    add_library(sld_opengl SHARED)
endif()
add_library(SLD::OpenGL ALIAS sld_opengl)

# unity build: sld-opengl.cpp includes the other source files
target_sources(sld_opengl PRIVATE
    src/sld-opengl.cpp
    src/context.cpp
    src/shader.cpp
    src/vertex.cpp
    src/buffer.cpp
    src/uniform.cpp
    include/sld-opengl.hpp
)
set_source_files_properties(
    src/context.cpp
    src/shader.cpp
    src/vertex.cpp
    src/buffer.cpp
    src/uniform.cpp
    PROPERTIES HEADER_FILE_ONLY ON
)

target_include_directories(sld_opengl
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# sld-opengl.hpp includes sld.hpp and the glew headers, so consumers need them too
target_link_libraries(sld_opengl
    PUBLIC  SLD::Core GLEW::GLEW OpenGL::GL
    PRIVATE user32 gdi32
)

target_compile_features(sld_opengl PUBLIC cxx_std_17)
set_target_properties(sld_opengl PROPERTIES
    CXX_EXTENSIONS           OFF
    OUTPUT_NAME              "SLD.OpenGL"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(SLD_OPENGL_STATIC)
    target_compile_definitions(sld_opengl PUBLIC SLD_OPENGL_STATIC)
endif()

target_compile_definitions(sld_opengl PRIVATE _HAS_EXCEPTIONS=0)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(sld_opengl PRIVATE /EHs-)
endif()
