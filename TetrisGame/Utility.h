#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <conio.h>

constexpr unsigned char TETROMINO_SIZE = 4; // meaning tetrominos are 4 by 4 shape;
constexpr unsigned int BOARD_OFFSET_X = 5;
constexpr unsigned int BOARD_OFFSET_Y = 5;

// moves cursor to x,y of terminal
void gotoxy(int x, int y);
int pyMod(int a, int b);


