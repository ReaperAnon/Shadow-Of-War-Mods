#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern "C" int		epicChance;
	extern "C" int		legendaryChance;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}