::@ECHO OFF

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86

rmdir /Q /S "./enginedata/"

:: Build release shaders
cd windows
msbuild PropellerEngine.sln /target:Shaders:Rebuild /property:Configuration=GameRelease;Platform=Win32
cd ..

:: Lets create the glsl shaders for the

for %%f in ("./enginedata/*") do (
	.\HLSLcc.exe -lang=es100 -in="./enginedata/%%~f" -out="./enginedata/%%~nf.glsl" -reflect="./enginedata/%%~nf.reflect"
)
