@ECHO OFF
SET REGKEYNAME=UO98
SET SERVERNAME=UO98
SET RUNDIR=rundir
SET REALDAMAGE=YES
SET MANUALLOGON=YES
SET USEACCOUNTNAME=YES
SET SAVEDYNAMIC0=NO
SET LOCALCOUNSELOR=0
rem SET UODEMODLL=%CD%\Sidekick\UO98dll\src\UO98.dll
SET UODEMODLL=%CD%\binaries\Sidekick.dll
CD binaries 
IF "%1"=="IDA" GOTO IDA
echo Parsing UOSL scripts...
uosl.exe -outspec Enhanced -outdir ..\rundir\scripts.uosl -overwrite ..\rundir\scripts.uosl\*.uosl
START "" /B UoDemo+.exe
GOTO DONE

:IDA
START "" /B "c:\Program Files\IDA\idag.exe"
GOTO DONE

:DONE
CD ..
