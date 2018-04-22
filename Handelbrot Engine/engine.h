#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Complex.h"
#include "input.h"

// For graphics
struct Pixmap
{
	uint8_t *pixels;
	uint16_t width, height;
};

struct MS_Engine
{
	// Graphics
	Pixmap map;
	sf::Texture msTexture;
	sf::Sprite msSprite;
	double zoom;
	sf::Vector2f cameraPos;

	// Other
	Input input;
	bool runOnGPU = false;
	float defaultRadious = 2.2f;
	uint32_t maxIterations = 500;
};

int MS_init(MS_Engine *engine, int pixelWidth, int pixelHeight, bool runOnGPU = false);
void MS_update(MS_Engine *engine);
void MS_draw(MS_Engine *engine, sf::RenderWindow *window);
void MS_clean(MS_Engine *engine);

#endif
