#include "GameFunctions.h"




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
        players_arr[1]->play(curr_key);

        // 27 is "ESC" key
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            players_arr[0]->start = true;
            players_arr[1]->start = true;
        }

        if (players_arr[0]->game_over || players_arr[1]->game_over) {
            if (players_arr[0]->game_over)
                menu->printGameOverMenu(players_arr[1]->player->id, players_arr[1]->player->score);
            else
                menu->printGameOverMenu(players_arr[0]->player->id, players_arr[0]->player->score);
            game_state = GameState::NO_GAME_STATE;

        }
        // keep at bottom
        curr_key = 0;
    }
}

// dynamically initializes tetris games, pointers are returned by writing to the input array
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