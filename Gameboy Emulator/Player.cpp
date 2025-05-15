#include "Player.h"
#include<iostream>
#include<fstream>
using namespace std;
Player::Player()
{
	name = " ";
	highScore = 0;
	acheivements = 0;
}
Player::Player(const string& n, int hs, int a)
{
	name = n;
	highScore = hs;
	acheivements = a;
}

string Player::getName()
{
	return name;
}
int Player::getHighScore()
{
	return highScore;
}
int Player::getAcheivements()
{
	return acheivements;
}
void Player::setName(string n)
{
	name = n;
}
void Player::setHighScore(int hs)
{
	if (hs > highScore)
	{
		highScore = hs;
	}
}
void Player::addAcheivements()
{
	acheivements++;
}
void Player::resetProgress()
{
	highScore = 0;
	acheivements = 0;
}
void Player::saveInFile()
{
	ofstream file;
	file.open("player.txt");
	file << name << endl;
	file << highScore << endl;
	file << acheivements << endl;
	file.close();
}
void Player::loadFromFile()
{
	ifstream file;
	file.open("player.txt");
	file >> name;
	file >> highScore;
	file >> acheivements;
	file.close();
}