
#define pFUNC_SendInfoWindowOrDoPlayerShadow 0x0045EE75

void __stdcall (* FUNC_SendInfoWindowOrDoPlayerShadow)(void* ARG_InfoStruct, int unused) = pFUNC_SendInfoWindowOrDoPlayerShadow;
void __cdecl _declspec(dllexport) SendInfoWindowOrDoPlayerShadow(void* InfoStruct)
{
    int unused=0;
    FUNC_SendInfoWindowOrDoPlayerShadow(InfoStruct, unused);
}