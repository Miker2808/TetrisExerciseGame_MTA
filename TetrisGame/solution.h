#pragma once
#include "Utility.h"
#include "MultiplayerTetris.h"

struct Solution {
    double height_penalty;
    double max_height_penality;
    double holes_penality;
    double bumpiness_penality;

    double fitness_score;
    
    void fit();
};
