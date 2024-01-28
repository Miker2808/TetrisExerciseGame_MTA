
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
// rotates to desired rotation
void AITetrisGame::movementHandler() {

	int current_x, current_y, current_rot;

	this->currentMino->getTransform(current_x, current_y, current_rot);
	// rotate to desired position
	if (current_rot != this->best_rotation && this->checkCollision(0, 0, 1)) {
		this->currentMino->transform(0, 0, 1);
		
	}
	// only then move it
	else if (current_x > this->best_x) {
		this->currentMino->transform(-1, 0, 0);
	}
	else if (current_x < this->best_x) {
		this->currentMino->transform(1, 0, 0);
	}
	else {
		// drop it
		movePiceDown();
	}

}


// Runs a single cycle of playing the Tetris game
void AITetrisGame::play() {
	
	if (start) {
        this->board->printBoard();
        start = false;
    }
    if (!game_over) {
        this->tick_counter += 1;
        this->ticks_survived += 1;
		this->current_tetromino_ticks += 1;

        this->currentMino->erase();

        this->movementHandler();

        // Move the tetromino down automatically at a regular interval
        forcePiceDown();

        // Check for collision with the bottom or other blocks

        this->currentMino->print();
        this->printGameStats();


    }
    else {
        //print game over on the board
    }
}

int AITetrisGame::getColumnHeight(TetrisBoard* board, const int x) {

	for (int y = 0; y < board->board_height; y++) {
		if (board->getBoardCell(x, y) != Settings::DEFAULT_EMPTY) {
			return board->board_height - y - 1;

		}
	}
	return 0;
}

// returns array of max block height for each column
std::vector<int> AITetrisGame::boardHeights(TetrisBoard* board) {
	int height = board->board_height;
	int width = board->board_width;
	std::vector<int> output = std::vector<int>(width - 2, 0);

	for (int x = 1; x < width - 1; x++) {
		output[x - 1] = getColumnHeight(board, x);
	}

	return output;
}

int AITetrisGame::getColumnHoles(TetrisBoard* board, const int x) {
	int columnHeight = getColumnHeight(board, x);
	int board_height = board->board_height;
	int holes = 0;
	for (int y = 0; y <= columnHeight; y++) {
		if (board->getBoardCell(x, (board_height - y - 1)) == Settings::DEFAULT_EMPTY) {
			holes += 1;
		}
	}
	return holes;
}

// creates a vector that counts the number of holes on each column
std::vector<int> AITetrisGame::boardHoles(TetrisBoard* board) {
	int width = board->board_width;
	std::vector<int> holes = std::vector<int>(width - 2, 0);

	for (int x = 1; x < width - 1; x++) {
		holes[x - 1] = getColumnHoles(board, x);
	}

	return holes;
}


int AITetrisGame::calculateHeuristicScore(TetrisBoard* board) {
	std::vector<int> heightScores = boardHeights(board);
	std::vector<int> holesScores = boardHoles(board);
	int max_height = heightScores[0];
	int total_score = 0;
	for (int i = 1; i < heightScores.size(); i++) {
		total_score -= 2 * heightScores[i];

		if (max_height < heightScores[i]) {
			max_height = heightScores[i];
		}

	}
	
	total_score -= 5 * max_height;
	for (int i = 0; i < holesScores.size(); i++) {
		total_score -= 4 * holesScores[i];
	}

	return total_score;

}

// returns by reference best rotation and best x position
void AITetrisGame::estimateBestMove() {
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