#include "TetrisGame.h"

Settings global_settings;

void initNewGame(TetrisGame ** game_p1, TetrisGame ** game_p2) {
    if (game_p1 != nullptr) {
        delete game_p1;
    }
    if (game_p2 != nullptr) {
        delete game_p2;
    }

    *game_p1 = new TetrisGame(10, 5);
    *game_p2 = new TetrisGame(30, 5);

    (*game_p2)->player->setSecondaryControls();
}

int main()
{
    srand(time(NULL));

    GameState game_state = GameState::NO_GAME_STATE;
    MenuManager menu;

    TetrisGame* game_p1 = new TetrisGame(10, 5);;
    TetrisGame* game_p2 = new TetrisGame(30, 5);

    game_state = menu.mainMenu(game_state);


    unsigned char curr_key = 0;
    while (game_state != GameState::EXIT_GAME) {
        // get key from input -- keep at top of loop
        if (_kbhit()) {
            curr_key = _getch();
        }

        //if (game_state == GameState::NEW_GAME) {
        //    game_p1 = TetrisGame(10, 5);
        //    game_p2 = TetrisGame(30, 5);
        //}

        Sleep(TetrisGame::TICKS_TIME); //game clock

        // take action based on user key
        game_p2->play(curr_key);
        Sleep(1); // fixes stuttering of second game screen
        game_p1->play(curr_key);
            

        // 27 is "ESC" key
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            game_state = menu.mainMenu(game_state);
        }

        // keep at bottom
        curr_key = 0;

    }
    std::cout << "\nColors:" << global_settings.game_colors;
    delete game_p1;
    delete game_p2;

}