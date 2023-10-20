#include "framework.h"
#include "mod.h"

MODLOADERAPI OnRegisterLogAPI(ModLoader::LogAPI* api)
{
	ModLoader::LogAPI::Init(api);
}

MODLOADERAPI OnRegisterMenuAPI(ModLoader::MenuAPI* api)
{
	ModLoader::MenuAPI::Init(api);
}

MODLOADERAPI OnPluginLoad(ModLoader::PluginAPI* api)
{
	api->RegisterPlugin("Improved Ice Storm", "IceStorm", { 1, 0, 0 });

	std::thread(Mod::InitalizeMod).detach();
}

MODLOADERAPI OnPluginUnload()
{
	Mod::DisableMod();
}