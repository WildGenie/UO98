#pragma once
#include "Classes.h"

extern "C"
{
    void _declspec(dllexport) APIENTRY getLocation(LocationObject* outLocationObject, int itemSerial);
    int _declspec(dllexport) APIENTRY setHue(int serial, short hue);
    int _declspec(dllexport) APIENTRY getValueByFunctionFromObject(int serial, void* function, const char* debugCallString);
    int _declspec(dllexport) APIENTRY setOverloadedWeight(int serial, int weight);
    int _declspec(dllexport) APIENTRY deleteObject(int serial);
}
