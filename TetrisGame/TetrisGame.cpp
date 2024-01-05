#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


void TetrisGame::play() {

    TetrisBoard game_board;
    Tetromino mino;
    int test = 1;
    while (true) {
        Sleep(500);
        mino.transform(10, 7 + (test++));
        game_board.printBoard(5, 5);
        mino.print();

    }
}


int main()
{
    
    
    
    
}
