// UO98: UoDemo Server
// Author: Derrick
// 12/07/2011
// Misc patches that don't fit into any other category.

//-=-=-=-=-
void Initialize_misc(void);
//-=-=-=-=-

// This is a patch for the timing warning regarding DoTick duration. 
// The function expects time in Seconds, but gets time in MS due to a porting bug. 
// This changes the threshold from 10ms to 255 ms
PATCHINFO PI_FixTimingErrors =
{
 0x004682DD,
 8, {0x83, 0xF8, 0x0A, 0x76, 0x24, 0x68, 0x40, 0xB7}, // cmp     eax, 10
 8, {0x83, 0xF8, 0xFF, 0x76, 0x24, 0x68, 0x40, 0xB7}, // cmp     eax, 255
};

void Initialize_misc()
{
	Patch(&PI_FixTimingErrors);
}