#include "HangmanGame.h"
#include "Category.h"
#include "HangmanFigure.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

// Default constructor
HangmanGame::HangmanGame(const string& difficulty, Leaderboard* leaderboard, const string& playerName) 
    : Game("Hangman Game", leaderboard), playerName(playerName),
    secretWord(""), guessedWord(""), incorrectGuesses(""),
    maxLives(6), hints(3), difficulty("Easy"), category(nullptr), hangmanFigure() {

    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }
    if (difficulty == "Medium" || difficulty == "Hard") {
        string randomCategory = Category().getCategoryName(true); 
        category = new Category(randomCategory); 
        hints = (difficulty == "Medium") ? 1 : 0; 
    }
    else if (difficulty == "Easy") {
        RenderWindow categoryWindow(VideoMode(800, 600), "Select Category");
        string userSelectedCategory = selectCategory(categoryWindow); 
        category = new Category(userSelectedCategory);
        hints = 2; 
    }


    if (category) {
        secretWord = category->getWord();
        guessedWord = "";
        for (char ch : secretWord) {
            if (ch == ' ') {
                guessedWord += ' ';  
            }
            else {
                guessedWord += '_';
            }
        }
    }
    else {
        cerr << "Error: Category is null!" << endl;
        return; 
    }

  

    hintText.setFont(font);
    hintText.setString("HINT");
    hintText.setCharacterSize(24);
    hintText.setFillColor(Color::Blue);
    hintText.setPosition(650, 50);  
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(10, 10);

    
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(Color::Black);
    livesText.setPosition(650, 10);  

    hangmanFigure.reset();  
    if (!bgTexture.loadFromFile("C:/Semester 3/OOP/oopProject/oopProject/hangmanbg.png")) {
        cerr << "Error loading background texture!" << endl;
    }
    bgSprite.setTexture(bgTexture);
}


void HangmanGame::trackGuesses(char guessedLetter) {
    guessedLetter = tolower(guessedLetter); 
    bool correctGuess = false;

    
    if (isalpha(guessedLetter)) {
        if (guessedWord.find(guessedLetter) != string::npos ||
            incorrectGuesses.find(guessedLetter) != string::npos) {
            cout << "Letter already guessed: " << guessedLetter << endl;
            return; 
        }

        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (tolower(secretWord[i]) == guessedLetter) {
                guessedWord[i] = secretWord[i]; 
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses += guessedLetter;
            maxLives--; 
            hangmanFigure.updateLives(incorrectGuesses.length()); 
            score -= 10; 
            cout << "Wrong guess: " << guessedLetter << endl;
        }
        else {
            cout << "Correct guess: " << guessedLetter << endl;
        }
    }
    else {
        cout << "Invalid input: " << guessedLetter << endl;
    }
}


int HangmanGame::manageLives() {
    if (maxLives <= 0) {
        cout << "You lost! The word was: " << secretWord << endl;
        return -1;    // Indicate game loss
    }

    // Check if the player has won
    if (guessedWord == secretWord) {
        cout << "You won! The word is: " << secretWord << endl;
        score += 70;  // Award points for correctly guessing the word
        return 1;      // Indicate game win
    }

    // Game continues
    return 0;
}


void HangmanGame::useHint() 
{
    if (hints > 0) {
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (guessedWord[i] == '_') { // Find the first unrevealed character
                guessedWord[i] = secretWord[i]; // Reveal it
                hints--; // Decrease hint count
                cout << "Hint used! Revealed letter: " << secretWord[i] << ". Hints left: " << hints << endl;
                return;
            }
        }
    }
    else {
        cout << "No hints left!" << endl;
    }
}

