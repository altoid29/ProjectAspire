#include "../../Header Files/Menu.h"

#include "../../Header Files/Framework/ToggleSwitch.h"
#include "../../Header Files/Framework/SliderSwitch.h"
#include "../../Header Files/Framework/SelectionSwitch.h"
#include "../../Header Files/Framework/HotkeySwitch.h"
#include "../../Header Files/Framework/ButtonSwitch.h"
#include "../../Header Files/Framework/WindowSwitch.h"

namespace Switches
{
	// Aimbot related.
	inline static ToggleSwitch AimbotEnable{};
	inline static SelectionSwitch AimbotTargetSelection{};
	inline static HotkeySwitch AimbotHotkey{};
	inline static ToggleSwitch AimbotVisibleCheck{};
	inline static ToggleSwitch AimbotTeamCheck{};
	inline static SliderSwitch AimbotFOVRadius{};
	inline static ToggleSwitch AimbotDynamicSmoothness{};
	inline static SelectionSwitch AimbotHitbox{};
	inline static SliderSwitch AimbotAfterXShots{};
	inline static ToggleSwitch AimbotFlashDisable{};
	inline static ToggleSwitch AimbotSmokeDisable{};
	inline static ToggleSwitch AimbotAirDisable{};
	inline static ToggleSwitch AimbotSpectatedDisable{};

	// Triggerbot related.
	inline static ToggleSwitch TriggerbotEnable{};
	inline static HotkeySwitch TriggerbotHotkey{};
	inline static SelectionSwitch TriggerbotHitbox{};
	inline static ToggleSwitch TriggerbotTeamCheck{};
	inline static ToggleSwitch TriggerbotSmokeCheck{};
	inline static ToggleSwitch TriggerbotFlashCheck{};
	inline static SliderSwitch TriggerbotDelay{};

	// ESP related.
	inline static ToggleSwitch ESPEnable{};
	inline static ToggleSwitch ESPVisibleCheck{};
	inline static ToggleSwitch ESPTeamCheck{};
	inline static ToggleSwitch ESPBox{};
	inline static ToggleSwitch ESPName{};
	inline static ToggleSwitch ESPHealth{};
	inline static ToggleSwitch ESPDistance{};
	inline static ToggleSwitch ESPArea{};
	inline static ToggleSwitch ESPSkeleton{};
	inline static ToggleSwitch ESPLines{};
	inline static SelectionSwitch ESPLinesPosition{};
	inline static ToggleSwitch ESPSubtle{};

	// Projectile related.
	inline static ToggleSwitch ProjectilesEnable{};
	inline static ToggleSwitch ProjectilesVisibleCheck{};
	inline static ToggleSwitch ProjectilesWeaponNames{};
	inline static ToggleSwitch ProjectilesBomb{};
	inline static ToggleSwitch ProjectilesHostage{};
	inline static ToggleSwitch ProjectilesUtilities{};

	// Colors related.
	inline static SelectionSwitch ColorsBoxColorSelection{};
	inline static SelectionSwitch ColorsNameColorSelection{};
	inline static SelectionSwitch ColorsDistanceColorSelection{};
	inline static SelectionSwitch ColorsAreaColorSelection{};
	inline static SelectionSwitch ColorsSkeletonColorSelection{};
	inline static SelectionSwitch ColorsLinesColorSelection{};
	inline static SelectionSwitch ColorsDotColorSelection{};
	inline static SelectionSwitch ColorsWeaponNamesColorSelection{};
	inline static SelectionSwitch ColorsBombColorSelection{};
	inline static SelectionSwitch ColorsHostageColorSelection{};
	inline static SelectionSwitch ColorsUtilitiesColorSelection{};
	inline static SelectionSwitch ColorsInterfaceSelection{};
	inline static SelectionSwitch ColorsFOVRadiusSelection{};

