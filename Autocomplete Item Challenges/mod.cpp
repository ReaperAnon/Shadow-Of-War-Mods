#include "mod.h"

const SHORT bytePattern[] = { 0x48, 0x8B, 0x51, 0x08, 0x33, 0xC0, 0x48, 0x85, 0xD2, 0x74, 0x09, 0x8B, 0x4A, 0x34 };

const SHORT patternOffset = 0xB;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* itemChallengeAddress = nullptr;
    BYTE* itemChallengeJmpAddr = nullptr;

    void ItemChallengeInjectCode();
}

void Mod::InitalizeMod()
{
    ModLoader::LogAPI::GetSingleton()->Log("Initializing MinHook: %s", MH_StatusToString(
        MH_Initialize()
    ));

    while (!FindAddresses())
        Sleep(500);

    ModLoader::LogAPI::GetSingleton()->Log("Addresses found.");
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
    itemChallengeAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    itemChallengeJmpAddr = itemChallengeAddress + 0x6;
    return itemChallengeAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(itemChallengeAddress, reinterpret_cast<void*>(ItemChallengeInjectCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}