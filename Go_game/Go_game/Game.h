#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <assert.h>
#include <strstream>

#include "Board.h"
#include "MyTests.h"

#define BLACK (1)
#define WHITE (2)

class Game
{
public:

	Game(  );
	~Game();

	// -----------------------
	// Get Methods:
	sf::RenderWindow&		  get_mWindow() 			{ return mWindow; };

	const sf::Texture&		  get_bt()		const		{ return bt; }
	const sf::Texture&	      get_wt()		const		{ return wt; }

	sf::Sprite&				  get_bs()					{ return bs; }
	sf::Sprite&				  get_ws()					{ return ws; }

	STARTUPINFO&			  get_sti()					{ return sti; }
	

	// -----------------------
	// Textures Metods:
	void					  LoadTextures();
	void					  AddSmoothness();
	void					  ApplyTextures();
	void					  SetScale();



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

	void					  Run();

	void					  Tests();

protected:///////////////////////////////////////////////////////////////////////////////////
	
			// Init Data:

	Board				mBoard;

	const char*			path = "gnugo.exe --mode gtp";
	const char*			soundPath = "pop.wav";

	sf::Sound			sound;

	sf::Event			e;

	sf::RenderWindow	mWindow;
	
	sf::ContextSettings mS;

	int					mTestCounter = 0;

			// Runtime Data:
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



