#pragma once

#include <d3dx9.h>
#include <stdint.h>
#include <memory>

#include "../Header Files/SDK/ValveSDK.h"

enum GradientT
{
	HORIZONTAL,
	VERTICAL,
};

class CRender
{
protected:
	struct VertexT
	{
		VertexT(float x, float y, float z, Color_t color) : x(x), y(y), z(z), color(D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()))
		{

		}

		float x;
		float y;
		float z;
		float w = 0;
		D3DCOLOR color;
	};

public:
	CRender(IDirect3DDevice9*);

	void Create();
	void Release();

	void Start();
	void Finish();
	void Draw();

	void Rect(Color_t color, float x, float y, float w, float h);
	void FilledRect(Color_t color, float x, float y, float w, float h);
	void RectGradient(GradientT, Color_t start, Color_t end, float x, float y, float w, float h);
	void Circle(Vector2 Position, float Points, float Radius, Color_t Color);
	void Line(Color_t color, float x1, float y1, float x2, float y2);
	float TextWidth(ID3DXFont*, const char* fmt, ...);
	void String(ID3DXFont* selectedFont, Color_t color, float x, float y, bool centered, const char* fmt, ...);
	void WideString(ID3DXFont* selectedFont, Color_t color, float x, float y, bool centered, const wchar_t* fmt, ...);
	void Image(uint32_t x, uint32_t y, uint32_t w, uint32_t h, LPDIRECT3DTEXTURE9 texture, LPD3DXSPRITE sprite, uint8_t* image, const uint32_t size, bool setup);

	inline void DrawPrimitive(VertexT* vert, const D3DPRIMITIVETYPE& type)
	{
		m_verts.push_back(vert);
		m_types.push_back(type);
	}

	ID3DXFont* tahoma;
	ID3DXFont* testFont;
	ID3DXFont* smallFonts;
	ID3DXFont* sliderSmallFont;

	IDirect3DDevice9* device;
	IDirect3DStateBlock9* stateBlock;
	ID3DXSprite* sprite;
	IDirect3DVertexBuffer9* buffer;
	IDirect3DIndexBuffer9* indexedBuffer;
	DWORD oldFvf;
	std::vector<VertexT*> m_verts;
	std::vector<D3DPRIMITIVETYPE>m_types;
};

class RenderList : protected CRender
{
public:
	RenderList(size_t maxVerts);

	void empty();
	void batch();

	std::vector<VertexT>m_verts;
};
