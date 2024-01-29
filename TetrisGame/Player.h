#pragma once
#include "Controls.h"

//Represents a player in the Tetris game with a unique ID, score, and control settings.
struct Player
{
	bool isCPU;
	unsigned int score = 0;
	unsigned int id = 0;
	Controls my_ctrl;
	
	// Constructor: Initializes a player with a unique ID and control settings
	Player(const Controls& controls , unsigned int id) {
		this->id = id;
		this->my_ctrl = controls;
		this->isCPU = false;

	}

	Player(const Player& other) {
		this->isCPU = other.isCPU;
		this->score = other.score;
		this->id = other.id;
		this->my_ctrl = other.my_ctrl;
	}

	Player(unsigned int id) {
		this->id = id;
		//for debugging reasons , to emphasise that this game is CPU controlled 
		this->my_ctrl = { '~','~','~','~','~','~','~','~','~','~' };
		this->isCPU = true;
	}

	~Player() {

	}
};

