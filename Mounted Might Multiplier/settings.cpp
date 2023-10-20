#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Mounted Might Multiplier.ini";

float Settings::mightGainMult = 1;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	mightGainMult = iniFile.GetDoubleValue(L"General", L"MightGainMult", 0);
}

void Settings::SetDefaultSettings()
{
	mightGainMult = 3;
}

void Settings::SaveSettings()
{
	iniFile.SetDoubleValue(L"General", L"MightGainMult", mightGainMult);

	iniFile.SaveFile(iniFileName.c_str());
}
