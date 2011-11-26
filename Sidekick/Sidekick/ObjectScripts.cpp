#include "ObjectScripts.h"

#pragma unmanaged

typedef char* (_cdecl *FUNCPTR_addScript)(int, const char*, int);
typedef int (_cdecl *FUNCPTR_hasScript)(int, const char*);
typedef int (_cdecl *FUNCPTR_detachScript)(int, const char*);

FUNCPTR_addScript     _addScript;
FUNCPTR_hasScript     _hasScript;
FUNCPTR_detachScript  _detachScript;

#include "RegisterImportTemplate.h"
void InitObjectScripts(HMODULE dll_handle)
{
	RegisterImport(dll_handle,"_addScript",_addScript);
	RegisterImport(dll_handle,"_hasScript",_hasScript);
	RegisterImport(dll_handle,"_detachScript",_detachScript);
}

extern "C"
{
	char _declspec(dllexport) *APIENTRY addScript(int serial, const char* scriptName, int executeCreation)
	{
		if(_addScript) 
      return _addScript(serial, scriptName, executeCreation);
    else
		  return 0;
	}

 	bool _declspec(dllexport) APIENTRY hasScript(int serial, const char* scriptName)
	{
		if(_hasScript) 
      return _hasScript(serial, scriptName);
    else
		  return 0;
	}

 	bool _declspec(dllexport) APIENTRY detachScript(int serial, const char* scriptName)
	{
		if(_detachScript) 
      return _detachScript(serial, scriptName);
    else
		  return 0;
	}

}