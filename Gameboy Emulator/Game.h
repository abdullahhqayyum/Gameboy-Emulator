#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include "Leaderboard.h"
using namespace std;
using namespace sf;
class Game
{
protected:
	string name;
	int score;
	Leaderboard* leaderboard;
public:
	Game(const string& n, Leaderboard* leaderboard);
	virtual ~Game();
	virtual void startGame()=0;
	virtual void endGame(RenderWindow& window, string c)=0;
	virtual void render(RenderWindow& window)=0;
	string getName();
	int getScore();
	void updateScore(int newScore);
	void addScore(int newScore);
	Leaderboard* getLeaderboard();
	void displayLeaderboard(RenderWindow& window);

};

