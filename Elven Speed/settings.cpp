#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Elven Speed.ini";

float Settings::elvenSpeedRegenMult = 0;
float Settings::elvenSpeedDurationMult = 2;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	elvenSpeedRegenMult = iniFile.GetDoubleValue(L"General", L"RegenRateMult", 0);
	elvenSpeedDurationMult = iniFile.GetDoubleValue(L"General", L"DurationMult", 2);
	Mod::RefreshValues();
}

void Settings::SetDefaultSettings()
{
	elvenSpeedRegenMult = 0;
	elvenSpeedDurationMult = 2;
	Mod::RefreshValues();
}

void Settings::SaveSettings()
{
	iniFile.SetDoubleValue(L"General", L"RegenRateMult", elvenSpeedRegenMult);
	iniFile.SetDoubleValue(L"General", L"DurationMult", elvenSpeedDurationMult);

	iniFile.SaveFile(iniFileName.c_str());
}
