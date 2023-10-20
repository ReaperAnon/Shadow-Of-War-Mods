#include "menu.h"
#include "settings.h"
#include "mod.h"

void Menu::ShowSettings()
{
	bool update = false;
	ImGui::Text("Focus Regen Multiplier"); ImGui::Spacing();
	update |= ImGui::SliderFloat("##regenMult", &Settings::elvenSpeedRegenMult, -1, 1, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Text("Ability Duration Multiplier"); ImGui::Spacing();
	update |= ImGui::SliderFloat("##durationMult", &Settings::elvenSpeedDurationMult, 0, 10, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	if (update)
		Mod::RefreshValues();
}