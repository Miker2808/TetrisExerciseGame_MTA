#pragma once
#include "Utility.h"
#include "TetrisGame.h"

extern Settings global_settings;

// MultiplayerTetris class manages the overall flow and logic of a multiplayer Tetris game.
class MultiplayerTetris
{
private:
	TetrisGame** games_arr = nullptr;
	GameState game_state = GameState::NO_GAME_STATE;
	MenuManager menu;
	unsigned int curr_num_of_games = 0;

	

	void setUpNewGame();

	void gameplayLoop();

	void gameOverLogic(unsigned int games_in_play);
	
	void freeGames();

	void allocateGames();

	void updateBoardOffsetPos(unsigned int gameindex , unsigned int& x_pos , unsigned int& y_pos);

public:

	void launcher();

	MultiplayerTetris() {}

	MultiplayerTetris(const MultiplayerTetris& other) = delete;

	MultiplayerTetris& operator=(const MultiplayerTetris& other) = delete;

	~MultiplayerTetris() {
		if (games_arr != nullptr) {
			freeGames();
			delete games_arr;
		}
	}

};

