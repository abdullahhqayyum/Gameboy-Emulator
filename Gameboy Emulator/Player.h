#pragma once
using namespace std;
#include<iostream>
class Player
{
private:
	string name;
	int highScore;
	int acheivements;
public:
	Player();
	Player(const string& n, int hs, int a);
	string getName();
	int getHighScore();
	int getAcheivements();
	void setName(string n);
	void setHighScore(int hs);
	void addAcheivements();
	void saveInFile();
	void loadFromFile();
	void resetProgress();



};

