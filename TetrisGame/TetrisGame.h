#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"

#define Board_OFFEST_T_X 10
#define Board_OFFEST_T_Y 10
class TetrisGame {

public:

	void play();
	bool checkCollision(Tetromino& object, TetrisBoard& board, int move_x, int move_y, int move_rot);
	unsigned char inputHandler(Tetromino& object, TetrisBoard& board, unsigned char curr_key);
};