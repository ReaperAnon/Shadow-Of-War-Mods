#include <imgui_hotkey.h>

bool ImGui::IsHotkeyBeingSet = false;

const char* const KeyNames[]
{
	"Tab",
	"Left",
	"Right",
	"Up",
	"Down",
	"Page Up",
	"Page Down",
	"Home",
	"End",
	"Insert",
	"Delete",
	"Backspace",
	"Space",
	"Enter",
	"Escape",
	"LCtrl",
	"LShift",
	"LAlt",
	"LSuper",
	"RCtrl",
	"RShift",
	"RAlt",
	"RSuper",
	"Menu",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"'",
	",",
	"-",
	".",
	"/",
	";",
	"=",
	"[",
	"\\",
	"]",
	"`",
	"Caps Lock",
	"Scrl Lock",
	"Num Lock",
	"Prnt Scrn",
	"Pause",
	"Num 0",
	"Num 1",
	"Num 2",
	"Num 3",
	"Num 4",
	"Num 5",
	"Num 6",
	"Num 7",
	"Num 8",
	"Num 9",
	"Num .",
	"Num /",
	"Num *",
	"Num -",
	"Num +",
	"Num Enter",
	"Num =",
	"Start",
	"Back",
	"Face Left",
	"Face Right",
	"Face Up",
	"Face Down",
	"Dpad Left",
	"Dpad Right",
	"Dpad Up",
	"Dpad Down",
	"L1",
	"R1",
	"L2",
	"R2",
	"L3",
	"R3",
	"LStick Left",
	"LStick Right",
	"LStick Up",
	"LStick Down",
	"RStick Left",
	"RStick Right",
	"RStick Up",
	"RStick Down",
	"LMB",
	"RMB",
	"MMB",
	"Mouse 4",
	"Mouse 5",
	"Mouse Wheel X",
	"Mouse Wheel Y"
};

const std::string ImGui::GetKeyName(ImGuiKey key1, ImGuiKey key2)
{
	if (key1 == 0)
		return "None";

	std::string displayName = KeyNames[key1 - 512];
	if (key2 != ImGuiKey_None)
	{
		displayName += " + ";
		displayName += KeyNames[key2 - 512];
	}

	return displayName;
}

bool ImGui::KeyPressBehavior(const bool isHovered, const bool isSelected, bool* focusReleasedWithNav, bool* isMouseActivation)
{
	static bool waitForRelease = false;
	if (!isSelected && !isHovered)
	{
		*focusReleasedWithNav = false;
		waitForRelease = false;
		return false;
	}

	if ((isHovered && IsKeyDown(ImGuiKey_MouseLeft)) || (isSelected && (IsKeyDown(ImGuiKey_Space) || IsKeyDown(ImGuiKey_NavGamepadActivate))))
	{
		if (isHovered && IsKeyDown(ImGuiKey_MouseLeft))
			*isMouseActivation = true;

		waitForRelease = true;
		return false;
	}

	if(waitForRelease)
	{
		if (*focusReleasedWithNav)
		{
			*focusReleasedWithNav = false;
			waitForRelease = false;
			return false;
		}

		waitForRelease = false;
		return true;
	}

	return false;
}

