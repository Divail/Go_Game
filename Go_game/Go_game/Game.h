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
	sf::Sprite&  get_bs() { return bs; }
	sf::Sprite&  get_ws() { return ws; }


	void LoadTextures();

	void AddSmoothness();

	void ApplyTextures();

	~Game();

protected:
	sf::RenderWindow mWindow;
	sf::ContextSettings mS;

	// Black Stone
	sf::Texture bt;
	// White Stone
	sf::Texture wt;

	sf::Sprite bs;
	sf::Sprite ws;
};



