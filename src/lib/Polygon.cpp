#include "Polygon.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"

namespace my
{

Polygon::Polygon()
{
	isFinished = false;
	points = std::vector<sf::CircleShape>();
	polygonColor = ColorSelector::activeColor;
}

void Polygon::addPoint(sf::RenderWindow& window, sf::Vector2f position)
{
	sf::CircleShape circle;

	circle.setOrigin(2, 2);
	circle.setRadius(2);
	sf::Vector2u pos = DrawManager::setShapeBoundaries(window, circle.getLocalBounds(), circle.getGlobalBounds());
	circle.setPosition(pos.x, pos.y);
	circle.setPosition(position);
	circle.setFillColor(polygonColor);

	points.push_back(circle);
}

void Polygon::drawLastLine(sf::RenderWindow& window)
{
	if (points.size() > 1)
	{
		sf::Vertex line[] = {
			points.front().getPosition(),
			points.back().getPosition()
		};

		line[0].color = polygonColor;
		line[1].color = polygonColor;

		window.draw(line, 2, sf::Lines);
	}
}
}