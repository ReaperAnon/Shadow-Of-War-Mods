#pragma once

#include <string>
#include <vector>

#define MODLOADERAPI extern "C" void __declspec(dllexport)

namespace ModLoader
{
	class PluginAPI
	{
	public:
		/** Register a plugin for the mod loader. When not registered, the plugin name and short name will be the loaded dll's file name without the extension, with the version at 1.0.0 and a default description.

		@param pluginName:			The name of the plugin displayed in the mod configuration menu.
		@param shortName:			A short identifier used for logging.
		@param pluginVersion:		The current version of the plugin in an { x, x, x } format.
		@param pluginDescription:	A description of the plugin and potentially what it does. Displayed in the description tab in the mod configuration menu.
		*/
		virtual void RegisterPlugin(const std::string& pluginName, const std::string& shortName, const std::vector<int>& pluginVersion = {}, const std::string& pluginDescription = "") = 0;
	};
	
	class LogAPI
	{
	private:
		static inline LogAPI* singleton = nullptr;

	public:
		/** Returns the loging API singleton which can be used to call its functions.

		@return LogAPI*: A pointer to an instance of the logger. Null pointer if LogAPI::Init was not called first.
		*/
		static LogAPI* GetSingleton() {
			return singleton;
		}

		/** Initializes the logging API singleton for later use.

		@param *logAPI: A pointer to the logging API passed in the OnRegisterLogAPI event function.
		*/
		static void Init(LogAPI* logAPI) {
			singleton = logAPI;
		}

		/** Creates a marked log entry with formatting for the current plugin. For formatting information check the "printf" function's usage.

		@param *fmt: A pointer to a regular C-style string (optionally with formatting).
		@param ...: Additional arguments to be inserted into the formatted string. Can be left empty.
		*/
		virtual void Log(const char* fmt, ...) = 0;

		/** Creates a marked log entry with formatting for the current plugin with an additional ERROR message. For formatting information check the "printf" function's usage.

		@param *fmt: A pointer to a regular C-style string (optionally with formatting).
		@param ...: Additional arguments to be inserted into the formatted string. Can be left empty.
		*/
		virtual void LogError(const char* fmt, ...) = 0;
	};
}

#ifndef MODLOADER_NO_MENU
	#include <imgui.h>
	#include <functional>

	namespace ModLoader
	{
		class MenuAPI
		{
		private:
			static inline MenuAPI* singleton = nullptr;

			virtual ImGuiContext* GetContext() const = 0;

			virtual void GetAllocators(ImGuiMemAllocFunc* allocFunc, ImGuiMemFreeFunc* freeFunc, void** userData) const = 0;

		public:
			/** Returns the menu API singleton which can be used to call its functions.

			@return MenuAPI*: A pointer to an instance of the logger. Null pointer if MenuAPI::Init was not called first.
			*/
			static MenuAPI* GetSingleton() {
				return singleton;
			}

			/** Initializes the menu API singleton for later use.

			@param *menuAPI: A pointer to the menu API passed in the OnRegisterMenuAPI event function.
			*/
			static void Init(MenuAPI* menuAPI) {
				ImGui::SetCurrentContext(menuAPI->GetContext());

				singleton = menuAPI;
				void* userData; ImGuiMemFreeFunc freeFunc; ImGuiMemAllocFunc allocFunc;
				menuAPI->GetAllocators(&allocFunc, &freeFunc, &userData);
				ImGui::SetAllocatorFunctions(allocFunc, freeFunc, userData);
			}

			/** Registers a menu tab in the mod configuration menu's plugin entry. It's possible to register multiple consequent tabs.

			@param drawFunction: A pointer to a function containing ImGui functions to create the actual menu. The menu items created here will be placed under a named tab in the options menu.
			@param defaultFunction: A pointer to a function which sets the options in this sub-menu to their default values. Will be called when the premade "Default" button is pressed in the menu.
			@param saveFunction: A pointer to a function which saves the options in this sub-menu to a file. Will be called when the premade "Save" button is pressed or when the settings are autosaved.
			@param menuName: The name the tab should have under which the options menu is drawn. Will be "Settings", "Extra Settings", "Extra Settings 2" and so on if left empty.
			*/
			virtual void RegisterMenuEntry(std::function<void()> drawFunction, std::function<void()> defaultFunction = nullptr, std::function<void()> saveFunction = nullptr, std::string menuName = "") = 0;

			/** Registers a drawing function of any kind for custom menus or UI elements. It will be called between ImGui::NewFrame and ImGui::EndFrame inside the Present function hook.

			@param drawFunction: A pointer to a function containing ImGui functions to be drawn on the screen.
			*/
			virtual void RegisterDrawCallEntry(std::function<void()> drawFunction) = 0;

			/** Displays a permanently focused Notice menu on the screen with a message. Useful if an option would require restarting the game.

			@param *noticeText: A pointer to a regular C-style string.
			*/
			virtual void DisplayNotice(const char* noticeText) = 0;

			/** Returns the state of the mod configuration menu.

			@return bool: Returns true if the menu is open, false if it's not.
			*/
			virtual bool IsMenuOpen() const = 0;

			/** Returns the state of the debug option found in the mod configuration menu. Useful for debug menus that you don't want to normally be visible.

			@return bool: Returns true if the debug mode option is on, false if it's off.
			*/
			virtual bool IsDebugActive() const = 0;

			/** Returns whether the game is currently paused or not, be it from a SetGamePaused call or because the mod menu is currently open.

			@return bool: True if the game is paused, false if not.
			*/
			virtual bool IsGamePaused() const = 0;

			/** Pauses or unpauses the game. If the mod menu is open the game will remain paused until the menu is closed, even if the option is set to false.

			@param state: True is paused and false is unpaused.
			*/
			virtual void SetGamePaused(bool state) = 0;
		};
	}
#endif

/** Event function called by the mod loader when the logging API is registered. First function to get called after a dll is loaded.

@param LogAPI*: A pointer to the created instance of the logging API. Can be used directly or to initialize the plugin's instance of it with LogAPI::Init.
*/
MODLOADERAPI OnRegisterLogAPI(ModLoader::LogAPI*);
#ifndef MODLOADER_NO_MENU
	/** Event function called by the mod loader when the menu API is registered. Second function to get called after a dll is loaded.
	*	Can be disabled by defining the "MODLOADER_NO_MENU" directive which removes the ImGui dependency.

	@param MenuAPI*: A pointer to the created instance of the menu API. Can be used directly or to initialize the plugin's instance of it with MenuAPI::Init.
	*/
	MODLOADERAPI OnRegisterMenuAPI(ModLoader::MenuAPI*);
#endif
/** Event function called by the mod loader when the plugin API is registered and it's finished loading. Third function to get called after a dll is loaded.

@param PluginAPI*: A pointer to the created instance of the plugin API. Can be used to register a plugin with the "RegisterPlugin" function.
*/
MODLOADERAPI OnPluginLoad(ModLoader::PluginAPI*);
/* Event function called by the mod loader when the mod is unloaded for any reason. Should be used to turn off everything in the mod and set it back to how it was in the base game, as the mod may be initialized again later.
*/
MODLOADERAPI OnPluginUnload();