#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <assert.h>

#define BLACK (1)
#define WHITE (2)

class Game;

class Board
{
public:
				Board( Game& inGame );
				~Board();

	// -----------------------
	// Get Methods:
	bool&		set_visit( int x, int y ) { return visit[x][y]; }

	auto&		set_board( int x, int y ) { return board[x][y]; }

	const int&  get_cell()    const		  { return cell_size; }


	// -----------------------
	// Face Methods:
	void		draw_stone();
	void		draw_board();


protected:///////////////////////////////////////////////////////////////////////////////////

			// Runtime Data:
	Game& game;

	int	 cell_size = 50;
	int	 board[19][19] = { 0 };
	bool visit[19][19];


};

