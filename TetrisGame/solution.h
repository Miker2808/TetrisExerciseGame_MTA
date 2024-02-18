#pragma once
#include "Utility.h"
#include "MultiplayerTetris.h"

struct Solution {
    // Penalty for the maximum height of the Tetris stack
    double max_height_penality;
    // Penalty for the number of holes in the Tetris stack
    double holes_penality;
    // Reward for the number of lines cleared in Tetris
    double lines_reward;
    // Penalty for the bumpiness of the Tetris stack
    double bumpiness_penality;


    // Fitness score of the solution
    double fitness_score;

    //stats for testing spesific solutions
    double blocks_placed_avg = 0;
    double blocks_placed_std_dev = 0;
    double score_avg = 0;
    double score_std_dev = 0;
    double blocks_placed_variance = 0;
    double score_variance = 0;

    
    void fit(int num_of_simulations);
    void generateStats(const int num_of_simulations, bool bombs);
};
