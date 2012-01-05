#pragma unmanaged

#include "CoreEvents.h"

extern "C"
{
	void _declspec(dllexport) APIENTRY Test_EventsInvoke_OnPulse()
	{
		InvokeOnPulse();
	}

	void _declspec(dllexport) APIENTRY Test_EventInvoke_OnAfterSave()
	{
		InvokeOnAfterSave();
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
	{
		InvokeOnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnHandleOutsideRangePacketd(unsigned char* pSocket)
	{
		InvokeOnHandleOutsideRangePacket(pSocket);
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
	{
		InvokeOnPacketSending(pSocket, ppData, pDataLen);
	}

}
