#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu();
	~Menu();

	void draw();

	void MoveUp();

	void MoveDown();

	void switchCaseMenu();

	void Run();

	int GetPressedItem() { return selectedItemIndex; }

private:
	Game game;
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};