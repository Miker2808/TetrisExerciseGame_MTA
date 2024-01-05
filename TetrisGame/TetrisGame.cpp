#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


void TetrisGame::play() {

    TetrisBoard game_board = TetrisBoard(2, 2); // start board and set it to be x=10,y=10 relative to console
    Tetromino mino = Tetromino(8, 2);
    unsigned char curr_key = 0;
    unsigned char iter_counter = 0;
    unsigned char drop_counter = 0;
    while (curr_key != 27) { // 27 is "ESC" key
        Sleep(50); // clock
        drop_counter++;

        if (_kbhit()) {
            curr_key = _getch();

            if (curr_key == 'a' || curr_key == 'A') 
                mino.transform(-1, 0, 0);
            else if (curr_key == 'd' || curr_key == 'D')
                mino.transform(1, 0, 0);
            else if (curr_key == 'w' || curr_key == 'W') {
                mino.transform(0, 0, 1);
            }
            else if (curr_key == 's' || curr_key == 'S') {
                mino.transform(0, 0, -1);
            }
            else if (curr_key == 'x' || curr_key == 'X') {
                mino.transform(0, 1, 0);
            }
        }

        if (drop_counter > 20){
            mino.transform(0, 1, 0);
            drop_counter = 0;
        }

        game_board.printBoard();
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
    srand(time(NULL));
    TetrisGame game = TetrisGame();
    game.play();
    
    
}
