// A Managed to Native Proxy class for API commands.

#pragma once

#include "Commands.h"
#include "Classes_Managed.h"

namespace UODemo
{
  public ref class Core abstract sealed // Static
  {
  public:
    static void Save()      { UnsafeNativeMethods::SaveWorld();      }
    static void Shutdown()  { UnsafeNativeMethods::ShutdownServer(); }

    static void Counselor(PlayerObject *Target, int CounType)
    {
      UnsafeNativeMethods::MakeCounselor(Target, CounType);
    }

    static void UnCounselor(PlayerObject *Target)
    {
      UnsafeNativeMethods::UnmakeCounselor(Target);
    }

    static void OpenInfoWindow(Serial gmserial, Serial playerserial)
    {
      UnsafeNativeMethods::SendInfoWindowToGodClient(gmserial, playerserial);
    }

    static Location getObjectLocation(Serial itemSerial)
    {
        class_Location Loc;
        UnsafeNativeMethods::getLocation(&Loc, itemSerial);
        return Loc;
    }

    static int setObjectHue(Serial itemSerial, short hue)
    {
        return UnsafeNativeMethods::setHue(itemSerial, hue);
    }

    #define FUNC_ItemObject_GetQuantity 0x004854F2
    static int getQuantity(Serial serial)
    {
        return UnsafeNativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetQuantity, "getQuantity");
    }

    #define FUNC_ItemObject_GetWeight 0x00489FAB
    static int getWeight(int serial)
    {
        return UnsafeNativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetWeight, "getWeight");
    }

    static int SetOverloadedWeight(Serial serial, int weight)
    {
        return UnsafeNativeMethods::setOverloadedWeight(serial, weight);
    }

    static bool DeleteObject(int serial)
    {
        return UnsafeNativeMethods::deleteObject(serial) != 0;
    }
  };
}
