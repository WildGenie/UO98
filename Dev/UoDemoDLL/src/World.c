
bool __cdecl _declspec(dllexport) IsItem   (void* object) { return IsItemObject(object); } 
bool __cdecl _declspec(dllexport) IsNPC    (void* object) { return IsAnyNPC(object); }
bool __cdecl _declspec(dllexport) IsMobile (void* object) { return IsAnyMobile(object); }
bool __cdecl _declspec(dllexport) IsPlayer (void* object) { return IsPlayerObject(object); }


#define pCOMMAND_createGlobalObjectAt 0x0041DDE4
int __cdecl (*COMMAND_createGlobalObjectAt)(int ItemID, LocationObject* Location) = pCOMMAND_createGlobalObjectAt;
int __cdecl _declspec(dllexport) createGlobalObjectAt(int ItemID, LocationObject* Location)
{
	return COMMAND_createGlobalObjectAt(ItemID, Location);
}

#define pCOMMAND_getFirstObjectOfType 0x00417B86
int __cdecl (*COMMAND_getFirstObjectOfType)(LocationObject* location, int itemId) = pCOMMAND_getFirstObjectOfType;
int __cdecl _declspec(dllexport) getFirstObjectOfType(LocationObject* location, int itemId)
{
	return COMMAND_getFirstObjectOfType(location, itemId);
}

#define pCOMMAND_getNextObjectOfType 0x00417C0C
int __cdecl (*COMMAND_getNextObjectOfType)(LocationObject* location, int itemId, int lastItemSerial) = pCOMMAND_getNextObjectOfType;
int __cdecl _declspec(dllexport) getNextObjectOfType(LocationObject* location, int itemId, int lastItemSerial)
{
	return COMMAND_getNextObjectOfType(location, itemId, lastItemSerial);
}

// Returns the count of items within the XY range of the location matching the flags
// flags: 0 is not understood and should be avoided
#define pCOMMAND_getNumAllObjectsInRangewithFlags 0x00416BDD
int __cdecl (*COMMAND_getNumAllObjectsInRangewithFlags)(LocationObject* location, int range, unsigned int flags) = pCOMMAND_getNumAllObjectsInRangewithFlags;
int __cdecl _declspec(dllexport) getNumAllObjectsInRangewithFlags(LocationObject* location, int range, unsigned int flags)
{
	return COMMAND_getNumAllObjectsInRangewithFlags(location, range, flags);
}

// Populates the passed list<int> with the serials within the XY range of the location matching the flags
// flags: 0 is not understood and should be avoided
// BUG: Items returned from this function may not be in the requested range. CalculateDistance (which is called by other similar functions) is not performed 
//    on the result from FUNC_MapObject_GetObjectsInRange
#define pCOMMAND_getObjectsInRangeWithFlags 0x00416B16
void __cdecl (*COMMAND_getObjectsInRangeWithFlags)(void* resultList, LocationObject* location, int range, unsigned int flags) = pCOMMAND_getObjectsInRangeWithFlags;
void __cdecl _declspec(dllexport) getObjectsInRangeWithFlags(void* resultList, LocationObject* location, int range, unsigned int flags)
{
	COMMAND_getObjectsInRangeWithFlags(resultList, location, range, flags);
}

// Populates the passed list<int> with the serials at the XY location
#define pCOMMAND_getObjectsAt 0x00417A23
void __cdecl (*COMMAND_getObjectsAt)(void* resultList, LocationObject* location) = pCOMMAND_getObjectsAt;
void __cdecl _declspec(dllexport) getObjectsAt(void* resultList, LocationObject* location)
{
	COMMAND_getObjectsAt(resultList, location);
}
