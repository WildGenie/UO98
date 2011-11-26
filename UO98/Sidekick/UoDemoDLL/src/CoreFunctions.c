
//-=-=-=-=-
void __cdecl SaveWorld(void);
void __cdecl ShutdownServer(void);
void __cdecl MakeCounselor(PlayerObject *Target, int Type);
void __cdecl UnmakeCounselor(PlayerObject *Target);

//-=-=-=-=-

void __cdecl _declspec(dllexport) SaveWorld()
{
  puts("Saving world...");
  __asm
  {
    mov eax, 0x4C8A5C
    call eax
  }
  puts("World saved!");
  
  if(my_OnAfterSave)	// invoke OnAfterSave event if set
	  my_OnAfterSave();
}

#define GLOBAL_TerminateServerFlag 0x6999E0
void __cdecl _declspec(dllexport) ShutdownServer()
{
  __asm
  {
    mov edx, GLOBAL_TerminateServerFlag
    mov dword ptr [edx], 1
  }
}

#define GLOBAL_HelpEngineObject 0x6982D8
void __cdecl _declspec(dllexport) MakeCounselor(PlayerObject *Target, int Type)
{
  __asm
  {
    push Type
    push Target
    mov ecx, GLOBAL_HelpEngineObject
    mov eax, 0x44E039
    call eax
  }
}

void __cdecl _declspec(dllexport) UnmakeCounselor(PlayerObject *Target)
{
  __asm
  {
    push Target
    mov ecx, GLOBAL_HelpEngineObject
    mov eax, 0x44DEE6
    call eax
  }
}

