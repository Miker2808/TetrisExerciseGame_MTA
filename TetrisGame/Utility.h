#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <conio.h>

#include "Settings.h"

const char TETROMINO_SIZE = 4; // meaning tetrominos are 4 by 4 shape;
//const unsigned int BOARD_OFFSET_X = 5;
//const unsigned int BOARD_OFFSET_Y = 5;

// moves cursor to x,y of terminal
void gotoxy(int x, int y);
int pyMod(int a, int b);
void debugPrint(const char* string, int param, int x, int y);

