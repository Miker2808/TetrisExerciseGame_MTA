#include "MenuManager.h"


void MenuManager::mainMenu(int& curr_token) {
	while (curr_token == 2 ) 
	{
		system("cls");
		gotoxy(0, 0);
		std::cout << "Tetris\n";
		std::cout << "Main menu\n";
		gotoxy(5, 0);
		std::cout << "1.New Game\n";
		if (curr_token = 2) {
			std::cout << "2.Continue Game\n";
		}
		std::cout << "8.Options\n";
		std::cout << "9.Exit Game\n";
		std::cin >> curr_token;
	}


}

void MenuManager::mainMenuLogic(int& curr_token)
{
	switch (curr_token)
		case 8:


}