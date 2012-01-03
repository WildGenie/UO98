#include "stdafx.h"

#pragma unmanaged

#define pFUNC_SendInfoWindowOrDoPlayerShadow 0x0045EE75

typedef void (_cdecl *FUNCPTR_SendInfoWindowOrDoPlayerShadow)(void* InfoStruct, int unused);
FUNCPTR_SendInfoWindowOrDoPlayerShadow	_SendInfoWindowOrDoPlayerShadow = (FUNCPTR_SendInfoWindowOrDoPlayerShadow)pFUNC_SendInfoWindowOrDoPlayerShadow;

extern "C"
{
    void _declspec(dllexport) APIENTRY SendInfoWindowOrDoPlayerShadow(void* InfoStruct)
    {
        int unused=0;
        _SendInfoWindowOrDoPlayerShadow(InfoStruct, unused);

    }
}
