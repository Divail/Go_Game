#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <assert.h>

#define BLACK (1)
#define WHITE (2)

class Game
{
public:

	Game();
	~Game();

	// -----------------------
	// Get Methods:
	const sf::RenderWindow&	  get_mWindow() const			{ return mWindow; };

	const sf::Texture&		  get_bt()		const			{ return bt; }
	const sf::Texture&	      get_wt()		const			{ return wt; }

	const sf::Sprite&		  get_bs()		const			{ return bs; }
	const sf::Sprite&		  get_ws()		const			{ return ws; }

	const int&				  get_cell()	const			{ return cell_size;  }

	bool&					  get_visit(int x, int y)		{ return visit[x][y]; }

	auto&			          get_board(int x, int y)		{ return board[x][y]; }

	STARTUPINFO&			  get_sti()						{ return sti; }
	

	// -----------------------
	// Textures Metods:
	void					  LoadTextures();
	void					  AddSmoothness();
	void					  ApplyTextures();
	void					  SetScale();

	// -----------------------
	// Face Metods:
	void					  draw_stone();
	void					  draw_board();

	// -----------------------
	// Logic Metods: 
	void					  update();
	void					  remove_dead_stone (int color);
	bool					  live_check		(int color, int x, int y);
	std::string				  getNextMove		(std::string position);

	// -----------------------
	// Engine Metods:
	void					  ConnectToEngine();
	void					  CloseConnection();

	// -----------------------
	// Mouse Metods:
	void					  MousePressEvent();


	void					  WindowIsOpen();


protected:///////////////////////////////////////////////////////////////////////////////////
	
			// Init Data:
	int					cell_size = 40;

	const char*			path = "gnugo.exe --mode gtp";
	
	sf::Event			e;

	sf::RenderWindow	mWindow;
	
	sf::ContextSettings mS;

			// Runtime Data:
	int					board[19][19] = { 0 };
	bool				visit[19][19];

	// Black Stone
	sf::Texture			bt;
	// White Stone
	sf::Texture			wt;

	sf::Sprite			bs;
	sf::Sprite			ws;

	STARTUPINFO			sti = { 0 };
	SECURITY_ATTRIBUTES sats = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	HANDLE				pipin_w, pipin_r;
	HANDLE				pipout_w, pipout_r;
	BYTE				buffer[2048];
	DWORD				write, excode, read, avaiable;
};



