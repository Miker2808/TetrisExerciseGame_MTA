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
    if (not games_arr.empty()) {
        freeGames();
        games_arr.clear();
    }
    if (not ai_games_arr.empty()){
        freeAIGames();
        ai_games_arr.clear();
    }

    TetrisGame::game_counter = 0;
    allocateGames();

}


// Main gameplay loop that handles player input and game state.
void MultiplayerTetris::gameplayLoop() {

    while (game_state == GameState::IN_PROGRESS_GAME)
    {
        unsigned char curr_key = 0;
        unsigned int games_in_play = 0;
        
        // Get key input from the user
        if (_kbhit()) {
            curr_key = _getch();
        }

        Sleep(Settings::TICKS_TIME); //game clock
        
        // take action based on user key
        for (size_t i = 0; i < games_arr.size(); i++) {
            if (!games_arr[i]->isGameOver()) {
                games_arr[i]->play(curr_key);
                games_in_play++;
            }
        }

        for (size_t i = 0; i < ai_games_arr.size(); i++) {
            if (!ai_games_arr[i]->isGameOver()) {
                ai_games_arr[i]->play();
                games_in_play++;
            }
        }

        // Check if the "ESC" key is pressed to pause the game
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            //reset the game start flag, so once play is resumed the board will be re printed
            for (size_t i = 0; i < games_arr.size(); i++) {
                if (!games_arr[i]->isGameOver())
                    games_arr[i]->setGameStart(true);
            }
            for (size_t i = 0; i < ai_games_arr.size(); i++) {
                if (!ai_games_arr[i]->isGameOver())
                    ai_games_arr[i]->setGameStart(true);
            }
        }

        // Check for game over condition
        if (games_in_play <= 1) {
            gameOverLogic(games_in_play);
        }

        // Reset current key to zero at the end of the loop
        curr_key = 0;
    }
}

// Handles game-over logic and displays the game over menu.
void MultiplayerTetris::gameOverLogic(unsigned int games_in_play) {
    TetrisGame* winning_game = nullptr; // works due to polymorphism of AITetrisGame
    //if one player survived
    if (games_in_play == 1) {
        for (size_t i = 0; i < games_arr.size(); i++) {
            if (!games_arr[i]->isGameOver()) {
                winning_game = games_arr[i];
            }
        }

        for (size_t i = 0; i < ai_games_arr.size(); i++) {
            if (!ai_games_arr[i]->isGameOver()) {
                winning_game = ai_games_arr[i];
            }
        }
    }

    game_state = GameState::NO_GAME_STATE;
    if (winning_game != nullptr) {
        menu.printGameOverMenu(winning_game->player->id, winning_game->player->score);
    }
}


void MultiplayerTetris::freeGames() {
    for (size_t i = 0; i < games_arr.size(); i++)
        delete games_arr[i];
}

void MultiplayerTetris::freeAIGames() {
    for (size_t i = 0; i < ai_games_arr.size(); i++) {
        delete ai_games_arr[i];
    }
}

// allocates memory for all the AITetrisGames and TetrisGames objects
void MultiplayerTetris::allocateGames() {
    unsigned int  board_offset_x = 0 , board_offset_y = 0;
    unsigned int i;

    //allocate human player games first
    for (i = 0; i < global_settings.num_of_human_players; i++) {
        updateBoardOffsetPos(i , board_offset_x, board_offset_y);
        games_arr.push_back( new TetrisGame(board_offset_x , board_offset_y, global_settings.bombs, true));
    }
    
    //allocate the rest of the games as CPU games
    for (unsigned int j = 0; j < global_settings.num_of_bots; j++) {
        updateBoardOffsetPos(j + i, board_offset_x, board_offset_y);
        ai_games_arr.push_back(new AITetrisGame(board_offset_x, board_offset_y, global_settings.bombs, false));
    }
}

//Update the offset based on the number of games created and number of games per row
void MultiplayerTetris::updateBoardOffsetPos(unsigned int gameindex, unsigned int& x_pos, unsigned int& y_pos) {
    unsigned int mult_x, mult_y;
    mult_x = gameindex % Settings::SCREEN_GAMES_PER_ROW;
    mult_y = (unsigned int)(gameindex / Settings::SCREEN_GAMES_PER_ROW);
    x_pos = Settings::SCREEN_OFFSET_X + (Settings::SCREEN_OFFSET_INTERVAL_X * mult_x);
    y_pos = Settings::SCREEN_OFFSET_Y + (Settings::SCREEN_OFFSET_INTERVAL_Y * mult_y);
}