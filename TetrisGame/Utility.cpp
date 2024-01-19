#include "Utility.h"

// moves terminal cursor to x,y position
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
//Calculates the positive modulus (remainder) of the division of two integers.
int pyMod(int a , int b) {
	return (b + (a % b)) % b;
}

void debugPrint(const char* string, int param, int x, int y) {
	gotoxy(x, y);
	std::cout << "DEBUG: " << string << " " << param << std::endl;
}


// hides the flashing terminal cursor from the terminal
void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
