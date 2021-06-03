#pragma once
#include <Windows.h>
#include <windef.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

#include <SDL.h>
#include <map>
#include "Singleton.h"
#include "Command.h"


enum class ControllerButton
{
	ButtonA = XINPUT_GAMEPAD_A,
	ButtonB = XINPUT_GAMEPAD_B,
	ButtonX = XINPUT_GAMEPAD_X,
	ButtonY = XINPUT_GAMEPAD_Y,

	DPadUp = XINPUT_GAMEPAD_DPAD_UP,
	DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
	DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
	DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,

	ShoulderRight = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	ShoulderLeft = XINPUT_GAMEPAD_LEFT_SHOULDER,

	ThumbRight = XINPUT_GAMEPAD_RIGHT_THUMB,
	ThumbLeft = XINPUT_GAMEPAD_LEFT_THUMB,
};

enum class InputType
{
	pressed,
	held,
	released
};

struct ButtonCommands
{
	explicit ButtonCommands(Command* pressed, Command* held, Command* released)
	{
		pressedCommand = pressed;
		heldCommand = held;
		releasedCommand = released;
	}
	Command* pressedCommand;
	Command* heldCommand;
	Command* releasedCommand;
};

class InputManager final : public Singleton<InputManager>
{
public:
	virtual ~InputManager();
	
	bool ProcessInput();
	bool IsPressed(ControllerButton button);
	bool IsReleased(ControllerButton button);
	bool IsHeld(ControllerButton button);

	void AddCommand(ControllerButton button, InputType inputType, Command* command);
	void AddCommand(SDL_Scancode SDLButton, InputType inputType, Command* command);

	void Destroy();
private:
	friend class Singleton<InputManager>;
	InputManager() = default;
	
	XINPUT_STATE m_CurrentState{};

	std::map<ControllerButton, bool> m_PressedButtons;
	std::map<ControllerButton, ButtonCommands*> m_ControllerCommands;
	std::map<SDL_Scancode, ButtonCommands*> m_KeyboardCommands;
};