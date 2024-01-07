#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


void TetrisGame::play() {

    TetrisBoard game_board = TetrisBoard(5, 5); // start board and set it to be x=10,y=10 relative to console
    Tetromino mino = Tetromino( 5 , 0 , game_board.board_start_x, game_board.board_start_y); // starting position relative to the board
    
    unsigned char iter_counter = 0;
    unsigned char drop_counter = 0;
    unsigned char curr_key = false;
    while (curr_key != 27) { // 27 is "ESC" key
        Sleep(50); // clock
        drop_counter++;

        //can be a part of a print manager
        game_board.printBoard();
        mino.print();

        if (_kbhit()) {
            curr_key = _getch();
            // take action depending on user key
            this->inputHandler(mino, game_board, curr_key);
        }


        movePiceDown(drop_counter, mino, game_board);
        //if (drop_counter > 20){
        //    mino.transform(0, 1, 0);
        //    drop_counter = 0;
        //}


        
    }
}

//function recives a ref to a tetromino object and the the disired move offset
//function calls the tetromino to recive its current position 
//function than calls rotate method to index of the object at the desired position and checks it with the board
//if the space is not empty and there is a cilision function will return false
bool TetrisGame::checkCollision(Tetromino& object, TetrisBoard&  board, int move_x, int move_y , int move_rot ) {
    int next_x, next_y, next_rot , shape_index;
    object.getTransform(next_x, next_y, next_rot);
    object.getShapeIndex(shape_index);
    next_x += move_x;
    next_y += move_y;
    next_rot = (next_rot + move_rot) % 4;
    int pi;
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pi = object.rotate(x_off , y_off, next_rot);
            if (tetromino_shapes[shape_index][pi] != ' ' && board.board[next_y + y_off][next_x + x_off] != ' ') {
                return false;
                
            }
        }
    }

    return true;
}

// given input character, will move object accordingly, or 
unsigned char TetrisGame::inputHandler(Tetromino& object, TetrisBoard& board, unsigned char curr_key)
{
    if (curr_key == 'a' || curr_key == 'A') {
        if (checkCollision(object , board, -1 , 0 , 0))
            object.transform(-1, 0, 0);
    }
    else if (curr_key == 'd' || curr_key == 'D'){
        if (checkCollision(object, board, 1, 0, 0))
            object.transform(1, 0, 0);
    }
    else if (curr_key == 'w' || curr_key == 'W') {
        if (checkCollision(object, board, 0, 0, 1))
            object.transform(0, 0, 1);
    }
    else if (curr_key == 's' || curr_key == 'S') {
        if (checkCollision(object, board, 0, 0, -1))
            object.transform(0, 0, -1);
    }
    else if (curr_key == 'x' || curr_key == 'X') {
        if (checkCollision(object, board, 0, 1, 0))
            object.transform(0, 1, 0);
    }

    return curr_key;
    
}


//!!not implemented yet!!
//a fucntion that fixes a tetromino to the board. 
//than destructs the tetromino object
void TetrisGame::fixTetrominoToBoard(Tetromino& object, TetrisBoard& board) {
    int obj_x_pos, obj_y_pos, obj_rot, obj_shape_index, pi, lines_destroyed = 0;
    object.getTransform(obj_x_pos, obj_y_pos, obj_rot);
    object.getShapeIndex(obj_shape_index);
    
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pi = object.rotate(x_off, y_off, obj_rot);
            if(tetromino_shapes[obj_shape_index][pi] != ' ')
                board.writeCellToBoard(obj_x_pos + x_off, obj_y_pos + y_off, tetromino_shapes[obj_shape_index][pi]);
        }
        //TODO: find some other place to put his check and make it better as a whole
        if ((obj_y_pos + y_off) < board.board_height-1)
            if (board.isALine(obj_y_pos + y_off)) {
                lines_destroyed++;
                board.destroyLine(obj_y_pos + y_off);
            }
    }
    if (lines_destroyed > 0) {
        board.shiftBoardDown(lines_destroyed);
    }
}


//function that moves the tetromino down evere X*'drop_counter'*50ms
//can be used to change game speed
void TetrisGame::movePiceDown(unsigned char& drop_counter , Tetromino& object, TetrisBoard& board) {
    if (drop_counter > 20) {

        if(checkCollision(object, board, 0, 1, 0))
        object.transform(0, 1, 0);
        else {
            fixTetrominoToBoard( object, board);
            object.resetTetromino();
        }
        drop_counter = 0;
    }
}


int main()
{
    srand(time(NULL));
    TetrisGame game = TetrisGame();
    game.play();
    
    
}
