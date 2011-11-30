
// -=-=-=-=-=-=-=-=-=-=
// Event Invokers
// -=-=-=-=-=-=-=-=-=-=

// Pulse handler
void (*my_OnPulse)(void)= NULL;		

// OnAfterSave handler
void (*my_OnAfterSave)(void)= NULL;

// Received packet handler
void (*my_OnPacket)(void *Socket, unsigned char PacketID, unsigned int PacketSize,int IsPacketDynamicSized)= NULL;

// Invalid packet handler
void (*my_OnHandleOutsideRangePacket)(void *Socket)= NULL;

// Sending packet handler
void (*my_OnPacketSending)(void *Socket, unsigned char **Data, unsigned int *DataLen)= NULL;

// -=-=-=-=-=-=-=-=-=-=
// Event Initialization
// -=-=-=-=-=-=-=-=-=-=

// Export for initialization of external OnPulse handler
void _declspec(dllexport) setHandler_onpulse(void* pulseFunc)
{
	my_OnPulse=pulseFunc;
}

// Export for initialization of external OnAfterSave handler
void _declspec(dllexport) setHandler_onaftersave(void* onaftersaveFunc)
{
	my_OnAfterSave=onaftersaveFunc;
}

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
