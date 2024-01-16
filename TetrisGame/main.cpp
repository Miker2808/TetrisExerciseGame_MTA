#include "TetrisGame.h"

Settings global_settings;

void playGame(TetrisGame* players[], GameState& game_state, MenuManager* menu);
void initNewGame(TetrisGame* players[]);

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

void playGame(TetrisGame* players_arr[], GameState& game_state, MenuManager* menu)
{
    while (game_state == GameState::IN_PROGRESS_GAME)
    {
        unsigned char curr_key = 0;
        // get key from input -- keep at top of loop
        if (_kbhit()) {
            curr_key = _getch();
        }
        Sleep(TetrisGame::TICKS_TIME); //game clock

        // take action based on user key CHANGE TO GENERALIZE
        players_arr[0]->play(curr_key);
        Sleep(10); // fixes stuttering of second game screen
        players_arr[1]->play(curr_key);

        // 27 is "ESC" key
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
        }

        if (players_arr[0]->game_over || players_arr[1]->game_over) {
            if (players_arr[0]->game_over)
                menu->printGameOverMenu(players_arr[1]->player->id , players_arr[1]->player->score);
            else
                menu->printGameOverMenu(players_arr[0]->player->id, players_arr[0]->player->score);
            game_state = GameState::NO_GAME_STATE;
            
        }
            // keep at bottom
            curr_key = 0;
    }
}

void initNewGame(TetrisGame* players[]) {
    if (players[0] != nullptr) {
        delete players[0];
    }
    if (players[1] != nullptr) {
        delete players[1];
    }

    players[0] = new TetrisGame(Settings::SCREEN_OFFSET_X, Settings::SCREEN_OFFSET_Y);
    players[1] = new TetrisGame(Settings::SCREEN_OFFSET_X + Settings::SCREEN_OFFSET_INTERVAL, Settings::SCREEN_OFFSET_Y);

}