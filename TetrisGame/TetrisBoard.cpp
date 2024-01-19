#include "TetrisBoard.h"

// Constructor: Initializes a dynamic 2D array and sets the position and dimensions of the Tetris board
TetrisBoard::TetrisBoard(int pos_x, int pos_y, int width, int height)
	: board_start_x(pos_x), board_start_y(pos_y), board_width(width), board_height(height)
{
	allocateBoard(height, width);
}

// Copy constructor for TetrisBoard
TetrisBoard::TetrisBoard(const TetrisBoard& other)
	: board_start_x(other.board_start_x), board_start_y(other.board_start_y),
	board_width(other.board_width), board_height(other.board_height)
{
	// Allocate memory for the new Tetris board
	allocateBoard(board_height, board_width);

	// Copy the content of the original board to the new one
	for (int i = 0; i < board_height; i++) {
		for (int j = 0; j < board_width; j++) {
			this->board[i][j] = other.board[i][j];
		}
	}
}


// Allocates dynamic memory for the board and initializes it with "empty spaces"
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

// Frees the dynamic memory allocated for the Tetris board
void TetrisBoard::freeBoard(int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] (this->board)[i];
	}
	delete[] this->board;

	this->board = nullptr;
	
}

// Frees the dynamic memory allocated for the Tetris board
TetrisBoard::~TetrisBoard() {
	freeBoard(board_height);
}

// Changes terminal colors based on symbols on the board
void TetrisBoard::printTetrisColor(char c, HANDLE& hConsole) {
	unsigned char color = 0;
	unsigned char guide_char = Settings::DEFAULT_SPACE; // to assist with navigation (blank is disorienting)
	switch (c) {
	case 'A': 
		color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case 'B': 
		color = BACKGROUND_RED;
		break;
	case 'C': 
		color = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case 'D': 
		color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case 'E': 
		color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case 'F': 
		color = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case 'G': 
		color = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case Settings::DEFAULT_WALL_SIGN: 
		color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	case Settings::DEFAULT_EMPTY: 
		guide_char = Settings::DEFAULT_EMPTY;
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	default: 
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
	
	SetConsoleTextAttribute(hConsole, color);
	std::cout << guide_char; 

}

// Prints the Tetris board at its current position
void TetrisBoard::printBoard() {
	
	if (global_settings.game_colors) {
		printBoardColor();
	}
	else {
		printBoardBNW();
	}
}

// Writes a given 'cell content' into a cell at specified coordinates
void TetrisBoard::writeCellToBoard(int x_coor , int y_coor , char cell_contents) {
	this->board[y_coor][x_coor] = cell_contents;
}

// Checks a row of the board array, returns true if the row is filled
bool TetrisBoard::isALine(int y_coor) {
	for (int x = 1; x < board_width-1; x++) {
		if (board[y_coor][x] == def_empty)
			return false;
	}
	return true;
}

// Destroys a filled line on the Tetris board at the given y coordinate
void TetrisBoard::destroyLine(int y_coor) {
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = '=';
	}
	this->printBoard();
	Sleep(Settings::TICKS_TIME * 2 * global_settings.game_speed); // Makes the remove speed variable
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = def_empty;
	}
	this->printBoard();
}

// Shifts the entire Tetris board down after clearing a line
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

// Prints the Tetris board in black and white
void TetrisBoard::printBoardBNW() 
{
	for (int curr_height = 0; curr_height < board_height; curr_height++) {
		gotoxy(this->board_start_x, this->board_start_y + curr_height);
		for (int j = 0; j < board_width; j++) {

			std::cout << board[curr_height][j];
		}
	}
}

// Prints the Tetris board in RGB colors
void TetrisBoard::printBoardColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int curr_height = 0; curr_height < board_height; curr_height++) {
		gotoxy(this->board_start_x, this->board_start_y + curr_height);
		for (int j = 0; j < board_width; j++) {

			printTetrisColor(board[curr_height][j], hConsole);
		}
	}
	SetConsoleTextAttribute(hConsole , FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//Returns a value for a specific cell in the board array
char TetrisBoard::getBoardCell(int x , int y){
	return board[y][x];
}

//check if works
void TetrisBoard::blowUpBomb(int x, int y) {

	for (int y_off = -4; y_off <= 4; y_off++) {
		if( (y+y_off) >= 0 && (y + y_off) < board_height-1 )
		{
			for (int x_off = -4; x_off <= 4; x_off++)
			{
				if ((x + x_off) > 0 && (x + x_off) < board_width - 1)
					writeCellToBoard(x + x_off , y + y_off , def_empty);
			}
		}
	}
}