string HangmanGame::selectCategory(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        cerr << "Failed to load font!" << endl;
        return "";
    }

    // Category names
    string categories[] = { "Animals", "Countries", "Fruits", "Shows", "Subjects" };
    int selectedIndex = 0;
    const int numCategories = 5;

    Text categoryText[numCategories];
    for (int i = 0; i < numCategories; ++i) {
        categoryText[i].setFont(font);
        categoryText[i].setString(categories[i]);
        categoryText[i].setCharacterSize(30);
        categoryText[i].setFillColor(i == selectedIndex ? Color::Red : Color::White); // Highlight selected
        categoryText[i].setPosition(200, 100 + i * 50); // Spaced vertically
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Navigate categories
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    selectedIndex = (selectedIndex - 1 + numCategories) % numCategories; // Wrap around
                }
                else if (event.key.code == Keyboard::Down) {
                    selectedIndex = (selectedIndex + 1) % numCategories;
                }
                else if (event.key.code == Keyboard::Enter) {
                    return categories[selectedIndex]; // Return selected category
                }
            }
        }

        // Update text colors
        for (int i = 0; i < numCategories; ++i) {
            categoryText[i].setFillColor(i == selectedIndex ? Color::Red : Color::White);
        }

        window.clear(Color::Black);
        for (int i = 0; i < numCategories; ++i) {
            window.draw(categoryText[i]);
        }
        window.display();
    }
    return "";
}
void HangmanGame::endGame(RenderWindow& window, string cause) {
    Font font;
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        throw runtime_error("Failed to load font!");
    }

    // Create the Game Over text
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition((window.getSize().x - textBounds.width) / 2, 150);

    // Create the cause text
    Text causeText;
    causeText.setFont(font);
    causeText.setString(cause);
    causeText.setCharacterSize(30);
    causeText.setFillColor(Color::White);
    textBounds = causeText.getLocalBounds();
    causeText.setPosition((window.getSize().x - textBounds.width) / 2, 250);

    // Create the score text
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Your Score: " + to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::Yellow);
    textBounds = scoreText.getLocalBounds();
    scoreText.setPosition((window.getSize().x - textBounds.width) / 2, 350);

    // Create the secret word text
    Text wordText;
    wordText.setFont(font);
    wordText.setString("The Word: " + secretWord);
    wordText.setCharacterSize(30);
    wordText.setFillColor(Color::Cyan);
    textBounds = wordText.getLocalBounds();
    wordText.setPosition((window.getSize().x - textBounds.width) / 2, 400);

    // Render the texts
    window.clear(Color::Black);
    window.draw(gameOverText);
    window.draw(causeText);
    window.draw(scoreText);
    window.draw(wordText);  // Draw the word on the next line
    window.display();

    sleep(seconds(3));
    window.close();
}


// Start the game logic
void HangmanGame::startGame() {
    RenderWindow window(VideoMode(800, 600), "Hangman Game");

   
    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Handle input for guesses and hints
            if (event.type == Event::KeyPressed) {
                if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z) {
                    char guessedLetter = static_cast<char>(event.key.code + 'A' - Keyboard::A);
                    trackGuesses(guessedLetter);
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    FloatRect hintBounds = hintText.getGlobalBounds();
                    if (hintBounds.contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
                        useHint();
                    }
                }
            }
        }

        // Check for win/loss conditions
        int gameStatus = manageLives();
        if (gameStatus == -1) { // Lost
            endGame(window, "Game Over: You Lost!");
            break;
        }
        else if (gameStatus == 1) { // Won
            endGame(window, "Congratulations! You Won!");
            break;
        }

        // Render the game
        window.clear(Color::White);
        render(window);
    }
}




string& HangmanGame::getGuessedWord() {
	return guessedWord;
}
string& HangmanGame::getIncorrectGuesses() {
	return incorrectGuesses;
}

void HangmanGame::render(RenderWindow& window) {
    window.draw(bgSprite);

    // Display score
    scoreText.setString("Score: " + to_string(score));
    window.draw(scoreText);

    // Display remaining lives
    livesText.setString("Lives: " + to_string(maxLives));
    window.draw(livesText);

    // Display hint text and hints left
    hintText.setString("HINTS: " + to_string(hints));
    window.draw(hintText);

    // Draw the hangman figure
    hangmanFigure.draw(window);

    // Create string with blanks for guessed letters
    Text guessedWordText;
    guessedWordText.setFont(font);
    guessedWordText.setCharacterSize(40);
    guessedWordText.setFillColor(Color::Black);

    float x = 50.0f;   
    float y = 500.0f;  
    float lineWidth = 0.0f;  
    float maxLineWidth = 700.0f;  
    float dashWidth = guessedWordText.getCharacterSize() * 1.2f;  
    float spaceWidth = dashWidth * 2.5f;  

    for (size_t i = 0; i < secretWord.length(); ++i) {
        char ch = secretWord[i];
        if (ch == ' ') {
            
            lineWidth += spaceWidth;
            if (lineWidth > maxLineWidth) {
                
                y += guessedWordText.getCharacterSize() * 1.5f;
                x = 50.0f;
                lineWidth = spaceWidth;
            }
            x += spaceWidth;
            continue;
        }

        guessedWordText.setString(guessedWord[i] == '_' ? "_" : string(1, guessedWord[i]));
        guessedWordText.setPosition(x, y);
        window.draw(guessedWordText);

        lineWidth += dashWidth;
        if (lineWidth > maxLineWidth) {
            y += guessedWordText.getCharacterSize() * 1.5f;
            x = 50.0f;
            lineWidth = dashWidth;
        }
        else {
            x += dashWidth;
        }
    }

    window.display();
}
