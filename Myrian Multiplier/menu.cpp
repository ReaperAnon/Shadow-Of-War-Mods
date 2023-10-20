#include "menu.h"
#include "settings.h"

void Menu::ShowSettings()
{
	ImGui::Text("Myrian Loss Multiplier");
	ImGui::Spacing();
	ImGui::SliderFloat("##myrianLossMult", &Settings::myrianLossMult, -3, 3, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	// ImGui::Text("Myrian Gain Multiplier");
	// ImGui::Spacing();
	// ImGui::SliderFloat("##myrianGainMult", &Settings::myrianGainMult, -3, 3, "%.2f", ImGuiSliderFlags_AlwaysClamp);
}