#include "settings.h"
#include "input.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Multi Equip Skills.ini";

bool Settings::playSound = true;
bool Settings::toggleBehavior = false;

void Settings::ReadSettings()
{
	GameKey<ImGuiKey>* gameKey;

	iniFile.LoadFile(iniFileName.c_str());

	playSound = iniFile.GetBoolValue(L"General", L"PlaySound", true);
	toggleBehavior = iniFile.GetBoolValue(L"General", L"ToggleBehavior", false);
	
	gameKey = Input::MakeGameKey(iniFile.GetValue(L"General", L"ToggleSkillEquip", L"527 0 0"));
	gameKey->PressAction = Mod::ToggleSkillEquipHook;
	gameKey->ReleaseAction = toggleBehavior ? nullptr : Mod::ToggleSkillEquipHook;
}

void Settings::SetDefaultSettings()
{
	GameKey<ImGuiKey>* gameKey;

	playSound = true;
	toggleBehavior = false;

	gameKey = Input::GetGameKey(0);
	gameKey->ReleaseAction = toggleBehavior ? nullptr : Mod::ToggleSkillEquipHook;
	gameKey->RemapKeys(ImGuiKey_LeftCtrl, ImGuiKey_None);

	Mod::DisableHotkey();
}

void Settings::SaveSettings()
{
	wchar_t buffer[16];
	GameKey<ImGuiKey>* gameKey;

	gameKey = Input::GetGameKey(0);
	swprintf(buffer, 16, L"%i %i %i", gameKey->FirstKey, gameKey->SecondKey, gameKey->ModKey);
	iniFile.SetValue(L"General", L"ToggleSkillEquip", buffer);

	iniFile.SetBoolValue(L"General", L"PlaySound", playSound);
	iniFile.SetBoolValue(L"General", L"ToggleBehavior", toggleBehavior);

	iniFile.SaveFile(iniFileName.c_str());
}
