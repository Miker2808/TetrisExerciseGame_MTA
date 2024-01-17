#pragma once


//Represents the key controls for a player, allowing runtime modification.
// Note: All caps variable names indicate their use as information access.
struct Controls{
	unsigned char MOVE_RIGHT_KEY_1;
	unsigned char MOVE_RIGHT_KEY_2;
	unsigned char MOVE_LEFT_KEY_1;
	unsigned char MOVE_LEFT_KEY_2;
	unsigned char ROT_RIGHT_KEY_1;
	unsigned char ROT_RIGHT_KEY_2;
	unsigned char ROT_LEFT_KEY_1;
	unsigned char ROT_LEFT_KEY_2;
	unsigned char DROP_KEY_1;
	unsigned char DROP_KEY_2;
};

// Array of predefined control presets for two players
const Controls ctrl_presets[2]{
		{'d','D','a','A','w','W','s','S','x','X'}, // Controls for player 1
		{'l','L','j','J','k','K','i','I','m','M'}  // Controls for player 2
};


//Represents a player in the Tetris game with a unique ID, score, and control settings.
struct Player
{
	static unsigned int players_counter;
	unsigned int score = 0;
	unsigned int id = 0;
	Controls my_ctrl;
	
	// Constructor: Initializes a player with a unique ID and control settings
	Player() {
		this->players_counter += 1;
		this->id = players_counter;
		int index = (this->id - 1);
		this->my_ctrl = ctrl_presets[index];

	}

	// Destructor: Decrements the player counter when a player is destroyed
	~Player() {
		this->players_counter -= 1;
	}
};

