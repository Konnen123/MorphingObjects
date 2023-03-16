#include "FirstImage.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "MenuSelector.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include <string>

namespace my
{
void FirstImage::display(sf::RenderWindow& window)
{
	window.clear(ColorSelector::backgroundColor);
	MenuSelector::displayMenu(window);
	DrawManager::drawShapes(window);
	MenuSelector::drawButtons(window);

	window.display();
}

void FirstImage::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	handleNextImage(window, event);
	ShapeSelector::handleShapeSelection(window, event);
	ShapeSelector::handlePolygonFinish(window, event);
	DrawManager::handleEvents(window, event);
}

void FirstImage::displayText(sf::RenderWindow& window, std::string information)
{
	sf::Text text;

	text.setFont(Font::font);
	text.setString(information);
	text.setCharacterSize(20);
	text.setFillColor(ColorSelector::textColor);
	text.setPosition(window.getSize().x / 2 - information.size() * 4, window.getSize().y - 50);

	window.draw(text);
}

void FirstImage::handleNextImage(sf::RenderWindow& window, sf::Event& event)
{
	if (ShapeSelector::movingShape != ShapeType::Nothing) //we will go to second image only if we have at least 1 shape on screen
		return;
	if (ShapeSelector::allShapeTypes.size() == 0)
		return;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
	{
		Screen::goToScreen(ScreenType::SecondImage);

		for (auto& rectangle : ShapeSelector::shapes.rectangles)
		{
			ShapeSelector::shapes2.rectangles.push_back(rectangle);
		}

		for (auto& triangle : ShapeSelector::shapes.triangles)
		{
			ShapeSelector::shapes2.triangles.push_back(triangle);
		}

		for (auto& circle : ShapeSelector::shapes.circles)
		{
			ShapeSelector::shapes2.circles.push_back(circle);
		}

		for (auto& polygon : ShapeSelector::shapes.polygons)
		{
			ShapeSelector::shapes2.polygons.push_back(polygon);
		}
	}
}
}