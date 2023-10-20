#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;
	
	extern "C" int		stunBehavior;
	extern "C" int		flurryBehavior;
	extern bool			toggleBehavior;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}