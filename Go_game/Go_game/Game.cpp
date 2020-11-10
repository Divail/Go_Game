#include <iostream>

#include "Game.h"


void Test_MyGame();


/***************************************************************************************/
Game::Game()
:
	mBoard( *this ),
	mWindow(sf::VideoMode(mBoard.get_cell() * 19, mBoard.get_cell() * 19), "Go", sf::Style::Default, mS)
{
	mS.antialiasingLevel = 8;
}


/***************************************************************************************/
Game::~Game()
{
}


/***************************************************************************************/
void Game::LoadTextures()
{
	bt.loadFromFile("black_stone.bmp");
	wt.loadFromFile("white_stone.bmp");
}


/***************************************************************************************/
void Game::AddSmoothness()
{
	// Apply Smoothness for Black Stone
	bt.setSmooth(true);
	// Apply Smoothness for White Stone
	wt.setSmooth(true);
}


/***************************************************************************************/
void Game::ApplyTextures()
{
	bs.setTexture(bt);
	ws.setTexture(wt);
}


/***************************************************************************************/
void Game::SetScale()
{
	bs.setScale(mBoard.get_cell() / bs.getLocalBounds().width, mBoard.get_cell() / bs.getLocalBounds().height);
	ws.setScale(mBoard.get_cell() / ws.getLocalBounds().width, mBoard.get_cell() / ws.getLocalBounds().height);
}


/***************************************************************************************/
void Game::update()
{
	mWindow.clear(sf::Color(255, 207, 97));

	mBoard.draw_board();

	// Draw stone
	mBoard.draw_stone();

	mWindow.display();
};


/***************************************************************************************/
void Game::remove_dead_stone(int color)
{
	int capture[19][19] = { 0 };

	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (mBoard.set_board(y, x) != color)
				continue;

			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 19; j++)
					mBoard.set_visit(i, j) = false;

			if (live_check(color, x, y) == false)
				capture[y][x] = 1;
		}

	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (capture[y][x])
				mBoard.set_board(y, x) = 0;
		}
};


/***************************************************************************************/
bool Game::live_check(int color, int x, int y)
{
	if (mBoard.set_visit(y, x) )
		return false;			// to remove cycle

	mBoard.set_visit(y, x) = true;

	if (mBoard.set_board(y, x) == 0)
	{
		return true;			// empty space means the dragon is alive
	}

	if (mBoard.set_board(y, x) != color)
		return false;			// captured by enemy stone

	// recursive search
	bool
		r = x > 0 && live_check(color, x - 1, y);
	r |= x < 19 - 1 && live_check(color, x + 1, y);
	r |= x > 0 && live_check(color, x, y - 1);
	r |= y < 19 - 1 && live_check(color, x, y + 1);

	return r;
}


/***************************************************************************************/
void Game::ConnectToEngine()
{
	pipin_w = pipin_r = pipout_w = pipout_r = NULL;
	sats.nLength = sizeof(sats);
	sats.bInheritHandle = TRUE;
	sats.lpSecurityDescriptor = NULL;

	CreatePipe(&pipout_r, &pipout_w, &sats, 0);
	CreatePipe(&pipin_r, &pipin_w, &sats, 0);

	sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sti.wShowWindow = SW_HIDE;
	sti.hStdInput = pipin_r;
	sti.hStdOutput = pipout_w;
	sti.hStdError = pipout_w;

	assert(CreateProcess(NULL, (char*)path, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi));
}


/***************************************************************************************/
std::string Game::getNextMove(std::string position)
{

	std::string str;

	position = "play black " + position + "\ngenmove white\n";

	std::cout << "\n" << position;

	WriteFile(pipin_w, position.c_str(), position.length(), &write, NULL);
	Sleep(500);

	PeekNamedPipe(pipout_r, buffer, sizeof(buffer), &read, &avaiable, NULL);

A:
	do
	{
		ZeroMemory(buffer, sizeof(buffer));
		if (!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read)
			break;

		buffer[read] = 0;

		str += (char*)buffer;
	} while (read >= sizeof(buffer));

	if (str.length() <= 5)
		goto A;

	std::cout << "\n" << str;

	int n = str.rfind("=");

	return str.substr(n + 1);
}


/***************************************************************************************/
void Game::CloseConnection()
{
	WriteFile(pipin_w, "quit\n", 5, &write, NULL);

	if (pipin_w)     CloseHandle(pipin_w);
	if (pipin_r)     CloseHandle(pipin_r);
	if (pipout_w)    CloseHandle(pipout_w);
	if (pipout_r)    CloseHandle(pipout_r);
	if (pi.hProcess) CloseHandle(pi.hProcess);
	if (pi.hThread)  CloseHandle(pi.hThread);
}


/***************************************************************************************/
void Game::MousePressEvent()
{
	if (mTestCounter < 1)
	{
		if (e.key.code == sf::Keyboard::F6)
		{
			Tests();
		}

		++mTestCounter;
	}

	if (e.type == sf::Event::MouseButtonPressed)
	{

		int ix = e.mouseButton.x / mBoard.get_cell();
		int iy = e.mouseButton.y / mBoard.get_cell();


		// Put Black Stone with left click
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (mBoard.set_board(ix, iy) != BLACK && mBoard.set_board(ix, iy) != WHITE)
			{
				mBoard.set_board(ix, iy) = BLACK;
				
				// Sound
				sf::SoundBuffer buffer;
				buffer.loadFromFile(soundPath);
				sound.setBuffer(buffer);
				sound.play();

				remove_dead_stone(WHITE);

				update();

				// AI
				//char move[10] = { 0 };

				ix += 'A';

				if (ix >= 'I') 
					ix += 1;

				//
				// MY MOVE:
				//
				//sprintf(move, "%c%d", ix, iy + 1);
				std::ostringstream buff;
				buff << (char)ix << iy + 1;


				// SEND TO ENGINE and GET HIS MOVE:
				std::string ret = getNextMove(buff.str());


				//
				// EXTRACT ENGINE MOVE from string:
				//
				std::istringstream buff2(ret);
				char ch = ix;
				buff2 >> ch >> iy;

				if (ix >= 'J')
					ix--;

				ix -= 'A';

				if (mBoard.set_board( iy - 1, ix ) != BLACK && mBoard.set_board( iy - 1, ix ) != WHITE)
					mBoard.set_board( iy - 1, ix ) = WHITE;  // AI will play white stones!
				else
					mBoard.set_board( iy, ix - 1 ) = WHITE;

				sound.play();

				remove_dead_stone(BLACK);

				update();

			}
		}
	}
}

/***************************************************************************************/
void Game::WindowIsOpen()
{
	while (mWindow.isOpen())
	{
		while (mWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				mWindow.close();

			MousePressEvent();

		}
		update();
	}
}


/***************************************************************************************/
void Game::Run()
{
	ConnectToEngine();

	LoadTextures();

	AddSmoothness();

	ApplyTextures();

	SetScale();

	update();

	WindowIsOpen();
}


/***************************************************************************************/
void Game::Tests()
{
	NewTests();

	Test_MyGame();

	EndTests();
}