#include "SecondImage.hpp"
#include "Button.hpp"
#include "Clamp.hpp"
#include "ColorSelector.hpp"
#include "DrawManager.hpp"
#include "Font.hpp"
#include "MenuSelector.hpp"
#include "Morphing.hpp"
#include "SavingImage.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"

namespace my
{

void SecondImage::display(sf::RenderWindow& window, sf::Event& event)
{
	window.clear(ColorSelector::backgroundColor);

	DrawManager::drawShapes(window);
	SecondImage::moveAllShapes(window, event);
	SecondImage::movePointsFromPolygon(window);
	Morphing::displayMorphingButton(window);

	window.display();
}

void SecondImage::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	//ShapeSelector::handleShapeSelection(window, event);
	//ShapeSelector::handlePolygonFinish(window, event);
	//DrawManager::handleEvents(window, event);
	//saveSecondImage();
}

void SecondImage::displayText(sf::RenderWindow& window)
{
	sf::Text text;

	text.setFont(Font::font);
	text.setString("Second Image");
	text.setCharacterSize(20);
	text.setFillColor(ColorSelector::textColor);
	text.setPosition(window.getSize().x / 2 - 50, window.getSize().y - 30);

	window.draw(text);
	window.display();
}

void SecondImage::moveAllShapes(sf::RenderWindow& window, sf::Event& event)
{

	for (int i = ShapeSelector::shapes2.rectangles.size() - 1; i >= 0; i--)
	{
		auto& rectangle = ShapeSelector::shapes2.rectangles[i];

		if (rectangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);

				rotateRectangle(window, event, rectangle);
				rectangleSizeDecrease(rectangle);
				rectangleSizeIncrease(rectangle);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, rectangle.getLocalBounds(), rectangle.getGlobalBounds());
				rectangle.setPosition(pos.x, pos.y);

				window.draw(rectangle);
				displayText(window);
			}
		}
	}

	for (int i = ShapeSelector::shapes2.circles.size() - 1; i >= 0; i--)
	{
		auto& circle = ShapeSelector::shapes2.circles[i];

		if (circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);
				circleSizeDecrease(circle);
				circleSizeIncrease(circle);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, circle.getLocalBounds(), circle.getGlobalBounds());
				circle.setPosition(pos.x, pos.y);

				window.draw(circle);
				displayText(window);
			}
		}
	}

	for (int i = ShapeSelector::shapes2.triangles.size() - 1; i >= 0; i--)
	{
		auto& triangle = ShapeSelector::shapes2.triangles[i];
		if (triangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.clear(ColorSelector::backgroundColor);
				rotateCircle(window, event, triangle);
				circleSizeDecrease(triangle);
				circleSizeIncrease(triangle);
				DrawManager::drawShapes(window);
				sf::Vector2u pos = DrawManager::setShapeBoundaries(window, triangle.getLocalBounds(), triangle.getGlobalBounds());
				triangle.setPosition(pos.x, pos.y);

				window.draw(triangle);
				displayText(window);
			}
		}
	}
	SavingImage::saveSecondImage();
}
void SecondImage::rotateRectangle(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& rectangle)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		return;

	unsigned int angle = rectangle.getRotation() + 1;
	rectangle.setRotation(angle);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().height / 2.f);
}
void SecondImage::rotateCircle(sf::RenderWindow& window, sf::Event& event, sf::CircleShape& circle)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		return;

	unsigned int r = circle.getRadius();
	unsigned int angle = circle.getRotation() + 1;

	clamp(window.getSize().x / 3, 20, r);

	circle.setOrigin(r, r);
	circle.setRotation(angle);
}
void SecondImage::rectangleSizeDecrease(sf::RectangleShape& rectangle)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		return;

	if (rectangle.getSize().x - rectangle.getSize().x * 0.1 <= 50 || rectangle.getSize().y - rectangle.getSize().y * 0.1 <= 50)
		return;

	rectangle.setSize(sf::Vector2f(rectangle.getSize().x - rectangle.getSize().x * 0.01, rectangle.getSize().y - rectangle.getSize().y * 0.01));
	DrawManager::clampShapeSize(rectangle);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
}
void SecondImage::rectangleSizeIncrease(sf::RectangleShape& rectangle)
{

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		return;
	if (rectangle.getSize().x + rectangle.getSize().x * 0.1 >= 300 || rectangle.getSize().y + rectangle.getSize().y * 0.1 >= 300)
		return;

	rectangle.setSize(sf::Vector2f(rectangle.getSize().x + rectangle.getSize().x * 0.01, rectangle.getSize().y + rectangle.getSize().y * 0.01));
	DrawManager::clampShapeSize(rectangle);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
}
void SecondImage::circleSizeIncrease(sf::CircleShape& circle)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		return;

	circle.setRadius(circle.getRadius() + circle.getRadius() * 0.01);
	DrawManager::clampShapeSize(circle);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
}
void SecondImage::circleSizeDecrease(sf::CircleShape& circle)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		return;

	circle.setRadius(circle.getRadius() - circle.getRadius() * 0.01);
	DrawManager::clampShapeSize(circle);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
}
void SecondImage::movePointsFromPolygon(sf::RenderWindow& window)
{
	for (auto& polygon : ShapeSelector::shapes2.polygons)
	{
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
					sf::Vector2u pos = DrawManager::setShapeBoundaries(window, point.getLocalBounds(), point.getGlobalBounds());
					point.setPosition(pos.x, pos.y);
				}
			}
		}
	}
}
void SecondImage::saveSecondImage()
{
	static int ok = 0;
	if (ok)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		ok = 1;
		SavingImage::saveSecondImage();
		std::cout << "llllll";
	}
}
}