#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define output_handle	GetStdHandle(STD_OUTPUT_HANDLE)
#define MAGENTA			0x0005

struct Vector
{
	int x;
	int y;
};

int framecount = 0;
int lastTime = 0;

bool init = true;
bool refresh = false;
Vector playerPos;
double startTime = timeGetTime();

char drawArray[20][20]
{
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' },
	{ 'O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O' }
};

void gotoxy(short x, short y)
{
	SetConsoleCursorPosition(output_handle, COORD{ x, y});
}

void setCursorVisibility(bool visible)
{
	CONSOLE_CURSOR_INFO cciInfo;
	cciInfo.dwSize = 1;
	cciInfo.bVisible = visible;

	SetConsoleCursorInfo(output_handle, &cciInfo);
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

void drawEngine()
{
	setCursorVisibility(false);

	//To start, draw a 20x20 grid of 0's
	if (init)
	{	
		//Draws Grid
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(i, j);
				std::cout << drawArray[i][j];
			}
		}

		//Adds Traps
		int numTraps = (rand() % 10) + 7;

		for (int i = 0; i < numTraps; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			int randX = (rand() % 20);
			int randY = (rand() % 20);
			
			drawArray[randX][randY] = 'T';
			gotoxy(randX, randY); std::cout << drawArray[randX][randY];

		}

		//Add "robots"
		/*
		int numRobots = 5;

		for (int i = 0; i < numTraps; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA | FOREGROUND_INTENSITY);

				int randX = (rand() % 20);
				int randY = (rand() % 20);

				drawArray[randX][randY] = 'R';
				gotoxy(randX, randY); std::cout << drawArray[randX][randY];

		}

		*/

		drawArray[1][1] = 'X';
		playerPos.x = 1;
		playerPos.y = 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		gotoxy(1, 1); std::cout << drawArray[1][1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		init = false;
	}
	else if(refresh)
	{
		//Refresh Grid
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(i, j);

				if(j == playerPos.y && i == playerPos.x)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				else if(drawArray[i][j] == 'T')
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				else if (drawArray[i][j] == 'R')
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA | FOREGROUND_INTENSITY);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				std::cout << drawArray[i][j];
			}
		}

		refresh = false;
	}
}

/*void robotAI()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (drawArray[i][j] == 'R')
			{
				int dir = rand() % 4;

				if (dir == 0)
				{
					//Go Left
					drawArray[i][j] = 'O';
					drawArray[i - 1][j] = 'R';
				}
				if (dir == 1)
				{
					//Go Right
					drawArray[i][j] = 'O';
					drawArray[i + 1][j] = 'R';
				}
				if (dir == 2)
				{
					//Go Up
					drawArray[i][j] = 'O';
					drawArray[i][j - 1] = 'R';
				}
				if (dir == 3)
				{
					//Go Down
					drawArray[i][j] = 'O';
					drawArray[i][j + 1] = 'R';
				}
			}
		}
		refresh = true;
		drawEngine();
	}
}
*/

void timerUpdate()
{
	double currentTime = timeGetTime() - lastTime;

	if (currentTime < 30)
		return;

	framecount++;

	lastTime = timeGetTime();
}

void main()
{	

GameStart:
	CONSOLE_FONT_INFOEX lol;

	lol.FontWeight = 1000;
	lol.dwFontSize = COORD{20000,20000};
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), true, &lol);

	char key = ' ';

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	bool in1t = true;

	while (timeGetTime() - startTime <= 2000)
	{
		if (in1t == true)
		{
			cout << "Loading... Try not to walk into the traps\n";
			in1t = false;
		}
	}

	system("cls");

	while (key != 'q')
	{	
		drawEngine();
		getInput(&key);
		
		if (key == 'w' || key == 'W')
		{
			if (playerPos.y - 1 < 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, that is out of bounds...";
			}
			else if (drawArray[playerPos.x][playerPos.y - 1] == 'O')
			{
				int tempY = playerPos.y - 1;

				drawArray[playerPos.x][tempY] = 'X';

				drawArray[playerPos.x][playerPos.y] = 'O';

				playerPos.y--;

				refresh = true;
				key = ' ';
			}

			else if (drawArray[playerPos.x][playerPos.y - 1] == 'T')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, you tragically walked into a trap and died...";
				key = 'q';
			}
		}
		else if (key == 's' || key == 'S')
		{
			if (playerPos.y + 1 > 19)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, that is out of bounds...";
			}
			else if (drawArray[playerPos.x][playerPos.y + 1] == 'O')
			{
				int tempY = playerPos.y + 1;

				drawArray[playerPos.x][tempY] = 'X';

				drawArray[playerPos.x][playerPos.y] = 'O';

				playerPos.y++;

				refresh = true;
				key = ' ';
			}
			else if (drawArray[playerPos.x][playerPos.y + 1] == 'T')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, you tragically walked into a trap and died...";
				key = 'q';
			}
		}
		if (key == 'a' || key == 'A')
		{
			if (playerPos.x - 1 < 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, that is out of bounds...";
			}
			else if (drawArray[playerPos.x - 1][playerPos.y] == 'O')
			{
				int tempX = playerPos.x - 1;
				drawArray[tempX][playerPos.y] = 'X';
				drawArray[playerPos.x][playerPos.y] = 'O';

				playerPos.x--;

				refresh = true;
				key = ' ';
			}
			else if (drawArray[playerPos.x - 1][playerPos.y] == 'T')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, you tragically walked into a trap and died...";
				key = 'q';
			}
		}
		if (key == 'd' || key == 'D')
		{
			if (playerPos.x + 1 > 19)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, that is out of bounds...";
			}
			else if (drawArray[playerPos.x + 1][playerPos.y] == 'O')
			{
				int tempX = playerPos.x + 1;
				drawArray[tempX][playerPos.y] = 'X';
				drawArray[playerPos.x][playerPos.y] = 'O';

				playerPos.x++;

				refresh = true;
				key = ' ';
			}
			else if (drawArray[playerPos.x + 1][playerPos.y] == 'T')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				gotoxy(25, 2); std::cout << "Sorry, you tragically walked into a trap and died...";
				key = 'q';
			}
		}
	}

	char temp = ' ';

	gotoxy(0, 22);
	std::cout << "Would you like to play again?(y/n) ";
	std::cin >> temp;

	if (temp == 'y')
	{
		init = true;   
		system("cls");

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				drawArray[i][j] = 'O';
			}
		}

		goto GameStart;
	}
}