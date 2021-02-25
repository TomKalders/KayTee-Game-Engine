#include "MiniginPCH.h"
#include "InputManager.h"
#include <iostream>
#include <SDL.h>

dae::InputManager::~InputManager()
{
	for (auto button : m_ButtonCommands)
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

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
	
	for (auto& button : m_ButtonCommands)
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
	if (m_ButtonCommands.find(button) == m_ButtonCommands.end())
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
		m_ButtonCommands[button] = buttonCommands;
	}
	else
	{
		auto pCommands = m_ButtonCommands[button];

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
