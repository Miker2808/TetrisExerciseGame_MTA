#include "TetrisBoard.h"

// constructor
TetrisBoard::TetrisBoard(int width, int height)
	: board_width(width), board_height(height)
{
	allocateBoard(height, width);
	std::cout << "allocated board" << std::endl;
}

// allocates dynamic memory for the board and initializes with spaces
void TetrisBoard::allocateBoard(int rows, int cols)
{
	this->board = new char* [rows];
	if (this->board == nullptr) {
		std::cout << "Failed to allocated memory for board object" << std::endl;
		exit(-3);
	}

	for (int i = 0; i < rows; i++) {
		(this->board)[i] = new char[cols];
		if ((this->board)[i] == nullptr) {
			std::cout << "Failed to allocated memory for board object" << std::endl;
			exit(-3);
		}
		for (int j = 0; j < cols; j++) {
			this->board[i][j] = ' ';
		}
	}
}

// frees the dynamic board memory
void TetrisBoard::freeBoard(int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] (this->board)[i];
	}
	delete[] this->board;

	this->board = nullptr;
}

// destructor
TetrisBoard::~TetrisBoard() {
	freeBoard(board_height);
	std::cout << "Freed board" << std::endl;
}

// prints the board at x, y position
void TetrisBoard::printBoard(int x, int y) {
	
	for (int curr_height = 0; curr_height < board_height; curr_height++) {
		gotoxy(x, y + curr_height);
		std::cout << wall;
		for (int j = 0; j < board_width; j++) {
			std::cout << board[curr_height][j];
		}
		std::cout << wall;
	}
	gotoxy(x, y + this->board_height);
	for (int i = 0; i <= board_width + 1; i++) {
		std::cout << wall;
	}
}
