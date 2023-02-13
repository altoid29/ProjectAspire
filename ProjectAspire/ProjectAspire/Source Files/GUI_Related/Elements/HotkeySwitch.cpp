#include "../../Header Files/Framework/HotkeySwitch.h"

#define SPACING 153

// These are the Windows virtual keys in order.
static const std::string virtualKeyNames[] =
{
	"", _( "Mouse1" ), _( "Mouse2" ), _( "Cancel" ), _( "Mouse3" ), _( "Mouse4" ), _( "Mouse5" ), _( "[7]" ),
	_( "Backspace" ), _( "Tab" ), _( "[10]" ), _( "[11]" ), _( "Num 5" ), _( "Enter" ), _( "[14]" ), _( "[15]" ), _( "Shift" ),
	_( "Ctrl" ), _( "Alt" ), _( "[19]" ), _( "Caps" ), _( "[21]" ), _( "[22]" ), _( "[23]" ), _( "[24]" ), _( "[25]" ),
	_( "[26]" ), _( "Esc" ), _( "[28]" ), _( "[29]" ), _( "[30]" ), _( "[31]" ), _( "Space" ), _( "Page-up" ), _( "Page-down" ), _( "End" ),
	_( "Home" ), _( "Left" ), _( "Up" ), _( "Right" ), _( "Down" ), _( "[41]" ), _( "[42]" ), _( "[43]" ), _( "[44]" ), _( "Insert" ),
	_( "Delete" ), _( "[47]" ), _( "0" ), _( "1" ), _( "2" ), _( "3" ), _( "4" ), _( "5" ), _( "6" ), _( "7" ), _( "8" ), _( "9" ),
	_( "[58]" ),  _( "[59]" ), _( "[60]" ), _( "[61]" ), _( "[62]" ), _( "[63]" ), _( "[64]" ), _( "A" ), _( "B" ), _( "C" ), _( "D" ),
	_( "E" ),  _( "F" ), _( "G" ), _( "H" ), _( "I" ), _( "J" ), _( "K" ), _( "L" ), _( "M" ), _( "N" ), _( "O" ), _( "P" ), _( "Q" ),
	_( "R" ), _( "S" ), _( "T" ), _( "U" ), _( "V" ), _( "W" ), _( "X" ), _( "Y" ), _( "Z" ), _( "Left-win" ), _( "Right-win" ),
	_( "App" ), _( "[94]" ),  _( "[95]" ), _( "Num-0" ), _( "Num-1" ), _( "Num-2" ), _( "Num-3" ), _( "Num-4" ), _( "Num-5" ),
	_( "Num-6" ), _( "Num-7" ), _( "Num-8" ), _( "Num-9" ), _( "Num-mult" ), _( "Num-plus" ), _( "[108]" ), _( "Num-sub" ), _( "Num-dec" ),
	_( "Num-div" ), _( "F1" ), _( "F2" ), _( "F3" ), _( "F4" ), _( "F5" ), _( "F6" ), _( "F7" ), _( "F8" ), _( "F9" ), _( "F10" ),
	_( "F11" ), _( "F12" ), _( "F13" ), _( "F14" ), _( "F15" ), _( "F16" ), _( "F17" ),  _( "F18" ), _( "F19" ), _( "F20" ), _( "F21" ),
	_( "F22" ), _( "F23" ), _( "F24" ), _( "[136]" ), _( "[137]" ), _( "[138]" ), _( "[139]" ), _( "[140]" ), _( "[141]" ), _( "[142]" ),
	_( "[143]" ), _( "Num-lock" ), _( "Break" ), _( "[146]" ), _( "[147]" ), _( "[148]" ), _( "[149]" ), _( "[150]" ), _( "[151]" ), _( "[152]" ),
	_( "[153]" ), _( "[154]" ), _( "[155]" ), _( "[156]" ),  _( "[157]" ), _( "[158]" ), _( "[159]" ), _( "[160]" ), _( "[161]" ), _( "Ctrl" ),
	_( "Ctrl" ), _( "Alt" ), _( "Alt" ), _( "[166]" ), _( "[167]" ), _( "[168]" ), _( "[169]" ), _( "[170]" ), _( "[171]" ), _( "M" ), _( "D" ),
	_( "C" ), _( "B" ),  _( "P" ), _( "Q" ), _( "J" ), _( "G" ), _( "[180]" ), _( "[181]" ), _( "[182]" ), _( "F" ), _( "[184]" ), _( "[185]" ),
	_( ";" ), _( "=" ), _( " )," ), _( "-" ), _( "." ), _( "/" ), _( "Grave" ), _( "[193]" ), _( "[194]" ), _( "[195]" ), _( "[196]" ),
	_( "[197]" ), _( "[198]" ),  _( "[199]" ), _( "[200]" ), _( "[201]" ), _( "[202]" ), _( "[203]" ), _( "[204]" ), _( "[205]" ), _( "[206]" ),
	_( "[207]" ), _( "[208]" ), _( "[209]" ), _( "[210]" ), _( "[211]" ), _( "[212]" ), _( "[213]" ), _( "[214]" ), _( "[215]" ), _( "[216]" ),
	_( "[217]" ),  _( "[218]" ), _( "[" ), _( "\\" ), _( "]" ), _( "[222]" ), _( "[223]" ), _( "[224]" ), _( "[225]" ), _( "\\" ), _( "[227]" ),
	_( "[228]" ), _( "[229]" ), _( "[230]" ), _( "[231]" ), _( "[232]" ), _( "[233]" ), _( "Right-win" ), _( "[235]" ), _( "[236]" ), _( "[237]" ),
	_( "[238]" ), _( "[239]" ), _( "[240]" ), _( "Left-win" ), _( "[242]" ), _( "[243]" ), _( "[244]" ), _( "[245]" ), _( "[246]" ), _( "[247]" ),
	_( "[248]" ), _( "App" ), _( "[250]" ), _( "[251]" ), _( "[252]" ), _( "[253]" )
};

