using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Sharpkick.Network;

namespace Sharpkick
{
    /// <summary>
    /// Functions intended to be exported to Sidekick
    /// </summary>
    public class CoreEvents
    {
        /// <summary>
        /// Called when a tick occurs on the server
        /// </summary>
        public static void OnPulse()
        {
            if (!Main.Initialized) Main.Initialize();
            EventSink.InvokeOnPulse();
        }

        /// <summary>
        /// Called after the world is saved.
        /// </summary>
        public static void OnAfterSave()
        {
            EventSink.InvokeOnAfterSave();
        }

        /// <summary>
        /// Called when the server receives a valid packet, before it's processed.
        /// </summary>
        /// <param name="pSocket">The servers socket which received the packet.</param>
        /// <param name="PacketID">The packet ID (first byte of Data)</param>
        /// <param name="PacketSize">Size of the packet</param>
        /// <param name="IsPacketDynamicSized">True if this is a dynamic length packet</param>
        unsafe public static void OnPacketReceived(byte* pSocket, byte PacketID, uint PacketSize, bool IsPacketDynamicSized)
        {
            if(MyServerConfig.PacketDebug) Console.WriteLine("Packet obj: ID:{0:X2} Size:{1} Dyn:{2}", PacketID, PacketSize, IsPacketDynamicSized);

            Network.ClientPacketSafe packet = Network.ClientPacket.Instantiate(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
            if (packet != null && !packet.OnReceived())
                packet.Remove();
        }

        /// <summary>
        /// Called when the server receives a packet that it cannot handle.
        /// </summary>
        /// <param name="pSocket">The servers socket which received the packet.</param>
        unsafe public static void OnHandleOutsideRangePacket(byte* pSocket)
        {
            //ClientSocket sock = new ClientSocket(pSocket);
            byte PacketID = *(pSocket + 0x28);
            uint PacketSize = 0;
            bool IsPacketDynamicSized = false;

            ClientVersionStruct ver = *(ClientVersionStruct*)(pSocket + 0x1003C);
            ClientVersion version;
            if (PacketID == 0xBB && ver < ClientVersion.v1_26_0) // detect client 1.26.0
            {
                ClientSocket socket = new ClientSocket(pSocket);
                version = ClientVersion.v1_26_0;
                socket.SetClientVersion(version.Version);
            }
            else
                version = ClientVersion.Instantiate(ver);
            
            PacketVersionEntry packetinfo = PacketVersions.GetPacketInfo(PacketID, version);

            if(packetinfo == null)
            {
                ConsoleUtils.PushColor(ConsoleColor.Red);
                Console.WriteLine("WARNING: Ignored Invalid Packet {0:X2}.", PacketID);
                ConsoleUtils.PopColor();
            }
            else
            {
                //case 0xB6: PacketSize = 9; IsPacketDynamicSized = false; break;
                //case 0xB8: PacketSize = 0; IsPacketDynamicSized = true; break;
                //case 0xBB: PacketSize = 9; IsPacketDynamicSized = false; break;
                //case 0xBD: PacketSize = 0; IsPacketDynamicSized = true; break;
                //default:
                PacketSize = packetinfo.Length;
                IsPacketDynamicSized = packetinfo.Dynamic;

                if(MyServerConfig.PacketDebug) Console.WriteLine("Handling Invalid Packet {0:X2} from client version {1}", PacketID, version);
                OnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
            }
        }

        /// <summary>
        /// Called when the server initiates a send to the client.
        /// </summary>
        unsafe public static void OnPacketSending(byte* pSocket, byte** pData, uint* pDataLen)
        {
            Network.ServerPacket packet = Network.ServerPacket.Instantiate(pSocket, pData, pDataLen);
            if (!packet.OnSending())
            {
                // TODO: Remove the packet.
            }
        }


    }
}

