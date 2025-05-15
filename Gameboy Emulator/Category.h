#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Category
{
private:
	string categoryName;
	static const int MAX_ITEMS = 10;
	string words[MAX_ITEMS];
	int numWords;
public:
	Category();
	Category(const string& categoryName);
	string getCategoryName(bool random);	
	int getNumWords();
	string getWord();
};

