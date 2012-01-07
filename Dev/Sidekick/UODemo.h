// A Managed to Native Proxy class for API commands.

#pragma once

#include "Commands.h"

public ref class UODemo
{
public:

  //UODemo(void)
  //{
  //}

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
};


