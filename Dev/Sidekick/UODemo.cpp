#include "UODemo.h"
#include "Commands.h"
#include <stdio.h>

namespace UODemo
{
    Core::Core()
    {
        PulseHandler=gcnew OnPulseEventHandler(this, &Core::InvokeOnPulse);
        GlobalOnPulse += PulseHandler;
    }

    Core::~Core()
    {
        GlobalOnPulse -= PulseHandler;
    }

    void Core::InvokeGlobalOnPulse()
    {
        GlobalOnPulse();
    }

    void Core::InvokeOnPulse()
    {
        OnPulse();
    }

    void Core::SaveWorld() 
    {
        UnsafeNativeMethods::SaveWorld();      
    }
    
    void Core::Shutdown()  
    {
        UnsafeNativeMethods::ShutdownServer(); 
    }

    void Core::MakeCounselor(void *PlayerObjectTarget, int CounType)
    {
        UnsafeNativeMethods::MakeCounselor((PlayerObject*)PlayerObjectTarget, CounType);
    }

    void Core::UnmakeCounselor(void *PlayerObjectTarget)
    {
        UnsafeNativeMethods::UnmakeCounselor((PlayerObject*) PlayerObjectTarget);
    }

    void Core::OpenInfoWindow(Serial gmserial, Serial playerserial)
    {
        UnsafeNativeMethods::SendInfoWindowToGodClient(gmserial, playerserial);
    }

    Location Core::getLocation(Serial itemSerial)
    {
        class_Location Loc;
        UnsafeNativeMethods::getLocation(&Loc, itemSerial);
        return Loc;
    }

    int Core::setHue(Serial itemSerial, short hue)
    {
        return UnsafeNativeMethods::setHue(itemSerial, hue);
    }

    #define FUNC_ItemObject_GetQuantity 0x004854F2
    int Core::getQuantity(Serial serial)
    {
        return UnsafeNativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetQuantity, "getQuantity");
    }

    #define FUNC_ItemObject_GetWeight 0x00489FAB
    int Core::getWeight(Serial serial)
    {
        return UnsafeNativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetWeight, "getWeight");
    }

    int Core::setOverloadedWeight(Serial serial, int weight)
    {
        return UnsafeNativeMethods::setOverloadedWeight(serial, weight);
    }

    bool Core::deleteObject(Serial serial)
    {
        return UnsafeNativeMethods::deleteObject(serial) != 0;
    }

    void Core::InitializeSharpkick()
    {
        if(aSharpkick==nullptr)
            aSharpkick=Assembly::LoadFrom("Sharpkick.dll");

        if(aSharpkick!=nullptr)
        {
            Type^ tMain=aSharpkick->GetType("Sharpkick.Main");
            MethodInfo^ mInit = tMain->GetMethod("Initialize");
            mInit->Invoke(nullptr, nullptr);

            puts("UODemo.Core Initialized");
        }
        else
            puts("UODemo.Core Initialize Fail: Could not load Assembly Sharpkick.");
    }

}
