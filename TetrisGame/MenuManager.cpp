#include "MenuManager.h"

// inner loop for the main menu options
// will receive a state as a prameter from the main loop
// and will return a state back
//Handles the Tetris main menu logic, allowing user navigation and returning the game.
GameState MenuManager::mainMenu(GameState state) {
	unsigned char curr_key = 0;
	current_state = state;

	while (current_state != GameState::NEW_GAME && current_state != GameState::EXIT_GAME && current_state != GameState::IN_PROGRESS_GAME)
	{
		this->printMainMenu();

		curr_key = _getch();

		mainMenuLogic(curr_key);

		curr_key = 0;
	}
	system("cls");
	return current_state;
}


//Displays the main menu with options such as starting a new game, continuing the game (if already started),
//accessing options, and exiting the game.
void MenuManager::printMainMenu() const
{
	system("cls");
	std::cout << "\n\n   Tetris\n";
	std::cout << "  Main menu\n";
	std::cout << "~~~~~~~~~~~~~~\n\n";
	std::cout << "Choose key:\n";
	std::cout << "[" << Settings::MENU_ONE << "] New Game - Player Vs Player\n";
	std::cout << "[" << Settings::MENU_TWO << "] New Game - Player Vs Computer\n";
	std::cout << "[" << Settings::MENU_THREE << "] New Game - Computer Vs Computer\n";
	if (this->game_started) {
		std::cout << "[" << Settings::MENU_FOUR << "] Continue Game\n";
	}
	std::cout << "[" << Settings::MENU_OPTIONS << "] Options\n";
	std::cout << "[" << Settings::MENU_EXIT << "] Exit Game\n";
}

// Prints controls extracted from pointers of player_1 and player_2.
void MenuManager::printControls() const
{
	int x = 25;
	int y = 1;
	gotoxy(x, y++);
	std::cout << "Player 1 controls:";
	gotoxy(x, y++);
	std::cout << "Left: " << global_settings.ctrl_presets[0].MOVE_LEFT_KEY_1 << " or " << global_settings.ctrl_presets[0].MOVE_LEFT_KEY_2;
	std::cout << " || Right: " << global_settings.ctrl_presets[0].MOVE_RIGHT_KEY_1 << " or " << global_settings.ctrl_presets[0].MOVE_RIGHT_KEY_2;
	gotoxy(x, y++);
	std::cout << "Rotate Clockwise: " << global_settings.ctrl_presets[0].ROT_RIGHT_KEY_1 << " or " << global_settings.ctrl_presets[0].ROT_RIGHT_KEY_2;
	std::cout << " || Rotate Counterclock: " << global_settings.ctrl_presets[0].ROT_LEFT_KEY_1 << " or " << global_settings.ctrl_presets[0].ROT_LEFT_KEY_1;
	gotoxy(x, y++);
	std::cout << "Drop: " << global_settings.ctrl_presets[0].DROP_KEY_1 << " or " << global_settings.ctrl_presets[0].DROP_KEY_2;
	y += 2;
	gotoxy(x, y++);
	std::cout << "Player 2 controls:";
	gotoxy(x, y++);
	
	std::cout << "Left: " << global_settings.ctrl_presets[1].MOVE_LEFT_KEY_1 << " or " << global_settings.ctrl_presets[1].MOVE_LEFT_KEY_2;
	std::cout << " || Right: " << global_settings.ctrl_presets[1].MOVE_RIGHT_KEY_1 << " or " << global_settings.ctrl_presets[1].MOVE_RIGHT_KEY_2;
	gotoxy(x, y++);
	std::cout << "Rotate Clockwise: " << global_settings.ctrl_presets[1].ROT_RIGHT_KEY_1 << " or " << global_settings.ctrl_presets[1].ROT_RIGHT_KEY_2;
	std::cout << " || Rotate Counterclock: " << global_settings.ctrl_presets[1].ROT_LEFT_KEY_1 << " or " << global_settings.ctrl_presets[1].ROT_LEFT_KEY_1;
	gotoxy(x, y++);
	std::cout << "Drop: " << global_settings.ctrl_presets[1].DROP_KEY_1 << " or " << global_settings.ctrl_presets[1].DROP_KEY_2;
}


//Updates game state based on user input from the main menu.
void MenuManager::mainMenuLogic(unsigned char curr_key)
{
	switch (curr_key) {
		case Settings::MENU_ONE:
			this->game_started = true;
			current_state = GameState::NEW_GAME;
			global_settings.num_of_bots = 0;
			global_settings.num_of_human_players = 2;
			return;
		case Settings::MENU_TWO:
			this->game_started = true;
			current_state = GameState::NEW_GAME;
			global_settings.num_of_bots = 1;
			global_settings.num_of_human_players = 1;
			return;

		case Settings::MENU_THREE:
			this->game_started = true;
			current_state = GameState::NEW_GAME;
			global_settings.num_of_bots = 2;
			global_settings.num_of_human_players = 0;
			return;

		case Settings::MENU_FOUR:
			if (this->game_started) {
				current_state = GameState::IN_PROGRESS_GAME;
				return;
			}
			break;
		case Settings::MENU_OPTIONS:
			this->optionsMenu();
			return;
		case Settings::MENU_EXIT:
			current_state = GameState::EXIT_GAME;
			return;
	}
}

