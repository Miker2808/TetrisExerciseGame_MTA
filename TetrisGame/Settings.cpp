#include "Settings.h"


const Controls Settings::ctrl_presets[2] = {
	{'d','D','a','A','w','W','s','S','x','X'}, // Controls for player 1
	{'l','L','j','J','k','K','i','I','m','M'}  // Controls for player 2
};


const TetrisAIProfile Settings::bot_difficulties[3] = {
	{0.627633 , 0.756441 , 0.254815, 0.9763},//Novice
	{0.618981 , 0.762115 , 0.253861, 0.974763},//Good
	{0.626957 , 0.830306 , 0.552015, 0.195814}//Best
};