#pragma once


struct Player
{
	static unsigned int players_counter;
	unsigned int score = 0;
	unsigned int id = 0;

	// keys left as variables to support runtime modification
	// all caps is to indicate their use as information access
	unsigned char MOVE_RIGHT_KEY_1 = 'd';
	unsigned char MOVE_RIGHT_KEY_2 = 'D';
	unsigned char MOVE_LEFT_KEY_1 = 'a';
	unsigned char MOVE_LEFT_KEY_2 = 'A';
	unsigned char ROT_RIGHT_KEY_1 = 'w';
	unsigned char ROT_RIGHT_KEY_2 = 'W';
	unsigned char ROT_LEFT_KEY_1 = 's';
	unsigned char ROT_LEFT_KEY_2 = 'S';
	unsigned char DROP_KEY_1 = 'x';
	unsigned char DROP_KEY_2 = 'X';

	Player() {
		this->players_counter += 1;
		this->id = players_counter;

	}

	~Player() {
		this->players_counter -= 1;
	}


};

