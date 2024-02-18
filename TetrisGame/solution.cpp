#include "solution.h"


// Evaluate the fitness of the solution by simulating Tetris games
void Solution::fit(const int num_of_simulations) {
	// Variable to store the average number of blocks placed in simulations
	double avg_blocks_placed = 0;
	double game_too_long_penalty = 5000;

	// Perform simulations to evaluate the solution's fitness
	for (int i = 0; i < num_of_simulations; i++) {
		// Create a Tetris game instance
		AITetrisGame game(0, 0,  true ,false);
		// Flag to indicate if the game lasts too long
		bool game_to_long = false;
		game.setAIWeights( max_height_penality, holes_penality, bumpiness_penality, lines_reward);

		// Simulate the Tetris game until game over or game lasts too long
		while (!game.isGameOver() && !game_to_long)
		{
			game.play(0);

			if (game.blocks_placed > 500)
				game_to_long = true;
		}
		if(!game_to_long)
			avg_blocks_placed += (double)game.blocks_placed / num_of_simulations;
		else
			avg_blocks_placed += game_too_long_penalty / num_of_simulations;

	}

	// Update the fitness score based on the average blocks placed
	if (avg_blocks_placed == 400)
		fitness_score = 99999999;
	else
		fitness_score += 1 / (abs(400 - avg_blocks_placed));
};