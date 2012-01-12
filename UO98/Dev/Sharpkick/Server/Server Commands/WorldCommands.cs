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

        unsafe public static bool deleteObject(Serial serial)
        {
            return Core.deleteObject(serial);
        }

        unsafe public static int getFirstObjectOftype(Location location, int itemId)
        {
            return Core.getFirstObjectOfType(&location, itemId);
        }

        unsafe public static int getNextObjectOfType(Location location, int itemId, int lastItemSerial)
        {
            return Core.getNextObjectOfType(&location, itemId, lastItemSerial);
        }

        unsafe public static bool TryFindObject(int serial, out DynamicItem item)
        {
            DynamicItem ditem = Server.Core.ConvertSerialToItem(serial);
            if (ditem == null)
            {
                item = null;
                return false;
            }
            else
            {
                item = ditem;
                return true;
            }
        }

        unsafe public static bool TryFindObject(int serial, out PlayerObject player)
        {
            class_Player* playerPtr = Server.Core.ConvertSerialToPlayer(serial);
            if(playerPtr == null)
            {
                player = new PlayerObject();
                return false;
            }
            else
            {
                player = *(PlayerObject*)playerPtr;
                return true;
            }
        }


    }
}
