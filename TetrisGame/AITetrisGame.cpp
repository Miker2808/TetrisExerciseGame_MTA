
#include "AITetrisGame.h"

AITetrisGame::AITetrisGame(int start_x, int start_y, bool bombs, bool human_player, TetrisAIProfile ai_profile) :
	TetrisGame(start_x, start_y, bombs, false)
{
	profile = ai_profile;
}


AITetrisGame::AITetrisGame(const AITetrisGame& other) : 
	TetrisGame(other), 
	best_x(other.best_x), 
	best_rotation(other.best_rotation)
{

}

// Getter for best_x
int AITetrisGame::getBestX()
{
	return this->best_x;
}

// Getter for best_rotation
int AITetrisGame::getBestRot()
{
	return this->best_rotation;
}

// Setter for best_x
void AITetrisGame::setBestX(int x)
{
	this->best_x = x;
}

// Setter for best_rotation
void AITetrisGame::setBestRot(int rot)
{
	this->best_rotation = rot;
}


// Handles the movemenent for the CPU game
// rotates to desired rotation and then moves to best X
// moves only if not collision is interfered, otherwise it falls.
void AITetrisGame::movementHandler() {

	int current_x, current_y, current_rot;

	this->currentMino->getTransform(current_x, current_y, current_rot);
	// rotate to desired position
	if (current_rot != this->best_rotation && this->checkCollision(0, 0, 1)) {
		this->currentMino->transform(0, 0, 1);
		
	}
	// move only after completing the rotations
	else if (current_x > this->best_x and this->checkCollision(-1, 0, 0)) {
		this->currentMino->transform(-1, 0, 0);
	}
	else if (current_x < this->best_x and this->checkCollision(1, 0, 0)) {
		this->currentMino->transform(1, 0, 0);
	}
	else {
		// drop the piece down
		movePieceDown();
	}

}


// Runs a single cycle of playing the Tetris game - overrides TetrisGame::play method
void AITetrisGame::play(unsigned char curr_key) {

	if (this->current_tetromino_ticks == 0) {
		this->estimateBestMove();
	}

	if (start_flag) {
        this->board->printBoard();
        start_flag = false;
    }

    if (!game_over) {
        this->tick_counter += 1;
        this->ticks_survived += 1;
		this->current_tetromino_ticks += 1;

        this->currentMino->erase();

        this->movementHandler();

        // Move the tetromino down automatically at a regular interval
        movePieceDownAfterTick();

        // Check for collision with the bottom or other blocks

        this->currentMino->print();
        this->printGameStats();
    }
}

// Returns the height of given column 'x' from board at given pointer
int AITetrisGame::getColumnHeight(TetrisBoard* board, const int x) const{

	for (int y = 0; y < board->getBoardHeight(); y++) {
		if (board->getBoardCell(x, y) != Settings::DEFAULT_EMPTY) {
			return board->getBoardHeight() - y - 1;

		}
	}
	return 0;
}


// Returns the sum of all heights, and the maximum height by reference to maximum
unsigned int AITetrisGame::getBoardMaxHeight(TetrisBoard* board) const {
	size_t height = board->getBoardHeight();
	size_t width = board->getBoardWidth();
	int curr;
	unsigned int maximum = 0;
	for (size_t x = 1; x < width - 1; x++) {
		curr = getColumnHeight(board, x);
		if (curr > maximum) {
			maximum = curr;
		}
	}

	return maximum;
}


// Returns number of holes at given column "x" from pointer of "board"
int AITetrisGame::getColumnHoles(TetrisBoard* board, const int x) const{
	int columnHeight = getColumnHeight(board, x);
	int board_height = board->getBoardHeight();
	int holes = 0;
	for (int y = 0; y <= columnHeight; y++) {
		if (board->getBoardCell(x, (board_height - y - 1)) == Settings::DEFAULT_EMPTY) {
			holes += 1;
		}
	}
	return holes;
}

// Returns the some of holes in the board
unsigned int AITetrisGame::getBoardHolesSum(TetrisBoard* board) const {
	size_t width = board->getBoardWidth();
	unsigned int sum = 0;

	for (unsigned int x = 1; x < width - 1; x++) {
		sum += getColumnHoles(board, x);
	}

	return sum;
}

// Calculates bumpiness relative to left and right columns in terms of blocks from highest block
// in the column
int AITetrisGame::getColumnBumpiness(TetrisBoard* board, const int x) const {
	int difference = 0;

	int xHeight = getColumnHeight(board, x);

	if ((x > 1) and x < (AITetrisGame::playable_width)) {
		difference = abs(xHeight - getColumnHeight(board, x + 1));
	}

	return difference;
}

// Calculates the sum of bumpiness in all columns of the board
unsigned int AITetrisGame::getBoardBumpinessSum(TetrisBoard* board) const {
	size_t width = board->getBoardWidth();
	unsigned int sum = 0;

	for (unsigned int x = 1; x < width - 1; x++) {
		sum += getColumnBumpiness(board, x);
	}

	return sum;
}


// calculates heirustics score by giving a penality for every imperfection with varied weights
double AITetrisGame::calculateHeuristicScore(TetrisBoard* board , int lines_cleard) const{
	unsigned int max_height = getBoardMaxHeight(board);
	unsigned int holesScores = getBoardHolesSum(board);
	unsigned int bumpinessScores = getBoardBumpinessSum(board);
	double total_score = 0;

	total_score -= holesScores * this->profile.holes_penality;
	total_score -= bumpinessScores * profile.bumpiness_penality;
	total_score -= pow(profile.max_height_penality, -1 * max_height);
	total_score += pow((lines_cleard * profile.lines_reward), max_height);

	return total_score;

}

// estimates best_x and best_rotation based on maximum algorithm with scoring
void AITetrisGame::estimateBestMove(){
	int best_x = 0;
	int best_rotation = 0;
	double currScore;
	double bestScore = -DBL_MAX; // most negative value in double
	Tetromino tetrominoCopy = *(this->currentMino); // copy to track after the width and offset for each rotation
	
	// Iterate through all possible moves (rotations and positions)
	for (int rotation = 0; rotation < 4; rotation++) {
		
		tetrominoCopy.assignTransform(0, 0, rotation);
		int shape_width = tetrominoCopy.getShapeWidth();
		int collision_offset = tetrominoCopy.getShapeCollisionOffset();

		// iterate for each rotation, start from x=1 up to the edge the tetromino can achieve excluding walls
		for (int x = 1 - collision_offset; x < Settings::DEFAULT_BOARD_WIDTH - (collision_offset + shape_width); x++) {
			
			AITetrisGame simulatedGame(*this);

			simulatedGame.currentMino->assignTransform(x, 0, rotation);

			// move to next x if this column is full
			if (not simulatedGame.checkCollision(0, 0, 0)) {
				continue;
			}

			// push piece down until it collides
			while (simulatedGame.checkCollision(0, 1, 0)) {
				simulatedGame.currentMino->transform(0, 1, 0);
			}

			simulatedGame.updateBoardStatus();

			// Calculate heuristic score for the simulated board
			currScore = calculateHeuristicScore(simulatedGame.board, simulatedGame.getLinesDestroyed());
			// Update best move if the score is better
			if (currScore > bestScore) {
				bestScore = currScore;
				best_x = x;
				best_rotation = rotation;
			}
		}
	}

	this->best_x = best_x;
	this->best_rotation = best_rotation;
	
}