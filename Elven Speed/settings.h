#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern float		elvenSpeedRegenMult;
	extern float		elvenSpeedDurationMult;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}