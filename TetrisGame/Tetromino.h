#pragma once
#include "Utility.h"

extern Settings global_settings;

/*
const char tetromino_shapes[7][17] = {
		{"  A   A   A   A "}, // vertical line shape
		{"     BB  BB     "}, // square shape
		{"    C   C   CC  "}, // L shape
		{" D   DD   D     "}, // S shape
		{"     E  EEE     "}, // T shape
		{"       F   F  FF"}, // inverted L shape
		{"  G  GG  G      "}  // inverted S shape
};
*/

// Class representing Tetrominos in the game
class Tetromino {

public:
	static const char tetromino_shapes[7][17];

private:
	int rotation;          // Current rotation state
	int x_pos;             // Current X position on the board
	int y_pos;             // Current Y position on the board
	int shape_index;       // Index representing the shape type
	int board_offset_x;    // X offset on the board
	int board_offset_y;    // Y offset on the board
	int start_pos_x;       // Starting X position
	int start_pos_y;       // Starting Y position
	

public:

	Tetromino(int start_x, int start_y, int board_start_x, int board_start_y);
	~Tetromino();
	void print();
	int rotate(int x, int y, int rotation);
	void transform(int move_x, int move_y, int rotate = 0);
	void getTransform(int& currXpos, int& currYpos, int& currRot);
	void getShapeIndex(int& shape_index);
	void resetTetromino();
	void erase();


private:
	void printBNW(bool erase = false);
	void printColor(bool erase = false);
	void printCharColor(char c, HANDLE& hConsole);
};