#pragma once
#include "Utility.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "Player.h"
#include "MenuManager.h"


// TetrisGame class represents the main logic and state of a Tetris game.
// Each user has its own game instance, allowing multiple players to play games with independent in game tick rates.
class TetrisGame {

private:
	// private members
	unsigned int ticks_per_drop = Settings::TICKS_PER_DROP; // kept as a variable to potentionally control drop speed
	int base_score_inc = Settings::BASE_SCORE_INCREMENT;
	unsigned int tick_counter = 0; // counts iterations each for given game session;
	bool bombs_present;
	bool game_over = false;
	bool start_flag = true;
	bool is_player = false;
	size_t current_tetromino_ticks = 0; // lifetime of current tetromino piece
	int last_tetromino_lines_destroyed = 0;

	// private methods
	void movePieceDownAfterTick();
	void findAndDestroyLines(int obj_y_pos);
	void writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index);
	void bombLogic(int obj_x_pos, int obj_y_pos, int obj_rot);
	virtual void movementHandler(unsigned char curr_key);

protected:
	// protected members
	TetrisBoard* board;
	Tetromino* currentTetromino;

	// protected methods
	void updateBoardStatus();
	void playHandler(char curr_key);

public:
	// members
	static unsigned int game_counter;
	Player* player;

	// constructors
	TetrisGame(int start_x, int start_y, bool bombs, bool human_player);
	TetrisGame(const TetrisGame& other);
	TetrisGame& operator=(const TetrisGame& other) = delete;
	// destructor
	virtual ~TetrisGame();
	
	// non-const methods
	void movePieceDown();
	virtual void play(unsigned char curr_key);
	void setGameOver(bool flag);
	void setGameStart(bool flag);

	// const methods
	bool isGameOver() const;
	bool isGameStart() const;
	void printGameStats() const;
	bool checkCollision(int move_x, int move_y, int move_rot) const;
	int getLinesDestroyed() const;
	void findBombCell(const int obj_rot, int& bomb_cell_x_off, int& bomb_cell_y_off) const;
	size_t getCurrentTetrominoTicks() const;

};