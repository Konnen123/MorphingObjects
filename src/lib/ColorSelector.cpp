#include "ColorSelector.hpp"
#include "Button.hpp"
#include "Font.hpp"

namespace my
{
sf::Color ColorSelector::backgroundColor = sf::Color(44, 62, 80);
sf::Color ColorSelector::textColor = sf::Color(236, 240, 241);
sf::Color ColorSelector::buttonColor = sf::Color(22, 160, 133);
sf::Color ColorSelector::activeColor = sf::Color(255, 255, 255);

std::vector<sf::Color> ColorSelector::colors = { sf::Color(0, 255, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 255), sf::Color(255, 0, 255), sf::Color(128, 128, 128), sf::Color(0, 128, 0), sf::Color(0, 255, 0), sf::Color(128, 0, 0), sf::Color(0, 0, 128), sf::Color(128, 128, 0), sf::Color(128, 0, 128), sf::Color(255, 0, 0), sf::Color(192, 192, 192), sf::Color(0, 128, 128), sf::Color(255, 255, 255), sf::Color(255, 255, 0) };
std::vector<Button> ColorSelector::colorButtons = std::vector<Button>();

void ColorSelector::displayMenu(sf::RenderWindow& window)
{
	unsigned int length = 50, height = 50, fontSize = 1;

	unsigned int x = 185, y = window.getSize().y - 135;
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		Button colorButton(window, colors[i], length, height, x, y);
		colorButton.setText(window, colors[i], "COLOR", Font::font, fontSize);
		colorButton.setOnClick([i]() { ColorSelector::activeColor = colors[i]; });
		colorButtons.push_back(colorButton);

		x += length + 40;
		if (x >= window.getSize().x - 150)
		{
			x = 185;
			y += height + 25;
		}
	}
}
}