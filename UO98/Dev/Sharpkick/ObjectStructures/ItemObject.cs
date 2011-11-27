using System;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    [StructLayout(LayoutKind.Explicit, Pack = 1, Size = 0x50)]
    struct ItemObject 
    {
        [FieldOffset(0x04)] public ushort ObjectType;
        [FieldOffset(0x08)] public ushort Hue;
        [FieldOffset(0x0A)] public Location Location;
        [FieldOffset(0x10)] public Location CreationLocation;
        [FieldOffset(0x16)] public uint Template;
        //...
        [FieldOffset(0x40)] public uint Serial;
        [FieldOffset(0x44)] public byte StatusFlags;
        [FieldOffset(0x45)] public byte DecayCount;
    }
}
