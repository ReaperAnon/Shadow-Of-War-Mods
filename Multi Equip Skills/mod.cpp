#include "mod.h"
#include "settings.h"
#include "input.h"
#include "menu.h"

const SHORT bytePattern[] = { 0x74, 0x100, 0x48, 0x8B, 0x100, 0x40, 0x04, 0x00, 0x00, 0x48, 0x85, 0x100, 0x74, 0x100, 0x4C, 0x39, 0x100, 0x40, 0x74, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x08, 0x00, 0x00, 0x00 };

const SHORT patternOffset = -0x12;

MemoryTools memTool(L"ShadowOfWar.exe");

bool isSkillHookEnabled = false;

extern "C"
{
   BYTE* skillEquipAddress = nullptr;
}

void Mod::InitalizeMod()
{
    while (!FindAddresses())
        Sleep(500);

    ModLoader::LogAPI::GetSingleton()->Log("Addresses found.");
    Settings::ReadSettings();
    ModLoader::LogAPI::GetSingleton()->Log("Registering menu.");
    ModLoader::MenuAPI::GetSingleton()->RegisterMenuEntry(Menu::ShowSettings, Settings::SetDefaultSettings, Settings::SaveSettings);
    Input::StartInputProcessing();
    ModLoader::LogAPI::GetSingleton()->Log("Finished loading.");
}

void Mod::DisableMod()
{
    Input::StopInputProcessing();
    memTool.Set(skillEquipAddress, { 0x74 });
}

bool Mod::FindAddresses()
{
    skillEquipAddress = memTool.Scan(bytePattern, sizeof(bytePattern) / sizeof(bytePattern[0]), patternOffset);
    return skillEquipAddress;
}

void Mod::ToggleSkillEquipHook(void*)
{
    if (Settings::playSound)
        PlaySound(L".\\plugins\\sound\\onEquip.wav", NULL, SND_ASYNC);

    if (isSkillHookEnabled)
        memTool.Set(skillEquipAddress, { 0x74 }), isSkillHookEnabled = false;
    else
        memTool.Set(skillEquipAddress, { 0xEB }), isSkillHookEnabled = true;
}

void Mod::DisableHotkey()
{
    memTool.Set(skillEquipAddress, { 0x74 }), isSkillHookEnabled = false;
}