#pragma once

#include <memory>
#include <Windows.h>
#include <winternl.h>
#include <Vector>
#include <string>

#include "../Header Files/SDK/ValveSDK.h"
#include "../Header Files/Utility/Hash.h"
#include "../Header Files/Utility/TinyFormat.h"
#include "../Header Files/Utility/SafeCall.h"

#pragma warning(disable : 6387)

namespace Hack
{
	template <typename t>
	inline t* GetInterface( std::string moduleName, std::string interfaceName )
	{
		using CreateInterfaceT = void* ( * )( const char*, int* );

		// Get address of CreateInterface dllexport.
		const CreateInterfaceT createInterface = reinterpret_cast< CreateInterfaceT >( SafeCall::Address::GetExport( moduleName, "CreateInterface" ) );
		if ( createInterface )
		{
#if _DEBUG
			// Get the address of the interface name from the CreateInterface export.
			const void* interfaceAddress = createInterface( interfaceName.c_str(), nullptr );
#else
			const uintptr_t currentModuleGadget = SafeCall::Address::GetGadget( moduleName );
			const void* interfaceAddress = SafeCall::Type::Stdcall<CreateInterfaceT>( ( uintptr_t )createInterface, currentModuleGadget, interfaceName.c_str(), nullptr );
#endif
			if ( !interfaceAddress )
			{
				throw std::runtime_error( tfm::format( "interfaceAddress (0x%p) is invalid.", interfaceAddress ) );
				exit( EXIT_FAILURE );
			}

			// Succeeded, let's return the address.
			return ( t* )interfaceAddress;
		}
		else
		{
			// Invalid export.
			throw std::runtime_error( tfm::format( "createInterface (0x%p) Is invalid.", createInterface ) );
			exit( EXIT_FAILURE );
		}
	}

	bool Init();
}

class Interfaces
{
public:
	CBaseClient* Client;
	IClientMode* ClientMode;
	EntityList* EntList;
	CVar* CVars;
	CEngineClient* Engine;
	CEngineTrace* EngineTrace;
	CGlobals* Globals;
	CDebugOverlay* DebugOverlay;
	IVModelInfoClient* ModelInfo;
	ISurface* Surface;
	VPanel* Panel;
	CDirectDeviceVTable* Device;
	CInput* Input;
	IGameMovement* Movement;
	IPrediction* Prediction;
	IMaterialSystem* MaterialSystem;
	IVRenderView* RenderView;
	IVModelRender* ModelRender;
	CClientState* ClientState;
	CLocalize* Localize;
	IGameEventManager2* EventManager;
	CHudChat* HudChat;
	HWND Window;
	PlayerMovementHelper* MoveHelper;
	void* SoundSystem;
};

inline Interfaces* g_interfaces = new Interfaces();