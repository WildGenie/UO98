using System;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    [Flags]
    enum MobileFlags : byte
    {
        None = 0x00,
        Frozen = 0x01,
        Female = 0x02,
        Poisoned = 0x04,        // Flying in post 7.x client
        Invulnerable = 0x08,    // Yellow healthbar
        IgnoreMobiles = 0x10,
        Movable = 0x20,
        WarMode = 0x40,
        Hidden = 0x80
    }

    [StructLayout(LayoutKind.Explicit, Pack = 1, Size = 0x37C)]
    unsafe struct MobileObject
    {
        [FieldOffset(0x00)] public ContainerObject ContainerObject;

        public ushort Body { get { return ContainerObject.ItemObject.ObjectType; } }
        public ushort Hue { get { return ContainerObject.ItemObject.Hue; } }
        public Location Location { get { return ContainerObject.ItemObject.Location; } }
        public uint Template { get { return ContainerObject.ItemObject.Template; } }
        public uint Serial { get { return ContainerObject.ItemObject.Serial; } }

        #region MobileFlags
        [FieldOffset(0x379)] public MobileFlags m_Flags;
        public static MobileFlags GetMobileFlags(MobileObject* mobile)
        {
            if (mobile == null) return 0;
            return (*mobile).m_Flags;
        }

        public static bool GetMobileFlags(MobileObject* mobile, MobileFlags toGet)
        {
            if (mobile == null) return false;
            return ((*mobile).m_Flags & toGet) == toGet;
        }

        public static void SetMobileFlags(MobileObject* mobile, MobileFlags toSet, bool Value = true)
        {
            if (mobile != null)
            {
                if (Value) (*mobile).m_Flags |= toSet;
                else (*mobile).m_Flags &= ~toSet;
            }
        }

        public static void ClearMobileFlags(MobileObject* mobile, MobileFlags toClear)
        {
            SetMobileFlags(mobile, toClear, false);
        }
        #endregion
    }
}
