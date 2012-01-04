
// -=-=-=-=-=-=-=-=-=-=
// Event Invokers
// -=-=-=-=-=-=-=-=-=-=

// Received packet handler
void (*my_OnPacket)(void *Socket, unsigned char PacketID, unsigned int PacketSize,int IsPacketDynamicSized)= NULL;

// Invalid packet handler
void (*my_OnHandleOutsideRangePacket)(void *Socket)= NULL;

// Sending packet handler
void (*my_OnPacketSending)(void *Socket, unsigned char **Data, unsigned int *DataLen)= NULL;

// -=-=-=-=-=-=-=-=-=-=
// Event Initialization
// -=-=-=-=-=-=-=-=-=-=

// Export for initialization of external packet handler
void _declspec(dllexport) setHandler_packets(void* onpacketFunc)
{
	my_OnPacket=onpacketFunc;
}

// Export for initialization of external packet handler
void _declspec(dllexport) setHandler_onhandleoutsiderangepacket(void* onhandleoutsiderangepacketFunc)
{
	my_OnHandleOutsideRangePacket=onhandleoutsiderangepacketFunc;
}

// Export for initialization of external OnPacketSending packet handler
void _declspec(dllexport) setHandler_onpacketsending(void* onpacketsendingFunc)
{
	my_OnPacketSending=onpacketsendingFunc;
}
