#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define MODLOADER_NO_MENU

#include <Windows.h>
#include <thread>
#include <modloaderapi.h>
#include <memorytool.h>
#include <MinHook.h>

#pragma comment(lib, "libMinHook.x64.lib")