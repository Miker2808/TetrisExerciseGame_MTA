#pragma once
#include "Utility.h"

extern Settings global_settings;

class TetrisBoard {

public:
	/*
	static const long DEFAULT_BOARD_WIDTH = Settings::DEFAULT_BOARD_WIDTH;
	static const long DEFAULT_BOARD_HEIGHT = Settings::DEFAULT_BOARD_HEIGHT;
	*/
	char** board = nullptr;
	const int board_start_x; // X offset from console edge of board location
	const int board_start_y;  // Y offset from console edge of board location
	const int board_width;
	const int board_height;
	
	
private:
	const char wall = Settings::DEFAULT_WALL_SIGN;
	const char def_empty = Settings::DEFAULT_EMPTY; // space

// methods
public:
	explicit TetrisBoard(
		int pos_x = 0,
		int pos_y = 0,
		int width = Settings::DEFAULT_BOARD_WIDTH,
		int height = Settings::DEFAULT_BOARD_HEIGHT
		);

	~TetrisBoard();
	void printBoard();
	void writeCellToBoard(int x_coor, int y_coor, char cell_contents);
	bool isALine(int y_coor);
	void destroyLine(int y_coor);
	void shiftBoardDown(int y_shift);
	void printTetrisColor(char c, HANDLE& hConsole);

private:
	
	void allocateBoard(int rows, int cols);
	
	void freeBoard(int rows);


};


