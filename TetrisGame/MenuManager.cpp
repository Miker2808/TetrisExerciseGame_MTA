#include "MenuManager.h"


GameState MenuManager::mainMenu(GameState curr_state) {
	bool in_curr_menu = true;
	while (in_curr_menu)
	{
		system("cls");
		gotoxy(0, 0);
		std::cout << "Tetris\n";
		std::cout << "Main menu\n";
		gotoxy(0, 5);
		std::cout << "1.New Game\n";
		if (curr_state == game_paused) {
			std::cout << "2.Continue Game\n";
		}
		std::cout << "8.Options\n";
		std::cout << "9.Exit Game\n";
		curr_state = mainMenuLogic(curr_state);
		system("cls");
		if (curr_state != game_paused || curr_state != none)
			in_curr_menu = false;
	}
	return curr_state;
}

GameState MenuManager::mainMenuLogic(GameState curr_token)
{
	unsigned char user_choise;
	user_choise = _getch();
	switch (user_choise) {
	//start a new game
	case '1':
		return init_new_game;
	//continue current game if there is one
	case '2':
		if (curr_token == game_paused) {
			return resume_game;
		}
		return curr_token;

	//call options menu
	case '8':
		//TODO: add options menu call
		return curr_token;
	case '9':
		return game_exit;
	default:
		return curr_token;
	}
}


void MenuManager::optionsMenu() {}