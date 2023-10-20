#include "settings.h"
#include "mod.h"

CSimpleIni Settings::iniFile;
std::string Settings::iniFileName = ".\\plugins\\config\\Orc Spawn Rarity.ini";

int Settings::epicChance = 0;
int Settings::legendaryChance = 0;

void Settings::ReadSettings()
{
	iniFile.LoadFile(iniFileName.c_str());

	epicChance = iniFile.GetLongValue(L"General", L"EpicChance", 15);
	legendaryChance = iniFile.GetLongValue(L"General", L"LegendaryChance", 15);
}

void Settings::SetDefaultSettings()
{
	epicChance = 15;
	legendaryChance = 15;
}

void Settings::SaveSettings()
{
	iniFile.SetLongValue(L"General", L"EpicChance", epicChance);
	iniFile.SetLongValue(L"General", L"LegendaryChance", legendaryChance);

	iniFile.SaveFile(iniFileName.c_str());
}
