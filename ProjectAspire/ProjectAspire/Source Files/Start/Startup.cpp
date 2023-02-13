#include "../../Header Files/Interface.h"
#include "../../Header Files/Hooks.h"

bool Hack::Init()
{
	bool isReady = false;

	// Use a bool rather then SLEEP so we can inject when the game isn't fully loaded.
	while ( !SafeCall::Address::GetModule( _( "serverbrowser.dll" ) ) )
		isReady = false;

	isReady = true;

	// Found serverbrowser.dll, lets begin.
	if ( isReady )
	{
		// Initialize WinAPI wrappers.
		g_globals->NtUserGetAsyncKeyState = reinterpret_cast< Globals::NtUserGetAsyncKeyStateT >( SafeCall::Address::GetExport( _( "win32u.dll" ), _( "NtUserGetAsyncKeyState" ) ) );
		g_globals->GetForegroundWindow = reinterpret_cast< Globals::GetForegroundWindowT >( SafeCall::Address::GetExport( _( "user32.dll" ), _( "GetForegroundWindow" ) ) );
		g_globals->GetTickCount = reinterpret_cast< Globals::GetTickCountT >( SafeCall::Address::GetExport( _( "kernel32.dll" ), _( "GetTickCount" ) ) );

		// Get CSGO window name.
#ifdef _DEBUG
		g_interfaces->Window = FindWindowA( "Valve001", nullptr );
#else
		g_interfaces->Window = SafeCall::Type::Stdcall<HWND>( SafeCall::Address::GetExport( _( "user32.dll" ), _( "FindWindowA" ) ), SafeCall::Address::GetGadget( _( "csgo.exe" ) ), _( "Valve001" ), nullptr );
#endif

		// Initialize interfaces.
		g_interfaces->Client = GetInterface<CBaseClient>( _( "client.dll" ), _( "VClient018" ) );
		g_interfaces->EntList = GetInterface<EntityList>( _( "client.dll" ), _( "VClientEntityList003" ) );
		g_interfaces->Engine = GetInterface<CEngineClient>( _( "engine.dll" ), _( "VEngineClient014" ) );
		g_interfaces->Panel = GetInterface<VPanel>( _( "vgui2.dll" ), _( "VGUI_Panel009" ) );
		g_interfaces->Surface = GetInterface<ISurface>( _( "vguimatsurface.dll" ), _( "VGUI_Surface031" ) );
		g_interfaces->MaterialSystem = GetInterface<IMaterialSystem>( _( "materialsystem.dll" ), _( "VMaterialSystem080" ) );
		g_interfaces->ModelInfo = GetInterface<IVModelInfoClient>( _( "engine.dll" ), _( "VModelInfoClient004" ) );
		g_interfaces->ModelRender = GetInterface<IVModelRender>( _( "engine.dll" ), _( "VEngineModel016" ) );
		g_interfaces->RenderView = GetInterface<IVRenderView>( _( "engine.dll" ), _( "VEngineRenderView014" ) );
		g_interfaces->CVars = GetInterface<CVar>( _( "vstdlib.dll" ), _( "VEngineCvar007" ) );
		g_interfaces->Localize = GetInterface<CLocalize>( _( "localize.dll" ), _( "Localize_001" ) );
		g_interfaces->EventManager = GetInterface<IGameEventManager2>( _( "engine.dll" ), _( "GAMEEVENTSMANAGER002" ) );
		g_interfaces->DebugOverlay = GetInterface<CDebugOverlay>( _( "engine.dll" ), _( "VDebugOverlay004" ) );
		g_interfaces->Input = GetInterface<CInput>( _( "inputsystem.dll" ), _( "InputSystemVersion001" ) );
		g_interfaces->EngineTrace = GetInterface<CEngineTrace>( _( "engine.dll" ), _( "EngineTraceClient004" ) );
		g_interfaces->Movement = GetInterface<IGameMovement>( _( "client.dll" ), _( "GameMovement001" ) );
		g_interfaces->Prediction = GetInterface<IPrediction>( _( "client.dll" ), _( "VClientPrediction001" ) );
		g_interfaces->SoundSystem = GetInterface<IEngineSound>( _( "engine.dll" ), _( "IEngineSoundClient003" ) );

		// Initialize manual interfaces.
		g_interfaces->Globals = **reinterpret_cast< CGlobals*** >( ( *reinterpret_cast< uintptr_t** >( g_interfaces->Client ) )[ 11 ] + 10 );
		g_interfaces->Device = **reinterpret_cast< CDirectDeviceVTable*** >( Memory::FindSignature( _( "shaderapidx9.dll" ), _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 1 );
		g_interfaces->Input = *reinterpret_cast< CInput** >( Memory::FindSignature( _( "client.dll" ), _( "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) ) + 1 );
		g_interfaces->ClientMode = **reinterpret_cast< IClientMode*** >( ( *reinterpret_cast< uintptr_t** >( g_interfaces->Client ) )[ 10 ] + 5 );
		g_interfaces->ClientState = **reinterpret_cast< CClientState*** >( Memory::FindSignature( _( "engine.dll" ), _( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) ) + 1 );
		g_interfaces->MoveHelper = **reinterpret_cast< PlayerMovementHelper*** >( Memory::FindSignature( _( "client.dll" ), _( "8B 0D ? ? ? ? 8B 46 08 68" ) ) + 2 ); // XREF: "Player.swim" | Two lines above, look for mov ecx, dword_1532FA24.

		// Initialize signatures.
		Offsets::getSequenceActivity = Memory::FindSignature( _( "client.dll" ), _( "55 8B EC 53 8B 5D 08 56 8B F1 83" ) );
		Offsets::hasC4 = Memory::FindSignature( _( "client.dll" ), _( "56 8B F1 85 F6 74 31" ) );
		Offsets::viewMatrix = Memory::FindSignature( _( "client.dll" ), _( "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9" ) );
		Offsets::isHLTV = Memory::FindSignature( _( "client.dll" ), _( "84 C0 0F 85 ? ? ? ? 8B CB E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 83 BF" ) );

		// Initialize functions.
		g_globals->LineGoesThroughSmoke = reinterpret_cast< decltype( g_globals->LineGoesThroughSmoke ) >( Memory::FindSignature( _( "client.dll" ), _( "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0" ) ) );

		// Acquire netvars.
		g_netvars.Init();

		// Create new VMT instances.
		g_globals->vmt1 = std::make_unique<SafeVMT>( g_interfaces->Device );
		g_globals->vmt2 = std::make_unique<SafeVMT>( g_interfaces->Device );
		g_globals->vmt3 = std::make_unique<SafeVMT>( g_interfaces->RenderView );
		g_globals->vmt4 = std::make_unique<SafeVMT>( g_interfaces->Surface );
		g_globals->vmt5 = std::make_unique<SafeVMT>( g_interfaces->Engine );

		// Set the hook originals.
		Hooks::oReset = ( Hooks::ResetT )g_globals->vmt1->GetVFunc( 16 );
		Hooks::oReset = reinterpret_cast< decltype( Hooks::oReset ) >( ( uintptr_t )Hooks::oReset );

		Hooks::oPresent = ( Hooks::PresentT )g_globals->vmt2->GetVFunc( 17 );
		Hooks::oPresent = reinterpret_cast< decltype( Hooks::oPresent ) >( ( uintptr_t )Hooks::oPresent );

		Hooks::oSceneEnd = ( Hooks::SceneEndT )g_globals->vmt3->GetVFunc( 9 );
		Hooks::oSceneEnd = reinterpret_cast< decltype( Hooks::oSceneEnd ) >( ( uintptr_t )Hooks::oSceneEnd );

		Hooks::oOnScreenSizeChanged = ( Hooks::OnScreenSizeChangedT )g_globals->vmt4->GetVFunc( 116 );
		Hooks::oOnScreenSizeChanged = reinterpret_cast< decltype( Hooks::oOnScreenSizeChanged ) >( ( uintptr_t )Hooks::oOnScreenSizeChanged );

		Hooks::oIsHLTV = ( Hooks::IsHLTVT )g_globals->vmt5->GetVFunc( 93 );
		Hooks::oIsHLTV = reinterpret_cast< decltype( Hooks::oIsHLTV ) >( ( uintptr_t )Hooks::oIsHLTV );

		// Set our hooks.
		g_globals->vmt1->PlaceHook( Hooks::Reset, 16 );
		g_globals->vmt2->PlaceHook( Hooks::Present, 17 );
		g_globals->vmt3->PlaceHook( Hooks::SceneEnd, 9 );
		g_globals->vmt4->PlaceHook( Hooks::OnScreenSizeChanged, 116 );
		g_globals->vmt5->PlaceHook( Hooks::IsHLTV, 93 );

		// Clear the console and smooth the game out.
		g_globals->spoofedFunctions->ClientCmdUnrestricted( _( "clear" ) );
		g_globals->spoofedFunctions->ClientCmdUnrestricted( _( "fps_max 0" ) );

		return true;
	}

	return false;
}