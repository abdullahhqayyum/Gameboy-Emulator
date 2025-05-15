#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "GameBoy.h"
#include <iostream>
using namespace std;
using namespace sf;

class DifficultyMenu : public Menu
{
private:
	GameBoy* gameboy;
	string gameName;
public:
	DifficultyMenu(GameBoy* gameboy, const string& gameName);
	void displayMenu(RenderWindow& window) override;
	void handleInput(Event& event) override;
};

