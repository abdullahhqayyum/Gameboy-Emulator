#include "PlayerNameMenu.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include "SelectGameMenu.h"
#include <string>
using namespace std;
using namespace sf;

PlayerNameMenu::PlayerNameMenu(GameBoy* gameboy) : gameboy(gameboy), playerName("")
{
	
	if(!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf"))
	{
		cout << "Error loading font" << endl;
	}
    promptText.setFont(font);
    promptText.setString("Enter Player Name:");
    promptText.setCharacterSize(30);
    promptText.setFillColor(Color::White);
    promptText.setPosition(200, 200);

    // Input text
    inputText.setFont(font);
    inputText.setCharacterSize(25);
    inputText.setFillColor(Color::Yellow);
    inputText.setPosition(200, 250);
}

void PlayerNameMenu::handleInput(Event& event) {
    if (event.type == Event::TextEntered) {
        if (event.text.unicode == '\b') { 
            if (!playerName.empty()) {
                playerName.pop_back();
            }
        }
        else if (event.text.unicode == '\r') {
            if (!playerName.empty()) {
                gameboy->setPlayer(playerName); 
                gameboy->setMenu(new SelectGameMenu(gameboy)); 
            }
        }
        else if (playerName.size() < 15) { 
            playerName += static_cast<char>(event.text.unicode);
        }
    }
}

void PlayerNameMenu::displayMenu(RenderWindow& window) {
    window.clear(Color::Black);
    inputText.setString(playerName + (playerName.size() < 15 ? "_" : ""));

    window.draw(promptText);
    window.draw(inputText);
}

string PlayerNameMenu::getPlayerName()
{
	return playerName;
}