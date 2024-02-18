#pragma once
#include "Utility.h"
#include "MultiplayerTetris.h"

struct Solution {
    // Penalty for the maximum height of the Tetris stack
    double max_height_penality;
    // Penalty for the number of holes in the Tetris stack
    double holes_penality;
    // Penalty for the bumpiness of the Tetris stack
    double bumpiness_penality;
    // Reward for the number of lines cleared in Tetris
    double lines_reward;

    // Fitness score of the solution
    double fitness_score;
    
    void fit(int num_of_simulations);
};
