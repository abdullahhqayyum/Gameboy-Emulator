#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class HangmanFigure
{
private:
	int wrongGuesses;
	Sprite hangmanBody[7];
	Texture hangmanTexture[7];
public:
	HangmanFigure();
	void reset();
	void updateLives(int wrongGuesses);
	void draw(RenderWindow& window);

};

