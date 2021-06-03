#pragma once
#include "SDL.h"

struct MovementControls
{
	SDL_Scancode LeftUp = SDL_SCANCODE_LEFT;
	SDL_Scancode RightUp = SDL_SCANCODE_UP;
	SDL_Scancode LeftDown = SDL_SCANCODE_DOWN;
	SDL_Scancode RightDown = SDL_SCANCODE_RIGHT;

	ControllerButton ControllerLeftUp = ControllerButton::DPadLeft;
	ControllerButton ControllerRightUp = ControllerButton::DPadUp;
	ControllerButton ControllerLeftDown = ControllerButton::DPadDown;
	ControllerButton ControllerRightDown = ControllerButton::DPadRight;

	int ControllerId = 0;
};

