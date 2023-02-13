#pragma once

#define NOMINMAX

#pragma warning (disable : 4005)

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <filesystem>

#include "Renderer.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "SDK/ValveSDK.h"
#include "SDK/Player.h"
#include "Interface.h"
#include "Memory.h"
#include "Math.h"
#include "Include.h"
#include "Settings/Settings.h"
#include "Settings/Configuration.h"
#include "Signatures.h"
#include "Hacks.h"

#include "Utility/Vmt.h"
#include "Utility/TinyFormat.h"
#include "Utility/SafeCall.h"

// Get-Project -All | Foreach { $_.ConfigurationManager.DeleteConfigurationRow("Release") }

class Globals
{
public:
	// Globals.
	bool shouldUnload;
	bool rendererInitialized;
	bool updateScreen;

	// Game.
	Player* localPlayer;
	VMatrix viewMatrix;

	// Screen.
	int screenW;
	int screenH;

	// Drawing.
	std::unique_ptr<CRender>renderer;
	c_render_context* renderContext;

	HMODULE thisModule;

	// Hook pointers.
	std::unique_ptr<SafeVMT>vmt1;
	std::unique_ptr<SafeVMT>vmt2;
	std::unique_ptr<SafeVMT>vmt3;
	std::unique_ptr<SafeVMT>vmt4;
	std::unique_ptr<SafeVMT>vmt5;

	// Functions.
	using LineGoesThroughSmokeT = bool( __cdecl* )( Vector3, Vector3 );
	using NtUserGetAsyncKeyStateT = SHORT( NTAPI* )( INT );
	using GetForegroundWindowT = HWND( WINAPI* )( );
	using GetTickCountT = DWORD( WINAPI* )( );

	LineGoesThroughSmokeT LineGoesThroughSmoke = nullptr;
	NtUserGetAsyncKeyStateT NtUserGetAsyncKeyState = nullptr;
	GetForegroundWindowT GetForegroundWindow = nullptr;
	GetTickCountT GetTickCount = nullptr;

	// Spoofed game-specific functions.
	class SpoofedGameFunctions
	{
	public:
		inline void GetScreenSize( int& w, int& h )
		{
#ifdef _DEBUG
			return Memory::GetVirtual<void( __thiscall* )( void*, int&, int& )>( g_interfaces->Engine, 5 )( g_interfaces->Engine, w, h );
#else
			return SafeCall::Type::Stdcall<void>( ( uintptr_t )Memory::GetVirtual( g_interfaces->Engine, 5 ), SafeCall::Address::GetGadget( _( "engine.dll" ) ), &w, &h );
#endif
		}

		inline int GetLocalPlayer()
		{
			return SafeCall::Type::Stdcall<int>( ( uintptr_t )Memory::GetVirtual( g_interfaces->Engine, 12 ), SafeCall::Address::GetGadget( _( "engine.dll" ) ) );
		}

		inline void ClientCmdUnrestricted( const char* cmd )
		{
#ifdef _DEBUG
			return Memory::GetVirtual<void( __stdcall* )( void*, const char* )>( g_interfaces->Engine, 114 )( g_interfaces->Engine, cmd );
#else
			return SafeCall::Type::Stdcall<void>( ( uintptr_t )Memory::GetVirtual( g_interfaces->Engine, 114 ), SafeCall::Address::GetGadget( _( "engine.dll" ) ), cmd );
#endif
		}

		inline c_client* GetAllClasses()
		{
			return SafeCall::Type::Stdcall<c_client*>( ( uintptr_t )Memory::GetVirtual( g_interfaces->Client, 8 ), SafeCall::Address::GetGadget( _( "client.dll" ) ) );
		}
	};

	SpoofedGameFunctions* spoofedFunctions = new SpoofedGameFunctions();
};

inline Globals* g_globals = new Globals();

#define CROSSHAIR_X g_globals->screenW / 2
#define CROSSHAIR_Y g_globals->screenH / 2

#include "Utility/Utility.hpp"
#include "Wrapper.h"
#include "World.h"