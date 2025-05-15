#include "PlayOrInstructionsMenu.h"
#include "GameBoy.h"
#include "Leaderboard.h"
#include "DifficultyMenu.h"
#include "SelectGameMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;
PlayOrInstructionsMenu::PlayOrInstructionsMenu(GameBoy* gameboy, const string& gameName):gameboy(gameboy), gameName(gameName)
{
	addMenuItem("Play");
	addMenuItem("Instructions");
    addMenuItem("Leaderboard");
	addMenuItem("Back");
}
void PlayOrInstructionsMenu::displayMenu(RenderWindow& window)
{
	window.clear(Color(100, 100, 200));
	render(window);
	Font font;
	if (font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf"))
	{
		Text gameHeader("Game: " + gameName, font, 30);
		gameHeader.setFillColor(Color::White);
		gameHeader.setPosition(50, 50);
		window.draw(gameHeader);
	}
}
void PlayOrInstructionsMenu::handleInput(Event& event) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up) {
            navigateMenu(-1); // Move up in the menu
        }
        else if (event.key.code == Keyboard::Down) {
            navigateMenu(1); // Move down in the menu
        }
        else if (event.key.code == Keyboard::Enter) {
            if (selectedOption == 0) { // Play
                cout << "Transitioning to Difficulty Menu for " << gameName << endl;
                gameboy->setMenu(new DifficultyMenu(gameboy, gameName));
            }
            else if (selectedOption == 1) { // View Instructions
                cout << "Showing Instructions for " << gameName << endl;

                // Create a new window for instructions
                RenderWindow instructionsWindow(VideoMode(800, 600), "Instructions - " + gameName);
                Font font;
                if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
                    cerr << "Failed to load font!" << endl;
                    return;
                }

                // Instructions loop
                while (instructionsWindow.isOpen()) {
                    Event instEvent;
                    while (instructionsWindow.pollEvent(instEvent)) {
                        if (instEvent.type == Event::Closed) {
                            instructionsWindow.close(); // Close the window when done
                        }
                        if (instEvent.type == Event::KeyPressed && instEvent.key.code == Keyboard::Enter) {
                            // When "Enter" is pressed, go back to the PlayOrInstructionsMenu
                            instructionsWindow.close(); // Close instructions window
                            gameboy->setMenu(new PlayOrInstructionsMenu(gameboy, gameName)); // Go back to menu
                        }
                    }

                    // Clear and display instructions
                    instructionsWindow.clear(Color(100, 100, 200)); // Background color
                    Text instructionsText("Instructions: \n 1. Use arrow keys to move \n 2. Don't hit the walls \n 3. Don't hit yourself", font, 20);
                    instructionsText.setFillColor(Color::White);
                    instructionsText.setPosition(50, 100);
                    if (gameName == "Snake Game") {
                        instructionsText.setString(
                            "Instructions: \n"
                            "1. Use arrow keys to move.\n"
                            "2. Avoid hitting the walls.\n"
                            "3. Don't run into yourself."
                        );
                    }
                    else if (gameName == "Hangman Game") {
                        instructionsText.setString(
                            "Instructions: \n"
                            "1. Guess the secret word letter by letter.\n"
                            "2. Use hints if available (depends on difficulty).\n"
                            "3. Avoid exceeding the allowed number of wrong guesses."
                        );
                    }
                    instructionsWindow.draw(instructionsText);

                    Text backButtonText("Press Enter to go back", font, 20);
                    backButtonText.setFillColor(Color::White);
                    backButtonText.setPosition(50, 300);  // Position the Back button text below the instructions
                    instructionsWindow.draw(backButtonText);

                    instructionsWindow.display();
                }
            }
            else if (selectedOption == 2)
            { // Leaderboard
                RenderWindow leaderboardWindow(VideoMode(800, 600), "Leaderboard - " + gameName);
                displayLeaderboard(leaderboardWindow);
            }
            else if (selectedOption == 3)
            { // Back
                gameboy->setMenu(new SelectGameMenu(gameboy));
            }
        }
    }
}
void PlayOrInstructionsMenu::displayLeaderboard(RenderWindow& window) {
    // Load font
    Font font;
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    // Create a new window for the leaderboard
    RenderWindow leaderboardWindow(VideoMode(800, 600), "Leaderboard - " + gameName);

    while (leaderboardWindow.isOpen()) {
        Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == Event::Closed ||
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)) {
                leaderboardWindow.close(); // Exit leaderboard view on Enter key or window close
            }
        }

        leaderboardWindow.clear(Color(50, 50, 50)); 

        // Display the leaderboard title
        Text title("Leaderboard - " + gameName, font, 30);
        title.setFillColor(Color::Yellow);
        title.setPosition(50, 20);
        leaderboardWindow.draw(title);

        Leaderboard& leaderboard = gameboy->getLeaderboard();
        leaderboard.sort(gameName); 

        Leaderboard::Entry entries[10];
        int entryCount = leaderboard.getEntries(gameName, entries, 10); 

        // Display leaderboard entries
        float yPosition = 100.0f;
        for (int i = 0; i < entryCount; i++) {
            Text entryText(entries[i].playerName + " - " + to_string(entries[i].score), font, 20);
            entryText.setFillColor(Color::White);
            entryText.setPosition(50, yPosition);
            leaderboardWindow.draw(entryText);
            yPosition += 30.0f;
        }

        // Display "Back" message
        Text backButton("Press Enter to go back", font, 20);
        backButton.setFillColor(Color::White);
        backButton.setPosition(50, leaderboardWindow.getSize().y - 50);
        leaderboardWindow.draw(backButton);

        leaderboardWindow.display();
    }
}
