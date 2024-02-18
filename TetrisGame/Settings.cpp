#include "Settings.h"


const Controls Settings::ctrl_presets[2] = {
	{'d','D','a','A','w','W','s','S','x','X'}, // Controls for player 1
	{'l','L','j','J','k','K','i','I','m','M'}  // Controls for player 2
};

// Holds the AI profile settings for three difficulty levels: Novice, Good, and Best. 
// Each element of the array is an instance of the TetrisAIProfile struct.
// Each defines the heuristic weights for the AI.
const TetrisAIProfile Settings::bot_difficulties[3] = {
	{0.627633 , 0.756441 , 0.254815, 0.9763},//Novice
	{0.926435 , 0.778338 , 0.404692, 0.579211},//Good
	{0.626957 , 0.830306 , 0.552015, 0.195814}//Best
};