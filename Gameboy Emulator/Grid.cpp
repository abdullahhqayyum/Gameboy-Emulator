#include "Grid.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Grid::Grid() : height(0), width(0), cellSize(0) {}

Grid::Grid(int x, int y, int cellSize)
    : width(x), height(y + 1), cellSize(cellSize)
{
    if (x * cellSize > 800) width = 800 / cellSize;
    if (y * cellSize > 600) height = 600 / cellSize;
}

int Grid::getX() {
    return width;
}

int Grid::getY() {
    return height;
}

int Grid::getCellSize() const {
    return cellSize;
}

bool Grid::isEdge(int x, int y) {
    return x == 0 || y == 0 || x == width - 1 || y == height - 1;
}

void Grid::setX(int x) {
    width = x;
}

void Grid::setY(int y) {
    height = y + 1;
}

void Grid::shrinkGrid(int amount) {
    if (width > amount * 2 && height > amount * 2) {
        width -= amount * 2;
        height -= amount * 2;
    }
}

void Grid::renderBoundary(RenderWindow& window, const Texture& boundaryTexture) {
    Sprite boundarySprite;
    boundarySprite.setTexture(boundaryTexture);

    float scaleX = static_cast<float>(cellSize) / boundaryTexture.getSize().x;
    float scaleY = static_cast<float>(cellSize) / boundaryTexture.getSize().y;

    for (int x = 0; x < width; ++x) {
        boundarySprite.setScale(scaleX, scaleY);
        boundarySprite.setPosition(x * cellSize, 0);
        window.draw(boundarySprite);
    }

    for (int x = 0; x < width; ++x) {
        boundarySprite.setScale(scaleX, scaleY);
        boundarySprite.setPosition(x * cellSize, (height ) * cellSize);
        window.draw(boundarySprite);
    }

    for (int y = 0; y < height; ++y) {
        boundarySprite.setScale(scaleX, scaleY);
        boundarySprite.setPosition(0, y * cellSize);
        window.draw(boundarySprite);
    }

    for (int y = 0; y < height; ++y) {
        boundarySprite.setScale(scaleX, scaleY);
        boundarySprite.setPosition((width - 1) * cellSize, y * cellSize);
        window.draw(boundarySprite);
    }
}
