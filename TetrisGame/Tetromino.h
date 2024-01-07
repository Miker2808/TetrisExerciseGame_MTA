#pragma once
#include "Utility.h"

class TetrisBoard;

const char tetromino_shapes[5][17] = {
		{"  X   X   X   X "}, // vertical line shape
		{"     XX  XX     "}, // square shape
		{"X   X   X   XX  "}, // L shape
		{" X   XX   X     "}, // S shape
		{"     X  XXX     "}  // T shape
};

// the class of the shapes that move in the game
class Tetromino {

private:
	char* shape = nullptr;
	int rotation;
	int x_pos;
	int y_pos;
	int shape_index;
	int board_offset_x;
	int board_offset_y;
	

public:

	Tetromino(int start_x, int start_y, int board_start_x, int board_start_y);
	void print();
	int rotate(int x, int y, int rotation); 
	void transform(int move_x, int move_y, int rotate = 0);
	void getTransform(int& currXpos, int& currYpos, int& currRot);
	void getShapeIndex(int& shape_index);
};