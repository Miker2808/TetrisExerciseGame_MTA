#include "TetrisGame.h"
#include "GameFunctions.h"

Settings global_settings;


int main()
{
    srand(time(NULL));
    GameState game_state = GameState::NO_GAME_STATE;
    MenuManager menu;
    TetrisGame* players[Settings::NUMBER_OF_PLAYERS] = {nullptr, nullptr};

    unsigned char curr_key = 0;
    while (game_state != GameState::EXIT_GAME) {
        game_state = menu.mainMenu(game_state);

        if (game_state == GameState::NEW_GAME) 
        {
            initNewGame(players);
            game_state = GameState::IN_PROGRESS_GAME;
        }

        playGame(players, game_state, &menu);

    }
    delete players[0];
    delete players[1];
}
