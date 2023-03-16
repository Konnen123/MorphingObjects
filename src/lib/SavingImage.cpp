#include "SavingImage.hpp"
#include "ColorPalette.hpp"
#include "ColorSelector.hpp"
#include "Screen.hpp"
#include "ShapeSelector.hpp"
#include <fstream>
#include <iostream>

namespace my
{
Rectangle SavingImage::savingRect;
Circle SavingImage::savingCircle;
thisPolygon SavingImage::savingPolygon;
char SavingImage::savingOrder;

std::string rectFileName = "rectangle.dat";
std::string circleFileName = "circle.dat";
std::string polygonFileName = "polygon.dat";
std::string shapeOrderFileName = "shapeOrder.dat";
std::string colorPaletteFileName = "colorPalette.dat";

std::string image2Prefix = "image2";

//color palette
void SavingImage::saveColorPalette(int index)
{
	std::fstream f;
	f.open(colorPaletteFileName, std::ios::out | std::ios::binary);

	f.write(reinterpret_cast<char*>(&index), sizeof(index));
	f.close();
}
void SavingImage::loadColorPalette()
{
	std::fstream f;
	f.open(colorPaletteFileName, std::ios::in | std::ios::binary);
	int index = 0;

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	if (fileSize != 0)
		f.read(reinterpret_cast<char*>(&index), sizeof(index));

	ColorSelector::backgroundColor = ColorPalette::backgroundColors[index];
	ColorSelector::buttonColor = ColorPalette::buttonColors[index];
	ColorSelector::textColor = ColorPalette::textColors[index];

	f.close();
}

//first image
void SavingImage::saveAllShapes()
{
	switch (ShapeSelector::movingShape)
	{
		case ShapeType::Rectangle:
			saveRectangle();
			saveOrder();
			break;
		case ShapeType::Circle:
			saveCircle();
			saveOrder();
			break;
		case ShapeType::Triangle:
			saveCircle();
			saveOrder();
			break;
		case ShapeType::Polygon:
			savePolygon();
			saveOrder();
			break;

		default:
			break;
	}
}
void SavingImage::loadAllShapes(sf::RenderWindow& window, int shapeToSave)
{

	loadRectangle(window, shapeToSave);
	loadCircle(window, shapeToSave);
	loadPolygon(window, shapeToSave);
	loadOrder();
}
void SavingImage::saveRectangle()
{
	std::fstream f;
	if (ShapeSelector::shapes.rectangles.size() == 1)
	{
		f.open(rectFileName, std::ios::out | std::ios::binary);
		deleteAllShapes();
	}
	else
		f.open(rectFileName, std::ios::app | std::ios::binary);

	auto& rect = ShapeSelector::shapes.rectangles.back();
	savingRect = { rect.getSize().x, rect.getSize().y, rect.getPosition().x, rect.getPosition().y, rect.getRotation(), rect.getFillColor().r, rect.getFillColor().g, rect.getFillColor().b }; //saving length,height,position and color

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << rectFileName;
		return;
	}
	f.write(reinterpret_cast<char*>(&savingRect), sizeof(Rectangle));

