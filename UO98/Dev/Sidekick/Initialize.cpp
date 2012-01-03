#include <stdio.h>
#include <io.h>
#include <iostream>
#include "Interop.h"

#include "CoreEvents.h"

#pragma unmanaged

#include "RegisterImportTemplate.h"

#include "Packets.h"
#include "World.h"
#include "Player.h"
#include "ItemObject.h"
#include "ObjVars.h"
#include "ObjectScripts.h"

#include "TestsMain.h"

void LoadUODemoDLL();
void InitializeInterop();
void InitializeUODemoDLL();
void InitializeEventHandlers();

bool isRunUODemoDLLTestMode();
void RunTests();
void EnterNormalRuntimeMode();

void InitializeAPICommands();

HMODULE uodemodll_handle;

void Initialize()
{
	LoadUODemoDLL();
	if (uodemodll_handle)
		InitializeInterop();
	else
		printf("Error (%d): could not load UODemoDLL.DLL\n",GetLastError());
}

void Uninitialize()
{
	if(uodemodll_handle)
		FreeLibrary(uodemodll_handle);
}

void LoadUODemoDLL()
{
	uodemodll_handle = LoadLibrary("UODemoDLL.dll");
}

void InitializeInterop()
{
	InitializeUODemoDLL();

	InitializeAPICommands();

  if(isRunUODemoDLLTestMode())
    RunTests();
  else
    EnterNormalRuntimeMode();
}

bool isRunUODemoDLLTestMode()
{
  char* envTest=getenv("UODemoDLLTest");
  return envTest!=NULL;
}

void RunTests()
{
    InitializeTests(uodemodll_handle);
}

void EnterNormalRuntimeMode()
{
	InitializeEventHandlers(uodemodll_handle);
	puts("Sidekick Initialized.");
	puts("Please wait while the world loads...");
}

void InitializeUODemoDLL()
{
	FUNCPTR_Void _Configure=NULL;

	if (RegisterImport(uodemodll_handle,"_Configure",_Configure))
	{
		_Configure();
	}
	else
		throw; // exit, couldn't configure UODemoDLL.
}

void InitializeAPICommands()
{
  InitPackets(uodemodll_handle);
  InitWorld(uodemodll_handle);
  InitItemObject(uodemodll_handle);
  InitPlayer(uodemodll_handle);
  InitObjVars(uodemodll_handle);
  InitObjectScripts(uodemodll_handle);
}

