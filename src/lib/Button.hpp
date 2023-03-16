#pragma once
#include <SFML/Graphics.hpp>

namespace my
{
class Button
{
private:
	std::function<void()> onClick;

public:
	bool isActive;
	sf::RectangleShape button;
	sf::Text text;
	Button(sf::RenderWindow& window, sf::Color fillColor, int length, int height, int x, int y);
	void setText(sf::RenderWindow& window, sf::Color color, std::string txt, sf::Font font, int chSize);
	void setOnClick(std::function<void()> onClick);
	std::function<void()> getOnClick();
};
}