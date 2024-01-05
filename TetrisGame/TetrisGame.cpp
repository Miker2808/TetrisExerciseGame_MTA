#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


void TetrisGame::play() {

    TetrisBoard game_board;
    Tetromino mino;
    unsigned char curr_key = 0;
    unsigned char iter_counter = 0;

    while (curr_key != 27) { // 27 is "ESC" key
        Sleep(50); // clock
        iter_counter++;

        if (iter_counter > 20){
            mino.transform(7, 7);
            iter_counter++;
        }
            game_board.printBoard(5, 5);
            mino.print();

            iter_counter = 0;
        }
        

    }
}


int main()
{
    
    TetrisGame game = TetrisGame();
    game.play();
    
    
}
