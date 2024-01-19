#include "Tetromino.h"

const char Tetromino::tetromino_shapes[8][17] = {
		{"  A   A   A   A "}, // vertical line shape
		{"     BB  BB     "}, // square shape
		{"    C   C   CC  "}, // L shape
		{" D   DD   D     "}, // S shape
		{"     E  EEE     "}, // T shape
		{"       F   F  FF"}, // inverted L shape
		{"  G  GG  G      "}, // inverted S shape
		{"         @      "}  //bomb
};


// Randomly generate a tetromino piece, places it at (start_x, start_y) relative to (board_x, board_y)
Tetromino::Tetromino(int start_x, int start_y, int board_start_x, int board_start_y, bool bombs_flag) {
	this->shape_index = 7;
	this->start_pos_x = start_x;
	this->start_pos_y = start_y;
	this->x_pos = start_x;
	this->y_pos = start_y;
	this->rotation = 0;
	this->board_offset_x = board_start_x ;
	this->board_offset_y = board_start_y ;
	this->bombs_present = bombs_flag;

}

// destructor for the tetromino piece
Tetromino::~Tetromino() {

}


int Tetromino::initShapeindex() {
	if (!bombs_present)
		return rand() % 7;
	else {
		if (rand() % 20)
			return rand() % 7;
		else
			return 7;
	}
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

// Function to reset the tetromino to its initial state
void Tetromino::resetTetromino() {
	this->shape_index = (rand() % 7);
	this->x_pos = this->start_pos_x;
	this->y_pos = this->start_pos_y;
	this->rotation = 0;
}

// Function to print the tetromino in black and white colors on the console
// Supports erasing the tetromino if 'erase' is true
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
					std::cout << Settings::DEFAULT_EMPTY;
				else
					std::cout << tetromino_shapes[this->shape_index][curr_pixel_index];
			}
		}

	}
}

// Function to print the tetromino in RGB colors on the console
// Supports erasing the tetromino if 'erase' is true
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
					std::cout << Settings::DEFAULT_EMPTY;
				else
					printCharColor(tetromino_shapes[this->shape_index][curr_pixel_index], hConsole);
			}
		}

	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


// Function to print a colored character on the console based on the provided character code
// Uses the provided console handle for setting text attributes
void Tetromino::printCharColor(char c, HANDLE& hConsole) {
	unsigned char color = 0;
	unsigned char guide_char = Settings::DEFAULT_SPACE;
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
		break;
	default:
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

	SetConsoleTextAttribute(hConsole, color);
	std::cout << guide_char;

}

// Function to erase the tetromino from the console display
// Chooses between color and black-and-white printing based on global game settings
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