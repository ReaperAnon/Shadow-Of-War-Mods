#include "menu.h"
#include "input.h"
#include "settings.h"
#include "mod.h"

void Menu::ShowSettings()
{
	ImGui::Checkbox("Toggle Sound", &Settings::playSound);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Whether to play a subtle sound on activation or not.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	if(ImGui::Checkbox("Toggle Behavior", &Settings::toggleBehavior)) {
		Input::GetGameKey(0)->ReleaseAction = Settings::toggleBehavior ? nullptr : Mod::ToggleSkillEquipHook;
		Mod::DisableHotkey();
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Toggle functionality on key press when enabled instead of having to hold the key to keep it active.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Hotkey("Multi Equip Toggle Key", &Input::GetGameKey(0)->FirstKey, &Input::GetGameKey(0)->SecondKey);
}