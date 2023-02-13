#include "../../Header Files/Framework/SelectionSwitch.h"

#define SPACING 153

void SelectionSwitch::Add( float x, float y, std::string name, int* currentItem, std::vector<std::string>items )
{
	// Initialize our data.
	this->x = x;
	this->y = y;
	this->name = name;
	this->currentItem = currentItem;
	this->items = items;

	// Draw the label.
	static const auto font1 = g_globals->renderer->tahoma;
	Renderer::AddString( font1, Renderer::UIColorT( 255, 255, 255, 255 ), x, y, false, name.c_str(), true );

	// Draw outline.
	static const auto font2 = g_globals->renderer->sliderSmallFont;
	Renderer::AddRect( Renderer::UIColorT( 82, 82, 82, 255 ), x + SPACING + 20, y, 59, 13 );

	// Draw curent selection.
	const auto width = Renderer::GetTextWidth( font2, items[ *currentItem ].c_str() );
	Renderer::AddString( font2, Renderer::UIColorT( 255, 255, 255, 255 ), x + SPACING + 51 - width / 2, y + 1, false, items[ *currentItem ].c_str(), false );
}

void SelectionSwitch::Handle()
{
	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ), x, y, false, name.c_str(), true );

	if ( g_globals->NtUserGetAsyncKeyState( VK_LEFT ) & 1 && *currentItem > 0 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		*currentItem -= 1;
	else if ( g_globals->NtUserGetAsyncKeyState( VK_RIGHT ) & 1 && *currentItem < items.size() - 1 && g_globals->GetForegroundWindow() == g_interfaces->Window )
		*currentItem += 1;
}