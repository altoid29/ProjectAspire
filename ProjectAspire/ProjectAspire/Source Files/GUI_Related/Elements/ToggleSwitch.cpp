#include "../../Header Files/Framework/ToggleSwitch.h"

#define SPACING 200

void ToggleSwitch::Add( float x, float y, std::string name, bool* variable )
{
	// Initialize data.
	this->x = x;
	this->y = y;
	this->variable = variable;
	this->name = name;

	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::UIColorT( 255, 255, 255, 255 ), x, y, false, name.c_str(), true );

	// Add the switch outline.
	Renderer::AddRect( Renderer::UIColorT( 82, 82, 82, 255 ), x + SPACING + 25, y + 2, 7, 7 );

	const Renderer::UIColorT desiredColor = *variable ? Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ) : Renderer::UIColorT( 18, 18, 18, 255 );

	// Add the switch fill.
	Renderer::AddFilledRect( desiredColor, x + SPACING + 26, y + 3, 6, 6 );
}

void ToggleSwitch::Handle()
{
	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ), x, y, false, name.c_str(), true );

	if ( g_globals->NtUserGetAsyncKeyState( VK_RIGHT ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		*variable = true;
	else if ( g_globals->NtUserGetAsyncKeyState( VK_LEFT ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		*variable = false;
}