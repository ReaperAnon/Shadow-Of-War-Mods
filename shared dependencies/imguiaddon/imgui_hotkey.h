#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include <string>
#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
	extern bool IsHotkeyBeingSet;

	const std::string GetKeyName(ImGuiKey key1, ImGuiKey key2);

	bool KeyPressBehavior(const bool isHovered, const bool isSelected, bool* focusReleasedWithNav, bool* isMouseActivation);

	bool Hotkey(const char* label, ImGuiKey* keyToSet1, ImGuiKey* keyToSet2 = nullptr, const ImVec2& size_arg = ImVec2(0, 0));
}
