
void (*OnTestResult)(bool passed, char *message, ...)= NULL;

void _declspec(dllexport) setHandler_OnTestResult(void* resultFunc)
{
	OnTestResult=resultFunc;
  OnTestResult(true, "Test Result Handler %s!","Initialized");
}

LocationObject location;
LocationObject locationPlus1;
LocationObject locationPlus8;

void InitTestLocations(void);

#include "Tests_Lists.c"
#include "Tests_World.c"
#include "Tests_ObjectVars.c"
#include "Tests_ObjectScripts.c"

void Tests_Lists_Execute(void);
void Tests_World_Execute(void);
void Tests_ObjectVars_Execute(void);
void Tests_ObjectScripts_Execute(void);

void __cdecl _declspec(dllexport) DoTests()
{
  Tests_Lists_Execute();
  Tests_World_Execute();
  Tests_ObjectVars_Execute();
  Tests_ObjectScripts_Execute();
}

void InitTestLocations()
{
  location.X=33;
  location.Y=20;
  location.Z=0;

  locationPlus1.X=location.X+1;
  locationPlus1.Y=location.Y+0;
  locationPlus1.Z=location.Z;

  locationPlus8.X=location.X+8;
  locationPlus8.Y=location.Y+2;
  locationPlus8.Z=location.Z;
}


