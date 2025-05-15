#include "HangmanFigure.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

HangmanFigure::HangmanFigure() : wrongGuesses(0) {
    if (!hangmanTexture[0].loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/body1.png")) {
        cerr << "Failed to load stand texture!" << endl;
    }
    hangmanBody[0].setTexture(hangmanTexture[0]);
    hangmanBody[0].setPosition(0,0);

    for (int i = 1; i < 7; i++) {
        if (!hangmanTexture[i].loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/body" + to_string(i + 1) + ".png")) {
            cerr << "Failed to load body" << i + 1 << " texture!" << endl;
        }
        hangmanBody[i].setTexture(hangmanTexture[i]);
        hangmanBody[i].setPosition(0,0);
        hangmanBody[i].setColor(Color::Transparent);
    }
}

void HangmanFigure::reset() {
    wrongGuesses = 0;
    for (int i = 1; i < 7; ++i) {
        hangmanBody[i].setColor(Color::Transparent);
    }
}

void HangmanFigure::updateLives(int currentWrongGuesses) {
    if (currentWrongGuesses >= 1 && currentWrongGuesses < 7) {
        wrongGuesses = currentWrongGuesses;
        hangmanBody[wrongGuesses].setColor(Color::White);
        cout << "Drawing Hangman part: " << wrongGuesses << endl;
    }
}

void HangmanFigure::draw(RenderWindow& window) {
    window.draw(hangmanBody[0]);
    for (int i = 1; i <= wrongGuesses && i < 7; ++i) {
        window.draw(hangmanBody[i]);
    }
}
