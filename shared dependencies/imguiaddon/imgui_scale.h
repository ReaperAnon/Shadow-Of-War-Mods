#pragma once

#include "imgui.h"

namespace ImGui
{
	float GetResolutionScale();
	
	ImVec2 GetScaledScreenCoord(ImVec2 coords);
}
