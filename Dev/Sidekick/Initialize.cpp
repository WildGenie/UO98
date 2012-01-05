#include <stdio.h>
#include <io.h>
#include <iostream>
#include "Interop.h"

#include "CoreEvents.h"

#pragma unmanaged

#include "RegisterImportTemplate.h"

#include "Packets.h"
#include "ObjVars.h"
#include "ObjectScripts.h"

#include "TestsMain.h"

//-=-=-=-=
void Initialize_packets(void);
void Initialize_scommand(void);
void Initialize_timer();
void Initialize_logging(void);
void Initialize_misc(void);
void Initialize_jit(void);
//-=-=-=-=


void InitializeInterop();

bool isRunUODemoDLLTestMode();
void RunTests();
void EnterNormalRuntimeMode();

bool isRunTestMode()
{
    char* envTest=getenv("UODemoDLLTest");
    return envTest!=NULL;
}

void Initialize()
{
    Initialize_scommand();
    Initialize_logging();
    Initialize_misc();
    Initialize_jit();

    if(isRunTestMode())
        RunTests();
    else
        EnterNormalRuntimeMode();
}

void Uninitialize()
{
}

void RunTests()
{
    InitializeTests();
}

void EnterNormalRuntimeMode()
{
    Initialize_timer();
    Initialize_packets();
    puts("Sidekick Initialized.");
    puts("Please wait while the world loads...");
}


