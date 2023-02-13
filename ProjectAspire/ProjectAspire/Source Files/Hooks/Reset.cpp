#include "../../Header Files/Hooks.h"

long __stdcall Hooks::Reset( IDirect3DDevice9* device, void* params )
{
	g_globals->renderer->Release();

	static const auto original = oReset( device, params );

	g_globals->renderer->Create();

	return original;
}