#include "SnakeGame.h"
#include <iostream>
using namespace std;
using namespace sf;

SnakeGame::SnakeGame(const string& difficulty, Leaderboard* leaderboard, const string& playerName)
    : Game("Snake Game", leaderboard), difficulty(difficulty), playerName(playerName), leaderboard(leaderboard),
    food(5, 5), grid(25, 20, 32), snakeLength(1), dx(1), dy(0), capacity(10), win(false) {
    this->difficulty = difficulty;
    this->playerName=playerName;

    headTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/snakehead.png");
    bodyTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/snakebody.png");
    tailTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/snaketail.png");
    foodTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/food.png");

    snakeBody = new SnakeSegment[capacity];
    rotatingSegments = new float[capacity];

    snakeBody[0].setTexture(headTexture);
    snakeBody[0].setPos(10, 10);
    rotatingSegments[0] = 270;

    foodSprite.setTexture(foodTexture);
    foodSprite.setOrigin(
        foodTexture.getSize().x / 2.0f,
        foodTexture.getSize().y / 2.0f
    );
    spawnFood();

    if (!scoreFont.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        throw runtime_error("Failed to load font!");
    }

    
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");

    if (!bgTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/snakebg.png")) {
        throw runtime_error("Failed to load background image!");
    }
    bgSprite.setTexture(bgTexture);
    if(!boundary.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/boundary.png"))
	{
		throw runtime_error("Failed to load boundary image!");
	}
}


void SnakeGame::moveSnake()
{
    for (int i = snakeLength - 1; i > 0; i--) 
    {        snakeBody[i].setPos(snakeBody[i - 1].getX(), snakeBody[i - 1].getY());

        rotatingSegments[i] = rotatingSegments[i - 1];
        snakeBody[i].getSprite().setRotation(rotatingSegments[i]);

        snakeBody[i].setTexture(i < snakeLength - 1 ? bodyTexture : tailTexture);
    }

    snakeBody[0].move(dx, dy);

    // Update head rotation
    if (dx == 1 && dy == 0) rotatingSegments[0] = 270; // Right
    if (dx == -1 && dy == 0) rotatingSegments[0] = 90;  // Left
    if (dx == 0 && dy == -1) rotatingSegments[0] = 180; // Up
    if (dx == 0 && dy == 1) rotatingSegments[0] = 0;    // Down

    snakeBody[0].getSprite().setRotation(rotatingSegments[0]);

    snakeBody[0].setTexture(headTexture);
}

void SnakeGame::changeDirection(int newDx, int newDy) {
    if ((dx == 1 && newDx == -1) || (dx == -1 && newDx == 1) ||
        (dy == 1 && newDy == -1) || (dy == -1 && newDy == 1)) {
        return; // Prevent reversing direction
    }
    dx = newDx;
    dy = newDy;
}
void SnakeGame::spawnFood()
{
    bool collision;
    do {
        collision = false;
        // Randomly set food position within grid boundaries
        food.x = rand() % grid.getX(); // Use width (getX()) for horizontal limit
        food.y = rand() % grid.getY(); // Use height (getY()) for vertical limit

        if (food.x == 0 || food.x == grid.getX() - 1 ||
            food.y == 0 || food.y == grid.getY() - 1) {
            collision = true;
            continue; // Skip checking snake collision if position is invalid
        }

        // Check if food collides with snake's body
        for (int i = 0; i < snakeLength; i++) {
            if (snakeBody[i].getX() == food.x && snakeBody[i].getY() == food.y) {
                collision = true;
                break; // Food is invalid if it overlaps with the snake
            }
        }
    } while (collision);

    foodTimer.restart();
}
void SnakeGame::increaseArraySize()
{
    int newCapacity = capacity * 2;  // Double the capacity
    SnakeSegment* newSnakeBody = new SnakeSegment[newCapacity];  
    float* newRotatingSegments = new float[newCapacity];  // Create new array for rotating segments

    // Copy existing segments and rotations to the new arrays
    for (int i = 0; i < capacity; i++) {
        newSnakeBody[i] = snakeBody[i];
        newRotatingSegments[i] = rotatingSegments[i];
    }

    // Clean up old arrays
    delete[] snakeBody;
    delete[] rotatingSegments;

    // Update pointers and capacity
    snakeBody = newSnakeBody;
    rotatingSegments = newRotatingSegments;
    capacity = newCapacity;  // Update the capacity
}

void SnakeGame::detectCollision(RenderWindow& window)
{
    string cause;

   if (snakeBody[0].getX() < 0 ||
    snakeBody[0].getX() >= grid.getX() || // Right boundary remains the same
    snakeBody[0].getY() < 0 ||
    snakeBody[0].getY() > grid.getY()) { // Bottom boundary adjusted to allow one more block
    if (!win) {
        win = true;
        cause = "You hit the wall!";
        endGame(window, cause); // End the game
        resetGame(); // Reset game after death
    }
    return;
}



    // Check if snake ate itself
    for (int i = 1; i < snakeLength; i++) {
        if (snakeBody[0].getX() == snakeBody[i].getX() && snakeBody[0].getY() == snakeBody[i].getY()) {
            if (!win) {
                win = true;
                cause = "You ate yourself!";
                endGame(window, cause); 
                resetGame(); 
            }
            return;
        }
    }

    // Check if snake eats food
    if (snakeBody[0].getX() == food.x && snakeBody[0].getY() == food.y) {
        // Update score
        float spawnTime = foodTimer.getElapsedTime().asSeconds();
        if (spawnTime <= 3.0f && score != 0) {
            updateScore(score * 2);
        }
        else if (spawnTime <= 3.0f && score == 0) {
            updateScore(score + 20);
        }
        else {
            updateScore(score + 1);
        }

        // Increase snake length
        snakeLength++;

        // If snake exceeds capacity, resize
        if (snakeLength >= capacity) {
            increaseArraySize();
        }

        snakeBody[snakeLength - 1].setTexture(tailTexture);
        snakeBody[snakeLength - 1].setPos(
            snakeBody[snakeLength - 2].getX(),
            snakeBody[snakeLength - 2].getY()
        );
        rotatingSegments[snakeLength - 1] = rotatingSegments[snakeLength - 2];

        spawnFood(); // Spawn new food
    }
}

void SnakeGame::resetGame()
{
    // Reset the snake's position and size
    snakeLength = 1;
    dx = 1;
    dy = 0;
    score = 0;
    scoreText.setString("Score: 0");

    delete[] snakeBody;
    snakeBody = new SnakeSegment[capacity];
    rotatingSegments = new float[capacity];

    // Initialize the snake head
    snakeBody[0].setTexture(headTexture);
    snakeBody[0].setPos(10, 10);
    rotatingSegments[0] = 270;

    // Reset food
    spawnFood();
}

void SnakeGame::startGame()
{
    RenderWindow window(VideoMode(800, 600), "Snake Game");
    Clock clock;
    float moveInterval = 0;

    // Set move interval based on difficulty
    if (difficulty == "Easy") {
        moveInterval = 0.2f;
    }
    else if (difficulty == "Medium") {
        moveInterval = 0.1f;
    }
    else if (difficulty == "Hard") {
        moveInterval = 0.075f;
        shrinkTimer.restart();
    }

    // Start the game and reset if needed
    if (win) {
        resetGame(); // Reset the game if previously lost
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) changeDirection(0, -1);
                else if (event.key.code == Keyboard::Down) changeDirection(0, 1);
                else if (event.key.code == Keyboard::Left) changeDirection(-1, 0);
                else if (event.key.code == Keyboard::Right) changeDirection(1, 0);
            }
        }

        if (difficulty == "Hard" && shrinkTimer.getElapsedTime().asSeconds() >= 10) {
            grid.shrinkGrid(1);
            if (food.x < 0 || food.x >= grid.getX() || food.y < 0 || food.y >= grid.getY()) {
                spawnFood(); // Reposition the food within the new grid boundaries
            }

            shrinkTimer.restart();
        }

        // Move the snake and detect collisions
        if (clock.getElapsedTime().asSeconds() > moveInterval) {
            moveSnake();
            detectCollision(window);
            clock.restart();
        }

        window.clear(Color::Black);
        render(window);
        window.display();
    }
}


