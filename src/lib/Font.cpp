#include "Font.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
sf::Font Font::font = sf::Font();
sf::Font Font::fontBold = sf::Font();

void Font::load()
{
	//dam load la fonturile din fisier
	if (!font.loadFromFile("DIN.ttf"))
		std::cout << "ERROR, DIN FONT NOT LOADED";

	if (!fontBold.loadFromFile("DINBold.ttf"))
		std::cout << "ERROR, DINBold FONT NOT LOADED";
}
}