@echo off
setlocal enabledelayedexpansion

rem Set the path to glslc.exe (adjust as needed)
set "GLSLC_PATH=C:\VulkanSDK\1.3.261.1\Bin\glslc.exe"

rem Compile all .vert and .frag files in the current directory
for %%f in (*.vert *.frag) do (
    set "shader_source=%%~nf"
    set "shader_output=!shader_source!.spv"
    "%GLSLC_PATH%" "%%~f" -o "!shader_output!"
    if errorlevel 1 (
        echo Failed to compile "%%~nxf" to SPIR-V.
        exit /b 1
    )
    echo "%%~nxf" compiled to "!shader_output!"
)

echo All shaders compiled successfully to SPIR-V.

endlocal
