#include "MiniginPCH.h"
#include "InputManager.h"
#include <iostream>

dae::InputManager::~InputManager()
{
	Destroy();
}

bool dae::InputManager::ProcessInput()
{

	//// todo: read the input
	RtlZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			for (auto keyboardButton : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == keyboardButton.first)
				{
					Command* command = keyboardButton.second->pressedCommand;
					if (command)
						keyboardButton.second->pressedCommand->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (auto keyboardButton : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == keyboardButton.first)
				{
					Command* command = keyboardButton.second->releasedCommand;
					if (command)
						keyboardButton.second->releasedCommand->Execute();
				}
			}
		}

		const Uint8* state = SDL_GetKeyboardState(nullptr);
		for (auto keyboardButton : m_KeyboardCommands)
		{
			if (state[keyboardButton.first])
			{
				Command* command = keyboardButton.second->heldCommand;
				if (command)
					command->Execute();
			}
		}
	}

	
	for (auto& button : m_ControllerCommands)
	{
		if (IsPressed(button.first))
		{
			Command* command = button.second->pressedCommand;
			if (command)
				command->Execute();
		}
		if (IsHeld(button.first))
		{
			Command* command = button.second->heldCommand;
			if (command)
				command->Execute();
		}
		if (IsReleased(button.first))
		{
			Command* command = button.second->releasedCommand;
			if (command)
				command->Execute();
		}
	}

	UNREFERENCED_PARAMETER(result);
	//if (result == ERROR_SUCCESS)
	//{

	//}
	//else
	//{
	//	std::cout << "Controller Not Found!";
	//}
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button)
{
	if (m_CurrentState.Gamepad.wButtons & int(button))
	{
		if (!m_PressedButtons[button])
		{
			m_PressedButtons[button] = true;
			return true;
		}
	}

	return false;
}

bool dae::InputManager::IsReleased(ControllerButton button)
{
	if (!(m_CurrentState.Gamepad.wButtons & int(button)))
	{
		if (m_PressedButtons[button])
		{
			m_PressedButtons[button] = false;
			return true;
		}
	}

	return false;
}

bool dae::InputManager::IsHeld(ControllerButton button)
{
	return m_PressedButtons[button];
}

void dae::InputManager::AddCommand(ControllerButton button, InputType inputType, Command* command)
{
	if (m_ControllerCommands.find(button) == m_ControllerCommands.end())
	{
		Command* pressed = nullptr;
		Command* held = nullptr;
		Command* released = nullptr;

		switch (inputType)
		{
		case InputType::pressed:
			pressed = command;
			break;
		case InputType::held:
			held = command;
			break;
		case InputType::released:
			released = command;
			break;
		}

		ButtonCommands* buttonCommands = new ButtonCommands(pressed, held, released);
		m_ControllerCommands[button] = buttonCommands;
	}
	else
	{
		auto pCommands = m_ControllerCommands[button];

		switch (inputType)
		{
		case InputType::pressed:
			if (pCommands->pressedCommand)
				delete pCommands->pressedCommand;

			pCommands->pressedCommand = command;
			break;
		case InputType::held:
			if (pCommands->heldCommand)
				delete pCommands->heldCommand;

			pCommands->heldCommand = command;
			break;
		case InputType::released:
			if (pCommands->releasedCommand)
				delete pCommands->releasedCommand;

			pCommands->releasedCommand = command;
			break;
		}
	}
}

void dae::InputManager::AddCommand(SDL_Scancode SDLButton, InputType inputType, Command* command)
{
	if (m_KeyboardCommands.find(SDLButton) == m_KeyboardCommands.end())
	{
		Command* pressed = nullptr;
		Command* held = nullptr;
		Command* released = nullptr;

		switch (inputType)
		{
		case InputType::pressed:
			pressed = command;
			break;
		case InputType::held:
			held = command;
			break;
		case InputType::released:
			released = command;
			break;
		}

		ButtonCommands* buttonCommands = new ButtonCommands(pressed, held, released);
		m_KeyboardCommands[SDLButton] = buttonCommands;
	}
	else
	{
		auto pCommands = m_KeyboardCommands[SDLButton];

		switch (inputType)
		{
		case InputType::pressed:
			if (pCommands->pressedCommand)
				delete pCommands->pressedCommand;

			pCommands->pressedCommand = command;
			break;
		case InputType::held:
			if (pCommands->heldCommand)
				delete pCommands->heldCommand;

			pCommands->heldCommand = command;
			break;
		case InputType::released:
			if (pCommands->releasedCommand)
				delete pCommands->releasedCommand;

			pCommands->releasedCommand = command;
			break;
		}
	}
}

void dae::InputManager::Destroy()
{
	for (auto button : m_ControllerCommands)
	{
		if (button.second->heldCommand)
			delete button.second->heldCommand;
		if (button.second->pressedCommand)
			delete button.second->pressedCommand;
		if (button.second->releasedCommand)
			delete button.second->releasedCommand;

		delete button.second;
	}

	for (auto button : m_KeyboardCommands)
	{
		if (button.second->heldCommand)
			delete button.second->heldCommand;
		if (button.second->pressedCommand)
			delete button.second->pressedCommand;
		if (button.second->releasedCommand)
			delete button.second->releasedCommand;

		delete button.second;
	}
}
