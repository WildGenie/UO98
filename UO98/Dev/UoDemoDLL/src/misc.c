// UO98: UoDemo Server
// Author: Derrick
// 12/07/2011
// Misc patches that don't fit into any other category.

//-=-=-=-=-
void Initialize_misc(void);
//-=-=-=-=-

// This is a patch for the timing warning regarding DoTick duration. 
// The function expects time in Seconds, but gets time in MS due to a porting bug. 
// This changes the (incorrect) threshold from 10ms to 255 ms
PATCHINFO PI_FixTimingErrors =
{
 0x004682DD,
 8, {0x83, 0xF8, 0x0A, 0x76, 0x24, 0x68, 0x40, 0xB7}, // cmp     eax, 10 ...
 8, {0x83, 0xF8, 0x7F, 0x76, 0x24, 0x68, 0x40, 0xB7}, // cmp     eax, 127 ...
};

PATCHINFO PI_FixTimingMessage =
{
 0x0061B75E,
 12, {"10 seconds."},
 12, {"127 ms....."},
};


void Initialize_misc()
{
	Patch(&PI_FixTimingErrors);
	Patch(&PI_FixTimingMessage);
}