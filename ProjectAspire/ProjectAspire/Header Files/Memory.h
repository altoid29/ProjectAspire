#pragma once

#pragma warning(disable : 4996)
#pragma warning(disable : 4018)

#include <Windows.h>
#include <new>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <intrin.h>

#include "Utility/Hash.h"
#include "Utility/TinyFormat.h"
#include "Utility/SafeCall.h"

namespace Memory
{
	template <typename t>
	inline t GetVirtual( void* base, uint16_t index )
	{
		if ( !base || index < 0 )
			return nullptr;

		return ( t )( *( uintptr_t** )base )[ index ];
	}

	inline uintptr_t GetVirtual( void* base, size_t index )
	{
		return static_cast< uintptr_t >( ( *static_cast< int** >( base ) )[ index ] );
	}

	inline uint8_t* FindSignature( std::string moduleName, const char* signature )
	{
		const auto moduleAddress = SafeCall::Address::GetModule( moduleName );

		// Failed to acquire the module base address.
		if ( !moduleAddress )
			return nullptr;

		static auto PatternToByte = []( const char* Pattern )
		{
			auto bytes = std::vector<int>{};
			auto start = const_cast< char* >( Pattern );
			auto end = const_cast< char* >( Pattern ) + std::strlen( Pattern );

			for ( auto current = start; current < end; current++ )
			{
				if ( *current == '?' )
				{
					current++;

					if ( *current == '?' )
						current++;

					bytes.push_back( -1 );
				}
				else
				{
					bytes.push_back( std::strtoul( current, &current, 16 ) );
				}
			}

			return bytes;
		};

		auto nt = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< uint8_t* >( moduleAddress ) + reinterpret_cast< PIMAGE_DOS_HEADER >( moduleAddress )->e_lfanew );
		auto imageSize = nt->OptionalHeader.SizeOfImage;
		auto patternBytes = PatternToByte( signature );
		auto scannedBytes = reinterpret_cast< uint8_t* >( moduleAddress );

		auto size = patternBytes.size();
		auto data = patternBytes.data();

		for ( auto i = 0ul; i < imageSize - size; i++ )
		{
			bool found = true;

			for ( auto j = 0ul; j < size; j++ )
			{
				if ( scannedBytes[ i + j ] != data[ j ] && data[ j ] != -1 )
				{
					found = false;
					break;
				}
			}

			if ( found )
				return &scannedBytes[ i ];
		}

		// We failed to find the signature.
		throw std::runtime_error( tfm::format( "Invalid signature (%s)", signature ) );
		return nullptr;
	}
}