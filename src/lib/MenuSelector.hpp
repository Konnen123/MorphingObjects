namespace my
{
enum class MenuSelectorType
{
	ShapeSelector,
	ColorSelector
};

class MenuSelector
{
private:
	static void toggleMenuSelector();
	static void disableColorButtons();
	static void disableShapeButtons();
	static void enableColorButtons();
	static void enableShapeButtons();
	static void changeFooterText();

public:
	static MenuSelectorType activeMenuSelector;
	static void drawButtons(sf::RenderWindow& window);
	static void displayMenu(sf::RenderWindow& window);
};
}