:: @ECHO OFF

:: param 1 is path to the directory with binaries
:: param 2 is dll filename identifer

:: VS CALL
:: "$(SolutionDir)dllcopy.bat" "$(SolutionDir)build\$(Configuration)\" "$(TargetName)"

echo DLL COPY
echo path param: %1%
echo targetname: %2%

cd %1

:: take path as param, go there, do everything there

dir | findstr Game.dll | find "Game.dll" /c

dir | findstr Game.dll | find "Game.dll" /c > dllcount.txt.temp

set /P DLLCOUNT=<dllcount.txt.temp

echo copy %2.dll

copy "%2.dll" "Game.dll.tmp%DLLCOUNT%"
