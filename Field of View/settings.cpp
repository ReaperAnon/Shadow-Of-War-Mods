#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\FOV Extender.ini";

float Settings::minFOVRaw = 0;
float Settings::maxFOVRaw = 0;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	minFOVRaw = iniFile.GetDoubleValue(L"General", L"MinFOV", 40);
	maxFOVRaw = iniFile.GetDoubleValue(L"General", L"MaxFOV", 55);
	Mod::RefreshFOV();
}

void Settings::SetDefaultSettings()
{
	minFOVRaw = 40;
	maxFOVRaw = 55;
	Mod::RefreshFOV();
}

void Settings::SaveSettings()
{
	iniFile.SetDoubleValue(L"General", L"MinFOV", minFOVRaw);
	iniFile.SetDoubleValue(L"General", L"MaxFOV", maxFOVRaw);

	iniFile.SaveFile(iniFileName.c_str());
}
