#pragma once
#include <SFML/Graphics.hpp>


class Game
{
public:
	Game();

	Game(sf::ContextSettings mS);

	sf::RenderWindow& get_mWindow() { return mWindow; };

	~Game();

protected:
	sf::RenderWindow mWindow;
	sf::ContextSettings mS;

	// Black Stone
	sf::Texture bt;
	// White Stone
	sf::Texture wt;
};



