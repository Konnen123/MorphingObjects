
namespace my
{
class FirstImage
{
public:
	static void display(sf::RenderWindow& window);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
	static void displayText(sf::RenderWindow& window, std::string information = "First Image");
	static void handleNextImage(sf::RenderWindow& window, sf::Event& event);
};
}