#include "menu.h"
#include "input.h"
#include "settings.h"

void Menu::ShowSettings()
{
	ImGui::Hotkey("Toggle Infinite Focus", &Input::GetGameKey(0)->FirstKey, &Input::GetGameKey(0)->SecondKey); ImGui::Spacing();
	ImGui::Hotkey("Toggle Infinite Might", &Input::GetGameKey(1)->FirstKey, &Input::GetGameKey(1)->SecondKey); ImGui::Spacing();
	ImGui::Hotkey("Toggle Infinite Arrows", &Input::GetGameKey(2)->FirstKey, &Input::GetGameKey(2)->SecondKey); ImGui::Spacing();
	ImGui::Hotkey("Toggle Infinite Wrath", &Input::GetGameKey(3)->FirstKey, &Input::GetGameKey(3)->SecondKey); ImGui::Spacing();
	ImGui::Hotkey("Toggle Infinite Health", &Input::GetGameKey(4)->FirstKey, &Input::GetGameKey(4)->SecondKey); ImGui::Spacing();
	ImGui::Hotkey("Toggle Infinite MissionTime", &Input::GetGameKey(5)->FirstKey, &Input::GetGameKey(5)->SecondKey);
}