bool ImGui::Hotkey(const char* label, ImGuiKey* keyToSet1, ImGuiKey* keyToSet2, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiIO& io = GetIO();
	ImGuiContext& imguiContext = *GetCurrentContext();
	const ImGuiStyle& style = imguiContext.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	static int keysPressed = 0;
	static bool keyStates[ImGuiKey_NamedKey_COUNT];

	static bool isMouseActivation = false;
	static bool focusReleasedWithNav = false;
	const bool hovered = ItemHoverable(frame_bb, id, ImGuiItemFlags_None);
	if (imguiContext.ActiveId != id && (hovered || imguiContext.NavId == id))
	{
		if (hovered)
			imguiContext.NavId = id;

		const bool pressed = KeyPressBehavior(hovered, imguiContext.NavId == id, &focusReleasedWithNav, &isMouseActivation);
		if (pressed)
		{
			keysPressed = 0;
			ImGui::SetActiveID(id, window);
			ImGui::FocusWindow(window);
			memset(keyStates, 0, sizeof(keyStates));
			io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;
			io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;
		}
	}

	bool wasChanged = false;
	if (imguiContext.ActiveId == id)
	{
		IsHotkeyBeingSet = true;
		ImGuiKey newKey1 = ImGuiKey_None, newKey2 = ImGuiKey_None;

		if (!keyToSet2)
		{
			for (int keyID = ImGuiKey_NamedKey_BEGIN; keyID < ImGuiKey_NamedKey_BEGIN + 136; keyID++)
			{
				if (IsKeyDown((ImGuiKey)keyID))
				{
					if (keyStates[keyID - 512]) // skip button if it was already marked as pressed
						continue;

					keyStates[keyID - 512] = 1;
				}
				else if (keyStates[keyID - 512]) // if one key was pressed and released
				{
					*keyToSet1 = (ImGuiKey)keyID;
					IsHotkeyBeingSet = false;
					wasChanged = true;
					ClearActiveID();
				}
			}
		}
		else
		{
			for (int keyID = ImGuiKey_NamedKey_BEGIN; keyID < ImGuiKey_NamedKey_BEGIN + 136; keyID++)
			{
				if (IsKeyDown((ImGuiKey)keyID))
				{
					if (keyStates[keyID - 512]) // skip button if it was already marked as pressed
						continue;

					++keysPressed;
					keyStates[keyID - 512] = 1;
					if (keysPressed > 1) // if two keys were pressed at once
					{
						for (int i = 0; i < ImGuiKey_NamedKey_COUNT; i++)
						{
							if (keyStates[i])
							{
								if (newKey1 == ImGuiKey_None)
									newKey1 = (ImGuiKey)(i + 512);
								else if (newKey1 != (ImGuiKey)(i + 512))
									newKey2 = (ImGuiKey)(i + 512);
							}
						}

						if (newKey1 == ImGuiKey_MouseLeft || newKey2 == ImGuiKey_MouseLeft || newKey1 == ImGuiKey_Space || newKey2 == ImGuiKey_Space || newKey1 == ImGuiKey_NavGamepadActivate || newKey2 == ImGuiKey_NavGamepadActivate)
							focusReleasedWithNav = true;

						IsHotkeyBeingSet = false;
						*keyToSet1 = newKey1;
						*keyToSet2 = newKey2;
						wasChanged = true;
						ClearActiveID();
					}
				}
				else if (keyStates[keyID - 512]) // if one key was pressed and released
				{
					newKey1 = (ImGuiKey)keyID;
					IsHotkeyBeingSet = false;
					*keyToSet1 = newKey1;
					*keyToSet2 = newKey2;
					wasChanged = true;
					ClearActiveID();
				}
			}
		}

		if (IsKeyDown(ImGuiKey_Escape)) // remove bound key if escape was pressed
		{
			*keyToSet1 = ImGuiKey_None;
			if (keyToSet2)
				*keyToSet2 = ImGuiKey_None;
			IsHotkeyBeingSet = false;
			wasChanged = true;
			ClearActiveID();
		}
	}

	// Render
	RenderNavHighlight(total_bb, id);
	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);

	std::string displayName = "None";
	if (imguiContext.ActiveId == id)
		displayName = "<PRESS A KEY>";
	else
		displayName = GetKeyName(*keyToSet1, *keyToSet2);

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, displayName.c_str(), NULL, NULL, style.ButtonTextAlign, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	if (wasChanged)
	{
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		if (!isMouseActivation)
			imguiContext.NavDisableHighlight = false;
		isMouseActivation = false;
	}

	return wasChanged;
}