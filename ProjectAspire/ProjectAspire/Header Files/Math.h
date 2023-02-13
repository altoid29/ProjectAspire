#pragma once

#include <xmmintrin.h>
#include <cmath>

#include "Utility/Hash.h"
#include "Utility/SafeCall.h"

#define PI 3.14159265358979323846f
#define RADPI 57.295779513082f
#define PIRAD 0.01745329251f

namespace Math
{
	static constexpr float Deg2Rad( const float& x )
	{
		return x * PIRAD;
	}

	static constexpr float Rad2Deg( const float& x )
	{
		return x * RADPI;
	}

	// Vector2 GetDistance.
	inline float GetDistance( float x1, float y1, float x2, float y2 )
	{
		// D = sqrt( ( x2 - x1)^2 + ( y2 - y1)^2 )

		return sqrt( pow( ( x2 - x1 ), 2 ) + pow( ( y2 - y1 ), 2 ) );
	}

	inline bool IsInFOV( Vector2 screenSize, Vector2 targetPos, Vector2 radius )
	{
		// Get crosshair position.
		const float crosshairX = screenSize.x / 2.f;
		const float crosshairY = screenSize.y / 2.f;

		const bool inFov = ( targetPos.x >= crosshairX - radius.x ) && ( targetPos.x <= crosshairX + radius.x ) && ( targetPos.y >= crosshairY - radius.y ) && ( targetPos.y <= crosshairY + radius.y );
		return inFov;
	}

	inline void VectorTransform( Vector3& in1, const matrix3x4_t& in2, Vector3& out )
	{
		out.x = in1.dot( in2.m_flMatVal[ 0 ] ) + in2.m_flMatVal[ 0 ][ 3 ];
		out.y = in1.dot( in2.m_flMatVal[ 1 ] ) + in2.m_flMatVal[ 1 ][ 3 ];
		out.z = in1.dot( in2.m_flMatVal[ 2 ] ) + in2.m_flMatVal[ 2 ][ 3 ];
	}

	inline void VectorAngles( const Vector3& forward, Vector3& angles )
	{
		angles = Vector3( Rad2Deg( atan2( -forward.z, std::sqrt( forward.x * forward.x + forward.y * forward.y ) ) ),
						  Rad2Deg( atan2( forward.y, forward.x ) ),
						  0.0f );
	}

	inline void SinCos( float radians, float* sine, float* cosine )
	{
		*sine = sin( radians );
		*cosine = cos( radians );
	}

	inline void AngleVectors( const Vector3& angles, Vector3* forward = nullptr, Vector3* right = nullptr, Vector3* up = nullptr )
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos( Deg2Rad( angles.y ), &sy, &cy );
		SinCos( Deg2Rad( angles.x ), &sp, &cp );
		SinCos( Deg2Rad( angles.z ), &sr, &cr );

		if ( forward )
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if ( right )
		{
			right->x = ( -1 * sr * sp * cy + -1 * cr * -sy );
			right->y = ( -1 * sr * sp * sy + -1 * cr * cy );
			right->z = -1 * sr * cp;
		}

		if ( up )
		{
			up->x = ( cr * sp * cy + -sr * -sy );
			up->y = ( cr * sp * sy + -sr * cy );
			up->z = cr * cp;
		}
	}
}