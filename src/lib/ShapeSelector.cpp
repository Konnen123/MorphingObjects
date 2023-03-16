#include "ShapeSelector.hpp"
#include "AllButtons.hpp"
#include "Clamp.hpp"
#include "Polygon.hpp"
#include "ShapeSettings.hpp"
#include "Timer.hpp"
#include "Triangulation.hpp"
#include "lib/Button.hpp"
#include "lib/ColorSelector.hpp"
#include "lib/Font.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
ShapeType ShapeSelector::selectedShape = ShapeType::Nothing;
ShapeType ShapeSelector::movingShape = ShapeType::Nothing;

std::vector<ShapeType> ShapeSelector::allShapeTypes;

Shapes ShapeSelector::shapes = {
	std::vector<sf::RectangleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<Polygon>()
};

Shapes ShapeSelector::shapes2 = {
	std::vector<sf::RectangleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<sf::CircleShape>(),
	std::vector<Polygon>()
};

Button* ShapeSelector::rectangleButton = nullptr;
Button* ShapeSelector::circleButton = nullptr;
Button* ShapeSelector::triangleButton = nullptr;
Button* ShapeSelector::polygonButton = nullptr;

void ShapeSelector::handleCircleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;
	unsigned int r;

	r = ShapeSettings::setCircleSettings(window, "Radius"); //pops up the settings for the shape

	clamp(window.getSize().x / 3, 10, r);

	addCircle(window, r);

	setMovingShape();
}

void ShapeSelector::handleRectangleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;

	unsigned int width, height;

	ShapeSettings::setRectangleSettings(window, width, height);

	clamp(window.getSize().x / 3, 10, width);
	clamp(window.getSize().y / 3, 10, height);

	addRectangle(window, width, height);

	setMovingShape();
}

void ShapeSelector::handleTriangleSelection(sf::RenderWindow& window)
{
	if (movingShape != ShapeType::Nothing)
		return;

	unsigned int side;

	side = ShapeSettings::setCircleSettings(window, "Side"); //pops up the settings for the shape

	clamp(window.getSize().x / 3, 10, side);

	addTriangle(window, side);

	setMovingShape();
}

void ShapeSelector::handlePolygonSelection(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		Polygon polygon;

		ShapeSelector::shapes.polygons.push_back(polygon);

		setMovingShape();
	}
}

void ShapeSelector::setMovingShape()
{
	movingShape = selectedShape;
	allShapeTypes.push_back(movingShape);
	selectedShape = ShapeType::Nothing;
}

void ShapeSelector::addCircle(sf::RenderWindow& window, unsigned int radius)
{
	sf::CircleShape circle;

	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	circle.setFillColor(my::ColorSelector::activeColor);

	shapes.circles.push_back(circle);

	window.draw(circle);
	window.display();
}

void ShapeSelector::addRectangle(sf::RenderWindow& window, unsigned int width, unsigned int height)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(width / 2.f, height / 2.f);
	rectangle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	rectangle.setFillColor(my::ColorSelector::activeColor);

	shapes.rectangles.push_back(rectangle);

	window.draw(rectangle);
	window.display();
}

void ShapeSelector::addTriangle(sf::RenderWindow& window, unsigned int side)
{
	sf::CircleShape triangle;

	triangle.setRadius(side);
	triangle.setPointCount(3);
	triangle.setOrigin(side, side);
	triangle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	triangle.setFillColor(my::ColorSelector::activeColor);

	shapes.triangles.push_back(triangle);

	window.draw(triangle);
	window.display();
}

void ShapeSelector::refreshShapesCount()
{
	shapes.rectangles.clear();
	shapes.circles.clear();
	shapes.triangles.clear();
}

void ShapeSelector::displayMenu(sf::RenderWindow& window)
{
	int length = 150, height = 50;

	my::Button rectangleButton(window, my::ColorSelector::buttonColor, length, height, 200, window.getSize().y - 100);
	rectangleButton.setText(window, my::ColorSelector::textColor, "RECTANGLE", my::Font::font, 24);
	rectangleButton.setOnClick([]() { selectedShape = ShapeType::Rectangle; });
	ShapeSelector::rectangleButton = &rectangleButton;

	my::Button circleButton(window, my::ColorSelector::buttonColor, length, height, 400, window.getSize().y - 100);
	circleButton.setText(window, my::ColorSelector::textColor, "CIRCLE  ", my::Font::font, 24);
	circleButton.setOnClick([]() { selectedShape = ShapeType::Circle; });
	ShapeSelector::circleButton = &circleButton;

	my::Button triangleButton(window, my::ColorSelector::buttonColor, length, height, 600, window.getSize().y - 100);
	triangleButton.setText(window, my::ColorSelector::textColor, "TRIANGLE", my::Font::font, 24);
	triangleButton.setOnClick([]() { selectedShape = ShapeType::Triangle; });
	ShapeSelector::triangleButton = &triangleButton;

	my::Button polygonButton(window, my::ColorSelector::buttonColor, length, height, 800, window.getSize().y - 100);
	polygonButton.setText(window, my::ColorSelector::textColor, "POLYGON", my::Font::font, 24);
	polygonButton.setOnClick([]() { selectedShape = ShapeType::Polygon; });
	ShapeSelector::polygonButton = &polygonButton;
}

void ShapeSelector::handlePolygonFinish(sf::RenderWindow& window, sf::Event& event)
{
	if (movingShape == ShapeType::Polygon)
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
		{
			if (shapes.polygons.back().points.size() >= 3)
			{
				shapes.polygons.back().isFinished = true;
			}
		}
}

void ShapeSelector::handleShapeSelection(sf::RenderWindow& window, sf::Event& event)
{
	switch (selectedShape)
	{
		case ShapeType::Rectangle:
			handleRectangleSelection(window);
			break;
		case ShapeType::Circle:
			handleCircleSelection(window);
			break;
		case ShapeType::Triangle:
			handleTriangleSelection(window);
			break;
		case ShapeType::Polygon:
			handlePolygonSelection(window, event);
			break;

		case ShapeType::Nothing:
			break;
		default:
			break;
	}
}

}