namespace my
{
class Morphing
{
private:
	static bool isShapeFinished(sf::Vector2u initialPoint, sf::Vector2u finalPoint);
	static float lerp(float a, float b, float t);
	static void animateCircle(sf::RenderWindow& window, sf::CircleShape& circle, sf::Vector2u finalPoint, float finalSize, float finalRotation, float progress, bool& isFinished);
	static void animateRectangle(sf::RenderWindow& window, sf::RectangleShape& rectangle, sf::Vector2u finalPoint, sf::Vector2u finalSize, float finalRotation, float progress, bool& isFinished);
	static void clearShapeVector();
	static void beginMorph(sf::RenderWindow& window);

public:
	static void displayMorphingButton(sf::RenderWindow& window);
	static void animateAllShapes(sf::RenderWindow& window, unsigned int ms);
};
}