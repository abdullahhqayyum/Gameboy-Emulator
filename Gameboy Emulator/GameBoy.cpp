#include "GameBoy.h"
#include "MainMenu.h"
#include <iostream>
#include "Game.h"
#include "SnakeGame.h"
#include "HangmanGame.h"
#include "WordleGame.h"
#include<ctime>
#include<iostream>
using namespace std;
#include<cstdlib>
using namespace sf;
using namespace std;


GameBoy::GameBoy(const string& title, int width, int height)
    : window(VideoMode(width, height), title), currentMenu(nullptr), currentGame(nullptr), currentPlayer(nullptr)
{
    string leaderboardFile = "C:/Semester 3/OOP/oopProject/oopProject/leaderboard.txt"; 
    leaderboard.loadFromFile(leaderboardFile); 
    cout << "Leaderboard loaded from file: " << leaderboardFile << endl;

    window.create(VideoMode(width, height), title);
    if (!window.isOpen()) {
        cerr << "Error: Failed to create window!" << endl;
    }
    window.setFramerateLimit(60);

    makeMenus("MAIN_MENU");
    cout << "GameBoy initialized with MAIN_MENU." << endl;
}

GameBoy::~GameBoy() {
    if (currentMenu) {
        delete currentMenu;
    }
    if (currentGame)
    {
        delete currentGame;
	
    }
    if (currentPlayer)
	{
		delete currentPlayer;
	}
}

void GameBoy::makeMenus(const string& menuType) {
    if (currentMenu) {
        delete currentMenu;
    }

    if (menuType == "MAIN_MENU") {
        currentMenu = new MainMenu(this);
    }
    else {
        cerr << "Error: Unknown menu type '" << menuType << "'!" << endl;
        currentMenu = new MainMenu(this);
    }
}

void GameBoy::setMenu(Menu* menu) {
    if (currentMenu) {
        delete currentMenu;
    }
    currentMenu = menu;
}

void GameBoy::setPlayer(const string& n) {
    if (currentPlayer)
    {
        delete currentPlayer;
    }
    currentPlayer = new Player(n, 0, 0);
}
void GameBoy::updatePlayerScore(int score) {
	if (currentPlayer) 
    {
        if (score > currentPlayer->getHighScore())
        {
            currentPlayer->setHighScore(score);
        }
    }
}
void GameBoy::startGame(const string& gameName, const string& difficulty) {
    if (currentGame) {
        delete currentGame;
    }

    if (gameName == "Snake Game") {
        currentGame = new SnakeGame (difficulty, &leaderboard, currentPlayer->getName());
    }
    else if (gameName == "Hangman Game") {
        currentGame = new HangmanGame(difficulty, &leaderboard, currentPlayer->getName());
    }

 else if (gameName == "Wordle Game") {
     currentGame = new WordleGame(difficulty, &leaderboard);
    }

   
    else
    {
        return;
    }
    
  
    if (currentGame) {
        currentGame->startGame();
    }
}

void GameBoy::start() {
    srand(time(0));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) 
            {
                shutDown();
            }

            if (currentMenu) {
                currentMenu->handleInput(event);
            }
        }

        window.clear(Color::Black);
        if (currentMenu) {
            currentMenu->displayMenu(window);
        }
        window.display();
    }
}
Player* GameBoy::getPlayer()
{
	return currentPlayer;
}
RenderWindow& GameBoy::getWindow() {
	return window;
}

void GameBoy::shutDown() {
    cout << "Shutting down GameBoy." << endl;
    window.close();
}
Leaderboard& GameBoy::getLeaderboard() {
	return leaderboard;
}