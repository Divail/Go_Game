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

void Game::draw_board()
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

		mWindow.draw(hline, 2, sf::Lines);
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

		mWindow.draw(vline, 2, sf::Lines);
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

			mWindow.draw(circle);
		}
};

void Game::draw_stone()
{
	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (board[x][y] == BLACK)
			{
				bs.setPosition(x * cell_size, y * cell_size);
				mWindow.draw(bs);
			}
			else if (board[x][y] == WHITE)
			{
				ws.setPosition(x * cell_size, y * cell_size);
				mWindow.draw(ws);
			}
		}

};

void Game::update()
{
	mWindow.clear(sf::Color(255, 207, 97));

	draw_board();

	// Draw stone
	draw_stone();

	mWindow.display();
};

Game::~Game()
{
}
