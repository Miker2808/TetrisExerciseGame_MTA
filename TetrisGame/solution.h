#pragma once
#include "Utility.h"
#include "MultiplayerTetris.h"

struct Solution {
    double max_height_penality;
    double holes_penality;
    double bumpiness_penality;

    double fitness_score;
    
    void fit();
};
