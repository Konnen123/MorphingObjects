#include "lib/AllButtons.hpp"
#include "lib/Button.hpp"
#include "lib/ColorSelector.hpp"
#include "lib/Font.hpp"
#include "lib/SavingImage.hpp"
#include "lib/Screen.hpp"
#include "lib/ShapeSelector.hpp"
#include "lib/Sound.hpp"
#include "lib/StartMenu.hpp"
#include "lib/Triangulation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
	unsigned int width = 1000;
	unsigned int height = 1000;

	my::Font::load();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Morphing - Proiect IP", sf::Style::Default, settings);

	my::SavingImage::loadColorPalette();

	window.setFramerateLimit(240);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			my::Screen::screenHandler(window, event);
			my::AllButtons::handleEvents(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

	}
	return 0;
}
