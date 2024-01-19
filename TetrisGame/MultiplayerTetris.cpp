#include "MultiplayerTetris.h"


// Launches the multiplayer Tetris game.
void MultiplayerTetris::launcher() {
    showConsoleCursor(false);
    srand((unsigned int)time(NULL));

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
}

// Sets up a new game for both players.
void MultiplayerTetris::setUpNewGame() {
    // Delete existing TetrisGame instances, if any
    if (players[0] != nullptr) {
        delete players[0];
    }
    if (players[1] != nullptr) {
        delete players[1];
    }

    // Create new TetrisGame instances for both players
    players[0] = new TetrisGame(Settings::SCREEN_OFFSET_X, Settings::SCREEN_OFFSET_Y, global_settings.bombs);
    players[1] = new TetrisGame(Settings::SCREEN_OFFSET_X + Settings::SCREEN_OFFSET_INTERVAL, Settings::SCREEN_OFFSET_Y, global_settings.bombs);

}


// Main gameplay loop that handles player input and game state.
void MultiplayerTetris::gameplayLoop() {
    while (game_state == GameState::IN_PROGRESS_GAME)
    {
        unsigned char curr_key = 0;
        
        // Get key input from the user
        if (_kbhit()) {
            curr_key = _getch();
        }
        Sleep(TetrisGame::TICKS_TIME); //game clock

        // take action based on user key
        players[0]->play(curr_key);
        players[1]->play(curr_key);

        // Check if the "ESC" key is pressed to pause the game
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            //reset the game start flag, so once play is resumed the board will be re printed
            players[0]->start = true;
            players[1]->start = true;
        }

        // Check for game over condition
        if (players[0]->game_over || players[1]->game_over) {
            gameOverLogic();
        }

        // Reset current key to zero at the end of the loop
        curr_key = 0;
    }
}

// Handles game-over logic and displays the game over menu.
void MultiplayerTetris::gameOverLogic() {
    if (players[0]->game_over && players[1]->game_over){
        // Determine the winner based on scores and display the game-over menu
        if (players[1]->player->score > players[0]->player->score)
            menu.printGameOverMenu(players[1]->player->id, players[1]->player->score);
        else
            menu.printGameOverMenu(players[0]->player->id, players[0]->player->score);
        game_state = GameState::NO_GAME_STATE;

    }
    else {
        // Display the game-over menu based on the player who lost
        if (players[0]->game_over)
            menu.printGameOverMenu(players[1]->player->id, players[1]->player->score);
        else
            menu.printGameOverMenu(players[0]->player->id, players[0]->player->score);
        game_state = GameState::NO_GAME_STATE;
    }

}