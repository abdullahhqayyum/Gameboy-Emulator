#include "Category.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
using namespace std;
using namespace sf;

Category::Category() {
    numWords = 0;
    categoryName = "";
}

Category::Category(const string& categoryName) {
    numWords = 0;
    this->categoryName = categoryName;

    if (categoryName == "Countries") {
        words[0] = "Afghanistan";
        words[1] = "United States of America";
        words[2] = "United Kingdom";
        words[3] = "France";
        words[4] = "Germany";
        words[5] = "Italy";
        words[6] = "Venezuela";
        words[7] = "Brazil";
        words[8] = "Portugal";
        words[9] = "Spain";
        numWords = 10;
    }
 
    else if (categoryName == "Subjects") {
        words[0] = "Mathematics";
        words[1] = "Physics";
        words[2] = "Chemistry";
        words[3] = "Biology";
        words[4] = "Computer Science";
        words[5] = "History";
        words[6] = "Geography";
        words[7] = "Literature";
        words[8] = "Art";
        words[9] = "Music";
        numWords = 10;
    }
    else if (categoryName == "Animals") {
        words[0] = "Dog";
        words[1] = "Cat";
        words[2] = "Elephant";
        words[3] = "Lion";
        words[4] = "Tiger";
        words[5] = "Giraffe";
        words[6] = "Zebra";
        words[7] = "Horse";
        words[8] = "Cow";
        words[9] = "Pig";
        numWords = 10;
    }
    else if (categoryName == "Fruits") {
        words[0] = "Apple";
        words[1] = "Banana";
        words[2] = "Orange";
        words[3] = "Grapes";
        words[4] = "Strawberry";
        words[5] = "Watermelon";
        words[6] = "Pineapple";
        words[7] = "Mango";
        words[8] = "Peach";
        words[9] = "Pear";
        numWords = 10;
    }
    else if (categoryName == "Shows") {
        words[0] = "Breaking Bad";
        words[1] = "Better Call Saul";
        words[2] = "The Walking Dead";
        words[3] = "Stranger Things";
        words[4] = "The Big Bang Theory";
        words[5] = "Friends";
        words[6] = "How I Met Your Mother";
        words[7] = "The Simpsons";
        words[8] = "Family Guy";
        words[9] = "South Park";
        numWords = 10;
    }
}

string Category::getCategoryName(bool random) {
    static const string categoryNames[] = { "Countries", "Subjects", "Animals", "Fruits", "Shows" };

    if (random) {
        int randomIndex = rand() % 5;
        return categoryNames[randomIndex];
    }
    return categoryName;
}

int Category::getNumWords() {
    return numWords;
}

string Category::getWord() {
    if (numWords == 0) {
        return ""; 
    }
    int wordIndex = rand() % numWords;
    return words[wordIndex];
}
