#pragma once

#include "Include.h"
#include "Renderer.h"

namespace Renderer
{
	struct UIColorT
	{
		uint8_t r = 255;
		uint8_t g = 255;
		uint8_t b = 255;
		uint8_t a = 255;

		constexpr UIColorT() : r( 0 ), g( 0 ), b( 0 ), a( 0 ) {}
		constexpr UIColorT( uint8_t r, uint8_t g, uint8_t b, uint8_t a ) : r( r ), g( g ), b( b ), a( a ) {}
		constexpr UIColorT( uint8_t r, uint8_t g, uint8_t b ) : r( r ), g( g ), b( b ), a( 255 ) {}

		inline Color_t ToRendererColor() const
		{
			return Color_t( r, g, b, a );
		}
	};

	inline Color_t DetermineColorFromSelection2( int selection )
	{
		switch ( selection )
		{
			case 0: return Color_t( 237, 40, 40, 255 ); break;
			case 1: return Color_t( 250, 120, 45, 255 ); break;
			case 2: return Color_t( 255, 250, 97, 255 ); break;
			case 3: return Color_t( 149, 255, 79, 255 ); break;
			case 4: return Color_t( 8, 199, 252, 255 ); break;
			case 5: return Color_t( 8, 154, 252, 255 ); break;
			case 6: return Color_t( 158, 62, 247, 255 ); break;
			case 7: return Color_t( 255, 255, 255, 255 ); break;
			case 8: return Color_t( 0, 0, 0, 255 ); break;
			case 9: return Color_t( 227, 59, 121 ); break;
			default: return Color_t( 0, 0, 0, 255 ); break;
		}

		// Failed.
		return Color_t( 0, 0, 0, 255 );
	}

	inline Renderer::UIColorT DetermineColorFromSelection( int selection )
	{
		switch ( selection )
		{
			case 0: return Renderer::UIColorT( 237, 40, 40, 255 ); break;
			case 1: return Renderer::UIColorT( 250, 120, 45, 255 ); break;
			case 2: return Renderer::UIColorT( 255, 250, 97, 255 ); break;
			case 3: return Renderer::UIColorT( 149, 255, 79, 255 ); break;
			case 4: return Renderer::UIColorT( 8, 199, 252, 255 ); break;
			case 5: return Renderer::UIColorT( 8, 154, 252, 255 ); break;
			case 6: return Renderer::UIColorT( 158, 62, 247, 255 ); break;
			case 7: return Renderer::UIColorT( 255, 255, 255, 255 ); break;
			case 8: return Renderer::UIColorT( 0, 0, 0, 255 ); break;
			case 9: return Renderer::UIColorT( 227, 59, 121 ); break;
			default: return Renderer::UIColorT( 0, 0, 0, 255 ); break;
		}

		// Failed.
		return Renderer::UIColorT( 0, 0, 0, 255 );
	}

	inline void AddRect( UIColorT color, float x, float y, float w, float h )
	{
		Color_t rendererColor = color.ToRendererColor();

		g_globals->renderer->Rect( rendererColor, x, y, x + w, y + h );
	}

	inline void AddFilledRect( UIColorT color, float x, float y, float w, float h )
	{
		Color_t rendererColor = color.ToRendererColor();

		g_globals->renderer->FilledRect( rendererColor, x, y, w, h );
	}

	inline void AddRectGradient( UIColorT top, UIColorT bottom, float x, float y, float w, float h )
	{
		Color_t rendererTop = top.ToRendererColor();
		Color_t rendererBottom = bottom.ToRendererColor();

		g_globals->renderer->RectGradient( GradientT::VERTICAL, rendererTop, rendererBottom, x, y, w, h );
	}

	inline void AddLine( UIColorT color, float x, float y, float x1, float y1 )
	{
		Color_t rendererColor = color.ToRendererColor();

		g_globals->renderer->Line( rendererColor, x, y, x1, y1 );
	}

	static void AddString( ID3DXFont* font, UIColorT color, float x, float y, bool center, const char* text, bool outline )
	{
		char buf[ 256 ];
		va_list args;
		va_start( args, text );
		vsprintf( buf, text, args );
		va_end( args );

		Color_t renderer_color = color.ToRendererColor();

		if ( outline )
			g_globals->renderer->String( font, Color_t( 0, 0, 0, color.a ), x + 1, y + 1, center, buf );

		g_globals->renderer->String( font, renderer_color, x, y, center, buf );
	}

	static void AddString( ID3DXFont* font, UIColorT color, float x, float y, bool center, const wchar_t* text, bool outline )
	{
		wchar_t buf[ 256 ];
		va_list args;
		va_start( args, text );
		vswprintf( buf, 256, text, args );
		va_end( args );

		Color_t renderer_color = color.ToRendererColor();

		if ( outline )
			g_globals->renderer->WideString( font, Color_t( 0, 0, 0, color.a ), x + 1, y + 1, center, buf );

		g_globals->renderer->WideString( font, renderer_color, x, y, center, buf );
	}

	static float GetTextWidth( ID3DXFont* font, const char* text, ... )
	{
		char buf[ 256 ];
		va_list args;
		va_start( args, text );
		vsprintf( buf, text, args );
		va_end( args );

		return g_globals->renderer->TextWidth( font, buf );
	}
}