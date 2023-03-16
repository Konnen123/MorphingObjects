#include "DrawManager.hpp"
#include "Clamp.hpp"
#include "ColorSelector.hpp"
#include "SavingImage.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include "Timer.hpp"
#include "Triangulation.hpp"

namespace my
{
unsigned int minimumSize = 50;
unsigned int maximumSize = 300;

void DrawManager::drawShapes(sf::RenderWindow& window)
{
	int r, c, t, p;
	r = c = t = p = 0; //counters for all shapes

	Shapes currentShape = ShapeSelector::shapes;
	if (Screen::currentScreen == ScreenType::SecondImage)
	{
		currentShape = ShapeSelector::shapes2;
	}

	for (auto type : ShapeSelector::allShapeTypes)
	{
		switch (type)
		{
			case ShapeType::Rectangle:
				window.draw(currentShape.rectangles[r++]);
				break;
			case ShapeType::Circle:
				window.draw(currentShape.circles[c++]);
				break;
			case ShapeType::Triangle:
				window.draw(currentShape.triangles[t++]);
				break;
			case ShapeType::Polygon: {

				for (auto& point : currentShape.polygons[p].points)
				{

					window.draw(point);
				}
				if (!currentShape.polygons[p].isFinished)
					break;

				std::vector<sf::VertexArray> triangles = Triangulation::createTrianglesToFillPolygon(window, currentShape.polygons[p].points);

				for (int i = 0; i < triangles.size(); i++)
				{
					auto triangleColorPoint = triangles[i];
					triangleColorPoint[0].color = currentShape.polygons[p].polygonColor;
					triangleColorPoint[1].color = currentShape.polygons[p].polygonColor;
					triangleColorPoint[2].color = currentShape.polygons[p].polygonColor;

					window.draw(triangleColorPoint);
				}
				p++;
				break;
			}

			default:
				break;
		}
	}
	drawLinesBetweenPolygonPoints(window);
}

void DrawManager::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	handleRotation(window, event);
	handleSizeIncrease(window, event);
	handleSizeDecrease(window, event);
	handleMoveShape(window, event);
	handleSavePosition(window, event);

	movePointsFromPolygon(window, event);
}
sf::Vector2u DrawManager::setShapeBoundaries(sf::RenderWindow& window, sf::FloatRect localBounds, sf::FloatRect globalBounds)
{
	sf::Vector2u pos;
	pos.x = sf::Mouse::getPosition(window).x;
	pos.y = sf::Mouse::getPosition(window).y;

	if (pos.x > window.getSize().x * 10) //e ceva bug in care din stanga se teleporteaza in dreapta
		pos.x = 0;
	if (pos.y > window.getSize().y * 10)
		pos.y = 0;

	clamp(window.getSize().x - globalBounds.width + localBounds.width / 2.f, localBounds.width / 2.f, pos.x);
	clamp(window.getSize().y - 200 - globalBounds.height + localBounds.height / 2.f, localBounds.height / 2.f, pos.y);

	return pos;
}

void DrawManager::handleMoveShape(sf::RenderWindow& window, sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle: {
				sf::Vector2u pos = setShapeBoundaries(window, ShapeSelector::shapes.rectangles.back().getLocalBounds(), ShapeSelector::shapes.rectangles.back().getGlobalBounds());
				ShapeSelector::shapes.rectangles.back().setPosition(pos.x, pos.y);
			}
			break;
			case ShapeType::Circle: {
				sf::Vector2u pos = setShapeBoundaries(window, ShapeSelector::shapes.circles.back().getLocalBounds(), ShapeSelector::shapes.circles.back().getGlobalBounds());
				ShapeSelector::shapes.circles.back().setPosition(pos.x, pos.y);
			}
			break;
			case ShapeType::Triangle: {
				sf::Vector2u pos = setShapeBoundaries(window, ShapeSelector::shapes.triangles.back().getLocalBounds(), ShapeSelector::shapes.triangles.back().getGlobalBounds());
				ShapeSelector::shapes.triangles.back().setPosition(pos.x, pos.y);
			}
			break;
			case ShapeType::Polygon:
				handleAddPolygonPoint(window, event);

				break;
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::handleAddPolygonPoint(sf::RenderWindow& window, sf::Event& event)
{

	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && !ShapeSelector::shapes.polygons.back().isFinished)
	{
		sf::CircleShape point;

		point.setRadius(2);
		point.setFillColor(ColorSelector::activeColor);
		sf::Vector2u pos = DrawManager::setShapeBoundaries(window, point.getLocalBounds(), point.getGlobalBounds());
		point.setPosition(pos.x, pos.y);

		ShapeSelector::shapes.polygons.back().points.push_back(point);
	}
}
void DrawManager::movePointsFromPolygon(sf::RenderWindow& window, sf::Event& event)
{
	if (ShapeSelector::shapes.polygons.size() == 0)
		return;

	auto& polygon = ShapeSelector::shapes.polygons.back();

	if (ShapeSelector::movingShape != ShapeType::Polygon) //we will modify the points when we dont have any shape moving
		return;

	if (!polygon.isFinished)
		return;

	for (auto& point : polygon.points)
	{
		point.setRadius(2);
		point.setOrigin(2, 2);
		point.setFillColor(polygon.polygonColor);

		if (point.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			point.setRadius(10);
			point.setOrigin(10, 10);
			point.setFillColor(ColorSelector::buttonColor);
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2u pos = setShapeBoundaries(window, point.getLocalBounds(), point.getGlobalBounds());
				point.setPosition(pos.x, pos.y);
			}
		}
	}
}

