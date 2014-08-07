#include "StdInc.h"
#include "ResourceManager.h"
#include "ResourceScripting.h"
#include "RuntimeHooks.h"

bool SetStreamingWbnMode(bool fs);

static std::string currentWorldAsset;

LUA_FUNCTION(EnableWorldAssetConfig)
{
	std::string worldAssetName = luaL_checkstring(L, 1);

	if (!currentWorldAsset.empty() && worldAssetName != currentWorldAsset)
	{
		GlobalError("World asset %s does not match %s.", worldAssetName.c_str(), currentWorldAsset.c_str());
	}

	return 0;
}

LUA_FUNCTION(SetWorldAssetConfig)
{
	DWORD oldProtect;
	VirtualProtect((void*)0x401000, 0x94C000, PAGE_EXECUTE_READWRITE, &oldProtect); // .text
	VirtualProtect((void*)0xD4D000, 0x1BF000, PAGE_READWRITE, &oldProtect); // .idata/.rdata

	std::string key = luaL_checkstring(L, 1);

	if (key == "ignore_lod_modelinfos" || key == "modelinfo_deadlock_hack" || key == "bounds_arent_cdimage" || key == "entity_sanity" || key == "static_bound_sanity" || key == "odd_wait_deadlock")
	{
		lua_toboolean(L, 2) && RuntimeHooks::InstallRuntimeHook(key.c_str());
	}
	else if (key == "world_definition")
	{
		RuntimeHooks::SetWorldDefinition(va("resources:/%s/%s", g_currentEnvironment->GetResource()->GetName().c_str(), luaL_checkstring(L, 2)));
	}
	else if (key.find("limit_") == 0)
	{
		RuntimeHooks::SetLimit(key.substr(6).c_str(), luaL_checkinteger(L, 2));
	}

	if (key == "bounds_arent_cdimage")
	{
		lua_toboolean(L, 2) && SetStreamingWbnMode(true);
	}

	VirtualProtect((void*)0x401000, 0x94C000, PAGE_EXECUTE_READ, &oldProtect); // .text
	VirtualProtect((void*)0xD4D000, 0x1BF000, PAGE_READONLY, &oldProtect); // .idata/.rdata

	return 0;
}