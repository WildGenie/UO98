#pragma once

#include "stdafx.h"
#include "Classes.h"

extern "C"
{
    char _declspec(dllexport) *APIENTRY addScript(int serial, const char* scriptName, int executeCreation);
    int _declspec(dllexport) APIENTRY hasScript(int serial, const char* scriptName);
    int _declspec(dllexport) APIENTRY detachScript(int serial, const char* scriptName);
}