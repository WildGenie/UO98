using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    partial class Server
    {
        unsafe private partial class LiveCore : ICore
        {
            private Network.IPackets _PacketEngine;
            public Network.IPackets PacketEngine { get { return _PacketEngine ?? (_PacketEngine = new Network.LiveCorePackets()); } }

            public void SaveWorld()
            {
                UODemo.Core.Save();
            }

            public void SendSystemMessage(PlayerObject* player, byte* message)
            { UnsafeNativeMethods.SendSystemMessage(player, message); }

            public int createGlobalObjectAt(int ItemID, Location* Location)
            { return UnsafeNativeMethods.createGlobalObjectAt(ItemID, Location); }

            public unsafe int deleteObject(int serial)
            { return UnsafeNativeMethods.deleteObject(serial); }

            public int setObjVarInt(int serial, byte* name, int value)
            { return UnsafeNativeMethods.setObjVarInt(serial, name, value); }

            public int setObjVarString(int serial, byte* name, byte* value)
            { return UnsafeNativeMethods.setObjVarString(serial, name, value); }

            public int setObjVarLocation(int serial, byte* name, Location* value)
            { return UnsafeNativeMethods.setObjVarLocation(serial, name, value); }

            public void removeObjVar(int serial, byte* varName)
            { UnsafeNativeMethods.removeObjVar(serial, varName); }

            public bool hasObjVarOfType(int serial, byte* varName, VariableType varType)
            { return UnsafeNativeMethods.hasObjVarOfType(serial, varName, varType); }

            public int getObjVarInt(int serial, byte* varName)
            { return UnsafeNativeMethods.getObjVarInt(serial, varName); }

            public byte* getObjVarString(int serial, byte* varName)
            { return UnsafeNativeMethods.getObjVarString(serial, varName); }

            public bool getObjVarLocation(int serial, byte* varName, Location* locationResult)
            { return UnsafeNativeMethods.getObjVarLocation(serial, varName, locationResult); }

            public int setHue(int serial, short hue)
            { return UnsafeNativeMethods.setHue(serial, hue); }

            public byte* addScript(int serial, byte* scriptName, int executeCreation)
            { return UnsafeNativeMethods.addScript(serial, scriptName, executeCreation); }

            public bool hasScript(int serial, byte* scriptName)
            { return UnsafeNativeMethods.hasScript(serial, scriptName); }

            public bool detachScript(int serial, byte* scriptName)
            { return UnsafeNativeMethods.detachScript(serial, scriptName); }

            private const int FUNC_ItemObject_GetWeight = 0x00489FAB;
            public int getWeight(int serial)
            {
                return getValueByFunctionFromObject(serial, FUNC_ItemObject_GetWeight, "getWeight");
            }

            private const int FUNC_ItemObject_GetQuantity = 0x004854F2;
            public int getQuantity(int serial)
            {
                return getValueByFunctionFromObject(serial, FUNC_ItemObject_GetQuantity, "getQuantity");
            }

            private int getValueByFunctionFromObject(int serial, int function, string debugCallString)
            { return UnsafeNativeMethods.getValueByFunctionFromObject(serial, function, debugCallString); }

            public int setOverloadedWeight(int serial, int weight)
            { return UnsafeNativeMethods.setOverloadedWeight(serial, weight); }

            public int getFirstObjectOfType(Location* location, int itemId)
            { return UnsafeNativeMethods.getFirstObjectOfType(location, itemId); }

            public int getNextObjectOfType(Location* location, int itemId, int lastItemSerial)
            { return UnsafeNativeMethods.getNextObjectOfType(location, itemId, lastItemSerial); }

            public unsafe Location* getLocation(Location* location, int itemSerial)
            {
                Location* loc = UODemo.Core.getObjectLocation(itemSerial);
                return (Location*)loc;
                //return UnsafeNativeMethods.getLocation(location, itemSerial); 
            }

            public void MakeGameMaster(PlayerObject* Target)
            { UnsafeNativeMethods.MakeGameMaster(Target); }

            public void UnmakeGameMaster(PlayerObject* Target)
            { UnsafeNativeMethods.UnmakeGameMaster(Target); }

            public int IsGameMaster(PlayerObject* Target)
            { return UnsafeNativeMethods.IsGameMaster(Target); }

            public void OpenBank(PlayerObject* Target, PlayerObject* ShowTo)
            { UnsafeNativeMethods.OpenBank(Target, ShowTo); }

            public ItemObject* ConvertSerialToObject(int serial)
            { return UnsafeNativeMethods.ConvertSerialToObject(serial); }

            public void OpenInfoWindow(Serial gmserial, Serial playerserial)
            {
                UODemo.Core.OpenInfoWindow(gmserial, playerserial);
            }

            public bool IsItem(void* @object)
            { return UnsafeNativeMethods.IsItem(@object); }

            public bool IsNPC(void* @object)
            { return UnsafeNativeMethods.IsNPC(@object); }

            public bool IsMobile(void* @object)
            { return UnsafeNativeMethods.IsMobile(@object); }

            public bool IsPlayer(void* @object)
            { return UnsafeNativeMethods.IsPlayer(@object); }

            private class UnsafeNativeMethods
            {
                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern void SendSystemMessage(PlayerObject* player, byte* message);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int createGlobalObjectAt(int ItemID, Location* Location);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int deleteObject(int serial);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int setObjVarInt(int serial, byte* name, int value);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int setObjVarString(int serial, byte* name, byte* value);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int setObjVarLocation(int serial, byte* name, Location* value);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern void removeObjVar(int serial, byte* varName);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool hasObjVarOfType(int serial, byte* varName, VariableType varType);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int getObjVarInt(int serial, byte* varName);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern byte* getObjVarString(int serial, byte* varName);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool getObjVarLocation(int serial, byte* varName, Location* locationResult);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int setHue(int serial, short hue);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern byte* addScript(int serial, byte* scriptName, int executeCreation);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool hasScript(int serial, byte* scriptName);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool detachScript(int serial, byte* scriptName);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int getValueByFunctionFromObject(int serial, int function, [MarshalAs(UnmanagedType.LPStr)]string debugCallString);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int setOverloadedWeight(int serial, int weight);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int getFirstObjectOfType(Location* location, int itemId);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int getNextObjectOfType(Location* location, int itemId, int lastItemSerial);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern Location* getLocation(Location* location, int itemSerial);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern void MakeGameMaster(PlayerObject* Target);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern void UnmakeGameMaster(PlayerObject* Target);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern int IsGameMaster(PlayerObject* Target);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern void OpenBank(PlayerObject* Target, PlayerObject* ShowTo);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern ItemObject* ConvertSerialToObject(int serial);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool IsItem(void* @object);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool IsNPC(void* @object);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool IsMobile(void* @object);

                [DllImport("sidekick.dll", CallingConvention = CallingConvention.Winapi)]
                public static extern bool IsPlayer(void* @object);
            }
        }
    }
}