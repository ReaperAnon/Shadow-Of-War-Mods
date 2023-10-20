#include "framework.h"
#include "mod.h"

MODLOADERAPI OnRegisterLogAPI(ModLoader::LogAPI* api)
{
	ModLoader::LogAPI::Init(api);
}

MODLOADERAPI OnPluginLoad(ModLoader::PluginAPI* api)
{
	api->RegisterPlugin("No Skill Story Locks", "StorySkills", { 1, 0, 0 });

	std::thread(Mod::InitalizeMod).detach();
}

MODLOADERAPI OnPluginUnload()
{
	Mod::DisableMod();
}