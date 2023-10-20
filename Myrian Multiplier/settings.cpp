#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Myrian Multiplier.ini";

float Settings::myrianLossMult = 1;
float Settings::myrianGainMult = 1;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	myrianLossMult = iniFile.GetDoubleValue(L"General", L"MyrianLossMult", 1);
	myrianGainMult = iniFile.GetDoubleValue(L"General", L"MyrianGainMult", 1);
}

void Settings::SetDefaultSettings()
{
	myrianLossMult = 1;
	myrianGainMult = 1;
}

void Settings::SaveSettings()
{
	iniFile.SetDoubleValue(L"General", L"MyrianLossMult", myrianLossMult);
	iniFile.SetDoubleValue(L"General", L"MyrianGainMult", myrianGainMult);

	iniFile.SaveFile(iniFileName.c_str());
}
