#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
class ColorSelector
{
public:
	static sf::Color backgroundColor;
	static sf::Color textColor;
	static sf::Color buttonColor;
	static sf::Color activeColor;

	static std::vector<sf::Color> colors;
	static std::vector<Button> colorButtons;

	static void displayMenu(sf::RenderWindow& window);
};
}