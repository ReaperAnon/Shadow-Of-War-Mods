#include "mod.h"
#include "settings.h"
#include "menu.h"

const SHORT bytePattern[] = { 0xF3, 0x0F, 0x10, 0xBB, 0x08, 0x01, 0x00, 0x00 };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* elvenSpeedAddress = nullptr;
    BYTE* elvenSpeedJmpAddr = 0;

    float elvenSpeedDrain = -6; // default focus drain rate of elven speed
    float elvenSpeedRegen = 40; // default focus regen rate
    float elvenSpeedDuration = 5; // default elven speed duration

    void ElvenSpeedInjectCode();
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
    elvenSpeedAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    elvenSpeedJmpAddr = elvenSpeedAddress + 0x8;
    return elvenSpeedAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(elvenSpeedAddress, reinterpret_cast<void*>(ElvenSpeedInjectCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}

void Mod::RefreshValues()
{
    elvenSpeedRegen = 40 * Settings::elvenSpeedRegenMult;
    elvenSpeedDuration = 5 * Settings::elvenSpeedDurationMult;
}