#pragma once
#include "Controls.h"
#include "TetrisBotProfile.h"

//Holds static settings for startup configurations and dynamic settings for runtime modification in the Tetris game.
class Settings
{
public:
	// Static settings for startup configurations

	// Number of players in the Tetris game
	static constexpr int NUMBER_OF_PLAYERS = 2;

	// Game clock in milliseconds (time between each tick)
	static constexpr unsigned int TICKS_TIME = 50;

	// Base score increment for each action in the game
	static constexpr int BASE_SCORE_INCREMENT = 25;

	// Ticks per drop, determining the speed of the falling Tetris pieces
	static constexpr unsigned int TICKS_PER_DROP = 20;
	
	// Default width of the Tetris game board
	static constexpr size_t DEFAULT_BOARD_WIDTH = 14;

	// Default height of the Tetris game board
	static constexpr size_t DEFAULT_BOARD_HEIGHT = 19;

	// Default symbol for walls on the Tetris game board
	static constexpr unsigned char DEFAULT_WALL_SIGN = '#';

	// Default symbol for empty cells on the Tetris game board
	static constexpr unsigned char DEFAULT_EMPTY = '.';

	// Default symbol for space bar (literally empty space)
	static constexpr unsigned char DEFAULT_SPACE = ' ';

	// Horizontal offset from the console edge for displaying Tetris boards
	static constexpr int SCREEN_OFFSET_X = 10;

	// Interval between consecutive horizontal offsets for multiplayer Tetris
	static constexpr int SCREEN_OFFSET_INTERVAL_X = 40;

	//Interval between consecutive vertical offsets for multiplayer Tetris
	static constexpr unsigned int SCREEN_OFFSET_INTERVAL_Y = 30;

	//Games displayed in each row
	static constexpr unsigned int SCREEN_GAMES_PER_ROW = 3;

	// Vertical offset from the console edge for displaying Tetris boards
	static constexpr unsigned int SCREEN_OFFSET_Y = 2;

	static constexpr unsigned int BOMB_RADIUS = 4;

	static const Controls ctrl_presets[2];

	static const TetrisBotProfile bot_difficulties[3];

	// keys to access menu features
	static constexpr unsigned char MENU_ONE = '1';
	static constexpr unsigned char MENU_TWO = '2';
	static constexpr unsigned char MENU_THREE = '3';
	static constexpr unsigned char MENU_FOUR = '4';
	static constexpr unsigned char MENU_FIVE = '5';
	static constexpr unsigned char MENU_OPTIONS = '8';
	static constexpr unsigned char MENU_EXIT = '9';
	static constexpr unsigned char MENU_PAUSE = 27;

	// dynamic settings for runtime modification

	int chosen_bot_difficulty[2] = { 0 , 0 };

	// Game speed modifier, affecting the overall speed of the Tetris game
	int game_speed = 1;

	// Flag indicating whether to use colored symbols for Tetris blocks
	bool game_colors = false;

	// Flag indicating whether to use bombs in the tetris game
	bool bombs = true;

	//indicates total human games
	unsigned int num_of_human_players = 1;
	
	//indicates total cpu played games
	unsigned int num_of_bots = 1;
};

