#pragma once

#include "Netvar.h"
#include "ValveSDK.h"
#include "../Interface.h"
#include "../Signatures.h"
#include "Math.h"

#include <codecvt>

enum Hitboxes_t
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
};

#define _(Str) (Str)

class CBaseWeapon;
class Player
{
	template <typename t>
	inline t& Get( ptrdiff_t Offset )
	{
		return *reinterpret_cast< t* >( uintptr_t( this ) + Offset );
	}

public:
	// Manual netvars.
	NETVAR_OFFSET( OldSimulationTime, float, _( "DT_BaseEntity" ), _( "m_flSimulationTime" ), sizeof( float ) );
	NETVAR_OFFSET( GetMoveType, uint8_t, _( "DT_BaseEntity" ), _( "m_nRenderMode" ), 1 );

	// DT_CSPlayer Netvars.
	NETVAR( IsWalking, bool, _( "DT_CSPlayer" ), _( "m_bIsWalking" ) );
	NETVAR( GetArmorValue, int, _( "DT_CSPlayer" ), _( "m_ArmorValue" ) );
	NETVAR( HasDefuser, bool, _( "DT_CSPlayer" ), _( "m_bHasDefuser" ) );
	NETVAR( IsDefusing, bool, _( "DT_CSPlayer" ), _( "m_bIsDefusing" ) );
	NETVAR( HasHelmet, bool, _( "DT_CSPlayer" ), _( "m_bHasHelmet" ) );
	NETVAR( HasSpawnProtection, bool, _( "DT_CSPlayer" ), _( "m_bGunGameImmunity" ) );
	NETVAR( GetEyeAngles, Vector3, _( "DT_CSPlayer" ), _( "m_angEyeAngles[0]" ) );
	NETVAR( GetVelocity, Vector3, _( "DT_CSPlayer" ), _( "m_vecVelocity[0]" ) );
	NETVAR( GetLBY, float, _( "DT_CSPlayer" ), _( "m_flLowerBodyYawTarget" ) );
	NETVAR( IsScoped, bool, _( "DT_CSPlayer" ), _( "m_bIsScoped" ) );
	NETVAR( GetMoney, int, _( "DT_CSPlayer" ), _( "m_iAccount" ) );
	NETVAR( GetShotsFired, int, _( "DT_CSPlayer" ), _( "m_iShotsFired" ) );

	// DT_BaseAnimating Netvars.
	NETVAR( HitboxSet, int, _( "DT_BaseAnimating" ), _( "m_nHitboxSet" ) );

	// DT_BaseEntity Netvars.
	NETVAR( GetOrigin, Vector3, _( "DT_BaseEntity" ), _( "m_vecOrigin" ) );
	NETVAR( ModelIndex, int, _( "DT_BaseEntity" ), _( "m_nModelIndex" ) );
	NETVAR( VecMins, Vector3, _( "DT_BaseEntity" ), _( "m_vecMins" ) );
	NETVAR( VecMaxs, Vector3, _( "DT_BaseEntity" ), _( "m_vecMaxs" ) );
	NETVAR( OwnerEntityHandle, ulong, _( "DT_BaseEntity" ), _( "m_hOwnerEntity" ) );
	NETVAR( GetTeam, int, _( "DT_BaseEntity" ), _( "m_iTeamNum" ) );

