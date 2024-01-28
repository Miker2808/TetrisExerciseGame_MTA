#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "Player.h"
#include "MenuManager.h"


// TetrisGame class represents the main logic and state of a Tetris game.
// NOTE: Each user has its own game instance, allowing multiple players to play games with independent in game tick rates.
class TetrisGame {

public:
	// public members
	static const unsigned int TICKS_TIME = Settings::TICKS_TIME;
	int base_score_inc = Settings::BASE_SCORE_INCREMENT;
	static unsigned int game_counter;
	unsigned int ticks_survived = 0;

	TetrisBoard* board;
	Tetromino* currentMino;
	Player* player;

	bool bombs_present;
	bool game_over = false;
	bool start = true;
	bool human_player = false;

	size_t current_tetromino_ticks = 0; // lifetime of current tetromino piece
	
	
protected:
	// protected members
	unsigned int tick_counter = 0; // counts iterations each for given game session;
	unsigned int ticks_per_drop = Settings::TICKS_PER_DROP; // kept as a variable to potentionally control drop speed

public:
	TetrisGame(int start_x, int start_y, bool bombs, bool human_player);
	TetrisGame(const TetrisGame& other);
	~TetrisGame();
	void play(unsigned char curr_key);
	
	// for the heuristics
	void updateBoardStatus();
	bool checkCollision(int move_x, int move_y, int move_rot);

protected:

	void forcePiceDown();
	void movementHandler(unsigned char curr_key);
	void findAndDestroyLines(int obj_y_pos);
	void writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index);
	void blowBombUp(int obj_x_pos, int obj_y_pos, int obj_rot);
	void printGameStats();
	void movePiceDown();
	

};