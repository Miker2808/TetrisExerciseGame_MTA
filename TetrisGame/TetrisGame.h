#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "Player.h"
#include "MenuManager.h"



class TetrisGame {

public:
	// public members
	static const unsigned int TICKS_TIME = Settings::TICKS_TIME;
	int base_score_inc = Settings::BASE_SCORE_INCREMENT;

	TetrisBoard* board;
	Tetromino* currentMino;
	Player* player;
	bool game_over = false;
	bool start = true;
	
	
private:
	// private members
	unsigned int tick_counter = 0; // counts iterations each for given game session;
	unsigned int ticks_per_drop = Settings::TICKS_PER_DROP; // kept as a variable to potentionally control drop speed

public:
	TetrisGame(int start_x, int start_y);
	~TetrisGame();
	void play(unsigned char curr_key);

private:

	bool checkCollision(int move_x, int move_y, int move_rot);
	void movementHandler(unsigned char curr_key);
	void updateBoardStatus();
	void findAndDestroyLines(int obj_y_pos);
	void writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index);
	void movePiceDown();
	void printGameStats();
	void forcePiceDown();

};