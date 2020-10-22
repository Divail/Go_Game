// 1. Create Game Window
// 2. Draw Board
// 3. Draw Start Points
// 4. Draw Stones
// 5. Mouse Click
// 6. Apply Textures
// 7. Capture Stone
// 8. AI


/***************************************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <assert.h>
#include "Game.h"


/***************************************************************************************/
using namespace std;
using namespace sf;


/***************************************************************************************/
int main()
{

	Game game;

	game.ConnectToEngine();

	game.LoadTextures();

	game.AddSmoothness();

	game.ApplyTextures();

	game.SetScale();

	game.update();

	game.WindowIsOpen();

	return 0;
}
