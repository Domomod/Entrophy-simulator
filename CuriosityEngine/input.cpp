#include "input.h"
#include <SDL2/SDL.h>
#include "sdl_backend.h"

#include <iostream>
#include <windows.h>

const static int NUM_KEYS = 512;
const static int NUM_MOUSEBUTTONS = 256;

static SDL_Event event;

static int mouseX = 0;
static int mouseY = 0;

static bool inputs[NUM_KEYS];
static bool downKeys[NUM_KEYS];
static bool upKeys[NUM_KEYS];

static bool mouseInput[NUM_MOUSEBUTTONS];
static bool downMouse[NUM_MOUSEBUTTONS];
static bool upMouse[NUM_MOUSEBUTTONS];
static bool downWheel;
static bool upWheel;

void Input::update()
{
	upWheel = false;
	downWheel = false;
	for(int i = 0; i < NUM_MOUSEBUTTONS; i++)
	{
		downMouse[i] = false;
		upMouse[i] = false;
	}

	for(int i = 0; i < NUM_KEYS; i++)
	{
		downKeys[i] = false;
		upKeys[i] = false;
	}

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			SDLSetIsCloseRequested(true);

		if(event.type == SDL_MOUSEMOTION)
		{
			mouseX = event.motion.x;
			mouseY = event.motion.y;
		}

		if(event.type == SDL_KEYDOWN)
		{
			int value = event.key.keysym.scancode;

			inputs[value] = true;
			downKeys[value] = true;
		}
		if(event.type == SDL_KEYUP)
		{
			int value = event.key.keysym.scancode;

			inputs[value] = false;
			upKeys[value] = true;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = event.button.button;

			mouseInput[value] = true;
			downMouse[value] = true;
		}
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			int value = event.button.button;

			mouseInput[value] = false;
			upMouse[value] = true;
		}
		if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0)
			{
				upWheel = true;
				downWheel = false;
			}
			else if (event.wheel.y < 0)
			{
				downWheel = true;
				upWheel = false;
			}
		}
	}
}

bool Input::getKey(int keyCode)
{
	return inputs[keyCode];
}

bool Input::getKeyDown(int keyCode)
{
	return downKeys[keyCode];
}

bool Input::getKeyUp(int keyCode)
{
	return upKeys[keyCode];
}

bool Input::getMouse(int button)
{
	return mouseInput[button];
}

bool Input::getMouseDown(int button)
{
	return downMouse[button];
}

bool Input::getMouseUp(int button)
{
	return upMouse[button];
}

bool Input::getWheelUp()
{
	return upWheel;
}

bool Input::getWheelDown() 
{
	return downWheel;
}

glm::vec2 Input::getMousePosition()
{
	glm::vec2 res((float)mouseX,(float)mouseY);
	return res;
}

void Input::setCursor(bool visible)
{
	if(visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::setMousePosition(glm::vec2 pos)
{
	SDLSetMousePosition((int)pos.x, (int)pos.y);
}
