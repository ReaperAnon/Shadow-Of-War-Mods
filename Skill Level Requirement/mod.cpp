#include "mod.h"

const SHORT bytePattern[] = { 0x41, 0x8B, 0xE8, 0x48, 0x8B, 0xFA, 0xE8 };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* skillReqAddress = nullptr;
    BYTE* skillReqJmpAddr = nullptr;

    void SkillReqInjectCode();
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
    skillReqAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    skillReqJmpAddr = skillReqAddress + 0x6;
    return skillReqAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(skillReqAddress, reinterpret_cast<void*>(SkillReqInjectCode), nullptr)
    ));

    ModLoader::LogAPI::GetSingleton()->Log("Enabling hooks: %s", MH_StatusToString(
        MH_EnableHook(MH_ALL_HOOKS)
    ));
}