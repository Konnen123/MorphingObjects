namespace my
{
class SecondImage
{
private:
	static void saveSecondImage();
	static void rotateRectangle(sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& rectangle);
	static void rotateCircle(sf::RenderWindow& window, sf::Event& event, sf::CircleShape& circle);
	static void rectangleSizeDecrease(sf::RectangleShape& rectangle);
	static void circleSizeDecrease(sf::CircleShape& circle);
	static void rectangleSizeIncrease(sf::RectangleShape& rectangle);
	static void circleSizeIncrease(sf::CircleShape& circle);

public:
	static void display(sf::RenderWindow& window, sf::Event& event);
	static void handleEvents(sf::RenderWindow& window, sf::Event& event);
	static void displayText(sf::RenderWindow& window);
	static void moveAllShapes(sf::RenderWindow& window, sf::Event& event);
	static void movePointsFromPolygon(sf::RenderWindow& window);
};
}