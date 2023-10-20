#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <Windows.h>
#include <thread>
#include <imgui_hotkey.h>
#include <imgui.h>
#include <string>
#include <input_processing.h>
#include <modloaderapi.h>
#include <SimpleIni.h>
#include <memorytool.h>
#include <MinHook.h>

#pragma comment(lib, "libMinHook.x64.lib")