#include "SelectGameMenu.h"
#include "GameBoy.h"
#include <iostream>
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include "PlayOrInstructionsMenu.h"
#include "HangmanGame.h" 

using namespace std;
using namespace sf;

SelectGameMenu::SelectGameMenu(GameBoy* gameboy) : gameboy(gameboy) {
    addMenuItem("Snake Game");
    addMenuItem("Hangman Game");  
    addMenuItem("Wordle Game");
    addMenuItem("Back to Main Menu");
}

void SelectGameMenu::handleInput(Event& event) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
            navigateMenu(-1); // Move up
        }
        else if (event.key.code == Keyboard::Down) {
            navigateMenu(1); // Move down
        }
        else if (event.key.code == Keyboard::Enter) {
            if (selectedOption == 0) {
                cout << "Starting Snake Game..." << endl;
                gameboy->setMenu(new PlayOrInstructionsMenu(gameboy, "Snake Game"));
            }
            else if (selectedOption == 1) {
                cout << "Starting Hangman Game..." << endl;
                // Transition to Hangman Game, passing the gameboy to the menu
                gameboy->setMenu(new PlayOrInstructionsMenu(gameboy, "Hangman Game"));
            }
            else if (selectedOption == 2) {
				cout << "Starting Wordle Game..." << endl;
				gameboy->setMenu(new PlayOrInstructionsMenu(gameboy, "Wordle Game"));
			}
            else if (selectedOption == 3) {
                // Transition back to Main Menu
                cout << "Returning to Main Menu..." << endl;
                gameboy->setMenu(new MainMenu(gameboy));
            }
        }
    }
}

void SelectGameMenu::displayMenu(RenderWindow& window) {
    window.clear(Color(50, 50, 150));
    Sprite bgSprite;
    Texture bgTexture;
    if (bgTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/selectbg.png")) {
		bgSprite.setTexture(bgTexture);
		window.draw(bgSprite);
	}
    Menu::render(window); 

}
