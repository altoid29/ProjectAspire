#pragma once

#include <cstdint>
#include <winnt.h>

/*
    1. Declare new instance of SafeVMT with the class address as a parameter.
    2. Set the original to the casted type_t then the get_vfunc with the index.
    3. Place the hook with place_hook.
*/

class SafeVMT
{
private:
    uintptr_t* pVmt;
    void* ClassBase = nullptr;

public:
    uintptr_t** VTableAddress = nullptr;
    uintptr_t* OriginalAddress = nullptr;
    size_t FunctionCount = 0;

    // initialize our vmt class.
    inline SafeVMT( void* ClassAddress )
    {
        ClassBase = ClassAddress;
        VTableAddress = reinterpret_cast< uintptr_t** >( ClassAddress );

        // Acquire the amount of functions inside the virtual class.
        while ( reinterpret_cast< uintptr_t* >( *VTableAddress )[ FunctionCount ] )
        {
            FunctionCount++;
        }

        // Set the original.
        OriginalAddress = *VTableAddress;

        pVmt = new uintptr_t[ FunctionCount + 1 ];

        // Make a copy of the entire table.
        memcpy( pVmt, &OriginalAddress[ -1 ], ( sizeof( uintptr_t ) * FunctionCount ) + sizeof( uintptr_t ) );
    }

    // Get the virtual function.
    inline unsigned int GetVFunc( size_t index )
    {
        return static_cast< unsigned int >( ( *static_cast< int** >( ClassBase ) )[ index ] );
    }

    // Apply the hook to the given function.
    inline void PlaceHook( void* replacement, size_t index )
    {
        // A simple sanity check to ensure that are hook is valid and in valid boundaries.
        bool ValidHook = replacement != nullptr && index >= 0 && index <= FunctionCount;

        if ( ValidHook )
        {
            pVmt[ index + 1 ] = reinterpret_cast< uintptr_t >( replacement );
            *VTableAddress = &pVmt[ 1 ];
        }
    }

    // Restores the address change from our replacement back to the original.
    inline void RemoveHook()
    {
        // Let's ensure that we don't remove a hook that doesn't need to be removed.
        if ( *VTableAddress != OriginalAddress )
        {
            *VTableAddress = OriginalAddress;
            delete pVmt;
        }
    }

    // Acquires the original address before the swap.
    inline uintptr_t* GetOriginalAddress()
    {
        if ( OriginalAddress != nullptr )
            return OriginalAddress;

        return nullptr;
    }

    // Aquires the address after the hook has been applied.
    inline uintptr_t* GetHookedAddress()
    {
        // Already equals the original address, must be non-hooked.
        if ( OriginalAddress == *VTableAddress )
            return nullptr;

        return pVmt;
    }

    // Get the method used before the hook was applied.
    template<typename t>
    inline t GetOriginalMethod( size_t method_index )
    {
        return reinterpret_cast< t >( OriginalAddress[ method_index ] );
    }
};