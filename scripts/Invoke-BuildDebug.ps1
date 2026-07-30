$ProjectRoot = Split-Path -Parent $PSScriptRoot 

$SrcFile    = Join-Path $ProjectRoot "src\sld-opengl.cpp"
$Compile = @(
    "cl.exe"
    $SrcFile
    "/Fo:" + @(Join-Path $ProjectRoot "build\debug\obj\SLD.OpenGL.obj")  
    "/I"   + @(Join-Path $ProjectRoot "include")
    "/I"   + @(Join-Path $ProjectRoot "src")
    "/I"   + @(Join-Path $ProjectRoot "SLD.Core\include")
    "/I"   + @(Join-Path $ProjectRoot "vcpkg_installed\x64-windows\include")
    "/nologo"             # startup banner disabled
    "/c"                  # compile without linking
    "/MD"                 # link against multithreaded runtime library (MSVCRT.dll)
    "/Z7"                 # generate debug info
    "/EHs-"               # disable exception handling
    "/std:c++17"          # c++17 standard mode
    "/Od"                 # disable optimizations
    "/D_HAS_EXCEPTIONS=0" # disable exceptions for STL and CRT
) -join " "

$Link = @(
    "link.exe"
    "SLD.OpenGL.obj"
    "user32.lib"
    "Gdi32.lib"
    "opengl32.lib"
    "glew32.lib"
    "/LIBPATH:" + @(Join-Path $ProjectRoot "build\debug\obj")
    "/LIBPATH:" + @(Join-Path $ProjectRoot "build\debug\lib")
    "/LIBPATH:" + @(Join-Path $ProjectRoot "vcpkg_installed/x64-windows/lib")
    "/OUT:"     + @(Join-Path $ProjectRoot "build\debug\bin\SLD.OpenGL.dll")
    "/IMPLIB:"  + @(Join-Path $ProjectRoot "build\debug\lib\SLD.OpenGL.lib")
    "/nologo"
    "/SUBSYSTEM:WINDOWS"
    "/DEBUG"
    "/DLL"
) -join " "

& .\SLD.Core\scripts\Build-SLDCoreDebug.ps1

Invoke-Expression $Compile
Invoke-Expression $Link

