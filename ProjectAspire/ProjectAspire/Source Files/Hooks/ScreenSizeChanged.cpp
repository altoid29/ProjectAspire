#include "../../Header Files/Hooks.h"

void __fastcall Hooks::OnScreenSizeChanged( void* ecx, void* edx, int old_w, int old_h )
{
	// Handled in Present.
	g_globals->updateScreen = true;

	Hooks::oOnScreenSizeChanged( ecx, edx, old_w, old_h );
}