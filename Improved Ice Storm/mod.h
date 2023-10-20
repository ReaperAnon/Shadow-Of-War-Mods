#pragma once

#include "framework.h"

namespace Mod
{
	void InitalizeMod();

	void DisableMod();

	bool FindAddresses();

	void CreateHooks();

	void ToggleHotkeyActive(void*);
	
	void DisableHotkey();
}