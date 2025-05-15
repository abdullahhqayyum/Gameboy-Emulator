#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
using namespace sf;
class SnakeSegment
{
private:
    int x, y;
    int size;
    Sprite segment;
    Texture segmentTexture;
public:
    SnakeSegment();
    SnakeSegment(int x, int y);
    void setTexture(const Texture& text);
    void setPos(int x, int y);
    void move(int x, int y);

    void render(RenderWindow& window);
    int getX();
    int getY();
    Sprite& getSprite();

};
