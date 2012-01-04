#pragma once
#include "Interop.h"

// Managed Events
void InvokeOnPulse();
void InvokeOnAfterSave();
void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
bool InvokeOnHandleOutsideRangePacket(unsigned char* pSocket);
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

