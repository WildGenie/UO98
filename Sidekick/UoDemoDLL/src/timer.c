// UO98: UoDemo Server
// Author: Derrick
// 03/12/2011
// Hooks pulses

//-=-=-=-=-
void Initialize_timer(void);
//-=-=-=-=-

#define ptFUNC_OnPulse 0x00004D8A9A	// Address of their time handler
void (*FUNC_OnPulse)(int) = NULL;	// their time handler (called every 250ms tick)

PATCHINFO PI_OnPulse =
{
 0x004D83AD, //  call    FUNC_OnPulse
 5, {0xE8, 0xE8, 0x06, 0x00, 0x00},
 5, {0xE8, 0x00, 0x00, 0x00, 0x00},
};

void __cdecl OnPulse(int _this)
{
	_asm pusha
	if(my_OnPulse)
		my_OnPulse();
	_asm popa
	FUNC_OnPulse(_this);
}

void Initialize_timer()
{
	SetRel32_AtPatch(&PI_OnPulse, OnPulse);
	Patch(&PI_OnPulse);
	FUNC_OnPulse=(void*)ptFUNC_OnPulse;
}
