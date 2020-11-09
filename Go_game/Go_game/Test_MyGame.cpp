#include "MyTests.h"
#include "Board.h"
#include "Game.h"


/***************************************************************************************/
void Board_Move()
{
	Game game;

	Board board( game );


	board.set_board(1, 1) = BLACK;
	DO_TEST( board.set_board(1, 1) == BLACK );

	board.set_visit(1, 1) = 1;
	DO_TEST( board.set_visit(1, 1) == 1 );

}


/***************************************************************************************/
void Test_MyGame()
{
	Board_Move();
}