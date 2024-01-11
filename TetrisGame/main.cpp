#include "Utility.h"
#include "TetrisGame.h"



int main()
{
    GameState game_token = none;
    MenuManager menu;
    srand(time(NULL));
    TetrisGame game_p1 = TetrisGame(10, 8);
    TetrisGame game_p2 = TetrisGame(30, 8);
    TetrisGame game_p3 = TetrisGame(50, 8);

    unsigned char curr_key = 0;
    while (game_token != game_exit) {
        game_token = menu.mainMenu(game_token);

        if (game_token == init_new_game) {

            game_token = resume_game;
        }

        while (game_token == resume_game) {
            Sleep(TetrisGame::TICKS_TIME); // clock

            if (_kbhit()) {
                curr_key = _getch();
            }

            // take action depending on user key
            game_p1.play(curr_key);
            game_p2.play(curr_key);
            game_p3.play(curr_key);

            // 27 is "ESC" key
            if (curr_key == 27)
                game_token = game_paused;
            curr_key = 0;
        }
    }



}