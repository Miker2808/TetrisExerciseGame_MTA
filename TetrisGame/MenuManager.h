#pragma once
#include "Utility.h"
#include "Player.h"
#include "Settings.h"


extern Settings global_settings;

// enume has to be all caps
enum class GameState { NEW_GAME = 500, PAUSED_GAME, RESUME_GAME, EXIT_GAME, GAME_OPTIONS, NO_GAME_STATE, IN_PROGRESS_GAME};

class MenuManager {
public:
	

private:
	
	bool game_started = false;
	//GameState state = GameState::NO_GAME_STATE;

public:
	
	GameState mainMenu(GameState state);
	void printMainMenu();
	void printControls();
	GameState mainMenuLogic(unsigned char curr_key);
	GameState optionsMenu();
	void printGameOverMenu(int player_indx, int score);
	void printOptionsMenu();

};