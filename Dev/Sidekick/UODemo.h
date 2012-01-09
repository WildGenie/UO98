// A Managed to Native Proxy class for API commands.

#pragma once

#include "Commands.h"
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

    static class_Location* getObjectLocation(int itemSerial)
    {
        class_Location* outLocationObject;
        getLocation(outLocationObject, itemSerial);
        return outLocationObject;
    }

  };
}