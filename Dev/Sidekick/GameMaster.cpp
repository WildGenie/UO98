#include "Commands.h"

#pragma unmanaged

#define pFUNC_SendInfoWindowOrDoPlayerShadow 0x0045EE75
typedef void (_cdecl *FUNCPTR_SendInfoWindowOrDoPlayerShadow)(void* InfoStruct, int unused);
FUNCPTR_SendInfoWindowOrDoPlayerShadow	FUNC_SendInfoWindowOrDoPlayerShadow = (FUNCPTR_SendInfoWindowOrDoPlayerShadow)pFUNC_SendInfoWindowOrDoPlayerShadow;
void SendInfoWindowOrDoPlayerShadow(void* InfoStruct)
{
    int unused=0;
    FUNC_SendInfoWindowOrDoPlayerShadow(InfoStruct, unused);
}

void SendInfoWindowToGodClient(Serial beholder, Serial beheld)
{
  PlayerObject* BeholderObject;
  PlayerObject* BeheldObject;

  struct_PlayerHelpInfoArgs args;

  BeholderObject=(PlayerObject*)ConvertSerialToObject(beholder);
  if(IsPlayerObject(BeholderObject))
  {
    BeheldObject=(PlayerObject*)ConvertSerialToObject(beheld);
    if(!IsPlayerObject(BeheldObject))
    {
      SendSystemMessage(BeholderObject, "That object is not a player.");
    }
    else
    {
        args.mode = 2;
        args.field_1=0;
        args.gm_serial = BeholderObject->MyOwnSerial;
        args.player_serial = BeheldObject->MyOwnSerial;
        args.locationObject = BeheldObject->Location;
        args.account_number = BeheldObject->account_number;
        args.character_number = (__int8)BeheldObject->character_number;

        strcpy(args.CharacterRealName, (const char*)BeheldObject->RealName);
 
        SendInfoWindowOrDoPlayerShadow(&args);

        SendSystemMessage(BeholderObject, "That object is a player.");
    }
  }
}

