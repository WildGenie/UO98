using System;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    [StructLayout(LayoutKind.Explicit, Pack = 1, Size = 0x458)]
    unsafe struct PlayerObject
    {
        [FieldOffset(0x00)] public MobileObject MobileObject;

        public ushort Body { get { return MobileObject.ContainerObject.ItemObject.ObjectType; } }
        public ushort Hue { get { return MobileObject.ContainerObject.ItemObject.Hue; } }
        public Location Location { get { return MobileObject.ContainerObject.ItemObject.Location; } }
        public uint Template { get { return MobileObject.ContainerObject.ItemObject.Template; } }
        public uint Serial { get { return MobileObject.ContainerObject.ItemObject.Serial; } }

        [FieldOffset(0x3A8)] private PlayerFlag m_PlayerFlags;
        #region PlayerFlags
        public static PlayerFlag GetPlayerFlags(PlayerObject* player)
        {
            if(player==null) return 0;
            return (*player).m_PlayerFlags;
        }

        public static bool GetPlayerFlag(PlayerObject* player, PlayerFlag toGet)
        {
            if (player == null) return false;
            return ((*player).m_PlayerFlags & toGet) == toGet;
        }

        public static void SetPlayerFlag(PlayerObject* player, PlayerFlag toSet, bool Value = true)
        {
            if (player != null)
            {
                if (Value) (*player).m_PlayerFlags |= toSet;
                else (*player).m_PlayerFlags &= ~toSet;
            }
        }

        public static void ClearPlayerFlag(PlayerObject* player, PlayerFlag toClear)
        {
            SetPlayerFlag(player, toClear, false);
        }
        #endregion

        [FieldOffset(0x3FC)] public int AccountNumber;
        [FieldOffset(0x400)] public uint CharacterNumber;
    }
}
