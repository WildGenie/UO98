// A Managed to Native Proxy class for API commands.

#pragma once

#include "Commands.h"
#include "Classes_Managed.h"

namespace UODemo
{
  public ref class Core abstract sealed // Static
  {
  public:
    static void Save()      { SaveWorld();      }
    static void Shutdown()  { ShutdownServer(); }

    static void Counselor(PlayerObject *Target, int CounType)
    {
      MakeCounselor(Target, CounType);
    }

    static void UnCounselor(PlayerObject *Target)
    {
      UnmakeCounselor(Target);
    }

    static void OpenInfoWindow(Serial gmserial, Serial playerserial)
    {
      SendInfoWindowToGodClient(gmserial, playerserial);
    }

    static Location getObjectLocation(Serial itemSerial)
    {
        class_Location Loc;
        getLocation(&Loc, itemSerial);
        return Loc;
    }

    static int setObjectHue(Serial itemSerial, short hue)
    {
        return setHue(itemSerial, hue);
    }


  };
}