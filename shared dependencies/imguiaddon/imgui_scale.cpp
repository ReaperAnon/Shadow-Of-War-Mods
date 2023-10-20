#include "imgui_scale.h"

float ImGui::GetResolutionScale()
{
	ImGuiIO& io = ImGui::GetIO();
	float resActual = io.DisplaySize.x * io.DisplaySize.y;

	return (io.DisplaySize.x / 1920 + io.DisplaySize.y / 1080) / 2.f;
}

ImVec2 ImGui::GetScaledScreenCoord(ImVec2 coords)
{
	ImGuiIO& io = ImGui::GetIO();

	return ImVec2(coords.x / 1920 * io.DisplaySize.x, coords.y / 1080 * io.DisplaySize.y);
}
