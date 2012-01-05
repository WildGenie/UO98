#pragma once

extern "C"
{
    int _declspec(dllexport) APIENTRY createGlobalObjectAt(int ItemID, void* Location);
    int _declspec(dllexport) APIENTRY getFirstObjectOfType(void* location, int itemId);
    int _declspec(dllexport) APIENTRY getNextObjectOfType(void* location, int itemId, int lastItemSerial);
    int _declspec(dllexport) APIENTRY getNumAllObjectsInRangewithFlags(LocationObject* location, int range, unsigned int flags);
    void _declspec(dllexport) APIENTRY getObjectsInRangeWithFlags(void* resultList, LocationObject* location, int range, unsigned int flags);
    void _declspec(dllexport) APIENTRY getObjectsAt(void* resultList, LocationObject* location);

    int _declspec(dllexport) APIENTRY IsItem(void* object);
    int _declspec(dllexport) APIENTRY IsMobile(void* object);
    int _declspec(dllexport) APIENTRY IsPlayer(void* object);
}
