@ECHO OFF

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86

echo Publishing on win32 platform.
echo Make sure following steps are done:
echo
echo 1) Build the 'data' directory using the editor. (WIP)
echo

pause

rmdir /Q /S "output/"
mkdir "output/"

cd windows
:: Build the whole thing
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameRelease;Platform=Win32
cd ..

:: Copy exe's
copy "windows\build\GameRelease\Standalone.exe" "output/game.exe"

:: Copy media
xcopy /E /Y ".\bin" ".\output"

echo Game published to output directory!

pause
