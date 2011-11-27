using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Sharpkick
{
    enum ALRReason : byte
    {
        /// <summary>This account doesn't exist. If you just created or updated the account on the web site, it may take a few minutes to be transmitted to Origin</summary>
        Invalid = 0x00,
        /// <summary>Someone is already using this account.</summary>
        InUse = 0x01,
        /// <summary>Your account has been blocked. Please visit http://ultima-registration.com for information on reactivating your account.</summary>
        Blocked = 0x02,
        /// <summary>Your account credentials are invalid. Check your user ID and password and try again.</summary>
        BadPass = 0x03,
        /// <summary>Sends user back to the Main Menu</summary>
        Idle = 0xFE,
        /// <summary>There is some problem communicating with Origin. Please restart ultima Online and try again.</summary>
        BadComm = 0xFF
    }

    struct Serial
    {
        private uint _serial;

        private Serial(uint serial)
        {
            _serial = serial;
        }

        public static implicit operator int(Serial serial)
        {
            return (int)serial._serial;
        }
        public static implicit operator uint(Serial serial)
        {
            return (uint)serial._serial;
        }
        public static implicit operator Serial(uint serial)
        {
            return new Serial(serial);
        }
        public static implicit operator Serial(int serial)
        {
            return new Serial((uint)serial);
        }
    }

    struct ItemRange
    {
        public int Begin;
        public int End;
        public ItemRange(int begin, int end)
        {
            Begin = begin;
            End = end;
        }
    }

    struct ItemAndLocation
    {
        public ushort ItemID;
        public Location Location;

        public ItemAndLocation(ushort itemid, Location location)
        {
            ItemID = itemid;
            Location = location;
        }

        public override string ToString()
        {
            return string.Format("{0} @ {1}", ItemID, Location);
        }
    }

    enum Direction : byte
    {
        North = 0,
        Right = 1,
        East = 2,
        Down = 3,
        South = 4,
        Left = 5,
        West = 6,
        Up = 7,
        /// <summary>Running FLAG</summary>
        Running = 0x80
    }

    enum Facing
    {
        EastWest,
        NorthSouth,
    }

    [Flags]
    enum TileFlag : int
    {
        Background      = 0x1,
        Weapon          = 0x2,
        Transparent     = 0x4,
        Translucent     = 0x8,
        Wall            = 0x10,
        Damaging        = 0x20,
        Impassable      = 0x40,
        Wet             = 0x80,
        Unknown1        = 0x100,
        Surface         = 0x200,
        Bridge          = 0x400,
        Generic         = 0x800,
        Window          = 0x1000,
        NoShoot         = 0x2000,
        ArticleA        = 0x4000,
        ArticleAn       = 0x8000,
   		Internal		= 0x00010000,
		Foliage			= 0x00020000,
		PartialHue		= 0x00040000,
		Unknown2		= 0x00080000,
		Map				= 0x00100000,
		Container		= 0x00200000,
		Wearable		= 0x00400000,
		LightSource		= 0x00800000,
		Animation		= 0x01000000,
		NoDiagonal		= 0x02000000,
		Unknown3		= 0x04000000,
		Armor			= 0x08000000,
		Roof			= 0x10000000,
		Door			= 0x20000000,
		StairBack		= 0x40000000,
		StairRight		= unchecked( (int)0x80000000 )
 }

    struct CharInfo
    {
        public CharInfo(string charname, string password)
        {
            CharName = charname;
            Password = password;
        }
        public string CharName;
        public string Password;
    }

    enum BookWriteableFlag
    {
        ReadOnly=0,
        Writeable=1
    }

    struct LocationDelta
    {
        public short X;
        public short Y;
        public short Z;

        public LocationDelta(short x, short y, short z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Location operator +(Location location, LocationDelta delta)
        {
            return new Location((short)(location.X + delta.X), (short)(location.Y + delta.Y), (short)(location.Z + delta.Z));
        }
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct Location
    {
        public short X;
        public short Y;
        public short Z;

        public Location(short x, short y, short z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Location Zero = new Location(0, 0, 0);

        public static bool operator ==(Location A, Location B)
        {
            return A.Equals(B);
        }

        public static bool operator !=(Location A, Location B)
        {
            return !A.Equals(B);
        }

        public override int GetHashCode()
        {
            return (int)((X & 0xFFF00000) << 20) + ((Y & 0xFFF00) << 8) + (Z & 0xFF);
        }

        public override bool Equals(object obj)
        {
            if(!(obj is Location)) return false;
            Location toCompare=(Location)obj;
            return
                X == toCompare.X &&
                Y == toCompare.Y &&
                Z == toCompare.Z;
        }

        public static LocationDelta operator -(Location A, Location B)
        {
            return new LocationDelta((short)(A.X - B.X), (short)(A.Y - B.Y), (short)(A.Z - B.Z));
        }

        public override string ToString()
        {
            return string.Format("{0} {1} {2}", X, Y, Z);
        }
    }

    [Flags]
    enum AccessFlags
    {
        Player=0,
        Admin=Editor | SaveWorld | Shutdown,

        Editor=0x01,
        SaveWorld=0x02,
        Shutdown=0x04,
    }
}
