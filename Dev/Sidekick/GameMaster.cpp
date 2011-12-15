#pragma unmanaged

typedef void (_cdecl *FUNCPTR_SendInfoWindowOrDoPlayerShadow)(void* InfoStruct);

FUNCPTR_SendInfoWindowOrDoPlayerShadow	_SendInfoWindowOrDoPlayerShadow;

#include "RegisterImportTemplate.h"
void InitGameMaster(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_SendInfoWindowOrDoPlayerShadow",_SendInfoWindowOrDoPlayerShadow);
}

extern "C"
{
    void _declspec(dllexport) APIENTRY SendInfoWindowOrDoPlayerShadow(void* InfoStruct)
    {
        return; // TODO: AccessViolationException....
	    if(_SendInfoWindowOrDoPlayerShadow) _SendInfoWindowOrDoPlayerShadow(InfoStruct); 
    }
}
