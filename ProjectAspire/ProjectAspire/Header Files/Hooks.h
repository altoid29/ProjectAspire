#pragma once

#include "Include.h"
#include "Utility/SafeCall.h"

#define NEW_HOOK(type, convention, name, ...) type convention name(__VA_ARGS__);
#define NEW_ORIGINAL(name, originalName, function) using name = decltype(&function); inline name originalName = nullptr;

namespace Hooks
{
	NEW_HOOK( void, __fastcall, SceneEnd, void*, void* );
	NEW_ORIGINAL( SceneEndT, oSceneEnd, SceneEnd );

	NEW_HOOK( void, __fastcall, OnScreenSizeChanged, void*, void*, int, int );
	NEW_ORIGINAL( OnScreenSizeChangedT, oOnScreenSizeChanged, OnScreenSizeChanged );

	NEW_HOOK( long, __stdcall, Present, IDirect3DDevice9*, RECT*, const RECT*, HWND, const RGNDATA* );
	NEW_ORIGINAL( PresentT, oPresent, Present );

	NEW_HOOK( long, __stdcall, Reset, IDirect3DDevice9*, void* );
	NEW_ORIGINAL( ResetT, oReset, Reset );

	NEW_HOOK( bool, __fastcall, IsHLTV, void*, void* );
	NEW_ORIGINAL( IsHLTVT, oIsHLTV, IsHLTV );

	inline void Unload()
	{
		// Restore hooked functions.
		g_globals->vmt1->RemoveHook();
		g_globals->vmt2->RemoveHook();
		g_globals->vmt3->RemoveHook();
		g_globals->vmt4->RemoveHook();
		g_globals->vmt5->RemoveHook();

		return;
	}
}