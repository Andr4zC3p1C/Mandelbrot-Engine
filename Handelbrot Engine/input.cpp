#include "input.h"

Input::Input()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keysPressed[i] = false;
		p_keysPressed[i] = false;
	}
}

void Input_update(Input *input, sf::Event *event)
{
	switch (event->type)
	{
	case sf::Event::KeyPressed:
		input->keysPressed[event->key.code] = true;
		break;

	case sf::Event::KeyReleased:
		input->keysPressed[event->key.code] = false;
		input->p_keysPressed[event->key.code] = false;
		break;
	}
}

bool Input_isKeyPressed(Input *input, int key)
{
	bool returnValue = false;
	if (input->keysPressed[key] && !input->p_keysPressed[key])
		returnValue = true;

	if (returnValue)
		input->p_keysPressed[key] = true;

	return returnValue;
}

bool Input_isKeyDown(Input *input, int key)
{
	return input->keysPressed[key];
}