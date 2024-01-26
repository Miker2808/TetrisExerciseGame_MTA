#include "MultiplayerTetris.h"
#include "HeuristicsExplorer.h"

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
    if (games_arr != nullptr) {
        freeGames();
        delete games_arr;
    }
    curr_num_of_games = global_settings.num_of_human_players + global_settings.num_of_bots;

    games_arr = new TetrisGame * [curr_num_of_games];

    // Create new TetrisGame instances for both players
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
        Sleep(TetrisGame::TICKS_TIME); //game clock

        
        // take action based on user key
        for (unsigned int i = 0; i < curr_num_of_games; i++) {
            if (!games_arr[i]->game_over) {
                games_arr[i]->play(curr_key);
                games_in_play++;
            }
        }
        
        std::vector<int> heights = HeuristicsExplorer().boardHeights(games_arr[0]->board);
        std::vector<int> holes = HeuristicsExplorer().boardHoles(games_arr[0]->board);
        gotoxy(35, 23);
        std::cout << "width: " << games_arr[0]->currentMino->getShapeWidth();
        
        gotoxy(1, 23);
        std::cout << "heights:";
        for (int i = 0; i < heights.size(); i++) {
            std::cout << heights[i] << " ";
        }

        
        gotoxy(3, 24);
        std::cout << "holes:";
        for (int i = 0; i < holes.size(); i++) {
            std::cout << holes[i] << " ";
        }

        

        // Check if the "ESC" key is pressed to pause the game
        if (curr_key == 27) {
            game_state = GameState::PAUSED_GAME;
            //reset the game start flag, so once play is resumed the board will be re printed
            for (unsigned int i = 0; i < curr_num_of_games; i++) {
                if (!games_arr[i]->game_over)
                    games_arr[i]->start = true;
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
    TetrisGame* winning_game = nullptr;
    //if one player survived
    if (games_in_play == 1) {
        for (unsigned int i = 0; i < curr_num_of_games; i++) {
            if (!games_arr[i]->game_over)
                winning_game = games_arr[i];
        }
    }
    //if no one survived
    else {
        winning_game = games_arr[0];
        for (unsigned int i = 0; i < curr_num_of_games; i++) {
            //check ticks survived
            if (games_arr[i]->ticks_survived > winning_game->ticks_survived)
                winning_game = games_arr[i];
            else {
                //if ticks survived are equal check score
                if(games_arr[i]->ticks_survived == winning_game->ticks_survived)
                    if(games_arr[i]->player->score > winning_game->player->score)
                        winning_game = games_arr[i];
            }
        }
    }
    game_state = GameState::NO_GAME_STATE;
    menu.printGameOverMenu(winning_game->player->id, winning_game->player->score);
}


void MultiplayerTetris::freeGames() {
    for (unsigned int i = 0; i < curr_num_of_games; i++)
        delete games_arr[i];
}


void MultiplayerTetris::allocateGames() {
    unsigned int i , board_offset_x = 0 , board_offset_y = 0;

    //allocate human player games first
    for (i = 0; i < global_settings.num_of_human_players; i++) {
        updateBoardOffsetPos(i , board_offset_x, board_offset_y);
        games_arr[i] = new TetrisGame(board_offset_x , board_offset_y, global_settings.bombs, true);
    }

    //allocate the rest of the games as CPU games
    for (i; i < curr_num_of_games; i++) {
        updateBoardOffsetPos(i, board_offset_x, board_offset_y);
        games_arr[i] = new TetrisGame(board_offset_x, board_offset_y, global_settings.bombs, false);
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