#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>

using namespace std;

#define FOREGROUND_MAGENTA	0x0050
#define output_handle	GetStdHandle(STD_OUTPUT_HANDLE)
#define xSize	50
#define ySize	20

char grid[xSize][ySize];
char key = ' ';
int totalBombs = 0;
int playerScore = 0;
bool refresh = false;

struct Vector
{
	int x;
	int y;
};

void sleepTime(int x)
{
	Sleep(x);
}

void gotoxy(short x, short y)
{
	SetConsoleCursorPosition(output_handle, COORD{x, y});
}

bool getInput(char *c)
{
	if (_kbhit())
	{
		*c = _getch();
		return true;
	}
	else
		return false;
}

void cursorVisible()
{
	CONSOLE_CURSOR_INFO info;

	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(output_handle, &info);
}

void levelCreation()
{
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			if (x == 0 || y == 0 || x == 49 || y == 19)
			{
				grid[x][y] = 178;
			}
			else if (y == 18)
			{	
				grid[x][y] = 1;
			}
			else
			{
				grid[x][y] = ' ';
			}
		}
	}

	if (totalBombs <= 4)
	{
		for (int i = totalBombs; i <= 4; i++)
		{
			int random = rand() % 3;

			if (random == 0)
			{
				int randX = rand() % 48;
				grid[randX][1] = '*';
				totalBombs++;
			}
		}
	}

	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			if (x == 0 || y == 0 || x == 49 || y == 19)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else if (y == 18)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			gotoxy(x, y + 3); std::cout << grid[x][y];
		}
	}

	gotoxy(24, 17); std::cout << '_';
}

void bombUpdate()
{
reStart:

	for (int x = 1; x < xSize - 1; x++)
	{
		for (int y = 1; y < ySize - 1; y++)
		{
			if (grid[x][y] == '*')
			{
				if (grid[x][y + 1] == ' ' || grid[x][y + 1] == 1)
				{

					int tempY = y + 1;

					grid[x][y] = ' ';
					grid[x][tempY] = '*';

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

					gotoxy(x, y + 3); std::cout << grid[x][y];

					gotoxy(x, tempY + 3); std::cout << grid[x][tempY];

					y += 2;
				}
				else if (grid[x][y + 1] == '_')
				{
					grid[x][y] = ' ';
					gotoxy(x, y + 3); std::cout << grid[x][y];

					totalBombs--;
					playerScore++;

					gotoxy(0, 23); std::cout << "Your Score:" << playerScore << endl;
				}
				else
				{
					grid[x][y] = ' ';
					gotoxy(x, y + 3); std::cout << grid[x][y];

					totalBombs--;
				}
			}
		}
	}

	if (totalBombs <= 4)
	{
		for (int i = totalBombs; i <= 4; i++)
		{
			int random = rand() % 3;

			if (random == 0)
			{
				int randX = rand() % 48;
				grid[randX][1] = '*';
				totalBombs++;
			}
		}
	}

	sleepTime(500);

	goto reStart;
}

void playerUpdate()
{
	Vector playerPos;

	playerPos.x = 24;
	playerPos.y = 14;

	while (key != 'q')
	{
		refresh = false;

		key = ' ';

		getInput(&key);

		if (key == 'd' || key == 'D')
		{
			if (grid[playerPos.x + 1][14] == ' ')
			{
				grid[playerPos.x][14] = ' ';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerPos.x += 1;

				grid[playerPos.x][14] = '_';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];
			}
			else if (grid[playerPos.x + 1][14] == '*')
			{
				grid[playerPos.x][14] = ' ';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerPos.x += 1;

				grid[playerPos.x][14] = '_';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerScore++;
				totalBombs--;
			}
		}

		if (key == 'a' || key == 'A')
		{
			if (grid[playerPos.x - 1][14] == ' ')
			{
				grid[playerPos.x][14] = ' ';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerPos.x -= 1;

				grid[playerPos.x][14] = '_';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];
			}
			else if (grid[playerPos.x - 1][14] == '*')
			{
				grid[playerPos.x][14] = ' ';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerPos.x -= 1;

				grid[playerPos.x][14] = '_';

				gotoxy(playerPos.x, 17); std::cout << grid[playerPos.x][14];

				playerScore++;
				totalBombs--;
			}
		}
	}
}

void main()
{
	cursorVisible();
	levelCreation();



	grid[24][14] = '_';

	thread normUpdate(playerUpdate);
	thread bombUpdate(bombUpdate);

	char localKey = ' ';

	while(localKey != 'q')
		getInput(&key);

	std::system("pause");
}