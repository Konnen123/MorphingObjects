#include "Morphing.hpp"
#include "Button.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "SavingImage.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include "Timer.hpp"
#include <cassert>
#include <cmath>

namespace my
{
unsigned int moveSpeed = 20000;
void Morphing::displayMorphingButton(sf::RenderWindow& window)
{

	Screen::goToScreen(ScreenType::Morphing);

	Button button = Button(window, ColorSelector::buttonColor, 200, 50, window.getSize().x / 2 + 15, window.getSize().y - 75);
	button.setText(window, ColorSelector::textColor, "START MORPHING", Font::font, 20);

	if (button.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		beginMorph(window);
	}

	Screen::goToScreen(ScreenType::SecondImage);
}

void Morphing::beginMorph(sf::RenderWindow& window)
{
	if (!SavingImage::areAllFilesTheSameSize())
	{
		std::cout << "ERROR! FILES DO NOT HAVE THE SAME SIZE!\n";
		return;
	}
	clearShapeVector();

	//we load only if the vectors are null
	if (ShapeSelector::shapes.rectangles.size() == 0 && ShapeSelector::shapes.circles.size() == 0 && ShapeSelector::shapes.triangles.size() == 0 && ShapeSelector::shapes.polygons.size() == 0)
		SavingImage::loadAllShapes(window, 1);

	if (ShapeSelector::shapes2.rectangles.size() == 0 && ShapeSelector::shapes2.circles.size() == 0 && ShapeSelector::shapes2.triangles.size() == 0 && ShapeSelector::shapes2.polygons.size() == 0)
		SavingImage::loadAllShapes(window, 2);

	std::cout << "Morphing started...\n";
	animateAllShapes(window, moveSpeed);
	std::cout << "Morphing ended...\n";
}

float Morphing::lerp(float initialPoint, float finalPoint, float time)
{
	return initialPoint + time * (finalPoint - initialPoint);
}

void Morphing::animateAllShapes(sf::RenderWindow& window, unsigned int ms)
{
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() < ms)
	{
		bool isFinished = true;
		window.clear(ColorSelector::backgroundColor);
		float progress = (float)clock.getElapsedTime().asMilliseconds() / ms;
		for (int i = 0; i < ShapeSelector::shapes.circles.size(); i++)
		{
			animateCircle(window, ShapeSelector::shapes.circles[i], { ShapeSelector::shapes2.circles[i].getPosition().x, ShapeSelector::shapes2.circles[i].getPosition().y }, ShapeSelector::shapes2.circles[i].getRadius(), ShapeSelector::shapes2.circles[i].getRotation(), progress, isFinished);
		}
		for (int i = 0; i < ShapeSelector::shapes.rectangles.size(); i++)
		{
			animateRectangle(window, ShapeSelector::shapes.rectangles[i], { ShapeSelector::shapes2.rectangles[i].getPosition().x, ShapeSelector::shapes2.rectangles[i].getPosition().y }, { ShapeSelector::shapes2.rectangles[i].getSize().x, ShapeSelector::shapes2.rectangles[i].getSize().y }, ShapeSelector::shapes2.rectangles[i].getRotation(), progress, isFinished);
		}
		for (int i = 0; i < ShapeSelector::shapes.triangles.size(); i++)
		{
			animateCircle(window, ShapeSelector::shapes.triangles[i], { ShapeSelector::shapes2.triangles[i].getPosition().x, ShapeSelector::shapes2.triangles[i].getPosition().y }, ShapeSelector::shapes2.triangles[i].getRadius(), ShapeSelector::shapes2.triangles[i].getRotation(), progress, isFinished);
		}
		for (int i = 0; i < ShapeSelector::shapes.polygons.size(); i++)
		{
			for (int j = 0; j < ShapeSelector::shapes.polygons[i].points.size(); j++)
			{
				auto& point1 = ShapeSelector::shapes.polygons[i].points[j];
				auto& point2 = ShapeSelector::shapes2.polygons[i].points[j];

				if (point1.getPosition() == point2.getPosition())
					continue;

				sf::Vector2u finalPoint = { point2.getPosition().x, point2.getPosition().y };
				animateCircle(window, point1, finalPoint, point2.getRadius(), point2.getRotation(), progress, isFinished);
			}
		}
		DrawManager::drawShapes(window);

		window.display();

		if (isFinished)
			break;
	}
}

void Morphing::animateCircle(sf::RenderWindow& window, sf::CircleShape& circle, sf::Vector2u finalPoint, float finalSize, float finalRotation, float progress, bool& isFinished)
{
	sf::Vector2u initialPoint = { circle.getPosition().x, circle.getPosition().y };
	float initialSize = circle.getRadius();
	float initialRotation = circle.getRotation();

	isFinished = isShapeFinished(initialPoint, finalPoint);

	if (!isFinished)
	{
		circle.setPosition(lerp(initialPoint.x, finalPoint.x, progress), lerp(initialPoint.y, finalPoint.y, progress));
		circle.setRadius(lerp(initialSize, finalSize, progress));
		circle.setRotation(lerp(initialRotation, finalRotation, progress));
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}
}

void Morphing::animateRectangle(sf::RenderWindow& window, sf::RectangleShape& rectangle, sf::Vector2u finalPoint, sf::Vector2u finalSize, float finalRotation, float progress, bool& isFinished)
{
	sf::Vector2u initialPoint = { rectangle.getPosition().x, rectangle.getPosition().y };
	sf::Vector2u initialSize = { rectangle.getSize().x, rectangle.getSize().y };
	float initialRotation = rectangle.getRotation();

	isFinished = isShapeFinished(initialPoint, finalPoint);

	if (!isFinished)
	{
		rectangle.setPosition(lerp(initialPoint.x, finalPoint.x, progress), lerp(initialPoint.y, finalPoint.y, progress));
		rectangle.setSize({ lerp(initialSize.x, finalSize.x, progress), lerp(initialSize.y, finalSize.y, progress) });
		rectangle.setRotation(lerp(initialRotation, finalRotation, progress));
		rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	}

	rectangle.setPosition(lerp(initialPoint.x, finalPoint.x, progress), lerp(initialPoint.y, finalPoint.y, progress));
}

bool Morphing::isShapeFinished(sf::Vector2u initialPoint, sf::Vector2u finalPoint)
{
	if (abs((int)initialPoint.x - (int)finalPoint.x) <= 4 && abs((int)initialPoint.y - (int)finalPoint.y) <= 4)
		return true;

	return false;
}
void Morphing::clearShapeVector()
{
	ShapeSelector::shapes.rectangles.clear();
	ShapeSelector::shapes.circles.clear();
	ShapeSelector::shapes.triangles.clear();
	ShapeSelector::shapes.polygons.clear();
}

}