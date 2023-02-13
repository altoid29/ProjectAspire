#include "../../Header Files/Hacks.h"

void ProjectileRelated::Handle()
{
	if ( !Settings::Projectiles::enable )
		return;

	if ( !g_globals->localPlayer )
		return;

	for ( size_t i = 0; i < g_interfaces->EntList->GetHighestIndex(); i++ )
	{
		Player* entity = g_interfaces->EntList->GetClientEntity( i );
		if ( !entity )
			continue;

		// Valid owner handle; This means a player is holding the item, stop here.
		if ( entity->OwnerEntityHandle() != -1 )
			continue;

		// We have visible check on, but cannot see entity, stop here.
		if ( Settings::Projectiles::visibleCheck && !entity->IsVisible( entity, g_globals->localPlayer->GetEyeOrigin() ) )
			continue;

		if ( Settings::Projectiles::weaponNames )
		{
			const auto GetWeaponForName = []( Player* ent ) -> std::string
			{
				if ( !ent )
					return "INVALID_ENTITY";

				std::string Name = ent->Client()->Name;

				if ( strstr( Name.c_str(), "CWeapon" ) )
					Name.replace( Name.find( "CWeapon" ), sizeof( "CWeapon" ) - 1, "" );

				if ( Hash::Fnv1a( Name ) == HASH( "HKP2000" ) )
					Name.replace( Name.find( "HKP2000" ), sizeof( "HKP2000" ) - 1, "P2000" );

				if ( Hash::Fnv1a( Name ) == HASH( "CDEagle" ) )
					Name.replace( Name.find( "CDEagle" ), sizeof( "CDEagle" ) - 1, "DEAGLE" );

				if ( Hash::Fnv1a( Name ) == HASH( "CAK47" ) )
					Name.replace( Name.find( "CAK47" ), sizeof( "CAK47" ) - 1, "AK-47" );

				std::transform( Name.begin(), Name.end(), Name.begin(), ::toupper );

				return Name;
			};

			Vector2 screen{};
			if ( !World::WorldToScreen( entity->GetOrigin(), screen ) )
				continue;

			static const std::vector<int>List = { CAK47, CWEAPONAUG, CWEAPONFAMAS, CWEAPONGALIL, CWEAPONGALILAR, CWEAPONM4A1, CWEAPONNOVA, CWEAPONXM1014, CWEAPONSAWEDOFF, CWEAPONNEGEV, CWEAPONSHIELD, CWEAPONM249, CWEAPONMAC10, CWEAPONUMP45, CWEAPONBIZON, CWEAPONP90, CWEAPONTASER, CWEAPONMP7, CWEAPONSG550, CWEAPONSG552, CWEAPONSG556, CWEAPONUSP, CDEAGLE, CWEAPONELITE, CWEAPONFIVESEVEN, CWEAPONGLOCK, CWEAPONHKP2000, CWEAPONP250, CWEAPONTEC9, CWEAPONAWP, CWEAPONG3SG1, CWEAPONSCAR20, CWEAPONSSG08 };
			if ( std::find( List.begin(), List.end(), entity->Client()->ClassID ) != List.end() )
				Renderer::AddString( g_globals->renderer->testFont, Renderer::DetermineColorFromSelection( Settings::Colors::weaponNamesSelection ), screen.x, screen.y, true, GetWeaponForName( entity ).c_str(), true );
		}

		if ( Settings::Projectiles::bomb )
		{
			if ( entity->Client()->ClassID == ClassID::CC4 )
			{
				Vector2 screen{};
				if ( !World::WorldToScreen( entity->GetOrigin(), screen ) )
					continue;

				Renderer::AddString( g_globals->renderer->testFont, Renderer::DetermineColorFromSelection( Settings::Colors::bombSelection ), screen.x, screen.y, true, "BOMB", true );
			}
		}

		if ( Settings::Projectiles::hostage )
		{
			if ( entity->Client()->ClassID == ClassID::CHOSTAGE )
			{
				Vector2 screen{};
				if ( !World::WorldToScreen( entity->GetOrigin(), screen ) )
					continue;

				Renderer::AddString( g_globals->renderer->testFont, Renderer::DetermineColorFromSelection( Settings::Colors::hostageSelection ), screen.x, screen.y, true,  "HOSTAGE", true );
			}
		}

		if ( Settings::Projectiles::utilities )
		{
			const auto GetUtilityName = []( Player* entity ) -> std::string
			{
				if ( !entity )
					return "INVALID_ENTITY";

				switch ( entity->Client()->ClassID )
				{
					case ClassID::CFLASHBANG: return "FLASHBANG"; break;
					case ClassID::CDECOYGRENADE: return "DECOY"; break;
					case ClassID::CSMOKEGRENADE: return "SMOKE"; break;
					case ClassID::CHEGRENADE: return "GRENADE"; break;
					case ClassID::CMOLOTOVGRENADE: return "MOLOTOV"; break;
					case ClassID::CINCENDIARYGRENADE: return "INCENDIARY"; break;

					default: return std::to_string( entity->Client()->ClassID ); break;
				}

				return std::to_string( entity->Client()->ClassID );
			};

			Vector2 screen{};
			if ( !World::WorldToScreen( entity->GetOrigin(), screen ) )
				continue;

			static const std::vector<int>Utilities = { CFLASHBANG, CDECOYGRENADE, CSMOKEGRENADE, CHEGRENADE, CMOLOTOVGRENADE, CINCENDIARYGRENADE };
			if ( std::find( Utilities.begin(), Utilities.end(), entity->Client()->ClassID ) != Utilities.end() )
				Renderer::AddString( g_globals->renderer->testFont, Renderer::DetermineColorFromSelection( Settings::Colors::utilitiesSelection ), screen.x, screen.y, true, GetUtilityName( entity ).c_str(), true );
		}
	}
}