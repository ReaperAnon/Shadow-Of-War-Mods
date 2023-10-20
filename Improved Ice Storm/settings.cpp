#include "settings.h"
#include "input.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Improved Ice Storm.ini";

int Settings::stunBehavior = 1;
int Settings::flurryBehavior = 0;
bool Settings::toggleBehavior = false;

void Settings::ReadSettings()
{
	GameKey<ImGuiKey>* gameKey;

	iniFile.LoadFile(iniFileName.c_str());

	flurryBehavior = iniFile.GetLongValue(L"General", L"FlurryBehavior", 0);
	stunBehavior = iniFile.GetLongValue(L"General", L"StunBehavior", 1);
	toggleBehavior = iniFile.GetBoolValue(L"General", L"ToggleBehavior", false);

	gameKey = Input::MakeGameKey(iniFile.GetValue(L"General", L"FlurryModifierKey", L"644 0 0"));
	gameKey->PressAction = Mod::ToggleHotkeyActive;
	gameKey->ReleaseAction = toggleBehavior ? nullptr : Mod::ToggleHotkeyActive;
}

void Settings::SetDefaultSettings()
{
	flurryBehavior = 0;
	stunBehavior = 1;
	toggleBehavior = false;

	Input::GetGameKey(0)->ReleaseAction = toggleBehavior ? nullptr : Mod::ToggleHotkeyActive;
	Input::GetGameKey(0)->RemapKeys(ImGuiKey_MouseX1, ImGuiKey_None);
	Mod::DisableHotkey();
}

void Settings::SaveSettings()
{
	wchar_t buffer[16];
	GameKey<ImGuiKey>* gameKey;
	
	gameKey = Input::GetGameKey(0);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"General", L"FlurryModifierKey", buffer);

	iniFile.SetLongValue(L"General", L"FlurryBehavior", flurryBehavior);
	iniFile.SetLongValue(L"General", L"StunBehavior", stunBehavior);
	iniFile.SetBoolValue(L"General", L"ToggleBehavior", toggleBehavior);

	iniFile.SaveFile(iniFileName.c_str());
}
