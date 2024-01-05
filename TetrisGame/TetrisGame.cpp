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

bool TetrisGame::checkCollision(Tetromino object, TetrisBoard  board, int posX, int posY) {
    int pi;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pi = object.rotate(posX + i, posY + j, object.rotation);
            if (tetromino_shapes[object.shape_index][pi] != ' ' && board.board[i][j] != ' ') {
                std::cout << "collisionsfnajfbhafbhabfhasbfhassbfjabfjasbfija" << std::endl;
                return false;
                
            }
                

        }
    }

    return true;
}


int main()
{


    
    
}
