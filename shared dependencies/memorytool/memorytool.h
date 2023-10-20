#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

// A memory pattern scanner class.
class MemoryTools
{
private:
    LPVOID moduleBase;
    uintptr_t moduleSize;

    // Scans a given memory part for a given pattern.
	BYTE* ScanPattern(const SHORT* pattern, uintptr_t patternLen, BYTE* begin, uintptr_t size)
	{
		uintptr_t patternIdx = 0;

		for (uintptr_t i = 0; i < size; ++i)
		{
			if (pattern[patternIdx] > 0xFF || pattern[patternIdx] == begin[i])
				++patternIdx;
			else
				patternIdx = 0;

			if (patternIdx == patternLen)
				return begin + i - patternLen + 1;
		}

		return nullptr;
	}

    // Determines which region of the process module to scan and passes it onto the pattern scanner.
	BYTE* ScanModuleInternal(const SHORT* pattern, uintptr_t patternLen, BYTE* begin, uintptr_t size)
	{
		BYTE* resultAddress = nullptr;
		MEMORY_BASIC_INFORMATION mbi{};

		for (BYTE* currByte = begin; currByte < begin + size; currByte += mbi.RegionSize)
		{
			if (!VirtualQuery(currByte, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
				continue;

			resultAddress = ScanPattern(pattern, patternLen, currByte, mbi.RegionSize);
			if (resultAddress != nullptr)
				break;
		}

		return resultAddress;
	}

    // Populates the module data for the given module name.
	void GetModuleData(const WCHAR* moduleName)
	{
		MODULEENTRY32 moduleEntry{};
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(GetCurrentProcess()));
		
		moduleEntry.dwSize = sizeof(moduleEntry);
		Module32First(hModule, &moduleEntry);
		do {
			if (!wcscmp(moduleEntry.szModule, moduleName))
			{
				CloseHandle(hModule);
				moduleBase = moduleEntry.modBaseAddr;
				moduleSize = moduleEntry.modBaseSize;
				break;
			}
		} while (Module32Next(hModule, &moduleEntry));
	}

public:
    MemoryTools(const WCHAR* moduleName)
	{
		GetModuleData(moduleName);
	}

	BYTE* GetStaticAddress(uintptr_t offset)
	{
		return reinterpret_cast<BYTE *>(moduleBase) + offset;
	}

	void Set(BYTE* writeAddress, const std::vector<BYTE>& newBytes)
	{
		MEMORY_BASIC_INFORMATION mbi{};
		if (!VirtualQuery(writeAddress, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
			return;

		DWORD oldProtect;
		if (!VirtualProtect(reinterpret_cast<LPVOID>(writeAddress), newBytes.size(), PAGE_READWRITE, &oldProtect))
			return;

		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(writeAddress), newBytes.data(), newBytes.size(), nullptr);
		VirtualProtect(reinterpret_cast<LPVOID>(writeAddress), newBytes.size(), oldProtect, &oldProtect);
	}

	BYTE* ResolvePointerChain(BYTE* baseAddress, const std::vector<int> offsets)
	{
		BYTE* retAddress = baseAddress;
		for(auto offset : offsets)
		{
			ReadProcessMemory(GetCurrentProcess(), retAddress, &retAddress, sizeof(retAddress), 0);
			if (retAddress == nullptr)
				break;
			retAddress += offset;
		}

		return reinterpret_cast<uintptr_t>(retAddress) < reinterpret_cast<uintptr_t>(moduleBase) ? nullptr : retAddress;
	}

    // Performs a pattern scan on a given process module. Returns nullptr if not found.
	BYTE* Scan(const SHORT* pattern, uintptr_t patternLen, uintptr_t patternOffset)
	{
		BYTE* result = ScanModuleInternal(pattern, patternLen, reinterpret_cast<BYTE*>(moduleBase), moduleSize);

		return result ? result + patternOffset : nullptr;
	}

    // Performs a region scan between two given addresses for a given module. Returns nullptr if not found.
	BYTE* RegionScan(const SHORT* pattern, uintptr_t patternLen, uintptr_t patternOffset, uintptr_t offset, uintptr_t size)
	{
		BYTE* result = ScanModuleInternal(pattern, patternLen, reinterpret_cast<BYTE*>(moduleBase) + offset, size) + patternOffset;

		return result ? result + patternOffset : nullptr;
	}
};