void DrawManager::handleSavePosition(sf::RenderWindow& window, sf::Event& event)
{
	window.pollEvent(event);
	if (!sf::Event::EventType::TextEntered)
		return;

	if (!(event.text.unicode == 13 && !sf::Mouse::isButtonPressed(sf::Mouse::Left))) //13 for enter key
		return;

	SavingImage::saveAllShapes();
	ShapeSelector::movingShape = ShapeType::Nothing;
	ShapeSelector::selectedShape = ShapeType::Nothing;

	// we will not save polygons that are not finished, if enter pressed the unfinished polygon will be deleted!
	if (ShapeSelector::shapes.polygons.size() == 0)
		return;
	if (!ShapeSelector::shapes.polygons.back().isFinished)
	{
		ShapeSelector::shapes.polygons.pop_back();
		ShapeSelector::allShapeTypes.pop_back();
	}
}

void DrawManager::handleSizeIncrease(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle: {
				auto& rectangle = ShapeSelector::shapes.rectangles.back();

				if (rectangle.getSize().x + rectangle.getSize().x * 0.1 >= maximumSize || rectangle.getSize().y + rectangle.getSize().y * 0.1 >= maximumSize)
					break;

				rectangle.setSize(sf::Vector2f(rectangle.getSize().x + rectangle.getSize().x * 0.1, rectangle.getSize().y + rectangle.getSize().y * 0.1));
				clampShapeSize(rectangle);
				rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
				break;
			}
			case ShapeType::Circle: {
				auto& circle = ShapeSelector::shapes.circles.back();
				circle.setRadius(circle.getRadius() + circle.getRadius() * 0.1);
				clampShapeSize(circle);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				break;
			}
			case ShapeType::Triangle: {
				auto& triangle = ShapeSelector::shapes.triangles.back();
				triangle.setRadius(triangle.getRadius() + triangle.getRadius() * 0.1);
				clampShapeSize(triangle);
				triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
				break;
			}
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::handleSizeDecrease(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
		switch (ShapeSelector::movingShape)
		{
			case ShapeType::Rectangle: {
				auto& rectangle = ShapeSelector::shapes.rectangles.back();

				if (rectangle.getSize().x - rectangle.getSize().x * 0.1 <= minimumSize || rectangle.getSize().y - rectangle.getSize().y * 0.1 <= minimumSize)
					break;

				rectangle.setSize(sf::Vector2f(rectangle.getSize().x - rectangle.getSize().x * 0.1, rectangle.getSize().y - rectangle.getSize().y * 0.1));
				clampShapeSize(rectangle);
				rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
				break;
			}
			case ShapeType::Circle: {
				auto& circle = ShapeSelector::shapes.circles.back();
				circle.setRadius(circle.getRadius() - circle.getRadius() * 0.1);
				clampShapeSize(circle);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				break;
			}
			case ShapeType::Triangle: {
				auto& triangle = ShapeSelector::shapes.triangles.back();
				triangle.setRadius(triangle.getRadius() - triangle.getRadius() * 0.1);
				clampShapeSize(triangle);
				triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
				break;
			}
			case ShapeType::Nothing:
				break;
			default:
				break;
		}
}

void DrawManager::handleRotation(sf::RenderWindow& window, sf::Event& event)
{

	if (!(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R))
		return;

	switch (ShapeSelector::movingShape)
	{
		case ShapeType::Rectangle: {

			auto& rectangle = ShapeSelector::shapes.rectangles.back();
			unsigned int angle = rectangle.getRotation() + 10;
			rectangle.setRotation(angle);
			rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().height / 2.f);
			break;
		}
		case ShapeType::Triangle: {
			auto& triangle = ShapeSelector::shapes.triangles.back();
			unsigned int r = triangle.getRadius();
			unsigned int angle = triangle.getRotation() + 10;

			clamp(window.getSize().x / 3, 20, r);

			triangle.setOrigin(r, r);
			triangle.setRotation(angle);

			break;
		}
		case ShapeType::Nothing:
			break;
		default:
			break;
	}
}
void DrawManager::clampShapeSize(sf::RectangleShape& shape)
{
	float x = shape.getSize().x, y = shape.getSize().y;

	clamp(maximumSize, minimumSize, x);
	clamp(maximumSize, minimumSize, y);

	shape.setSize(sf::Vector2f(x, y));
}

void DrawManager::clampShapeSize(sf::CircleShape& shape)
{
	float radius = shape.getRadius();

	clamp(maximumSize, minimumSize, radius);

	shape.setRadius(radius);
}

void DrawManager::drawLinesBetweenPolygonPoints(sf::RenderWindow& window)
{
	auto shape = ShapeSelector::shapes;
	if (Screen::currentScreen == ScreenType::SecondImage)
		shape = ShapeSelector::shapes2;

	if (shape.polygons.size() > 0)
	{
		for (auto& polygon : shape.polygons)
		{
			if (polygon.isFinished)
				continue;

			auto& points = polygon.points;

			for (int i = 0; i < points.size() - 1; i++)
			{
				sf::Vertex line[] = {
					sf::Vertex(points[i].getPosition()),
					sf::Vertex(points[i + 1].getPosition())
				};

				sf::Color color = polygon.polygonColor;

				line[0].color = color;
				line[1].color = color;

				window.draw(line, 2, sf::Lines);
			}

			if (polygon.isFinished)
				polygon.drawLastLine(window);
		}
	}
}
}