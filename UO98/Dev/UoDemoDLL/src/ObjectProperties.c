
#define pCOMMAND_setHue 0x004124F3
int __cdecl (*COMMAND_setHue)(int serial, short Hue) = pCOMMAND_setHue;
int __cdecl _declspec(dllexport) setHue(int serial, short Hue)
{
	return COMMAND_setHue(serial, Hue);
}

#define pFUNC_getValueByFunctionFromObject 0x00411319
int __cdecl (*FUNC_getValueByFunctionFromObject)(int serial, void* function, const char* debugCallString) = pFUNC_getValueByFunctionFromObject;
int __cdecl _declspec(dllexport) getValueByFunctionFromObject(int serial, int function, const char* debugCallString)
{
	return FUNC_getValueByFunctionFromObject(serial, (void*)function, debugCallString);
}

#define pFUNC_ItemObject_setOverloadedWeight 0x00490C37
int __cdecl (*FUNC_ItemObject_setOverloadedWeight)(int weight) = pFUNC_ItemObject_setOverloadedWeight;
int __cdecl _declspec(dllexport) setOverloadedWeight(int serial, int weight)
{
	ItemObject *subject = ConvertSerialToObject(serial);
	if(IsAnyItem(subject))
	{
		_asm
		{
		   push weight
		   mov ecx, subject
		   mov eax, pFUNC_ItemObject_setOverloadedWeight
		   call eax
		}
		return _EAX;
	}
	return 0;
}

#define pCOMMAND_getLocation 0x00413884
int __cdecl (*COMMAND_getLocation)(void* ReturnLocationObject, int ItemSerial) = pCOMMAND_getLocation;
void* __cdecl _declspec(dllexport) getLocation(void* ReturnLocationObject, int ItemSerial)
{
	return COMMAND_getLocation(ReturnLocationObject, ItemSerial);
}

#define pCOMMAND_deleteObject 0x00411D3C
int __cdecl (*COMMAND_deleteObject)(int serial)=pCOMMAND_deleteObject;
int __cdecl _declspec(dllexport) deleteObject(int serial)
{
	return COMMAND_deleteObject(serial);
}

