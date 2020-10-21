#include "Game.h"

Game::Game()
{

}

Game::Game(sf::ContextSettings mS)
:
	mWindow(sf::VideoMode(40 * 19, 40 * 19), "Go", sf::Style::Default, mS)
{
	
}


Game::~Game()
{
}
