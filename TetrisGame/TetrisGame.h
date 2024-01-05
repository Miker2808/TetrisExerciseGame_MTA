#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"

class TetrisGame {

public:

	void play();
	bool checkCollision(Tetromino object, TetrisBoard board, int posX, int posY);
};