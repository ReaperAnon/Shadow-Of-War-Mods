#include "menu.h"
#include "settings.h"
#include "mod.h"

void Menu::ShowSettings()
{
	ImGui::Text("Might Gain Multiplier");
	ImGui::Spacing();
	ImGui::SliderFloat("##mightMult", &Settings::mightGainMult, 0, 10, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::EndTabItem();
}