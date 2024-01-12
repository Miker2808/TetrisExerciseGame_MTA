#pragma once


// keys left as variables to support runtime modification
// all caps is to indicate their use as information access
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


const Controls ctrl_presets[2]{
		{'d','D','a','A','w','W','s','S','x','X'},
		{'l','L','j','J','k','K','i','I','m','M'}
};

struct Player
{
	static unsigned int players_counter;
	unsigned int score = 0;
	unsigned int id = 0;
	Controls my_ctrl;
	

	Player() {
		this->players_counter += 1;
		this->id = players_counter;
		int index = (this->id - 1);
		this->my_ctrl = ctrl_presets[index];

	}


	~Player() {
		this->players_counter -= 1;
	}
};

