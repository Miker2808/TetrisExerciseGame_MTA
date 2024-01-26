#include "TetrisGame.h"

unsigned int TetrisGame::game_counter = 0;

// Constructor for the TetrisGame object, sets up the initial location and state of the game
TetrisGame::TetrisGame(int start_x, int start_y, bool bombs)
{
    // Create dynamic objects for the game (board, tetromino, and player)
    bombs_present = bombs;
    this->board = new TetrisBoard(start_x, start_y); // start board and set it to be x=10,y=10 relative to console
    this->currentMino = new Tetromino(5, 0, start_x, start_y , bombs_present); // relative to the board
    this->game_counter += 1;
    this->player = new Player(Settings::ctrl_presets[game_counter-1] , game_counter);
}

// Destructor for the TetrisGame object, frees dynamically allocated memory
TetrisGame::~TetrisGame() {
    delete this->board;
    delete this->currentMino;
    delete this->player;
    this->game_counter -= 1;
}

// Runs a single cycle of playing the Tetris game
void TetrisGame::play(unsigned char curr_key) {

    // Initial check to print the board when the game starts
    if (start) {
        this->board->printBoard();
        start = false;
    }


    this->tick_counter += 1;

    this->currentMino->erase();

    this->movementHandler(curr_key);

    // Move the tetromino down automatically at a regular interval
    forcePiceDown();

    // Check for collision with the bottom or other blocks

    this->currentMino->print();
    this->printGameStats();
        
    
}


// Function to check for collision of the tetromino with the board or other blocks
bool TetrisGame::checkCollision(int move_x, int move_y , int move_rot ) {
    // Calculate the next position and rotation of the tetromino based on the provided movement offsets
    int next_x, next_y, next_rot , shape_index;
    this->currentMino->getTransform(next_x, next_y, next_rot);
    this->currentMino->getShapeIndex(shape_index);
    next_x += move_x;
    next_y += move_y;
    next_rot = pyMod((next_rot + move_rot), 4); // map rotation by using modulu

    // Iterate over the tetromino's pixels and check for collisions with the board
    int pixel;
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pixel = this->currentMino->rotate(x_off , y_off, next_rot);
            if (Tetromino::tetromino_shapes[shape_index][pixel] != ' ' && this->board->getBoardCell(next_x + x_off, next_y + y_off) != '.') {
                return false;
            }
        }
    }

    return true;
}

// Handle movement and rotation of the tetromino based on user input
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
        movePiceDown();
    }
    
}


// Function to fix a tetromino to the board and reset the tetromino object to the top
void TetrisGame::updateBoardStatus() {
    int obj_x_pos, obj_y_pos, obj_rot, obj_shape_index, lines_destroyed = 0;
    this->currentMino->getTransform(obj_x_pos, obj_y_pos, obj_rot);
    this->currentMino->getShapeIndex(obj_shape_index);
    if (obj_shape_index == 7) {
        blowBombUp(obj_x_pos, obj_y_pos, obj_rot);
    }
    else {
        writeTetrominoToBoard(obj_x_pos, obj_y_pos, obj_rot, obj_shape_index);
        findAndDestroyLines(obj_y_pos);
    }

}

// Function to find and destroy completed lines in the tetromino's position
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

// Function to write the pixels of the current tetromino to the game board
void TetrisGame::writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index) {
    int pixel;
    
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pixel = this->currentMino->rotate(x_off, y_off, obj_rot);
            if (Tetromino::tetromino_shapes[obj_shape_index][pixel] != ' ')
                this->board->writeCellToBoard(obj_x_pos + x_off, obj_y_pos + y_off, Tetromino::tetromino_shapes[obj_shape_index][pixel]);
        }
    }
}


// Function to force the tetromino down every game tick, affected by game speed
void TetrisGame::forcePiceDown() {
    if (this->tick_counter > this->ticks_per_drop) {
        movePiceDown();
    }
}


// Function to print the game statistics below the game board
void TetrisGame::printGameStats() {
    int print_x = this->board->board_start_x;
    int print_y = this->board->board_start_y + this->board->board_height + 1;
    gotoxy(print_x, print_y);
    std::cout << "Player " << this->player->id << "  Score:" << this->player->score;
}


// Function to move the tetromino down and handle collision
void TetrisGame::movePiceDown() {

    if (checkCollision(0, 1, 0))
        this->currentMino->transform(0, 1, 0);
    else {
        // Update the game board status and reset the tetromino
        updateBoardStatus();
        this->currentMino->resetTetromino();
        this->board->printBoard();

        // Check for collision after resetting the tetromino
        // If there is a collision, the board is full, and the player has lost
        if (!checkCollision(0, 0, 0))
            this->game_over = true;
    }

    //reset the tick counter
    this->tick_counter = 0;
}

//function that blows up the bomb Tetromino
void TetrisGame::blowBombUp(int obj_x_pos, int obj_y_pos, int obj_rot) {
    int pixel;
    for (int y_off = 1; y_off < 3; y_off++) {
        for (int x_off = 1; x_off < 3; x_off++) {
            pixel = this->currentMino->rotate(x_off, y_off, obj_rot);
            if (Tetromino::tetromino_shapes[7][pixel] != ' ')
                this->board->blowUpBomb(obj_x_pos + x_off, obj_y_pos + y_off);
        }
    }

    
}