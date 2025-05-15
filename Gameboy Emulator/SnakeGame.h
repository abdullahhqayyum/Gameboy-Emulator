#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Point.h"
#include "SnakeSegment.h"
using namespace sf;
using namespace std;
class SnakeGame  : public Game
{
private:
    SnakeSegment* snakeBody;
    Point food;
    Grid grid;
    int snakeLength;
    int dx, dy;
    float* rotatingSegments;
    int capacity;
    bool win;
    Texture headTexture, bodyTexture, tailTexture, foodTexture, boundary, bgTexture;
    Sprite foodSprite, bgSprite;
    Font scoreFont;
    Text scoreText;
    Clock foodTimer;
    string difficulty;
    Clock shrinkTimer;
    string playerName;
    Leaderboard* leaderboard;

public:
    SnakeGame(const string& difficult, Leaderboard* leaderboard, const string& playerName);
    void startGame() override;
    void endGame(RenderWindow& window, string c) override;
    void render(RenderWindow& window) override;
    void updateScore(int newScore);
	void moveSnake();
	void changeDirection(int dx, int dy);
	void detectCollision(RenderWindow& window);
    void resetGame();
	void spawnFood();
	void increaseArraySize();
	virtual ~SnakeGame();
};

