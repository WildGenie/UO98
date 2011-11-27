#include "Interop.h"
#include "ItemObject.h"

#pragma unmanaged

typedef int  (_cdecl *FUNCPTR_setHue)(int, short);
typedef int  (_cdecl *FUNCPTR_setOverloadedWeight)(int, int);
typedef void (_cdecl *FUNCPTR_getLocation)(void*, int);
typedef int  (_cdecl *FUNCPTR_getValueByFunctionFromObject)(int, void*, const char*);
typedef int  (_cdecl *FUNCPTR_deleteObject)(int);

FUNCPTR_setHue							          _setHue;
FUNCPTR_getValueByFunctionFromObject	_getValueByFunctionFromObject;
FUNCPTR_getLocation						        _getLocation;
FUNCPTR_setOverloadedWeight				    _setOverloadedWeight;
FUNCPTR_deleteObject				          _deleteObject;

#include "RegisterImportTemplate.h"
void InitItemObject(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_getLocation",_getLocation);
	RegisterImport(dll_handle,"_setHue",_setHue);
	RegisterImport(dll_handle,"_setOverloadedWeight",_setOverloadedWeight);
	RegisterImport(dll_handle,"_getValueByFunctionFromObject",_getValueByFunctionFromObject);
	RegisterImport(dll_handle,"_deleteObject",_deleteObject);
}

extern "C"
{
	void _declspec(dllexport) APIENTRY getLocation(void* location, int itemSerial)
	{
		if(_getLocation) _getLocation(location, itemSerial); 
	}

	int _declspec(dllexport) APIENTRY setHue(int serial, short hue)
	{
		if(_setHue) 
      return _setHue(serial, hue); 
		else
      return 0;
	}

	int _declspec(dllexport) APIENTRY getValueByFunctionFromObject(int serial, void* function, const char* debugCallString)
	{
		if(_getValueByFunctionFromObject) 
      return _getValueByFunctionFromObject(serial, function, debugCallString); 
    else
		  throw; // likely risky to assume zero with this one, throw an exception if undefined.
	}

	int _declspec(dllexport) APIENTRY setOverloadedWeight(int serial, int weight)
	{
		if(_setOverloadedWeight) 
      return _setOverloadedWeight(serial, weight); 
    else
		  return 0;
	}

	int _declspec(dllexport) APIENTRY deleteObject(int serial)
	{
		if(_deleteObject) 
      return _deleteObject(serial); 
    else
		  return 0;
	}
}