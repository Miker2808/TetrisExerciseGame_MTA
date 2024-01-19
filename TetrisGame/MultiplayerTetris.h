#pragma once
#include "Utility.h"
#include "TetrisGame.h"

extern Settings global_settings;

// MultiplayerTetris class manages the overall flow and logic of a multiplayer Tetris game.
class MultiplayerTetris
{
private:
	TetrisGame* players[Settings::NUMBER_OF_PLAYERS] = { nullptr, nullptr };
	GameState game_state = GameState::NO_GAME_STATE;
	MenuManager menu;

	

	void setUpNewGame();

	void gameplayLoop();

	void gameOverLogic();

public:

	void launcher();

	MultiplayerTetris() {}

	MultiplayerTetris(const MultiplayerTetris& other ) {
		delete(this);
	}

	~MultiplayerTetris() {
		if (players[0] != nullptr) {
			delete players[0];
		}
		if (players[1] != nullptr) {
			delete players[1];
		}
	}

};

