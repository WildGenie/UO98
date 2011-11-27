
void RemovePacket(unsigned char *Data, unsigned int PacketSize, unsigned int *pTotalDataSize);
void PrependEmptyPacket(unsigned char PacketID, unsigned char *Data, unsigned int PacketSize, unsigned int *pTotalDataSize);

// Debug Settings:
enum PACKETDEBUGLEVEL{ None, Error, Warning, Translation, All };
enum PACKETDEBUGLEVEL packetDebugLevel=None; // This should be set to desired level in Configure()

// Packet handling API functions:
int _declspec(dllexport) IsDynamicSizedPacket(unsigned char PacketID)
{
  // NOTE: the demo supports only up to 0xB5, any value above will cause invalid results!
  __asm
  {
    mov al, PacketID
    mov ecx, 0x47F320
    push eax
    call ecx
    pop ecx
  }
  return _EAX & 0x8000 ? 1 : 0;
}

unsigned int _declspec(dllexport) GetFixedPacketSize(unsigned char PacketID)
{
  // NOTE: the demo supports only up to 0xB5, any value above will cause invalid results!
  __asm
  {
    movzx eax, PacketID
    imul eax, 0x0A
    mov ax, [eax + 0x61F138]
  }
  return _EAX;
}

void _declspec(dllexport)ReplaceClientPacket(void *Socket, unsigned int CurPacketSize, unsigned char *NewPacket, unsigned int NewPacketSize)
{
  unsigned int      *pTotalDataSize = (unsigned int *) ((char *) Socket + 0x1002C);
  unsigned char     *Data           = (unsigned char *) Socket + 0x28;

  RemovePacket(Data, CurPacketSize, pTotalDataSize);

  memmove(Data + NewPacketSize, Data, *pTotalDataSize);
  *pTotalDataSize += NewPacketSize;
  memcpy(Data, NewPacket, NewPacketSize);
}

void _declspec(dllexport) RemoveFirstPacket(void *Socket, int PacketLen)
{
	unsigned int      *pTotalDataSize = (unsigned int *) ((char *) Socket + 0x1002C);
	unsigned char     *Data           = (unsigned char *) Socket + 0x28;
	unsigned char      PacketID       = *Data;

	RemovePacket(Data, PacketLen, pTotalDataSize);
	if(packetDebugLevel>=Translation)
		printf("PACKETS <- Removed packet %02X.\n", PacketID);
	//if(*pTotalDataSize <=0)	// Only need to append a packet if the buffer is now empty
	{
		PrependEmptyPacket(0xA4, Data, 149, pTotalDataSize);
		if(packetDebugLevel>=Translation)
			puts("PACKETS <- Added packet 0xA4.");
	}
}

//Outgoing Packets:

#define ptFUNC_AddPacketToSendQueue 0x47FE9C
void __cdecl (*FUNC_AddPacketToSendQueue)(void*, unsigned char*, unsigned int) = ptFUNC_AddPacketToSendQueue;
// This intercepts packets sent to the client. If the packet is desired to be replaced, you must free(Data), and allocate a new(buffer) for your packet.
void __cdecl Hook_PacketSend(void *Socket, unsigned char* Data, unsigned int DataLen)
{
	unsigned int SocketNumber = *(unsigned int *)((char *) Socket + 0x0C);

  if(packetDebugLevel>=All)
	  printf("PACKETS -> %08X: ID=%02X, PS=%3u\n",SocketNumber,*Data,DataLen);
	
  if(my_OnPacketSending)
		my_OnPacketSending(Socket, &Data, &DataLen);
	
  FUNC_AddPacketToSendQueue(Socket,Data,DataLen);
}

//Incoming packets:

// Make a copy of packet
unsigned char *ExtractPacket(unsigned char *Data, unsigned int PacketSize)
{
  unsigned char *buffer = (unsigned char *) malloc(PacketSize);
  // If unable to allocate, we will just crash on the next line.
  memcpy(buffer, Data, PacketSize);
  return buffer;
}

void RemovePacket(unsigned char *Data, unsigned int PacketSize, unsigned int *pTotalDataSize)
{
  *pTotalDataSize -= PacketSize;
  memmove(Data, Data + PacketSize, *pTotalDataSize);
}

void PrependEmptyPacket(unsigned char PacketID, unsigned char *Data, unsigned int PacketSize, unsigned int *pTotalDataSize)
{
  memmove(Data + PacketSize, Data, *pTotalDataSize);
  *pTotalDataSize += PacketSize;
  *Data = PacketID;
}

// Socket operations:
#define FUNC_SendPacket_PostLogin 0x47E0D1
int _cdecl _declspec(dllexport) SendPacket_PostLogin(void* Player, char* PacketData, unsigned int DataSize) // PacketData is copied new a new allocated buffer
{
	__asm
	{
		mov ecx, DataSize
		push ecx
		mov edx, PacketData
		push edx
		mov ecx, Player							//this
		push ecx
		mov eax, FUNC_SendPacket_PostLogin
		call eax
		add esp, 0Ch
	}
	return _EAX;
}

#define FUNC_SendPacket_PreLogin 0x47E42D
int _cdecl _declspec(dllexport) SendPacket_PreLogin(void* Socket, char* PacketData, unsigned int DataSize) // PacketData is copied new a new allocated buffer
{
	__asm
	{
		mov ecx, DataSize
		push ecx
		mov edx, PacketData
		push edx
		mov ecx, Socket							//this
		push ecx
		mov eax, FUNC_SendPacket_PreLogin
		call eax
		add esp, 0Ch
	}
	return _EAX;
}

#define FUNC_SocketObject_SendPacket 0x47F222
int _cdecl _declspec(dllexport) SocketObject_SendPacket(void* Socket, char* PacketData, unsigned int DataSize) // PacketData is copied new a new allocated buffer
{
	__asm
	{
		mov ecx, DataSize
		push ecx
		mov edx, PacketData
		push edx
		mov ecx, Socket							//this
		mov eax, FUNC_SocketObject_SendPacket
		call eax
	}
	return _EAX;
}