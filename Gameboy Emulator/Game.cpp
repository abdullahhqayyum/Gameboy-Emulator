#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
Game::Game(const string& name, Leaderboard* leaderboard): name(name), score(0), leaderboard(leaderboard) {}
Game::~Game()
{
	name = "";
	score = 0;
}
int Game:: getScore()
{
	return score;
}
string Game::getName()
{
	return name;
}
void Game::updateScore(int newScore)
{
	score = newScore;
}
void Game::addScore(int newScore)
{
	score += newScore;
}

Leaderboard* Game::getLeaderboard()
{
	return leaderboard;
}