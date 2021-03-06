#include "StdInc.h"
#include "fiDevice.h"
#include "ResourceManager.h"

static InitFunction initFunction([] ()
{
	rage::fiDevice::SetInitialMountHook([] (void*)
	{
		static char citRoot[512];
		std::wstring citPath = MakeRelativeCitPath(L"citizen");

		size_t offset = wcstombs(citRoot, citPath.c_str(), sizeof(citRoot));
		citRoot[offset] = '\\';
		citRoot[offset + 1] = '\0';

		rage::fiDeviceRelative* device = new rage::fiDeviceRelative();
		device->setPath(citRoot, true);
		device->mount("citizen:/");

		/*static char viivRoot[512];
		std::wstring viivPath = MakeRelativeCitPath(L"viiv");

		offset = wcstombs(viivRoot, viivPath.c_str(), sizeof(citRoot));
		viivRoot[offset] = '\\';
		viivRoot[offset + 1] = '\0';

		rage::fiDeviceRelative* device2 = new rage::fiDeviceRelative();
		device2->setPath(viivRoot, true);
		device2->mount("gta5:/");*/

		static char cacheRoot[512];
		std::wstring cachePath = MakeRelativeCitPath(L"cache");

		if (GetFileAttributes(cachePath.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(cachePath.c_str(), nullptr);
		}

		std::wstring unconfPath = MakeRelativeCitPath(L"cache/unconfirmed");

		if (GetFileAttributes(unconfPath.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(unconfPath.c_str(), nullptr);
		}

		offset = wcstombs(cacheRoot, cachePath.c_str(), sizeof(cacheRoot));
		cacheRoot[offset] = '\\';
		cacheRoot[offset + 1] = '\0';

		rage::fiDeviceRelative* cacheDevice = new rage::fiDeviceRelative();
		cacheDevice->setPath(cacheRoot, true);
		cacheDevice->mount("rescache:/");

		TheResources.GetCache()->LoadCache(cacheDevice);
	});
});