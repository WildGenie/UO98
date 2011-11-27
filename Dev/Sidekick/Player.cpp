#include "Player.h"

#pragma unmanaged

typedef void (_cdecl *FUNCPTR_SendSystemMessage)(void* , const char*);

FUNCPTR_SendSystemMessage	_SendSystemMessage;
FUNCPTR						_MakeGameMaster;
FUNCPTR						_UnmakeGameMaster;
FUNCPTR						_IsGameMaster;
FUNCPTR						_OpenBank;

#include "RegisterImportTemplate.h"
void InitPlayer(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_SendSystemMessage",_SendSystemMessage);
	RegisterImport(dll_handle,"_MakeGameMaster",_MakeGameMaster);
	RegisterImport(dll_handle,"_UnmakeGameMaster",_UnmakeGameMaster);
	RegisterImport(dll_handle,"_IsGameMaster",_IsGameMaster);
	RegisterImport(dll_handle,"_OpenBank",_OpenBank);
}

extern "C"
{
	void _declspec(dllexport) APIENTRY SendSystemMessage(void *player, const char *message)
	{
		if(_SendSystemMessage) _SendSystemMessage(player, message); 
	}

	int _declspec(dllexport) APIENTRY MakeGameMaster(void* player)
	{
		if(_MakeGameMaster) return _MakeGameMaster(player); 
		return 0;
	}

	int _declspec(dllexport) APIENTRY UnmakeGameMaster(void* player)
	{
		if(_UnmakeGameMaster) return _UnmakeGameMaster(player); 
		return 0;
	}

	int _declspec(dllexport) APIENTRY IsGameMaster(void* player)
	{
		if(_IsGameMaster) return _IsGameMaster(player); 
		return 0;
	}

	int _declspec(dllexport) APIENTRY OpenBank(void* mobile, void* ShowTo)
	{
		if(_OpenBank) return _OpenBank(mobile, ShowTo); 
		return 0;
	}
}
