#pragma once
// Managed Events
void InvokeOnPulse();
void InvokeOnAfterSave();
void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
bool InvokeOnHandleOutsideRangePacket(unsigned char* pSocket);
void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

// Timer Init
typedef void (_cdecl *FUNCPTR_OnPulse)();
void Initialize_timer(FUNCPTR_OnPulse func);
