@echo off

@set "PATH=%PATH%;%MINGW_ROOT%"

cd .

if "%1"=="" ("C:\PROGRA~1\POLYSP~1\R2020b\bin\win64\gmake"  -f SILS_201704211.mk all) else ("C:\PROGRA~1\POLYSP~1\R2020b\bin\win64\gmake"  -f SILS_201704211.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1