#include "menu.h"
#include "input.h"
#include "settings.h"
#include "mod.h"

const char* Menu::flurryModes[] = { "Normal Attacks", "Flurry Attack" };
const char* Menu::stunModes[] = { "Normal Stun", "Frost Stun" };

void Menu::ShowSettings()
{
	if(ImGui::Checkbox("Toggle Behavior", &Settings::toggleBehavior)) { Input::GetGameKey(0)->ReleaseAction = Settings::toggleBehavior ? nullptr : Mod::ToggleHotkeyActive; Mod::DisableHotkey(); }
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("By default the modifier button must be held to switch behaviors, but with this enabled the behavior will be toggled between states instead.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Hotkey("Behavior Modifier", &Input::GetGameKey(0)->FirstKey, &Input::GetGameKey(0)->SecondKey);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Toggle between behavior states on key press when enabled instead of having to hold the modifier for it.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
	ImGui::Text("Frozen Enemy Behavior");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Default behavior for attacking a frozen enemy.");
		ImGui::EndTooltip();
	}
	ImGui::ListBox("##flurry", &Settings::flurryBehavior, flurryModes, 2);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Default behavior for attacking a frozen enemy.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
	ImGui::Text("Wraith Stun Behavior");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Default behavior for the wraith stun ability.");
		ImGui::EndTooltip();
	}
	ImGui::ListBox("##stun", &Settings::stunBehavior, stunModes, 2);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Default behavior for the wraith stun ability.");
		ImGui::EndTooltip();
	}
}