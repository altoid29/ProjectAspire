#pragma once

#pragma warning(disable : 4307) // '*': Integral constant overflow.
#pragma warning(disable : 4244) // Possible loss of data.

#include <cstdint>
#include <string>

using HashT = size_t;

// Used for compile-time FNV-1a 32bit hashes.
#define FNV(str)                                   \
    [&]()										   \
	{											   \
        constexpr HashT out = Hash::Fnv1a(str);    \
        return out;                                \
    }()

// Used for compile-time FNV-1a 32bit hashes when above macro cant be used for constexpr variables.
#define FNV_CONST(str)[]()								\
	{													\
        constexpr HashT out{ Hash::fnv1a_32( str ) };  \
                                                        \
        return out;                                     \
    }()

namespace Hash
{
	enum : HashT
	{
		FNV1A_PRIME = 0x1000193,
		FNV1A_BASIS = 0x811C9DC5
	};

	// Compile-time string length.
	inline constexpr size_t CT_Strlen( const char* Str )
	{
		size_t Out = 1;

		for ( ; Str[ Out ] != '\0'; Out++ );

		return Out;
	}

	// Hash data.
	inline constexpr HashT Fnv1a( const uint8_t* Data, const size_t Length )
	{
		HashT out = FNV1A_BASIS;

		for ( size_t i = 0; i < Length; i++ )
		{
			out = ( out ^ Data[ i ] ) * FNV1A_PRIME;
		}

		return out;
	}

	// Hash c-style string.
	inline constexpr HashT Fnv1a( const char* Str )
	{
		HashT out = FNV1A_BASIS;
		size_t len = CT_Strlen( Str );

		for ( size_t i = 0; i < len; i++ )
		{
			out = ( out ^ Str[ i ] ) * FNV1A_PRIME;
		}

		return out;
	}

	// Hash C++ style string. (runtime only)
	inline HashT Fnv1a( const std::string& str )
	{
		return Fnv1a( ( uint8_t* )str.c_str(), str.size() );
	}
}

// Compile-time hash.
#define HASH(str)[]()									\
	{													\
        constexpr HashT out{Hash::Fnv1a(str)};			\
        return out;                                     \
    }()