void HotkeySwitch::Add( float x, float y, std::string name, int* key )
{
	// Initialize our data.
	this->x = x;
	this->y = y;
	this->keyValue = key;
	this->name = name;

	static const auto font1 = g_globals->renderer->tahoma;
	static const auto font2 = g_globals->renderer->sliderSmallFont;

	// Draw the label.
	Renderer::AddString( font1, Renderer::UIColorT( 255, 255, 255, 255 ), x, y, false, name.c_str(), true );

	// Draw outline rectangle.
	Renderer::AddRect( Renderer::UIColorT( 82, 82, 82, 255 ), x + SPACING + 20, y, 59, 13 );

	// Draw selected key name.
	const char* currentKeyName = virtualKeyNames[ *keyValue ].c_str();
	const auto width = Renderer::GetTextWidth( font2, this->waitingForKey ? "..." : currentKeyName );
	Renderer::AddString( font2, Renderer::UIColorT( 255, 255, 255, 255 ), x + SPACING + 51 - width / 2, y + 1, false, this->waitingForKey ? "..." : currentKeyName, false );
}

void HotkeySwitch::Handle()
{
	static const auto font = g_globals->renderer->tahoma;

	// Add the toggle label.
	Renderer::AddString( font, Renderer::DetermineColorFromSelection( Settings::Colors::interfaceSelection ), x, y, false, name.c_str(), true );

	static bool waitingForKeyInput = false;

	// We've pressed enter, and are currently on this element.
	// Lets wait for the user to toggle a key.
	if ( g_globals->NtUserGetAsyncKeyState( VK_RETURN ) && g_globals->GetForegroundWindow() == g_interfaces->Window )
	{
		waitingForKeyInput = true;
		this->waitingForKey = true;
	}

	// We're waiting for a key and have pressed escape.
	// We no longer want to select a key.
	if ( waitingForKeyInput && g_globals->NtUserGetAsyncKeyState( VK_ESCAPE ) && g_globals->GetForegroundWindow() == g_interfaces->Window )
	{
		*keyValue = 0;
		waitingForKeyInput = false;
		this->waitingForKey = false;

		return;
	}

	if ( waitingForKeyInput )
	{
		// Iterate all keys.
		for ( size_t i = 0; i < 254; i++ )
		{
			if ( g_globals->NtUserGetAsyncKeyState( i ) & 1 && !g_globals->NtUserGetAsyncKeyState( VK_RETURN ) && i > 0 && g_globals->GetForegroundWindow() == g_interfaces->Window )
			{
				*keyValue = i;
				waitingForKeyInput = false;
				this->waitingForKey = false;
				break;
			}
		}
	}
}