#pragma once
#include "Controls.h"

//Holds static settings for startup configurations and dynamic settings for runtime modification in the Tetris game.
class Settings
{
public:
	// Static settings for startup configurations

	// Number of players in the Tetris game
	static const int NUMBER_OF_PLAYERS = 2;

	// Game clock in milliseconds (time between each tick)
	static const unsigned int TICKS_TIME = 50;

	// Base score increment for each action in the game
	static const int BASE_SCORE_INCREMENT = 25;

	// Ticks per drop, determining the speed of the falling Tetris pieces
	static const unsigned int TICKS_PER_DROP = 20;
	
	// Default width of the Tetris game board
	static const int DEFAULT_BOARD_WIDTH = 14;

	// Default height of the Tetris game board
	static const int DEFAULT_BOARD_HEIGHT = 19;

	// Default symbol for walls on the Tetris game board
	static const unsigned char DEFAULT_WALL_SIGN = '#';

	// Default symbol for empty cells on the Tetris game board
	static const unsigned char DEFAULT_EMPTY = '.';

	// Default symbol for space bar (literally empty space)
	static const unsigned char DEFAULT_SPACE = ' ';

	// Horizontal offset from the console edge for displaying Tetris boards
	static const unsigned int SCREEN_OFFSET_X = 10;

	// Interval between consecutive horizontal offsets for multiplayer Tetris
	static const unsigned int SCREEN_OFFSET_INTERVAL = 40;

	// Vertical offset from the console edge for displaying Tetris boards
	static const unsigned int SCREEN_OFFSET_Y = 2;

	static const Controls ctrl_presets[2];

	// keys to access menu features
	static const unsigned char MENU_ONE = '1';
	static const unsigned char MENU_TWO = '2';
	static const unsigned char MENU_OPTIONS = '8';
	static const unsigned char MENU_EXIT = '9';
	static const unsigned char MENU_PAUSE = 27;

	// dynamic settings for runtime modification

	// Game speed modifier, affecting the overall speed of the Tetris game
	int game_speed = 1;

	// Flag indicating whether to use colored symbols for Tetris blocks
	bool game_colors = false;

	// Flag indicating whether to use bombs in the tetris game
	bool bombs = true;
};

