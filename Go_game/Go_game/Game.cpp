#include "Game.h"

Game::Game()
{

}

Game::Game(sf::ContextSettings mS)
:
	mWindow(sf::VideoMode(40 * 19, 40 * 19), "Go", sf::Style::Default, mS)
{
	
}

void Game::LoadTextures()
{
	bt.loadFromFile("black_stone.bmp");
	wt.loadFromFile("white_stone.bmp");
}

void Game::AddSmoothness()
{
	// Apply Smoothness for Black Stone
	bt.setSmooth(true);
	// Apply Smoothness for White Stone
	wt.setSmooth(true);
}


Game::~Game()
{
}
