// A Managed to Native Proxy class for API commands.

#pragma once

using namespace System::Reflection;

#include "Classes_Managed.h"

/// <summary>Delegate for EventSink.OnPulse event</summary>
public delegate void OnPulseEventHandler();

/// <summary>Delegate for EventSink.OnAfterSave event</summary>
public delegate void OnAfterSaveEventHandler();

/// <summary>
/// Called when the server receives a valid packet, before it's processed.
/// </summary>
/// <param name="pSocket">The servers socket which received the packet.</param>
/// <param name="PacketID">The packet ID (first byte of Data)</param>
/// <param name="PacketSize">Size of the packet</param>
/// <param name="IsPacketDynamicSized">True if this is a dynamic length packet</param>
public delegate void OnPacketReceivedEventHandler(unsigned __int8* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);

/// <summary>
/// Called when the server receives a packet that it cannot handle.
/// </summary>
/// <param name="pSocket">The servers socket which received the packet.</param>
public delegate bool OnOutsideRangePacketEventHandler(unsigned __int8* pSocket);


/// <summary>
/// Called when the server initiates a send to the client.
/// </summary>
public delegate void OnPacketSendingEventHandler(unsigned __int8* pSocket, unsigned char **ppData, unsigned int *pDataLen);

public interface class IPackets
{
    event OnPacketReceivedEventHandler^ OnPacketReceived;
    event OnOutsideRangePacketEventHandler^ OnOutsideRangePacket;
    event OnPacketSendingEventHandler^ OnPacketSending;

    int SocketObject_SendPacket(void* pSocket, unsigned __int8* PacketData, unsigned int DataSize);
    void SocketObject_RemoveFirstPacket(void* pSocket, unsigned int Length);
    void ReplaceServerPacketData(unsigned __int8** pData, unsigned int* pDataLen, unsigned __int8* newData, unsigned int newDataLength);
};

public interface class IUOServer
{
    property IPackets^ PacketEngine { IPackets^ get(); }

    event OnPulseEventHandler^ OnPulse;
    event OnAfterSaveEventHandler^ OnAfterSave;

    void SaveWorld();
    void Shutdown();

    void MakeCounselor(void *PlayerObjectTarget, int CounType);
    void UnmakeCounselor(void *PlayerObjectTarget);
    void OpenInfoWindow(Serial gmserial, Serial playerserial);

    DynamicItem^ ConvertSerialToItem(Serial serial);
    Mobile^ ConvertSerialToMobile(Serial serial);
    PlayerObject* ConvertSerialToPlayer(Serial serial);
    bool IsItem(void* object);
    bool IsNPC(void* object);
    bool IsMobile(void* object);
    bool IsPlayer(void* object);

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
        static bool Initialized=false;

        static Assembly^ aSharpkick;
        IPackets^ _PacketEngine;

        void InvokeOnPulse();
        void InvokeOnAfterSave();

    public:
        Core();
        ~Core();

        virtual property IPackets^ PacketEngine { IPackets^ get(); }

        OnPulseEventHandler^ PulseHandler;
        OnAfterSaveEventHandler^ OnAfterSaveHandler;

        static void InvokeGlobalOnPulse();
        static event OnPulseEventHandler^ GlobalOnPulse;

        static void InvokeGlobalOnAfterSave();
        static event OnAfterSaveEventHandler^ GlobalOnAfterSave;

        static void Core::InitializeSharpkick();

        virtual event OnPulseEventHandler^ OnPulse;

        virtual event OnAfterSaveEventHandler^ OnAfterSave;

        virtual void SaveWorld();
        virtual void Shutdown();
        virtual void MakeCounselor(void *PlayerObjectTarget, int CounType);
        virtual void UnmakeCounselor(void *PlayerObjectTarget);
        virtual void OpenInfoWindow(Serial gmserial, Serial playerserial);

        virtual DynamicItem^ ConvertSerialToItem(Serial serial);
        virtual Mobile^ ConvertSerialToMobile(Serial serial);
        virtual PlayerObject* ConvertSerialToPlayer(Serial serial);
        virtual bool IsItem(void* object);
        virtual bool IsNPC(void* object);
        virtual bool IsMobile(void* object);
        virtual bool IsPlayer(void* object);

        virtual Location getLocation(Serial itemSerial);
        virtual int setHue(Serial itemSerial, short hue);
        virtual int getQuantity(Serial serial);
        virtual int getWeight(Serial serial);
        virtual int setOverloadedWeight(Serial serial, int weight);
        virtual bool deleteObject(Serial serial);

    };

    public ref class Core_PacketEngine : public IPackets
    {
        OnPacketReceivedEventHandler^ OnPacketReceivedHandler;
        OnOutsideRangePacketEventHandler^ OnOutsideRangePacketHandler;
        OnPacketSendingEventHandler^ OnPacketSendingHandler;

        void InvokeOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
        bool InvokeOnOutsideRangePacket(unsigned char* pSocket);
        void InvokeOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

    public:
        Core_PacketEngine();
        ~Core_PacketEngine();

        static event OnPacketReceivedEventHandler^ GlobalOnPacketReceived;
        static event OnOutsideRangePacketEventHandler^ GlobalOnOutsideRangePacket;
        static event OnPacketSendingEventHandler^ GlobalOnPacketSending;
        
        static void InvokeGlobalOnPacketReceived(unsigned char* pSocket, unsigned char PacketID, unsigned int PacketSize, int IsPacketDynamicSized);
        static bool InvokeGlobalOnOutsideRangePacket(unsigned char* pSocket);
        static void InvokeGlobalOnPacketSending(unsigned char *pSocket, unsigned char **ppData, unsigned int *pDataLen);

        virtual event OnPacketReceivedEventHandler^ OnPacketReceived;
        virtual event OnOutsideRangePacketEventHandler^ OnOutsideRangePacket;
        virtual event OnPacketSendingEventHandler^ OnPacketSending;

        virtual int SocketObject_SendPacket(void* pSocket, unsigned __int8* PacketData, unsigned int DataSize);
        virtual void SocketObject_RemoveFirstPacket(void* pSocket, unsigned int Length);
        virtual void ReplaceServerPacketData(unsigned __int8** pData, unsigned int* pDataLen, unsigned __int8* newData, unsigned int newDataLength);
    };
}

