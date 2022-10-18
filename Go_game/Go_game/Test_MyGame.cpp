#include "MyTests.h"
#include "Board.h"
#include "Game.h"
#include "Menu.h"

/***************************************************************************************/
void Board_Move()
{
	Game game;

	Board board( game );

	board.set_board( 0, 0 ) = BLACK;
	DO_TEST( board.set_board(0, 0) == BLACK );

	board.set_board( 0, 1 ) = WHITE;
	DO_TEST( board.set_board( 0, 1 ) == WHITE );

}


void Remove_Stone()
{
	Game game;

	Board board( game );

	board.set_board( 1, 0 ) = BLACK;
	board.set_board( 1, 1 ) = WHITE;
	board.set_board( 1, 2 ) = BLACK;
	board.set_board( 0, 1 ) = BLACK;
	board.set_board( 2, 1 ) = BLACK;

	game.remove_dead_stone( WHITE );

	DO_TEST( board.set_board(1, 1) == 1 );

}


/***************************************************************************************/
void Test_MyGame()
{
	Board_Move();
	Remove_Stone();
}