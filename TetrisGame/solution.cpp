#include "solution.h"



void Solution::fit() {

	for (int i = 0; i < 10; i++){
		int ticks_survived = 0;
		AITetrisGame game(0, 0, false, false);
		game.setAIWeights(height_penalty, max_height_penality, holes_penality, bumpiness_penality);
		while (!game.isGameOver())
		{
			game.play(0);
			ticks_survived++;
		}
		fitness_score += ((double)ticks_survived) /1000000;
		// fitness_score =  0 - std::abs(10000 - ticks_survived)/100;
		// fitness_score =  0 - std::abs(100 - ticks_survived)/100;
	}
};