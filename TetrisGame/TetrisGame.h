#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"

class TetrisGame {

public:

	static constexpr unsigned int BOARD_OFFSET_X = 10;
	static constexpr unsigned int BOARD_OFFSET_Y = 10;

	void play();
	bool checkCollision(Tetromino& object, TetrisBoard& board, int move_x, int move_y, int move_rot);
	unsigned char inputHandler(Tetromino& object, TetrisBoard& board, unsigned char curr_key);
};