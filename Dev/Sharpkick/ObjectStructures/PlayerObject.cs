using System;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    [Flags]
    enum PlayerFlag : uint
    {
        LastMoveRej = 0x00000001,  // ??
        IsGod = 0x00000002,
        IsOnline = 0x00000004,
        IsEditing = 0x00000008,
        HackMove = 0x00000010,
        IsManifesting = 0x00000020,
        unk00000040 = 0x00000040,
        unk00000080 = 0x00000080,
        unk00000100 = 0x00000100,
        un0000k0200 = 0x00000200,
        InSeance = 0x00000400,
        unk00000800 = 0x00000800,
        IsGM = 0x00001000,
        unk00002000 = 0x00002000,     // something with login
        unk00004000 = 0x00004000,     // something with counselor
        IsCounselor = 0x00008000,
        BankDefs = 0x00010000,
        IsGoldAccount = 0x00020000
    }

    [StructLayout(LayoutKind.Explicit, Pack = 1, Size = 0x458)]
    unsafe struct PlayerObject
    {
        [FieldOffset(0x00)] public MobileObject MobileObject;

        public ushort Body { get { return MobileObject.ContainerObject.ItemObject.ObjectType; } }
        public ushort Hue { get { return MobileObject.ContainerObject.ItemObject.Hue; } }
        public Location Location { get { return MobileObject.ContainerObject.ItemObject.Location; } }
        public uint Template { get { return MobileObject.ContainerObject.ItemObject.Template; } }
        public uint Serial { get { return MobileObject.ContainerObject.ItemObject.Serial; } }

        #region PlayerFlags
        [FieldOffset(0x3A8)] private PlayerFlag m_PlayerFlags;
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
    }
}
