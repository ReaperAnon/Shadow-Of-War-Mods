#include "mod.h"

const SHORT bytePattern[] = { 0x45, 0x33, 0xC0, 0x49, 0x8B, 0xCA, 0xE8, 0x8B, 0xB3 };

const SHORT patternOffset = 0;

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* hitStreakAddress = nullptr;
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
    memTool.Set(hitStreakAddress, { 0x45, 0x33, 0xC0 });
}

bool Mod::FindAddresses()
{
    hitStreakAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return hitStreakAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Enabling hook.");
    memTool.Set(hitStreakAddress, { 0x90, 0x90, 0x90 });
}