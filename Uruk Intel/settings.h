#pragma once

#include "framework.h"

namespace Settings
{
	extern CSimpleIni	iniFile;
	extern std::string	iniFileName;

	extern "C" bool 	partialIntel;
	extern "C" bool		fullIntel;

	void ReadSettings();

	void SetDefaultSettings();

	void SaveSettings();
}