using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick.Network
{
    unsafe interface IPackets
    {
        int SocketObject_SendPacket(ClientSocketStruct* pSocket, byte* PacketData, uint DataSize);
        int SocketObject_RemoveFirstPacket(ClientSocketStruct* pSocket, uint Length);
        int ReplaceServerPacketData(byte** pData, uint* pDataLen, byte* newData, uint newDataLength);
    }
}
