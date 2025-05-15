#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "GameBoy.h"
#include <iostream>
using namespace std;
using namespace sf;

class PlayerNameMenu : public Menu
{
private:
	GameBoy* gameboy;
	string playerName;
	Text inputText, promptText;
	Font font;
public:
	PlayerNameMenu(GameBoy* gameboy);
	void displayMenu(RenderWindow& window) override;
	void handleInput(Event& event) override;
	string getPlayerName();

};

