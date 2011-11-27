#include "Packets.h"
#include <stdio.h>

#pragma unmanaged

// Function Pointers for calls from Sharpkick
typedef int  (_cdecl *FUNCPTR_SendPack)(void*, char*, unsigned int);
typedef void (_cdecl *FUNCPTR_RemoveFirstPacket)(void*, unsigned int);
typedef void (_cdecl *FUNCPTR_ReplaceClientPacket)(void*, unsigned int, unsigned char*, unsigned int);

FUNCPTR_SendPack			        _SocketObject_SendPacket;
FUNCPTR_SendPack			        _SendPacket_PostLogin;
FUNCPTR_SendPack			        _SendPacket_PreLogin;
FUNCPTR_RemoveFirstPacket	    _RemoveFirstPacket;
FUNCPTR_ReplaceClientPacket		_ReplaceClientPacket;

#include "RegisterImportTemplate.h"
void InitPackets(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_SocketObject_SendPacket",_SocketObject_SendPacket);
	RegisterImport(dll_handle,"_RemoveFirstPacket",_RemoveFirstPacket);
	RegisterImport(dll_handle,"_ReplaceClientPacket",_ReplaceClientPacket);
}

extern "C"
{
  unsigned char localPacketBuffer[0xFFFF];

	// Packet functions
	int _declspec(dllexport) APIENTRY SocketObject_SendPacket(void* pClientSocket, char* PacketData, unsigned int DataSize)
	{
		if(_SocketObject_SendPacket)
			return _SocketObject_SendPacket(pClientSocket, PacketData, DataSize);
    else
		  return 0;
	}

	void _declspec(dllexport) APIENTRY SocketObject_RemoveFirstPacket(void* pClientSocket, unsigned int PacketLength)
	{
		if(_RemoveFirstPacket)
			_RemoveFirstPacket(pClientSocket, PacketLength);
	}

	void _declspec(dllexport) APIENTRY ReplaceServerPacketData(unsigned char **ppCurrentPacketBuffer, unsigned int *pCurrentPacketLen, unsigned char *newPacketBytes, unsigned int newPacketLength)
	{
    unsigned int currentPacketLength=*pCurrentPacketLen;

    unsigned char *originalStackAllocatedPacketBuffer=*ppCurrentPacketBuffer;
    unsigned char *bufferToUse;

		if(newPacketLength <= currentPacketLength)
			bufferToUse= originalStackAllocatedPacketBuffer;
		else
      bufferToUse= localPacketBuffer;
    
    memcpy(bufferToUse, newPacketBytes, newPacketLength);
    *pCurrentPacketLen=newPacketLength;
		*ppCurrentPacketBuffer=bufferToUse;
	}

}
