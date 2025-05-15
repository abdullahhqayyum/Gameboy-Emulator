#pragma once
#include "HangmanFigure.h"
#include "Category.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class HangmanGame : public Game
{
private:
	string secretWord;
	string guessedWord;
	string incorrectGuesses;
	int maxLives;
	int hints;
	string difficulty;
	Category* category;
	HangmanFigure hangmanFigure;
	Font font;
	Text scoreText, livesText, hintText;
	Sprite bgSprite;
	Texture bgTexture;
	string playerName;
	Leaderboard* leaderboard;

public:
	HangmanGame(const string& difficulty, Leaderboard* leaderboard, const string& playerName);
	
	void trackGuesses(char word);
	int manageLives();
	void useHint();
	string& getGuessedWord();
	string& getIncorrectGuesses();
	string selectCategory(RenderWindow& window);
void startGame() override;
	void endGame(RenderWindow& window, string c) override;
	void render(RenderWindow& window) override;

	
};

