#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Leaderboard::Leaderboard() : entryCount(0) {}

void Leaderboard::addEntry(const string& playerName, const string& gameName, int score)
{
	if (entryCount < 10) 
	{
		entries[entryCount++] = { playerName, gameName, score };
	}
	else
	{
		cerr << "Error: Leaderboard is full!" << endl;
	}
	for (int i = 0; i < entryCount; i++) {
		cout << "Player: " << entries[i].playerName
			<< ", Game: " << entries[i].gameName
			<< ", Score: " << entries[i].score << endl;
	}

}

void Leaderboard::loadFromFile(const string& filename) 
{
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error: Failed to open file '" << filename << "' for reading!" << endl;
		return;
	}

	entryCount = 0;
	while (file >> entries[entryCount].playerName >> entries[entryCount].gameName >> entries[entryCount].score) {
		entryCount++;
		if (entryCount >= 10) {
			break; // Stop if the leaderboard is full
		}
	}
	file.close();
	cout << "Leaderboard successfully loaded from file: " << filename << endl;
}


void Leaderboard::saveToFile(const string& filename) {
	ofstream file(filename, ios::app); 
	if (!file.is_open()) {
		cerr << "Error: Failed to open file '" << filename << "' for writing!" << endl;
		return;
	}

	for (int i = 0; i < entryCount; i++) {
		file << entries[i].playerName << " "
			<< entries[i].gameName << " "
			<< entries[i].score << endl;
	}
	file.close();
	cout << "Leaderboard successfully saved to file: " << filename << endl;
}


void Leaderboard::sort(const string& gameName)
{
	for (int i = 0; i < entryCount - 1; i++)
	{
		for (int j = i + 1; j < entryCount; j++)
		{
			if (entries[i].gameName == gameName && entries[j].gameName == gameName)
			{
				if (entries[i].score < entries[j].score)
				{
					Entry temp = entries[i];
					entries[i] = entries[j];
					entries[j] = temp;
				}
			}
		}
	}
}
void Leaderboard::displayLeaderboard(sf::RenderWindow& window, const string& gameName) {
	sf::Font font;
	if (!font.loadFromFile("C:/path/to/font.ttf")) {
		cerr << "Error loading font!" << endl;
		return;
	}

	// Title
	Text title("Leaderboard - " + gameName, font, 30);
	title.setFillColor(sf::Color::Yellow);
	title.setPosition(50, 20);
	window.draw(title);

	// Get entries for the game
	Entry filteredEntries[10];
	int entryCount = getEntries(gameName, filteredEntries, 10);

	// Display entries
	float yPosition = 100.0f;
	for (int i = 0; i < entryCount; i++) {
		Text entryText(
			filteredEntries[i].playerName + " - " + std::to_string(filteredEntries[i].score),
			font, 20);
		entryText.setFillColor(sf::Color::White);
		entryText.setPosition(50, yPosition);
		window.draw(entryText);
		yPosition += 30.0f; // Move down for the next entry
	}

	// Back button
	Text backButton("Press Enter to go back", font, 20);
	backButton.setFillColor(sf::Color::White);
	backButton.setPosition(50, window.getSize().y - 50);
	window.draw(backButton);

	window.display();
}

bool Leaderboard::isEmpty()
{
	return entryCount == 0;
}

int Leaderboard::getEntries(const string& gameName, Entry result[], int maxResults)
{
	int count = 0;
	for (int i = 0; i < entryCount && count < maxResults; i++)
	{
		if (entries[i].gameName == gameName)
		{
			result[count++] = entries[i];
		}
	}
	return count;
}