#pragma once
#include "Utility.h"

constexpr long DEFAULT_BOARD_WIDTH = 14;
constexpr long DEFAULT_BOARD_HEIGHT = 19;

class TetrisBoard {

public:
	char** board = nullptr;
	const int board_start_x; // X offset from console edge of board location
	const int board_start_y;  // Y offset from console edge of board location
	const int board_width;
	const int board_height;
	
private:
	const char wall = '#';
	const char def_empty = ' '; // space

// methods
public:
	explicit TetrisBoard(
		int pos_x = 0,
		int pos_y = 0,
		int width = DEFAULT_BOARD_WIDTH, 
		int height = DEFAULT_BOARD_HEIGHT
		);
	~TetrisBoard();
	void printBoard();
	void writeCellToBoard(int x_coor, int y_coor, char cell_contents);
	bool isALine(int y_coor);
	void destroyLine(int y_coor);

	void shiftBoardDown(int y_shift);

private:
	
	void allocateBoard(int rows, int cols);

	void freeBoard(int rows);


};


