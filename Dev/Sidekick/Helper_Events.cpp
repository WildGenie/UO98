#include "CoreEvents.h"

extern "C"
{
	void _declspec(dllexport) APIENTRY Test_EventsInvoke_OnPulse()
	{
		OnPulse();
	}

	void _declspec(dllexport) APIENTRY Test_EventInvoke_OnAfterSave()
	{
		OnAfterSave();
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnPacketRecieved(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
	{
		OnPacketRecieved(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnHandleOutsideRangePacketd(unsigned char* pSocket)
	{
		OnHandleOutsideRangePacket(pSocket);
	}

  void _declspec(dllexport) APIENTRY Test_EventInvoke_OnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
	{
		OnPacketSending(pSocket, ppData, pDataLen);
	}

}
