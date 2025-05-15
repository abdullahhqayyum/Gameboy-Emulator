#include "DifficultyMenu.h"
#include "GameBoy.h"
#include "PlayOrInstructionsMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

DifficultyMenu::DifficultyMenu(GameBoy* gameboy, const string& gameName) : gameboy(gameboy), gameName(gameName)
{
    addMenuItem("Easy");
    addMenuItem("Medium");
    addMenuItem("Hard");
    addMenuItem("Back");
}
void DifficultyMenu::displayMenu(RenderWindow& window)
{
	window.clear(Color(150, 150, 250));
	render(window);

	if (font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf"))
	{
		Text header("Select Difficulty for \n" + gameName, font, 30);
		header.setFillColor(Color::White);
		header.setPosition(50, 50);
		window.draw(header);
	}
}
void DifficultyMenu::handleInput(Event& event)
{
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
            navigateMenu(-1);
        }
        else if (event.key.code == Keyboard::Down) {
            navigateMenu(1);
        }
        else if (event.key.code == Keyboard::Enter) {
            if (selectedOption == 0) {
                gameboy->startGame(gameName, "Easy");
            }
            else if (selectedOption == 1) {
                gameboy->startGame(gameName, "Medium");
            }
            else if (selectedOption == 2) {
                gameboy->startGame(gameName, "Hard");
            }
            else if (selectedOption == 3) {
                gameboy->setMenu(new PlayOrInstructionsMenu(gameboy, gameName));
            }
        }
    }
}
