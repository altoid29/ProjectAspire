#include "../../Header Files/Hooks.h"

bool __fastcall Hooks::IsHLTV( void* ecx, void* edx )
{
	// Enable server-radar.
	if ( Settings::Misc::radar )
	{
		if ( g_interfaces->Engine->IsInGame() && g_globals->localPlayer && _ReturnAddress() == Offsets::isHLTV && !g_globals->shouldUnload )
			return true;
	}

	return oIsHLTV( ecx, edx );
}