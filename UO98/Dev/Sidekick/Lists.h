#pragma once

#include "stdafx.h"
#include "Classes.h"

void initList(ListObject* list);
void List_DebugPrint(char* description, char* listname, ListObject* list);

extern "C"
{
    void _declspec(dllexport) APIENTRY List_GetLocation(LocationObject* locationResult, ListObject* List, unsigned int index);
    int _declspec(dllexport) APIENTRY List_GetInteger(ListObject* List, unsigned int index);
    ListObject _declspec(dllexport) *APIENTRY List_GetList(ListObject* List, unsigned int index);
    int _declspec(dllexport) APIENTRY List_Append(ListObject* List, _VARTYPE ListElementType, int ListElementData);
    int _declspec(dllexport) APIENTRY List_Contains(ListObject *List, _VARTYPE ValueType, int ValueOrRef);
    int _declspec(dllexport) APIENTRY List_RemoveAt(ListObject* List, unsigned int index);
    int _declspec(dllexport) APIENTRY List_RemoveSpecificItem(ListObject *List, _VARTYPE ValueType, int ValueOrRef);
    int _declspec(dllexport) APIENTRY List_Clear(ListObject *List);
}