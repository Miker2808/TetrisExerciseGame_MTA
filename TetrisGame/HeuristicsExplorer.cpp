#include "HeuristicsExplorer.h"


int HeuristicsExplorer::getColumnHeight(TetrisBoard* board, const int x) {

	for (int y = 0; y < board->board_height; y++) {
		if (board->getBoardCell(x, y) != Settings::DEFAULT_EMPTY) {
			return board->board_height - y - 1;
			
		}
	}
	return 0;
}

// returns array of max block height for each column
std::vector<int> HeuristicsExplorer::boardHeights(TetrisBoard* board){
	int height = board->board_height;
	int width = board->board_width;
	std::vector<int> output = std::vector<int>(width - 2, 0);
	
	for (int x = 1; x < width - 1; x++) {
		output[x - 1] = getColumnHeight(board, x);
	}

	return output;
}

int HeuristicsExplorer::getColumnHoles(TetrisBoard* board, const int x) {
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
std::vector<int> HeuristicsExplorer::boardHoles(TetrisBoard* board) {
	int width = board->board_width;
	std::vector<int> holes = std::vector<int>(width - 2, 0);

	for (int x = 1; x < width - 1; x++) {
		holes[x-1] = getColumnHoles(board, x);
	}

	return holes;
}


int calculateHeuristicScore(TetrisBoard* board) {
	std::vector<int> heightScores = HeuristicsExplorer::boardHeights(board);
	std::vector<int> holesScores = HeuristicsExplorer::boardHoles(board);
	int max_height = heightScores[0];
	int total_score = 0;
	for (int i = 1; i < heightScores.size(); i++) {
		total_score -= heightScores[i];

		if (max_height < heightScores[i]) {
			max_height = heightScores[i];
		}
		
	}

	total_score -= 10 * max_height;
	for (int i = 0; i < holesScores.size(); i++) {
		total_score -= 2 * holesScores[i];
	}

	return total_score;

}

// returns vector<int> {x,rotation} for best rotation and x for the game
std::vector<int> HeuristicsExplorer::chooseMove(const TetrisGame & game) {
	std::vector<int> bestMove = { 0, 0 };
	int currScore;
	int bestScore = INT_MIN;
	Tetromino copyMino =  *(game.currentMino);

	// Iterate through all possible moves (rotations and positions)
	for (int rotation = 0; rotation < 4; rotation++) {
		
		copyMino.assignTransform(0, 0, rotation);
		int shape_width = copyMino.getShapeWidth();
		int collision_offset = copyMino.getShapeCollisionOffset();

		// iterate for each rotation, start from x=1 up to the edge the tetromino can achieve excluding walls
		for (int x = 1; x < Settings::DEFAULT_BOARD_WIDTH - shape_width - 1; x++) {
			
			TetrisGame simulatedGame = game;

			simulatedGame.currentMino->assignTransform(x - collision_offset,  0, rotation);

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
				bestMove[0] = x;
				bestMove[1] = rotation;
			}
		}
	}
	//debugPrint("Bestscore: ", bestScore, 40, 23);
	
	return bestMove;
}