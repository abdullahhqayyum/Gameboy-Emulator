#include "SnakeSegment.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
SnakeSegment::SnakeSegment() : x(0), y(0), size(32) {}

SnakeSegment::SnakeSegment(int x, int y) : x(x), y(y), size(32) {}

void SnakeSegment::setPos(int x, int y) {
    this->x = x;
    this->y = y;
    segment.setPosition(x * size, y * size); 
}

void SnakeSegment::move(int x, int y) {
    this->x += x;
    this->y += y;

   
    if (segment.getTexture() == nullptr) {
        std::cerr << "Error: Texture not loaded for segment!" << std::endl;
        return;
    }

    segment.setPosition(this->x * size, this->y * size); 
}

void SnakeSegment::setTexture(const sf::Texture& text) {
    if (!text.getSize().x || !text.getSize().y) {
        std::cerr << "Error: Invalid texture size!" << std::endl;
        return;
    }

    segmentTexture = text;
    segment.setTexture(segmentTexture); 
}


void SnakeSegment::render(sf::RenderWindow& window) {
    segment.setPosition(x * size, y * size); 
    window.draw(segment);
}

int SnakeSegment::getX() {
    return x;
}

int SnakeSegment::getY() {
    return y;
}

Sprite& SnakeSegment::getSprite()
{
    return segment;
}
