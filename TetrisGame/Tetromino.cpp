#include "Tetromino.h"

// Randomly generate a tetromino piece, places it at (start_x, start_y) relative to (board_x, board_y)
Tetromino::Tetromino(int start_x, int start_y, int board_start_x, int board_start_y) {
	this->shape_index = rand() % 7;
	this->start_pos_x = start_x;
	this->start_pos_y = start_y;
	this->x_pos = start_x;
	this->y_pos = start_y;
	this->rotation = 0;
	this->board_offset_x = board_start_x ;
	this->board_offset_y = board_start_y ;

	debugPrint("Generated tetromino shape", this->shape_index, 1, 23);
}

// destructor for the tetromino piece
Tetromino::~Tetromino() {
	debugPrint("Destroyed tetromino shape", 0 , 1, 23);
}

// returns point of 1D with rotation from 2D coordinates
int Tetromino::rotate(int x, int y, int rotation) {
	switch (rotation) {
		case 1: return 12 + y - (x * 4); // 90 deg rotation
		case 2: return 15 - x - (y * 4); // 180 deg rotation
		case 3: return 3 - y + (x * 4); // 270 deg rotation
		default: // no rotation
			return y * 4 + x;
	}
}

// prints the shape at x,y based on rotation using the "rotate" method
void Tetromino::print()
{
	if (global_settings.game_colors) {
		printColor();
	}
	else {
		printBNW();
	}
	
}

// updates the coordinates of the tetromino piece.
void Tetromino::transform(int move_x, int move_y, int rotate) {
	this->x_pos += move_x;
	this->y_pos += move_y;
	this->rotation += rotate;

	if (this->rotation > 3) {
		this->rotation = 0;
	}
	else if (this->rotation < 0) {
		this->rotation += 4;
	}
}

//function recives 3 reference int and returns the current position of the tetromino
void Tetromino::getTransform(int& curr_x_pos , int& curr_y_pos , int& curr_rot) {
	curr_x_pos = this->x_pos;
	curr_y_pos = this->y_pos;
	curr_rot = this->rotation;
}

//function recives a reference to an int and returns its shape index
void Tetromino::getShapeIndex(int& shape_index) {
	shape_index = this->shape_index;
}

void Tetromino::resetTetromino() {
	this->shape_index = (rand() % 7);
	this->x_pos = this->start_pos_x;
	this->y_pos = this->start_pos_y;
	this->rotation = 0;
	debugPrint("Tetromino shape was reset to:", this->shape_index, 1, 23);
}


void Tetromino::printBNW(bool erase) {

	int x_absolute = this->x_pos + this->board_offset_x;
	int y_absolute = this->y_pos + this->board_offset_y;
	int curr_pixel_index;
	for (int y = 0; y < TETROMINO_SIZE; y++) {
		for (int x = 0; x < TETROMINO_SIZE; x++) {
			gotoxy(x_absolute + x, y_absolute + y);
			curr_pixel_index = rotate(x, y, this->rotation);
			if (tetromino_shapes[this->shape_index][curr_pixel_index] != ' ') {
				if(erase)
					std::cout << '.';
				else
					std::cout << tetromino_shapes[this->shape_index][curr_pixel_index];
			}
		}

	}
}

void Tetromino::printColor(bool erase) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int x_absolute = this->x_pos + this->board_offset_x;
	int y_absolute = this->y_pos + this->board_offset_y;
	int curr_pixel_index;
	for (int y = 0; y < TETROMINO_SIZE; y++) {
		for (int x = 0; x < TETROMINO_SIZE; x++) {
			gotoxy(x_absolute + x, y_absolute + y);
			curr_pixel_index = rotate(x, y, this->rotation);
			if (tetromino_shapes[this->shape_index][curr_pixel_index] != ' ') {
				if(erase)
					std::cout << ' ';
				else
					printCharColor(tetromino_shapes[this->shape_index][curr_pixel_index], hConsole);
			}
		}

	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


// changes terminal colors based on symbols on the board
void Tetromino::printCharColor(char c, HANDLE& hConsole) {
	switch (c) {
	case 'A':
		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		break;
	case 'B':
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
		break;
	case 'C':
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY);
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


void Tetromino::erase()
{
	bool erase = true;
	if (global_settings.game_colors) {
		printColor(erase);
	}
	else {
		printBNW(erase);
	}

}