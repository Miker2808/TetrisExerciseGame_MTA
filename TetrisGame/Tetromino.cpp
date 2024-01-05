#include "Tetromino.h"

Tetromino::Tetromino() {
	this->shape_index = (rand() % 5);
	this->x_pos = 0;
	this->y_pos = 0;
	this->rotation = 0;
	this->shape = new char[TETROMINO_SIZE*TETROMINO_SIZE + 1];
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
	int curr_pixel_index;
	for (int y = 0; y < TETROMINO_SIZE; y++) {
		for (int x = 0; x < TETROMINO_SIZE; x++) {
			gotoxy(this->x_pos + x, this->y_pos + y);
			curr_pixel_index = rotate(x, y, this->rotation);
			if ((this->shape)[curr_pixel_index] == 'X') {
				std::cout << (this->shape)[curr_pixel_index];
			}
		}
		
	}
	
}

for (
	for (
		shape[x][y] ==? "X"
		)
	)

// Rotates 
void Tetromino::transform(int move_x, int move_y, int rotate) {
	this->x_pos += move_x;
	this->y_pos += move_y;
	this->rotation += rotate;
}

