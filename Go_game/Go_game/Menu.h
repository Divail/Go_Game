#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Board.h"

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

	void Display();

	int GetPressedItem() { return selectedItemIndex; }

protected:
	Game game;

	Board board;

	int selectedItemIndex;

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};