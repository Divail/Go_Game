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

void Game::ApplyTextures()
{
	bs.setTexture(bt);
	ws.setTexture(wt);
}

void Game::SetScale()
{
	bs.setScale(40 / bs.getLocalBounds().width, 40 / bs.getLocalBounds().height);
	ws.setScale(40 / ws.getLocalBounds().width, 40 / ws.getLocalBounds().height);
}

Game::~Game()
{
}
