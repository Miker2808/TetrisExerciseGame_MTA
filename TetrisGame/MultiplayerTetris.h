#pragma once
#include "Utility.h"
#include "TetrisGame.h"

extern Settings global_settings;


class MultiplayerTetris
{

	TetrisGame* players[Settings::NUMBER_OF_PLAYERS] = { nullptr, nullptr };
	GameState game_state = GameState::NO_GAME_STATE;
	MenuManager menu;

public:
	void launcher();

	void setUpNewGame();

	void gameplayLoop();

	void gameOverLogic();

};

