#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern "C" float	myrianLossMult;
	extern "C" float	myrianGainMult;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}