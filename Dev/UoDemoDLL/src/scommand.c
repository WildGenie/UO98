// UO98: UoDemo Server
// Author: Batlin
// 09/14/2010
// Provides in game commands via DoSCommand
// Requires GMCheat script

//-=-=-=-=-
void Initialize_scommand(void);
//-=-=-=-=-

typedef void (__cdecl *SCOMMAND_FUNC)(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1);

// DO NOT CHANGE THE DEFINITION OF THIS STRUCTURE, DOING SO WILL CRASH THE CORE
typedef struct SCOMMAND_DEF
{
  const char *Command;
  SCOMMAND_FUNC Function;
} SCOMMAND_DEF;

// NOTE: it's your responsibility to avoid buffer-overruns in TargetBuffer!
//       the demo is old-school and doesn't handle those well :)
const char *ExtractString_HandleQuotes(const char *Command, char *TargetBuffer)
{
  __asm
  {
    // Time to go inside uodemo.exe and call the function that does the real magic
    // (this is easier than reimplementing our own ExtractString function)
    // (but then again, by implementing our own we could get rid of the buffer-overrun problem)
    push TargetBuffer
    push Command
    mov eax, 0x4475AB
    call eax
    add esp, 8
  }
  return (const char*) _EAX;
}

void __cdecl Command_Test(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1)
{
  SendSystemMessage(Player, "doSCommand(...): Test OK!");
}

void __cdecl Command_MakeCounselor(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1)
{
  char buffer[512];

  PlayerObject *Target;
  unsigned int TargetSerial;
  int Type;

  Command = ExtractString_HandleQuotes(Command, buffer);
  if(strcmpi(buffer, "me") == 0)
  {
    TargetSerial = PlayerSerial;
  }
  else
  {
    TargetSerial = (unsigned int) atoi(buffer);
  }
  if(TargetSerial == 0)
  {
    SendSystemMessage(Player, "Usage: coun me/<serial> [type]!");
    return;
  }

  /*Command =*/ ExtractString_HandleQuotes(Command, buffer);
  Type = atoi(buffer);

  Target = ConvertSerialToObject(TargetSerial);
  if((Target == NULL) || !IsPlayerObject(Target))
  {
    SendSystemMessage(Player, "coun: You must target a player!");
    return;
  }

  // Time to go inside uodemo.exe and call the function that does the real magic
  MakeCounselor(Target, Type);

  if(Target != Player)
  {
    SendSystemMessage(Target, "You've become a counselor!");
    SendSystemMessage(Player, "You've made him/her a counselor!");
  }
  else
    SendSystemMessage(Player, "You've made yourself a counselor!");
}

void __cdecl Command_UnmakeCounselor(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1)
{
  char buffer[512];

  PlayerObject *Target;
  unsigned int TargetSerial;

  /*Command =*/ ExtractString_HandleQuotes(Command, buffer);
  if(strcmpi(buffer, "me") == 0)
  {
    TargetSerial = PlayerSerial;
  }
  else
  {
    TargetSerial = (unsigned int) atoi(buffer);
  }
  if(TargetSerial == 0)
  {
    SendSystemMessage(Player, "Usage: ucoun me/<serial>!");
    return;
  }

  Target = ConvertSerialToObject(TargetSerial);
  if((Target == NULL) || !IsPlayerObject(Target))
  {
    SendSystemMessage(Player, "ucoun: You must target a player!");
    return;
  }

  // Time to go inside uodemo.exe and call the function that does the real magic
  UnmakeCounselor(Target);

  if(Target != Player)
  {
    SendSystemMessage(Target, "You've lost your counselor powers!");
    SendSystemMessage(Player, "You've unmade him/her a counselor!");
  }
  else
    SendSystemMessage(Player, "You've unmade yourself a counselor!");
}

void __cdecl Command_SaveWorld(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1)
{
  SendSystemMessage(Player, "Saving world...");
  // Time to go inside uodemo.exe and call the function that does the real magic
  SaveWorld();
  SendSystemMessage(Player, "World saved!");
}

void __cdecl Command_ShutdownServer(PlayerObject *Player, unsigned int PlayerSerial, const char *Command, int AlwaysMinus1)
{
    // Time to go inside uodemo.exe and call the function that does the real magic
	ShutdownServer();
}

// This function is and must be declared naked!!!
// Do not modify this function unless you know enough assembler
// And also unless you know deep down in your heart what "naked" functions are
int __declspec(naked) PreventSpeechBroadcast()
{
  __asm
  {
    xor eax, eax
    ret
  }
  return _EAX; // Gets ignored but satifies the compiler
}

SCOMMAND_DEF MySCommandTable[] = 
{
  {"test", Command_Test},
  {"coun", Command_MakeCounselor},
  {"ucoun", Command_UnmakeCounselor},
  {"save", Command_SaveWorld},
  {"shutdown", Command_ShutdownServer},
};

PATCHINFO PI_PreventSpeechBroadcast =
{
 0x493C49,
 5, {0xE8, 0x96, 0x2A, 0xFC, 0xFF},
 5, {0xE8, 0x00, 0x00, 0x00, 0x00},
};

void Initialize_scommand()
{
    // Prepare the patches
    SetAbs32_AtRelPatch(&PI_SCommandTable_C1, 3, (void *) &MySCommandTable[0].Command);
    SetAbs32_AtRelPatch(&PI_SCommandTable_C2, 3, (void *) &MySCommandTable[0].Command);
    SetAbs32_AtRelPatch(&PI_SCommandTable_F1, 3, (void *) &MySCommandTable[0].Function);
    SetAbs32_AtRelPatch(&PI_SCommandTable_F2, 3, (void *) &MySCommandTable[0].Function);
    SetRel32_AtPatch(&PI_PreventSpeechBroadcast, PreventSpeechBroadcast);

    // Apply the patches
    Patch(&PI_SCommandTable_C1);
    Patch(&PI_SCommandTable_C2);
    Patch(&PI_SCommandTable_F1);
    Patch(&PI_SCommandTable_F2);
    Patch(&PI_PreventSpeechBroadcast);
}
