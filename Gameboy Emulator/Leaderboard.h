#pragma once
#include <string>
using namespace std;
#include<iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace sf;

class Leaderboard
{
public:
	struct Entry
	{
		string playerName;
		string gameName;
		int score;
	};
private:
	Entry entries[10];
	int entryCount;
public:

	Leaderboard();
	void addEntry(const string& playerName, const string& gameName, int score);
	void loadFromFile(const string& filename);
	void saveToFile(const string& filename);
	void displayLeaderboard(RenderWindow& window, const string& gameName);
	void sort(const string& gameName);
	bool isEmpty();
	int getEntries(const string& gameName, Entry result[], int maxResults);
};

