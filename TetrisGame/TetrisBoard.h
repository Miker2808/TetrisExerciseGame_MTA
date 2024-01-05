#pragma once
#include "Utility.h"


class TetrisBoard {

public:
	char** board = nullptr;
	const int board_width;
	const int board_height;
	
private:
	const char wall = '#';
	const char def_empty = ' '; // space

// methods
public:
	TetrisBoard(int width, int height);
	~TetrisBoard();
	void printBoard(int x, int y);

private:
	
	void allocateBoard(int rows, int cols);

	void freeBoard(int rows);


};


