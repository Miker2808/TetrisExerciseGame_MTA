#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"

int main()
{
    srand((unsigned)time(NULL));
    int test_i = 0;
    int test_j = 0;
    system("cls");
    TetrisBoard board(12, 18);
    std::cout << "test success" << std::endl;
    Tetromino item = Tetromino();
    
    while (true) {
        Sleep(500);
        item.transform(10, 7 + (test_i++));
        board.printBoard(5, 5);
        item.print();
        
    }
    
    
}
