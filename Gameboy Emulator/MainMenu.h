#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include"GameBoy.h"
#include <iostream>
using namespace std;
using namespace sf;

class MainMenu : public Menu {
private:
    GameBoy* gameboy;

public:
    MainMenu(GameBoy* gameboy);
    void displayMenu(RenderWindow& window) override; 
    void handleInput(Event& event) override; 
};
