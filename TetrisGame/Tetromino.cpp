#include "Tetromino.h"

Tetromino::Tetromino() {
	this->shape_index = (rand() % 5);
	this->x_pos = 5;
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
		gotoxy(this->x_pos, this->y_pos + y);
		for (int x = 0; x < TETROMINO_SIZE; x++) {
			curr_pixel_index = rotate(x, y, this->rotation);
			std::cout << (this->shape)[curr_pixel_index];
		}
		
	}
	
}

// modify x, y and r
void Tetromino::transform(int x, int y, int r) {
	this->x_pos = x;
	this->y_pos = y;
	this->rotation = r;
}
