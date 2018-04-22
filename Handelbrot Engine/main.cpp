#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>

#include "engine.h"

void loop(sf::RenderWindow *window, MS_Engine *engine);
void screenshot(MS_Engine *engine);

int main()
{
#ifdef _DEBUG
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Mandelbrot Engine - DEBUG");
#else
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Mandelbrot Engine", sf::Style::Fullscreen);
#endif

	// Engine setup
	MS_Engine engine;
	if (!MS_init(&engine, window.getSize().x, window.getSize().y))
	{
		printf("\nError trying to initialize the engine!\n");
		return -1;
	}

	loop(&window, &engine);

	return 0;
}

void loop(sf::RenderWindow *window, MS_Engine *engine)
{
	bool cursor = false;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			// Any relavent input
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				engine->input.triggerInput = true;
				break;
			}

			Input_update(&engine->input, &event);
		}

		// Updating the set only on input
		if (engine->input.triggerInput)
		{
			// Cursor flipping
			if (Input_isKeyPressed(&engine->input, sf::Keyboard::H))
			{
				window->setMouseCursorVisible(cursor);
				cursor = !cursor;
			}

			MS_update(engine);

			// Screenshot
			if (Input_isKeyPressed(&engine->input, sf::Keyboard::P))
			{
				screenshot(engine);
			}

			engine->input.triggerInput = false;
		}

		window->clear(sf::Color(0, 0, 0, 0));
		MS_draw(engine, window);
		window->display();
	}
}

void screenshot(MS_Engine *engine)
{
	sf::Image image;
	image.create(engine->map.width, engine->map.height, engine->map.pixels);

	// File will save to current date and time
	time_t t = time(NULL);
	tm *Time = localtime(&t);
	image.saveToFile("Handelbrot_Set_" + std::to_string(Time->tm_mday) 
									   + "_" + std::to_string(Time->tm_mon + 1) 
									   + "_" + std::to_string(Time->tm_year + 1900) 
									   + ";" + std::to_string(Time->tm_hour) + "h" 
									   + "-" + std::to_string(Time->tm_min) + "min"
									   + "-" + std::to_string(Time->tm_sec) + "s"
									   + ".png");
}