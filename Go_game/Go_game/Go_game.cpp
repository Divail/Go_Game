//1. Create Game Window
//2. Draw Board


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
		auto draw_board = [&]()
		{
			float half_cell = cell_size / 2.0;

			//Draw horizontal lines
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

			//Draw vertical lines
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
		};
		draw_board();
		window.display();
	}
	return 0;
}
