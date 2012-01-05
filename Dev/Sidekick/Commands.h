#pragma once

#include "Classes.h"

extern "C"
{
  void _declspec(dllexport) APIENTRY SaveWorld(void);
  void _declspec(dllexport) APIENTRY ShutdownServer(void);
  void MakeCounselor(PlayerObject *Target, int CounType);
  void UnmakeCounselor(PlayerObject *Target);
}