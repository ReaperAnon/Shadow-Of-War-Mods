#pragma once

#include "framework.h"

namespace Mod
{
	void InitalizeMod();

	void DisableMod();

	bool FindAddresses();

	void ToggleSkillEquipHook(void*);

	void CreateHooks();

	void DisableHotkey();
}