#pragma once

#include "stdafx.h"

// Generic Function pointers for calls to UODemoDLL
typedef void (*FUNCPTR_Void)();
typedef int (_cdecl *FUNCPTR)(...);

// Function pointer for setting a local "event handler" to call in the UODemoDll
typedef void (*FUNCPTR_SetHandler)(void*);
