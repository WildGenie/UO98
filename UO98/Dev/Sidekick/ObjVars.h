#pragma once

extern "C"
{
  int _declspec(dllexport) APIENTRY setObjVarInt(int serial, const char *varName, int value);
  int _declspec(dllexport) APIENTRY setObjVarString(int serial, const char *varName, const char* value);
  int _declspec(dllexport) APIENTRY setObjVarLocation(int serial, const char *varName, void* location);
  void _declspec(dllexport) APIENTRY removeObjVar(int serial, const char *varName);
  int _declspec(dllexport) APIENTRY hasObjVarOfType(int serial, const char *varName, int varType);
  int _declspec(dllexport) APIENTRY getObjVarInt(int serial, const char *varName);
  char _declspec(dllexport) *APIENTRY getObjVarString(int serial, const char *varName);
  int _declspec(dllexport) APIENTRY getObjVarLocation(int serial, const char *varName, void* locationResult);
}