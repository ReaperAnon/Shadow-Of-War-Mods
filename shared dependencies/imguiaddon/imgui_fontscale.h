#pragma once

#include "imgui.h"

namespace ImGui
{
	extern float origFontScale;
	
	void PushFontScale(float scale);
	
	void PopFontScale();
}
