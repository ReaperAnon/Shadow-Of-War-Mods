#include "mod.h"
#include "settings.h"
#include "menu.h"

const SHORT bytePattern[] = { 0x0F, 0x28, 0xC8, 0x48, 0x8B, 0xCB, 0x48, 0x83, 0xC4, 0x20, 0x5B, 0xE9, 0x77 };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* mountedMightAddress = nullptr;
    BYTE* mountedMightJmpAddress = 0;

    void MountedMightCode();
}

void Mod::InitalizeMod()
{
    ModLoader::LogAPI::GetSingleton()->Log("Initializing MinHook: %s", MH_StatusToString(
        MH_Initialize()
    ));

    while (!FindAddresses())
        Sleep(500);

    ModLoader::LogAPI::GetSingleton()->Log("Addresses found.");
    Settings::ReadSettings();
    ModLoader::LogAPI::GetSingleton()->Log("Registering menu.");
    ModLoader::MenuAPI::GetSingleton()->RegisterMenuEntry(Menu::ShowSettings, Settings::SetDefaultSettings, Settings::SaveSettings);
    CreateHooks();
    ModLoader::LogAPI::GetSingleton()->Log("Finished loading.");
}

void Mod::DisableMod()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

bool Mod::FindAddresses()
{
    mountedMightAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    mountedMightJmpAddress = mountedMightAddress + 0x6;
    return mountedMightAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(mountedMightAddress, reinterpret_cast<void*>(MountedMightCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}