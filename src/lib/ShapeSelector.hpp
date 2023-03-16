#include "Button.hpp"
#include "Polygon.hpp"
#include <SFML/Graphics.hpp>

namespace my
{
struct Shapes
{
	std::vector<sf::RectangleShape> rectangles;
	std::vector<sf::CircleShape> circles;
	std::vector<sf::CircleShape> triangles;
	std::vector<Polygon> polygons;
};

enum class ShapeType
{
	Nothing,
	Rectangle,
	Circle,
	Triangle,
	Polygon
};

class ShapeSelector
{
private:
	static void handleRectangleSelection(sf::RenderWindow& window);
	static void handleCircleSelection(sf::RenderWindow& window);
	static void handleTriangleSelection(sf::RenderWindow& window);
	static void handlePolygonSelection(sf::RenderWindow& window, sf::Event& event);
	static void addRectangle(sf::RenderWindow& window, unsigned int width, unsigned int height);
	static void addCircle(sf::RenderWindow& window, unsigned int radius);
	static void addTriangle(sf::RenderWindow& window, unsigned int side);
	static void setMovingShape();

public:
	static Button* rectangleButton;
	static Button* circleButton;
	static Button* triangleButton;
	static Button* polygonButton;
	static Shapes shapes;
	static Shapes shapes2;
	static std::vector<ShapeType> allShapeTypes;
	static ShapeType selectedShape;
	static ShapeType movingShape;
	static void displayMenu(sf::RenderWindow& window);
	static void refreshShapesCount();
	static void handlePolygonFinish(sf::RenderWindow& window, sf::Event& event);
	static void handleShapeSelection(sf::RenderWindow& window, sf::Event& event);
};
}