#include <stdio.h>
#include "Interop.h"

template<typename T>
bool RegisterImport(HMODULE dll_handle, char* name, T &function)
{
	if(dll_handle)
	{
		function = (T)GetProcAddress(dll_handle, name);
		if (function) return true;
		printf("Error: could not find address of function %s\n", name);
	}
	return false;
}
