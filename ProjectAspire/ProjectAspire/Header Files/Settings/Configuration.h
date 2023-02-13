#pragma once

#include "../Include.h"

#include <algorithm>
#include <fstream>

namespace Configuration
{
	inline std::string GetPath()
	{
		char buf[ MAX_PATH ];
#ifdef _DEBUG
		GetModuleFileNameA( nullptr, buf, sizeof( buf ) );
#else
		SAFECALL_STDCALL( DWORD, "kernel32.dll", "GetModuleFileNameA", "csgo.exe", nullptr, buf, sizeof( buf ) );
#endif

		std::string fullPath = buf;
		if ( strstr( fullPath.c_str(), "csgo.exe" ) )
			fullPath.replace( fullPath.find( "csgo.exe" ), sizeof( "csgo.exe" ), "" );

		char buf2[ 256 + 1 ];
		DWORD length = 256 + 1;
#ifdef _DEBUG
		GetUserNameA( buf2, &length );
#else
		SAFECALL_STDCALL( BOOL, "advapi32.dll", "GetUserNameA", "csgo.exe", buf2, &length );
#endif

		return tfm::format( "%s%s", fullPath, Hash::Fnv1a( buf2 ) );
	}

	inline void Save()
	{
		if ( !std::filesystem::exists( GetPath() ) )
			std::ofstream{ Configuration::GetPath() };

		std::ofstream fout{};
		fout.open( GetPath(), std::ios::trunc );

#define SAVE_ITEM(String, Variable) \
fout << String << Variable << std::endl;

		SAVE_ITEM( _( "aimbot.enable " ), Settings::Aimbot::enable );
		SAVE_ITEM( _( "aimbot.target_selection " ), Settings::Aimbot::targetSelection );
		SAVE_ITEM( _( "aimbot.hotkey " ), Settings::Aimbot::hotkey );
		SAVE_ITEM( _( "aimbot.visible_check " ), Settings::Aimbot::visibleCheck );
		SAVE_ITEM( _( "aimbot.team_check " ), Settings::Aimbot::teamCheck );
		SAVE_ITEM( _( "aimbot.fov_radius " ), Settings::Aimbot::fovRadius );
		SAVE_ITEM( _( "aimbot.dynamic_smoothness " ), Settings::Aimbot::dynamicSmoothness );
		SAVE_ITEM( _( "aimbot.hitbox " ), Settings::Aimbot::hitbox );
		SAVE_ITEM( _( "aimbot.aim_after_x_shots " ), Settings::Aimbot::aimAfterXShots );
		SAVE_ITEM( _( "aimbot.flash_disable " ), Settings::Aimbot::flashDisable );
		SAVE_ITEM( _( "aimbot.smoke_disable " ), Settings::Aimbot::smokeDisable );
		SAVE_ITEM( _( "aimbot.air_disable " ), Settings::Aimbot::airDisable );
		SAVE_ITEM( _( "aimbot.spectator_disable " ), Settings::Aimbot::specatatorDisable );

		SAVE_ITEM( _( "triggerbot.enable " ), Settings::Triggerbot::enable );
		SAVE_ITEM( _( "triggerbot.team_check " ), Settings::Triggerbot::teamCheck );
		SAVE_ITEM( _( "triggerbot.smoke_check " ), Settings::Triggerbot::smokeCheck );
		SAVE_ITEM( _( "triggerbot.flash_check " ), Settings::Triggerbot::flashCheck );
		SAVE_ITEM( _( "triggerbot.delay " ), Settings::Triggerbot::delay );

		SAVE_ITEM( _( "esp.enable " ), Settings::ESP::enable );
		SAVE_ITEM( _( "esp.visible_check " ), Settings::ESP::visibleCheck );
		SAVE_ITEM( _( "esp.team_check " ), Settings::ESP::teamCheck );
		SAVE_ITEM( _( "esp.box " ), Settings::ESP::box );
		SAVE_ITEM( _( "esp.name " ), Settings::ESP::name );
		SAVE_ITEM( _( "esp.health " ), Settings::ESP::health );
		SAVE_ITEM( _( "esp.distance " ), Settings::ESP::distance );
		SAVE_ITEM( _( "esp.area " ), Settings::ESP::area );
		SAVE_ITEM( _( "esp.skeleton " ), Settings::ESP::skeleton );
		SAVE_ITEM( _( "esp.lines " ), Settings::ESP::lines );
		SAVE_ITEM( _( "esp.lines_position " ), Settings::ESP::lines );
		SAVE_ITEM( _( "esp.head_dot.delay " ), Settings::ESP::dot );

		SAVE_ITEM( _( "projectiles.enable " ), Settings::Projectiles::enable );
		SAVE_ITEM( _( "projectiles.visible_check " ), Settings::Projectiles::visibleCheck );
		SAVE_ITEM( _( "projectiles.weapon_names " ), Settings::Projectiles::weaponNames );
		SAVE_ITEM( _( "projectiles.bomb " ), Settings::Projectiles::bomb );
		SAVE_ITEM( _( "projectiles.hostages " ), Settings::Projectiles::hostage );
		SAVE_ITEM( _( "projectiles.utilities " ), Settings::Projectiles::utilities );

		SAVE_ITEM( _( "colors.box " ), Settings::Colors::boxSelection );
		SAVE_ITEM( _( "colors.name " ), Settings::Colors::nameSelection );
		SAVE_ITEM( _( "colors.distance " ), Settings::Colors::distanceSelection );
		SAVE_ITEM( _( "colors.area " ), Settings::Colors::areaSelection );
		SAVE_ITEM( _( "colors.skeleton " ), Settings::Colors::skeletonSelection );
		SAVE_ITEM( _( "colors.lines " ), Settings::Colors::linesSelection );
		SAVE_ITEM( _( "colors.head_dot " ), Settings::Colors::dotSelection );
		SAVE_ITEM( _( "colors.weapon_names " ), Settings::Colors::weaponNamesSelection );
		SAVE_ITEM( _( "colors.bomb " ), Settings::Colors::bombSelection );
		SAVE_ITEM( _( "colors.hostage " ), Settings::Colors::hostageSelection );
		SAVE_ITEM( _( "colors.utilities " ), Settings::Colors::utilitiesSelection );
		SAVE_ITEM( _( "colors.interface " ), Settings::Colors::interfaceSelection );

		SAVE_ITEM( _( "misc.safe_mode " ), Settings::Misc::safeMode );
		SAVE_ITEM( _( "misc.show_navigation_keys " ), Settings::Misc::showKeybinds );
		SAVE_ITEM( _( "misc.show_active_keybinds " ), Settings::Misc::showActiveKeybinds );
		SAVE_ITEM( _( "misc.server_radar " ), Settings::Misc::radar );
		SAVE_ITEM( _( "misc.reveal_spectators " ), Settings::Misc::revealSpectators );
		SAVE_ITEM( _( "misc.visualize_fov_radius " ), Settings::Misc::visualizeFov );
		SAVE_ITEM( _( "misc.panic_hotkey " ), Settings::Misc::panicHotkey );

		fout.close();
	}

