#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include "Interop.h"

#using "Sharpkick.dll"

using namespace System;
using namespace System::Runtime::InteropServices;

// Sharpkick Dot Net Function invocations (Imports from Sharpkick), called from unmanaged code.

void InvokeOnPulse()
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPulse();
}
void InvokeOnAfterSave()
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnAfterSave();
}
void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized!=0);
}
void InvokeOnHandleOutsideRangePacket(unsigned char* pSocket)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnHandleOutsideRangePacket(pSocket);
}
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
{
	Sharpkick::CoreEvents DotNetObject;
	DotNetObject.OnPacketSending(pSocket, ppData, pDataLen);
}

#pragma unmanaged

void InitializeEventHandler(HMODULE dll_handle, char* FunctionName, void* invoke);

void InitializeEventHandlers(HMODULE dll_handle)
{
	InitializeEventHandler(dll_handle, "_setHandler_packets",							        &InvokeOnPacketReceived);
	InitializeEventHandler(dll_handle, "_setHandler_onhandleoutsiderangepacket",  &InvokeOnHandleOutsideRangePacket);
	InitializeEventHandler(dll_handle, "_setHandler_onpacketsending",					    &InvokeOnPacketSending);
}

void InitializeEventHandler(HMODULE dll_handle, char* FunctionName, void* invoke)
{
	FUNCPTR_SetHandler _setHandler = (FUNCPTR_SetHandler) GetProcAddress(dll_handle, FunctionName);
	if (!_setHandler)
		printf("Error: could not find address of function %s\n", FunctionName);
	else
		_setHandler(invoke);
}
