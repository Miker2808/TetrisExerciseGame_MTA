#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "Player.h"


class TetrisGame {

public:

	static constexpr unsigned int BOARD_OFFSET_X = 10;
	static constexpr unsigned int BOARD_OFFSET_Y = 10;
	static constexpr unsigned int TICKS_TIME = 50;
	TetrisBoard* board;
	Tetromino* currentMino;
	Player* player;
	
private:
	unsigned int tick_counter = 0; // counts iterations each for given game session;
	unsigned int ticks_per_drop = 20; // kept as a variable to potentionally control drop speed

public:
	TetrisGame(int start_x, int start_y);
	~TetrisGame();
	void play(unsigned char curr_key);
	bool checkCollision(int move_x, int move_y, int move_rot);
	void movementHandler(unsigned char curr_key);
	void fixTetrominoToBoard();
	void movePiceDown();
};