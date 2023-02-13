#pragma once

#include <memory>
#include <vector>

#include "../SDK/ValveSDK.h"

#define CREATE_VARIABLE(type, name, value) inline type name = value;

namespace Settings
{
	namespace Aimbot
	{
		CREATE_VARIABLE( bool, enable, false );
		CREATE_VARIABLE( int, targetSelection, 0 );
		CREATE_VARIABLE( int, hotkey, 1 );
		CREATE_VARIABLE( bool, visibleCheck, false );
		CREATE_VARIABLE( bool, teamCheck, false );
		CREATE_VARIABLE( int, fovRadius, 0 );
		CREATE_VARIABLE( bool, dynamicSmoothness, false );
		CREATE_VARIABLE( int, hitbox, 0 );
		CREATE_VARIABLE( int, aimAfterXShots, 0 );
		CREATE_VARIABLE( bool, flashDisable, false );
		CREATE_VARIABLE( bool, smokeDisable, false );
		CREATE_VARIABLE( bool, airDisable, false );
		CREATE_VARIABLE( bool, specatatorDisable, false );
	};

	namespace Triggerbot
	{
		CREATE_VARIABLE( bool, enable, false );
		CREATE_VARIABLE( bool, teamCheck, false );
		CREATE_VARIABLE( bool, smokeCheck, false );
		CREATE_VARIABLE( bool, flashCheck, false );
		CREATE_VARIABLE( int, hotkey, 0 );
		CREATE_VARIABLE( int, hitbox, 0 );
		CREATE_VARIABLE( int, delay, 0 );
	};

	namespace ESP
	{
		CREATE_VARIABLE( bool, enable, false );
		CREATE_VARIABLE( bool, visibleCheck, false );
		CREATE_VARIABLE( bool, box, false );
		CREATE_VARIABLE( bool, name, false );
		CREATE_VARIABLE( bool, health, false );
		CREATE_VARIABLE( bool, distance, false );
		CREATE_VARIABLE( bool, area, false );
		CREATE_VARIABLE( bool, skeleton, false );
		CREATE_VARIABLE( bool, lines, false );
		CREATE_VARIABLE( int, linesPosition, 2 );
		CREATE_VARIABLE( bool, dot, false );
		CREATE_VARIABLE( bool, teamCheck, false );
	};

	namespace Projectiles
	{
		CREATE_VARIABLE( bool, enable, false );
		CREATE_VARIABLE( bool, visibleCheck, false );
		CREATE_VARIABLE( bool, weaponNames, false );
		CREATE_VARIABLE( bool, bomb, false );
		CREATE_VARIABLE( bool, hostage, false );
		CREATE_VARIABLE( bool, utilities, false );
	}

	namespace Colors
	{
		CREATE_VARIABLE( int, boxSelection, 7 );
		CREATE_VARIABLE( int, nameSelection, 7 );
		CREATE_VARIABLE( int, distanceSelection, 7 );
		CREATE_VARIABLE( int, areaSelection, 7 );
		CREATE_VARIABLE( int, skeletonSelection, 7 );
		CREATE_VARIABLE( int, linesSelection, 7 );
		CREATE_VARIABLE( int, dotSelection, 7 );
		CREATE_VARIABLE( int, weaponNamesSelection, 7 );
		CREATE_VARIABLE( int, bombSelection, 7 );
		CREATE_VARIABLE( int, hostageSelection, 7 );
		CREATE_VARIABLE( int, utilitiesSelection, 7 );
		CREATE_VARIABLE( int, interfaceSelection, 6 );
		CREATE_VARIABLE( int, fovSelection, 7 );
	}

	namespace Misc
	{
		CREATE_VARIABLE( bool, safeMode, true );
		CREATE_VARIABLE( bool, showKeybinds, true );
		CREATE_VARIABLE( bool, showActiveKeybinds, false );
		CREATE_VARIABLE( bool, radar, false );
		CREATE_VARIABLE( bool, revealSpectators, false );
		CREATE_VARIABLE( int, panicHotkey, 0 );
		CREATE_VARIABLE( bool, visualizeFov, false );
		CREATE_VARIABLE( std::vector<int>, getSpectatorObserverMode, {} );
		CREATE_VARIABLE( std::vector<std::string>, getSpectators, {} );
	}
}