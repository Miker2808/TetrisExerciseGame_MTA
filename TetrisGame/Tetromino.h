#pragma once
#include "Utility.h"

extern Settings global_settings;

// Class representing Tetrominos in the game
class Tetromino {

public:
	static const char tetromino_shapes[8][17];

private:
	int rotation;          // Current rotation state
	int x_pos;             // Current X position on the board
	int y_pos;             // Current Y position on the board
	int shape_index;       // Index representing the shape type
	int board_offset_x;    // X offset on the board
	int board_offset_y;    // Y offset on the board
	int start_pos_x;       // Starting X position
	int start_pos_y;       // Starting Y position
	bool bombs_present;     // Indicates wether bombs are used
	

public:

	Tetromino(int start_x, int start_y, int board_start_x, int board_start_y, bool bombs_flag);
	Tetromino(const Tetromino& other);
	// Default copy constructor is in the heart, here.
	~Tetromino();
	void print() const;
	int getCell(int x, int y, int rotation) const;
	void transform(int move_x, int move_y, int rotate = 0);
	void assignTransform(int new_x, int new_y, int new_rotation);
	void getTransform(int& currXpos, int& currYpos, int& currRot) const;
	void getShapeIndex(int& shape_index);
	void resetTetromino();
	void erase() const;
	unsigned int getShapeWidth() const;
	unsigned int getShapeCollisionOffset() const;


private:
	int initShapeindex() const;
	void printBNW(bool erase = false) const;
	void printColor(bool erase = false) const;
	void printCharColor(char c, HANDLE& hConsole) const;
};