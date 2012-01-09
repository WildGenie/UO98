#include "Classes.h"

#pragma managed

using namespace System;

typedef public value struct LocationDelta { 
    def_class_Location 

    LocationDelta(short x, short y, short z)
    {
        X = x;
        Y = y;
        Z = z;
    }

} LocationDelta;

typedef public value struct Location { 
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

} Location;

