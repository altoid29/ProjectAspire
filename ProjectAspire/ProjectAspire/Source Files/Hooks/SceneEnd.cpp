#include <algorithm>

#include "../../Header Files/Interface.h"
#include "../../Header Files/Hooks.h"

void __fastcall Hooks::SceneEnd( void* ecx, void* edx )
{
	return Hooks::oSceneEnd( ecx, edx );
}