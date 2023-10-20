#include "mod.h"

const SHORT bytePattern[] = { 0x0F, 0x84, 0xCE, 0x00, 0x00, 0x00, 0xE8, 0xE7 };

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
    memTool.Set(skillReqAddress, { 0x0F, 0x84, 0xCE, 0x00, 0x00, 0x00 });
}

bool Mod::FindAddresses()
{
    skillReqAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return skillReqAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Enabling hook.");
    memTool.Set(skillReqAddress, { 0xE9, 0xCF, 0x00, 0x00, 0x00, 0x90 });
}