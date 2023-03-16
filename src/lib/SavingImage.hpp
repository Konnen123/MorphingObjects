//L FOR LOADING IMAGE, ENTER TO SAVE CURRENT SHAPE(LOADING WORKS WHEN IMAGE HAS NO SHAPE DRAWN)
//DRAWING ANY SHAPE WILL DELETE THE SAVED ONE

namespace my
{
struct Rectangle
{
	float length, height, posX, posY, rotation;
	int r, g, b;
};
struct Circle
{
	float posX, posY, rotation;
	int radius, r, g, b, pointCount;
};
struct thisPolygon
{
	int r, g, b;
	int pointCounter, posX[50], posY[50]; // din pacate nu putem stoca std::vectori in fisiere binare 😞
};

class SavingImage
{
private:
	static void saveRectangle();
	static void saveCircle();
	static void saveOrder();
	static void loadRectangle(sf::RenderWindow& window, int shapeToSave);
	static void loadCircle(sf::RenderWindow& window, int shapeToSave);
	static void loadPolygon(sf::RenderWindow& window, int shapeToSave);
	static void loadOrder();
	static bool compareFilesSize(std::string fileName);

	static void image2SaveRectangle();
	static void image2SaveCircle();
	static void image2SavePolygon();

	static void deleteAllShapes();

	static Rectangle savingRect;
	static Circle savingCircle;
	static thisPolygon savingPolygon;
	static char savingOrder;

public:
	static void saveColorPalette(int index);
	static void loadColorPalette();
	static void savePolygon();
	static void saveAllShapes();
	static void saveSecondImage();
	static bool areAllFilesTheSameSize();

	static void loadAllShapes(sf::RenderWindow& window, int shapeToSave);
};

}