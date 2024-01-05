#pragma once
#include "Utility.h"

constexpr long DEFAULT_BOARD_WIDTH = 12;
constexpr long DEFAULT_BOARD_HEIGHT = 18;

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
	explicit TetrisBoard(int width = DEFAULT_BOARD_WIDTH, int height = DEFAULT_BOARD_HEIGHT);
	~TetrisBoard();
	void printBoard(int x, int y);

private:
	
	void allocateBoard(int rows, int cols);

	void freeBoard(int rows);


};


