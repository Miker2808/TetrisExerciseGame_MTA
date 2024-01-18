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
void MenuManager::printMainMenu() {
	system("cls");
	std::cout << "\n\n   Tetris\n";
	std::cout << "  Main menu\n";
	std::cout << "~~~~~~~~~~~~~~\n\n";
	std::cout << "Choose key:\n";
	std::cout << "[1] New Game\n";
	if (this->game_started) {
		std::cout << "[2] Continue Game\n";
	}
	std::cout << "[8] Options\n";
	std::cout << "[9] Exit Game\n";
}

// Prints controls extracted from pointers of player_1 and player_2.
void MenuManager::printControls()
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
		case '1':
			this->game_started = true;
			current_state = GameState::NEW_GAME;
			return ;
			break;
		case '2':
			if (this->game_started) {
				current_state = GameState::IN_PROGRESS_GAME;
				return ;
			}
			break;
		case '8':
			this->optionsMenu();
			return;
		case '9':
			current_state = GameState::EXIT_GAME;
			return ;
		default:
			return;

	}
}

//Displays the options menu with settings like enabling / disabling colors and the option to go back or exit.
void MenuManager::printOptionsMenu() {
	system("cls");
	std::cout << "\n\n   Tetris\n";
	std::cout << "   Options\n";
	std::cout << "~~~~~~~~~~~~~~\n\n";
	std::cout << "Choose key:\n";
	std::cout << "[1] Color: ";

	if (global_settings.game_colors) {
		std::cout << "Enabled\n";
	}
	else {
		std::cout << "Disabled\n";
	}

	std::cout << "[2] Back\n";
	std::cout << "[9] Exit Game\n";

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
			case '1':
				global_settings.game_colors ? global_settings.game_colors = false : global_settings.game_colors = true;
				break;
			case '2':
				return;
			case '9':
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