
#include "AITetrisGame.h"

AITetrisGame::AITetrisGame(int start_x, int start_y, bool bombs, bool human_player) : 
	TetrisGame(start_x, start_y, bombs, false)
{

}


AITetrisGame::AITetrisGame(const AITetrisGame& other) : 
	TetrisGame(other), 
	best_x(other.best_x), 
	best_rotation(other.best_rotation)
{

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
		movePiceDown();
	}

}


// Runs a single cycle of playing the Tetris game
void AITetrisGame::play() {

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

// returns the height of given column 'x' from board at given pointer
int AITetrisGame::getColumnHeight(TetrisBoard* board, const int x) const{

	for (int y = 0; y < board->getBoardHeight(); y++) {
		if (board->getBoardCell(x, y) != Settings::DEFAULT_EMPTY) {
			return board->getBoardHeight() - y - 1;

		}
	}
	return 0;
}

// returns array of max block height for each column
std::vector<int> AITetrisGame::boardHeights(TetrisBoard* board) const{
	size_t height = board->getBoardHeight();
	size_t width = board->getBoardWidth();
	std::vector<int> output = std::vector<int>(width - 2, 0);

	for (unsigned int x = 1; x < width - 1; x++) {
		output[x - 1] = getColumnHeight(board, x);
	}

	return output;
}

// best_x getter
int AITetrisGame::getBestX()
{
	return this->best_x;
}

// best_rotation getter
int AITetrisGame::getBestRot()
{
	return this->best_rotation;
}

// best_x setter
void AITetrisGame::setBestX(int x)
{
	this->best_x = x;
}

// best_rotation setter
void AITetrisGame::setBestRot(int rot)
{
	this->best_rotation = rot;
}


// returns number of holes at given column "x" from pointer of "board"
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

// creates a vector that counts the number of holes on each column
std::vector<int> AITetrisGame::boardHoles(TetrisBoard* board) const{
	size_t width = board->getBoardWidth();
	std::vector<int> holes = std::vector<int>(width - 2, 0);

	for (unsigned int x = 1; x < width - 1; x++) {
		holes[x - 1] = getColumnHoles(board, x);
	}

	return holes;
}

// calculates heirustics score by giving a penality for every imperfection with varied weights
// Note: perfect calculation is achieved only by actively teaching for best penality coefficients
int AITetrisGame::calculateHeuristicScore(TetrisBoard* board) const{
	// should sum to 20
	const unsigned int height_penalty = 5;
	const unsigned int max_height_penality = 10;
	const unsigned int holes_penality = 6;

	std::vector<int> heightScores = boardHeights(board);
	std::vector<int> holesScores = boardHoles(board);
	int max_height = heightScores[0];
	int total_score = 0;
	for (int i = 1; i < heightScores.size(); i++) {
		total_score -= height_penalty * heightScores[i];

		if (max_height < heightScores[i]) {
			max_height = heightScores[i];
		}

	}
	
	total_score -= max_height_penality * max_height;
	for (int i = 0; i < holesScores.size(); i++) {
		total_score -= holes_penality * holesScores[i];
	}

	return total_score;

}

// returns by reference best rotation and best x position
void AITetrisGame::estimateBestMove(){
	int best_x = 0;
	int best_rotation = 0;
	int currScore;
	int bestScore = INT_MIN;
	Tetromino tetrominoCopy = *(this->currentMino); // copy to track after width and offset for each rotation
	
	// Iterate through all possible moves (rotations and positions)
	for (int rotation = 0; rotation < 4; rotation++) {
		
		tetrominoCopy.assignTransform(0, 0, rotation);
		int shape_width = tetrominoCopy.getShapeWidth();
		int collision_offset = tetrominoCopy.getShapeCollisionOffset();

		// iterate for each rotation, start from x=1 up to the edge the tetromino can achieve excluding walls
		for (int x = 1 - collision_offset; x < Settings::DEFAULT_BOARD_WIDTH - (collision_offset + shape_width); x++) {
			
			AITetrisGame simulatedGame(*this);
			simulatedGame.currentMino->assignTransform(x, 0, rotation);

			// push piece down until it collides
			while (simulatedGame.checkCollision(0, 1, 0)) {
				simulatedGame.currentMino->transform(0, 1, 0);
			}

			simulatedGame.updateBoardStatus();

			// Calculate heuristic score for the simulated board
			currScore = calculateHeuristicScore(simulatedGame.board);
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