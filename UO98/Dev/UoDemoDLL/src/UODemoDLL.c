// UO98: UoDemo Server
// Based on UODemoDLL & API by Batlin
// Server DLL Entry Point, Patch Initialization, and Configuration
// 03/09/2011

#define bool int
#define true -1
#define false 0

#include <windows.h>
#include <stdio.h>

#pragma warn -8057
#pragma warn -8004
#pragma warn -8069  // Non portable pointer conversions

// Internal API Files
#include "classes.c"
#include "Location.c"
#include "List.c"
#include "TimeManager.h"
#include "Mobile.c"
#include "Player.c"
#include "Weapon.c"

// Exported API Functions
#include "ObjectProperties.c"
#include "ObjectScripts.c"
#include "ObjectVars.c"
#include "World.c"
#include "Lists.c"

// Unit Tests
#include "Tests.c"

// Server Configuration
void _declspec(dllexport) Configure()
{
	puts("UODemoDLL Initialized (nothing to do anymore).");
}

BOOL WINAPI DllEntryPoint(HINSTANCE hInstance, ULONG ulReason, LPVOID pv)
{
	return TRUE;
}
