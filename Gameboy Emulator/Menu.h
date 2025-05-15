#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Menu {
protected:
    Font font;
    int optionCount;
    static const int maxOptions = 10;
    string menuItems[maxOptions];
    int selectedOption;

public:
    Menu();
    ~Menu() = default;
    void addMenuItem(const string& item);
    void navigateMenu(int direction);
    void render(RenderWindow& window);

    virtual void displayMenu(RenderWindow& window) = 0;
    virtual void handleInput(Event& event) = 0;

};