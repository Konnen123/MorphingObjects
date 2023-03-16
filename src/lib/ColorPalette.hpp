
namespace my
{
class ColorPalette
{
private:
	static void displayColorOptions(sf::RenderWindow& window, sf::Event& event);
	static void backToMainMenu(sf::RenderWindow& window, sf::Event& event);

public:
	static std::vector<sf::Color> backgroundColors;
	static std::vector<sf::Color> textColors;
	static std::vector<sf::Color> buttonColors;

	static void displayMenu(sf::RenderWindow& window, sf::Event& event);
};
}