#pragma once
#include "Utility.h"

class TetrisBoard;

const char tetromino_shapes[5][17] = {
		{"  A   A   A   A "}, // vertical line shape
		{"     BB  BB     "}, // square shape
		{"C   C   C   CC  "}, // L shape
		{" D   DD   D     "}, // S shape
		{"     E  EEE     "}  // T shape
};

// the class of the shapes that move in the game
class Tetromino {

private:
	int rotation;
	int x_pos;
	int y_pos;
	int shape_index;
	int board_offset_x;
	int board_offset_y;
	int start_pos_x;
	int start_pos_y;
	

public:

	Tetromino(int start_x, int start_y, int board_start_x, int board_start_y);
	~Tetromino();
	void print();
	Tetromino(int start_x, int start_y, int board_offset_x, int board_offset_y);
	int rotate(int x, int y, int rotation);
	void transform(int move_x, int move_y, int rotate = 0);
	void getTransform(int& currXpos, int& currYpos, int& currRot);
	void getShapeIndex(int& shape_index);
	void resetTetromino();
};