	// DT_BasePlayer Netvars.
	NETVAR( GetHealth, int, _( "DT_BasePlayer" ), _( "m_iHealth" ) );
	NETVAR( GetFlags, int, _( "DT_BasePlayer" ), _( "m_fFlags" ) );
	NETVAR( GetLifeState, uint8_t, _( "DT_BasePlayer" ), _( "m_lifeState" ) );
	NETVAR( GetOBSMode, int, _( "DT_BasePlayer" ), _( "m_iObserverMode" ) );
	NETVAR( ObserverTargetHandle, uint32_t, _( "DT_BasePlayer" ), _( "m_hObserverTarget" ) );
	NETVAR( AimPunchAngle, Vector3, _( "DT_BasePlayer" ), _( "m_aimPunchAngle" ) );
	NETVAR( PunchVelocity, Vector3, _( "DT_BasePlayer" ), _( "m_aimPunchAngleVel" ) );
	NETVAR( ViewPunchAngle, Vector3, _( "DT_BasePlayer" ), _( "m_viewPunchAngle" ) );
	NETVAR( GetTickBase, int, _( "DT_BasePlayer" ), _( "m_nTickBase" ) );
	NETVAR( GetViewOffset, Vector3, _( "DT_BasePlayer" ), _( "m_vecViewOffset[0]" ) );
	NETVAR( GetDuckAmount, float, _( "DT_BasePlayer" ), _( "m_flDuckAmount" ) );

	// DT_BaseCombatCharacter Netvars.
	NETVAR( MyWeaponsHandle, uint32_t*, _( "DT_BaseCombatCharacter" ), _( "m_hMyWeapons" ) );
	NETVAR( ActiveWeaponHandle, uint32_t, _( "DT_BaseCombatCharacter" ), _( "m_hActiveWeapon" ) );
	NETVAR( NextAttack, float, _( "DT_BaseCombatCharacter" ), _( "m_flNextAttack" ) );

	inline void* Renderable()
	{
		if ( !this )
			return nullptr;

		return reinterpret_cast< void* >( this + 0x4 );
	}

	inline void* Networkable()
	{
		if ( !this )
			return nullptr;

		return reinterpret_cast< void* >( this + 0x8 );
	}

	inline ICollideable* Collideable()
	{
		if ( !this )
			return nullptr;

		using T = ICollideable * ( __thiscall* )( void* );
		return Memory::GetVirtual<T>( this, 3 )( this );
	}

	inline int Index()
	{
		if ( !this )
			return 0;

		using IndexT = int( __thiscall* )( void* );
		return ( *( IndexT** )Networkable() )[ 10 ]( Networkable() );
	}

	inline c_client* Client()
	{
		if ( !this )
			return nullptr;

		return Memory::GetVirtual<c_client* ( __thiscall* )( void* )>( this->Networkable(), 2 )( this->Networkable() );
	}

	inline bool IsWeapon()
	{
		if ( !this )
			return false;

		// XREF; CNewParticleEffect::DrawModel
		// SIG; 8B 80 ? ? ? ? FF D0 84 C0 74 6F 8B 4D A4
		const bool IsBaseCombatWeapon = Memory::GetVirtual<bool( __thiscall* )( void* )>( this, 165 )( this );
		return IsBaseCombatWeapon || Client()->ClassID == ClassID::CC4;
	}

	inline bool IsPlayer()
	{
		if ( !this )
			return false;

		// XREF; "effects/nightvision"
		// SIG; 8B 92 ? ? ? ? FF D2 84 C0 0F 45 F7 85 F6
		return Memory::GetVirtual<bool( __thiscall* )( void* )>( this, 158 )( this );
	}

	inline const char* GetMapAreaName()
	{
		if ( !this )
			return _( "INVALID_PTR" );

		static const size_t offset = g_netvars.GetNetvar( FNV( "DT_BasePlayer" ), FNV( "m_szLastPlaceName" ) );
		return reinterpret_cast< char* >( this + offset );
	}

	inline Vector3 GetEyeOrigin()
	{
		if ( !this )
			return Vector3( 0, 0, 0 );

		return GetOrigin() + GetViewOffset();
	}

	inline Vector3& GetAbsAngles()
	{
		if ( !this )
		{
			static Vector3 invalid{ 0, 0, 0 };
			return invalid;
		}

		return Memory::GetVirtual<Vector3& ( __thiscall* )( void* )>( this, 11 )( this );
	}

	inline Vector3 WorldSpaceCenter()
	{
		if ( !this )
			return Vector3( 0, 0, 0 );

		return Vector3( ( this->VecMins() + this->VecMaxs() ) * 0.5f );
	}

