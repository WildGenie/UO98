using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Sharpkick.Global
{
    class TileData
    {
        public static void Configure()
        {
            //Console.WriteLine("Configuring TileData...");

            //// Make Spell Scrolls Generic items
            //for (ushort tileid = 7981; tileid <= 8050; tileid++)
            //    MakeGeneric(tileid);
        }

        public const int TileSize = 0x28;
        unsafe static private Tile* GLOBAL_TILEDATA { get { return *(Tile**)0x0064B364; } }

        unsafe static private void SetFlag(ushort TileID, TileFlag flag) { (*(TileFlag*)(GLOBAL_TILEDATA + TileID)) |= flag; }

        unsafe static public bool HasFlag(ushort TileID, TileFlag flag)
        {
            return ((*(TileFlag*)(GLOBAL_TILEDATA + TileID)) & flag) == flag;
        }

        private static void MakeGeneric(ushort TileID)
        {
            SetFlag(TileID, TileFlag.Generic);
        }

    }

    [StructLayout(LayoutKind.Sequential, Pack = 1, Size = TileData.TileSize)]
    unsafe struct Tile
    {
        public TileFlag Flags;
        public byte Weight;
        public byte Quality;
        byte undef1;
        byte undef2;
        public int MiscData;
        public short AnimData;
        public short Hue;
        public short BaseValue;
        public byte Height;
        public fixed byte Name[20];
        byte namezero;
    }

}
