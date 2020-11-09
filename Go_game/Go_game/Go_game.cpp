// 1. Create Game Window
// 2. Draw Board
// 3. Draw Start Points
// 4. Draw Stones
// 5. Mouse Click
// 6. Apply Textures
// 7. Capture Stone
// 8. AI


/***************************************************************************************/
#include "Game.h"
#include "MyTests.h"
#include "Menu.h"


/***************************************************************************************/
int main()
{
	Game  game;
	Menu menu(game.get_mWindow().getSize().x, game.get_mWindow().getSize().x);

	menu.Run();

	game.Run();

	return 0;
}