	inline Vector3 GetHitboxPosition( int HitboxID )
	{
		if ( !this )
			return Vector3( 0, 0, 0 );

		matrix3x4_t boneMatrix[ 128 ];
		if ( SetupBones( boneMatrix, 128, BONE_USED_BY_HITBOX, 0.f ) )
		{
			auto studioModel = g_interfaces->ModelInfo->GetStudioModel( this->Model() );
			if ( studioModel )
			{
				auto hitbox = studioModel->pHitboxSet( 0 )->pHitbox( HitboxID );
				if ( hitbox )
				{
					auto min = Vector3{}, max = Vector3{};

					Math::VectorTransform( hitbox->m_Mins, boneMatrix[ hitbox->m_Bone ], min );
					Math::VectorTransform( hitbox->m_Maxs, boneMatrix[ hitbox->m_Bone ], max );

					return Vector3( ( min.x + max.x ) * 0.5f, ( min.y + max.y ) * 0.5f, ( min.z + max.z ) * 0.5f );
				}
			}
		}

		return Vector3( 0, 0, 0 );
	}

	inline Vector3 GetHeadPosition()
	{
		if ( !this )
			return Vector3( 0, 0, 0 );

		return this->GetViewOffset() + this->GetOrigin();
	}

	CBaseWeapon* Weapon();

	inline bool IsAlive()
	{
		if ( !this )
			return false;

		return this->GetHealth() > 0;
	}

	inline bool IsInAir()
	{
		if ( !this )
			return false;

		return !( this->GetFlags() & FL_ONGROUND );
	}

	inline bool IsDormant()
	{
		if ( !this )
			return false;

		// XREF; client.dll, 8A 81 ? ? ? ? C3 32 C0

		using DormantT = bool( __thiscall* )( void* );
		return ( *static_cast< DormantT** >( Networkable() ) )[ 9 ]( Networkable() );
	}

	inline CAnimationLayer* AnimOverlay()
	{
		if ( !this )
			return nullptr;

		// Todo: Test; Can we use this?
		// static const auto Offset = g_netvars.GetNetvar(FNV("DT_OverlayVars"), FNV("m_AnimOverlay"));

		// XREF: m_AnimOverlay
		return *reinterpret_cast< CAnimationLayer** >( ( uintptr_t )this + 0x2990 );
	}

	inline CCSGOPlayerAnimState* GetAnimState()
	{
		if ( !this )
			return nullptr;

		// XREF: hand_L
		return *reinterpret_cast< CCSGOPlayerAnimState** >( ( uintptr_t )this + 0x9960 );
	}

	inline model_t* Model()
	{
		if ( !this )
			return nullptr;

		return Memory::GetVirtual< model_t* ( __thiscall* )( void* ) >( this->Renderable(), 8 )( this->Renderable() );
	}

	inline int GetSequenceActivity( uint16_t Sequence )
	{
		if ( !this )
			return 0;

		auto Hdr = g_interfaces->ModelInfo->GetStudioModel( this->Model() );

		// Return dumb value to inform us it failed.
		if ( !Hdr )
			return -1337;

		static const auto _GetSequenceActivity = reinterpret_cast< int( __fastcall* )( void*, studiohdr_t*, int ) >( Offsets::getSequenceActivity );

		return _GetSequenceActivity( this, Hdr, Sequence );
	}

	inline int DrawModel( int flags, uint8_t Alpha = 255 )
	{
		if ( !this )
			return 0;

		return Memory::GetVirtual< int( __thiscall* )( void*, int, uint8_t ) >( this->Renderable(), 9 )( this->Renderable(), flags, Alpha );
	}

