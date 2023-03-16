#include "Button.hpp"
#include "AllButtons.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
Button::Button(sf::RenderWindow& window, sf::Color fillColor, int length, int height, int x, int y)
{
	isActive = true;

	button.setSize(sf::Vector2f(length, height));
	button.setOrigin(length / 2, height / 2);
	button.setPosition(x, y);
	button.setFillColor(fillColor);

	window.draw(button);
}

void Button::setText(sf::RenderWindow& window, sf::Color color, std::string txt, sf::Font font, int chSize)
{
	text.setString(txt);
	text.setFont(font);
	text.setFillColor(color);

	text.setCharacterSize(chSize);

	float xPos = (button.getPosition().x + button.getGlobalBounds().width / 10) - (text.getGlobalBounds().width / 1.6f);
	float yPos = (button.getPosition().y + button.getGlobalBounds().height / 10) - (text.getGlobalBounds().height / .9f);

	text.setPosition({ xPos, yPos });

	window.draw(text);
}

void Button::setOnClick(std::function<void()> onClick)
{
	this->onClick = onClick;
	my::AllButtons::buttons.push_back(*this);
}

std::function<void()> Button::getOnClick()
{
	return onClick;
}
}