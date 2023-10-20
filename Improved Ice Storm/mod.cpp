#include "mod.h"
#include "settings.h"
#include "menu.h"
#include "input.h"

const SHORT bytePattern[] = { 0x41, 0x8B, 0x14, 0x92, 0x44, 0x0F, 0xA3, 0xC2, 0x0F, 0x92, 0xC0, 0xEB, 0x2F };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* abilityCheckAddress = nullptr;
    BYTE* abilityCheckJmpAddress = nullptr;

    bool isKeyHeld = false;

    void AbilityCheckHook();
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
    Input::StartInputProcessing();
    CreateHooks();
    ModLoader::LogAPI::GetSingleton()->Log("Finished loading.");
}

void Mod::DisableMod()
{
    Input::StopInputProcessing();
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

bool Mod::FindAddresses()
{
    abilityCheckAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    abilityCheckJmpAddress = abilityCheckAddress + 0x8;
    return abilityCheckAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(abilityCheckAddress, reinterpret_cast<LPVOID>(AbilityCheckHook), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}

void Mod::ToggleHotkeyActive(void*)
{
    isKeyHeld = !isKeyHeld;
}

void Mod::DisableHotkey()
{
    isKeyHeld = false;
}