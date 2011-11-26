CD Sidekick
call BUILDDLL.cmd
if "%ERRORLEVEL%" EQU "0" GOTO ok
cd ..
EXIT /B 1

:ok
cd ..
call StartUO98.cmd