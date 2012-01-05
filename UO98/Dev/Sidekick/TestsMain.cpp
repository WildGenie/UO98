#include <stdio.h>
#include <windows.h>
#include "Commands.h"
#include "TestsMain.h"

void DoShutdownServer();

void OnTestResult(bool passed, char* message, ...);
void putsColored(char* text, WORD color);

#using "Sharpkick.dll"

using namespace System;
using namespace System::Runtime::InteropServices;

void InitiateSharpkickOnlineTests()
{
    Sharpkick::Tests::OnlineTests DotNetObject;
    DotNetObject.BeginOnlineTesting();
}

void Tests_OnPulse()
{
  putsColored("Beginning UODemoDLL Tests...", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);

  DoTests();

  putsColored("Beginning Sharpkick Tests...", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
  InitiateSharpkickOnlineTests();

  putsColored("Tests Completed.", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
  putsColored("Press <ENTER> to shutdown server...", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
  char c = getc(stdin);

  DoShutdownServer();
}

void DoShutdownServer()
{
    ShutdownServer();
}

#pragma unmanaged

#include "Timer.h"

void OnTestResult(bool passed, char* message, ...)
{
  va_list fmtargs;
  char buffer[1024];

  va_start(fmtargs,message);
  #pragma warning( disable: 4996 ) // C4996: 'vsnprintf': This function or variable may be unsafe.
  vsnprintf(buffer,sizeof(buffer)-1,message,fmtargs);
  #pragma warning( default: 4996 )
  va_end(fmtargs);

  putsColored(buffer, FOREGROUND_INTENSITY | (passed ? FOREGROUND_GREEN : FOREGROUND_RED));
}

void putsColored(char* text, WORD color)
{
  HANDLE std_handle=GetStdHandle(STD_OUTPUT_HANDLE);

  _CONSOLE_SCREEN_BUFFER_INFO cInfo;
  GetConsoleScreenBufferInfo(std_handle, &cInfo);

  WORD saveColor=cInfo.wAttributes;

  SetConsoleTextAttribute(std_handle, color);
  puts(text);
  SetConsoleTextAttribute(std_handle, saveColor);
}

void InitializeTests()
{
  putsColored("Entering test mode after server load...", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
  Initialize_timer(Tests_OnPulse);
}
