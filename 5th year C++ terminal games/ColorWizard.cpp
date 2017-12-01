#include "stdafx.h"
#include <Windows.h>
#include <iostream>

int text;

int notmain()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	std::cout << "TIC TAC TOE GAME";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "TIC TAC TOE GAME";

	std::cin >> text;

	return 0;
}