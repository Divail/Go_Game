//1. Create Game Window


/***************************************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>


/***************************************************************************************/
using namespace std;
using namespace sf;


/***************************************************************************************/
int main()
{
    RenderWindow window(VideoMode(300, 300), "Go");
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
	return 0;
}
