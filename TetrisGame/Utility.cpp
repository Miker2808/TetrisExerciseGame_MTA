#include "Utility.h"


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// a - dividend , b - modulus
int pyMod(int a , int b) {
	return (b + (a % b)) % b;
}

void debugPrint(const char* string, int param, int x, int y) {
	gotoxy(x, y);
	std::cout << "DEBUG: " << string << " " << param << std::endl;
}