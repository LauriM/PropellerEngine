::@ECHO OFF

:: ######################
:: # Init stuff and vars
:: ######################

::TODO: Ask for version number and inject to .zip files

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86

set host=%COMPUTERNAME%

set starttime=%TIME%
set startcsec=%STARTTIME:~9,2%
set startsecs=%STARTTIME:~6,2%
set startmins=%STARTTIME:~3,2%
set starthour=%STARTTIME:~0,2%
set /a starttime=(%starthour%*60*60*100)+(%startmins%*60*100)+(%startsecs%*100)+(%startcsec%)

:: #####################
:: # Cleanup old build
:: #####################

rmdir /Q /S "./propellerengine_full/"
rmdir /Q /S "./propellerengine_patch/"
mkdir "propellerengine_full/"
mkdir "propellerengine_patch/"

del propellerengine_full.zip
del propellerengine_patch.zip


:: ###########################################
:: # Build the engine with all configurations
:: ###########################################

cd windows

msbuild /t:Clean PropellerEngine.sln /property:Configuration=GameDebug;Platform=Win32
msbuild /t:Clean PropellerEngine.sln /property:Configuration=GameDevelopment;Platform=Win32
msbuild /t:Clean PropellerEngine.sln /property:Configuration=GameRelease;Platform=Win32
msbuild /t:Clean PropellerEngine.sln /property:Configuration=GameDebug;Platform=Tegra-Android
msbuild /t:Clean PropellerEngine.sln /property:Configuration=GameRelease;Platform=Tegra-Android

msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameRelease;Platform=Tegra-Android
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameDebug;Platform=Tegra-Android
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameDebug;Platform=Win32
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameDevelopment;Platform=Win32
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameRelease;Platform=Win32
msbuild /t:Rebuild PropellerEngine.sln /property:Configuration=GameDebugGL2;Platform=Win32

:: Move back to the project root from build directory
cd ..

:: #############################################
:: # Build the shaders and crosscompile to glsl
:: #############################################

call "./compileShaders.bat"

:: ###############################################################
:: # Copy relevant files into the propellerengine_full directory
:: ###############################################################

:: Copy all relevant files
xcopy /E /Y ".\bin" ".\propellerengine_full\bin\"
xcopy /E /Y ".\data" ".\propellerengine_full\data\"
xcopy /E /Y ".\enginedata" ".\propellerengine_full\enginedata\"
xcopy /E /Y ".\other" ".\propellerengine_full\other\"
xcopy /E /Y ".\src" ".\propellerengine_full\src\"
xcopy /E /Y ".\thirdparty" ".\propellerengine_full\thirdparty\"
xcopy /E /Y ".\src" ".\propellerengine_full\src\"
xcopy /E /Y ".\windows\*.props" ".\propellerengine_full\windows\"
xcopy /E /Y ".\windows\PropellerGame.sln" ".\propellerengine_full\windows\"
xcopy /E /Y ".\windows\Shaders" ".\propellerengine_full\windows\Shaders\"
xcopy /E /Y ".\windows\EngineReference" ".\propellerengine_full\windows\EngineReference\"
xcopy /E /Y ".\windows\Game" ".\propellerengine_full\windows\Game\"
xcopy /E /Y ".\windows\Standalone" ".\propellerengine_full\windows\Standalone\"
xcopy /E /Y ".\windows\build\GameDebug\*.lib" ".\propellerengine_full\windows\build\GameDebug\*.lib"
xcopy /E /Y ".\windows\build\GameDevelopment\*.lib" ".\propellerengine_full\windows\build\GameDevelopment\*.lib"
xcopy /E /Y ".\windows\build\GameRelease\*.lib" ".\propellerengine_full\windows\build\GameRelease\*.lib"
xcopy /E /Y ".\windows\build\GameDebug\*.a" ".\propellerengine_full\windows\build\GameDebugGL2\*.a"
xcopy /E /Y ".\windows\build\GameDebug\*.a" ".\propellerengine_full\windows\build\GameDebug\*.a"
xcopy /E /Y ".\windows\build\GameDebug\*.a" ".\propellerengine_full\windows\build\GameDebugGL2\*.a"
xcopy /E /Y ".\windows\build\GameDevelopment\*.a" ".\propellerengine_full\windows\build\GameDevelopment\*.a"
xcopy /E /Y ".\windows\build\GameRelease\*.a" ".\propellerengine_full\windows\build\GameRelease\*.a"

copy "LICENSE.txt" ".\propellerengine_full\"
copy "README.md" ".\propellerengine_full\"
copy ".gitignore" ".\propellerengine_full\"
:: TODO consider dropping gitignore for patch

rmdir /Q /S propellerengine_full/src/html/
rmdir /Q /S propellerengine_full/src/unittesting/
rmdir /Q /S propellerengine_full/src/editorbackend/

rmdir /Q /S propellerengine_full/thirdparty/orbit_toolkit/

del /S .\propellerengine_full\*.cpp
del /S .\propellerengine_full\*.c

:: Copy these after the .c/.cpp delete, these source files are for the user
xcopy /E /Y ".\src\game" ".\propellerengine_full\src\game"
xcopy /E /Y ".\src\standalone" ".\propellerengine_full\src\standalone"
xcopy /E /Y ".\doc" ".\propellerengine_full\doc\"

:: Copy androidnative and cleanup
xcopy /E /Y ".\android" ".\propellerengine_full\android\"
rmdir /Q /S propellerengine_full/android/NativePropeller/Tegra-Android/

:: ##################################
:: # Inject timestamp to the release
:: ##################################

for /f "delims=" %%a in ('wmic OS Get localdatetime  ^| find "."') do set dt=%%a
set datestamp=%dt:~0,8%
set timestamp=%dt:~8,6%
set YYYY=%dt:~0,4%
set MM=%dt:~4,2%
set DD=%dt:~6,2%
set HH=%dt:~8,2%
set Min=%dt:~10,2%
set Sec=%dt:~12,2%

set stamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%
echo PropellerEngine build on %host% at %stamp% > .\propellerengine_full\timestamp.txt

:: ############################################
:: # Build patch zip. (remove user data files)
:: # First make a copy of the full folder
:: ############################################

xcopy /E /Y ".\propellerengine_full" ".\propellerengine_patch"

rmdir /Q /S "propellerengine_patch/data/"
rmdir /Q /S "propellerengine_patch/bin/"
rmdir /Q /S "propellerengine_patch/src/game/"
rmdir /Q /S "propellerengine_patch/windows/Game/"

:: ####################
:: # ZIP THE FILES
:: # (Only if 7-zip exists)
:: ####################

"%PROGRAMFILES%\7-Zip\7z.exe" a -tzip propellerengine_full.zip .\propellerengine_full\ -r
"%PROGRAMFILES%\7-Zip\7z.exe" a -tzip propellerengine_patch.zip .\propellerengine_patch\ -r

set endtime=%time%

echo ################################
echo # PropellerEngine release done #
echo ################################

set endtime=%time%
set endcsec=%endTIME:~9,2%
set endsecs=%endTIME:~6,2%
set endmins=%endTIME:~3,2%
set endhour=%endTIME:~0,2%
if %endhour% LSS %starthour% set /a endhour+=24
set /a endtime=(%endhour%*60*60*100)+(%endmins%*60*100)+(%endsecs%*100)+(%endcsec%)

set /a timetaken= ( %endtime% - %starttime% )
set /a timetakens= %timetaken% / 100
set timetaken=%timetakens%.%timetaken:~-2%

echo Build took: %timetaken% sec.

pause