	inline bool SetupBones( matrix3x4_t* bone_matrix, int max_bones, int bone_mask, float curtime )
	{
		if ( !this )
			return false;

		using original_fn = bool( __thiscall* )( void*, matrix3x4_t*, int, int, float );
		return ( *( original_fn** )Renderable() )[ 13 ]( Renderable(), bone_matrix, max_bones, bone_mask, curtime );
	}

	inline bool HasC4()
	{
		if ( !this )
			return false;

		static const auto PlayerHasBomb = reinterpret_cast< bool( __thiscall* )( void* ) >( Offsets::hasC4 );
		return PlayerHasBomb( this );
	}

	inline void think()
	{
		if ( !this )
			return;

		return Memory::GetVirtual< void( __thiscall* )( void* ) >( this, 137 )( this );
	}

	inline void RunPostThink()
	{
		if ( !this )
			return;

		return Memory::GetVirtual< void( __thiscall* )( void* ) >( this, 308 )( this );
	}

	inline Vector3 GetBonePosition( int bone, matrix3x4_t* matrix )
	{
		if ( !this )
			return Vector3{ 0, 0, 0 };

		return Vector3( matrix[ bone ][ 0 ][ 3 ], matrix[ bone ][ 1 ][ 3 ], matrix[ bone ][ 2 ][ 3 ] );
	}

	mstudiobbox_t* GetHitbox( int Hitbox );

	bool IsVisible( Player* target, Vector3 FromEyePosition );

	bool IsReloading();
	bool IsFlashed();
};

enum Weapon_t
{
	RIFLE,
	PISTOL,
	SNIPER,
	SMG,
	HEAVY,
	KNIFE,
	GRENADE,
};

enum ItemDefinitionIndex_t
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_BAYONET = 500,
	WEAPON_CLASSIC_KNIFE = 503,
	WEAPON_FLIP_KNIFE = 505,
	WEAPON_GUT_KNIFE,
	WEAPON_KARAMBIT,
	WEAPON_M9_BAYONET,
	WEAPON_HUNTSMAN_KNIFE,
	WEAPON_FALCHION_KNIFE = 512,
	WEAPON_BOWIE_KNIFE = 514,
	WEAPON_BUTTERFLY_KNIFE,
	WEAPON_SHADOW_DAGGERS,
	WEAPON_PARACORD_KNIFE,
	WEAPON_SURVIVAL_KNIFE,
	WEAPON_URSUS_KNIFE,
	WEAPON_NAVAJA_KNIFE,
	WEAPON_NOMAD_KNIFE,
	WEAPON_STILETTO_KNIFE,
	WEAPON_TALON_KNIFE,
	WEAPON_SKELETON_KNIFE = 525
};

class CBaseWeapon : public Player
{
	template <typename t>
	inline t& Get( std::ptrdiff_t offset )
	{
		return *reinterpret_cast< t* >( uintptr_t( this ) + offset );
	}

public:
	NETVAR( ItemDefinitionIndex, int, _( "DT_BaseAttributableItem" ), _( "m_iItemDefinitionIndex" ) );
	NETVAR( Clip1AmmoCount, int, _( "DT_BaseCombatWeapon" ), _( "m_iClip1" ) );
	NETVAR( PrimaryReserveAmmoCount, int, _( "DT_BaseCombatWeapon" ), _( "m_iPrimaryReserveAmmoCount" ) );
	NETVAR( GetNextPrimaryAttack, float, _( "DT_BaseCombatWeapon" ), _( "m_flNextPrimaryAttack" ) );
	NETVAR( GetRecoilIndex, float, _( "DT_WeaponCSBase" ), _( "m_flRecoilIndex" ) );
	NETVAR( GetShotTime, float, _( "DT_WeaponCSBase" ), _( "m_fLastShotTime" ) );
	NETVAR( IsPinPulled, bool, _( "DT_BaseCSGrenade" ), _( "m_bPinPulled" ) );
	NETVAR( GetThrowTime, float, _( "DT_BaseCSGrenade" ), _( "m_fThrowTime" ) );

