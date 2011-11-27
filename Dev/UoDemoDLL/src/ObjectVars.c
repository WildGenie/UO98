#include "classes.h"

#define pFUNC_SetWomVar 0x004C8EEB
void __cdecl (*FUNC_SetWomVar)(ItemObject *ARG_subject, const char *ARG_VarName, _VARTYPE ARG_VarType, int ARG_ValueOrPointer) = pFUNC_SetWomVar;

int __cdecl _declspec(dllexport) setObjVarInt(int serial, const char *varName, int value)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
		FUNC_SetWomVar(subject, varName, 0, value);
    return 1;
  }
	return 0;
}

int __cdecl _declspec(dllexport) setObjVarString(int serial, const char *varName, const char* value)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
		{
      FUNC_SetWomVar(subject, varName, VARTYPE_String, (int)value);
      return 1;
    }
	return 0;
}

int __cdecl _declspec(dllexport) setObjVarLocation(int serial, const char *varName, void* location)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
		FUNC_SetWomVar(subject, varName, VARTYPE_Location, (int)location);
    return 1;
  }
	return 0;
}

#define pFUNC_ItemObject_RemoveObjVar 0x004CDEAC
void __cdecl _declspec(dllexport) removeObjVar(int serial, const char *varName)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
 		_asm
		{
		   push varName
		   mov ecx, subject
		   mov eax, pFUNC_ItemObject_RemoveObjVar
		   call eax
		}
  }
}

#define pFUNC_ItemObject_HasObjVarOfType 0x004CDCD4
bool __cdecl _declspec(dllexport) hasObjVarOfType(int serial, const char *varName, _VARTYPE varType)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
 		_asm
		{
		   push varType
		   push varName
		   mov ecx, subject
		   mov eax, pFUNC_ItemObject_HasObjVarOfType
		   call eax
		}
    return _EAX;
  }
	return 0;
}

#define pFUNC_ItemObject_FindAndGetObjVarValue 0x004CDD01
int __cdecl _declspec(dllexport) getObjVarInt(int serial, const char *varName)
{
  if(hasObjVarOfType(serial, varName, VARTYPE_Integer))
  {
	  ItemObject *subject = ConvertSerialToObject(serial);
	  if( (IsAnyItem(subject)||IsAnyMobile(subject)) )
    {
      int result;
      int* pResult=&result;

 		  _asm
		  {
		     push pResult
		     push varName
		     mov ecx, subject
		     mov eax, pFUNC_ItemObject_FindAndGetObjVarValue
		     call eax
		  }
      return result;
    }
  }
	return 0;
}

#define pFUNC_ItemObject_GetObjVarString 0x004CDD7C
char* __cdecl _declspec(dllexport) getObjVarString(int serial, const char *varName)
{
  if(hasObjVarOfType(serial, varName, VARTYPE_String))
  {
	  ItemObject *subject = ConvertSerialToObject(serial);
	  if( (IsAnyItem(subject)||IsAnyMobile(subject)) )
    {
 		  _asm
		  {
		     push varName
		     mov ecx, subject
		     mov eax, pFUNC_ItemObject_GetObjVarString
		     call eax
		  }
      return *(char**)_EAX; // StringObject->StringMemory
    }
  }
	return 0;
}

#define pFUNC_ItemObject_GetObjVarLocation 0x004CDD53
bool __cdecl _declspec(dllexport) getObjVarLocation(int serial, const char *varName, LocationObject* locationResult)
{
  if(hasObjVarOfType(serial, varName, VARTYPE_Location))
  {
	  ItemObject *subject = ConvertSerialToObject(serial);
	  if( (IsAnyItem(subject)||IsAnyMobile(subject)) )
    {
 		  _asm
		  {
		     push locationResult
		     push varName
		     mov ecx, subject
		     mov eax, pFUNC_ItemObject_GetObjVarLocation
		     call eax
		  }
      return _EAX;
    }
  }
	return 0;
}