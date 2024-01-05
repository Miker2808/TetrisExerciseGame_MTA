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
    
    TetrisGame game = TetrisGame();
    game.play();
    
    
}
