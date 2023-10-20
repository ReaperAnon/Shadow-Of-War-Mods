#include "mod.h"

const SHORT bytePattern[] = { 0x75, 0x34, 0x48, 0x85, 0xDB };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* skillReqAddress = nullptr;
}

void Mod::InitalizeMod()
{
    while (!FindAddresses())
        Sleep(500);

    ModLoader::LogAPI::GetSingleton()->Log("Addresses found.");
    CreateHooks();
    ModLoader::LogAPI::GetSingleton()->Log("Finished loading.");
}

void Mod::DisableMod()
{
    memTool.Set(skillReqAddress, { 0x75 });
}

bool Mod::FindAddresses()
{
    skillReqAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return skillReqAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Enabling hook.");
    memTool.Set(skillReqAddress, { 0xEB });
}