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
#include "patcher.c"
#include "patches.c"
#include "classes.c"
#include "Location.c"
#include "List.c"
#include "TimeManager.h"
#include "Mobile.c"
#include "Player.c"
#include "Weapon.c"

// Exported Events
#include "events.c"

// Exported API Functions
#include "ObjectProperties.c"
#include "ObjectScripts.c"
#include "ObjectVars.c"
#include "PacketFunctions.c"
#include "World.c"
#include "Lists.c"

// Patches
#include "packets.c"	// Packet patches and handler

void Initialize_jit(void); // jit.cpp is compiled as a separate assembly as it is C++

// Unit Tests
#include "Tests.c"

// Server Configuration
void _declspec(dllexport) Configure()
{
  packetDebugLevel=Warning;	  // Level of packet diagnostic information written to console. Values: None, Error, Warning, Translation, All

  Initialize_packets();	  // Patch packet handler (packets.c)
  Initialize_jit();

	puts("UODemoDLL Initialized.");
}

BOOL WINAPI DllEntryPoint(HINSTANCE hInstance, ULONG ulReason, LPVOID pv)
{
	return TRUE;
}
