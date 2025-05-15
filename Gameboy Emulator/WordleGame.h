#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

class WordleGame : public Game {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text spriteTexts[24];
    sf::Vector2i spritePositions[24];
    bool spriteHighlighted[24];
    int selectedSpriteIndex;

    void processEvents(sf::RenderWindow& window);
    void update();
    void handleMouseClick(sf::Vector2i mousePosition);
    void printLetterOnSprite(char letter, int spriteIndex);

public:
    WordleGame(const std::string& difficulty, Leaderboard* leaderboard);
    void startGame() override;
    void endGame(sf::RenderWindow& window, std::string cause) override;
    void render(sf::RenderWindow& window) override;
};
