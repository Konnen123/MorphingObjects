#include <SFML/Graphics.hpp>

namespace my
{
class Font
{
public:
	static sf::Font font, fontBold;
	static void load();
};
}