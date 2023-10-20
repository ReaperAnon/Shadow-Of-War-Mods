#include "menu.h"
#include "settings.h"
#include "mod.h"

void Menu::ShowSettings()
{
	bool update = false;
	ImGui::Text("Minimum Field of View"); ImGui::Spacing();
	update |= ImGui::SliderFloat("##minFOV", &Settings::minFOVRaw, 40, 70, "%.0f FOV", ImGuiSliderFlags_AlwaysClamp);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Text("Maximum Field of View"); ImGui::Spacing();
	update |= ImGui::SliderFloat("##maxFOV", &Settings::maxFOVRaw, 40, 70, "%.0f FOV", ImGuiSliderFlags_AlwaysClamp);
	if (update)
		Mod::RefreshFOV();
}