#include "Button.hpp"
#include <SFML/Graphics.hpp>

namespace my
{

enum class InputType
{
	FirstInput,
	SecondInput
};

class ShapeSettings
{
private:
	static void createCanvas(sf::RenderWindow& window, int x, int y);
	static void createUserInput(sf::RenderWindow& window, std::string argument, sf::Vector2f v2f);
	static void writeSize(sf::RenderWindow& window, Button currInput, std::string& txt, sf::Event event);
	static void chooseInputCase(sf::RenderWindow& window, InputType selectedInput, Button lengthInput, Button heightInput, std::string& lengthTxt, std::string& heightTxt, sf::Event event);
	static bool isButtonPressed(Button currButton, sf::Event event, sf::RenderWindow& window);
	static InputType selectedInput;

public:
	static int setCircleSettings(sf::RenderWindow& window, std::string argument);
	static void setRectangleSettings(sf::RenderWindow& window, unsigned int& length, unsigned int& height);
};
}