void SnakeGame::updateScore(int newScore)
{
    score = newScore;
    scoreText.setString("Score: " + to_string(score));
}

void SnakeGame::render(RenderWindow& window)
{
    window.draw(bgSprite);

    grid.renderBoundary(window, boundary);


    window.draw(scoreText);
    for (int i = 0; i < snakeLength; i++) { 
        // Store original position
        float originalX = snakeBody[i].getSprite().getPosition().x;
        float originalY = snakeBody[i].getSprite().getPosition().y;

        // Temporarily adjust position for rendering
        snakeBody[i].getSprite().move(0, 0);
        snakeBody[i].render(window);

        // Restore original position
        snakeBody[i].getSprite().setPosition(originalX, originalY);
    }

    // Set food sprite position and draw it
    foodSprite.setPosition(food.x * grid.getCellSize(), food.y * grid.getCellSize());
    window.draw(foodSprite);
}




void SnakeGame::endGame(RenderWindow& window, string cause) {
    Font font;
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        throw runtime_error("Failed to load font!");
    }

    // Display "Game Over" text
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition((window.getSize().x - textBounds.width) / 2, 150);

    // Display cause of the game ending
    Text causeText;
    causeText.setFont(font);
    causeText.setString(cause);
    causeText.setCharacterSize(30);
    causeText.setFillColor(Color::White);
    textBounds = causeText.getLocalBounds();
    causeText.setPosition((window.getSize().x - textBounds.width) / 2, 250);

    // Display the player's score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Your Score: " + to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::Yellow);
    textBounds = scoreText.getLocalBounds();
    scoreText.setPosition((window.getSize().x - textBounds.width) / 2, 350);

    // Render game over screen
    window.clear(Color::Black);
    window.draw(gameOverText);
    window.draw(causeText);
    window.draw(scoreText);
    window.display();
    if (leaderboard) {
        cout << "Before calling Player: " << playerName << ", Game: " << name << ", Score: " << score << endl;
        leaderboard->addEntry(playerName, name, score);
        leaderboard->saveToFile("leaderboard.txt");
        cout << "After saving leaderboard" << endl;
        string leaderboardFile = "C: / Semester 3 / OOP / oopProject / oopProject / leaderboard.txt"; // Use the same path as in the GameBoy constructor
        leaderboard->saveToFile(leaderboardFile); // Save updated leaderboard
        cout << "Leaderboard saved to file: " << leaderboardFile << endl;
    }

    sleep(seconds(3));
    window.close();

   
}

SnakeGame::~SnakeGame() {
    delete[] snakeBody;
    delete[] rotatingSegments;
}
