#include "Tetromino.h"
#include "TetrisBoard.h"

// Randomly generate a
Tetromino::Tetromino(int start_x, int start_y, TetrisBoard& board) {
	// test (rand() % 5)
	this->shape_index = 2;
	this->x_pos = start_x;
	this->y_pos = start_y;
	this->rotation = 0;
	this->shape = new char[TETROMINO_SIZE*TETROMINO_SIZE + 1];
	this->board_offset_x = board.board_start_x ;
	this->board_offset_y = board.board_start_y ;
	strcpy_s(this->shape, TETROMINO_SIZE*TETROMINO_SIZE + 1,tetromino_shapes[this->shape_index]);
	std::cout << "tetromino shape is: " << this->shape_index << std::endl;
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
	int x_rel = this->x_pos + this->board_offset_x;
	int y_rel = this->y_pos + this->board_offset_y;
	int curr_pixel_index;
	for (int y = 0; y < TETROMINO_SIZE; y++) {
		for (int x = 0; x < TETROMINO_SIZE; x++) {
			gotoxy(x_rel +x , y_rel + y);
			curr_pixel_index = rotate(x, y, this->rotation);
			if ((this->shape)[curr_pixel_index] == 'X') {
				std::cout << (this->shape)[curr_pixel_index];
			}
		}
		
	}
	
}

// Rotates 
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

//function recives 3 refrence int and returns the current position of the tetromino
void Tetromino::getTransform(int& curr_x_pos , int& curr_y_pos , int& curr_rot) {
	curr_x_pos = this->x_pos;
	curr_y_pos = this->y_pos;
	curr_rot = this->rotation;
}

//function recives a refence to an int and returns its shape index
void Tetromino::getShapeIndex(int& shape_index) {
	shape_index = this->shape_index;
}