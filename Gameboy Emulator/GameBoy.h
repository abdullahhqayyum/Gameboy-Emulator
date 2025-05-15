#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "Game.h"
#include "Player.h"
using namespace std;
using namespace sf;
class GameBoy {
private:
     RenderWindow window;
    Menu* currentMenu;
    Game* currentGame;
    Player* currentPlayer;
    Leaderboard leaderboard;
    string playerName;
public:
    GameBoy(const string& title, int width, int height);
    ~GameBoy();
    void makeMenus(const string& menuType);
    void setMenu(Menu* menu);
    void start();
    void startGame(const string& gameName, const string& difficulty);
    void shutDown();
    void setPlayer(const string& n);
    Player* getPlayer();
    void updatePlayerScore(int score);
    Leaderboard& getLeaderboard();
    RenderWindow& getWindow();
};