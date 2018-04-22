#include <stdlib.h>

#include "engine.h"
#include "mandelbrot_cpu.h"

int MS_init(MS_Engine *engine, int pixelWidth, int pixelHeight, bool runOnGPU)
{
	// Pixel Map
	engine->map.pixels = (uint8_t*) malloc(pixelWidth * pixelHeight * 4);
	if (!engine->map.pixels)
	{
		printf("Could not allocate %d Bytes of memory for pixelmap!\n", pixelWidth * pixelHeight * 4);
		return 0;
	}
	memset(engine->map.pixels, 0, pixelWidth * pixelHeight * 4);

	if (!engine->msTexture.create(pixelWidth, pixelHeight))
	{
		printf("Could not create the main texture!\n");
		return 0;
	}
	engine->msTexture.setSmooth(true);	// IMPORTANT!
	engine->msTexture.update(engine->map.pixels);
	engine->msSprite.setTexture(engine->msTexture);
	engine->cameraPos.x = 0;
	engine->cameraPos.y = 0;

	// Other
	engine->zoom = 1.0f;
	engine->runOnGPU = runOnGPU;
	engine->map.width = pixelWidth;
	engine->map.height = pixelHeight;

	return 1;
}

void MS_update(MS_Engine *engine)
{
	if (Input_isKeyPressed(&engine->input, sf::Keyboard::A))
	{
		engine->cameraPos.x = sf::Mouse::getPosition().x;
		engine->cameraPos.y = sf::Mouse::getPosition().y;
	}

	// TODO: Consider further optimization!
	static Complex cpx;
	for (uint16_t y = 0; y < engine->map.height; y++)
	{
		for(uint16_t x = 0; x < engine->map.width; x++)
		{
			cpx.re = x;
			cpx.im = y;
			MS_convertToComplexPlane(&cpx, engine);

			MS_updatePixel(x, y, &cpx, engine);
		}
	}
	
#ifdef _DEBUG
	int x = engine->map.width / 2.0;
	int y = engine->map.height / 2.0;
	printf("%d\n", engine->map.pixels[x * 4 + 3 + engine->map.width * y * 4]);
#endif		

	engine->msTexture.update(engine->map.pixels);
}

void MS_draw(MS_Engine *engine, sf::RenderWindow *window)
{
	window->draw(engine->msSprite);
}

void MS_clean(MS_Engine *engine)
{
	free(engine->map.pixels);
}