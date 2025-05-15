#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "GameBoy.h"
#include "Leaderboard.h"
#include <iostream>
using namespace std;
using namespace sf;
class PlayOrInstructionsMenu : public Menu
{
private: 
	GameBoy* gameboy;
	string gameName;
	//void displayLeaderboard(RenderWindow& window);
public:
	PlayOrInstructionsMenu(GameBoy* gameboy, const string& gameName);
	void displayMenu(RenderWindow& window) override;
	void displayLeaderboard(RenderWindow& window);
	void handleInput(Event& event) override;
};

