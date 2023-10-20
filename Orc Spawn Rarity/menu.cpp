#include "menu.h"
#include "settings.h"

void Menu::ShowSettings()
{
	ImGui::Text("Additional Epic Spawn Chance");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Additional chance to spawn an epic tier orc. The legendary setting has priority. Has no effect on the game's tier system (so no higher chance of orcs cheating death), setting it above zero merely increases the likelihood of regular orcs spawning as epic.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	ImGui::SliderInt("##epicSpawnChance", &Settings::epicChance, 0, 100, "%d%", ImGuiSliderFlags_AlwaysClamp);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Additional chance to spawn an epic tier orc. The legendary setting has priority. Has no effect on the game's tier system (so no higher chance of orcs cheating death), setting it above zero merely increases the likelihood of regular orcs spawning as epic.");
		ImGui::EndTooltip();
	}
	ImGui::Text("Additional Legendary Spawn Chance");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Additional chance to spawn a legendary tier orc. The legendary setting has priority. Has no effect on the game's tier system (so no higher chance of orcs cheating death), setting it above zero merely increases the likelihood of regular orcs spawning as legendary.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	ImGui::SliderInt("##legendarySpawnChance", &Settings::legendaryChance, 0, 100, "%d%", ImGuiSliderFlags_AlwaysClamp);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("Additional chance to spawn a legendary tier orc. The legendary setting has priority. Has no effect on the game's tier system (so no higher chance of orcs cheating death), setting it above zero merely increases the likelihood of regular orcs spawning as legendary.");
		ImGui::EndTooltip();
	}
}