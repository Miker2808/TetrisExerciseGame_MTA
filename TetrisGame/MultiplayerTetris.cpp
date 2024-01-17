#include "MultiplayerTetris.h"



void MultiplayerTetris::launcher() {
    showConsoleCursor(false);
    srand(time(NULL));

    unsigned char curr_key = 0;
    while (game_state != GameState::EXIT_GAME) {
        game_state = menu.mainMenu(game_state);

        if (game_state == GameState::NEW_GAME)
        {
            setUpNewGame();
            game_state = GameState::IN_PROGRESS_GAME;
        }

        gameplayLoop();

    }
    delete players[0];
    delete players[1];
}


void MultiplayerTetris::setUpNewGame() {

    if (players[0] != nullptr) {
        delete players[0];
    }
    if (players[1] != nullptr) {
        delete players[1];
    }

    players[0] = new TetrisGame(Settings::SCREEN_OFFSET_X, Settings::SCREEN_OFFSET_Y);
    players[1] = new TetrisGame(Settings::SCREEN_OFFSET_X + Settings::SCREEN_OFFSET_INTERVAL, Settings::SCREEN_OFFSET_Y);

}


void MultiplayerTetris::gameplayLoop() {
    while (game_state == GameState::IN_PROGRESS_GAME)
    {
        unsigned char curr_key = 0;
        // get key from input -- keep at top of loop
        if (_kbhit()) {
            curr_key = _getch();
        }
        Sleep(TetrisGame::TICKS_TIME); //game clock

        // take action based on user key CHANGE TO GENERALIZE
        players[0]->play(curr_key);
        players[1]->play(curr_key);

        // 27 is "ESC" key
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            players[0]->start = true;
            players[1]->start = true;
        }

        if (players[0]->game_over || players[1]->game_over) {
            gameOverLogic();
        }
        // keep at bottom
        curr_key = 0;
    }
}

void MultiplayerTetris::gameOverLogic() {
    if (players[0]->game_over && players[1]->game_over){
        if (players[1]->player->score > players[0]->player->score)
            menu.printGameOverMenu(players[1]->player->id, players[1]->player->score);
        else
            menu.printGameOverMenu(players[0]->player->id, players[0]->player->score);
        game_state = GameState::NO_GAME_STATE;

    }
    else {
        if (players[0]->game_over)
            menu.printGameOverMenu(players[1]->player->id, players[1]->player->score);
        else
            menu.printGameOverMenu(players[0]->player->id, players[0]->player->score);
        game_state = GameState::NO_GAME_STATE;
    }

}