	inline bool IsSniperRifle()
	{
		if ( !this )
			return false;

		const auto itemID = this->ItemDefinitionIndex();
		return itemID == 9 || itemID == 11 || itemID == 38 || itemID == 40;
	}

	inline WeaponInfo* GetWeaponData()
	{
		if ( !this )
			return nullptr;

		return Memory::GetVirtual<WeaponInfo* ( __thiscall* )( void* )>( this, 445 )( this );
	}

	inline const char* GetName()
	{
		if ( !this )
			return _( "INVALID" );

		return Memory::GetVirtual< const char* ( __thiscall* )( void* ) >( this, 376 )( this );
	}

	inline float GetSpread()
	{
		if ( !this )
			return 0.f;

		// XREF: Client | "Inaccuracy =\t%f\tSpread =\t%f\tSpreadDistance =\t%f\tPlayer Velocity =\t%f\n"
		return Memory::GetVirtual< float( __thiscall* )( void* ) >( this, 453 )( this );
	}

	inline void UpdateAccuracyPenalty()
	{
		if ( !this )
			return;

		// XREF: Client | "Inaccuracy =\t%f\tSpread =\t%f\tSpreadDistance =\t%f\tPlayer Velocity =\t%f\n"
		return Memory::GetVirtual< void( __thiscall* )( void* ) >( this, 483 )( this );
	}

	inline float GetInaccuracy()
	{
		if ( !this )
			return 0.f;

		return Memory::GetVirtual< float( __thiscall* )( void* ) >( this, 483 )( this );
	}

	inline Weapon_t GetWeaponType()
	{
		switch ( this->ItemDefinitionIndex() )
		{
			case WEAPON_DEAGLE:
			case WEAPON_ELITE:
			case WEAPON_FIVESEVEN:
			case WEAPON_HKP2000:
			case WEAPON_USP_SILENCER:
			case WEAPON_CZ75A:
			case WEAPON_TEC9:
			case WEAPON_REVOLVER:
			case WEAPON_GLOCK:
			case WEAPON_P250:
				return PISTOL;
				break;

			case WEAPON_AK47:
			case WEAPON_M4A1:
			case WEAPON_M4A1_SILENCER:
			case WEAPON_GALILAR:
			case WEAPON_AUG:
			case WEAPON_FAMAS:
			case WEAPON_SG556:
				return RIFLE;
				break;

			case WEAPON_P90:
			case WEAPON_BIZON:
			case WEAPON_MP7:
			case WEAPON_MP9:
			case WEAPON_MAC10:
			case WEAPON_UMP45:
				return SMG;
				break;

			case WEAPON_AWP:
			case WEAPON_SSG08:
			case WEAPON_G3SG1:
			case WEAPON_SCAR20:
				return SNIPER;
				break;

			case WEAPON_MAG7:
			case WEAPON_SAWEDOFF:
			case WEAPON_NOVA:
			case WEAPON_XM1014:
			case WEAPON_NEGEV:
			case WEAPON_M249:
				return HEAVY;
				break;

			case WEAPON_KNIFE:
			case WEAPON_BAYONET:
			case WEAPON_BUTTERFLY_KNIFE:
			case WEAPON_FALCHION_KNIFE:
			case WEAPON_FLIP_KNIFE:
			case WEAPON_GUT_KNIFE:
			case WEAPON_KARAMBIT:
			case WEAPON_HUNTSMAN_KNIFE:
			case WEAPON_M9_BAYONET:
			case WEAPON_SHADOW_DAGGERS:
			case WEAPON_BOWIE_KNIFE:
			case WEAPON_KNIFE_T:
				return KNIFE;
				break;

			case WEAPON_HEGRENADE:
			case WEAPON_FLASHBANG:
			case WEAPON_SMOKEGRENADE:
			case WEAPON_MOLOTOV:
			case WEAPON_INCGRENADE:
			case WEAPON_DECOY:
				return GRENADE;
				break;

			default:
				return KNIFE;
		}
	}
};
