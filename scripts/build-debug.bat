@echo off
@echo off

pushd ..

::--------------------------------------------------------------------
:: BUILD DIRECTORIES
::--------------------------------------------------------------------

@set dir_bin=    build\debug\bin
@set dir_lib=    build\debug\lib
@set dir_obj=    build\debug\obj

IF NOT EXIST %dir_bin% mkdir %dir_bin%
IF NOT EXIST %dir_lib% mkdir %dir_lib%
IF NOT EXIST %dir_obj% mkdir %dir_obj%

::--------------------------------------------------------------------
:: BUILD COMMAND
::--------------------------------------------------------------------

@set cl_in=      src\sld-opengl.cpp
@set cl_out=     /Fo:build\debug\obj\SLD.OpenGL.obj
@set cl_include= /Iinclude /Isrc /ISLD.Core/include /Ivcpkg_installed/x64-windows/include
@set cl_flags=   /nologo /c /MD /LD /Z7 /EHs- /std:c++17 /Od /D_HAS_EXCEPTIONS=0

@set link_in=    SLD.OpenGL.obj user32.lib opengl32.lib gdi32.lib glew32.lib
@set link_out=   /OUT:build\debug\bin\SLD.OpenGL.dll /IMPLIB:build\debug\lib\SLD.OpenGL.lib
@set link_path=  /LIBPATH:build\debug\obj /LIBPATH:build\debug\lib /LIBPATH:vcpkg_installed/x64-windows/lib
@set link_flags= /nologo /SUBSYSTEM:WINDOWS /DEBUG /DLL

@set cmd_cl=     cl.exe   %cl_in%      %cl_out%    %cl_include% %cl_flags%
@set cmd_link=   link.exe %link_flags% %link_path% %link_in%    %link_out%

call %cmd_cl%
call %cmd_link%

popd
