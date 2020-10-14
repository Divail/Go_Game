// 1. Create Game Window
// 2. Draw Board
// 3. Draw Start Points
// 4. Draw Stones


/***************************************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>


/***************************************************************************************/
using namespace std;
using namespace sf;


/***************************************************************************************/
int cell_size = 40;

/***************************************************************************************/
int main()
{
    RenderWindow window(VideoMode(cell_size * 19, cell_size * 19), "Go");
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		window.clear(Color::Yellow);


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
			CircleShape stone(cell_size / 2.0);
			stone.setFillColor(Color::White);
			stone.setOutlineColor(Color::Black);
			stone.setOutlineThickness(-2); // inner grow
			stone.setPosition(0, 0);

			window.draw(stone);

			stone.setFillColor(Color::Black);
			stone.setPosition(0, cell_size);

			window.draw(stone);

		};

		draw_stone();

		window.display();
	}
	return 0;
}
