#include "Utility.h"
#include "TetrisGame.h"



int main()
{
    srand(time(NULL));
    TetrisGame game_p1 = TetrisGame(1, 8);
    TetrisGame game_p2 = TetrisGame(25, 8);
    TetrisGame game_p3 = TetrisGame(50, 8);

    unsigned char curr_key = 0;

    while (curr_key != 27) { // 27 is "ESC" key
        Sleep(TetrisGame::TICKS_TIME); // clock

        if (_kbhit()) {
            curr_key = _getch();
        }

        // take action depending on user key
        game_p1.play(curr_key);
        //game_p2.play(curr_key);
        //game_p3.play(curr_key);

        curr_key = 0;

    }

}