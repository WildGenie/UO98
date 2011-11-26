#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <iostream>
#include "Interop.h"

#using "Sharpkick.dll"

using namespace System;
using namespace System::Runtime::InteropServices;

// Sharpkick Dot Net Function invocations (Imports from Sharpkick), called from unmanaged code.

void OnPulse()
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPulse();
}
void OnAfterSave()
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnAfterSave();
}
void OnPacketRecieved(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPacketRecieved(pSocket, PacketID, PacketSize, IsPacketDynamicSized!=0);
}
void OnHandleOutsideRangePacket(unsigned char* pSocket)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnHandleOutsideRangePacket(pSocket);
}
void OnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPacketSending(pSocket, ppData, pDataLen);
}

#pragma unmanaged

void InitializeEventHandler(HMODULE dll_handle, char* FunctionName, void* invoke);

void InitializeEventHandlers(HMODULE dll_handle)
{
	InitializeEventHandler(dll_handle, "_setHandler_onpulse",							        &OnPulse);		
	InitializeEventHandler(dll_handle, "_setHandler_onaftersave",					        &OnAfterSave);
	InitializeEventHandler(dll_handle, "_setHandler_packets",							        &OnPacketRecieved);
	InitializeEventHandler(dll_handle, "_setHandler_onhandleoutsiderangepacket",  &OnHandleOutsideRangePacket);
	InitializeEventHandler(dll_handle, "_setHandler_onpacketsending",					    &OnPacketSending);
}

void InitializeEventHandler(HMODULE dll_handle, char* FunctionName, void* invoke)
{
	FUNCPTR_SetHandler _setHandler = (FUNCPTR_SetHandler) GetProcAddress(dll_handle, FunctionName);
	if (!_setHandler)
		printf("Error: could not find address of function %s\n", FunctionName);
	else
		_setHandler(invoke);
}
