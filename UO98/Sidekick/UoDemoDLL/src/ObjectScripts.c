
#define pFUNC_addScript 0x00425F34
char* __cdecl (*FUNC_addScript)(ItemObject *subject, const char* scriptName) = pFUNC_addScript;
char* __cdecl _declspec(dllexport) addScript(int serial, const char* scriptName)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(subject)
		return FUNC_addScript(subject, scriptName);
	return "Item not found";
}

//#define pFUNC_ItemObject_LoadAndHasScript 0x00490780
#define pGLOBAL_Global148andStringLookupObject 0x00698988
#define pFUNC_ItemObject_HasScript 0x004CDF4B
#define pFUNC_FindScriptAndParseIfNeeded 0x00426106
bool __cdecl _declspec(dllexport) hasScript(int serial, const char *scriptName)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
    _asm
    {
		  push  scriptName
      mov   ecx, offset pGLOBAL_Global148andStringLookupObject
      mov   eax, pFUNC_FindScriptAndParseIfNeeded
      call  eax                                     // Find the script object if exists, pointer returned in EAX
      test  eax, eax
      jz    loc_return                              // Jump to return if script was not found
      push  eax
		  mov   ecx, subject
		  mov   eax, pFUNC_ItemObject_HasScript         // Check for this script on the subject, using the ScriptObject obtained above as the param.
		  call  eax
loc_return:
		}
    return _EAX;                                    // Zero if the script was invalid, or not attached to the subject
  }
	return 0;
}


#define pFUNC_ItemObject_DetachScript 0x004CDDF7
bool __cdecl _declspec(dllexport) detachScript(int serial, const char *scriptName)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject) || IsAnyMobile(subject))
  {
 		_asm
		{
		   push scriptName
		   mov ecx, subject
		   mov eax, pFUNC_ItemObject_DetachScript
		   call eax
		}
    return 1;
  }
	return 0;
}
