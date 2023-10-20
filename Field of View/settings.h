#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern float		minFOVRaw;
	extern float		maxFOVRaw;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}