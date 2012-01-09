using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    unsafe interface ICore
    {
        Network.IPackets PacketEngine { get; }

        void SaveWorld();

        void SendSystemMessage(PlayerObject* player, byte* message);
        int createGlobalObjectAt(int ItemID, Location* Location);
        int deleteObject(int serial);

        int setObjVarInt(int serial, byte* name, int value);
        int setObjVarString(int serial, byte* name, byte* value);
        int setObjVarLocation(int serial, byte* name, Location* value);
        void removeObjVar(int serial, byte* varName);
        bool hasObjVarOfType(int serial, byte* varName, VariableType varType);
        int getObjVarInt(int serial, byte* varName);
        byte* getObjVarString(int serial, byte* varName);
        bool getObjVarLocation(int serial, byte* varName, Location* locationResult);

        int setHue(int serial, short hue);
        byte* addScript(int serial, byte* scriptName, int executeCreation);
        bool hasScript(int serial, byte* scriptName);
        bool detachScript(int serial, byte* scriptName);

        int getQuantity(int serial);
        int getWeight(int serial);
        int setOverloadedWeight(int serial, int weight);
        
        int getFirstObjectOfType(Location* location, int itemId);
        int getNextObjectOfType(Location* location, int itemId, int lastItemSerial);

        Location* getLocation(Location* location, int itemSerial);
        void MakeGameMaster(PlayerObject* Target);
        void UnmakeGameMaster(PlayerObject* Target);
        int IsGameMaster(PlayerObject* Target);
        void OpenBank(PlayerObject* Target, PlayerObject* ShowTo);
        ItemObject* ConvertSerialToObject(int serial);

        void OpenInfoWindow(Serial gmserial, Serial playerserial);

        bool IsItem(void* @object);
        bool IsNPC(void* @object);
        bool IsMobile(void* @object);
        bool IsPlayer(void* @object);

        ITimeManager TimeManager { get; }
        IServerConfiguration ServerConfiguration { get; }
        ISpawnLimits SpawnLimits { get; }
        IResources Resources { get; }
        ISkillsObject SkillsObject { get; }
    }
}
