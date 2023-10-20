#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Uruk Intel.ini";

bool Settings::partialIntel = true;
bool Settings::fullIntel = false;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	partialIntel = iniFile.GetBoolValue(L"General", L"PartialIntel", true);
	fullIntel = iniFile.GetBoolValue(L"General", L"FullIntel", false);

	if (fullIntel)
		partialIntel = false;
}

void Settings::SetDefaultSettings()
{
	partialIntel = true;
	fullIntel = false;
}

void Settings::SaveSettings()
{
	iniFile.SetBoolValue(L"General", L"PartialIntel", partialIntel);
	iniFile.SetBoolValue(L"General", L"FullIntel", fullIntel);

	iniFile.SaveFile(iniFileName.c_str());
}
