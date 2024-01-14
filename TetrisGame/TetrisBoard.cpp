#include "TetrisBoard.h"

// constructor that initializes a dynamic 2D array and position of the board
TetrisBoard::TetrisBoard(int pos_x, int pos_y, int width, int height)
	: board_start_x(pos_x), board_start_y(pos_y), board_width(width), board_height(height)
{
	allocateBoard(height, width);
}

// allocates dynamic memory for the board and initializes with spaces
void TetrisBoard::allocateBoard(int rows, int cols)
{
	this->board = new char* [rows];


	for (int i = 0; i < rows; i++) {
		(this->board)[i] = new char[cols];

		this->board[i][0] = wall;
		this->board[i][cols - 1] = wall;

		for (int j = 1; j < cols - 1; j++) {
			this->board[i][j] = def_empty;
		}
		
	}
	for (int j = 0; j < cols; j++) {
		this->board[rows - 1][j] = wall;
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
	debugPrint("Tetris board destructed", 0,1, 2);
}

// changes terminal colors based on symbols on the board
void TetrisBoard::printTetrisColor(char c, HANDLE& hConsole) {
	switch (c) {
	case 'A': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY); 
		break;
	case 'B': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY); 
		break;
	case 'C': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY); 
		break;
	case 'D': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_INTENSITY); 
		break;
	case 'E': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); 
		break;
	case 'F': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN); 
		break;
	case 'G': 
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY); 
		break;
	case Settings::DEFAULT_WALL_SIGN: 
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); 
		break;
	case Settings::DEFAULT_EMPTY: 
		SetConsoleTextAttribute(hConsole, 0); 
		break;
	default: 
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	std::cout << ' ';

}

// prints the board at x, y position
void TetrisBoard::printBoard() {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int curr_height = 0; curr_height < board_height; curr_height++) {
		gotoxy(this->board_start_x, this->board_start_y + curr_height);
		for (int j = 0; j < board_width; j++) {

			if (global_settings.game_colors) {
				printTetrisColor(board[curr_height][j], hConsole);
			}
			else {
				std::cout << board[curr_height][j];
			}
		}
	}
}

//writes a given 'cell content' into a cell
void TetrisBoard::writeCellToBoard(int x_coor , int y_coor , char cell_contents) {
	this->board[y_coor][x_coor] = cell_contents;
}

//checks a row of the board array, returns true if the row is filled
bool TetrisBoard::isALine(int y_coor) {
	for (int x = 1; x < board_width-1; x++) {
		if (board[y_coor][x] == def_empty)
			return false;
	}
	return true;
}

void TetrisBoard::destroyLine(int y_coor) {
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = '=';
	}
	this->printBoard();
	Sleep(Settings::TICKS_TIME * 2);
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = def_empty;
	}
	this->printBoard();
}

void TetrisBoard::shiftBoardDown(int destroyed_line_y ) {
	for (int y = destroyed_line_y -1 ; y >= 0; y--) {
		for (int x = 1; x < board_width - 1; x++) {
			board[y+1][x] = board[y][x];
		}
	}

	for (int x = 1; x < board_width - 1; x++) {
		board[0][x] = def_empty;
	}

}




