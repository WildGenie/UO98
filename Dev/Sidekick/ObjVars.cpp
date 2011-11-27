#include "ObjVars.h"

#pragma unmanaged

typedef int  (_cdecl *FUNCPTR_setObjVarInt)(int, const char*, int);
typedef int  (_cdecl *FUNCPTR_setObjVarString)(int, const char*, const char*);
typedef int  (_cdecl *FUNCPTR_setObjVarLocation)(int, const char*, void*);
typedef void (_cdecl *FUNCPTR_removeObjVar)(int, const char*);
typedef bool (_cdecl *FUNCPTR_hasObjVarOfType)(int, const char*, int);
typedef int  (_cdecl *FUNCPTR_getObjVarInt)(int, const char*);
typedef char*(_cdecl *FUNCPTR_getObjVarString)(int, const char*);
typedef bool (_cdecl *FUNCPTR_getObjVarLocation)(int, const char*, void*);

FUNCPTR_setObjVarInt					        _setObjVarInt;
FUNCPTR_setObjVarString					      _setObjVarString;
FUNCPTR_setObjVarLocation				      _setObjVarLocation;
FUNCPTR_removeObjVar				          _removeObjVar;
FUNCPTR_hasObjVarOfType				        _hasObjVarOfType;
FUNCPTR_getObjVarInt				          _getObjVarInt;
FUNCPTR_getObjVarString				        _getObjVarString;
FUNCPTR_getObjVarLocation				      _getObjVarLocation;

#include "RegisterImportTemplate.h"
void InitObjVars(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_setObjVarInt",_setObjVarInt);
	RegisterImport(dll_handle,"_setObjVarString",_setObjVarString);
	RegisterImport(dll_handle,"_setObjVarLocation",_setObjVarLocation);
	RegisterImport(dll_handle,"_removeObjVar",_removeObjVar);
	RegisterImport(dll_handle,"_hasObjVarOfType",_hasObjVarOfType);
	RegisterImport(dll_handle,"_getObjVarInt",_getObjVarInt);
	RegisterImport(dll_handle,"_getObjVarString",_getObjVarString);
	RegisterImport(dll_handle,"_getObjVarLocation",_getObjVarLocation);
}

extern "C"
{
  int _declspec(dllexport) APIENTRY setObjVarInt(int serial, const char *varName, int value)
	{
		if(_setObjVarInt) 
      return _setObjVarInt(serial, varName, value); 
    else
		  return 0;
	}

	int _declspec(dllexport) APIENTRY setObjVarString(int serial, const char *varName, const char* value)
	{
		if(_setObjVarString) 
      return _setObjVarString(serial, varName, value); 
    else
		  return 0;
	}

	int _declspec(dllexport) APIENTRY setObjVarLocation(int serial, const char *varName, void* location)
	{
		if(_setObjVarLocation) 
      return _setObjVarLocation(serial, varName, location); 
    else
		  return 0;
	}

  void _declspec(dllexport) APIENTRY removeObjVar(int serial, const char *varName)
	{
		if(_removeObjVar) 
      _removeObjVar(serial, varName); 
	}

  bool _declspec(dllexport) APIENTRY hasObjVarOfType(int serial, const char *varName, int varType)
	{
		if(_hasObjVarOfType) 
      return _hasObjVarOfType(serial, varName, varType); 
	  else
		  return 0;
	}

  int _declspec(dllexport) APIENTRY getObjVarInt(int serial, const char *varName)
	{
		if(_getObjVarInt) 
      return _getObjVarInt(serial, varName); 
	  else
		  return 0;
  }

  char _declspec(dllexport) *APIENTRY getObjVarString(int serial, const char *varName)
	{
		if(_getObjVarString) 
      return _getObjVarString(serial, varName); 
	  else
		  return 0;
	}

  bool _declspec(dllexport) APIENTRY getObjVarLocation(int serial, const char *varName, void* locationResult)
	{
		if(_getObjVarLocation) 
      return _getObjVarLocation(serial, varName, locationResult); 
	  else
		  return 0;
  }
}
