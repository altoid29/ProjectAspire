 #include "../../Header Files/Hacks.h"

enum SelectionType
{
	CROSSHAIR,
	DISTANCE,
	HEALTH
};

void MoveMouse( int x, int y )
{
	INPUT Ip{};
	Ip.type = INPUT_MOUSE;
	Ip.mi.mouseData = NULL;
	Ip.mi.time = NULL;
	Ip.mi.dx = x;
	Ip.mi.dy = y;
	Ip.mi.dwFlags = MOUSEEVENTF_MOVE;

	const auto sendInput = reinterpret_cast< UINT( WINAPI* )( UINT, LPINPUT, int ) >( ( void* )SafeCall::Address::GetExport( _( "user32.dll" ), _( "SendInput" ) ) );
	if ( !sendInput )
		return;

	sendInput( 1, &Ip, sizeof( INPUT ) );
}

void AimbotRelated::VisualizeFOVRadius()
{
	if ( !Settings::Misc::visualizeFov )
		return;

	if ( !g_globals->localPlayer || !g_globals->localPlayer->IsAlive() )
		return;

	if ( !Settings::Aimbot::enable || Settings::Aimbot::fovRadius == 0 )
		return;

	const float radiusDeg = fabs( Settings::Aimbot::fovRadius * ( 180.f / M_PI ) ) / 12.f;
	g_globals->renderer->Circle( Vector2( g_globals->screenW / 2, g_globals->screenH / 2 ), 32, radiusDeg, Renderer::DetermineColorFromSelection2( Settings::Colors::fovSelection ) );
}

constexpr int GetHitboxFromSelection()
{
	switch ( Settings::Aimbot::hitbox )
	{
		case 0: return HITBOX_HEAD; break;
		case 1: return HITBOX_NECK; break;
		case 2: return HITBOX_CHEST; break;
		case 3: return HITBOX_THORAX; break;
		case 4: return HITBOX_PELVIS; break;
		default: return HITBOX_HEAD; break;
	}

	return HITBOX_HEAD;
};

Player* AimbotRelated::GetBestPlayer()
{
	Player* selectedEnt = nullptr;
	float bestCrosshairDist = FLT_MAX;
	float bestDistance = FLT_MAX;
	float bestHealth = FLT_MAX;

	for ( size_t i = 0; i < 32; i++ )
	{
		Player* entity = g_interfaces->EntList->GetClientEntity( i );
		if ( !entity || !entity->IsAlive() || entity->IsDormant() || entity->HasSpawnProtection() || entity == g_globals->localPlayer )
			continue;

		// Visible-check.
		if ( Settings::Aimbot::visibleCheck && !entity->IsVisible( entity, g_globals->localPlayer->GetEyeOrigin() ) )
			continue;

		// Team-check.
		if ( Settings::Aimbot::teamCheck && entity->GetTeam() == g_globals->localPlayer->GetTeam() )
			continue;

		// Flash-check.
		if ( Settings::Aimbot::flashDisable && g_globals->localPlayer->IsFlashed() )
			continue;

		// Smoke-check.
		if ( Settings::Aimbot::smokeDisable && g_globals->LineGoesThroughSmoke( g_globals->localPlayer->GetOrigin(), entity->GetOrigin() ) )
			continue;

		// Air-check.
		if ( Settings::Aimbot::airDisable && g_globals->localPlayer->IsInAir() )
			continue;

		// First-person spectator disable.
		if ( Settings::Aimbot::specatatorDisable &&
			 std::find( Settings::Misc::getSpectatorObserverMode.begin(), Settings::Misc::getSpectatorObserverMode.end(), OBS_MODE_IN_EYE ) != Settings::Misc::getSpectatorObserverMode.end() )
			continue;

		Vector2 screen{};
		if ( !World::WorldToScreen( entity->GetHitboxPosition( HITBOX_HEAD ), screen ) )
			continue;

		switch ( Settings::Aimbot::targetSelection )
		{
			case SelectionType::CROSSHAIR:
			{
				const float crosshairDist = Math::GetDistance( screen.x, screen.y, CROSSHAIR_X, CROSSHAIR_Y );
				if ( crosshairDist < bestCrosshairDist )
				{
					bestCrosshairDist = crosshairDist;
					selectedEnt = entity;
				}
			}
			break;

			case SelectionType::DISTANCE:
			{
				const float entityDistance = g_globals->localPlayer->GetOrigin().dist( entity->GetOrigin() );
				if ( entityDistance < bestDistance )
				{
					bestDistance = entityDistance;
					selectedEnt = entity;
				}
			}
			break;

			case SelectionType::HEALTH:
			{
				const int entityHealth = entity->GetHealth();
				if ( entityHealth < bestHealth )
				{
					bestHealth = entityHealth;
					selectedEnt = entity;
				}
			}
			break;
		}
	}

	return selectedEnt;
}

void AimbotRelated::Handle()
{
	if ( !Settings::Aimbot::enable || Settings::Aimbot::fovRadius == 0 )
		return;

	// Don't fire when we're not tabbed into the game.
	if ( g_globals->GetForegroundWindow() != g_interfaces->Window )
		return;

	if ( !g_globals->localPlayer || !g_globals->localPlayer->IsAlive() )
		return;

	// Can't fire.
	if ( g_globals->localPlayer->IsReloading() )
		return;

	const auto weapon = g_globals->localPlayer->Weapon();
	if ( !weapon )
		return;

	if ( weapon->ItemDefinitionIndex() == WEAPON_TASER || weapon->ItemDefinitionIndex() == WEAPON_KNIFE )
		return;

	const auto entity = this->GetBestPlayer();
	if ( !entity )
		return;

	Vector2 screen{};
	if ( !World::WorldToScreen( this->GetBestPlayer()->GetHitboxPosition( GetHitboxFromSelection() ), screen ) )
		return;

	// Allow execution when holding a key, or not holding a key.
	if ( Settings::Aimbot::hotkey > 0 && g_globals->NtUserGetAsyncKeyState( Settings::Aimbot::hotkey ) ||
		 Settings::Aimbot::hotkey == 0 && !g_globals->NtUserGetAsyncKeyState( Settings::Aimbot::hotkey ) )
	{
		// Handle FOV amount.
		Vector2 fovRadius = Vector2( fabs( Settings::Aimbot::fovRadius * ( 180.f / M_PI ) ), fabs( Settings::Aimbot::fovRadius * ( 180.f / M_PI ) ) ) / 12.f;

		// In field of view range.
		if ( Math::IsInFOV( Vector2( g_globals->screenW, g_globals->screenH ), screen, fovRadius ) )
		{
			Vector2 entityDist( screen.x - CROSSHAIR_X, screen.y - CROSSHAIR_Y );
			const float crosshairDist = Math::GetDistance( screen.x, screen.y, CROSSHAIR_X, CROSSHAIR_Y );

			// Handle smoothness based on crosshair distance.
			if ( Settings::Aimbot::dynamicSmoothness )
				entityDist /= ( crosshairDist / 1.75f );

			// Perform the aimbot.
			if ( g_globals->localPlayer->GetShotsFired() >= Settings::Aimbot::aimAfterXShots )
				MoveMouse( entityDist.x, entityDist.y );
		}
	}
}