	// Other related.
	inline static ToggleSwitch Other_SafeMode{};
	inline static ToggleSwitch Other_ShowKeybinds{};
	inline static ToggleSwitch Other_ShowActiveKeybinds{};
	inline static ToggleSwitch Other_Radar{};
	inline static ToggleSwitch Other_RevealSpectators{};
	inline static ToggleSwitch Other_VisualizeFOV{};
	inline static ButtonSwitch Other_SaveSettings{};
	inline static ButtonSwitch Other_LoadSettings{};
	inline static HotkeySwitch Other_PanicHotkey{};
	inline static ButtonSwitch Other_Unload{};
}

void AimbotTab( float MenuPosX, float MenuPosY )
{
	Switches::AimbotEnable.Add( MenuPosX, MenuPosY, _( "Enable" ), &Settings::Aimbot::enable );
	Switches::AimbotTargetSelection.Add( MenuPosX, MenuPosY + 20, _( "Target selection" ), &Settings::Aimbot::targetSelection, { _( "Crosshair" ), _( "Distance" ), _( "Health" ) } );
	Switches::AimbotHotkey.Add( MenuPosX, MenuPosY + 40, _( "Hotkey" ), &Settings::Aimbot::hotkey );
	Switches::AimbotVisibleCheck.Add( MenuPosX, MenuPosY + 60, _( "Visible check" ), &Settings::Aimbot::visibleCheck );
	Switches::AimbotTeamCheck.Add( MenuPosX, MenuPosY + 80, _( "Exclude team" ), &Settings::Aimbot::teamCheck );
	Switches::AimbotFOVRadius.Add( MenuPosX, MenuPosY + 100, _( "Field of view" ), &Settings::Aimbot::fovRadius, 0, 35 );
	Switches::AimbotDynamicSmoothness.Add( MenuPosX, MenuPosY + 120, _( "Adaptive smoothness" ), &Settings::Aimbot::dynamicSmoothness );
	Switches::AimbotHitbox.Add( MenuPosX, MenuPosY + 140, _( "Hitbox" ), &Settings::Aimbot::hitbox, { _( "Head" ), _( "Neck" ), _( "Chest" ), _( "Stomach" ), _( "Pelvis" ) } );
	Switches::AimbotAfterXShots.Add( MenuPosX, MenuPosY + 160, _( "Aim after X shots" ), &Settings::Aimbot::aimAfterXShots, 0, 5 );
	Switches::AimbotFlashDisable.Add( MenuPosX, MenuPosY + 180, _( "Flash disable" ), &Settings::Aimbot::flashDisable );
	Switches::AimbotSmokeDisable.Add( MenuPosX, MenuPosY + 200, _( "Smoke disable" ), &Settings::Aimbot::smokeDisable );
	Switches::AimbotAirDisable.Add( MenuPosX, MenuPosY + 220, _( "Air disable" ), &Settings::Aimbot::airDisable );
	Switches::AimbotSpectatedDisable.Add( MenuPosX, MenuPosY + 240, _( "First-person spectated disable" ), &Settings::Aimbot::specatatorDisable );
}

void TriggerbotTab( float MenuPosX, float MenuPosY )
{
	Switches::TriggerbotEnable.Add( MenuPosX, MenuPosY, _( "Enable" ), &Settings::Triggerbot::enable );
	Switches::TriggerbotHotkey.Add( MenuPosX, MenuPosY + 20, _( "Hotkey" ), &Settings::Triggerbot::hotkey );
	Switches::TriggerbotHitbox.Add( MenuPosX, MenuPosY + 40, _( "Hitbox" ), &Settings::Triggerbot::hitbox, { _( "Head" ), _( "Chest" ), _( "Stomach" ), _( "Lower" ), _( "Crosshair" ) } );
	Switches::TriggerbotTeamCheck.Add( MenuPosX, MenuPosY + 60, _( "Exclude team" ), &Settings::Triggerbot::teamCheck );
	Switches::TriggerbotSmokeCheck.Add( MenuPosX, MenuPosY + 80, _( "Smoke disable" ), &Settings::Triggerbot::smokeCheck );
	Switches::TriggerbotFlashCheck.Add( MenuPosX, MenuPosY + 100, _( "Flash disable" ), &Settings::Triggerbot::flashCheck );
	Switches::TriggerbotDelay.Add( MenuPosX, MenuPosY + 120, _( "Delay (ms)" ), &Settings::Triggerbot::delay, 0, 1000 );
}

