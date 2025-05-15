#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
Menu::Menu() : optionCount(0), selectedOption(0) {
    if (!font.loadFromFile("C:/Semester 3/OOP/oopProject/pixel-emulator-font/PixelEmulator-xq08.ttf")) {
        cout << "Error loading font!" << endl;
    }
    else {
        cout << "Font loaded successfully!" << endl;
    }
}

void Menu::addMenuItem(const string& item) {
    if (optionCount < maxOptions) {
        menuItems[optionCount] = item;
        optionCount++;
        cout << "Added menu item: " << item << " at index " << optionCount - 1 << endl;
    }
    else {
        cout << "Error: Cannot add more menu items. Maximum reached!" << endl;
    }
}

void Menu::navigateMenu(int direction) {
    selectedOption += direction;

    if (selectedOption < 0) {
        selectedOption = optionCount - 1;  
    }
    else if (selectedOption >= optionCount) {
        selectedOption = 0;  
    }
}

void Menu::render(RenderWindow& window) {
    float centerX = window.getSize().x / 2.0f;
    float startY = 300.0f; 
    float spacing = 60.0f; 

    for (int i = 0; i < optionCount; i++) {
        Text text(menuItems[i], font, 40); 
        FloatRect bounds = text.getLocalBounds();
        text.setStyle(Text::Bold); 
        text.setOutlineColor(Color::Black); 
        text.setOutlineThickness(2); 
        text.setPosition(centerX - bounds.width / 2.0f, startY + i * spacing); 
        text.setFillColor(i == selectedOption ? Color::White : Color::Yellow); 
        window.draw(text);
    }
}
