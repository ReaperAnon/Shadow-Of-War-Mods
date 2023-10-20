#include "mod.h"
#include "menu.h"
#include "settings.h"

const SHORT bytePattern[] = { 0xB0, 0x01, 0xEB, 0x100, 0x48, 0x8D, 0x8B, 0x100, 0x100, 0x100, 0x100, 0xBA, 0x03 };

const SHORT patternOffset = 0xB;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* urukIntelAddress = nullptr;
    BYTE* urukIntelJmpAddress = nullptr;

    void UrukIntelInjectCode();
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
    urukIntelAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    urukIntelJmpAddress = urukIntelAddress + 0x5;
    return urukIntelAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(urukIntelAddress, reinterpret_cast<void*>(UrukIntelInjectCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}