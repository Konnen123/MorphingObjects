#include "AllButtons.hpp"
#include "Button.hpp"

namespace my
{
std::vector<Button> AllButtons::buttons = std::vector<Button>();

void AllButtons::handleEvents(sf::RenderWindow& window, sf::Event& ev)
{
	for (auto& myButton : buttons)
		if (myButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			if (ev.type == sf::Event::MouseButtonPressed)
				if (ev.mouseButton.button == sf::Mouse::Left)
				{
					auto func = myButton.getOnClick();
					if (myButton.isActive)
						func();
				}
}
}