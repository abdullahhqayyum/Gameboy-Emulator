#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "GameBoy.h"
using namespace std;
using namespace sf;
class SelectGameMenu: public Menu
{
private:
	GameBoy* gameboy;
public:
		SelectGameMenu(GameBoy* gameboy);
		void displayMenu(RenderWindow& window) override;
		void handleInput(Event& event) override;
};

