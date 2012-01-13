#include "UODemo.h"
#include "Commands.h"
#include <stdio.h>

namespace UODemo
{
    Core::Core()
    {
        PulseHandler=gcnew OnPulseEventHandler(this, &Core::InvokeOnPulse);
        GlobalOnPulse += PulseHandler;
        OnAfterSaveHandler=gcnew OnAfterSaveEventHandler(this, &Core::InvokeOnAfterSave);
        GlobalOnAfterSave += OnAfterSaveHandler;
    }

    Core::~Core()
    {
        GlobalOnPulse -= PulseHandler;
    }

    IPackets^ Core::PacketEngine::get()
    {
        return _PacketEngine==nullptr ? (_PacketEngine=gcnew Core_PacketEngine()) : _PacketEngine;
    }

    void Core::InvokeGlobalOnPulse()
    {
        if(!Initialized)
        {
            UODemo::Core::InitializeSharpkick();
            Initialized=true;
        }

        GlobalOnPulse();
    }

    void Core::InvokeGlobalOnAfterSave()
    {
        GlobalOnAfterSave();
    }

    void Core::InvokeOnPulse()
    {
        OnPulse();
    }

    void Core::InvokeOnAfterSave()
    {
        OnAfterSave();
    }

    void Core::SaveWorld() 
    {
        NativeMethods::SaveWorld();      
    }
    
    void Core::Shutdown()  
    {
        NativeMethods::ShutdownServer(); 
    }

    void Core::MakeCounselor(void *PlayerObjectTarget, int CounType)
    {
        NativeMethods::MakeCounselor((PlayerObject*)PlayerObjectTarget, CounType);
    }

    void Core::UnmakeCounselor(void *PlayerObjectTarget)
    {
        NativeMethods::UnmakeCounselor((PlayerObject*) PlayerObjectTarget);
    }

    void Core::OpenInfoWindow(Serial gmserial, Serial playerserial)
    {
        NativeMethods::SendInfoWindowToGodClient(gmserial, playerserial);
    }

    ItemObject* Core::ConvertSerialToItem(Serial serial)
    {
        return (ItemObject*)NativeMethods::ConvertSerialToObject(serial);
    }

    MobileObject* Core::ConvertSerialToMobile(Serial serial)
    {
        MobileObject* mobile = (MobileObject*)NativeMethods::ConvertSerialToObject(serial);
        if(mobile==NULL || !IsMobile(mobile))
            return NULL;
        return mobile;
    }

    PlayerObject* Core::ConvertSerialToPlayer(Serial serial)
    {
        PlayerObject* player = (PlayerObject*)NativeMethods::ConvertSerialToObject(serial);
        if(player==NULL || !IsPlayer(player))
            return NULL;
        return player;
    }

    bool Core::IsItem(void* object)
    {
        return IsItemObject(object);
    }

    bool Core::IsNPC(void* object)
    {
        return IsAnyNPC(object);
    }

    bool Core::IsMobile(void* object)
    {
        return IsAnyMobile(object);
    }

    bool Core::IsPlayer(void* object)
    {
        return IsPlayerObject(object);
    }        

    Location Core::getLocation(Serial itemSerial)
    {
        class_Location Loc;
        NativeMethods::getLocation(&Loc, itemSerial);
        return Loc;
    }

    int Core::setHue(Serial itemSerial, short hue)
    {
        return NativeMethods::setHue(itemSerial, hue);
    }

    #define FUNC_ItemObject_GetQuantity 0x004854F2
    int Core::getQuantity(Serial serial)
    {
        return NativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetQuantity, "getQuantity");
    }

    #define FUNC_ItemObject_GetWeight 0x00489FAB
    int Core::getWeight(Serial serial)
    {
        return NativeMethods::getValueByFunctionFromObject(serial, (void*)FUNC_ItemObject_GetWeight, "getWeight");
    }

    int Core::setOverloadedWeight(Serial serial, int weight)
    {
        return NativeMethods::setOverloadedWeight(serial, weight);
    }

    bool Core::deleteObject(Serial serial)
    {
        return NativeMethods::deleteObject(serial) != 0;
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

    Core_PacketEngine::Core_PacketEngine()
    {
        OnPacketReceivedHandler = gcnew OnPacketReceivedEventHandler(this, &Core_PacketEngine::InvokeOnPacketReceived);
        GlobalOnPacketReceived += OnPacketReceivedHandler;

        OnOutsideRangePacketHandler = gcnew OnOutsideRangePacketEventHandler(this, &Core_PacketEngine::InvokeOnOutsideRangePacket);
        GlobalOnOutsideRangePacket += OnOutsideRangePacketHandler;

        OnPacketSendingHandler = gcnew OnPacketSendingEventHandler(this, &Core_PacketEngine::InvokeOnPacketSending);
        GlobalOnPacketSending += OnPacketSendingHandler;
    }

    Core_PacketEngine::~Core_PacketEngine()
    {
        GlobalOnPacketReceived -= OnPacketReceivedHandler;
    }

    void Core_PacketEngine::InvokeGlobalOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
    {
        GlobalOnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
    }

    void Core_PacketEngine::InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized)
    {
        OnPacketReceived(pSocket, PacketID, PacketSize, IsPacketDynamicSized);
    }

    bool Core_PacketEngine::InvokeGlobalOnOutsideRangePacket(unsigned char* pSocket)
    {
        return GlobalOnOutsideRangePacket(pSocket);
    }

    bool Core_PacketEngine::InvokeOnOutsideRangePacket(unsigned char* pSocket)
    {
        return OnOutsideRangePacket(pSocket);
    }

    void Core_PacketEngine::InvokeGlobalOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
    {
        GlobalOnPacketSending(pSocket, ppData, pDataLen);
    }

    void Core_PacketEngine::InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen)
    {
        OnPacketSending(pSocket, ppData, pDataLen);
    }

    int Core_PacketEngine::SocketObject_SendPacket(void* pSocket, unsigned __int8* PacketData, unsigned int DataSize)
    {
        return NativeMethods::SocketObject_SendPacket(pSocket, PacketData, DataSize);
    }

    void Core_PacketEngine::SocketObject_RemoveFirstPacket(void* pSocket, unsigned int Length)
    {
        NativeMethods::SocketObject_RemoveFirstPacket(pSocket, Length);
    }

    void Core_PacketEngine::ReplaceServerPacketData(unsigned __int8** pData, unsigned int* pDataLen, unsigned __int8* newData, unsigned int newDataLength)
    {
        NativeMethods::ReplaceServerPacketData(pData, pDataLen, newData, newDataLength);
    }

}
