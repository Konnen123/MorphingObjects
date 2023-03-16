#include "ShapeSettings.hpp"
#include "AllButtons.hpp"
#include "Clamp.hpp"
#include "Polygon.hpp"
#include "ShapeSelector.hpp"
#include "Timer.hpp"
#include "lib/Button.hpp"
#include "lib/ColorSelector.hpp"
#include "lib/Font.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
InputType ShapeSettings::selectedInput = InputType::FirstInput;

void ShapeSettings::createCanvas(sf::RenderWindow& window, int x, int y)
{
	//creating canvas
	sf::RectangleShape dimensions({ x, y });
	dimensions.setOrigin(x / 2, y / 2);
	dimensions.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	dimensions.setFillColor(ColorSelector::buttonColor);
	window.draw(dimensions);
}
void ShapeSettings::createUserInput(sf::RenderWindow& window, std::string argument, sf::Vector2f v2f)
{
	//user input
	sf::Text userInput;
	userInput.setString(argument);
	userInput.setColor(ColorSelector::textColor);
	userInput.setFont(Font::font);
	userInput.setPosition(v2f);
	window.draw(userInput);
}
void ShapeSettings::writeSize(sf::RenderWindow& window, Button currInput, std::string& txt, sf::Event event)
{

	if (event.type == sf::Event::TextEntered)
	{
		window.draw(currInput.button);

		if (event.text.unicode >= 48 && event.text.unicode <= 57 && txt.length() < 3) //will only type numbers between 0 and 9 and makes sure it doesnt get above 1000 size
			txt += static_cast<char>(event.text.unicode);

		if (event.text.unicode == 8 && txt.length() > 0) //backspace for deleting last digit if text has more than 1 digit
			txt.pop_back();

		currInput.setText(window, ColorSelector::buttonColor, txt + ' ', Font::font, 24);
		window.display();
		Timer::setTimer(150); //timer
	}
}
int ShapeSettings::setCircleSettings(sf::RenderWindow& window, std::string argument)
{
	unsigned int r;
	//settings size
	int x = 300;
	int y = 400;

	createCanvas(window, x, y);
	createUserInput(window, argument, { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 120 });

	//creating confirmation button
	Button confirmButton(window, ColorSelector::backgroundColor, 100, 50, window.getSize().x / 2.f, window.getSize().y / 2.f + 150);
	confirmButton.setText(window, ColorSelector::textColor, "Confirm", Font::font, 24);

	//creating text input
	Button textInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 100);

	window.display();

	std::string txt;
	sf::Event event;

	while (!confirmButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) || event.type != sf::Event::MouseButtonPressed)
	{
		//settings size
		int x = 300;
		int y = 400;

		createCanvas(window, x, y);
		createUserInput(window, argument, { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 120 });

		//creating confirmation button
		Button confirmButton(window, ColorSelector::backgroundColor, 100, 50, window.getSize().x / 2.f, window.getSize().y / 2.f + 150);
		confirmButton.setText(window, ColorSelector::textColor, "Confirm", Font::font, 24);

		//creating text input
		Button textInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 100);

		//window.display();
		window.pollEvent(event);
		writeSize(window, textInput, txt, event);
	}

	if (txt.empty()) //checks if user didnt write a number
		r = 0;
	else
		r = std::stoi(txt);

	return r;
}
void ShapeSettings::chooseInputCase(sf::RenderWindow& window, InputType selectedInput, Button lengthInput, Button heightInput, std::string& lengthTxt, std::string& heightTxt, sf::Event event)
{
	switch (selectedInput)
	{
		case InputType::FirstInput:
			writeSize(window, lengthInput, lengthTxt, event);
			break;
		case InputType::SecondInput:
			writeSize(window, heightInput, heightTxt, event);

		default:
			break;
	}
}
bool ShapeSettings::isButtonPressed(Button currButton, sf::Event event, sf::RenderWindow& window)
{
	return currButton.button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::MouseButtonPressed;
}
void ShapeSettings::setRectangleSettings(sf::RenderWindow& window, unsigned int& length, unsigned int& height)
{

	//settings size
	int x = 300;
	int y = 400;

	createCanvas(window, x, y);
	createUserInput(window, "Length", { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 120 });
	createUserInput(window, "Height", { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 30 });

	//creating confirmation button
	Button confirmButton(window, ColorSelector::backgroundColor, 100, 50, window.getSize().x / 2.f, window.getSize().y / 2.f + 150);
	confirmButton.setText(window, ColorSelector::textColor, "Confirm", Font::font, 24);

	//creating text input
	Button lengthInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 100);
	Button heightInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 10);

	window.display();

	std::string lengthTxt;
	std::string heightTxt;
	sf::Event event;

	while (!isButtonPressed(confirmButton, event, window))
	{
		int x = 300;
		int y = 400;

		createCanvas(window, x, y);
		createUserInput(window, "Length", { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 120 });
		createUserInput(window, "Height", { window.getSize().x / 2.f - 100, window.getSize().y / 2.f - 30 });

		//creating confirmation button
		Button confirmButton(window, ColorSelector::backgroundColor, 100, 50, window.getSize().x / 2.f, window.getSize().y / 2.f + 150);
		confirmButton.setText(window, ColorSelector::textColor, "Confirm", Font::font, 24);

		//creating text input
		Button lengthInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 100);
		Button heightInput(window, ColorSelector::textColor, 60, 50, window.getSize().x / 2.f + 50, window.getSize().y / 2.f - 10);

		window.pollEvent(event);

		if (isButtonPressed(lengthInput, event, window))
			selectedInput = InputType::FirstInput;

		if (isButtonPressed(heightInput, event, window))
			selectedInput = InputType::SecondInput;

		lengthInput.setText(window, ColorSelector::buttonColor, lengthTxt + ' ', Font::font, 24);
		heightInput.setText(window, ColorSelector::buttonColor, heightTxt + ' ', Font::font, 24);
		chooseInputCase(window, selectedInput, lengthInput, heightInput, lengthTxt, heightTxt, event);
		window.display();
	}

	if (lengthTxt.empty()) //checks if user didnt write a number
		length = 0;
	else
		length = std::stoi(lengthTxt);

	if (heightTxt.empty())
		height = 0;
	else
		height = std::stoi(heightTxt);
}
}