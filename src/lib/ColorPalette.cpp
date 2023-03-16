#include "ColorPalette.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "Font.hpp"
#include "SavingImage.hpp"
#include "Screen.hpp"

namespace my
{
std::vector<sf::Color> ColorPalette::backgroundColors = { sf::Color(44, 62, 80), sf::Color(111, 30, 81), sf::Color(247, 159, 31), sf::Color(59, 59, 59), sf::Color(34, 112, 147), sf::Color(153, 128, 250), sf::Color(0, 148, 50), sf::Color(206, 214, 224), sf::Color(0, 128, 128), sf::Color(212, 78, 40), sf::Color(245, 245, 220), sf::Color(39, 60, 117), sf::Color(199, 236, 238), sf::Color(255, 71, 87), sf::Color(116, 125, 140) };
std::vector<sf::Color> ColorPalette::textColors = { sf::Color(236, 240, 241), sf::Color(153, 128, 250), sf::Color(255, 195, 18), sf::Color(28, 28, 28), sf::Color(255, 177, 66), sf::Color(217, 128, 250), sf::Color(196, 229, 56), sf::Color(236, 204, 104), sf::Color(255, 0, 255), sf::Color(36, 32, 33), sf::Color(92, 64, 51), sf::Color(220, 221, 225), sf::Color(223, 249, 251), sf::Color(255, 165, 2), sf::Color(164, 176, 190) };
std::vector<sf::Color> ColorPalette::buttonColors = { sf::Color(22, 160, 133), sf::Color(181, 52, 113), sf::Color(238, 90, 36), sf::Color(255, 182, 6), sf::Color(52, 172, 224), sf::Color(87, 88, 187), sf::Color(0, 98, 102), sf::Color(223, 228, 234), sf::Color(255, 215, 0), sf::Color(44, 188, 178), sf::Color(139, 69, 19), sf::Color(245, 246, 250), sf::Color(149, 175, 192), sf::Color(255, 99, 72), sf::Color(47, 53, 66) };

void ColorPalette::displayMenu(sf::RenderWindow& window, sf::Event& event)
{
	window.clear(ColorSelector::backgroundColor);
	displayColorOptions(window, event);
	backToMainMenu(window, event);
	window.display();
}
void ColorPalette::displayColorOptions(sf::RenderWindow& window, sf::Event& event)
{
	for (int i = 0; i < backgroundColors.size(); i++)
	{
		sf::Color currentBackgroundColor = backgroundColors[i];
		sf::Color currentButtonColor = buttonColors[i];
		sf::Color currentTextColor = textColors[i];
		Button colorButton(window, currentBackgroundColor, 50, 50, (i % 5 + 3) * 100, (i / 5 + 4) * 100);
		colorButton.button.setOutlineColor(sf::Color::White);

		if (currentBackgroundColor == ColorSelector::backgroundColor) // the button with the same color will be highlighted
			colorButton.button.setOutlineThickness(.2f);

		if (colorButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::MouseButtonPressed)
		{
			ColorSelector::backgroundColor = currentBackgroundColor;
			ColorSelector::buttonColor = currentButtonColor;
			ColorSelector::textColor = currentTextColor;

			SavingImage::saveColorPalette(i);
		}

		window.draw(colorButton.button);
	}
}
void ColorPalette::backToMainMenu(sf::RenderWindow& window, sf::Event& event)
{
	Button colorButton(window, ColorSelector::buttonColor, 200, 50, 850, 900);
	colorButton.setText(window, ColorSelector::textColor, "BACK   ", Font::font, 24);
	if (colorButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::MouseButtonPressed)
	{
		Screen::goToScreen(ScreenType::StartMenu);
	}
	//window.display(colorButton)
}

}