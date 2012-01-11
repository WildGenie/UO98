// A Managed to Native Proxy class for API commands.

#pragma once

#include "Classes_Managed.h"

public interface class IUOServer
{
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
    public:
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

