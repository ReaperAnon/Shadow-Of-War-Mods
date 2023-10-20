#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern bool			playSound;
	extern bool			toggleBehavior;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}