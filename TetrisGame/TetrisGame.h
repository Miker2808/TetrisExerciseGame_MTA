#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


class TetrisGame {

public:

	void play();
	bool checkCollision(Tetromino& object, TetrisBoard& board, int move_x, int move_y, int move_rot);
	unsigned char inputHandler(Tetromino& object, TetrisBoard& board, unsigned char curr_key);
	void fixTetrominoToBoard(Tetromino& object, TetrisBoard& board);
	void movePiceDown(unsigned char& drop_counter, Tetromino& object, TetrisBoard& board);
};