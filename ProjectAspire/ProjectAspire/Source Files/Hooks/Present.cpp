#include "../../Header Files/Hooks.h"
#include "../../Header Files/Wrapper.h"
#include "../../Header Files/Hacks.h"
#include "../../Header Files/Menu.h"

void DisplayActiveKeybinds()
{
	if ( !Settings::Misc::showActiveKeybinds || !g_globals->localPlayer )
		return;

	auto AddHotkey = []( int hotkey, std::vector<std::string>*vector, std::string nameToAdd ) -> void
	{
		if ( g_globals->GetForegroundWindow() == g_interfaces->Window )
		{
			if ( hotkey > 0 && g_globals->NtUserGetAsyncKeyState( hotkey ) )
			{
				// List doesn't already contain this item, let's add it.
				if ( !( std::find( vector->begin(), vector->end(), nameToAdd ) != vector->end() ) )
					vector->push_back( nameToAdd );
			}
		}
	};

	auto AddHotkeyRequireMasterswitch = []( bool masterswitchValue, int hotkey, std::vector<std::string>* vector, std::string nameToAdd ) -> void
	{
		if ( g_globals->GetForegroundWindow() == g_interfaces->Window )
		{
			if ( masterswitchValue )
			{
				if ( hotkey > 0 && g_globals->NtUserGetAsyncKeyState( hotkey ) )
				{
					// List doesn't already contain this item, let's add it.
					if ( !( std::find( vector->begin(), vector->end(), nameToAdd ) != vector->end() ) )
						vector->push_back( nameToAdd );
				}
			}
		}
	};

	std::vector<std::string>items{};

	AddHotkeyRequireMasterswitch( Settings::Aimbot::enable, Settings::Aimbot::hotkey, &items, "aimbot.enable" );
	AddHotkeyRequireMasterswitch( Settings::Triggerbot::enable, Settings::Triggerbot::hotkey, &items, "triggerbot.enable" );
	AddHotkey( Settings::Misc::panicHotkey, &items, "misc.panic_hotkey" );

	for ( size_t i = 0; i < items.size(); i++ )
	{
		const auto currentItemWidth = g_globals->renderer->TextWidth( g_globals->renderer->tahoma, items[ i ].c_str() );
		Renderer::AddString( g_globals->renderer->tahoma, Renderer::UIColorT( 255, 255, 255, 255 ), 15, g_globals->screenH / 2 + ( i * 15 ), false, items[ i ].c_str(), true );
	}
}

HRESULT __stdcall Hooks::Present( IDirect3DDevice9* device, RECT* src, const RECT* dst, HWND dst_window_override, const RGNDATA* dirty_region )
{
	if ( !g_globals->localPlayer )
		g_globals->localPlayer = g_interfaces->EntList->GetClientEntity( g_interfaces->Engine->GetLocalPlayer() );

	if ( g_globals->shouldUnload )
		Unload();

	// Panic.
	if ( g_globals->NtUserGetAsyncKeyState( Settings::Misc::panicHotkey ) && g_globals->GetForegroundWindow() == g_interfaces->Window )
	{
		Settings::Aimbot::enable = false;
		Settings::Triggerbot::enable = false;
		Settings::ESP::enable = false;
		Settings::Projectiles::enable = false;
		Settings::Misc::revealSpectators = false;
	}

	// Initialize renderer.
	if ( !g_globals->rendererInitialized )
	{
		g_globals->renderer = std::make_unique<CRender>( device );
		g_globals->rendererInitialized = true;
	}

	// Initialize view-matrix.
	{
		static uintptr_t viewMatrix = NULL;
		if ( !viewMatrix )
			viewMatrix = *reinterpret_cast< uintptr_t* >( reinterpret_cast< uintptr_t >( Offsets::viewMatrix ) + 3 ) + 176;

		g_globals->viewMatrix = *reinterpret_cast< VMatrix* >( viewMatrix );
	}

	static bool doneOnce = false;
	if ( !doneOnce )
	{
		// Grab screen size.
		g_globals->spoofedFunctions->GetScreenSize( g_globals->screenW, g_globals->screenH );
		doneOnce = true;
	}

	// Update screen size.
	if ( g_globals->updateScreen )
	{
		g_globals->spoofedFunctions->GetScreenSize( g_globals->screenW, g_globals->screenH );
		g_globals->updateScreen = false;
	}

	// Triggerbot.
	if ( Settings::Triggerbot::delay > 1 )
	{
		static DWORD triggerTick = g_globals->GetTickCount();
		if ( ( DWORD )( triggerTick ) + Settings::Triggerbot::delay <= g_globals->GetTickCount() )
		{
			triggerTick = DWORD( g_globals->GetTickCount() );
			g_triggerbot.Handle();
		}
	}
	else
	{
		g_triggerbot.Handle();
	}

	// Aimbot.
	g_aimbot.Handle();

	g_globals->renderer->Start();
	{
		const bool shouldDraw = Settings::Misc::safeMode ? !g_interfaces->Engine->IsTakingSteamScreenshot() : true;
		if ( shouldDraw )
		{
			// Hud related.
			g_hud.RevealSpectators();

			// ESP related.
			g_esp.Handle();

			// Aimbot related.
			g_aimbot.VisualizeFOVRadius();

			// Projectile related.
			g_projectiles.Handle();

			DisplayActiveKeybinds();

			// Render the GUI.
			g_menu.Render();
		}
	}
	g_globals->renderer->Finish();

	return oPresent( device, src, dst, dst_window_override, dirty_region );
}