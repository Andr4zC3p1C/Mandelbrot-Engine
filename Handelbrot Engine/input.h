#ifndef INPUT_H
#define INPUT_H

#include <SFML\Graphics.hpp>

struct Input
{
	bool triggerInput = false;
	bool keysPressed[sf::Keyboard::KeyCount];
	bool p_keysPressed[sf::Keyboard::KeyCount];

	Input();
};

void Input_update(Input *input, sf::Event *event);
bool Input_isKeyPressed(Input *input, int key);
bool Input_isKeyDown(Input *input, int key);

#endif
