
#define pCOMMAND__oprlist_cli 0x0040E863
void __cdecl (*COMMAND__oprlist_cli)(LocationObject* locationResult, ListObject* List, unsigned int index) = pCOMMAND__oprlist_cli;
void __cdecl _declspec(dllexport) List_GetLocation(LocationObject* locationResult, ListObject* List, unsigned int index)
{
	COMMAND__oprlist_cli(locationResult, List, index);
}

#define pCOMMAND__oprlist__ili 0x0040E733
int __cdecl (*COMMAND__oprlist__ili)(ListObject* List, unsigned int index) = pCOMMAND__oprlist__ili;
int __cdecl _declspec(dllexport) List_GetInteger(ListObject* List, unsigned int index)
{
	return COMMAND__oprlist__ili(List, index);
}

// List_GetList allocates and returns a new ListObject. Should implement FUNC_ListElementObject_Destructor?
#define pCOMMAND__oprlist__lli 0x0040E698
ListObject* __cdecl (*COMMAND__oprlist__lli)(ListObject* List, unsigned int index) = pCOMMAND__oprlist__lli;
ListObject* __cdecl _declspec(dllexport) List_GetList(ListObject* List, unsigned int index)
{
	return COMMAND__oprlist__lli(List, index);
}

// Types of VARTYPE_List, VARTYPE_String, VARTYPE_2 and VARTYPE_Location are copied, VARTYPE_Object and other types above 5 (List) are referenced
#define pCOMMAND_appendToList 0x0040DA53
int __cdecl (*COMMAND_appendToList)(ListObject* List, _VARTYPE ListElementType, int ListElementData) = pCOMMAND_appendToList;
int __cdecl _declspec(dllexport) List_Append(ListObject* List, int ListElementType, int ListElementData)
{
	return COMMAND_appendToList(List, ListElementType, ListElementData);
}

#define pCOMMAND_isInList 0x0040E006
int __cdecl (*COMMAND_isInList)(ListObject *List, _VARTYPE ValueType, int ValueOrRef) = pCOMMAND_isInList;
int __cdecl _declspec(dllexport) List_Contains(ListObject *List, _VARTYPE ValueType, int ValueOrRef)
{
	return COMMAND_isInList(List, ValueType, ValueOrRef);
}

#define pCOMMAND_removeItem 0x0040E01B
int __cdecl (*COMMAND_removeItem)(ListObject* List, unsigned int index) = pCOMMAND_removeItem;
int __cdecl _declspec(dllexport) List_RemoveAt(ListObject* List, unsigned int index)
{
	return COMMAND_removeItem(List, index);
}

#define pCOMMAND_removeSpecificItem 0x0040E06F
int __cdecl (*COMMAND_removeSpecificItem)(ListObject *List, _VARTYPE ValueType, int ValueOrRef) = pCOMMAND_removeSpecificItem;
int __cdecl _declspec(dllexport) List_RemoveSpecificItem(ListObject *List, _VARTYPE ValueType, int ValueOrRef)
{
	return COMMAND_removeSpecificItem(List, ValueType, ValueOrRef);
}

#define pCOMMAND_clearList 0x0040E084
int __cdecl (*COMMAND_clearList)(ListObject *List) = pCOMMAND_clearList;
int __cdecl _declspec(dllexport) List_Clear(ListObject *List)
{
	return COMMAND_clearList(List);
}
