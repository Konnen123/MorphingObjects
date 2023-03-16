#include "MenuSelector.hpp"
#include "AllButtons.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "FirstImage.hpp"
#include "Font.hpp"
#include "ShapeSelector.hpp"

namespace my
{
MenuSelectorType MenuSelector::activeMenuSelector = MenuSelectorType::ShapeSelector;

std::string footerText;

void MenuSelector::toggleMenuSelector()
{

	switch (activeMenuSelector)
	{
		case MenuSelectorType::ShapeSelector:
			activeMenuSelector = MenuSelectorType::ColorSelector;
			break;
		case MenuSelectorType::ColorSelector:
			activeMenuSelector = MenuSelectorType::ShapeSelector;
			break;
		default:
			break;
	}
}

void MenuSelector::drawButtons(sf::RenderWindow& window)
{
	unsigned int length = 75, height = 50, fontSize = 18;
	Button previousButton(window, ColorSelector::buttonColor, length, height, 50, window.getSize().y - 100);
	previousButton.setText(window, ColorSelector::textColor, " <   ", Font::font, fontSize);
	//previousButton.setOnClick([]() { toggleMenuSelector(); }); codul pentru setonclick nu este bun deoarece intra de peste 100 de ori in functie cand se da click
	if (previousButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		toggleMenuSelector();

	Button nextButton(window, ColorSelector::buttonColor, length, height, window.getSize().y - 50, window.getSize().y - 100);
	nextButton.setText(window, ColorSelector::textColor, " >  ", Font::font, fontSize);
	//nextButton.setOnClick([]() { toggleMenuSelector(); });
	if (nextButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		toggleMenuSelector();
}

void MenuSelector::disableShapeButtons()
{
	for (Button& button : AllButtons::buttons)
		if (button.text.getString() == "RECTANGLE" || button.text.getString() == "CIRCLE  " || button.text.getString() == "TRIANGLE" || button.text.getString() == "POLYGON")
			button.isActive = false;
}

void MenuSelector::disableColorButtons()
{
	for (Button& button : ColorSelector::colorButtons)
		if (button.text.getString() == "COLOR")
			button.isActive = false;
}

void MenuSelector::enableShapeButtons()
{
	for (Button& button : AllButtons::buttons)
		if (button.text.getString() == "RECTANGLE" || button.text.getString() == "CIRCLE  " || button.text.getString() == "TRIANGLE" || button.text.getString() == "POLYGON")
			button.isActive = true;
}

void MenuSelector::enableColorButtons()
{
	for (Button& button : ColorSelector::colorButtons)
		if (button.text.getString() == "COLOR")
			button.isActive = true;
}

void MenuSelector::displayMenu(sf::RenderWindow& window)
{
	switch (activeMenuSelector)
	{
		case MenuSelectorType::ShapeSelector:
			ShapeSelector::displayMenu(window);
			changeFooterText();
			FirstImage::displayText(window, footerText);
			disableColorButtons();
			enableShapeButtons();
			break;
		case MenuSelectorType::ColorSelector:
			ColorSelector::displayMenu(window);
			disableShapeButtons();
			enableColorButtons();
			break;

		default:
			break;
	}
}
void MenuSelector::changeFooterText()
{
	switch (ShapeSelector::movingShape)
	{
		case ShapeType::Rectangle:
			footerText = "Rotate-R | Increase Size-Q | Decrease Size-E | Save-Enter";
			break;
		case ShapeType::Circle:
			footerText = "Increase Size-Q | Decrease Size-E | Save-Enter";
			break;
		case ShapeType::Triangle:
			footerText = "Rotate-R | Increase Size-Q | Decrease Size-E | Save-Enter";
			break;
		case ShapeType::Polygon:
			footerText = "Connect All Points-U | Save-Enter";
			break;
		default:
			if (ShapeSelector::allShapeTypes.size() == 0)
			{
				footerText = "First Image";
				break;
			}
			footerText = "Press 2 To Go To Second Image";
			break;
	}
}
}