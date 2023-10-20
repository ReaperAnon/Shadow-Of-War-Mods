#pragma once

#include "framework.h"

namespace Mod
{
	void InitalizeMod();

	void DisableMod();

	bool FindAddresses();

	void CreateHooks();

	void PlayActivateSound();

	void ToggleFocusBool(void*);

	void ToggleMightBool(void*);

	void ToggleArrowBool(void*);

	void ToggleWrathBool(void*);

	void ToggleInfiniteHealth(void*);

	void ToggleMissionTimers(void*);
}