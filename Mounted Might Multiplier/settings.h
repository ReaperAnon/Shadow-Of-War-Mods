#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern "C" float	mightGainMult;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}