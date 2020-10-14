// 1. Create Game Window
// 2. Draw Board
// 3. Draw Start Points
// 4. Draw Stones
// 5. Mouse Click
// 6. Apply Textures


/***************************************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>


/***************************************************************************************/
using namespace std;
using namespace sf;


/***************************************************************************************/
int cell_size = 40;
int board[19][19] = { 0 };
#define BLACK (1)
#define WHITE (2)


/***************************************************************************************/
int main()
{
	ContextSettings s;
	s.antialiasingLevel = 8;

	RenderWindow window(VideoMode(cell_size * 19, cell_size * 19), "Go", Style::Default, s);

	// Black Stone
	Texture bt;
	// White Stone
	Texture wt;

	bt.loadFromFile("black_stone.bmp");
	wt.loadFromFile("white_stone.bmp");

	bt.setSmooth(true);
	wt.setSmooth(true);
	
	Sprite bs(bt);
	Sprite ws(wt);

	bs.setScale(1.0 * cell_size / bs.getLocalBounds().width, 1.0 * cell_size / bs.getLocalBounds().height);
	ws.setScale(1.0 * cell_size / ws.getLocalBounds().width, 1.0 * cell_size / ws.getLocalBounds().height);


	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::MouseButtonPressed)
			{

				int ix = e.mouseButton.x / cell_size;
				int iy = e.mouseButton.y / cell_size;

				// Put Black Stone with left click
				if (e.mouseButton.button == Mouse::Left)
				{
					board[ix][iy] = BLACK;
				}
				// Put White Stone with right click
				else if (e.mouseButton.button == Mouse::Right)
				{
					board[ix][iy] = WHITE;
				}
			}
		}
		window.clear(Color(255, 207, 97));


		// Draw lines
		auto draw_board = [&]()
		{
			float half_cell = cell_size / 2.0;

			// Draw horizontal lines
			for (int y = 0; y < 19; y++)
			{
				Vertex hline[] =
				{
					Vertex( Vector2f( half_cell, half_cell + y * cell_size ) ),
					Vertex( Vector2f( cell_size * 19 - half_cell, half_cell + y * cell_size ) )
				};

				hline[0].color = Color::Black;
				hline[1].color = Color::Black;
				
				window.draw(hline, 2, Lines);
			}

			// Draw vertical lines
			for (int x = 0; x < 19; x++)
			{
				Vertex vline[] =
				{				
					Vertex( Vector2f( half_cell + x * cell_size, half_cell ) ),
					Vertex( Vector2f( half_cell + x * cell_size, cell_size * 19 - half_cell ) )
				};

				vline[0].color = Color::Black;
				vline[1].color = Color::Black;

				window.draw(vline, 2, Lines);
			}


			// Draw Start Points
			float start_point_r = half_cell / 5;
			CircleShape circle( start_point_r );
			circle.setFillColor( Color::Black );
			for (int y = 0; y < 3; y++)
				for (int x = 0; x < 3; x++)
				{
					circle.setPosition(half_cell + (3 + 6 * x) * cell_size - start_point_r,
						half_cell + (3 + 6 * y) * cell_size - start_point_r);
					window.draw(circle);
				}

		};


		draw_board();

		// Draw stone
		auto draw_stone = [&]()
		{
			for (int y = 0; y < 19; y++)
				for (int x = 0; x < 19; x++)
				{
					if (board[x][y] == BLACK)
					{
						bs.setPosition(x * cell_size, y * cell_size);
						window.draw(bs);
					}
					else if (board[x][y] == WHITE)
					{
						ws.setPosition(x * cell_size, y * cell_size);
						window.draw(ws);
					}
				}

		};

		draw_stone();

		window.display();
	}
	return 0;
}
