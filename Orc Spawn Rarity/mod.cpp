#include "mod.h"
#include "settings.h"
#include "menu.h"

const SHORT bytePattern[] = { 0x48, 0x8D, 0x4C, 0x24, 0x100, 0x0F, 0x57, 0xC0, 0x33, 0xDB };

const SHORT patternOffset = -0x1E;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* rarityAddress = nullptr;
    void* rarityJmpAddr = nullptr;

    int commonIdx = 2;
    int epicIdx = 0;
    int legendaryIdx = 1;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    auto randomNumber = std::bind(distribution, generator);

    int GetRandomNumber()
    {
        return randomNumber();
    }

    void RarityHook();
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
    rarityAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return rarityAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(rarityAddress, reinterpret_cast<void*>(RarityHook), &rarityJmpAddr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}