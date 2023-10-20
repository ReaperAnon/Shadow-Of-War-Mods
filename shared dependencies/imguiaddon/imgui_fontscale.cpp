#include "imgui_fontscale.h"

float ImGui::origFontScale = 0;

void ImGui::PushFontScale(float scale)
{
	origFontScale = ImGui::GetFont()->Scale;
	ImGui::GetFont()->Scale = scale;
	ImGui::PushFont(ImGui::GetFont());
}

void ImGui::PopFontScale()
{
	ImGui::GetFont()->Scale = origFontScale;
    ImGui::PopFont();
}