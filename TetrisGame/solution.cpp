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

// Function to generate statistics for the solution based on simulations
void Solution::generateStats(const int num_of_simulations, bool bombs) {
    // Variables to store statistics
    std::vector<double> blocks_placed; // Store the number of blocks placed in each simulation
    std::vector<double> score; // Store the score achieved in each simulation

    // Perform simulations to evaluate the solution's performance
    for (int i = 0; i < num_of_simulations; i++) {
        // Create a Tetris game instance
        AITetrisGame game(0, 0, bombs, false);
        // Flag to indicate if the game lasts too long
        bool game_to_long = false;
        // Set AI weights based on solution parameters
        game.setAIWeights(max_height_penality, holes_penality, bumpiness_penality, lines_reward);

        // Simulate the Tetris game until game over
        while (!game.isGameOver()) {
            game.play(0); // Play the game with the AI
        }

        // Store the score and number of blocks placed from the simulation
        score.push_back(game.player->score);
        blocks_placed.push_back(game.blocks_placed);
        
        gotoxy(0, 0);
        std::cout << "Progress " << (i*100)/num_of_simulations << '%';
    }

    // Calculate the average number of blocks placed
    double blocks_placed_sum = 0;
    for (double blocks : blocks_placed) {
        blocks_placed_sum += blocks;
    }
    this->blocks_placed_avg = blocks_placed_sum / num_of_simulations;

    // Calculate the average score
    double score_sum = 0;
    for (double s : score) {
        score_sum += s;
    }
    this->score_avg = score_sum / num_of_simulations;

    // Calculate the variance of blocks placed
    for (double blocks : blocks_placed) {
        this->blocks_placed_variance += pow(blocks - blocks_placed_avg, 2);
    }
    this->blocks_placed_variance /= num_of_simulations;

    // Calculate the variance of score
    for (double s : score) {
        this->score_variance += pow(s - score_avg, 2);
    }
    this->score_variance /= num_of_simulations;

    // Calculate the standard deviation
    this->blocks_placed_std_dev = sqrt(blocks_placed_variance);
    this->score_std_dev = sqrt(score_variance);

    // Now you have blocks_placed_avg, score_avg, blocks_placed_std_dev, and score_std_dev
    // which represent the average, standard deviation, and variance for blocks placed and score.
}