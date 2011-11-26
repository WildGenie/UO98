#include "World.h"

#pragma unmanaged

typedef void (_cdecl *FUNCPTR_createGlobalObjectAt)(int, void*);
typedef int (_cdecl *FUNCPTR_getFirstObjectOfType)(void*, int);
typedef int (_cdecl *FUNCPTR_getNextObjectOfType)(void*, int, int);

FUNCPTR									          _ConvertSerialToObject;
FUNCPTR_createGlobalObjectAt			_createGlobalObjectAt;
FUNCPTR_getFirstObjectOfType			_getFirstObjectOfType;
FUNCPTR_getNextObjectOfType				_getNextObjectOfType;

#include "RegisterImportTemplate.h"
void InitWorld(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_ConvertSerialToObject",_ConvertSerialToObject);
	RegisterImport(dll_handle,"_createGlobalObjectAt",_createGlobalObjectAt);
	RegisterImport(dll_handle,"_getFirstObjectOfType",_getFirstObjectOfType);
	RegisterImport(dll_handle,"_getNextObjectOfType",_getNextObjectOfType);
}

extern "C"
{
  int _declspec(dllexport) APIENTRY ConvertSerialToObject(int serial)
	{
		if(_ConvertSerialToObject) 
      return _ConvertSerialToObject(serial); 
    else
		  return 0;
	}

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
}