void ESPTab( float MenuPosX, float MenuPosY )
{
	Switches::ESPEnable.Add( MenuPosX, MenuPosY, _( "Enable" ), &Settings::ESP::enable );
	Switches::ESPVisibleCheck.Add( MenuPosX, MenuPosY + 20, _( "Visible check" ), &Settings::ESP::visibleCheck );
	Switches::ESPTeamCheck.Add( MenuPosX, MenuPosY + 40, _( "Exclude team" ), &Settings::ESP::teamCheck );
	Switches::ESPBox.Add( MenuPosX, MenuPosY + 60, _( "Box" ), &Settings::ESP::box );
	Switches::ESPName.Add( MenuPosX, MenuPosY + 80, _( "Name" ), &Settings::ESP::name );
	Switches::ESPHealth.Add( MenuPosX, MenuPosY + 100, _( "Health" ), &Settings::ESP::health );
	Switches::ESPDistance.Add( MenuPosX, MenuPosY + 120, _( "Distance" ), &Settings::ESP::distance );
	Switches::ESPArea.Add( MenuPosX, MenuPosY + 140, _( "Map area" ), &Settings::ESP::area );
	Switches::ESPSkeleton.Add( MenuPosX, MenuPosY + 160, _( "Skeleton" ), &Settings::ESP::skeleton );
	Switches::ESPLines.Add( MenuPosX, MenuPosY + 180, _( "Tracers" ), &Settings::ESP::lines );
	Switches::ESPLinesPosition.Add( MenuPosX, MenuPosY + 200, _( "Position" ), &Settings::ESP::linesPosition, { _( "Top" ), _( "Middle" ), _( "Bottom" ) } );
	Switches::ESPSubtle.Add( MenuPosX, MenuPosY + 220, _( "Head dot" ), &Settings::ESP::dot );
}

void ProjectilesTab( float MenuPosX, float MenuPosY )
{
	Switches::ProjectilesEnable.Add( MenuPosX, MenuPosY, _( "Enable" ), &Settings::Projectiles::enable );
	Switches::ProjectilesVisibleCheck.Add( MenuPosX, MenuPosY + 20, _( "Visible Check" ), &Settings::Projectiles::visibleCheck );
	Switches::ProjectilesWeaponNames.Add( MenuPosX, MenuPosY + 40, _( "Weapon names" ), &Settings::Projectiles::weaponNames );
	Switches::ProjectilesBomb.Add( MenuPosX, MenuPosY + 60, _( "Bomb" ), &Settings::Projectiles::bomb );
	Switches::ProjectilesHostage.Add( MenuPosX, MenuPosY + 80, _( "Hostages" ), &Settings::Projectiles::hostage );
	Switches::ProjectilesUtilities.Add( MenuPosX, MenuPosY + 100, _( "Utilities" ), &Settings::Projectiles::utilities );
}

