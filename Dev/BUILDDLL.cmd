@ECHO OFF
SET BCCPATH=c:\borland\bcc55
SET TASMPATH=c:\borland\tasm

SET SLNDIR=%CD%
SET UODEMODIR=..
SET UODEMOEXE=StartUO98.cmd

SET PRJNAME=UODemoDLL
SET APIDIR=%CD%\%PRJNAME%\API
SET PRJDIR=%CD%\%PRJNAME%\src

IF NOT EXIST %BCCPATH%\bin\bcc32.exe GOTO BCCerror
IF NOT EXIST %TASMPATH%\bin\tasm32.exe GOTO TASMerror
IF NOT EXIST "%UODEMODIR%\" GOTO DemoError
IF NOT EXIST "%UODEMODIR%\%UODEMOEXE%" GOTO DemoError
IF "%PRJNAME%" EQU "" GOTO ParaError
IF "%PRJNAME%" EQU "api" GOTO ParaError
IF NOT EXIST %PRJDIR% GOTO DirError
GOTO :do

:BCCerror
ECHO Borland C++ 5.5 not found!
ECHO Ensure it's installed and BCCPATH inside the batch file is correctly set.
GOTO :done

:TASMerror
ECHO Borland Turbo Assembler not found!
ECHO Ensure it's installed and TASMPATH inside the batch file is correctly set.
GOTO :error

:DemoError
ECHO Ultima Online Demo not found!
ECHO Ensure UODEMODIR ^& UODEMOEXE inside the batch file is correctly set.
ECHO Ensure that you are running this build command from it's working directory
GOTO :error

:ParaError
ECHO Please provide the project name you are working on...
GOTO :error

:DirError
ECHO Unable to locate the project directory!
GOTO :error

:do
SET INC=%BCCPATH%\INCLUDE
SET LIB=%BCCPATH%\LIB

rem Add Complier/Assembler paths, if they don't exist
echo %PATH% | find /c /i ";%BCCPATH%\BIN;%TASMPATH%\BIN"
if errorlevel 1 PATH=%PATH%;%BCCPATH%\BIN;%TASMPATH%\BIN
echo %PATH% | find /c /i ";%CD%"
if errorlevel 1 PATH=%PATH%;%CD%

CD %UODEMODIR%
SET UODEMODIR=%CD%
SET UODEMOEXE=%UODEMODIR%\%UODEMOEXE%
SET UODEMODLL=%PRJDIR%\%PRJNAME%.DLL
CD %PRJDIR%

CALL b.cmd %prjname%
IF "%ERRORLEVEL%" EQU "0" GOTO lib

:error
cd %SLNDIR%
EXIT /B 1

:lib
move %PRJNAME%.dll %UODEMODIR%\Bin
move %PRJNAME%.tds %UODEMODIR%\Bin
cd %UODEMODIR%\Bin
implib -a %PRJNAME% %PRJNAME%.dll

:ok

:done
cd %SLNDIR%


