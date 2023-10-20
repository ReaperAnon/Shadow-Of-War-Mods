#pragma once

#include <Windows.h>
#include <thread>
#include <vector>
#include <functional>

template<typename KEYTYPE>
class GameKey
{
private:
    bool isPressed = false;

public:
    KEYTYPE ModKey;
    KEYTYPE FirstKey;
    KEYTYPE SecondKey;
    void* PressArgs = nullptr;
    void* AltPressArgs = nullptr;
    void* ReleaseArgs = nullptr;
    void* AltReleaseArgs = nullptr;
    std::function<void(void*)> PressAction = nullptr;
    std::function<void(void*)> AltPressAction = nullptr;
    std::function<void(void*)> ReleaseAction = nullptr;
    std::function<void(void*)> AltReleaseAction = nullptr;

	void RemapKeys(KEYTYPE firstKey) { FirstKey = firstKey; }
	void RemapKeys(KEYTYPE firstKey, KEYTYPE secondKey) { FirstKey = firstKey; SecondKey = secondKey; }
	void RemapKeys(KEYTYPE firstKey, KEYTYPE secondKey, KEYTYPE modKey) { FirstKey = firstKey; SecondKey = secondKey; ModKey = modKey; }

	GameKey(KEYTYPE firstKey) : FirstKey(firstKey) {}
	GameKey(KEYTYPE firstKey, KEYTYPE secondKey) : FirstKey(firstKey), SecondKey(secondKey) {}
	GameKey(KEYTYPE firstKey, KEYTYPE secondKey, KEYTYPE modKey) : FirstKey(firstKey), SecondKey(secondKey), ModKey(modKey) {}
	~GameKey() { delete PressArgs; delete AltPressArgs; delete ReleaseArgs; delete AltReleaseArgs; }

	bool IsPressed() { return isPressed; }

	void SetPressed(bool state) { isPressed = state; }
};
	

template<typename KEYTYPE>
class InputProcessor
{
public:
    std::vector<bool> KeyBlocks;
    std::vector<GameKey<KEYTYPE>*> GameKeys;

private:
    bool isInputLoaded = false;

    bool ShouldProcessInputs();
    bool IsActionPressed(GameKey<KEYTYPE>* gameKey);
    bool IsModifierPressed(GameKey<KEYTYPE>* gameKey);
    bool IsActionBlocked(GameKey<KEYTYPE>* gameKey);
    void SetActionBlock(GameKey<KEYTYPE>* gameKey, bool state);

	void InputProcessThread()
	{
		while (isInputLoaded)
		{
			Sleep(50);
			ProcessKeyEvents();
		}
	}

	void ProcessInputs(std::vector<GameKey<KEYTYPE>*>* inputArray)
	{
		for (auto gameKey : *inputArray)
		{
			if (IsActionPressed(gameKey))
			{
				if (IsActionBlocked(gameKey))
					continue;

				SetActionBlock(gameKey, true);
				if (gameKey->IsPressed())
					continue;

				gameKey->SetPressed(true);
				if (gameKey->AltPressAction && IsModifierPressed(gameKey))
					gameKey->AltPressAction(gameKey->AltPressArgs);
				else
					gameKey->PressAction(gameKey->PressArgs);
			}
			else if (gameKey->IsPressed())
			{
				gameKey->SetPressed(false);
				SetActionBlock(gameKey, false);

				if (gameKey->AltReleaseAction && IsModifierPressed(gameKey))
					gameKey->AltReleaseAction(gameKey->AltReleaseArgs);
				else if (gameKey->ReleaseAction)
					gameKey->ReleaseAction(gameKey->ReleaseArgs);
			}
		}
	}

	void ProcessKeyEvents()
	{
		if (!ShouldProcessInputs())
			return;

		ProcessInputs(&GameKeys);
	}

public:
	void StartInputProcessing()
	{
		isInputLoaded = true;
		std::thread(&InputProcessor<KEYTYPE>::InputProcessThread, this).detach();
	}

	void StopInputProcessing()
	{
		isInputLoaded = false;
	}

	// Takes regular Direct Input key params.
	void PressKey(std::vector<WPARAM>* keysToPress)
	{
		for (auto key : *keysToPress)
		{
			if (key == 0x1)
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			else if (key == 0x2)
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			else
				keybd_event(key, MapVirtualKey(key, 0), 0, 0);
		}
	}

    // Takes regular Direct Input key params.
	void ReleaseKey(std::vector<WPARAM>* keysToRelease)
	{
		for (auto key : *keysToRelease)
		{
			if (key == 0x1)
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			else if (key == 0x2)
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			else
				keybd_event(key, MapVirtualKey(key, 0), 0, 0);
		}
	}
};