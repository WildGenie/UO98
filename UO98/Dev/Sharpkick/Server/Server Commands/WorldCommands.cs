using System;

namespace Sharpkick
{
    static partial class Server
    {
        /// <summary>
        /// Create an item in the world
        /// </summary>
        /// <param name="ItemID">The Item ID</param>
        /// <param name="Location">The Location of the object</param>
        /// <returns>New items serial, or 0 on failure</returns>
        unsafe public static int createGlobalObjectAt(int ItemID, Location Location)
        {
            return Core.createGlobalObjectAt(ItemID, &Location);
        }

        unsafe public static bool deleteObject(int serial)
        {
            return Core.deleteObject(serial) != 0;
        }

        unsafe public static int getFirstObjectOftype(Location location, int itemId)
        {
            return Core.getFirstObjectOfType(&location, itemId);
        }

        unsafe public static int getNextObjectOfType(Location location, int itemId, int lastItemSerial)
        {
            return Core.getNextObjectOfType(&location, itemId, lastItemSerial);
        }

        unsafe public static bool TryFindObject(int serial, out ItemObject item)
        {
            ItemObject* itemPtr = Server.Core.ConvertSerialToObject(serial);
            if (itemPtr == null)
            {
                item = new ItemObject();
                return false;
            }
            else
            {
                item = *itemPtr;
                return true;
            }
        }

        unsafe public static bool TryFindObject(int serial, out PlayerObject player)
        {
            PlayerObject* playerPtr = (PlayerObject*)Server.Core.ConvertSerialToObject(serial);
            if(playerPtr == null || !Server.Core.IsPlayer(playerPtr))
            {
                player = new PlayerObject();
                return false;
            }
            else
            {
                player = *playerPtr;
                return true;
            }
        }


    }
}