//Displays the options menu with settings like enabling / disabling colors and the option to go back or exit.
void MenuManager::printOptionsMenu() const{
	system("cls");
	std::cout << "\n\n   Tetris\n";
	std::cout << "   Options\n";
	std::cout << "~~~~~~~~~~~~~~\n\n";
	std::cout << "Choose key:\n";
	std::cout << "[" << Settings::MENU_ONE << "] Color: ";

	if (global_settings.game_colors) {
		std::cout << "Enabled\n";
	}
	else {
		std::cout << "Disabled\n";
	}

	std::cout << "[" << Settings::MENU_TWO << "] Bombs: ";

	if (global_settings.bombs) {
		std::cout << "Enabled\n";
	}
	else {
		std::cout << "Disabled\n";
	}


	std::cout << "[" << Settings::MENU_THREE << "] Bot Difficulties\n";
	std::cout << "[" << Settings::MENU_FOUR << "] Back\n";
	std::cout << "[" << Settings::MENU_EXIT << "] Exit Game\n";

}

//Controls the logicand inner loop for the additional options menu.
void MenuManager::optionsMenu() {
	unsigned char curr_key = 0;

	while (true)
	{	
		this->printOptionsMenu();
		this->printControls();

		curr_key = _getch();

		switch (curr_key) {
		case Settings::MENU_ONE:
				global_settings.game_colors = !(global_settings.game_colors);
				break;
		case Settings::MENU_TWO:
				global_settings.bombs = !(global_settings.bombs);
				break;
		case Settings::MENU_THREE:
				BotDifficultyMenu();
				break;
		case Settings::MENU_FOUR:
				return;
		case Settings::MENU_EXIT:
				current_state = GameState::EXIT_GAME;
				return;
		}

		// reset key - keep at bottom
		curr_key = 0;
	}
}


//Displays the game over menu with information about the winning playerand their score.
void MenuManager::printGameOverMenu(int player_indx, int score)
{
	system("cls");
	std::cout << "\n\n   Game Over!!!\n";
	std::cout << "   Player "<< player_indx <<" won!!!\n";
	std::cout << "   Score : "<< score << "\n";
	std::cout << "~~~~~~~~~~~~~~\n\n";
	this->game_started = false;
	Sleep(1000);
	std::cout << "Press any key to continue\n";
	(void)_getch(); // press any key
	system("cls");
}


// Prints bot difficulty menu options.
void MenuManager::printBotDifficultyMenu() const {
	system("cls");
	std::cout << "\n\n   Tetris\n";
	std::cout << "   Options->Bot Difficulty\n";
	std::cout << "~~~~~~~~~~~~~~\n";
	std::cout << "(Choose the CPU to cycle through its difficulties)\n";
	std::cout << "Choose key:\n";
	std::cout << "[" << Settings::MENU_ONE << "] CPU 1 Difficulty: ";

	if(global_settings.chosen_bot_difficulty[0] == 0)
		std::cout << "Novice\n";
	else if(global_settings.chosen_bot_difficulty[0] == 1)
		std::cout << "Good\n";
	else
		std::cout << "Best\n";


	std::cout << "[" << Settings::MENU_TWO << "] CPU 2 Difficulty: ";

	if (global_settings.chosen_bot_difficulty[1] == 0)
		std::cout << "Novice\n";
	else if (global_settings.chosen_bot_difficulty[1] == 1)
		std::cout << "Good\n";
	else
		std::cout << "Best\n";


	std::cout << "[" << Settings::MENU_THREE << "] Back\n";
	std::cout << "[" << Settings::MENU_EXIT << "] Exit Game\n";

}

// Controls bot difficulty menu logic.
void MenuManager::BotDifficultyMenu() {
	unsigned char curr_key = 0;

	while (true)
	{
		this->printBotDifficultyMenu();

		curr_key = _getch();

		switch (curr_key) {
		case Settings::MENU_ONE:
			global_settings.chosen_bot_difficulty[0] = (global_settings.chosen_bot_difficulty[0] + 1) % 3;
			break;
		case Settings::MENU_TWO:
			global_settings.chosen_bot_difficulty[1] = (global_settings.chosen_bot_difficulty[1] + 1) % 3;
			break;
		case Settings::MENU_THREE:
			return;
		case Settings::MENU_EXIT:
			current_state = GameState::EXIT_GAME;
			return;
		}

		// reset key - keep at bottom
		curr_key = 0;
	}
}
