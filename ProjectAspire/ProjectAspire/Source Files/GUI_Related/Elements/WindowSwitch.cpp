#include "../../Header Files/Framework/WindowSwitch.h"

void WindowSwitch::Add( Vector2 position, float sizeY, const std::string name, std::vector<std::string>tabs, int* currentTab )
{
	// Tab navigation.
	// Todo: Improve so we can use arrow keys.
	if ( g_globals->NtUserGetAsyncKeyState( VK_F2 ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window && *currentTab < tabs.size() - 1 )
		*currentTab += 1;
	else if ( g_globals->NtUserGetAsyncKeyState( VK_F1 ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window && *currentTab > 0 )
		*currentTab -= 1;

	constexpr static size_t placeholderWidth = 400;
	this->size.x = placeholderWidth;
	this->size.y = sizeY;

	// Outline.
	Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), position.x, position.y, placeholderWidth, sizeY );

	// Fill.
	Renderer::AddFilledRect( Renderer::UIColorT( 5, 5, 5, 100 ), position.x + 1, position.y + 1, placeholderWidth - 1, sizeY - 1 );

	// Top rectangle.
	Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), position.x, position.y, placeholderWidth, 35 );

	// Label.
	Renderer::AddString( g_globals->renderer->tahoma, Renderer::UIColorT( 255, 255, 255, 255 ), position.x + 10, position.y + 11, false, name.c_str(), true );

	// Iterate through the amount of tabs we have.
	for ( size_t i = 0; i < tabs.size() + 1; i++ )
	{
		// Line seperator.
		if ( i > 0 )
			Renderer::AddFilledRect( Renderer::UIColorT( 0, 0, 0, 255 ), position.x + 1, position.y + 36 + ( i * 35 ) - 1, placeholderWidth - 1, 1 );

		// Determine the current sub tab.
		this->currentSubTab = *currentTab;

		// Label.
		if ( i < tabs.size() )
		{
			const Renderer::UIColorT desiredColor = i == *currentTab ? Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ) : Renderer::UIColorT( 255, 255, 255, 255 );

			// Current tab label.
			Renderer::AddString( g_globals->renderer->tahoma, desiredColor, position.x + 10, position.y + 46 + ( i * 35 ), false, tabs[ i ].c_str(), true );

			const Renderer::UIColorT desiredArrowColor = this->currentSubTab == i ? Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ) : Renderer::UIColorT( 255, 255, 255, 255 );

			// Right side arrow.
			Renderer::AddString( g_globals->renderer->tahoma, desiredArrowColor, position.x + placeholderWidth - 17, position.y + 46 + ( i * 35 ), false, ">", true );
		}
	}
}