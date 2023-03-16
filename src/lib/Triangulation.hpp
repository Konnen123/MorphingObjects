
namespace my
{
class Triangulation
{
private:
	static float distance(sf::Vector2f point1, sf::Vector2f point2);
	static bool isVertexInsideCircumcircle(sf::CircleShape vertex, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3);
	static float getRadiusOfCircumcircle(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3);
	static bool isEdgeShared(sf::VertexArray edge, std::vector<sf::VertexArray> badTriangles, int index);
	static bool isEdgeTheLimitOfPolygon(sf::VertexArray edge, std::vector<sf::CircleShape> points);

public:
	static std::vector<sf::VertexArray> createTrianglesToFillPolygon(sf::RenderWindow& window, std::vector<sf::CircleShape> points);
	static sf::Vector2f findCircumcirclePosition(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3);
};
}