#pragma unmanaged

#include "Classes.h"
#include "World.h"

typedef void (_cdecl *FUNCPTR_createGlobalObjectAt)(int, void*);
typedef int  (_cdecl *FUNCPTR_getFirstObjectOfType)(void*, int);
typedef int  (_cdecl *FUNCPTR_getNextObjectOfType)(void*, int, int);
typedef bool (_cdecl *FUNCPTR_isType)(void*);

FUNCPTR_createGlobalObjectAt			_createGlobalObjectAt;
FUNCPTR_getFirstObjectOfType			_getFirstObjectOfType;
FUNCPTR_getNextObjectOfType				_getNextObjectOfType;

FUNCPTR_isType _IsItem;
FUNCPTR_isType _IsNPC;
FUNCPTR_isType _IsMobile;
FUNCPTR_isType _IsPlayer;

#include "RegisterImportTemplate.h"
void InitWorld(HMODULE dll_handle)
{
    RegisterImport(dll_handle,"_createGlobalObjectAt",_createGlobalObjectAt);
    RegisterImport(dll_handle,"_getFirstObjectOfType",_getFirstObjectOfType);
    RegisterImport(dll_handle,"_getNextObjectOfType",_getNextObjectOfType);

    RegisterImport(dll_handle,"_IsItem",_IsItem);
    RegisterImport(dll_handle,"_IsNPC",_IsNPC);
    RegisterImport(dll_handle,"_IsMobile",_IsMobile);
    RegisterImport(dll_handle,"_IsPlayer",_IsPlayer);
}

extern "C"
{
    void _declspec(dllexport) APIENTRY createGlobalObjectAt(int ItemID, void* Location)
    {
        if(_createGlobalObjectAt) _createGlobalObjectAt(ItemID, Location); 
    }

    int _declspec(dllexport) APIENTRY getFirstObjectOfType(void* location, int itemId)
    {
        if(_getFirstObjectOfType) return _getFirstObjectOfType(location, itemId); 
        return 0;
    }

    int _declspec(dllexport) APIENTRY getNextObjectOfType(void* location, int itemId, int lastItemSerial)
    {
        if(_getNextObjectOfType) return _getNextObjectOfType(location, itemId, lastItemSerial); 
        return 0;
    }

    bool _declspec(dllexport) APIENTRY IsItem(void* object)
    {
        if(_IsItem) return _IsItem(object); 
        return 0;
    }

    bool _declspec(dllexport) APIENTRY IsNPC(void* object)
    {
        if(_IsNPC) return _IsNPC(object); 
        return 0;
    }

    bool _declspec(dllexport) APIENTRY IsMobile(void* object)
    {
        if(_IsMobile) return _IsMobile(object); 
        return 0;
    }

    bool _declspec(dllexport) APIENTRY IsPlayer(void* object)
    {
        if(_IsPlayer) return _IsPlayer(object); 
        return 0;
    }
}
