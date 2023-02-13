#include "../../Header Files/Hacks.h"

void HudRelated::RevealSpectators()
{
	if ( !Settings::Misc::revealSpectators )
		return;

	if ( !g_globals->localPlayer || !g_globals->localPlayer->IsAlive() )
		return;

	std::vector<std::string>spectators{};
	std::vector<int>observerMode{};

	for ( size_t i = 0; i < Util::GetPlayerCount(); i++ )
	{
		const auto entity = g_interfaces->EntList->GetClientEntity( i );

		// No player, no list.
		if ( !entity )
			continue;

		// Of course, alive players aren't going to be a spectator.
		if ( entity->IsAlive() )
			continue;

		// Don't add dormant, otherwise the records will stay forever.
		if ( entity->IsDormant() )
			continue;

		// Get the current spectator.
		const auto observerHandle = entity->ObserverTargetHandle();
		const auto currentSpectator = g_interfaces->EntList->GetEntityFromHandle( observerHandle );

		// Player isn't spectating us.
		if ( currentSpectator != g_globals->localPlayer )
			continue;

		// Get player data.
		PlayerInfo_t info{};
		g_interfaces->Engine->GetPlayerInfo( i, &info );

		if ( info.IsHLTV )
			continue;

		// Valid player, add to the list.
		spectators.push_back( info.Name );
		observerMode.push_back( entity->GetOBSMode() );

		Settings::Misc::getSpectators = spectators;
		Settings::Misc::getSpectatorObserverMode = observerMode;
	}

	static const auto OBSValueToName = []( int mode ) -> std::string
	{
		switch ( mode )
		{
			case ObserverMode_t::OBS_MODE_NONE: return _( "None" ); break;
			case ObserverMode_t::OBS_MODE_DEATHCAM: return _( "Death" );  break;
			case ObserverMode_t::OBS_MODE_FREEZECAM: return _( "Freeze" ); break;
			case ObserverMode_t::OBS_MODE_FIXED: return _( "Fixed" ); break;
			case ObserverMode_t::OBS_MODE_IN_EYE: return _( "1st-Person" ); break;
			case ObserverMode_t::OBS_MODE_CHASE: return _( "3rd-Person" ); break;
			case ObserverMode_t::OBS_MODE_POI: return _( "Interest" ); break;
			case ObserverMode_t::OBS_MODE_ROAMING: return _( "Free-roam" ); break;

			default: return _( "Unknown" ); break;
		}

		return _( "Undefined" );
	};

	for ( size_t i = 0; i < spectators.size(); i++ )
	{
		// Note - Observer mode doesn't need to be in a separate loop, it will be the same amount.
		const std::string toDraw = tfm::format( _( "%s | %s" ), spectators[ i ], OBSValueToName( observerMode[ i ] ) );
		const auto width = g_globals->renderer->TextWidth( g_globals->renderer->tahoma, toDraw.c_str() );

		Renderer::AddString( g_globals->renderer->tahoma, Renderer::UIColorT( 255, 255, 255, 255 ), g_globals->screenW - 10 - width, 10 + ( i * 15 ), false, toDraw.c_str(), true );
	}
}