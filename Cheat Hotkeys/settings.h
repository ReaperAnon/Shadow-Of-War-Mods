#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}