#pragma once
#include "Interop.h"

// Managed Events
void InvokeOnPulse();
void InvokeOnAfterSave();
void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
void InvokeOnHandleOutsideRangePacket(unsigned char* pSocket);
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

// Unmanaged Initialization
void InitializeEventHandlers(HMODULE dll_handle);