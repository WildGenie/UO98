#pragma once

#include "Classes.h"
#include "stdafx.h"

extern "C"
{
  void _declspec(dllexport) APIENTRY SendSystemMessage(PlayerObject *player, const char *message);
  void _declspec(dllexport) APIENTRY MakeGameMaster(PlayerObject *player);
  void _declspec(dllexport) APIENTRY UnmakeGameMaster(PlayerObject *player);
  int _declspec(dllexport) APIENTRY IsGameMaster(PlayerObject *player);
}