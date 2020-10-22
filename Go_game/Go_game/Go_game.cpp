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
#define BLACK (1)
#define WHITE (2)


/***************************************************************************************/
STARTUPINFO sti = { 0 };
SECURITY_ATTRIBUTES sats = { 0 };
PROCESS_INFORMATION pi = { 0 };
HANDLE pipin_w, pipin_r;
HANDLE pipout_w, pipout_r;
BYTE buffer[2048];
DWORD write, excode, read, avaiable;


/***************************************************************************************/
void ConnectToEngine(const char* path)
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
string getNextMove(string position)
{

	string str;

	position = "play black " + position + "\ngenmove white\n";

	printf("%s\n", position.c_str());

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

	printf("%s\n", str.c_str());

	int n = str.rfind("=");


	return str.substr(n + 1);
}


/***************************************************************************************/
void CloseConnection()
{
	WriteFile(pipin_w, "quit\n", 5, &write, NULL);
	if (pipin_w != NULL) CloseHandle(pipin_w);
	if (pipin_r != NULL) CloseHandle(pipin_r);
	if (pipout_w != NULL) CloseHandle(pipout_w);
	if (pipout_r != NULL) CloseHandle(pipout_r);
	if (pi.hProcess != NULL) CloseHandle(pi.hProcess);
	if (pi.hThread != NULL) CloseHandle(pi.hThread);
}


/***************************************************************************************/
bool live_check(int color, int x, int y, Game& R)
{
	if (R.get_visit(y,x))
		return false;			// to remove cycle

	R.get_visit(y, x) = true;

	if (R.get_board(y, x) == 0)
	{
		return true;			// empty space means the dragon is alive
	}

	if (R.get_board(y, x) != color)
		return false;			// captured by enemy stone

	// recursive search
	bool
		r = x > 0 && live_check(color, x - 1, y, R);
	r |= x < 19 - 1 && live_check(color, x + 1, y, R);
	r |= x > 0 && live_check(color, x, y - 1, R);
	r |= y < 19 - 1 && live_check(color, x, y + 1, R);

	return r;
}


/***************************************************************************************/
void remove_dead_stone(int color, Game& R)
{
	int capture[19][19] = { 0 };

	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (R.get_board(y, x) != color)
				continue;

			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 19; j++)
					R.get_visit(i, j) = false;

			if (live_check(color, x, y, R) == false)
				capture[y][x] = 1;
		}

	for (int y = 0; y < 19; y++)
		for (int x = 0; x < 19; x++)
		{
			if (capture[y][x])
				R.get_board(y, x) = 0;
		}
};


/***************************************************************************************/



/***************************************************************************************/
void MousePressEvent(Sprite& bs, Sprite& ws, RenderWindow& window, Event e, Game& R)
{
	if (e.type == Event::MouseButtonPressed)
	{

		int ix = e.mouseButton.x / R.get_cell();
		int iy = e.mouseButton.y / R.get_cell();

		// Put Black Stone with left click
		if (e.mouseButton.button == Mouse::Left)
		{
			if (R.get_board(ix, iy) != BLACK && R.get_board(ix, iy) != WHITE)
			{
				R.get_board(ix, iy) = BLACK;
				remove_dead_stone(WHITE, R);
				R.update();


				// AI
				char move[10] = { 0 };
				ix += 'A';
				if (ix >= 'I') ix += 1;
				sprintf(move, "%c%d", ix, iy + 1);
				string ret = getNextMove(move);
				sscanf(ret.c_str(), " %c%d\r\n\r\n", &ix, &iy);
				if (ix >= 'J') ix--;
				ix -= 'A';
				R.get_board(iy - 1, ix) = WHITE;  // AI will play white stones!
				remove_dead_stone(BLACK, R);
				R.update();

			}

		}
	}
}


/***************************************************************************************/
void WindowIsOpen(Sprite& bs, Sprite& ws, RenderWindow& window, Game& R)
{
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			MousePressEvent(bs, ws, R.get_mWindow(), e, R);
			
		}
		R.update();
	}
}


/***************************************************************************************/
int main()
{
	ConnectToEngine("gnugo.exe --mode gtp");

	ContextSettings s;
	s.antialiasingLevel = 8;

	Game R(s);

	R.LoadTextures();

	R.AddSmoothness();

	R.ApplyTextures();

	R.SetScale();

	R.update();

	WindowIsOpen(R.get_bs(), R.get_ws(), R.get_mWindow(), R);

	return 0;
}
