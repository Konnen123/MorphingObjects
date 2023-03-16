#include "Triangulation.hpp"
#include <cmath>
namespace my
{
sf::Vector2f Triangulation::findCircumcirclePosition(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3)
{
	float firstSide, secondSide, thirdSide, d;

	sf::Vector2f circumCirclePosition;

	d = 2 * (point1.x * (point2.y - point3.y) + point2.x * (point3.y - point1.y) + point3.x * (point1.y - point2.y));
	circumCirclePosition.x = ((point1.x * point1.x + point1.y * point1.y) * (point2.y - point3.y) + (point2.x * point2.x + point2.y * point2.y) * (point3.y - point1.y) + (point3.x * point3.x + point3.y * point3.y) * (point1.y - point2.y)) / d;
	circumCirclePosition.y = ((point1.x * point1.x + point1.y * point1.y) * (point3.x - point2.x) + (point2.x * point2.x + point2.y * point2.y) * (point1.x - point3.x) + (point3.x * point3.x + point3.y * point3.y) * (point2.x - point1.x)) / d;

	return circumCirclePosition;
}
float Triangulation::getRadiusOfCircumcircle(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3)
{
	float firstSide, secondSide, thirdSide, radius;

	firstSide = distance(point1, point2);
	secondSide = distance(point1, point3);
	thirdSide = distance(point2, point3);
	radius = (firstSide * secondSide * thirdSide) / (sqrt((firstSide + secondSide + thirdSide) * (secondSide + thirdSide - firstSide) * (thirdSide + firstSide - secondSide) * (firstSide + secondSide - thirdSide)));

	return radius;
}
bool Triangulation::isVertexInsideCircumcircle(sf::CircleShape vertex, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3)
{
	sf::Vector2f circumCirclePosition = findCircumcirclePosition(point1, point2, point3);

	float radius = getRadiusOfCircumcircle(point1, point2, point3);

	if (distance(circumCirclePosition, vertex.getPosition()) < radius)
		return true;

	return false;
}
bool Triangulation::isEdgeShared(sf::VertexArray edge, std::vector<sf::VertexArray> badTriangles, int index)
{
	int sameEdge = 0;
	for (int i = 0; i < badTriangles.size(); i++)
	{
		int firstPointCounter = 0;
		int secondPointCounter = 0;
		if (i == index)
			continue;

		auto currentTriangle = badTriangles[i];

		if (edge[0].position == currentTriangle[0].position || edge[0].position == currentTriangle[1].position || edge[0].position == currentTriangle[2].position)
			firstPointCounter++;
		if (edge[1].position == currentTriangle[0].position || edge[1].position == currentTriangle[1].position || edge[1].position == currentTriangle[2].position)
			secondPointCounter++;

		if (firstPointCounter == 1 && secondPointCounter == 1)
			return true;
	}
	return false;
}
bool Triangulation::isEdgeTheLimitOfPolygon(sf::VertexArray edge, std::vector<sf::CircleShape> points)
{
	for (int i = 0; i < points.size() - 1; i++)
	{
		if ((edge[0].position == points[i].getPosition() || edge[0].position == points[i + 1].getPosition()) && (edge[1].position == points[i].getPosition() || edge[1].position == points[i + 1].getPosition()))
			return true;
	}
	if ((edge[0].position == points[points.size() - 1].getPosition() || edge[0].position == points[0].getPosition()) && (edge[1].position == points[points.size() - 1].getPosition() || edge[1].position == points[0].getPosition()))
		return true;

	return false;
}
std::vector<sf::VertexArray> Triangulation::createTrianglesToFillPolygon(sf::RenderWindow& window, std::vector<sf::CircleShape> points)
{
	//we will use Bowyer–Watson algorithm
	std::vector<sf::VertexArray> trianglesToFill;

	//create super-triangle(that contains all the vertexes)
	sf::VertexArray superTriangle(sf::Triangles, 3);
	superTriangle[0].position = sf::Vector2f(0, window.getSize().y);
	superTriangle[1].position = sf::Vector2f(window.getSize().x * 2, window.getSize().y);
	superTriangle[2].position = sf::Vector2f(0, -1000);

	trianglesToFill.push_back(superTriangle);

	for (auto& point : points)
	{
		std::vector<sf::VertexArray> badTriangles;
		for (auto triangle : trianglesToFill)
		{
			triangle.setPrimitiveType(sf::Triangles);
			triangle.resize(3);
			if (isVertexInsideCircumcircle(point, triangle[0].position, triangle[1].position, triangle[2].position)) //if the point/vertex is in circumcircle, it means the triangle isnt good
				badTriangles.push_back(triangle);
		}
		std::vector<sf::VertexArray> polygon;
		//we take all the edges of a triangle from badtriangle, then we compare to see if they have the same edge. If they dont have the same edge, we put it in polygon vector
		for (int i = 0; i < badTriangles.size(); i++)
		{
			auto currentTriangle = badTriangles[i];

			for (int j = 0; j < 3; j++)
			{
				sf::VertexArray edge(sf::Lines, 2);
				int pointCounter = j;
				edge[0].position = currentTriangle[pointCounter].position;

				if (pointCounter == 2)
					pointCounter = -1;
				edge[1].position = currentTriangle[pointCounter + 1].position;

				if (!isEdgeShared(edge, badTriangles, i))
					polygon.push_back(edge);
			}
		}
		for (auto triangle : badTriangles)
		{
			for (int i = 0; i < trianglesToFill.size(); i++)
			{
				auto goodTriangle = trianglesToFill[i];
				if (triangle[0].position == goodTriangle[0].position && triangle[1].position == goodTriangle[1].position && triangle[2].position == goodTriangle[2].position)
				{
					trianglesToFill.erase(trianglesToFill.begin() + i);
				}
			}
		}
		for (auto edge : polygon)
		{ //we create new triangles

			sf::VertexArray newTriangle(sf::Triangles, 3);
			newTriangle[0].position = edge[0].position;
			newTriangle[1].position = edge[1].position;
			newTriangle[2].position = point.getPosition();

			trianglesToFill.push_back(newTriangle);
		}
	}

	auto triangle = trianglesToFill.begin();
	while (triangle != trianglesToFill.end())
	{
		int ok = 0;

		for (int j = 0; j < 3; j++)
		{
			auto triangleVertex = (*triangle)[j].position;

			if (triangleVertex == superTriangle[0].position || triangleVertex == superTriangle[1].position || triangleVertex == superTriangle[2].position)
			{
				triangle = trianglesToFill.erase(triangle);
				ok = 1;
			}
		}
		if (ok == 0)
			triangle++;
	}

	std::vector<sf::VertexArray> testTriangles;
	for (int i = 0; i < trianglesToFill.size(); i++)
	{
		auto currentTriangle = trianglesToFill[i];
		int ok = 0;

		for (int j = 0; j < 3; j++)
		{
			sf::VertexArray edge(sf::Lines, 2);
			int pointCounter = j;
			edge[0].position = currentTriangle[pointCounter].position;

			if (pointCounter == 2)
				pointCounter = -1;
			edge[1].position = currentTriangle[pointCounter + 1].position;

			if (!(isEdgeShared(edge, trianglesToFill, i) || isEdgeTheLimitOfPolygon(edge, points)))
			{
				ok = 1;
				break;
			}
		}
		if (ok == 0)
			testTriangles.push_back(currentTriangle);
	}
	return testTriangles;
}

float Triangulation::distance(sf::Vector2f point1, sf::Vector2f point2)
{
	return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

}