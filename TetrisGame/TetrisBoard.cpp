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
void TetrisBoard::allocateBoard(size_t rows, size_t cols)
{
	this->board = std::vector<std::vector<unsigned char>>(rows, std::vector<unsigned char>(cols, Settings::DEFAULT_EMPTY));

	for (size_t i = 0; i < rows; i++) {

		this->board[i][0] = Settings::DEFAULT_WALL_SIGN;
		this->board[i][cols - 1] = Settings::DEFAULT_WALL_SIGN;
	}
	for (size_t j = 0; j < cols; j++) {
		this->board[rows - 1][j] = Settings::DEFAULT_WALL_SIGN;
	}
}

// Frees the dynamic memory allocated for the Tetris board
TetrisBoard::~TetrisBoard() {
	
}

// Changes terminal colors based on symbols on the board
void TetrisBoard::printTetrisColor(char c, HANDLE& hConsole) const{
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
void TetrisBoard::printBoard() const{
	
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

int TetrisBoard::getBoardStartX() const
{
	return this->board_start_x;
}

int TetrisBoard::getBoardStartY() const 
{
	return this->board_start_y;
}

int TetrisBoard::getBoardWidth() const
{
	return this->board_width;
}

int TetrisBoard::getBoardHeight() const
{
	return this->board_height;
}

// Checks a row of the board array, returns true if the row is filled
bool TetrisBoard::isALine(int y_coor) const {
	for (int x = 1; x < board_width-1; x++) {
		if (board[y_coor][x] == Settings::DEFAULT_EMPTY)
			return false;
	}
	return true;
}

// Destroys a filled line on the Tetris board at the given y coordinate
void TetrisBoard::destroyLine(int y_coor) {
	/* // temp delete as it inteferes with the AI calculations
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = '=';
	}
	this->printBoard();
	Sleep(Settings::TICKS_TIME * 2 * global_settings.game_speed); // Makes the remove speed variable
	*/
	for (int x = 1; x < board_width - 1; x++) {
		board[y_coor][x] = Settings::DEFAULT_EMPTY;
	}
	
	// temp delete
	//this->printBoard();
}

// Shifts the entire Tetris board down after clearing a line
void TetrisBoard::shiftBoardDown(int destroyed_line_y ) {
	for (int y = destroyed_line_y -1 ; y >= 0; y--) {
		for (int x = 1; x < board_width - 1; x++) {
			board[y+1][x] = board[y][x];
		}
	}

	for (int x = 1; x < board_width - 1; x++) {
		board[0][x] = Settings::DEFAULT_EMPTY;
	}

}

// Prints the Tetris board in black and white
void TetrisBoard::printBoardBNW() const
{
	for (int curr_height = 0; curr_height < board_height; curr_height++) {
		gotoxy(this->board_start_x, this->board_start_y + curr_height);
		for (int j = 0; j < board_width; j++) {

			std::cout << board[curr_height][j];
		}
	}
}

// Prints the Tetris board in RGB colors
void TetrisBoard::printBoardColor() const
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
char TetrisBoard::getBoardCell(int x , int y) const{
	if (not this->board.empty()) {
		return board[y][x];
	}
	return 0;
}

//Blows up the bomb tetromino
void TetrisBoard::blowUpBomb(int x, int y) {
	int cells_to_blow_up = 0;
	for (int y_off = -4; y_off <= 4; y_off++) {
		if ((y + y_off) >= 0 && (y + y_off) < board_height - 1) {
			cells_to_blow_up = 9 - 2 * abs(y_off);
			for (int x_off = -cells_to_blow_up / 2; x_off <= cells_to_blow_up / 2; x_off++) {
				if ((x + x_off) >= 0 && (x + x_off) < board_width - 1) {
					writeCellToBoard(x + x_off, y + y_off, Settings::DEFAULT_EMPTY);
				}
			}
		}
	}
}