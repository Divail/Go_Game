#pragma once
#include <SFML/Graphics.hpp>


class Game
{
public:
	Game();

	Game(sf::ContextSettings mS);

	sf::RenderWindow& get_mWindow() { return mWindow; };

	sf::Texture& get_bt() { return bt; }
	sf::Texture& get_wt() { return wt; }


	void LoadTextures()
	{
		bt.loadFromFile("black_stone.bmp");
		wt.loadFromFile("white_stone.bmp");
	}

	~Game();

protected:
	sf::RenderWindow mWindow;
	sf::ContextSettings mS;

	// Black Stone
	sf::Texture bt;
	// White Stone
	sf::Texture wt;
};



