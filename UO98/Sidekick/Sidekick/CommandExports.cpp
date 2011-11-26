#include <stdio.h>
#include "Interop.h"

#pragma unmanaged

FUNCPTR_Void	_SaveWorld;
FUNCPTR_Void	_ShutdownServer;

#include "RegisterImportTemplate.h"
void InitCommands(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_SaveWorld",_SaveWorld);
	RegisterImport(dll_handle,"_ShutdownServer",_ShutdownServer);
}

extern "C"
{
	void _declspec(dllexport) APIENTRY SaveWorld()
	{
		if(_SaveWorld) _SaveWorld();
	}

	void _declspec(dllexport) APIENTRY ShutdownServer()
	{
		if(_ShutdownServer) _ShutdownServer();
	}
}

