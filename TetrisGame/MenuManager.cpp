#include "MenuManager.h"


void MenuManager::mainMenu(int& curr_token) {
	bool in_curr_menu = true;
	while (in_curr_menu)
	{
		system("cls");
		gotoxy(0, 0);
		std::cout << "Tetris\n";
		std::cout << "Main menu\n";
		gotoxy(5, 0);
		std::cout << "1.New Game\n";
		if (curr_token == 2) {
			std::cout << "2.Continue Game\n";
		}
		std::cout << "8.Options\n";
		std::cout << "9.Exit Game\n";
		mainMenuLogic(curr_token);

	}


}

bool MenuManager::mainMenuLogic(int& curr_token)
{
	int user_choise;
	std::cin >> user_choise;
	switch (user_choise) {
	//start a new game
	case 1:
		curr_token = user_choise;
		return false;
	//continue current game if there is one
	case 2:
		if (curr_token == user_choise) {
			return false;
		}
		return true;

	//call options menu
	case 8:
		//TODO: add options menu call
		return true;
	case 9:
		curr_token = user_choise;
		return false;
	default:
		return true;
	}
}


void MenuManager::optionsMenu() {}