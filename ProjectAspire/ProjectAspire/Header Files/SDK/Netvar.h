#pragma once

#include "ValveSDK.h"
#include "../Utility/Hash.h"

#include <vector>

#define NETVAR(funcname, type, table, name)											  \
inline auto& funcname()																  \
{																					  \
	static std::ptrdiff_t offset = g_netvars.GetNetvar(FNV(table), FNV(name));		  \
    if (!offset)																	  \
		offset = g_netvars.GetNetvar(FNV(table), FNV(name));						  \
																					  \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset);						  \
}

#define NETVAR_OFFSET(funcname, type, table, name, extra)							  \
inline auto& funcname()																  \
{																					  \
	static ptrdiff_t offset = g_netvars.GetNetvar(FNV(table), FNV(name));			  \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset + extra);				  \
}

#define OFFSET(type, var, offset) type& var() return *(type*)(uintptr_t(this) + offset);

class NetvarManager
{
public:
	void Init();
	std::ptrdiff_t GetNetvar( HashT table, HashT hash ) const;
	RecvProp* GetNetvarProp( HashT table, HashT name ) const;

public:
	std::ptrdiff_t GetEntry( HashT hash, RecvTable* table ) const;
	RecvTable* GetTable( HashT hash ) const;

private:
	std::vector<RecvTable*>m_tables;
};

extern NetvarManager g_netvars;