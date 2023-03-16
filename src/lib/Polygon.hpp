#pragma once

namespace my
{
class Polygon
{
public:
	std::vector<sf::CircleShape> points;
	bool isFinished;
	sf::Color polygonColor;

public:
	Polygon();
	void addPoint(sf::RenderWindow& window, sf::Vector2f position);
	void drawLastLine(sf::RenderWindow& window);
};
}