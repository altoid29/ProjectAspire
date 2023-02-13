#pragma once

#include "Include.h"

namespace World
{
	template<class t = Vector3>
	inline bool WorldToScreen( const Vector3& world, t& screen )
	{
		screen.x = g_globals->viewMatrix[ 0 ][ 0 ] * world[ 0 ] + g_globals->viewMatrix[ 0 ][ 1 ] * world[ 1 ] + g_globals->viewMatrix[ 0 ][ 2 ] * world[ 2 ] + g_globals->viewMatrix[ 0 ][ 3 ];
		screen.y = g_globals->viewMatrix[ 1 ][ 0 ] * world[ 0 ] + g_globals->viewMatrix[ 1 ][ 1 ] * world[ 1 ] + g_globals->viewMatrix[ 1 ][ 2 ] * world[ 2 ] + g_globals->viewMatrix[ 1 ][ 3 ];

		float w = g_globals->viewMatrix[ 3 ][ 0 ] * world[ 0 ] + g_globals->viewMatrix[ 3 ][ 1 ] * world[ 1 ] + g_globals->viewMatrix[ 3 ][ 2 ] * world[ 2 ] + g_globals->viewMatrix[ 3 ][ 3 ];

		bool behind = false;

		if ( w < 0.001f )
		{
			behind = true;

			screen.x *= 100000;
			screen.y *= 100000;
		}
		else
		{
			behind = false;

			float invw = 1.0f / w;

			screen.x *= invw;
			screen.y *= invw;
		}

		float x = float( g_globals->screenW ) / 2.0f;
		float y = float( g_globals->screenH ) / 2.0f;

		x += 0.5f * screen.x * g_globals->screenW + 0.5f;
		y -= 0.5f * screen.y * g_globals->screenH + 0.5f;

		screen.x = x;
		screen.y = y;

		return true;
	}

	struct BoxT
	{
		int x, y, w, h;
		BoxT() = default;
		BoxT( const int x, const int y, const int w, const int h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	inline bool GetPlayerBox( Player* ent, BoxT& in )
	{
		Vector3 flb, brt, blb, frt, frb, brb, blt, flt;

		const auto origin = ent->GetOrigin();
		const auto min = ent->Collideable()->mins() + origin;
		const auto max = ent->Collideable()->maxs() + origin;

		Vector3 points[] =
		{
			Vector3( min.x, min.y, min.z ),
			Vector3( min.x, max.y, min.z ),
			Vector3( max.x, max.y, min.z ),
			Vector3( max.x, min.y, min.z ),
			Vector3( max.x, max.y, max.z ),
			Vector3( min.x, max.y, max.z ),
			Vector3( min.x, min.y, max.z ),
			Vector3( max.x, min.y, max.z )
		};

		if ( !WorldToScreen( points[ 3 ], flb ) || !WorldToScreen( points[ 5 ], brt ) || !WorldToScreen( points[ 0 ], blb ) || !WorldToScreen( points[ 4 ], frt ) ||
			 !WorldToScreen( points[ 2 ], frb ) || !WorldToScreen( points[ 1 ], brb ) || !WorldToScreen( points[ 6 ], blt ) || !WorldToScreen( points[ 7 ], flt ) )
			return false;

		Vector3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float right = flb.x;
		float bottom = flb.y;

		for ( int i = 1; i < 8; ++i )
		{
			if ( left > arr[ i ].x )
				left = arr[ i ].x;

			if ( bottom < arr[ i ].y )
				bottom = arr[ i ].y;

			if ( right < arr[ i ].x )
				right = arr[ i ].x;

			if ( top > arr[ i ].y )
				top = arr[ i ].y;
		}

		in.x = static_cast< int >( left );
		in.y = static_cast< int >( top );
		in.w = static_cast< int >( right - left );
		in.h = static_cast< int >( bottom - top );

		return true;
	}
}