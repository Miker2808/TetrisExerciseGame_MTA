#pragma once
#include "Utility.h"

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
	int x_pos;
	int y_pos;
	
	

public:
	int rotation;
	int shape_index;
	Tetromino(); // randomly generate a tetromino
	void print();
	int rotate(int x, int y, int rotation);
	void transform(int x, int y, int r=0);
};