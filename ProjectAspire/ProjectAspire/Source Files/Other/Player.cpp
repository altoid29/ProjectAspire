#include "../../Header Files/include.h"
#include "../../Header Files/Math.h"
#include "../../Header Files/interface.h"

mstudiobbox_t* Player::GetHitbox( int Hitbox )
{
	if ( !this )
		return nullptr;

	if ( !Model() )
		return nullptr;

	studiohdr_t* hdr = g_interfaces->ModelInfo->GetStudioModel( Model() );
	if ( !hdr )
		return nullptr;

	mstudiohitboxset_t* set = hdr->pHitboxSet( HitboxSet() );
	if ( !set )
		return nullptr;

	return set->pHitbox( Hitbox );
}

bool Player::IsFlashed()
{
	if ( !this )
		return false;

	const CAnimationLayer* layer = &g_globals->localPlayer->AnimOverlay()[ 9 ];
	if ( !layer )
		return false;

	return layer->m_flWeight > 0.2f;
}

bool Player::IsReloading()
{
	const auto& layer = g_globals->localPlayer->AnimOverlay()[ 1 ];
	int Sequence = g_globals->localPlayer->GetSequenceActivity( layer.m_nSequence );

	const bool reloading = Sequence == ACT_CSGO_RELOAD && layer.m_flWeight != 0.f;
	return reloading;
}

CBaseWeapon* Player::Weapon()
{
	if ( !this )
		return nullptr;

	return reinterpret_cast< CBaseWeapon* >( g_interfaces->EntList->GetEntityFromHandle( this->ActiveWeaponHandle() ) );
}

bool Player::IsVisible( Player* target, Vector3 FromEyePosition )
{
	if ( !this )
		return false;

	GameTrace tr;
	ray_t ray;
	TraceFilter filter;
	filter.m_filter = this; // ?

	auto start = GetEyeOrigin();
	auto dir = ( FromEyePosition - start ).normalized();

	ray.Init( start, FromEyePosition );
	g_interfaces->EngineTrace->TraceRay( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr );

	return tr.Entity == g_globals->localPlayer || tr.m_fraction > 0.97f;
}