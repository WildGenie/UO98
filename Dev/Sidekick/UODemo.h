// A Managed to Native Proxy class for API commands.

#pragma once

using namespace System::Reflection;

#include "Classes_Managed.h"

/// <summary>Delegate for EventSink.OnPulse event</summary>
public delegate void OnPulseEventHandler();

/// <summary>Delegate for EventSink.OnAfterSave event</summary>
public delegate void OnAfterSaveEventHandler();

public interface class IUOServer
{
    event OnPulseEventHandler^ OnPulse;

    void SaveWorld();
    void Shutdown();
    void MakeCounselor(void *PlayerObjectTarget, int CounType);
    void UnmakeCounselor(void *PlayerObjectTarget);
    void OpenInfoWindow(Serial gmserial, Serial playerserial);
    Location getLocation(Serial itemSerial);
    int setHue(Serial itemSerial, short hue);
    int getQuantity(Serial serial);
    int getWeight(Serial serial);
    int setOverloadedWeight(Serial serial, int weight);
    bool deleteObject(Serial serial);
};

namespace UODemo
{
    public ref class Core : public IUOServer
    {
        static Assembly^ aSharpkick;

    public:
        Core();
        ~Core();

        OnPulseEventHandler^ PulseHandler;

        static void InvokeGlobalOnPulse();
        static event OnPulseEventHandler^ GlobalOnPulse;

        static void Core::InitializeSharpkick();

        void InvokeOnPulse();
        virtual event OnPulseEventHandler^ OnPulse;

        virtual void SaveWorld();
        virtual void Shutdown();
        virtual void MakeCounselor(void *PlayerObjectTarget, int CounType);
        virtual void UnmakeCounselor(void *PlayerObjectTarget);
        virtual void OpenInfoWindow(Serial gmserial, Serial playerserial);
        virtual Location getLocation(Serial itemSerial);
        virtual int setHue(Serial itemSerial, short hue);
        virtual int getQuantity(Serial serial);
        virtual int getWeight(Serial serial);
        virtual int setOverloadedWeight(Serial serial, int weight);
        virtual bool deleteObject(Serial serial);

    };
}

