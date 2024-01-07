#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "Tetromino.h"


TetrisGame::TetrisGame(int start_x, int start_y)
{
    this->board = new TetrisBoard(start_x, start_y); // start board and set it to be x=10,y=10 relative to console
    this->currentMino = new Tetromino(4, 0, start_x, start_y); // relative to the board
    this->player = new Player();

}

TetrisGame::~TetrisGame() {
    delete this->board;
    delete this->currentMino;
    delete this->player;
}

void TetrisGame::play(unsigned char curr_key) {

    this->tick_counter += 1;

    this->movementHandler(curr_key);

    if (this->tick_counter > this->ticks_per_drop){
        this->currentMino->transform(0, 1, 0);
        this->tick_counter = 0;
    }

    this->board->printBoard();
    this->currentMino->print();
        
    
}

//function recives a ref to a tetromino object and the the disired move offset
//function calls the tetromino to recive its current position 
//function than calls rotate method to index of the object at the desired position and checks it with the board
//if the space is not empty and there is a cilision function will return false
bool TetrisGame::checkCollision(int move_x, int move_y , int move_rot ) {
    int next_x, next_y, next_rot , shape_index;
    this->currentMino->getTransform(next_x, next_y, next_rot);
    this->currentMino->getShapeIndex(shape_index);
    next_x += move_x;
    next_y += move_y;
    next_rot = (next_rot + move_rot) % 4;
    int pi;
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pi = this->currentMino->rotate(x_off , y_off, next_rot);
            if (tetromino_shapes[shape_index][pi] != ' ' && this->board->board[next_y + y_off][next_x + x_off] != ' ') {
                return false;   
            }
        }
    }

    return true;
}

// given input character, will move object accordingly or deny movement
void TetrisGame::movementHandler( unsigned char curr_key)
{
    if (curr_key == this->player->MOVE_LEFT_KEY_1 || curr_key == this->player->MOVE_LEFT_KEY_2) {
        // TODO: check if possible
        if (checkCollision(-1 , 0 , 0))
            this->currentMino->transform(-1, 0, 0);
    }
    else if (curr_key == this->player->MOVE_RIGHT_KEY_1 || curr_key == this->player->MOVE_RIGHT_KEY_2){
        if (checkCollision(1, 0, 0))
            this->currentMino->transform(1, 0, 0);
    }
    else if (curr_key == this->player->ROT_RIGHT_KEY_1 || curr_key == this->player->ROT_RIGHT_KEY_2) {
        if (checkCollision(0, 0, 1))
            this->currentMino->transform(0, 0, 1);
    }
    else if (curr_key == this->player->ROT_LEFT_KEY_1 || curr_key == this->player->ROT_LEFT_KEY_2) {
        if (checkCollision( 0, 0, -1))
            this->currentMino->transform(0, 0, -1);
    }
    else if (curr_key == this->player->DROP_KEY_1 || curr_key == this->player->DROP_KEY_2) {
        if (checkCollision(0, 1, 0))
            this->currentMino->transform(0, 1, 0);
    }
}


int main()
{
    srand(time(NULL));
    TetrisGame game_p1 = TetrisGame();
    TetrisGame game_p2 = TetrisGame();
    
    unsigned char curr_key = 0;
    
    while (curr_key != 27) { // 27 is "ESC" key
        Sleep(TetrisGame::TICKS_TIME); // clock

        if (_kbhit()) {
            curr_key = _getch();
            // take action depending on user key
            game_p1.play(curr_key);
            game_p2.play(curr_key);
        }


    }
    
}
