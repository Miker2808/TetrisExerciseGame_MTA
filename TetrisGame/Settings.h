#pragma once


class Settings
{
public:
	// static settings for startup configurations
	static const int NUMBER_OF_PLAYERS = 2;
	static const unsigned int TICKS_TIME = 50; // game clock in (miliseconds)
	static const int BASE_SCORE_INCREMENT = 25;
	static const unsigned int TICKS_PER_DROP = 20;
	static const int DEFAULT_BOARD_WIDTH = 14;
	static const int DEFAULT_BOARD_HEIGHT = 19;
	static const unsigned char DEFAULT_WALL_SIGN = '#';
	static const unsigned char DEFAULT_EMPTY = '.';
	static const unsigned int SCREEN_OFFSET_X = 10;
	static const unsigned int SCREEN_OFFSET_INTERVAL = 40;
	static const unsigned int SCREEN_OFFSET_Y = 2;


	// dynamic settings for runtime modification
	int game_speed = 1;
	bool game_colors = false;
};
