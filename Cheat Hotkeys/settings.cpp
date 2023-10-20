#include "settings.h"
#include "input.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Cheat Hotkeys.ini";

void Settings::ReadSettings()
{
	GameKey<ImGuiKey>* gameKey;

	iniFile.LoadFile(iniFileName.c_str());

	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteFocus", L"572 0 0"));
	gameKey->PressAction = Mod::ToggleFocusBool;
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteMight", L"573 0 0"));
	gameKey->PressAction = Mod::ToggleMightBool;
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteArrows", L"574 0 0"));
	gameKey->PressAction = Mod::ToggleArrowBool;
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteWrath", L"575 0 0"));
	gameKey->PressAction = Mod::ToggleWrathBool;
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteHealth", L"576 0 0"));
	gameKey->PressAction = Mod::ToggleInfiniteHealth;
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"Hotkeys", L"ToggleInfiniteMissionTime", L"577 0 0"));
	gameKey->PressAction = Mod::ToggleMissionTimers;
}

void Settings::SetDefaultSettings()
{
	Input::GetGameKey(0)->RemapKeys(ImGuiKey_F1, ImGuiKey_None, ImGuiKey_None);
	Input::GetGameKey(1)->RemapKeys(ImGuiKey_F2, ImGuiKey_None, ImGuiKey_None);
	Input::GetGameKey(2)->RemapKeys(ImGuiKey_F3, ImGuiKey_None, ImGuiKey_None);
	Input::GetGameKey(3)->RemapKeys(ImGuiKey_F4, ImGuiKey_None, ImGuiKey_None);
	Input::GetGameKey(4)->RemapKeys(ImGuiKey_F5, ImGuiKey_None, ImGuiKey_None);
	Input::GetGameKey(5)->RemapKeys(ImGuiKey_F6, ImGuiKey_None, ImGuiKey_None);
}

void Settings::SaveSettings()
{
	wchar_t buffer[16];
	GameKey<ImGuiKey>* gameKey;

	gameKey = Input::GetGameKey(0);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteFocus", buffer);
	gameKey = Input::GetGameKey(1);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteMight", buffer);
	gameKey = Input::GetGameKey(2);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteArrows", buffer);
	gameKey = Input::GetGameKey(3);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteWrath", buffer);
	gameKey = Input::GetGameKey(4);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteHealth", buffer);
	gameKey = Input::GetGameKey(5);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"Hotkeys", L"ToggleInfiniteMissionTime", buffer);

	iniFile.SaveFile(iniFileName.c_str());
}