	inline void Load()
	{
		if ( !std::filesystem::exists( GetPath() ) )
		{
			std::ofstream{ Configuration::GetPath() };
			Save();
		}

		std::ifstream fin{};
		std::string word = "";
		fin.open( GetPath(), std::ifstream::in );

#define LOAD_ITEM(Item) \
fin >> word >> Item;

		LOAD_ITEM( Settings::Aimbot::enable );
		LOAD_ITEM( Settings::Aimbot::targetSelection );
		LOAD_ITEM( Settings::Aimbot::hotkey );
		LOAD_ITEM( Settings::Aimbot::visibleCheck );
		LOAD_ITEM( Settings::Aimbot::teamCheck );
		LOAD_ITEM( Settings::Aimbot::fovRadius );
		LOAD_ITEM( Settings::Aimbot::dynamicSmoothness );
		LOAD_ITEM( Settings::Aimbot::hitbox );
		LOAD_ITEM( Settings::Aimbot::aimAfterXShots );
		LOAD_ITEM( Settings::Aimbot::flashDisable );
		LOAD_ITEM( Settings::Aimbot::smokeDisable );
		LOAD_ITEM( Settings::Aimbot::airDisable );
		LOAD_ITEM( Settings::Aimbot::specatatorDisable );

		LOAD_ITEM( Settings::Triggerbot::enable );
		LOAD_ITEM( Settings::Triggerbot::teamCheck );
		LOAD_ITEM( Settings::Triggerbot::smokeCheck );
		LOAD_ITEM( Settings::Triggerbot::flashCheck );
		LOAD_ITEM( Settings::Triggerbot::delay );

		LOAD_ITEM( Settings::ESP::enable );
		LOAD_ITEM( Settings::ESP::visibleCheck );
		LOAD_ITEM( Settings::ESP::teamCheck );
		LOAD_ITEM( Settings::ESP::box );
		LOAD_ITEM( Settings::ESP::name );
		LOAD_ITEM( Settings::ESP::health );
		LOAD_ITEM( Settings::ESP::distance );
		LOAD_ITEM( Settings::ESP::area );
		LOAD_ITEM( Settings::ESP::skeleton );
		LOAD_ITEM( Settings::ESP::lines );
		LOAD_ITEM( Settings::ESP::linesPosition );
		LOAD_ITEM( Settings::ESP::dot );

		LOAD_ITEM( Settings::Projectiles::enable );
		LOAD_ITEM( Settings::Projectiles::visibleCheck );
		LOAD_ITEM( Settings::Projectiles::weaponNames );
		LOAD_ITEM( Settings::Projectiles::bomb );
		LOAD_ITEM( Settings::Projectiles::hostage );
		LOAD_ITEM( Settings::Projectiles::utilities );

		LOAD_ITEM( Settings::Colors::boxSelection );
		LOAD_ITEM( Settings::Colors::nameSelection );
		LOAD_ITEM( Settings::Colors::distanceSelection );
		LOAD_ITEM( Settings::Colors::areaSelection );
		LOAD_ITEM( Settings::Colors::skeletonSelection );
		LOAD_ITEM( Settings::Colors::linesSelection );
		LOAD_ITEM( Settings::Colors::dotSelection );
		LOAD_ITEM( Settings::Colors::weaponNamesSelection );
		LOAD_ITEM( Settings::Colors::bombSelection );
		LOAD_ITEM( Settings::Colors::hostageSelection );
		LOAD_ITEM( Settings::Colors::utilitiesSelection );
		LOAD_ITEM( Settings::Colors::interfaceSelection );

		LOAD_ITEM( Settings::Misc::safeMode );
		LOAD_ITEM( Settings::Misc::showKeybinds );
		LOAD_ITEM( Settings::Misc::showActiveKeybinds );
		LOAD_ITEM( Settings::Misc::radar );
		LOAD_ITEM( Settings::Misc::revealSpectators );
		LOAD_ITEM( Settings::Misc::visualizeFov );
		LOAD_ITEM( Settings::Misc::panicHotkey );

		fin.close();
	}
}