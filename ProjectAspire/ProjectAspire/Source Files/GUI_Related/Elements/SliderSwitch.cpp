#include "../../Header Files/Framework/SliderSwitch.h"

#define SPACING 153

void SliderSwitch::Add( float x, float y, std::string name, int* variable, int minimum, int maximum )
{
	// Initialize Data.
	this->x = x;
	this->y = y;
	this->min = minimum;
	this->max = maximum;
	this->name = name;
	this->currentValue = variable;

	static const auto font = g_globals->renderer->tahoma;
	static const auto font2 = g_globals->renderer->sliderSmallFont;

	// Add the label.
	Renderer::AddString( font, Renderer::UIColorT( 255, 255, 255, 255 ), x, y, false, name.c_str(), true );

	// Add outline.
	Renderer::AddRect( Renderer::UIColorT( 82, 82, 82, 255 ), x + SPACING + 20, y, 59, 13 );

	// Add the minimum value / maximum value in the box in the middle.
	const int value = *variable;
	const auto str = tfm::format( _( "%i/%i" ), value, maximum );
	const auto width = Renderer::GetTextWidth( font2, str.c_str() );
	Renderer::AddString( font2, Renderer::UIColorT( 255, 255, 255, 255 ), x + SPACING + 51 - width / 2, y + 1, false, str.c_str(), false );
}

void SliderSwitch::Handle()
{
	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ), x, y, false, name.c_str(), true );

	if ( g_globals->NtUserGetAsyncKeyState( VK_RIGHT ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window && *currentValue < this->max )
		*currentValue += 1;
	else if ( g_globals->NtUserGetAsyncKeyState( VK_LEFT ) & 1 && g_globals->GetForegroundWindow() == g_interfaces->Window && *currentValue > this->min )
		*currentValue -= 1;
}