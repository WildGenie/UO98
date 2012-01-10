#include "Classes.h"

#pragma managed

using namespace System;

public enum struct ALRReason : __int8
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
};

public enum struct Direction : __int8
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
};

[Flags]
public enum struct TileFlag : unsigned __int32
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
    Internal		    = 0x00010000,
    Foliage			    = 0x00020000,
    PartialHue		  = 0x00040000,
    Unknown2		    = 0x00080000,
    Map				      = 0x00100000,
    Container		    = 0x00200000,
    Wearable		    = 0x00400000,
    LightSource		  = 0x00800000,
    Animation		    = 0x01000000,
    NoDiagonal		  = 0x02000000,
    Unknown3		    = 0x04000000,
    Armor			      = 0x08000000,
    Roof			      = 0x10000000,
    Door			      = 0x20000000,
    StairBack		    = 0x40000000,
    StairRight		  = 0x80000000
};

public enum struct BookWriteableFlag : __int8
{
    ReadOnly=0,
    Writeable=1
};

typedef public value struct Serial sealed { 
private:
  unsigned int _serial;

  Serial(unsigned int serial)
  {
    _serial=serial;
  }

  Serial(int serial)
  {
    _serial=(unsigned int)serial;
  }

public:

  static operator unsigned int(Serial serial)
  {
    return serial._serial;
  }

  static operator int(Serial serial)
  {
    return serial._serial;
  }

  static operator Serial(unsigned int serial)
  {
    return Serial(serial);
  }

  static operator Serial(int serial)
  {
    return Serial(serial);
  }
} Serial;

typedef public value struct LocationDelta sealed { 
    def_class_Location 

    LocationDelta(short x, short y, short z)
    {
        X = x;
        Y = y;
        Z = z;
    }

} LocationDelta;

typedef public value struct Location sealed { 
    def_class_Location 

    Location(short x, short y, short z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    static property Location Zero
    {
        Location get()
        {
            Location toReturn=Location();
            toReturn.X=toReturn.Y=toReturn.Z=0;
            return toReturn;
        }
    }

    static bool operator== (Location^ A, Object^ B)
    {
        return A->Equals(B);
    }

    bool operator!= (const Location& toCompare)
    {
        return !(this->Equals(toCompare));
    }

    virtual int GetHashCode() override
    {
        return (int)((X & 0xFFF00000) << 20) + ((Y & 0xFFF00) << 8) + (Z & 0xFF);
    }

    virtual bool Equals(Object^ obj) override
    {
        if(obj->GetType() == Location::typeid)
        {
            Location^ toCompare = (Location^)obj;
            return
                X == toCompare->X &&
                Y == toCompare->Y &&
                Z == toCompare->Z;
        }
        return false;
    }

    static LocationDelta operator- (Location^ A, Location^ B)
    {
        return LocationDelta((short)(A->X - B->X), (short)(A->Y - B->Y), (short)(A->Z - B->Z));
    }

    static Location operator+ (Location^ A, LocationDelta^ B)
    {
        return Location((short)(A->X + B->X), (short)(A->Y + B->Y), (short)(A->Z + B->Z));
    }

    virtual String^ ToString() override
    {
        return X + " " + Y + " " + Z;
    }

    static operator Location(LocationObject loc)
    {
      return Location(loc.X, loc.Y, loc.Z);
    }

    static operator Location(LocationObject* loc)
    {
      return Location(loc->X, loc->Y, loc->Z);
    }

} Location;

