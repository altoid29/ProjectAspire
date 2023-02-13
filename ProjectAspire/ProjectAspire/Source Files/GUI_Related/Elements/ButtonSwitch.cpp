#include "../../Header Files/Framework/ButtonSwitch.h"

#define SPACING 153

void ButtonSwitch::Add( float x, float y, std::string name, std::string buttonName, std::function<void()>callback )
{
	// Set our data.
	this->x = x;
	this->y = y;
	this->callback = callback;
	this->name = name;

	static const auto font1 = g_globals->renderer->tahoma;
	static const auto font2 = g_globals->renderer->sliderSmallFont;

	// Draw the label.
	Renderer::AddString( font1, Renderer::UIColorT( 255, 255, 255, 255 ), x, y, false, name.c_str(), true );

	// Draw outline.
	Renderer::AddRect( Renderer::UIColorT( 82, 82, 82, 255 ), x + SPACING + 20, y, 59, 13 );

	// Draw name.
	const auto Width = Renderer::GetTextWidth( font2, buttonName.c_str() );
	Renderer::AddString( font2, Renderer::UIColorT( 255, 255, 255, 255 ), x + SPACING + 51 - Width / 2, y + 1, false, buttonName.c_str(), false );
}

void ButtonSwitch::Handle()
{
	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ), x, y, false, name.c_str(), true );

	// Do the callback when we're pressing ENTER.
	if ( g_globals->NtUserGetAsyncKeyState( VK_RETURN ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		this->callback();
}