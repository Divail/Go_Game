#include "MyTests.h"
#include "Board.h"
#include "Game.h"


/***************************************************************************************/
void Board_Move()
{
	Game game;

	Board board( game );

	DO_TEST( board.get_board(1, 1) = BLACK);
	DO_TEST( board.get_visit(1, 1) = 1 );

}


/***************************************************************************************/
void Test_MyGame()
{
	Board_Move();
}