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
	bool& get_visit(int x, int y) { return visit[x][y]; }

	auto& get_board(int x, int y) { return board[x][y]; }

	const int& get_cell()  const  { return cell_size; }


	// -----------------------
	// Face Metods:
	void draw_stone();
	void draw_board();


protected:

	Game& game;

	int	 cell_size = 40;

	int	 board[19][19] = { 0 };
	bool visit[19][19];


};

