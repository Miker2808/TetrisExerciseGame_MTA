#pragma once
#include "Utility.h"

enum GameState {none, init_new_game , game_paused , resume_game , game_exit};

class MenuManager {
public:

	GameState mainMenu(GameState curr_state);
	GameState mainMenuLogic(GameState curr_token);
	void optionsMenu();

};