#include "../../Header Files/SDK/Netvar.h"
#include "../../Header Files/Include.h"
#include "../../Header Files/Interface.h"

NetvarManager g_netvars;

void NetvarManager::Init()
{
	for ( auto clientClass = g_globals->spoofedFunctions->GetAllClasses(); clientClass != nullptr; clientClass = clientClass->Next )
	{
		auto Table = clientClass->Table;
		m_tables.push_back( Table );
	}
}

RecvTable* NetvarManager::GetTable( HashT hash ) const
{
	if ( m_tables.empty() )
		return nullptr;

	for ( auto& table : m_tables )
	{
		if ( !table )
			continue;

		if ( hash == Hash::Fnv1a( table->m_pNetTableName ) )
			return table;
	}

	return nullptr;
}

RecvProp* NetvarManager::GetNetvarProp( HashT data, HashT name ) const
{
	RecvProp* prop{};
	RecvTable* child{};

	auto table = GetTable( data );

	if ( !table )
		return nullptr;

	for ( int i{}; i < table->m_nProps; i++ )
	{
		prop = &table->m_pProps[ i ];
		child = prop->m_pDataTable;

		if ( child && child->m_nProps )
		{
			auto tmp = GetNetvarProp( Hash::Fnv1a( child->m_pNetTableName ), name );

			if ( tmp )
				return tmp;
		}

		if ( name != Hash::Fnv1a( prop->m_pVarName ) )
			continue;

		return prop;
	}

	return nullptr;
}

std::ptrdiff_t NetvarManager::GetEntry( HashT name, RecvTable* table ) const
{
	std::ptrdiff_t ret{};
	RecvProp* prop;
	RecvTable* child;

	for ( int i{}; i < table->m_nProps; i++ )
	{
		prop = &table->m_pProps[ i ];
		child = prop->m_pDataTable;

		if ( child && child->m_nProps )
		{
			auto tmp = GetEntry( name, child );

			if ( tmp )
				ret += prop->m_Offset + tmp;
		}

		if ( name != Hash::Fnv1a( prop->m_pVarName ) )
			continue;

		return prop->m_Offset + ret;
	}

	return ret;
}

std::ptrdiff_t NetvarManager::GetNetvar( HashT data, HashT name ) const
{
	std::ptrdiff_t ret{};

	auto table = GetTable( data );
	if ( !table )
		return 0;

	ret = GetEntry( name, table );

	return ret;
}
