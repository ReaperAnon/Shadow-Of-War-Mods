#include "mod.h"
#include "menu.h"
#include "settings.h"

const SHORT bytePattern[] = { 0xE8, 0x100, 0x100, 0x100, 0x100, 0x45, 0x89, 0x51, 0x20, 0x48, 0x83, 0xC4, 0x28 };

const SHORT patternOffset = 5;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* myrianChangeAddress = nullptr;
    void* myrianJmpAddress = nullptr;

    void MyrianChangeCode();
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
    myrianChangeAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return myrianChangeAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(myrianChangeAddress, reinterpret_cast<void*>(MyrianChangeCode), &myrianJmpAddress)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}