	f.close();
}
void SavingImage::saveCircle()
{
	std::fstream f;
	if (ShapeSelector::shapes.circles.size() + ShapeSelector::shapes.triangles.size() <= 1)
	{
		f.open(circleFileName, std::ios::out | std::ios::binary);
		deleteAllShapes();
	}
	else
		f.open(circleFileName, std::ios::app | std::ios::binary);

	sf::CircleShape circle;
	if (ShapeSelector::movingShape == ShapeType::Triangle)
	{
		circle = ShapeSelector::shapes.triangles.back();
	}
	else
	{
		circle = ShapeSelector::shapes.circles.back();
	}

	savingCircle = { circle.getPosition().x, circle.getPosition().y, circle.getRotation(), circle.getRadius(), circle.getFillColor().r, circle.getFillColor().g, circle.getFillColor().b, circle.getPointCount() };
	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << circleFileName;
		return;
	}
	f.write(reinterpret_cast<char*>(&savingCircle), sizeof(Circle));

	f.close();
}
void SavingImage::savePolygon()
{

	std::fstream f;
	auto& polygon = ShapeSelector::shapes.polygons.back();
	if (!polygon.isFinished)
	{
		std::cout << "ERROR SAVING! CANT SAVE UNFINISHED POLYGONS!!!\n";
		return;
	}

	if (ShapeSelector::shapes.polygons.size() == 1)
	{
		f.open(polygonFileName, std::ios::out | std::ios::binary);
		deleteAllShapes();
	}
	else
		f.open(polygonFileName, std::ios::app | std::ios::binary);

	savingPolygon.pointCounter = polygon.points.size();
	f.write(reinterpret_cast<char*>(&savingPolygon.pointCounter), sizeof(savingPolygon.pointCounter));

	savingPolygon.r = polygon.polygonColor.r;
	savingPolygon.g = polygon.polygonColor.g;
	savingPolygon.b = polygon.polygonColor.b;

	f.write(reinterpret_cast<char*>(&savingPolygon.r), sizeof(savingPolygon.r));
	f.write(reinterpret_cast<char*>(&savingPolygon.g), sizeof(savingPolygon.g));
	f.write(reinterpret_cast<char*>(&savingPolygon.b), sizeof(savingPolygon.b));

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << polygonFileName;
		return;
	}
	for (int i = 0; i < savingPolygon.pointCounter; i++)
	{
		savingPolygon.posX[i] = polygon.points[i].getPosition().x;
		savingPolygon.posY[i] = polygon.points[i].getPosition().y;

		f.write(reinterpret_cast<char*>(&savingPolygon.posX[i]), sizeof(savingPolygon.posX[i]));
		f.write(reinterpret_cast<char*>(&savingPolygon.posY[i]), sizeof(savingPolygon.posY[i]));
	}

	f.close();
}
void SavingImage::saveOrder()
{
	std::fstream f;
	f.open(shapeOrderFileName, std::ios::app | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << shapeOrderFileName;
		return;
	}

	auto& type = ShapeSelector::allShapeTypes.back();

	switch (type)
	{
		case ShapeType::Rectangle:
			savingOrder = 'r';
			break;

		case ShapeType::Circle:
			savingOrder = 'c';
			break;

		case ShapeType::Triangle:
			savingOrder = 't';
			break;

		case ShapeType::Polygon:
			savingOrder = 'p';
			break;

		default:
			break;
	}
	f.write(reinterpret_cast<char*>(&savingOrder), sizeof(savingOrder));
	f.close();
}
void SavingImage::deleteAllShapes()
{
	std::fstream temp;

	if (ShapeSelector::allShapeTypes.size() == 1)
	{
		temp.open(shapeOrderFileName, std::ios::out | std::ios::trunc | std::ios::binary);
		temp.close();
	}
	if (ShapeSelector::shapes.polygons.size() == 0)
	{
		temp.open(polygonFileName, std::ios::out | std::ios::trunc | std::ios::binary);
		temp.close();
	}
	if (ShapeSelector::shapes.rectangles.size() == 0)
	{
		temp.open(rectFileName, std::ios::out | std::ios::trunc | std::ios::binary);
		temp.close();
	}
	if (ShapeSelector::shapes.circles.size() + ShapeSelector::shapes.triangles.size() == 0)
	{
		temp.open(circleFileName, std::ios::out | std::ios::trunc | std::ios::binary);
		temp.close();
	}
}
void SavingImage::loadRectangle(sf::RenderWindow& window, int shapeToSave)
{
	std::ifstream f;
	if (shapeToSave == 1)
		f.open(rectFileName, std::ios::in | std::ios::binary);
	else
		f.open(image2Prefix + rectFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	while (f.tellg() < fileSize)
	{
		Rectangle currRect;
		f.read(reinterpret_cast<char*>(&currRect), sizeof(currRect));

		sf::RectangleShape loadRect(sf::Vector2f(currRect.length, currRect.height));
		loadRect.setRotation(currRect.rotation);
		loadRect.setOrigin(sf::Vector2f(currRect.length / 2.f, currRect.height / 2.f));
		loadRect.setPosition(sf::Vector2f(currRect.posX, currRect.posY));
		loadRect.setFillColor(sf::Color(currRect.r, currRect.g, currRect.b));

		if (shapeToSave == 2)
		{

			ShapeSelector::shapes2.rectangles.push_back(loadRect);
		}
		else
		{

			ShapeSelector::shapes.rectangles.push_back(loadRect);
		}
	}

	f.close();
}
void SavingImage::loadCircle(sf::RenderWindow& window, int shapeToSave)
{
	std::ifstream f;
	if (shapeToSave == 1)
		f.open(circleFileName, std::ios::in | std::ios::binary);
	else
		f.open(image2Prefix + circleFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	while (f.tellg() < fileSize)
	{
		Circle currCircle;
		f.read(reinterpret_cast<char*>(&currCircle), sizeof(currCircle));

		sf::CircleShape newCircle(currCircle.radius);
		newCircle.setOrigin(currCircle.radius, currCircle.radius);
		newCircle.setRotation(currCircle.rotation);
		newCircle.setPosition(sf::Vector2f(currCircle.posX, currCircle.posY));
		newCircle.setPointCount(currCircle.pointCount);
		newCircle.setFillColor(sf::Color(currCircle.r, currCircle.g, currCircle.b));

		if (shapeToSave == 2)
		{
			if (newCircle.getPointCount() == 3)
				ShapeSelector::shapes2.triangles.push_back(newCircle);
			else
				ShapeSelector::shapes2.circles.push_back(newCircle);
		}
		else
		{
			if (newCircle.getPointCount() == 3)
				ShapeSelector::shapes.triangles.push_back(newCircle);
			else
				ShapeSelector::shapes.circles.push_back(newCircle);
		}
	}

	f.close();
}
void SavingImage::loadPolygon(sf::RenderWindow& window, int shapeToSave)
{
	std::ifstream f;
	if (shapeToSave == 1)
		f.open(polygonFileName, std::ios::in | std::ios::binary);
	else
		f.open(image2Prefix + polygonFileName, std::ios::in | std::ios::binary);

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	thisPolygon currPolygon;

	while (f.tellg() < fileSize)
	{
		Polygon poly;
		f.read(reinterpret_cast<char*>(&currPolygon.pointCounter), sizeof(currPolygon.pointCounter));

		f.read(reinterpret_cast<char*>(&currPolygon.r), sizeof(currPolygon.r));
		f.read(reinterpret_cast<char*>(&currPolygon.g), sizeof(currPolygon.g));
		f.read(reinterpret_cast<char*>(&currPolygon.b), sizeof(currPolygon.b));

		poly.polygonColor = sf::Color(currPolygon.r, currPolygon.g, currPolygon.b);

		poly.isFinished = true;
		for (int i = 0; i < currPolygon.pointCounter; i++)
		{
			f.read(reinterpret_cast<char*>(&currPolygon.posX[i]), sizeof(currPolygon.posX[i]));
			f.read(reinterpret_cast<char*>(&currPolygon.posY[i]), sizeof(currPolygon.posY[i]));

			poly.addPoint(window, { currPolygon.posX[i], currPolygon.posY[i] });
		}
		poly.drawLastLine(window);

		if (shapeToSave == 2)
			ShapeSelector::shapes2.polygons.push_back(poly);
		else
			ShapeSelector::shapes.polygons.push_back(poly);
	}

	f.close();
}
void SavingImage::loadOrder()
{

	if (ShapeSelector::allShapeTypes.size() != 0)
		return;

	std::fstream f;
	f.open(shapeOrderFileName, std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "ERROR LOADING " << shapeOrderFileName;
		return;
	}

	int fileSize = 0;

	f.seekg(0, std::ios::end);
	fileSize = f.tellg();
	f.seekg(0, std::ios::beg);

	while (f.tellg() < fileSize)
	{
		char type;
		f.read(reinterpret_cast<char*>(&type), sizeof(type));

		switch (type)
		{
			case 'r':
				ShapeSelector::allShapeTypes.push_back(ShapeType::Rectangle);
				break;

			case 'c':
				ShapeSelector::allShapeTypes.push_back(ShapeType::Circle);
				break;

			case 't':
				ShapeSelector::allShapeTypes.push_back(ShapeType::Triangle);
				break;

			case 'p':
				ShapeSelector::allShapeTypes.push_back(ShapeType::Polygon);
				break;

			default:
				break;
		}
	}
	f.close();
}

//second image
void SavingImage::saveSecondImage()
{
	image2SaveRectangle();
	image2SaveCircle();
	image2SavePolygon();
}
void SavingImage::image2SaveRectangle()
{
	std::fstream f;
	f.open(image2Prefix + rectFileName, std::ios::out | std::ios::trunc | std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "ERROR SAVING " << rectFileName;
		return;
	}

	for (auto& rect : ShapeSelector::shapes2.rectangles)
	{																																															  //auto& rect = ShapeSelector::shapes.rectangles.back();
		savingRect = { rect.getSize().x, rect.getSize().y, rect.getPosition().x, rect.getPosition().y, rect.getRotation(), rect.getFillColor().r, rect.getFillColor().g, rect.getFillColor().b }; //saving length,height,position and color

		f.write(reinterpret_cast<char*>(&savingRect), sizeof(Rectangle));
	}
	f.close();
}
void SavingImage::image2SaveCircle()
{
	std::fstream f;

	f.open(image2Prefix + circleFileName, std::ios::out | std::ios::trunc | std::ios::binary);

	for (auto& circle : ShapeSelector::shapes2.circles)
	{
		savingCircle = { circle.getPosition().x, circle.getPosition().y, circle.getRotation(), circle.getRadius(), circle.getFillColor().r, circle.getFillColor().g, circle.getFillColor().b, circle.getPointCount() };
		f.write(reinterpret_cast<char*>(&savingCircle), sizeof(savingCircle));
	}
	for (auto& triangle : ShapeSelector::shapes2.triangles)
	{
		savingCircle = { triangle.getPosition().x, triangle.getPosition().y, triangle.getRotation(), triangle.getRadius(), triangle.getFillColor().r, triangle.getFillColor().g, triangle.getFillColor().b, triangle.getPointCount() };
		f.write(reinterpret_cast<char*>(&savingCircle), sizeof(savingCircle));
	}
	f.close();
}
void SavingImage::image2SavePolygon()
{
	std::fstream f;
	f.open(image2Prefix + polygonFileName, std::ios::out | std::ios::trunc | std::ios::binary);

	for (auto& polygon : ShapeSelector::shapes2.polygons)
	{
		savingPolygon.pointCounter = polygon.points.size();
		f.write(reinterpret_cast<char*>(&savingPolygon.pointCounter), sizeof(savingPolygon.pointCounter));

		savingPolygon.r = polygon.polygonColor.r;
		savingPolygon.g = polygon.polygonColor.g;
		savingPolygon.b = polygon.polygonColor.b;

		f.write(reinterpret_cast<char*>(&savingPolygon.r), sizeof(savingPolygon.r));
		f.write(reinterpret_cast<char*>(&savingPolygon.g), sizeof(savingPolygon.g));
		f.write(reinterpret_cast<char*>(&savingPolygon.b), sizeof(savingPolygon.b));

		if (!f.is_open())
		{
			std::cout << "ERROR SAVING " << polygonFileName;
			return;
		}
		for (int i = 0; i < savingPolygon.pointCounter; i++)
		{
			savingPolygon.posX[i] = polygon.points[i].getPosition().x;
			savingPolygon.posY[i] = polygon.points[i].getPosition().y;

			f.write(reinterpret_cast<char*>(&savingPolygon.posX[i]), sizeof(savingPolygon.posX[i]));
			f.write(reinterpret_cast<char*>(&savingPolygon.posY[i]), sizeof(savingPolygon.posY[i]));
		}
	}
	f.close();
}

bool SavingImage::areAllFilesTheSameSize()
{
	return compareFilesSize(rectFileName) && compareFilesSize(circleFileName) && compareFilesSize(polygonFileName);
}
bool SavingImage::compareFilesSize(std::string fileName)
{
	std::fstream f1;
	std::fstream f2;

	f1.open(fileName, std::ios::in | std::ios::binary);
	f2.open(image2Prefix + fileName, std::ios::in | std::ios::binary);

	f1.seekg(0, std::ios::end);
	int f1Size = f1.tellg();
	f1.seekg(0, std::ios::beg);

	f2.seekg(0, std::ios::end);
	int f2Size = f2.tellg();
	f2.seekg(0, std::ios::beg);

	f1.close();
	f2.close();

	if (f1Size != f2Size)
		return false;

	return true;
}
}