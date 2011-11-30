using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Runtime.InteropServices;

namespace Sharpkick.Network
{
    [StructLayout(LayoutKind.Explicit, Pack = 1, Size = 0x10040)]
    unsafe struct ClientSocketStruct
    {
        [FieldOffset(0x0000C)] public uint Handle;
        [FieldOffset(0x00024)] public char* SocketIdentifierString;
        [FieldOffset(0x00028)] public fixed byte Data[65536];
        [FieldOffset(0x10028)] public uint AccountNumber;
        [FieldOffset(0x1002C)] public uint DataLength;
        [FieldOffset(0x10030)] public uint IpAddressLong;
        [FieldOffset(0x10038)] public PlayerObject* PlayerObject;
        [FieldOffset(0x1003C)] public ClientVersionStruct VersionInfo;
    }

    unsafe sealed class ClientSocket
    {
        ClientSocketStruct* pSocket = null;

        public ClientSocket(byte* psocket) : this((ClientSocketStruct*)psocket) { }
        public ClientSocket(ClientSocketStruct* psocket)
        {
            pSocket = psocket;
        }

        public uint SocketHandle { get { return (*pSocket).Handle; } }

        private string m_SocketIdentifierString = null;
        public string SocketIdentifierString { get { return m_SocketIdentifierString ?? (m_SocketIdentifierString = StringPointerUtils.GetAsciiString(*(byte**)((*pSocket).SocketIdentifierString))); } }

        public byte* Data { get { return (*pSocket).Data; } }
        public uint DataLength 
        {
            get { return (*pSocket).DataLength; }
            private set { (*pSocket).DataLength = value; }
        }

        /// <summary>
        /// Removes bytes from socket buffer. This does not check to ensure the buffer still contains data, which it must.
        /// </summary>
        /// <param name="start">Index at which to start removing</param>
        /// <param name="amount">The number of bytes to remove</param>
        public void RemoveBytes(ushort start, ushort amount)
        {
            for (ushort i = start; i < DataLength; i++)
                *(Data + i) = *(Data + amount + i);
            DataLength -= amount;
        }

        public void Replace(byte[] newData, uint oldLen)
        {
            // Make room after current packet
            for (uint i = oldLen; i < DataLength; i++)
                *(Data + i + newData.Length) = *(Data + i);
            // Write packet after the existing one
            for (uint i = 0; i < newData.Length; i++)
                *(Data + oldLen + i) = newData[i];
            // Remove first packet
            for (int i = 0; i < DataLength + newData.Length - oldLen; i++)
                *(Data + i) = *(Data + oldLen + i);
            DataLength = DataLength - oldLen + (uint)newData.Length;
        }

        public uint AccountNumber { get { return (*pSocket).AccountNumber; } }
        public ClientVersionStruct Version { get { return (*pSocket).VersionInfo; } }

        public bool VerifyGod { get { return Accounting.HasAccess(AccountNumber, AccessFlags.Editor); } }

        /// <summary>
        /// Set the client version for this socket, this is persistent server data
        /// </summary>
        /// <param name="vStruct"></param>
        public void SetClientVersion(ClientVersionStruct vStruct)
        {
            (*pSocket).VersionInfo = vStruct;
            //*(byte*)(pSocket + 0x1003C) = vStruct.Major;
            //*(byte*)(pSocket + 0x1003D) = vStruct.Minor;
            //*(byte*)(pSocket + 0x1003E) = vStruct.Build;
            //*(byte*)(pSocket + 0x1003F) = vStruct.Revision;
        }

        /// <summary>The Long representation of the remote IP in Host Byte Order</summary>
        private uint IpAddressLong { get { return (*pSocket).IpAddressLong; } }

        private IPAddress m_IPAddress = null;
        public IPAddress IPAddress 
        {
            get 
            {
                if (m_IPAddress != null) return m_IPAddress;

                try
                {
                    return (m_IPAddress = new IPAddress(IPAddress.HostToNetworkOrder((int)IpAddressLong)));
                }
                catch
                {
                    return null;
                }
            }
        }

        public PlayerObject* Player { get { return (*pSocket).PlayerObject; } }

        public PlayerFlag PlayerFlags { get { return PlayerObject.GetPlayerFlags(Player); } }

        public bool IsGod
        {
            get { return PlayerObject.GetPlayerFlag(Player, PlayerFlag.IsGod); }
            set { PlayerObject.SetPlayerFlag(Player, PlayerFlag.IsGod, value); }
        }

        public bool IsEditing
        {
            get { return PlayerObject.GetPlayerFlag(Player, PlayerFlag.IsEditing); }
            set { PlayerObject.SetPlayerFlag(Player, PlayerFlag.IsEditing, value); }
        }

        public bool IsGm
        {
            get { return PlayerObject.GetPlayerFlag(Player, PlayerFlag.IsGM); }
        }

        public bool IsInternal { get { return SocketHandle == 0xBEEF; } }

        public int SendPacket(ServerPacketSafe packet)
        {
            return SendPacket(packet.Data, (uint)packet.Length);
        }

        public int SendPacket(byte[] PacketData, uint Packetlength)
        {
            fixed (byte* pData = PacketData)
                return Server.PacketEngine.SocketObject_SendPacket(pSocket, pData, Packetlength);
        }

        /// <summary>
        /// Removes the top packet in the Sockets incoming packet buffer
        /// </summary>
        /// <param name="Length">The size of the packet</param>
        public void RemoveFirstPacket(int Length)
        {
            Server.PacketEngine.SocketObject_RemoveFirstPacket(pSocket, (uint)Length);
        }
    }
}
