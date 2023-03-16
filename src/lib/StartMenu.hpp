#include <SFML/Graphics.hpp>

namespace my
{
class StartMenu
{
private:
	static void displayTitle(sf::RenderWindow& window);
	static void displayButtons(sf::RenderWindow& window);

public:
	static void initialize();
	static void display(sf::RenderWindow& window);
	static void handleKeyPress(sf::Event& event, sf::RenderWindow& window);
};
}