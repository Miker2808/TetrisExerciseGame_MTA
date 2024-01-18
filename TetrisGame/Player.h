#pragma once
#include "Controls.h"

//Represents the key controls for a player, allowing runtime modification.
// Note: All caps variable names indicate their use as information access.
//struct Controls{
//	unsigned char MOVE_RIGHT_KEY_1;
//	unsigned char MOVE_RIGHT_KEY_2;
//	unsigned char MOVE_LEFT_KEY_1;
//	unsigned char MOVE_LEFT_KEY_2;
//	unsigned char ROT_RIGHT_KEY_1;
//	unsigned char ROT_RIGHT_KEY_2;
//	unsigned char ROT_LEFT_KEY_1;
//	unsigned char ROT_LEFT_KEY_2;
//	unsigned char DROP_KEY_1;
//	unsigned char DROP_KEY_2;
//};

// Array of predefined control presets for two players
//const Controls ctrl_presets[2]{
//		{'d','D','a','A','w','W','s','S','x','X'}, // Controls for player 1
//		{'l','L','j','J','k','K','i','I','m','M'}  // Controls for player 2
//};


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

