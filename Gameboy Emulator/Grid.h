#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Grid
{
private:
	int height;
	int width;
	int cellSize;
public:
	Grid();
	Grid(int x, int y, int cellSize);
	int getX();
	int getY();
	int getCellSize() const;
	void setX(int x);
	void setY(int y);
	void shrinkGrid(int amount);
	bool isEdge(int x, int y);
	void renderBoundary(RenderWindow& window, const Texture& boundary);
};

