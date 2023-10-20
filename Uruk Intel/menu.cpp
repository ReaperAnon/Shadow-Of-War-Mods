#include "menu.h"
#include "settings.h"
#include "mod.h"

void Menu::ShowSettings()
{
	if (ImGui::Checkbox("All Strengths Known", &Settings::partialIntel)) { if (Settings::partialIntel) Settings::fullIntel = false; }
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("All orcs have their looks, names and strengths uncovered by default when they spawn. Safe to use at all times.");
		ImGui::EndTooltip();
	}
	ImGui::Spacing();
	if (ImGui::Checkbox("Strengths and Weaknesses Known", &Settings::fullIntel)) { if (Settings::fullIntel) Settings::partialIntel = false; }
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
	{
		ImGui::BeginTooltip();
		ImGui::SetTooltip("All orcs have their looks, names and strengths, but also their weaknesses uncovered by default when they spawn.\nCan cause your game to lock up if uncovering a captain is part of a quest, like interrogating the worm at the start of the game in Minas Ithil.");
		ImGui::EndTooltip();
	}
}