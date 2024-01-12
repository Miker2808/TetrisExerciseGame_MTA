#include "TetrisGame.h"


// constructor for the game object, basically sets up a start point for the game
TetrisGame::TetrisGame(int start_x, int start_y)
{
    this->board = new TetrisBoard(start_x, start_y); // start board and set it to be x=10,y=10 relative to console
    this->currentMino = new Tetromino(5, 0, start_x, start_y); // relative to the board
    this->player = new Player();

}

// destructor for the game, free's dynamically allocated memory for the object
TetrisGame::~TetrisGame() {
    delete this->board;
    delete this->currentMino;
    delete this->player;
    gotoxy(1, 25);
    std::cout << "Destroyed tetris game object" << std::endl;
}

// runs a single cycle of playing the game
void TetrisGame::play(unsigned char curr_key) {

    this->tick_counter += 1;

    this->movementHandler(curr_key);

    movePiceDown();

    if (!checkCollision(0, 0, 0))
        this->game_over = true;

    this->board->printBoard();
    this->currentMino->print();
    this->printGameStats();
        
    
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
    next_rot = pyMod((next_rot + move_rot), 4); // map rotation by using modulu
    int pi;
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pi = this->currentMino->rotate(x_off , y_off, next_rot);
            if (tetromino_shapes[shape_index][pi] != ' ' && this->board->board[next_y + y_off][next_x + x_off] != '.') {
                return false;   
            }
        }
    }

    return true;
}

// given input character, will move the tetromino piece accordingly or do nothing
void TetrisGame::movementHandler( unsigned char curr_key)
{
    if (curr_key == this->player->my_ctrl.MOVE_LEFT_KEY_1 || curr_key == this->player->my_ctrl.MOVE_LEFT_KEY_2) {
        if (checkCollision(-1 , 0 , 0))
            this->currentMino->transform(-1, 0, 0);
    }
    else if (curr_key == this->player->my_ctrl.MOVE_RIGHT_KEY_1 || curr_key == this->player->my_ctrl.MOVE_RIGHT_KEY_2){
        if (checkCollision(1, 0, 0))
            this->currentMino->transform(1, 0, 0);
    }
    else if (curr_key == this->player->my_ctrl.ROT_RIGHT_KEY_1 || curr_key == this->player->my_ctrl.ROT_RIGHT_KEY_2) {
        if (checkCollision(0, 0, 1))
            this->currentMino->transform(0, 0, 1);
    }
    else if (curr_key == this->player->my_ctrl.ROT_LEFT_KEY_1 || curr_key == this->player->my_ctrl.ROT_LEFT_KEY_2) {
        if (checkCollision( 0, 0, -1))
            this->currentMino->transform(0, 0, -1);
    }
    else if (curr_key == this->player->my_ctrl.DROP_KEY_1 || curr_key == this->player->my_ctrl.DROP_KEY_2) {
        if (checkCollision(0, 1, 0))
            this->currentMino->transform(0, 1, 0);
    }
    
}


//a fucntion that fixes a tetromino to the board. 
//than destructs the tetromino object
void TetrisGame::updateBoardStatus() {
    int obj_x_pos, obj_y_pos, obj_rot, obj_shape_index, lines_destroyed = 0;
    this->currentMino->getTransform(obj_x_pos, obj_y_pos, obj_rot);
    this->currentMino->getShapeIndex(obj_shape_index);
    
    writeTetrominoToBoard(obj_x_pos, obj_y_pos, obj_rot, obj_shape_index);
    findAndDestroyLines(obj_y_pos);
}

//checks for lines in the tetromino object position, and destroyes them
void TetrisGame::findAndDestroyLines(int obj_y_pos) {
    int destroyed_lines = 0;
    for (int y_off = 0; y_off < 4; y_off++) {
        if ((obj_y_pos + y_off) < this->board->board_height - 1)
            if (this->board->isALine(obj_y_pos + y_off)) {
                destroyed_lines++;
                this->board->destroyLine(obj_y_pos + y_off);
                this->board->shiftBoardDown(obj_y_pos + y_off);
                this->player->score += (this->base_score_inc) * 4 * destroyed_lines;
            }
    }
    if (destroyed_lines == 0)
        this->player->score += this->base_score_inc;
}

//wirites the tetromino object into the board array
void TetrisGame::writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index) {
    int pixel;
    
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pixel = this->currentMino->rotate(x_off, y_off, obj_rot);
            if (tetromino_shapes[obj_shape_index][pixel] != ' ')
                this->board->writeCellToBoard(obj_x_pos + x_off, obj_y_pos + y_off, tetromino_shapes[obj_shape_index][pixel]);
        }
    }
}


//function that moves the tetromino down every game tick
//can be used to change game speed
void TetrisGame::movePiceDown() {
    if (this->tick_counter > this->ticks_per_drop) {

        if(checkCollision( 0, 1, 0))
        this->currentMino->transform(0, 1, 0);
        else {
            updateBoardStatus();
            this->currentMino->resetTetromino();
        }
        this->tick_counter = 0;
    }
}
// prints stats of the game under the board of the game
void TetrisGame::printGameStats() {
    int print_x = this->board->board_start_x + 1;
    int print_y = this->board->board_start_y + this->board->board_height + 1;
    gotoxy(print_x, print_y);
    std::cout << "Player " << this->player->id << "  Score:" << this->player->score;
}