#include "HeuristicsExplorer.h"


int HeuristicsExplorer::getColumnHeight(TetrisBoard* board, const int x) {

	for (int y = 0; y < board->board_height; y++) {
		if (board->getBoardCell(x, y) != Settings::DEFAULT_EMPTY) {
			return board->board_height - y - 1;
			
		}
	}
}

// returns array of max block height for each column
std::vector<int> HeuristicsExplorer::boardHeights(TetrisBoard* board){
	int height = board->board_height;
	int width = board->board_width;
	std::vector<int> output = std::vector<int>(width - 2, 0);
	char cell;
	
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
/*
int bestColumnScore(TetrisBoard& board, Tetromino& piece) {
	
}

*/

