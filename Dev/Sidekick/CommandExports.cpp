#include <stdio.h>
#include "CoreEvents.h"

#pragma unmanaged

extern "C"
{
    #define FUNC_WriteDynamic0 0x4C8A5C
    void _declspec(dllexport) APIENTRY SaveWorld()
    {
        puts("Saving world...");
        __asm
        {
            mov eax, FUNC_WriteDynamic0
            call eax
        }
        puts("World saved!");
  
        OnAfterSave();
    }

    #define GLOBAL_TerminateServerFlag 0x6999E0
    void _declspec(dllexport) APIENTRY ShutdownServer()
    {
      __asm
      {
        mov edx, GLOBAL_TerminateServerFlag
        mov dword ptr [edx], 1
      }
    }
}

