#pragma once
#include "Utility.h"
#include "Player.h"


extern Settings global_settings;

// Game state enumeration
enum class GameState { NEW_GAME = 500, PAUSED_GAME, RESUME_GAME, EXIT_GAME, GAME_OPTIONS, NO_GAME_STATE, IN_PROGRESS_GAME};

class MenuManager {

private:
	
	bool game_started = false;
	GameState current_state = GameState::NO_GAME_STATE;


public:
	GameState mainMenu(GameState state);
	void optionsMenu();
	void printGameOverMenu(int player_indx, int score);

private:
	void mainMenuLogic(unsigned char curr_key);
	void printMainMenu();
	void printControls();
	void printOptionsMenu();


};