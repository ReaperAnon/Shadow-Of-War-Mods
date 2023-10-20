#pragma once

#include "framework.h"

namespace Input
{
	extern HWND PROCHWND;

	extern InputProcessor<ImGuiKey> inputProcessor;

	BOOL CALLBACK WorkerProc(HWND hwnd, LPARAM lParam);

	GameKey<ImGuiKey>* GetGameKey(size_t idx);

	GameKey<ImGuiKey>* MakeGameKey(const wchar_t* inputString);

	GameKey<ImGuiKey>* MakeGameKey(ImGuiKey firstKey, ImGuiKey secondKey = ImGuiKey_None, ImGuiKey modKey = ImGuiKey_None);

	void StartInputProcessing();

	void StopInputProcessing();
}