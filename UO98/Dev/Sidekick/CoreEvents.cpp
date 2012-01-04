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
bool InvokeOnHandleOutsideRangePacket(unsigned char* pSocket)
{
    Sharpkick::CoreEvents DotNetObject;
    return DotNetObject.OnHandleOutsideRangePacket(pSocket);
}
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
{
    Sharpkick::CoreEvents DotNetObject;
    DotNetObject.OnPacketSending(pSocket, ppData, pDataLen);
}
