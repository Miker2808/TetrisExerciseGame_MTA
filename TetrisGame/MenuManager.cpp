#include "MenuManager.h"

// inner loop for the main menu options
// will receive a state as a prameter from the main loop
// and will return a state back to the main loop.
GameState MenuManager::mainMenu(GameState state) {
	unsigned char curr_key = 0;
	GameState current_state = state;

	while (current_state != GameState::NEW_GAME && current_state != GameState::EXIT_GAME && current_state != GameState::RESUME_GAME)
	{
		this->printMainMenu();
		Sleep(50);

		if (_kbhit()) {
			curr_key = _getch();
		}

		current_state = mainMenuLogic(curr_key);

		// keep at bottom
		curr_key = 0;
	}

	return current_state;
}

// prints the contents of the main menu
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

// prints controls extracted from pointers of player_1 and player_2
void MenuManager::printControls()
{
	int x = 25;
	int y = 1;
	gotoxy(x, y++);
	std::cout << "Player 1 controls:";
	gotoxy(x, y++);
	std::cout << "Left: " << ControlsPresetOne::MOVE_LEFT_KEY_1 << " or " << ControlsPresetOne::MOVE_LEFT_KEY_2;
	std::cout << " || Right: " << ControlsPresetOne::MOVE_RIGHT_KEY_1 << " or " << ControlsPresetOne::MOVE_RIGHT_KEY_2;
	gotoxy(x, y++);
	std::cout << "Rotate Clockwise: " << ControlsPresetOne::ROT_RIGHT_KEY_1 << " or " << ControlsPresetOne::ROT_RIGHT_KEY_2;
	std::cout << " || Rotate Counterclock: " << ControlsPresetOne::ROT_LEFT_KEY_1 << " or " << ControlsPresetOne::ROT_LEFT_KEY_1;
	gotoxy(x, y++);
	std::cout << "Drop: " << ControlsPresetOne::DROP_KEY_1 << " or " << ControlsPresetOne::DROP_KEY_2;
	y += 2;
	gotoxy(x, y++);
	std::cout << "Player 2 controls:";
	gotoxy(x, y++);
	
	std::cout << "Left: " << ControlsPresetTwo::MOVE_LEFT_KEY_1 << " or " << ControlsPresetTwo::MOVE_LEFT_KEY_2;
	std::cout << " || Right: " << ControlsPresetTwo::MOVE_RIGHT_KEY_1 << " or " << ControlsPresetTwo::MOVE_RIGHT_KEY_2;
	gotoxy(x, y++);
	std::cout << "Rotate Clockwise: " << ControlsPresetTwo::ROT_RIGHT_KEY_1 << " or " << ControlsPresetTwo::ROT_RIGHT_KEY_2;
	std::cout << " || Rotate Counterclock: " << ControlsPresetTwo::ROT_LEFT_KEY_1 << " or " << ControlsPresetTwo::ROT_LEFT_KEY_1;
	gotoxy(x, y++);
	std::cout << "Drop: " << ControlsPresetTwo::DROP_KEY_1 << " or " << ControlsPresetTwo::DROP_KEY_2;
}


// updates game state based on user input from the menu
GameState MenuManager::mainMenuLogic(unsigned char curr_key)
{
	switch (curr_key) {
		case '1':
			this->game_started = true;
			return GameState::NEW_GAME;
			break;
		case '2':
			if (this->game_started) {
				return GameState::RESUME_GAME;
			}
			break;
		case '8':
			return this->optionsMenu();
		case '9':
			return GameState::EXIT_GAME;

	}
}

// prints the menu for the additional options
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

// controls the logic and inner loop for the additional options
GameState MenuManager::optionsMenu() {
	unsigned char curr_key = 0;

	while (true)
	{	
		this->printOptionsMenu();
		this->printControls();
		Sleep(50);

		if (_kbhit()) {
			curr_key = _getch();
		}

		switch (curr_key) {
			case '1':
				global_settings.game_colors ? global_settings.game_colors = false : global_settings.game_colors = true;
				break;
			case '2':
				return GameState::PAUSED_GAME;
			case '9':
				return GameState::EXIT_GAME;
		}

		// reset key - keep at bottom
		curr_key = 0;
	}
}