#include "mod.h"
#include "settings.h"
#include "input.h"
#include "menu.h"

const SHORT bytePatternMissionTimer[] = { 0x48, 0x8D, 0x59, 0x10, 0x48, 0x8B, 0xF9, 0x48, 0x8B, 0xCB, 0xE8, 0x100, 0x100, 0x100, 0x100, 0x84, 0xC0, 0x0F, 0x85 };

const SHORT bytePatternDevBool[] = { 0x48, 0x8D, 0x0D, 0x100, 0x100, 0x100, 0x100, 0xE8, 0x100, 0x100, 0x100, 0x100, 0x84, 0xC0, 0x74, 0x37, 0x48, 0x8B, 0xCB };

const SHORT bytePatternInfHealth[] = { 0x0F, 0x2F, 0xF2, 0xF3, 0x0F, 0x11, 0x93, 0x2C, 0x04, 0x00, 0x00 };

MemoryTools memTool(L"ShadowOfWar.exe");

extern "C"
{
    BYTE* devBoolAddress = nullptr;
    BYTE* missionTimerAddress = nullptr;
    BYTE* infiniteHealthAddress = nullptr;

    BYTE* infiniteHealthJmpAddr = nullptr;

    bool missionTimerEnabled = false;
    bool infiniteHealthEnabled = false;

    void InfiniteHealthInjectCode();
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
    memTool.Set(devBoolAddress, { 0x00 });
    memTool.Set(devBoolAddress + 1, { 0x00 });
    memTool.Set(devBoolAddress + 2, { 0x00 });
    memTool.Set(devBoolAddress + 3, { 0x00 });
    memTool.Set(missionTimerAddress, { 0x84, 0xC0 });
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

bool Mod::FindAddresses()
{
    BYTE* devBoolAob = memTool.Scan(bytePatternDevBool, sizeof(bytePatternDevBool) / sizeof(bytePatternDevBool[0]), 0);
    devBoolAddress = devBoolAob + *reinterpret_cast<int *>(devBoolAob + 3) + 7;

    missionTimerAddress = memTool.Scan(bytePatternMissionTimer, sizeof(bytePatternMissionTimer) / sizeof(bytePatternMissionTimer[0]), 0xF);
    infiniteHealthAddress = memTool.Scan(bytePatternInfHealth, sizeof(bytePatternInfHealth) / sizeof(bytePatternInfHealth[0]), 0);
    infiniteHealthJmpAddr = infiniteHealthAddress + 0xB;

    return devBoolAob && missionTimerAddress && infiniteHealthAddress;
}

void Mod::CreateHooks()
{
    ModLoader::LogAPI::GetSingleton()->Log("Creating hooks: %s", MH_StatusToString(
        MH_CreateHook(infiniteHealthAddress, reinterpret_cast<LPVOID>(InfiniteHealthInjectCode), nullptr)
    ));
}

void Mod::PlayActivateSound()
{
    PlaySound(L".\\plugins\\sound\\onActivate.wav", NULL, SND_ASYNC);
}

void Mod::ToggleFocusBool(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Focus - %s", devBoolAddress[0] == 0x00 ? "ON" : "OFF");
    PlayActivateSound();
    if (devBoolAddress[0] == 0x00)
        memTool.Set(devBoolAddress, { 0x01 });
    else
        memTool.Set(devBoolAddress, { 0x00 });
}

void Mod::ToggleMightBool(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Might - %s", devBoolAddress[1] == 0x00 ? "ON" : "OFF");
    PlayActivateSound();
    if (devBoolAddress[1] == 0x00)
        memTool.Set(devBoolAddress + 1, { 0x01 });
    else
        memTool.Set(devBoolAddress + 1, { 0x00 });
}

void Mod::ToggleArrowBool(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Arrows - %s", devBoolAddress[2] == 0x00 ? "ON" : "OFF");
    PlayActivateSound();
    if (devBoolAddress[2] == 0x00)
        memTool.Set(devBoolAddress + 2, { 0x01 });
    else
        memTool.Set(devBoolAddress + 2, { 0x00 });
}

void Mod::ToggleWrathBool(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Wrath - %s", devBoolAddress[3] == 0x00 ? "ON" : "OFF");
    PlayActivateSound();
    if (devBoolAddress[3] == 0x00)
        memTool.Set(devBoolAddress + 3, { 0x01 });
    else
        memTool.Set(devBoolAddress + 3, { 0x00 });
}

void Mod::ToggleInfiniteHealth(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Health - %s", !infiniteHealthEnabled ? "ON" : "OFF");
    PlayActivateSound();
    if (!infiniteHealthEnabled)
        MH_EnableHook(infiniteHealthAddress), infiniteHealthEnabled = true;
    else
        MH_DisableHook(infiniteHealthAddress), infiniteHealthEnabled = false;
}

void Mod::ToggleMissionTimers(void*)
{
    ModLoader::LogAPI::GetSingleton()->Log("Toggle Timers - %s", !missionTimerEnabled ? "ON" : "OFF");
    PlayActivateSound();
    if (!missionTimerEnabled)
        memTool.Set(missionTimerAddress, { 0xEB, 0x06 }), missionTimerEnabled = true;
    else
        memTool.Set(missionTimerAddress, { 0x84, 0xC0 }), missionTimerEnabled = false;
}