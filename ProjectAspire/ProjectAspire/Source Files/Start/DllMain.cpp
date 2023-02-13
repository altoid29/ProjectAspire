#include "../../Header Files/Include.h"

BOOL APIENTRY DllMain( HMODULE thisModule, uintptr_t attachReason, LPVOID reserved )
{
	if ( attachReason == DLL_PROCESS_ATTACH )
	{
		g_globals->thisModule = thisModule;

		if ( !Hack::Init() )
			return FALSE;
	}

	return TRUE;
}