#include "stdafx.h"
#include <stdio.h>
#include <io.h>

#include "UODemo.h"

// CLI Event invocation proxies for native code.

void InvokeOnPulse()
{
    UODemo::Core::InvokeGlobalOnPulse();
}
void InvokeOnAfterSave()
{
    UODemo::Core::InvokeGlobalOnAfterSave();
}
void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
{
    UODemo::Core_PacketEngine::InvokeGlobalOnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized!=0);
}
bool InvokeOnOutsideRangePacket(unsigned char* pSocket)
{
    return UODemo::Core_PacketEngine::InvokeGlobalOnOutsideRangePacket(pSocket);
}
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
{
    UODemo::Core_PacketEngine::InvokeGlobalOnPacketSending(pSocket, ppData, pDataLen);
}
