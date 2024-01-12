#pragma once

struct ControlsPresetOne {
	static const unsigned char MOVE_RIGHT_KEY_1 = 'd';
	static const unsigned char MOVE_RIGHT_KEY_2 = 'D';
	static const unsigned char MOVE_LEFT_KEY_1 = 'a';
	static const unsigned char MOVE_LEFT_KEY_2 = 'A';
	static const unsigned char ROT_RIGHT_KEY_1 = 'w';
	static const unsigned char ROT_RIGHT_KEY_2 = 'W';
	static const unsigned char ROT_LEFT_KEY_1 = 's';
	static const unsigned char ROT_LEFT_KEY_2 = 'S';
	static const unsigned char DROP_KEY_1 = 'x';
	static const unsigned char DROP_KEY_2 = 'X';
};

struct ControlsPresetTwo {
	static const unsigned char MOVE_RIGHT_KEY_1 = 'l';
	static const unsigned char MOVE_RIGHT_KEY_2 = 'L';
	static const unsigned char MOVE_LEFT_KEY_1 = 'j';
	static const unsigned char MOVE_LEFT_KEY_2 = 'J';
	static const unsigned char ROT_RIGHT_KEY_1 = 'k';
	static const unsigned char ROT_RIGHT_KEY_2 = 'K';
	static const unsigned char ROT_LEFT_KEY_1 = 'i';
	static const unsigned char ROT_LEFT_KEY_2 = 'I';
	static const unsigned char DROP_KEY_1 = 'm';
	static const unsigned char DROP_KEY_2 = 'M';
};

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

	void setSecondaryControls() {
		MOVE_RIGHT_KEY_1 = ControlsPresetTwo::MOVE_RIGHT_KEY_1;
		MOVE_RIGHT_KEY_2 = ControlsPresetTwo::MOVE_RIGHT_KEY_2;
		MOVE_LEFT_KEY_1 = ControlsPresetTwo::MOVE_LEFT_KEY_1;
		MOVE_LEFT_KEY_2 = ControlsPresetTwo::MOVE_LEFT_KEY_2;
		ROT_RIGHT_KEY_1 = ControlsPresetTwo::ROT_RIGHT_KEY_1;
		ROT_RIGHT_KEY_2 = ControlsPresetTwo::ROT_RIGHT_KEY_2;
		ROT_LEFT_KEY_1 = ControlsPresetTwo::ROT_LEFT_KEY_1;
		ROT_LEFT_KEY_2 = ControlsPresetTwo::ROT_LEFT_KEY_2;
		DROP_KEY_1 = ControlsPresetTwo::DROP_KEY_1;
		DROP_KEY_2 = ControlsPresetTwo::DROP_KEY_2;
	}
};

