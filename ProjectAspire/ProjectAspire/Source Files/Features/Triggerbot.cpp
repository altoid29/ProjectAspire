#include "../../Header Files/Hacks.h"

void SimulateClick()
{
	const auto sendInput = reinterpret_cast< UINT( WINAPI* )( UINT, LPINPUT, int ) >( ( void* )SafeCall::Address::GetExport( _( "user32.dll" ), _( "SendInput" ) ) );

	INPUT Ip{};
	Ip.type = INPUT_MOUSE;
	Ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	sendInput( 1, &Ip, sizeof( INPUT ) );

	Ip.type = INPUT_MOUSE;
	Ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	sendInput( 1, &Ip, sizeof( INPUT ) );
}

void TriggerbotRelated::Handle()
{
	if ( !Settings::Triggerbot::enable )
		return;

	// Don't fire when we are not tabbed into CS:GO.
	if ( g_globals->GetForegroundWindow() != g_interfaces->Window )
		return;

	if ( !g_globals->localPlayer || !g_globals->localPlayer->IsAlive() )
		return;

	// Don't fire in the air.
	if ( g_globals->localPlayer->IsInAir() )
		return;

	const auto weapon = g_globals->localPlayer->Weapon();
	if ( !weapon )
		return;

	if ( weapon->ItemDefinitionIndex() == WEAPON_KNIFE || weapon->ItemDefinitionIndex() == WEAPON_TASER || weapon->ItemDefinitionIndex() == WEAPON_REVOLVER )
		return;

	// Don't no-scope.
	if ( weapon->IsSniperRifle() && !g_globals->localPlayer->IsScoped() )
		return;

	const auto angles = g_interfaces->Engine->GetViewAngles();
	const auto startPos = g_globals->localPlayer->GetEyeOrigin();
	const auto endPos = startPos + Vector3::FromAngle( angles + g_globals->localPlayer->AimPunchAngle() ) * 9999.f;

	// Ignore the local player.
	TraceFilter filter;
	filter.m_filter = g_globals->localPlayer;

	// Trace a ray from our current eye position, and see if it hits a player.
	GameTrace gameTrace;
	g_interfaces->EngineTrace->TraceRay( { startPos, endPos }, 0x46004009, &filter, &gameTrace );
	filter.m_filter = g_globals->localPlayer;

	if ( !gameTrace.Entity || !gameTrace.Entity->IsPlayer() )
		return;

	if ( !gameTrace.Entity->IsAlive() )
		return;

	if ( gameTrace.Entity->HasSpawnProtection() )
		return;

	// Disable when it the player is inside a smoke.
	if ( Settings::Triggerbot::smokeCheck && g_globals->LineGoesThroughSmoke( g_globals->localPlayer->GetOrigin(), gameTrace.Entity->GetOrigin() ) )
		return;

	// Disable if flashed.
	if ( Settings::Triggerbot::flashCheck && g_globals->localPlayer->IsFlashed() )
		return;

	// Ignore teammates.
	if ( Settings::Triggerbot::teamCheck && gameTrace.Entity->GetTeam() == g_globals->localPlayer->GetTeam() )
		return;

	const auto Fire = []() -> void
	{
		SimulateClick();
	};

	// Allow execution when holding a key, or not holding a key.
	if ( Settings::Triggerbot::hotkey > 0 && g_globals->NtUserGetAsyncKeyState( Settings::Triggerbot::hotkey ) ||
		 Settings::Triggerbot::hotkey == 0 && !g_globals->NtUserGetAsyncKeyState( Settings::Triggerbot::hotkey ) )
	{
		switch ( Settings::Triggerbot::hitbox )
		{
			case 0:
				if ( gameTrace.Hitbox == HITBOX_HEAD )
					Fire();
				break;

			case 1:
				if ( gameTrace.Hitbox == HITBOX_UPPER_CHEST || gameTrace.Hitbox == HITBOX_CHEST || gameTrace.Hitbox == HITBOX_THORAX )
					Fire();
				break;

			case 2:
				if ( gameTrace.Hitbox == HITBOX_BODY )
					Fire();
				break;

			case 3:
			{
				static const std::vector<int>hitboxes = { HITBOX_PELVIS, HITBOX_LEFT_THIGH, HITBOX_RIGHT_THIGH, HITBOX_LEFT_CALF, HITBOX_LEFT_FOOT, HITBOX_RIGHT_CALF, HITBOX_RIGHT_FOOT };
				if ( std::find( hitboxes.begin(), hitboxes.end(), gameTrace.Hitbox ) != hitboxes.end() )
					Fire();
			}
			break;

			case 4:
				Fire();
				break;

			default:
				return;
				break;
		}
	}
}