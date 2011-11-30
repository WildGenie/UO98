#pragma once
#include "Interop.h"

// Managed Events
void OnPulse();
void OnAfterSave();
void OnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
void OnHandleOutsideRangePacket(unsigned char* pSocket);
void OnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

// Unmanaged Initialization
void InitializeEventHandlers(HMODULE dll_handle);