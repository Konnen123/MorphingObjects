namespace my
{
enum class ScreenType
{
	StartMenu,
	ColorPalette,
	FirstImage,
	SecondImage,
	Morphing,
	EndMenu
};

class Screen
{
public:
	static ScreenType currentScreen;
	static void nextScreen();
	static void previousScreen();
	static void goToScreen(ScreenType screen);
	static void screenHandler(sf::RenderWindow& window, sf::Event& event);
	static void backToStartMenu(sf::RenderWindow& window, sf::Event& event);
};
}
