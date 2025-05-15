#include "WordleGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

WordleGame::WordleGame(const std::string& difficulty, Leaderboard* leaderboard)
    : Game("Wordle Game", leaderboard), selectedSpriteIndex(-1) {
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        std::exit(-1);
    }

    if (!backgroundTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/WordleBg.jpg")) {
        std::cerr << "Error loading background texture!" << std::endl;
        std::exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(800) / backgroundTexture.getSize().x,
        static_cast<float>(600) / backgroundTexture.getSize().y
    );

    sf::Vector2i positions[24] = {
        {306, 53}, {306, 114}, {306, 174}, {306, 233}, {306, 293}, {306, 352},
        {367, 53}, {367, 114}, {367, 174}, {367, 233}, {367, 293}, {367, 352},
        {429, 53}, {429, 114}, {429, 174}, {429, 233}, {429, 293}, {429, 352},
        {489, 53}, {489, 114}, {489, 174}, {489, 233}, {489, 293}, {489, 352}
    };

    for (int i = 0; i < 24; ++i) {
        spritePositions[i] = positions[i];
        spriteTexts[i].setFont(font);
        spriteTexts[i].setCharacterSize(24);
        spriteTexts[i].setFillColor(sf::Color::White);
        spriteHighlighted[i] = false;
    }
}

void WordleGame::startGame() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Wordle Game");

    while (window.isOpen()) {
        processEvents(window);
        update();
        render(window);
    }
}

void WordleGame::processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(sf::Mouse::getPosition(window));
            }
        }
    }
}

void WordleGame::update() {
    // Game logic updates here (if needed)
}

void WordleGame::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);

    for (int i = 0; i < 24; ++i) {
        if (spriteHighlighted[i]) {
            sf::RectangleShape highlight(sf::Vector2f(50, 50));
            highlight.setPosition(spritePositions[i].x, spritePositions[i].y);
            highlight.setFillColor(sf::Color(255, 255, 0, 100));
            window.draw(highlight);
        }
    }

    for (int i = 0; i < 24; ++i) {
        window.draw(spriteTexts[i]);
    }

    window.display();
}

void WordleGame::handleMouseClick(sf::Vector2i mousePosition) {
    for (int i = 0; i < 24; ++i) {
        sf::FloatRect spriteBounds(spritePositions[i].x, spritePositions[i].y, 50, 50);
        if (spriteBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
            selectedSpriteIndex = i;
            spriteHighlighted[i] = true;

            if (mousePosition.y >= 421 && mousePosition.y <= 472) {
                if (mousePosition.x >= 215 && mousePosition.x <= 252) printLetterOnSprite('Q', selectedSpriteIndex);
                else if (mousePosition.x >= 258 && mousePosition.x <= 294) printLetterOnSprite('W', selectedSpriteIndex);
            }
        }
    }
}

void WordleGame::printLetterOnSprite(char letter, int spriteIndex) {
    spriteTexts[spriteIndex].setString(std::string(1, letter));
    sf::FloatRect textBounds = spriteTexts[spriteIndex].getLocalBounds();
    spriteTexts[spriteIndex].setOrigin(textBounds.width / 2, textBounds.height / 2);

    float spriteX = spritePositions[spriteIndex].x + 25;
    float spriteY = spritePositions[spriteIndex].y + 25;

    spriteTexts[spriteIndex].setPosition(spriteX, spriteY);

    spriteHighlighted[spriteIndex] = false;
    selectedSpriteIndex = -1;
}

void WordleGame::endGame(sf::RenderWindow& window, std::string cause) {
    if (leaderboard) {
        leaderboard->addEntry("Player Name", name, score);
    }
}
