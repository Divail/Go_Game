#include "Board.h"

#include "Game.h"


/***************************************************************************************/
Board::Board( Game& inGame )
:
	game(inGame)
{
}


/***************************************************************************************/
Board::~Board()
{
}


/***************************************************************************************/
void Board::draw_board()
{
	float half_cell = cell_size / 2.0;

	// Draw horizontal lines
	for (int y = 0; y < 19; y++)
	{
		sf::Vertex hline[] =
		{
			sf::Vertex(sf::Vector2f(half_cell, half_cell + y * cell_size)),
			sf::Vertex(sf::Vector2f(cell_size * 19 - half_cell, half_cell + y * cell_size))
		};

		hline[0].color = sf::Color::Black;
		hline[1].color = sf::Color::Black;

		game.get_mWindow().draw(hline, 2, sf::Lines);
	}

	// Draw vertical lines
	for (int x = 0; x < 19; x++)
	{
		sf::Vertex vline[] =
		{
			sf::Vertex(sf::Vector2f(half_cell + x * cell_size, half_cell)),
			sf::Vertex(sf::Vector2f(half_cell + x * cell_size, cell_size * 19 - half_cell))
		};

		vline[0].color = sf::Color::Black;
		vline[1].color = sf::Color::Black;

		game.get_mWindow().draw(vline, 2, sf::Lines);
	}


	// Draw Start Points
	float start_point_r = half_cell / 5;

	sf::CircleShape circle(start_point_r);
	circle.setFillColor(sf::Color::Black);

	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
		{
			circle.setPosition(half_cell + (3 + 6 * x) * cell_size - start_point_r,
				half_cell + (3 + 6 * y) * cell_size - start_point_r);

			game.get_mWindow().draw(circle);
		}
};


/***************************************************************************************/
void Board::draw_stone()
{
	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (board[x][y] == BLACK)
			{
				game.get_bs().setPosition(x * cell_size, y * cell_size);
				game.get_mWindow().draw(game.get_bs());
			}
			else if (board[x][y] == WHITE)
			{
				game.get_ws().setPosition(x * cell_size, y * cell_size);
				game.get_mWindow().draw(game.get_ws());
			}
		}

};
