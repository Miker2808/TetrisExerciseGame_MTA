#include "TetrisGame.h"

unsigned int TetrisGame::game_counter = 0;

// Constructor for the TetrisGame object, sets up the initial location and state of the game
TetrisGame::TetrisGame(int start_x, int start_y, bool bombs , bool human_player)
{
    // Create dynamic objects for the game (board, tetromino, and player)
    this->is_player = human_player;
    bombs_present = bombs;
    this->board = new TetrisBoard(start_x, start_y); // start board and set it to be x=10,y=10 relative to console
    this->currentMino = new Tetromino(5, 0, start_x, start_y , bombs_present); // relative to the board
    this->game_counter += 1;
    if (this->is_player) {
        this->player = new Player(Settings::ctrl_presets[game_counter - 1], game_counter);
    }
    else {
        this->player = new Player(game_counter);
    }

}

// Copy constructor for TetrisGame
TetrisGame::TetrisGame(const TetrisGame& other)
    : base_score_inc(other.base_score_inc),
    game_over(other.game_over),
    start_flag(other.start_flag),
    is_player(other.is_player),
    tick_counter(other.tick_counter),
    ticks_per_drop(other.ticks_per_drop),
    ticks_survived(other.ticks_survived) {

    // Create dynamic objects for the copied game (board, tetromino, and player)
    this->bombs_present = other.bombs_present;
    this->board = new TetrisBoard(*other.board); // Assuming TetrisBoard has a copy constructor
    this->currentMino = new Tetromino(*other.currentMino); // Assuming Tetromino has a copy constructor
    this->player = new Player(*other.player); // Assuming Player has a copy constructor
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
    if (start_flag) {
        this->board->printBoard();
        start_flag = false;
    }
    if (!game_over) {
        this->tick_counter += 1;
        this->ticks_survived += 1;
        this->current_tetromino_ticks += 1;

        this->currentMino->erase();

        this->movementHandler(curr_key);

        // Move the tetromino down automatically at a regular interval
        movePieceDownAfterTick();

        // Check for collision with the bottom or other blocks

        this->currentMino->print();
        this->printGameStats();
        

    }
    else {
        //print game over on the board
    }
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
            pixel = this->currentMino->getCell(x_off , y_off, next_rot);
            if (Tetromino::tetromino_shapes[shape_index][pixel] != ' ' && this->board->getBoardCell(next_x + x_off, next_y + y_off) != '.') {
                return false;
            }
        }
    }

    return true;
}

bool TetrisGame::isGameOver()
{
    return this->game_over;
}

void TetrisGame::setGameOver(bool flag)
{
    this->game_over = flag;
}

bool TetrisGame::isGameStart()
{
    return this->start_flag;
}

void TetrisGame::setGameStart(bool flag)
{
    this->start_flag = flag;
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
        if (checkCollision(0, 0, -1))
            this->currentMino->transform(0, 0, -1);
    }
    else if (curr_key == this->player->my_ctrl.DROP_KEY_1 || curr_key == this->player->my_ctrl.DROP_KEY_2) {
        movePieceDown();
    }
    
}


// Function to fix a tetromino to the board and reset the tetromino object to the top
void TetrisGame::updateBoardStatus() {
    int obj_x_pos, obj_y_pos, obj_rot, obj_shape_index, lines_destroyed = 0;
    this->currentMino->getTransform(obj_x_pos, obj_y_pos, obj_rot);
    this->currentMino->getShapeIndex(obj_shape_index);
    if (obj_shape_index == 7) {
        bombLogic(obj_x_pos, obj_y_pos, obj_rot);
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
        if ((obj_y_pos + y_off) < this->board->getBoardHeight() - 1)
            if (this->board->isALine(obj_y_pos + y_off)) {
                destroyed_lines++;
                this->board->destroyLine(obj_y_pos + y_off);
                this->board->shiftBoardDown(obj_y_pos + y_off);
                this->player->score += (this->base_score_inc) * 4 * destroyed_lines;
            }
    }
    last_tetromino_lines_destroyed = destroyed_lines;
    if (destroyed_lines == 0)
        this->player->score += this->base_score_inc;
}

// Function to write the pixels of the current tetromino to the game board
void TetrisGame::writeTetrominoToBoard(int obj_x_pos, int obj_y_pos, int obj_rot, int obj_shape_index) {
    int pixel;
    
    for (int y_off = 0; y_off < 4; y_off++) {
        for (int x_off = 0; x_off < 4; x_off++) {
            pixel = this->currentMino->getCell(x_off, y_off, obj_rot);
            if (Tetromino::tetromino_shapes[obj_shape_index][pixel] != Settings::DEFAULT_SPACE)
                this->board->writeCellToBoard(obj_x_pos + x_off, obj_y_pos + y_off, Tetromino::tetromino_shapes[obj_shape_index][pixel]);
        }
    }
}


// Function to force the tetromino down every game tick, affected by game speed
void TetrisGame::movePieceDownAfterTick() {
    if (this->tick_counter > this->ticks_per_drop) {
        movePieceDown();
    }
}


// Function to print the game statistics below the game board
void TetrisGame::printGameStats() {
    int print_x = this->board->getBoardStartX();
    int print_y = this->board->getBoardStartY() + this->board->getBoardHeight() + 1;
    gotoxy(print_x, print_y);
    if (this->is_player)
        std::cout << "Player ";
    else {
        std::cout << "CPU ";
    }
    std::cout << this->player->id << "  Score:" << this->player->score;
}


// Function to move the tetromino down and handle collision
void TetrisGame::movePieceDown() {

    if (checkCollision(0, 1, 0))
        this->currentMino->transform(0, 1, 0);
    else {
        // Update the game board status and reset the tetromino
        this->current_tetromino_ticks = 0;
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
void TetrisGame::bombLogic(int obj_x_pos, int obj_y_pos, int obj_rot) {
    int bomb_cell_x_off = 0, bomb_cell_y_off = 0;

    findBombCell(obj_rot, bomb_cell_x_off , bomb_cell_y_off);
    this->board->blowUpBomb(obj_x_pos + bomb_cell_x_off, obj_y_pos + bomb_cell_y_off);
    //TODO maybe change it
    findAndDestroyLines(0);
    findAndDestroyLines(4);
    findAndDestroyLines(8);
    findAndDestroyLines(12);
    findAndDestroyLines(16);
    
}

//finds the bomb index within the bomb tetromino string
void TetrisGame::findBombCell(const int obj_rot , int& bomb_cell_x_off , int& bomb_cell_y_off) {
    int pixel;
    for (int y_off = 1; y_off < 3; y_off++) {
        for (int x_off = 1; x_off < 3; x_off++) {
            pixel = this->currentMino->getCell(x_off, y_off, obj_rot);
            if (Tetromino::tetromino_shapes[7][pixel] != Settings::DEFAULT_SPACE) {
                bomb_cell_x_off = x_off;
                bomb_cell_y_off = y_off;
            }

        }
    }
}

int TetrisGame::getLinesDestroyed() {
    return last_tetromino_lines_destroyed;
}