void ColorsTab( float MenuPosX, float MenuPosY )
{
	Switches::ColorsBoxColorSelection.Add( MenuPosX, MenuPosY, _( "Box color" ), &Settings::Colors::boxSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsNameColorSelection.Add( MenuPosX, MenuPosY + 20, _( "Name color" ), &Settings::Colors::nameSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsDistanceColorSelection.Add( MenuPosX, MenuPosY + 40, _( "Distance color" ), &Settings::Colors::distanceSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsAreaColorSelection.Add( MenuPosX, MenuPosY + 60, _( "Area color" ), &Settings::Colors::areaSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsSkeletonColorSelection.Add( MenuPosX, MenuPosY + 80, _( "Skeleton color" ), &Settings::Colors::skeletonSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsLinesColorSelection.Add( MenuPosX, MenuPosY + 100, _( "Lines color" ), &Settings::Colors::linesSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsDotColorSelection.Add( MenuPosX, MenuPosY + 120, _( "Dot color" ), &Settings::Colors::dotSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsWeaponNamesColorSelection.Add( MenuPosX, MenuPosY + 140, _( "Weapon names color" ), &Settings::Colors::weaponNamesSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsBombColorSelection.Add( MenuPosX, MenuPosY + 160, _( "Bomb color color" ), &Settings::Colors::bombSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsHostageColorSelection.Add( MenuPosX, MenuPosY + 180, _( "Hostage color" ), &Settings::Colors::hostageSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsUtilitiesColorSelection.Add( MenuPosX, MenuPosY + 200, _( "Utilities color" ), &Settings::Colors::utilitiesSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsInterfaceSelection.Add( MenuPosX, MenuPosY + 220, _( "Interface color" ), &Settings::Colors::interfaceSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
	Switches::ColorsFOVRadiusSelection.Add( MenuPosX, MenuPosY + 240, _( "Field of view radius color" ), &Settings::Colors::fovSelection, { _( "Red" ), _( "Orange" ), _( "Yellow" ), _( "Green" ), _( "Blue" ), _( "Light blue" ), _( "Violet" ), _( "White" ), _( "Black" ), _( "Pink" ) } );
}

void OtherTab( float MenuPosX, float MenuPosY )
{
	Switches::Other_SafeMode.Add( MenuPosX, MenuPosY, _( "Safety mode" ), &Settings::Misc::safeMode );
	Switches::Other_ShowKeybinds.Add( MenuPosX, MenuPosY + 20, _( "Show navigation-keys" ), &Settings::Misc::showKeybinds );
	Switches::Other_ShowActiveKeybinds.Add( MenuPosX, MenuPosY + 40, _( "Show active key-binds" ), &Settings::Misc::showActiveKeybinds );
	Switches::Other_Radar.Add( MenuPosX, MenuPosY + 60, _( "Server radar" ), &Settings::Misc::radar );
	Switches::Other_RevealSpectators.Add( MenuPosX, MenuPosY + 80, _( "Reveal spectators" ), &Settings::Misc::revealSpectators );
	Switches::Other_VisualizeFOV.Add( MenuPosX, MenuPosY + 100, _( "Show field of view radius" ), &Settings::Misc::visualizeFov );
	Switches::Other_SaveSettings.Add( MenuPosX, MenuPosY + 120, _( "Save settings" ), _( "Save" ), [] { Configuration::Save(); } );
	Switches::Other_LoadSettings.Add( MenuPosX, MenuPosY + 140, _( "Load settings" ), _( "Load" ), [] { Configuration::Load(); } );
	Switches::Other_PanicHotkey.Add( MenuPosX, MenuPosY + 160, _( "Panic hotkey" ), &Settings::Misc::panicHotkey );
	Switches::Other_Unload.Add( MenuPosX, MenuPosY + 180, _( "Unload" ), _( "Unload" ), [] { g_globals->shouldUnload = true; } );
}

void Menu::Render()
{
	// Swap state when we press menu key.
	if ( g_globals->NtUserGetAsyncKeyState( VK_INSERT ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		this->isOpened = !this->isOpened;

	if ( !this->isOpened )
		return;

	static int CurrentTab = 0;

	static WindowSwitch Window{};
	float PosX = ( CROSSHAIR_X - Window.size.x / 2 );
	float PosY = ( CROSSHAIR_Y - Window.size.y / 2 );

	// Decrypt altoid29.
	CHAR Me[] = { _( "ehpkm`6=" ) };
	for ( size_t i = 0; i < strlen( Me ); i++ )
	{
		Me[ i ] ^= 0x4;
	}

	Window.Add( { PosX, PosY }, 250, tfm::format( _( "ProjectAspire 1.2 | By %s" ), Me ), { _( "Aimbot" ), _( "Triggerbot" ), _( "Players" ), _( "Projectiles" ), _( "Colors" ), _( "Other" ) }, &CurrentTab );

	if ( Settings::Misc::showKeybinds )
	{
		static std::vector<std::string>Items = { _( "Insert: Toggle interface" ), _( "F1: Previous tab" ), _( "F2: Next tab" ), _( "Up arrow: Previous item" ), _( "Down arrow: Next item" ), _( "Left arrow: Disable" ), _( "Right arrow: Enable" ), _( "Enter: Select hotkey" ), _( "Enter: Button callback" ) };
		for ( size_t i = 0; i < Items.size(); i++ )
		{
			const auto TextWidth = Renderer::GetTextWidth( g_globals->renderer->tahoma, Items[ i ].c_str() );
			Renderer::AddString( g_globals->renderer->tahoma, Renderer::UIColorT( 255, 255, 255, 255 ), g_globals->screenW - 10 - TextWidth, 10 + ( i * 16 ), false, Items[ i ].c_str(), true );
		}
	}

	switch ( CurrentTab )
	{
		// Aimbot.
		case 0:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 35, 250, 265 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 35 + 1, 249, 264 );

			AimbotTab( PosX + Window.size.x + 9, PosY + 42 );

			if ( this->currentTab > 14 )
				this->currentTab = 0;

			switch ( this->currentTab )
			{
				case 0: Switches::AimbotEnable.Handle(); break;
				case 1: Switches::AimbotTargetSelection.Handle(); break;
				case 2: Switches::AimbotHotkey.Handle(); break;
				case 3: Switches::AimbotVisibleCheck.Handle(); break;
				case 4: Switches::AimbotVisibleCheck.Handle(); break;
				case 5: Switches::AimbotTeamCheck.Handle(); break;
				case 6: Switches::AimbotFOVRadius.Handle(); break;
				case 7: Switches::AimbotFOVRadius.Handle(); break;
				case 8: Switches::AimbotDynamicSmoothness.Handle(); break;
				case 9: Switches::AimbotHitbox.Handle(); break;
				case 10:Switches::AimbotAfterXShots.Handle(); break;
				case 11: Switches::AimbotFlashDisable.Handle(); break;
				case 12: Switches::AimbotSmokeDisable.Handle(); break;
				case 13: Switches::AimbotAirDisable.Handle(); break;
				case 14: Switches::AimbotSpectatedDisable.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 0 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 14 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;

		// Triggerbot.
		case 1:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 70, 250, Window.size.y - 101 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 70 + 1, 249, Window.size.y - 1 - 101 );

			TriggerbotTab( PosX + Window.size.x + 9, PosY + 77 );

			if ( this->currentTab < 15 || this->currentTab > 21 )
				this->currentTab = 15;

			switch ( this->currentTab )
			{
				case 15: Switches::TriggerbotEnable.Handle(); break;
				case 16: Switches::TriggerbotHotkey.Handle(); break;
				case 17: Switches::TriggerbotHitbox.Handle(); break;
				case 18: Switches::TriggerbotTeamCheck.Handle(); break;
				case 19: Switches::TriggerbotSmokeCheck.Handle(); break;
				case 20: Switches::TriggerbotFlashCheck.Handle(); break;
				case 21: Switches::TriggerbotDelay.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 15 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 21 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;

		// Players.
		case 2:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 105, 250, Window.size.y - 5 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 105 + 1, 249, Window.size.y - 1 - 5 );

			ESPTab( PosX + Window.size.x + 9, PosY + 112 );

			if ( this->currentTab < 22 || this->currentTab > 33 )
				this->currentTab = 22;

			switch ( this->currentTab )
			{
				case 22: Switches::ESPEnable.Handle(); break;
				case 23: Switches::ESPVisibleCheck.Handle(); break;
				case 24: Switches::ESPTeamCheck.Handle(); break;
				case 25: Switches::ESPBox.Handle(); break;
				case 26: Switches::ESPName.Handle(); break;
				case 27: Switches::ESPHealth.Handle(); break;
				case 28: Switches::ESPDistance.Handle(); break;
				case 29: Switches::ESPArea.Handle(); break;
				case 30: Switches::ESPSkeleton.Handle(); break;
				case 31: Switches::ESPLines.Handle(); break;
				case 32: Switches::ESPLinesPosition.Handle(); break;
				case 33: Switches::ESPSubtle.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 22 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 33 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;

		// Projectiles.
		case 3:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 140, 250, Window.size.y - 125 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 140 + 1, 249, Window.size.y - 1 - 125 );

			ProjectilesTab( PosX + Window.size.x + 9, PosY + 147 );

			if ( this->currentTab < 34 || this->currentTab > 39 )
				this->currentTab = 34;

			switch ( this->currentTab )
			{
				case 34: Switches::ProjectilesEnable.Handle(); break;
				case 35: Switches::ProjectilesVisibleCheck.Handle(); break;
				case 36: Switches::ProjectilesWeaponNames.Handle(); break;
				case 37: Switches::ProjectilesBomb.Handle(); break;
				case 38: Switches::ProjectilesHostage.Handle(); break;
				case 39: Switches::ProjectilesUtilities.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 34 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 39 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;

		// Colors.
		case 4:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 175, 250, 269 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 175 + 1, 249, 268 );

			ColorsTab( PosX + Window.size.x + 9, PosY + 182 );

			if ( this->currentTab < 40 || this->currentTab > 52 )
				this->currentTab = 40;

			switch ( this->currentTab )
			{
				case 40: Switches::ColorsBoxColorSelection.Handle(); break;
				case 41: Switches::ColorsNameColorSelection.Handle(); break;
				case 42: Switches::ColorsDistanceColorSelection.Handle(); break;
				case 43: Switches::ColorsAreaColorSelection.Handle(); break;
				case 44: Switches::ColorsSkeletonColorSelection.Handle(); break;
				case 45: Switches::ColorsLinesColorSelection.Handle(); break;
				case 46: Switches::ColorsDotColorSelection.Handle(); break;
				case 47: Switches::ColorsWeaponNamesColorSelection.Handle(); break;
				case 48: Switches::ColorsBombColorSelection.Handle(); break;
				case 49: Switches::ColorsHostageColorSelection.Handle(); break;
				case 50: Switches::ColorsUtilitiesColorSelection.Handle(); break;
				case 51: Switches::ColorsInterfaceSelection.Handle(); break;
				case 52: Switches::ColorsFOVRadiusSelection.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 40 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 52 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;

		// Other.
		case 5:
		{
			Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), PosX + Window.size.x, PosY + 210, 250, 208 );
			Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), PosX + Window.size.x + 1, PosY + 210 + 1, 249, 207 );

			OtherTab( PosX + Window.size.x + 9, PosY + 217 );

			if ( this->currentTab < 53 || this->currentTab > 62 )
				this->currentTab = 53;

			switch ( this->currentTab )
			{
				case 53: Switches::Other_SafeMode.Handle(); break;
				case 54: Switches::Other_ShowKeybinds.Handle(); break;
				case 55: Switches::Other_ShowActiveKeybinds.Handle(); break;
				case 56: Switches::Other_Radar.Handle(); break;
				case 57: Switches::Other_RevealSpectators.Handle(); break;
				case 58: Switches::Other_VisualizeFOV.Handle(); break;
				case 59: Switches::Other_SaveSettings.Handle(); break;
				case 60: Switches::Other_LoadSettings.Handle(); break;
				case 61: Switches::Other_PanicHotkey.Handle(); break;
				case 62: Switches::Other_Unload.Handle(); break;
			}

			if ( g_globals->NtUserGetAsyncKeyState( VK_UP ) & 1 && this->currentTab > 53 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab--;

			if ( g_globals->NtUserGetAsyncKeyState( VK_DOWN ) & 1 && this->currentTab < 62 && g_globals->GetForegroundWindow() == g_interfaces->Window )
				this->currentTab++;
		}
		break;
	}
}