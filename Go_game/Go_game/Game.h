#pragma once
#include <SFML/Graphics.hpp>

#define BLACK (1)
#define WHITE (2)

class Game
{
public:
	Game();

	Game(sf::ContextSettings mS);

	sf::RenderWindow& get_mWindow()				{ return mWindow; };

	sf::Texture&	  get_bt()					{ return bt; }
	sf::Texture&	  get_wt()					{ return wt; }

	sf::Sprite&		  get_bs()					{ return bs; }
	sf::Sprite&		  get_ws()					{ return ws; }

	int				  get_cell()    const		{ return cell_size;  }

	bool&			  get_visit(int x, int y)	{ return visit[x][y]; }

	auto&			  get_board(int x, int y)	{ return board[x][y]; }


	
	void LoadTextures();

	void AddSmoothness();

	void ApplyTextures();

	void SetScale();

	void draw_stone();

	void draw_board();

	void update();

	void remove_dead_stone(int color);

	bool live_check(int color, int x, int y);

	~Game();

protected:
	sf::RenderWindow mWindow;
	sf::ContextSettings mS;

	bool visit[19][19];
	int board[19][19] = { 0 };

	int cell_size = 40;

	// Black Stone
	sf::Texture bt;
	// White Stone
	sf::Texture wt;

	sf::Sprite bs;
	sf::Sprite ws;
};



