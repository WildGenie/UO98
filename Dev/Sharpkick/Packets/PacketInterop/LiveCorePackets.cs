using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Sharpkick.Network
{
    unsafe class LiveCorePackets : IPackets
    {
        private static class UnsafeNativeMethods
        {
            [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
            public static extern int SocketObject_SendPacket(ClientSocketStruct* pSocket, byte* PacketData, uint DataSize);

            [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
            public static extern int SocketObject_RemoveFirstPacket(ClientSocketStruct* pSocket, uint Length);

            [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
            public static extern int ReplaceServerPacketData(byte** pData, uint* pDataLen, byte* newData, uint newDataLength);
        }

        #region IPackets Members

        public int SocketObject_SendPacket(ClientSocketStruct* pSocket, byte* PacketData, uint DataSize)
        {
            return UnsafeNativeMethods.SocketObject_SendPacket(pSocket, PacketData, DataSize);
        }

        public int SocketObject_RemoveFirstPacket(ClientSocketStruct* pSocket, uint Length)
        {
            return UnsafeNativeMethods.SocketObject_RemoveFirstPacket(pSocket, Length);
        }

        public int ReplaceServerPacketData(byte** pData, uint* pDataLen, byte* newData, uint newDataLength)
        {
            return UnsafeNativeMethods.ReplaceServerPacketData(pData, pDataLen, newData, newDataLength);
        }

        #endregion

    }
}
