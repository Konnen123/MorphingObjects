#include "Button.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
class AllButtons
{
public:
	static std::vector<Button> buttons;
	static void handleEvents(sf::RenderWindow& window, sf::Event& ev);
};
}