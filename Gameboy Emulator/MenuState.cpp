#include "MenuState.h"
#include <iostream>
using namespace std;

// Constructor: Initialize selectedOption and currentOption
MenuState::MenuState() : selectedOption(0), currentOption("") {}

// Method to navigate up/down through the menu options
void MenuState::navigate(int direction, int optionCount) {
    cout << "Navigating menu with direction: " << direction << endl;
    selectedOption += direction;

    if (selectedOption < 0) {
        selectedOption = optionCount - 1;  // Wrap around to the last option
        cout << "Wrapped around to last option. Selected option: " << selectedOption << endl;
    }
    else if (selectedOption >= optionCount) {
        selectedOption = 0;  // Wrap around to the first option
        cout << "Wrapped around to first option. Selected option: " << selectedOption << endl;
    }
    else {
        cout << "Updated selected option: " << selectedOption << endl;
    }
}
