#include "MainMenu.h"
#include "SelectGameMenu.h"
#include "GameBoy.h"
#include "PlayerNameMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

MainMenu::MainMenu(GameBoy* gameboy): gameboy(gameboy) {
    addMenuItem("Play Game");
    addMenuItem("Exit");
    
}

void MainMenu::displayMenu(RenderWindow& window) {
    window.clear();
    Sprite bgSprite;
    Texture bgTexture;
    if (!bgTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/selectbg.png"))
    {
        cout << "Error loading mainbg.png" << endl;
    }
    else
    {
        bgSprite.setTexture(bgTexture);
        window.draw(bgSprite);

    }
    Font font;
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        cerr << "Error loading font!" << endl;
        return;
    }


    Text instructionsText("Use Arrow Keys to navigate and Enter to select.", font, 20);
    instructionsText.setStyle(Text::Bold);                  // Make text bold
    instructionsText.setOutlineColor(Color::Black);         // Set outline color to black
    instructionsText.setOutlineThickness(2);                // Set outline thickness
    instructionsText.setFillColor(Color::Yellow);           // Set fill color
    instructionsText.setPosition(10, 420);                  // Position instructions text
    window.draw(instructionsText);                          // Draw instructions text

    // Create and display the "Made By" text
    Text madeByText("A Project By:\nAbdullah Qayyum (23I-0049)\nHuzaifa Mazari (23I-0675)", font, 20);
    madeByText.setStyle(Text::Bold);                        // Make text bold
    madeByText.setOutlineColor(Color::Black);               // Set outline color to black
    madeByText.setOutlineThickness(2);                      // Set outline thickness
    madeByText.setFillColor(Color::Yellow);                 // Set fill color
    madeByText.setPosition(50, 450);                        // Position "Made By" text below instructions
    window.draw(madeByText);                                // Draw "Made By" text

    render(window); // Call base class render function
}

void MainMenu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            navigateMenu(-1);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            navigateMenu(1);
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) { // Play Games
                gameboy->setMenu(new PlayerNameMenu(gameboy)); // Transition to PlayerNameMenu
            }
            else if (selectedOption == 1) { // Exit
                gameboy->shutDown();
            }
        }
    }
}
