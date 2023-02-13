#include "../../Header Files/Renderer.h"

#include <stdio.h>
#include <limits>

CRender::CRender( IDirect3DDevice9* device )
{
	this->device = device;
	Create();
}

#include <stdio.h>
#include <tchar.h>

void CRender::Create()
{
	device->CreateStateBlock( D3DSBT_ALL, &stateBlock );

	D3DXCreateSprite( device, &sprite );

	D3DXCreateFontA( device, 13, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &tahoma );
	D3DXCreateFontA( device, 11, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Small Fonts", &testFont );
	D3DXCreateFontA( device, 8, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Small Fonts", &smallFonts );
	D3DXCreateFontA( device, 11, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &sliderSmallFont );
}

void CRender::Release()
{
	if ( stateBlock )
		stateBlock->Release();

	if ( sprite )
		sprite->Release();

	if ( tahoma )
		tahoma->Release();

	if ( testFont )
		testFont->Release();

	if ( smallFonts )
		smallFonts->Release();

	if ( sliderSmallFont )
		sliderSmallFont->Release();
}

void CRender::Start()
{
	if ( !stateBlock || !device || !sprite )
		return;

	m_verts.clear();
	m_types.clear();

	stateBlock->Capture();

	sprite->Begin( D3DXSPRITE_ALPHABLEND );

	device->GetFVF( &oldFvf );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	device->SetPixelShader( nullptr );
	device->SetTexture( 0, nullptr );

	device->SetRenderState( D3DRS_ZENABLE, false );
	device->SetRenderState( D3DRS_COLORWRITEENABLE, 0xFFFFFFFF );
	device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, false );
}

void CRender::Finish()
{
	if ( !stateBlock || !device || !sprite )
		return;

	device->SetFVF( oldFvf );
	stateBlock->Apply();
	sprite->End();
	device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, true );
}

void CRender::Draw()
{
	device->CreateVertexBuffer( sizeof( VertexT ) * m_verts.size(), 0, oldFvf, D3DPOOL_MANAGED, &buffer, 0 );
	device->CreateIndexBuffer( sizeof( VertexT ) * m_verts.size(), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexedBuffer, 0 );

	device->SetStreamSource( 0, buffer, 0, sizeof( VertexT ) );
	device->SetIndices( indexedBuffer );

	device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 5, 0, 6 );

	for ( size_t i = 0; i < m_verts.size(); i++ ) {}
}

void CRender::Line( Color_t color, float x1, float y1, float x2, float y2 )
{
	VertexT vertices[ 2 ] =
	{
		VertexT( x1, y1, 1.0f, color ),
		VertexT( x2, y2, 1.0f, color )
	};

	device->DrawPrimitiveUP( D3DPT_LINELIST, 1, vertices, sizeof( VertexT ) );
}

void CRender::Rect( Color_t color, float x, float y, float x1, float y1 )
{
	VertexT vertices[ 5 ] =
	{
		VertexT( x, y, 1.0f, color ),
		VertexT( x1, y, 1.0f, color ),
		VertexT( x1, y1, 1.0f, color ),
		VertexT( x, y1, 1.0f, color ),
		VertexT( x, y, 1.0f, color )
	};

	device->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, vertices, sizeof( VertexT ) );
}

void CRender::FilledRect( Color_t color, float x, float y, float w, float h )
{
	VertexT verts[ 4 ] =
	{
		VertexT( x, y, 1.0f, color ),
		VertexT( x + w, y, 1.0f, color ),
		VertexT( x, y + h, 1.0f, color ),
		VertexT( x + w, y + h, 1.0f, color ),
	};

	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, verts, sizeof( VertexT ) );
}

void CRender::RectGradient( GradientT type, Color_t start, Color_t end, float x, float y, float w, float h )
{
	VertexT vertice[ 4 ] =
	{
		VertexT( x, y, 1.0f, start ),
		VertexT( x + w, y, 1.0f, type == GradientT::VERTICAL ? start : end ),
		VertexT( x, y + h, 1.0f, type == GradientT::VERTICAL ? end : start ),
		VertexT( x + w, y + h, 1.0f, end ),
	};

	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertice, sizeof( VertexT ) );
}

float CRender::TextWidth( ID3DXFont* selected_font, const char* fmt, ... )
{
	char buffer[ 256 ];
	va_list args;

	va_start( args, fmt );
	vsprintf( buffer, fmt, args );
	va_end( args );

	ID3DXFont* font = selected_font;

	if ( !font )
		return 0.f;

	RECT textSize{ 0, 0, 0, 0 };
	font->DrawTextA( 0, buffer, -1, &textSize, DT_CALCRECT | DT_NOCLIP, D3DCOLOR_XRGB( 0, 0, 0 ) );

	return ( float )( textSize.right - textSize.left );
}

void CRender::String( ID3DXFont* selected_font, Color_t color, float x, float y, bool centered, const char* fmt, ... )
{
	char buffer[ 256 ];
	va_list args;

	va_start( args, fmt );
	vsprintf( buffer, fmt, args );
	va_end( args );

	ID3DXFont* font = selected_font;

	if ( !font )
		return;

	if ( centered )
	{
		RECT rec = { 0, 0, 0, 0 };

		font->DrawTextA( 0, buffer, -1, &rec, DT_CALCRECT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );

		rec = { static_cast< int >( x ) - rec.right / 2, static_cast< int >( y ), 0, 0 };

		font->DrawTextA( 0, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );
	}
	else
	{
		RECT rec = { static_cast< int >( x ), static_cast< int >( y ), 1000, 100 };

		font->DrawTextA( NULL, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );
	}
}

void CRender::Circle( Vector2 Position, float Points, float Radius, Color_t Color )
{
	float Step = ( float )M_PI * 2.f / Points;

	for ( float a = 0; a < ( M_PI * 2.f ); a += Step )
	{
		Vector2 Start( Radius * cosf( a ) + Position.x, Radius * sinf( a ) + Position.y );
		Vector2 End( Radius * cosf( a + Step ) + Position.x, Radius * sinf( a + Step ) + Position.y );

		Line( Color, Start.x, Start.y, End.x, End.y );
	}
}

void CRender::WideString( ID3DXFont* selected_font, Color_t color, float x, float y, bool centered, const wchar_t* fmt, ... )
{
	wchar_t buffer[ 256 ];
	va_list args;

	va_start( args, fmt );
	vswprintf( buffer, 256, fmt, args );
	va_end( args );

	ID3DXFont* font = selected_font;

	if ( !font )
		return;

	if ( centered )
	{
		RECT rec = { 0, 0, 0, 0 };

		font->DrawTextW( 0, buffer, -1, &rec, DT_CALCRECT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );

		rec = { static_cast< int >( x ) - rec.right / 2, static_cast< int >( y ), 0, 0 };

		font->DrawTextW( 0, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );
	}
	else
	{
		RECT rec = { static_cast< int >( x ), static_cast< int >( y ), 1000, 100 };

		font->DrawTextW( NULL, buffer, -1, &rec, DT_TOP | DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA( color.r(), color.g(), color.b(), color.a() ) );
	}
}

void CRender::Image( uint32_t x, uint32_t y, uint32_t w, uint32_t h, LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE sprite, uint8_t* image, const uint32_t size, bool setup )
{
	if ( setup )
	{
		D3DXCreateTextureFromFileInMemoryEx( device, image, size, w, h, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texture );
		D3DXCreateSprite( device, &sprite );
	}

	sprite->Begin( D3DXSPRITE_ALPHABLEND );
	sprite->Draw( texture, 0, 0, 0, 0xFFFFFFFF );
	sprite->End();
}