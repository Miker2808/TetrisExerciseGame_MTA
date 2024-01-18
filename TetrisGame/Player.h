#pragma once
#include "Controls.h"

//Represents a player in the Tetris game with a unique ID, score, and control settings.
struct Player
{

	unsigned int score = 0;
	unsigned int id = 0;
	Controls my_ctrl;
	
	// Constructor: Initializes a player with a unique ID and control settings
	Player(const Controls& controls , unsigned int id) {
		this->id = id;
		this->my_ctrl = controls;

	}

	// Destructor: Decrements the player counter when a player is destroyed
	~Player() {

	}
};

