#include "mod.h"
#include "settings.h"
#include "menu.h"

const SHORT bytePattern[] = { 0x0F, 0x28, 0xD8, 0x8B, 0x08, 0x89, 0x8B };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* fovAddress = nullptr;
    BYTE* fovJmpAddr = nullptr;

    float oldFOV = 0.69813f;
    float minFOV, minFOVRaw;
    float maxFOV, maxFOVRaw;

    void FOVCode();
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
    fovAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    fovJmpAddr = fovAddress + 0x5;
    return fovAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(fovAddress, reinterpret_cast<LPVOID>(FOVCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}

void Mod::RefreshFOV()
{
    minFOV = Settings::minFOVRaw * 0.01745329252;
    maxFOV = Settings::maxFOVRaw * 0.01745329252;
}